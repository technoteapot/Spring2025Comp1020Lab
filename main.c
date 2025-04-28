#include <stdio.h>
#include "myString.h"

int main(int argc, char* argv[]){
	//make an array of 100 myStrings
	MYSTRING strings[100];
	//initialize them all to NULL
	for(int i = 0; i < 100; i++){
		strings[i] = NULL;
	}
	//initialize the first element to "COPY ME!"
	strings[0] = myStringInitCString("COPY ME!");
	//write a for loop that uses you init copy function ot copy the first string into every other element of the array
	for(int i = 1; i < 100; i++){
		strings[i] = myStringInitCopy(strings[0]);
	}
	//Destroy the object in index 0
	myStringDestroy(&strings[0]);
	 //use initCstring to initialize the first element of the array to the string "FIRST FIFTY!"
	strings[0] = myStringInitCString("FIRST FIFTY!");
	//call your myStringAssignment function to copy the value of the first array element 
	//into the first fifty elements of the array
	for(int i = 1; i < 50; i++){
		if(myStringAssignment(strings[i], strings[0]) == FAILURE){
			printf("\n\n~~~MY STRING ASSIGNMENT FAILED~~~\n\n");
			return 1;
		}
	}
	//finally call your myStringSwap function to swap the values of the first 50 elements of the array with the last 50 elements
	for(int i = 0; i < 50; i++){
		myStringSwap(strings[i], strings[99-i]);
	}

	//then to finish make a loop that destroys all the myString objects
	for(int i = 0; i < 100; i++){
		myStringInsertion(strings[i], stdout);
		myStringDestroy(&strings[i]);
	}
	return 0;
}
