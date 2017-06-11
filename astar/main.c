#include "main.h"

typedef struct {
	double heuristique;
	double timespent;
	int type;
	int by;
	int done;
	char line[5];
} star;

int findName(sta* stations, int size, char* name) {
	int i;
	for (i = 0; i < size; i++){
		if (!(strcmp(stations[i].name,name)))
			return stations[i].id;
	}
	return -1;
}

int findId(sta* stations, int size, int id) {
	int i;
	for (i = 0; i < size; i++){
		if (stations[i].id == id)
			return i;
	}
	return -1;
}

int firstnotDone(star* S, int size){
	int i;
	for (i = 0; i < size; i++) {
		if (S[i].done == 0)
			break;
	}
	if (i < size) return i;
	else return -1;
}

int minStar(star* S, int size) {
	int i,imin = firstnotDone(S,size);
	if (imin + 1) {
		double min = S[imin].heuristique + S[imin].timespent;
		for (i = imin + 1; i < size; i++) {
			if (S[i].heuristique + S[i].timespent < min && !(S[i].done)) {
				min = S[i].heuristique + S[i].timespent;
				imin = i;
			}
		}
		return imin;
	} else return -1;
}

star* Astar(alscd* Session, sta* stations, move** Matrix, int size, int idBeg, int idEnd) {
	int i, id, n = 0;
	printf("from %d to %d\n", idBeg, idEnd);
	star* S = Alloc(Session, size*sizeof(star));
	// Initialisation
	for (i = 0; i < size; i++){
		S[i].heuristique = distanceLatLon(stations[i].lat,stations[i].lon,stations[idEnd].lat,stations[idEnd].lon);
		S[i].timespent = 1.0/0.0;
		S[i].type = PIETON;
		S[i].by = idBeg;
		S[i].done = 0;
	}
	S[idBeg].timespent = 0.0;
	for (id = idBeg; id != idEnd && id != -1; id = minStar(S,size)) {
		S[id].done = 1;
		for (i = 0; i < size; i++) {
			if (!(S[i].done)){
				if (S[i].timespent + S[i].heuristique > S[id].timespent + S[id].heuristique + Matrix[id][i].time) {
					S[i].timespent = S[id].timespent + Matrix[id][i].time;
					S[i].by = id;
					S[i].type =  Matrix[id][i].type;
					memcpy(S[i].line, Matrix[id][i].line, 5);
				}
			}
		}
		// for(i = 0; i < size; i++)
		// 	printf("%d\t%lf_by%d(%d)\t", i, S[i].timespent, S[i].by, S[i].type);
		n++;
	}
	if (id == -1) {
		printf("Out of Range\n");
		return NULL;
	}
	else printf("Reached the end in %d steps\n",n);
	return S;
}

void out(path P, star* S,int idEnd,sta* stations,char* filename){
	FILE* F = NULL;
	F = fopen(filename,"w+");
	if (F) {
		int tb = (int)P.time - 1495584000;
		int te = (int)S[idEnd].timespent + tb;
		int hb = tb/3600;
		int he = te/3600;
		int mb = (tb%3600)/60;
		int me = (te%3600)/60;
		fprintf(F,"%d:%d\r\n",hb,mb);
		fprintf(F,"%d:%d\r\n",he,me);
		fprintf(F,"Ligne : %s\n",S[idEnd].line);
		fprintf(F,"Station de depart : %s\n",stations[idEnd].name);
		fclose(F);
	} else {
		printf("Couldn't open file %s",filename);
		exit (-1);
	}
}

int main(int argc, char **argv) {
	system("tabs 4");
	alscd* Sess = NewLscdAlloc();
	int size = 0;//,i;//,j;
	sta* stations = NULL;
	move** Matrix = NULL;
	star* S = NULL;
	stations = getStations("../data/useful bdd/GraphMetroRER.txt", &size);
	Matrix = getMatrix(Sess,"../data/useful bdd/GraphMetroRER.txt", stations, size);
	printf("There are %d stations\n", size);
	printf("\tEach station is %lu bytes\n", sizeof(sta));
	printf("\tEach move is    %lu bytes\n", sizeof(move));
	printf("Memory size : \n");
	printf("\tStations take   %d bytes\n", size*(int)sizeof(sta));
	printf("\tMatrix takes    %d bytes\n", size*size*(int)sizeof(move));
	printf("Total memory is %d bytes\n", size*size*(int)sizeof(move) + size*(int)sizeof(sta));
	printf("%s\n%s\n",argv[1],argv[2]);
	path P = getPath("Demande_user.txt");
	printf("%lf\n%s -> %s\n%d\n",P.time,P.beg,P.end,P.type);
	int idBeg = findName(stations, size, P.beg);
	int idEnd = findName(stations, size, P.end);
	if (idBeg != -1 && idEnd != -1) {
		idBeg = findId(stations, size, idBeg);
		idEnd = findId(stations, size, idEnd);
		S = Astar(Sess,stations,Matrix,size,idBeg,idEnd);
		if (S) {
			printf("Arrived in %lf s\n",S[idEnd].timespent);
			out(P,S,idEnd,stations,"feuille_route.txt");
		} else
			printf("Problem with Astar\n");
	} else printf("Couldn't find those stations\n");
	FreeAll(Sess);
	free(stations);
	return 0;
}
