#include "main.h"

typedef struct station{
  int id;
  char name[50];
  double lat;
  double lon;
  struct station *nxt;
}sta;

typedef struct ligne{
  sta* start;
  sta* end;
  sta* curr;
  char name[3];
}lig;

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
    double lat = .0;
    double lon = .0;
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
        fscanf(F,"%lf\n",&lat);
        fscanf(F,"%lf\n",&lon);
        printf("\tstation : %s\n",station);
        printf("\t\tid : %d\n",id);
        printf("\t\tlat : %g\n",lat);
        printf("\t\tlon : %g\n",lon);
      }
    }
    fclose(F);
    return NULL;
  } else {
    printf("EMPTY FILE \"%s\"\n",filename);
    exit(-1);
  }
}

int main(int argc, char **argv) {
  alscd* Sess = NewLscdAlloc();
  getGraphFromFile("data.txt",Sess);
  FreeAll(Sess);
  return 0;
}
