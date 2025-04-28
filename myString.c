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
	}//this can be further optimized but this works fine
}




/**myStringExtraction
 * pulls the next string from the file stream that's passed in, according to the following rules:
 * leading whitespace is ignored
 * all characters afetr the first non whitespace character will be added to the string until a stopping condition is met. the capacity of the string will continue to grow as needed until all characters are stored. A stopping condition is met if we read a whitespace character after the first non-Whitespace character is met or if the end of the file is reached
 * function will return SUCCESS if a non empty string is read successfully, and FAILURE otherwise.
 **/
//~~~~~~~~~~~so this is going to asume that, string extraction will always wipe the incoming myString
Status myStringExtraction(MYSTRING hMyString, FILE* fp){
	MyString* extractTo = (MyString*)hMyString;//cast to the known type
	char stringIn[50] ;//the string read from the file - idk how to initialize this properly
	int stringInSize;
	int endCase = fscanf(fp, " %s", stringIn);//this is the end case for the function, 0 means no assignments, EOF means it found the end of the file or there was an error
	if(endCase == EOF || endCase == 0){
		return FAILURE;
	}
	//stringIn now holds the string
	//find the length of the string
	for (stringInSize = 0; stringIn[stringInSize] != '\0'; stringInSize++){}//stops when it finds the null terminator
	//get the capacity of the passed in myString
	const int myStringCapacity = myStringGetCapacity(extractTo);

	if(stringInSize > myStringCapacity){//if the passed in myString is too small for the thing
		char* temp = extractTo->data;
	  //have to resize the passed in string to allow it to handle the extracted string
     extractTo->data = (char*)malloc(sizeof(char) * (stringInSize + 1));//makes a new bigger pointer
     if(extractTo->data == NULL){
       //malloc failed
       extractTo->data = temp;
       return FAILURE;
       }
     extractTo->size = stringInSize;
     extractTo->capacity = (stringInSize+1);
     free(temp);
	}
		int j;
		//copy the string into the myString object
		for(j = 0; j < stringInSize; j++){
			extractTo->data[j] =  stringIn[j];//assign the values
		}
		//change the size of extractTo
		extractTo->size = j;
		//null terminate the string
		extractTo->data[j] = '\0';
		j++; 
		//fill in the rest of the string capacity with null
		for(j = j; j < myStringCapacity; j++){
			extractTo->data[j] = '\0';//just fill the rest of it with null
		}
		//return success because the extraction was a success
		return SUCCESS;				
}


//takes the string in the MYSTRING object and puts it to the FILE stream passed in
Status myStringInsertion(MYSTRING hMyString, FILE* fp){
	MyString* myStringInsert = (MyString*)hMyString;//cast to the known type

	if ( fprintf(fp, "%s", myStringInsert->data) > 0 ){
		return SUCCESS;
	}else{//if the return from fprintf is negative it means an error occured
		return FAILURE;
	}

	//if this triggers then there as something wacked
	return FAILURE;
}

//inserts the passed in character a the end of the passed in string object. retrurns success if it works and FAILURE if the string cannot be resized. if a resize is needed, increase the size up to 2x. just double the size
Status myStringPushBack(MYSTRING hMyString, char item){
	MyString* s = (MyString*)hMyString;//cast to the known type
	//check if the string could hold an extra character
	if((myStringGetSize(s) + 1) >= myStringGetCapacity(s)){//only executes if the size of the string plus 1 would be more than the capacity could hold
		//temp to hold the old string's address
		char* temp = s->data;
		s->data = (char*)malloc((myStringGetCapacity(s) * 2));//double the capacity of the string
		if(s->data == NULL){//malloc can fail
			s->data = temp;//preserve the object itself
			return FAILURE;
		}
		s->capacity = s->capacity * 2;//fix the held capacity value
		//copy the old data over to the new place
		const int oldSize = myStringGetSize(s);
		int i;
		for(i = 0; i < oldSize; i++){
			s->data[i] = temp[i];//copy over the data
		}//now i is at the final index of the string
		s->data[i] = item;//can just put the item at the end now
		i++;
		s->data[i] = '\0';//null terminate it
		s->size++;//fix the size field
		free(temp);//free the old data space
		return SUCCESS;//all this working would mean the function succeeded
	}else{//the string doesn't need a resize
		s->data[myStringGetSize(s)] = item;//the size is automatically going to be the address to put in item
		s->size++;//increment size
		return SUCCESS;//nothing else has to be done
	}
}

