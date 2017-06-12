////////////////////////////////////////////////////////////////////////////////
//Easy way to allocate and free any structure
////////////////////////////////////////////////////////////////////////////////
#ifndef _EASYALLOC_H_
#define _EASYALLOC_H_
#include <stdio.h>
#include <stdlib.h>

/*
start your code with : alscd* AllocationList = NewLscdAlloc();
use the functions with AllocationList as the alscd* argument
finish it with : FreeLscdAlloc(AllocationList);
:
alscd* AllocationList = NewLscdAlloc();
//code
FreeAll(AllocationList);
*/

typedef struct ealscd{
  void* data;
  struct ealscd* nxt;
  struct ealscd* prv;
} ealscd;

typedef struct alscd{
  ealscd* head;
  ealscd* tail;
  ealscd* curr;
  unsigned int size;
} alscd;

alscd* NewLscdAlloc();
ealscd* NewHeadLscdAlloc(alscd* L);
ealscd* NewTailLscdAlloc(alscd* L);
void DelHeadLscdAlloc(alscd* L);
void DelTailLscdAlloc(alscd* L);
void FreeAll (alscd* L);
void Delete(alscd* L, void* data);
void* Alloc(alscd* L,size_t type);

#endif
