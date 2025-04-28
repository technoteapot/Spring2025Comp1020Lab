#ifndef GENERICVECTORH
#define GENERICVECTORH
#include "generic.h"
#include "status.h"

typedef void* GENERICVECTOR;

GENERICVECTOR genericVectorInitDefault(ITEM (*initCopy)(ITEM), void (*destroy)(ITEM*));

Status genericVectorPushBack(GENERICVECTOR hVector, ITEM hItem);

//pop back
Status genericVectorPopBack(GENERICVECTOR hVEctor);

Boolean genericVectorIsEmpty(GENERICVECTOR hVector);

ITEM* genericVectorAt(GENERICVECTOR hVector, int index);

int genericVectorGetSize(GENERICVECTOR hVector);
int genericVectorGetCapacity(GENERICVECTOR hVector);

void genericVectorDestroy(GENERICVECTOR* phVector);

//this is added by cullen so that it is possible to make a vector of vectors
GENERICVECTOR genericVectorInitCopy(GENERICVECTOR vector);

#endif