//removes the last character of a string in constant time. returns failure if the string is empty
Status myStringPopBack(MYSTRING hMyString){
	MyString* s = (MyString*)hMyString;//cast to the known type
	if(myStringEmpty(s) == TRUE){//myStringEmpty(s) returns a bool indicating whether the passed in string is empty or not
		return FAILURE;//fails if empty string
	}else{
		s->data[(myStringGetSize(s)-1)] = '\0';//put null in place of the last char
		s->size--;//fix the size value
		return SUCCESS;//succeeds if it just does the thing
	}
}

//gets the address of the character located at the specified index, if the specified index is out of bounds returns NULL. 
char* myStringAt(MYSTRING hMyString, int index){
	MyString* s = (MyString*)hMyString;//cast to the known type
	if(myStringGetSize(s) <= index){//this would mean that the index would be out of bounds for the string (out side of the size of the string
		return NULL;
	}else{//the specified index is within bounds
		return &(s->data[index]);//this will properly return the address of the char at the index specified, after checking the index specified is within bounds
	}
}

//returns the address of the first element of the string as a null terminated C string
char* myStringCStr(MYSTRING hMyString){
	MyString* s = (MyString*)hMyString;//cast to the known type
	return s->data;
}

//both parameters are handles to valid myString objects. the function adds hAppend to the end of the hResult string. resize result if needed, return FAILURE if the resize is unsuccessful, and SUCESS if the strings are successfully concatenated to hResult
Status myStringConcat(MYSTRING hResult, MYSTRING hAppend){
	MyString* result = (MyString*)hResult;//cast to the known type
	MyString* append = (MyString*)hAppend;//cast to the known type
	//first check if result can handle the addition of append, if not try to increase the capacity
	if((myStringGetSize(result) + myStringGetSize(append)) >= myStringGetCapacity(result)){//this means a resize is required
		char* temp = result->data; //hold hold the old string data
		result->data = (char*)malloc(myStringGetCapacity(result) * 2);//alloc twice the current capacity
		if(result->data == NULL){//malloc can fail
			result->data = temp;
			return FAILURE;//neither strings are affected and it returns failure
		}else{//it worked and data has a new address with more capacity
			result->capacity = result->capacity * 2;//fix capacity
			//copy over old data
			int i = 0;
			for (i = 0; i < myStringGetSize(result); i++){
				result->data[i] = temp[i];
			}
			result->data[i] = '\0';//null terminate
			free(temp);//free the old place the data resided
		}
	}//whether or not a resize is needed, need to finally concat the two
	
	int j = 0; 
	for(j = 0; j < myStringGetSize(append); j++){
	       //iterate through append putting the current char at the end of the result string by starting at the last character of the result string
	       	result->data[myStringGetSize(result) + j] = append->data[j];
	}
	//null terminate it for fun
	result->data[myStringGetSize(result) + j] = '\0';
	result->size = myStringGetSize(result) + myStringGetSize(append);//fix the resulting size
	return SUCCESS;//if it reaches here without error that means it probably worked
}

//returns TRUE if the passed in string is EMTPY and FALSE if it is NOT EMPTY
//more specifically it simply checks if the size is less than or equal to 0
Boolean myStringEmpty(MYSTRING hMyString){
	MyString* s = (MyString*)hMyString;//cast to the known type
	if(0 >= myStringGetSize(s)){
		return TRUE;
	}else{
		return FALSE;
	}
}

