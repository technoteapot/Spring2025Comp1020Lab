//@Author Cullen Walsh
//this is just testing for the functions present in lab 4
//I hear that lab  is the implementation of a full testing library so I'll make test functions when I do that one

#include "status.h"
#include "myString.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
	//the functions I need to test are:
	//myStringPushBack
	//myStringPopBack
	//myStringAt
	//myStringCStr
	//myStringConcat
	//myStringEmpty
	MYSTRING testString1 = myStringInitDefault();
	if(myStringEmpty(testString1) == FALSE){
		printf("\nmyStringEmpty(testString1) returned FALSE on a string of size 0 indicating a FAILURE\n");
	}else{
		printf("\nmyStringEmpty(testString1) returned TRUE on a string of size 0  indicating a SUCCESS\n");
	}

	if(myStringPushBack(testString1, 'a') == FAILURE){
		printf("\nmyStringPushBack(testString1, 'a') returned FAILURE ~~~DIDN'T WORK PROPERLY\n");
	}else{
		printf("\nmyStringPushBack(testString1, 'a') returned SUCESS\n");
		if(myStringAt(testString1,0)[0] == 'a'){
			printf("\nmyStringPushBack(testString1, 'a') worked PROPERLY and put the 'a' at the end of the string\n");
		}else{
			printf("\nmyStringPushBack(testString1, 'a') did NOT work properly and the char at the end of testString1 is: %c\n", myStringAt(testString1, 0)[0]);
		}
	}
	if(myStringPopBack(testString1) == FAILURE){
		printf("\nmyStringPopBack(testString1) retrurned FAILURE, meaning it did not delete the last element of the string\n");
	}else{
		printf("\nmyStringPopBack(testString1) returned SUCCESS, meaning it deleted the last element of the string\n");
		if(myStringAt(testString1, 0) == NULL){
			printf("\nmyStringPopBack(testString1) correctly deleted the last element of the string and made the size 0\n");
		}else{
			printf("\nmyStringPopBack(testString1) did not replace the last element of the string with NULL and DID NOT work properly, the current char there is: %c\n", myStringAt(testString1, 0)[0]);
		}
	}
	myStringDestroy(&testString1);//   0123456789
	testString1 = myStringInitCString("this is a test string");
	printf("\ntestString1 reinitialized to \"this is a test string\"\n");
	char temp = (myStringAt(testString1, 10)[0]);
	printf("\nmyStringAt(testString1, 10) should return 't' and actually returns: %c\n", myStringAt(testString1, 10)[0]);
	if(temp == 't'){
		printf("\nmyStrinyAt(testString1, 10) successfully returned 't'\n");
	}else{
		printf("\nmyStringAt(testString1, 10) FAILED and did not return 't'\n");
	}
	printf("\nmyStringCStr(testString1) returned: \"%s\" and should have returned what the testString1 was set to above\n", myStringCStr(testString1));
       MYSTRING testString2 = myStringInitCString(" for testing");
       printf("\ntestString2 initialized to \" for testing\"\n");
       if(myStringConcat(testString1, testString2) == FAILURE){
	       printf("\nmyStringConcat(testString1, testString2) returned FAILURE\n");
       }else{
	       printf("\nmyStringConcat(testString1, testString2) returned SUCCESS and testString1 is now: \"%s\"\n", myStringCStr(testString1));
       }
       myStringDestroy(&testString1);
       myStringDestroy(&testString2);
       return 0;
}
