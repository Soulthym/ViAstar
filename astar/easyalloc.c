#ifndef _EASYALLOC_C_
#define _EASYALLOC_C_

#include "easyalloc.h"

alscd* NewLscdAlloc() {
	alscd* L = malloc(sizeof(alscd));
	L->head = NULL;
	L->tail = NULL;
	L->curr = NULL;
	L->size = 0;
	return L;
}

ealscd* NewHeadLscdAlloc(alscd* L) {
	L->curr = malloc(sizeof(ealscd));
	L->curr->nxt = L->head;
	if (L->head)	L->head->prv = L->curr;
	L->head = L->curr;
	if (!L->tail)	L->tail = L->head;
	L->head->data = NULL;
	L->size ++;
	return L->head;
}

ealscd* NewTailLscdAlloc(alscd* L) {
	L->curr = malloc(sizeof(ealscd));
  L->curr->prv = L->tail;
  if (L->tail)	L->tail->nxt = L->curr;
  L->tail = L->curr;
  if (!L->head)	L->head = L->tail;
	L->tail->nxt = NULL;
	L->tail->data = NULL;
	L->size ++;
	return L->tail;
}

void DelHeadLscdAlloc(alscd* L) {
  if (L->head) {
    L->curr = L->head->nxt;
    free(L->head->data);
    free(L->head);
    L->head = L->curr;
    if (L->head)	L->head->prv = NULL;
    else	L->tail = NULL;
    L->size--;
  }
}

void DelTailLscdAlloc(alscd* L) {
  if (L->tail) {
    L->curr = L->tail->prv;
    free(L->tail->data);
    free(L->tail);
    L->tail = L->curr;
    if (L->tail)	L->tail->nxt = NULL;
    else	L->head = NULL;
    L->size--;
  }
}

void FreeAll (alscd* L) {
  while(L->size > 0)
    DelHeadLscdAlloc(L);
  free(L);
}

void Delete(alscd* L, void* data) {
	for (L->curr = L->head;L->curr != NULL; L->curr = L->curr->nxt){
		if (L->curr->data == data) break;
	}
	if(L->curr) {
		ealscd* tmp = L->curr;
		free(data);
		if (L->curr->prv)	L->curr->prv->nxt = L->curr->nxt;
		if (L->curr->nxt)	L->curr->nxt->prv = L->curr->prv;
		free(tmp);
		L->size --;
	}
}

void* Alloc(alscd* L,size_t type) {
  void* new = malloc(type);
  NewHeadLscdAlloc(L)->data = new;
  return new;
}

#endif
