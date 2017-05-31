#include "main.h"

void print(int val) {
  printf("%d\n",val);
}

void DelApostrophe(char* str) {
  int i;
  for (i = 0; str[i] != '\0'; i++) {
    
  }
}

void* getGraphFromFile(char* filename, alscd* Session) {
  FILE* F = NULL;
  F = fopen(filename,"r");
  if (F) {
    fseek(F, 0L, SEEK_SET);
    long unsigned int pos = ftell(F);
    // int running = 1;
    // print(pos);
    char ligne[100] = {'\0'};
    char station[100] = {'\0'};
    while(1) {
      if (fscanf(F,"\"%s",ligne) == 1)
        printf("%s",ligne);
      else
        break;
      // printf("k\n");
    }
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

/*use :
alscd* Sess = NewLscdAlloc();
int* a = Alloc(Sess, sizeof(int));
*a = 10;
printf("%d\n",*a);
FreeAll(Sess);
return 0;
*/
