//Author: Cullen Walsh
//date: 2/7/2025
//
#include "myString.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct myString{
	int size;
	int capacity;
	char* data;
};typedef struct myString MyString;


//this follows the pattern from class where a vector struct was made, defaulcapacity is 7, the starting size is 0 (bc it's empty) and the data char pointer is just as long as the capacity
MYSTRING myStringInitDefault(void){
	MyString* s = (MyString*)malloc(sizeof(MyString));
	if(s != NULL){
		s->size = 0;
		s->capacity = 7;
		s->data = (char*)malloc(sizeof(char) * s->capacity);
		//malloc can fail
		if (s->data == NULL){
			free(s);
			return NULL;
		}
	}
	return s;
}

//again following the pattern from class and the vector struct, this function just frees all the memory used in a MyString Struct
void myStringDestroy(MYSTRING* phMyString){
	MyString* pMyString = (MyString*)*phMyString;//cast to the known type
	free(pMyString->data);
	free(pMyString);
	*phMyString = NULL; //make sure to set the left over pointer to null
}

//an initialization function that initializes a cstring object that is a copy of the passed in NULL terminated Cstring, with the capacity being 1 more than the capacity of the passed in string
MYSTRING myStringInitCString(const char* CString){
	int i = 0;
	//find the capacity of the passed in string
	for(i = 0; *(CString + i) != '\0'; i++){}
	//i is now the length of the passed in string
	MyString* newString = (MyString*)malloc(sizeof(MyString));
	if(newString != NULL){//malloc can fail
		newString->size = i;//the size is just i
		newString->capacity = (i+1);//the capacity is 1 more than the size
		newString->data = (char*)malloc(sizeof(char) * newString->capacity);//allocates enough for the capacity
		if(newString->data == NULL){//malloc can fail
			free(newString);
			return NULL;
		}
	}else{//if malloc fails
		return NULL;
	}
	//now to copy the contents of the passed in string to the new string
	int counter = 0;
	while (counter < i){
	*(newString->data + counter) = *(CString + counter);//the value of data at the offset of counter is set equal to the value of CString at the offset of counter
	counter++;
	}
	*(newString->data + i) = '\0';//the final char in the string is null terminated
	return newString;
}


/**
 * returns the capacity of the passed in MYSTRING handle
 * */
int myStringGetCapacity(MYSTRING hMyString){
	MyString* s = (MyString*)hMyString;//cast to the known type
	return s->capacity;//just return the capacity
}

/**
 * returns the size of the passed in MYSTRING handle
 **/
int myStringGetSize(MYSTRING hMyString){
	MyString* s = (MyString*)hMyString;//cast to the known type
	return s->size;//just has to return the size
}

/**
 * compares two MYSTRING objects lexicographically.
 * returns an integer less than 0 if the string represented by hLeftString is lexicographically smaller than hRightString. if one string is a prefix of the other string the shorter one is smaller (app is less than apple)
 * returns 0 if the strings are the same
 * returns a number greater than 0 if the string represented by hLeftString is bigger than hRightString
 * **/
int myStringCompare(MYSTRING hLeftString, MYSTRING hRightString){
	MyString* left = (MyString*)hLeftString;
	MyString* right = (MyString*)hRightString;//cast to the known type
	int i = 0;
	//now compare the two lexicographically
	////ok chars can just be directly compared using < > =
	//iterate through each string until difference found
	for(i = 0; (right->data[i] != '\0' && left->data[i] != '\0'); i++){
		if(tolower(right->data[i]) == tolower(left->data[i])){
			continue;
		}else{
			return tolower(left->data[i]) - tolower(right->data[i]);
		}
	}if(right->data[i] == '\0' && left->data[i] == '\0'){//both reached their end and were the same
		return 0;
	}else if(right->data[i] == '\0'){
		return 1;
	}else{
		return -1;
	}//this can be further optimized but I think this would work fine
}
