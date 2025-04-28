#include <stdio.h>
#include <stdlib.h>
#include "genericVector.h"

struct genericVector{
	int size;
	int capacity;
	ITEM* data;
	ITEM (*initCopy)(ITEM);
	void (*destroy)(ITEM*);
};typedef struct genericVector GenericVector;

GENERICVECTOR genericVectorInitDefault( ITEM(*initCopy)(ITEM), void (*destroy)(ITEM*)){
	GenericVector* pVector;
	int i;
	pVector = malloc(sizeof(GenericVector));
	if(pVector != NULL){
		pVector->size = 0;
		pVector->capacity = 1;
		pVector->initCopy = initCopy;
		pVector->destroy = destroy;
		pVector->data = (ITEM*)malloc(sizeof(ITEM) * pVector->capacity);
		if(pVector->data == NULL){
			free(pVector);
			return NULL;
		}
		for(i = 0; i < pVector->capacity; i++){
			pVector->data[i] = NULL;
		}
	}
	return pVector;
}

/**
 * this function needed to be created so that a GenericVector of GenericVectors could be created
 * @param vec vector that will be copied
 * @return pointer to a new GenericVector that is a deep copy of the passed in vector
 */
GENERICVECTOR genericVectorInitCopy(GENERICVECTOR vec) {
	GenericVector* vectorToCopy = (GenericVector*)vec;
	GenericVector* copyVector = (GenericVector*)malloc(sizeof(GenericVector));
	//malloc can fail
	if(copyVector == NULL) {
		return NULL;
	}else{//first malloc succeeded
		copyVector->data = (ITEM*)malloc(sizeof(ITEM) * genericVectorGetCapacity(vectorToCopy));
		//malloc can still fail
		if(copyVector->data == NULL) {
			//cLion DEMANDED I put this line
			free(copyVector->data);
			//free the allocated struct
			free(copyVector);
			return NULL;
		}else {
			//both mallocs pass
			copyVector->capacity = genericVectorGetCapacity(vectorToCopy);
			copyVector->size = genericVectorGetSize(vectorToCopy);
			copyVector->initCopy = vectorToCopy->initCopy;
			copyVector->destroy = vectorToCopy->destroy;
			//now to copy over the data
			for(int i = 0; i < genericVectorGetSize(copyVector); i++) {
				//since it genericVectorAt() could return NULL, but I index it that would segfault so just check
				if(genericVectorAt(vectorToCopy, i) == NULL) {
					copyVector->data[i] = NULL;
				}else{//else means that it's fine and this won't cause a segfault
					copyVector->data[i] = copyVector->initCopy(genericVectorAt(vectorToCopy, i)[0]);
				}
			}
		}
	}

	return copyVector;
}
Boolean genericVectorIsEmpty(GENERICVECTOR hVector){
	GenericVector* pVector = (GenericVector*)hVector;
	return (Boolean)(pVector->size <= 0);
}

Status genericVectorPushBack(GENERICVECTOR hVector, ITEM hItem){
	GenericVector* pVector = (GenericVector*)hVector;
	ITEM* temp;
	int i;

	if(pVector->size >= pVector->capacity){//if there is not enough space try to make spase
		temp = (ITEM*)malloc(sizeof(ITEM) * pVector->capacity * 2);
		if(temp == NULL){//malloc can fail
			return FAILURE;
		}
		for(i = 0; i < pVector->size; i++){
			temp[i] = pVector->data[i];//shallow copy
		}
		for(; i < pVector->capacity * 2; i++){
			temp[i] = NULL;
		}
		free(pVector->data);
		pVector->data = temp;
		pVector->capacity *= 2;
	}

	pVector->data[pVector->size] = pVector->initCopy(hItem);
	if(pVector->data[pVector->size] == NULL){
		return FAILURE;
	}
	pVector->size++;
	return SUCCESS;
}

int genericVectorGetSize(GENERICVECTOR hVector){
	GenericVector* pVector = (GenericVector*)hVector;
	
	return pVector->size;
}

int genericVectorGetCapacity(GENERICVECTOR hVector){
	GenericVector* pVector = (GenericVector*)hVector;

	return pVector->capacity;
}

ITEM* genericVectorAt(GENERICVECTOR hVector, int index){
	GenericVector* pVector = (GenericVector*)hVector;

	if(index < 0 || index >= pVector->size){
		return NULL;
	}
	return pVector->data + index;
}

Status genericVectorPopBack(GENERICVECTOR hVector){
	GenericVector* pVector = (GenericVector*)hVector;

	if(genericVectorIsEmpty(hVector)){
		return FAILURE;
	}
	pVector->destroy(&pVector->data[pVector->size - 1]);
	pVector->size--;
	return SUCCESS;
}

void genericVectorDestroy(GENERICVECTOR* phVector){
	GenericVector* pVector = (GenericVector*)*phVector;
	for(int i = 0; i < pVector->size; i++){
		pVector->destroy(&pVector->data[i]);
	}
	free(pVector->data);
	free(pVector);
	*phVector = NULL;
}

