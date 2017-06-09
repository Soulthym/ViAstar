#include "main.h"
#include <float.h>
#include <math.h>

#define pi 3.14159265358979323846

typedef struct station{
  int id;
  char name[50];
  long double lat;
  long double lon;
  struct station *nxt;
}sta;

typedef struct ligne{
  sta* start;
  sta* end;
  sta* curr;
  char name[5];
}lig;

long double deg2rad(long double deg) {
  return (deg * pi / 180);
}

lig* NewLig(alscd* Session){
  lig* L = Alloc(Session,sizeof(lig));
  L->start = NULL;
  L->end = NULL;
  L->curr = NULL;
  int i;
  for(i = 0; i < 3; i++)
    L->name[i] = '\0';
  return L;
}

sta* NewSta(alscd* Session){
  sta* S = Alloc(Session,sizeof(sta));
  S->id = -1;
  S->lat = -1;
  S->lon = -1;
  int i;
  for(i = 0; i < 50; i++)
    S->name[i] = '\0';
  return S;
}

void print(int val) {
  printf("%d\n",val);
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
  //getGraphFromFile("data.txt",Sess);
  // printf("%f\n",tempsPieton(48.783315, 2.286803, 47.884158, 6.275417));
  printf("%lu\n",sizeof(sta));
  FreeAll(Sess);
  return 0;
}
