#ifndef _GETFILE_H_
#define _GETFILE_H_

#include <float.h>
#include <math.h>
#include <string.h>

#include "main.h"

#define pi 3.14159265358979323846

#define PIETON 0
#define METRO 1
#define RER 2

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

long double deg2rad(long double deg);
size_t fgetStr(FILE* F,char* str, size_t maxSize, char* endChars);
void replace(char *chaine, char find, char new);
char* findlast(char* chaine, char find);
void print(int val);
int sum(int* Tab, int size);
int isinSta(sta* Tab, size_t size, int value);
sta* getStations(char* filename, int* sizeret);
double distanceLatLon(long double lat1, long double lon1, long double lat2, long double lon2);
double tempsPieton(long double lat1, long double lon1, long double lat2, long double lon2);
double tempsMetro(long double lat1, long double lon1, long double lat2, long double lon2);
double tempsRER(long double lat1, long double lon1, long double lat2, long double lon2);
move** getMatrix(alscd* Session, char* filename, sta* stations, int size);

#endif
