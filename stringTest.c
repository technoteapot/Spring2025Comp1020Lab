/**Author: Cullen Walsh
 * date: 3/20/2025
 * purpose: this is me starting to make some test functions to test functionality of 'myString.c', this is started in the MIDDLE OF LAB 2. it also helps that I've heard we need to make a lot of test cases later on but I still need a way to make sure my stuffs works good
 * */
#include "myString.h"
#include "stringTest.h"
#include <stdio.h>
#include <stdlib.h>
//I don't rember what else I need :skull:

int main(){
//declaring some variables to assist in testing:
	char* left;
	char* right; 
	int i;

	if(testGetCapacity(8) == SUCCESS){
		printf("\ntestGetCapacity returned: SUCCESS\n");
	}else{
		printf("\ntestGetCapacity returned: FAILURE\n");
	}

	if(testGetSize(8) == SUCCESS){
		printf("\ntestGetSize returned: SUCCESS\n");
	}else{
		printf("\ntestGetSize returned: FAILURE\n");
	}
	
	printf("\ntesting all combinations for stringCompare....\n");
	//from -2 all the way to +2
	for(i = -2; i < 3; i++){
		switch(i){
			case(-2):
				left = "test";
				right = "tesv";
				printf("case where left is lexico less than right:\n");
				break;
			case(-1):
				left = "tes";
				right = "test";
				printf("case where left is smaller than right:\n");
				break;
			case(0):
				left = "test";
				right = "test";
				printf("case where both are equal to each other\n");
				break;
			case(1):
				left = "test";
				right = "tes";
				printf("case where right is shorter than left:\n");
				break;
			case(2):
				left = "tesv";
				right = "test";
				printf("case where right is lexi smaller than left:\n");
				break;
			default:
				printf("I made the end case of the for loop wrong :skul:");
				break;
		}
		if(testCompareStrings(left, right, i) == SUCCESS){
			printf("The result of testCompareStrings for %s , %s and %d is SUCCESS\n", left, right, i);
		}else{
			printf("The result of testCompareStrings for %s , %s and %d is FAILURE\n", left, right, i);}

	}
	printf("\n\n compare strings tests completed\n\n");
	return 0;
}

/**
 * returns SUCCESS if the correct capacity is returned properly
 * returns FAILURE if not
 **/
Status testGetCapacity(int capacity){
	char testString[capacity-1];
	int i = 0;
	//fill the test string
	for(i = 0; i < capacity-1; i++){
		testString[i] = 'h';
	}
	testString[i] = '\0';//terminate the end of the string
	MYSTRING testMyString = myStringInitCString(&(testString[0]));//make the my string full of placeholder with a null terminated dummy string
	if(capacity == myStringGetCapacity(testMyString)){
		free(testMyString);//still have to free the memory
		return SUCCESS;
	}else{
		free(testMyString);//still have to free the memory
		return FAILURE;
	}
}

/**
 * returns SUCCESS if the correct size is returned properly
 * returns FAILURE if not
 **/
Status testGetSize(int size){
	//creates a placeholder myString object for testing
	char testString[size+1];
	int i = 0;
	//fill the test string with stuff
	for(i = 0; i < size; i++){
		testString[i] = 'h';
	}
	testString[i] = '\0';//null terminate the string
	MYSTRING testMyString = myStringInitCString(&(testString[0]));//create a dummy mystring object to test on
	if(size == myStringGetSize(testMyString)){
		free(testMyString);//still have to free the thing
		return SUCCESS;
	}else{
		free(testMyString);//still have to free the memory
		return FAILURE;
	}
}

/**
 * makes two myString objects each with the passed in strings, then compares them, and checks if the result from compare is the same as expected, if it is the same as expected returns SUCCESS if not returns FAILURE
 **/
Status testCompareStrings(char* left, char* right, int expected){
	//make the two MyString objects
	MYSTRING leftString = myStringInitCString(left);
	MYSTRING rightString = myStringInitCString(right);
	//now just test if the compare function works
	if(expected == myStringCompare(leftString, rightString)){
		free(leftString);
		free(rightString);
		return SUCCESS;
	}else{
		free(leftString);
		free(rightString);
		return FAILURE;
	}
}