//makes hLeft into a complete copy of hRight, increasing capacity if needed, but not reducing capacity
Status myStringAssignment(MYSTRING hLeft, MYSTRING hRight){
	MyString* left = (MyString*)hLeft;
	MyString* right = (MyString*)hRight;
	//cast to the known type
	//check if left is big enough for righ
	if(myStringGetCapacity(left) <= myStringGetSize(right)){
		//temp to hold the old data
		char* temp = left->data;
		//malloc something bigger
		left->data = (char*)malloc(myStringGetSize(right)+1);
		//malloc can fail
		if(left->data == NULL){
			left->data = temp;
			return FAILURE;
		}else{//resize was successful
			left->capacity = (myStringGetSize(right) + 1);
			//free the old data
			free(temp);
		}
	}
	//past here means either the resize was successful or the resize is unneeded

	//now copy the data over
	int i = 0;
	for(i = 0; i < myStringGetSize(right); i++){
		left->data[i] = right->data[i];
	}
	left->data[i] = '\0';//null terminate it for fun :)
	//finally to fix the size
	left->size = myStringGetSize(right);
	return SUCCESS;
}

//makes a independant new copy of the passed in myString object
MYSTRING myStringInitCopy(MYSTRING hMyString){
	MyString* copyFrom = (MyString*)hMyString;//cast to the known type
	MyString* newCopy = (MyString*)malloc(sizeof(MyString));
	if(newCopy == NULL){//malloc can fail
		return NULL;
	}else{//first malloc succeeded
		newCopy->data = (char*)malloc(myStringGetCapacity(copyFrom));
		if(newCopy->data == NULL){//malloc can fail
			//free(newCopy);
			return NULL;	
		}else{//second malloc succeeded
			newCopy->capacity = myStringGetCapacity(copyFrom);
			newCopy->size = myStringGetSize(copyFrom);
			int i = 0;
			for (i = 0; i < myStringGetSize(copyFrom); i++){
				newCopy->data[i] = copyFrom->data[i];
			}//copy the data 
			newCopy->data[i] = '\0'; //null terminate it for fun :)
		}
	}
	//if it reaches here there haven't been errors or fail cases so just return the new object
	return newCopy;
}

//idk what this is 
void myStringSwap(MYSTRING hLeft, MYSTRING hRight){
	MyString* left = (MyString*)hLeft;
	MyString* right = (MyString*)hRight;
	
	 
	//first have to make sure each is big enough to handle the other
	if(myStringGetCapacity(right) < myStringGetCapacity(left)){//right is too small
		char* temp = right->data;
		//temp to hold the old data
		//attempt to malloc something bigger
		right->data = (char*)malloc(myStringGetCapacity(left));
		if(right->data == NULL){
			right->data = temp;
			printf("\n\n~~~ERROR Malloc Failed~~~\n\n");
			return;
		}else{//malloc succeeded
			int i = 0;
			//copy the data from temp to the new data
			for(i = 0; i < myStringGetSize(right); i++){
				right->data[i] = temp[i];
			}
			right->data[i] = '\0';//null terminate it for fun :)
			free(temp);
		}
	}else if(myStringGetCapacity(right) > myStringGetCapacity(left)){//left is smaller
		char* temp = left->data;
		//temp to hold the old data
		//attempt to malloc something bigger
		left->data = (char*)malloc(myStringGetCapacity(right));
		if(left->data == NULL){
			left->data = temp;
			printf("\n\n~~~ERROR Malloc Failed~~~\n\n");
			return;
		}else{//malloc succeeded
			int i = 0;
			//copy the data from temp to the new data
			for(i = 0; i < myStringGetSize(left); i++){
				left->data[i] = temp[i];
			}
			left->data[i] = '\0';//null terminate it for fun :)
			free(temp);
		}
	}
	//now that the capacities match

	int i;
	//temp = a
	char temp[myStringGetSize(left)];
	for(i = 0; i < myStringGetSize(left); i++){
		temp[i] = left->data[i];
	}
	int tempSize = myStringGetSize(left);
	int tempCapacity = myStringGetCapacity(left);
	//a = b
	for(i = 0; i < myStringGetSize(right); i++){
		left->data[i] = right->data[i];
	}
	left->data[i] = '\0';//null terminate it :) for funzies
	left->capacity = myStringGetCapacity(right);
	left->size = myStringGetSize(right);
	//b = temp
	for(i = 0; i < tempSize; i++){
		right->data[i] = temp[i];
	}
	right->data[i] = '\0';//null terminate for fun as always
	right->size = tempSize;
	right->capacity = tempCapacity;

}