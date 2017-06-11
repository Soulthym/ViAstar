#include "main.h"

typedef struct {
	double heuristique;
	double timespent;
	int type;
	int by;
} star;

int minValue(*star S,int size,int id) {
	int i,imin = 0;
	double min = S[0];
	for (i = 1; i < size; i++) {
		if (S[i] < min) {
			min = S[i];
			imin = i;
		}
	}
	return imin;
}

star* Astar(alscd* Session, sta* stations, move** Matrix, int size, int idBeg, int idEnd) {
	int i,id;
	star* S = Alloc(Session, size*sizeof(star));
	// Initialisation
	for (i = 0; i < size; i++){
		S[i].heuristique = distanceLatLon(stations[i].lat,stations[i].lon,stations[idEnd].lat,stations[idEnd].lon);
		S[i].timespent = 0;
		S[i].type = PIETON;
		S[i].by = idBeg;
	}
	id = idBeg;
	for ()
}

int main(int argc, char **argv) {
	system("tabs 4");
	alscd* Sess = NewLscdAlloc();
	int size = 0;//,i,j;
	sta* stations = NULL;
	move** Matrix = NULL;
	stations = getStations("../data/useful bdd/GraphMetroRER.txt", &size);
	printf("%s\n",stations[1266].name);
	Matrix = getMatrix(Sess,"../data/useful bdd/GraphMetroRER.txt", stations, size);
	printf("There are %d stations\n", size);
	printf("\tEach station is %lu bytes\n", sizeof(sta));
	printf("\tEach move is    %lu bytes\n", sizeof(move));
	printf("Memory size : \n");
	printf("\tStations take   %d bytes\n", size*(int)sizeof(sta));
	printf("\tMatrix takes    %d bytes\n", size*size*(int)sizeof(move));
	printf("Total memory is %d bytes\n", size*size*(int)sizeof(move) + size*(int)sizeof(sta));
	FreeAll(Sess);
	free(stations);
	return 0;
}
