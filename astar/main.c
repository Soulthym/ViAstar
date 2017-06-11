#include "main.h"

// int idMinValue(move* M,int size,int id) {
// 	int i;
// 	for (i = 0; i < size; i++) {
//
// 	}
// }

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
