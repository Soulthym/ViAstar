#ifndef _GETFILE_C_
#define _GETFILE_C_

#include "getfile.h"

void lower(char* str) {
	int i;
	for (i = 0; str[i] != '\0'; i++){
		str[i] = (char)tolower(str[i]);
	}
	// printf("%s\n",str);
}

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
		if (p) {
			*p = new;
		}
	} while (p);
}

char* findlast(char* chaine, char find) {
	char *c = NULL, *p = NULL;
	c = strchr(chaine, find);
	while (c) {
		p = c;
		c = strchr(c+1, find);
	}
	return p;
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
			return i+1;
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
		long double lat, lon;
		char line[255] = {'\0'};
		char endChars[4] = {'\n', EOF, '\r', '\0'};
		sta *stations = NULL;
		int size = 0;//, i;
		stations = malloc(sizeof(sta));
		stations[0].id = -1;
		char name[255] = {'\0'};
		while (fgetStr(F, line ,sizeof line, endChars)) {
			replace(line,'\n','\0');
			replace(line,'\r','\0');
			if (line[0] != '\"') {
				sscanf(line,"%d",&id);
				if (isinSta(stations, size, id) == 0) {
					memcpy(name,line,sizeof(char)*255);
					size++;
					stations = realloc(stations,sizeof(sta)*size);
					*findlast(name,'\"') = '\0';
					replace(name,' ','_');
					// printf("%s\n",name);
					lower(name);
					sscanf(name, "%*d_\"%s",stations[size-1].name);
					replace(stations[size-1].name,'_',' ');
					// printf("%s\n",stations[size-1].name);
					stations[size-1].id = id;
					sscanf(findlast(line,'\"'),"\" %Lf %Lf",&lat,&lon);
					stations[size-1].lat = lat;
					stations[size-1].lon = lon;
				}
			}
		}
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
	return distanceLatLon(lat1,lon1,lat2,lon2)/0.11; // un pieton marche en moyenne a 1.15 m/s
}

double tempsMetro(long double lat1, long double lon1, long double lat2, long double lon2) {
	return distanceLatLon(lat1,lon1,lat2,lon2)/5.875; // un metro avance en moyenne a 5.875 m/s
}

double tempsRER(long double lat1, long double lon1, long double lat2, long double lon2) {
	return distanceLatLon(lat1,lon1,lat2,lon2)/13.9; // un RER avance en moyenne a 13.9 m/s
}

move** getMatrix(alscd* Session, char* filename, sta* stations, int size) {
	FILE* F = NULL;
	int i,j;
	move** Matrix = NULL;
	Matrix = Alloc(Session,sizeof(move*)*size);
	for (i = 0; i < size; i++) {
		Matrix[i] = Alloc(Session, sizeof(move)*size);
		for (j = 0; j < size; j++){
			Matrix[i][j].time = 1.0/0.0;
			Matrix[i][j].type = PIETON;
		}
	}
	F = fopen(filename,"r");
	if (F) {
		fseek(F, 0, SEEK_SET);
		char line[255] = {'\0'};
		char prev[255] = {'\0'};
		char endChars[4] = {'\n', EOF, '\r', '\0'};
		char rer[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		char metro[11] = "0123456789";
		char ligne[5] = {'\0'};
		int skip = 0, idBeg = 0, idEnd = 0;
		long double lat1 = 0,lat2 = 0,lon1 = 0,lon2 = 0;
		double t = 0;
		int type = PIETON;
		fgetStr(F, line ,sizeof line, endChars);
		memcpy(prev,line,sizeof line*sizeof(char));
		fseek(F, 0, SEEK_SET);
		while (fgetStr(F, line ,sizeof line, endChars)){
			replace(line,'\n','\0');
			replace(line,'\r','\0');
			if (line[0] == '\"') {
				if (strchr(metro,line[1])) {
					type = METRO;
				} else if (strchr(rer,line[1])) {
					type = RER;
				}
				skip = 1;
				replace(line,'\"','\0');
				memcpy(ligne,line+sizeof(char),5);
				replace(ligne,'\"','\0');
			} else {
				if (!(skip)) {
					sscanf(prev,"%d",&idBeg);
					sscanf(line,"%d",&idEnd);
					sscanf(findlast(prev,'\"'),"\" %Lf %Lf",&lat1,&lon1);
					sscanf(findlast(line,'\"'),"\" %Lf %Lf",&lat2,&lon2);
					// printf("\t%d\tto\t%d\t%Lf,%Lf\tto\t%Lf,%Lf\t",
					// idBeg, idEnd, lat1, lon1, lat2, lon2);
					switch (type) {
						case RER:
							t = tempsRER(lat1, lon1, lat2, lon2);
							// printf("%lf\tRER\n",t);
							break;
						case METRO:
							t = tempsMetro(lat1, lon1, lat2, lon2);
							// printf("%lf\tMETRO\n",t);
							break;
						case PIETON:
						default:
							t = tempsPieton(lat1, lon1, lat2, lon2);
							// printf("%lf\tPIETON\n",t);
							break;
					}
					memcpy(Matrix[isinSta(stations,size,idBeg)-1][isinSta(stations,size,idEnd)-1].line,ligne,5);
					Matrix[isinSta(stations,size,idBeg)-1][isinSta(stations,size,idEnd)-1].time = t;
					Matrix[isinSta(stations,size,idBeg)-1][isinSta(stations,size,idEnd)-1].type = type;
					// Matrix[idBeg][idEnd].type = type;
				}
				skip = 0;
			}
			memcpy(prev,line,sizeof line*sizeof(char));
		}
		fclose(F);
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++){
				if (Matrix[i][j].time == 1.0/0.0) {
					t = tempsPieton(stations[i].lat, stations[i].lon, stations[j].lat, stations[j].lon);
					Matrix[i][j].time = t;
					// printf("%Lf,%Lf\tto\t%Lf,%Lf = %lf s\n",stations[i].lat, stations[i].lon, stations[j].lat, stations[j].lon, t);
					// getchar();
					Matrix[i][j].type = PIETON;
				}
			}
		}
		return Matrix;
	} else {
		printf("Couldn't open file %s",filename);
		exit (-1);
	}
}

path getPath(char* filename) {
	FILE* F = NULL;
	path P;
	char endChars[4] = {'\n', EOF, '\r', '\0'};
	char line[255] = {'\0'};
	F = fopen(filename,"r");
	if (F) {
		fgetStr(F, line ,sizeof line, endChars);
		P.time = (double)atoi(line);
		fgetStr(F, line ,sizeof line, endChars);
		replace(line,'\n','\0');
		replace(line,'\r','\0');
		memcpy(P.beg,line,50);
		fgetStr(F, line ,sizeof line, endChars);
		replace(line,'\n','\0');
		replace(line,'\r','\0');
		memcpy(P.end,line,50);
		fgetStr(F, line ,sizeof line, endChars);
		P.type = atoi(line);
		if (P.type == 3) {
			fgetStr(F, line ,sizeof line, endChars);
			replace(line,' ','_');
			sscanf(line,"%s",P.avoid);
			replace(P.avoid,'_',' ');
		}
		fclose(F);
		return P;
	} else {
		printf("Couldn't open file %s",filename);
		exit (-1);
	}
}

#endif
