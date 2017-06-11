#include "main.h"
#include <float.h>
#include <math.h>
#include <string.h>

#define pi 3.14159265358979323846

typedef struct {
    int id;
    char name[50];
    long double lat;
    long double lon;
} sta;

typedef struct {
    int type; //0 pieton    1 metro     2 RER
    double time;
} move;

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

int isinSta(sta* Tab, size_t size, int value) {
    size_t i;
    for (i = 0; i < size; i++) {
        if (Tab[i].id == value) {
            return 1;
        }
    }
    return 0;
}

sta* getStations(char* filename, int* sizeret) {
    FILE* F = NULL;
    F = fopen(filename,"r");
    if (F) {
        fseek(F, 0, SEEK_SET);
        int id = 0;
        char line[255] = {'\0'};
        char endChars[4] = {'\n', EOF, '\r', '\0'};
        sta *stations = NULL;
        int size = 1, i;
        stations = malloc(sizeof(sta));
        while (fgetStr(F, line ,sizeof line, endChars)) {
            replace(line,'\n','\0');
            replace(line,'\r','\0');
            if (line[0] != '\"') {
                sscanf(line,"%d",&id);
                if (isinSta(stations, size, id) == 0) {
                    size++;
                    stations = realloc(stations,sizeof(sta)*size);
                    stations[size-1].id = id;
                }
            }
        }
        for (i = 0; i < size; i++)
            printf("%d_%d\n",i,stations[i].id);
        fclose(F);
        *sizeret = size;
        return stations;
    } else {
        printf("Couldn't open file %s",filename);
        exit (-1);
    }
}

double distanceLatLon(long double lat1, long double lon1, long double lat2, long double lon2) {
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
  int size = 0;
  sta* stations = NULL;
  move* Matrix = NULL;
  stations = getStations("../data/useful bdd/GraphMetroRER.txt", &size);
  // Matrix = getMatrix("");
  printf("There are %d stations\n", size);
  printf("Each station is %lu bytes\n", sizeof(sta));
  printf("Each move is    %lu bytes\n", sizeof(move));
  printf("Memory size : \n");
  printf("Stations take   %d bytes\n", size*(int)sizeof(sta));
  printf("Matrix takes    %d bytes\n", size*size*(int)sizeof(move));
  FreeAll(Sess);
  free(stations);
  return 0;
}
