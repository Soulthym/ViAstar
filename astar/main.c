#include "main.h"
#include <float.h>
#include <math.h>
#include <string.h>

#define pi 3.14159265358979323846

long double deg2rad(long double deg) {
  return (deg * pi / 180);
}

size_t fgetStr(FILE* F,char* str, size_t maxSize, char* endChars) {
    size_t i = 0;
    char c;
    for(c = fgetc(F);(i < maxSize); c = fgetc(F), i++) {
        if (strchr(endChars, c)) {
            str[i] = '\0';
            break;
        }
        str[i] = c;
    }
    return i;
}

void replace(char *chaine, char find, char new)
{
    char *p = NULL;
    do {
        p = strchr(chaine, find);
        if (p)
        {
            *p = new;
        }
    } while (p);
}

void print(int val) {
  printf("%d\n",val);
}

int sum(int* Tab, int size) {
    int i, sum = 0;
    for(i = 0; i < size; i++){
        sum += Tab[i];
    }
    return sum;
}

int countStations(FILE* F) {
    int id = 0;
    int max = 0;
    char line[255] = {'\0'};
    char endChars[4] = {'\n', EOF, '\r', '\0'};
    fseek(F, SEEK_SET,0);
    while (fgetStr(F, line ,sizeof line, endChars)) {
        replace(line,'\n','\0');
        replace(line,'\r','\0');
        if (line[0] != '\"') {
            sscanf(line,"%d",&id);
        }
        if (id > max)
            max = id;
    }
    printf("%d\n",max);
    int stations[max+1];
    // printf("%lu\n",sizeof stations);
    // int i;
    // for (i = 0; i < max+1; i++)
    //     stations[i] = 0;
    // fseek(F, SEEK_SET,0);
    // while (fgetStr(F, line, sizeof line, endChars)) {
    //     replace(line,'\n','\0');
    //     replace(line,'\r','\0');
    //     if (line[0] != '\"') {
    //         sscanf(line,"%d",&id);
    //         stations[id] = 1;
    //     }
    // }
    // return sum(stations,max+1);
}

void* getGraphFromFile(char* filename, alscd* Session) {
  FILE* F = NULL;
  F = fopen(filename,"r");
  if (F) {
    fseek(F, 0L, SEEK_SET);
    char c = EOF;
    char ligne[3] = {'\0'};
    char station[50] = {'\0'};
    int id = -1;
    long double lat = .0;
    long double lon = .0;
    while(1) {
      c = fgetc(F);
      if (c == '_'){
        fscanf(F,"%s\n",ligne);
        printf("ligne : %s\n",ligne);
      }
      else if (c == EOF)
        break;
      else {
        fseek(F,-1, SEEK_CUR);
        fscanf(F,"%d\n",&id);
        fscanf(F,"%s\n",station);
        fscanf(F,"%Lf\n",&lat);
        fscanf(F,"%Lf\n",&lon);
        printf("\tstation : %s\n",station);
        printf("\t\tid : %d\n",id);
        printf("\t\tlat : %.17Lg\n",lat);
        printf("\t\tlon : %.17Lg\n",lon);
      }
    }
    fclose(F);
    return NULL;
  } else {
    printf("EMPTY FILE \"%s\"\n",filename);
    exit(-1);
  }
}

double distanceLatLon(long double lat1, long double lon1, long double lat2, long double lon2) {
    // double distance = 6367445.0;
    // double distance = 6378137.0;
    // double distance = 6356752.3;
    double distance = 6371000.0;
    lat1 = deg2rad(lat1);
    lon1 = deg2rad(lon1);
    lat2 = deg2rad(lat2);
    lon2 = deg2rad(lon2);
    distance *= acos(sin(lat1)*sin(lat2)+cos(lat1)*cos(lat2)*cos(lon1-lon2));
    return distance;
}

double tempsPieton(long double lat1, long double lon1, long double lat2, long double lon2) {
    return distanceLatLon(lat1,lon1,lat2,lon2)/1.15; // un pieton marche en moyenne a 1.15 m/s
}

double tempsMetro(long double lat1, long double lon1, long double lat2, long double lon2) {
    return distanceLatLon(lat1,lon1,lat2,lon2)/5.875; // un metro avance en moyenne a 5.875 m/s
}

double tempsRER(long double lat1, long double lon1, long double lat2, long double lon2) {
    return distanceLatLon(lat1,lon1,lat2,lon2)/13.9; // un RER avance en moyenne a 13.9 m/s
}

int main(int argc, char **argv) {
  alscd* Sess = NewLscdAlloc();
  FILE* F = fopen("../data/useful bdd/GraphMetroRER.txt","r");
  printf("There are %d stations\n",countStations(F));
  fclose(F);
  // getGraphFromFile("data.txt",Sess);
  // printf("%f\n",tempsPieton(48.783315, 2.286803, 47.884158, 6.275417));
  // printf("%lu\n",sizeof(sta));
  FreeAll(Sess);
  return 0;
}
