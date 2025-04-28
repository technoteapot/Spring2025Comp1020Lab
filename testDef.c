//Author: Cullen Walsh
//
#include "status.h"
#include "myString.h"
#include <string.h>
Status testInitDefaultReturnsNonNULL(char* buffer, int length){
	MYSTRING hString = NULL;
	hString = myStringInitDefault();
	if(hString == NULL){
		strncpy(buffer, "testInitDefaultReturnsNonNULL\nmyStringInitDefault returns NULL",length);
		return FAILURE;
	}else{
		myStringDestroy(&hString);
			strncpy(buffer, "\ttestInitDefaultReturnsNonNULL\n", length);
		return SUCCESS;
	}
}

Status testGetSizeOnInitDefaultReturns0(char* buffer, int length){
	MYSTRING hString = NULL;
	Status status;

	hString = myStringInitDefault();

		if(myStringGetSize(hString) != 0){
			status = FAILURE;
			printf("Expected a size of 0 but got %d\n", myStringGetSize(hString));
			strncpy(buffer, "testGetSizeOnInitDefaultReturns0\nDid not receive 0 from getSize after init_Default\n", length);
		}else{
			status = SUCCESS;
			strncpy(buffer, "testGetSizeOnInitDefaultReturns0\n",length);
		}
	myStringDestroy(&hString);
	return status;
}

Status testInitDefaultCapacityIs7(char* buffer, int length){
	MYSTRING hString = NULL;
	Status status;
	//init the myString
	hString = myStringInitDefault();
	//now actually test the thing
	if(myStringGetCapacity(hString) != 7){
		status = FAILURE;
		printf("Expected a capacity of 7 but got %d\n", myStringGetCapacity(hString));
		strncpy(buffer, "testInitDefaultCapacityIs7\n", length);
	}else{
		status = SUCCESS;
		strncpy(buffer, "testInitDefaultCapacityIs7\n", length);
	}
	myStringDestroy(&hString);
	return status;
}

Status testInitCStringReturnsNotNULL(char* buffer, int length){
	MYSTRING testString = myStringInitCString("this is a test string.");
	//after trying to initialize it, test if it's valid
	if(testString == NULL){
		//the initCstring returned null
		printf("InitCString returned NULL\n");
		strncpy(buffer, "testInitCStringReturnsNotNULL\n", length);
		return FAILURE;
	}else{
		myStringDestroy(&testString);
		strncpy(buffer, "testInitCStringReturnsNotNULL\n", length);
		return SUCCESS;
	}
}

Status testInitCStringCorrectSize(char* buffer, int length){
	MYSTRING testString = myStringInitCString("this is a test");
	Status status;
	//test the actual thing
	if(myStringGetSize(testString) != 14){
		//not the correct size
		status = FAILURE;
		printf("Expected a size of 14, actually got: %d\n", myStringGetSize(testString));
		strncpy(buffer, "testInitCStringCorrectSize did not receive 14 from getCapacity after initCString of \"this is a test\"\n", length);
	}else{//is the correct size
		status = SUCCESS;
		strncpy(buffer, "testInitCStringCorrectSize\n", length);
	}
	//memory cleanup
	myStringDestroy(&testString);
	return status;
}

Status testInitCStringCorrectCapacity(char* buffer, int length){
	MYSTRING testString = myStringInitCString("this is a test");
	Status status;
	//test if the capacity is 15
	if(myStringGetCapacity(testString) != 15){
		status = FAILURE;
		//didn't make it the right capacity
		printf("Expected a capacity of 15, actually got %d\n", myStringGetCapacity(testString));
		strncpy(buffer, "testInitCStringCorrectCapacity did not receive 15 from getCapacity after initCString of \"this is a test\"\n", length);
	}else{
		//made the correct capacity
		status = SUCCESS;
		strncpy(buffer, "testInitCStringCorrectCapacity\n", length);
	}
	//memory cleanUp
	myStringDestroy(&testString);
	return status;
}

Status testInitCStringAssignsCorrectly(char* buffer, int length){
	MYSTRING testString = myStringInitCString("this is a test");
	char expected[15] = "this is a test";
	for (int i = 0; i < 14; i++){
		if(myStringAt(testString, i)[0] != expected[i]){
			printf("myStringInitCString FAILED expected: |%c| received: |%c|\n", expected[i], myStringAt(testString, i)[0]);
			strncpy(buffer, "testInitCStringAssignsCorrectly FAILED result differed from expected\n", length);
			myStringDestroy(&testString);
			return FAILURE;
		}
	}
	//if it gets here then it means it succeeded
	strncpy(buffer,"testInitCStringAssignsCorrectly\n", length);
	myStringDestroy(&testString);
	return SUCCESS;	
}

Status testCompareLeftShorter(char* buffer, int length){
	MYSTRING leftString = myStringInitCString("tes");
	MYSTRING rightString = myStringInitCString("test");
	Status status;
	//now for the test
	if(myStringCompare(leftString, rightString) != -1){
		status = FAILURE;
		printf("Expecte -1 with left string that is shorter than right, got: %d", myStringCompare(leftString, rightString));
		strncpy(buffer, "testCompareLeftShorter did not receive -1 from myStringCompare from left string that is shorter than right string\n", length);
	}else{
		status = SUCCESS;
		strncpy(buffer, "testCompareLeftShorter\n", length);
	}
	//memory cleanup
	myStringDestroy(&leftString);
	myStringDestroy(&rightString);
	//result
	return status;
}

Status testCompareLeftIsLess(char* buffer, int length){
	MYSTRING leftString = myStringInitCString("tesr");
	MYSTRING rightString = myStringInitCString("test");
	Status status;
	//now for the test
	if(myStringCompare(leftString, rightString) != -2){
		status = FAILURE;
		printf("Expected -2 from myStringCompare with left string being 'tesr' and right string being 'test', instead got: %d\n", myStringCompare(leftString, rightString));
		strncpy(buffer, "testCompareLeftIsLess expected -2 from myStringCompare with right string lexicographically less than the left\n", length);
	}else{
		status = SUCCESS;
		strncpy(buffer, "testCompareLeftIsLess\n", length);
	}
	//memory cleanup
	myStringDestroy(&leftString);
	myStringDestroy(&rightString);
	//result
	return status;
}

Status testCompareRightShorter(char* buffer, int length){
	MYSTRING leftString = myStringInitCString("test");
	MYSTRING rightString = myStringInitCString("tes");
	Status status;
	//now for the test
	if(myStringCompare(leftString, rightString) != 1){
		status = FAILURE;
		printf("Expected 1 from stringCompare with rightString shorter than left string, got: %d\n", myStringCompare(leftString, rightString));
		strncpy(buffer, "testCompareRightShorter expected 1 from a right string shorter than left string\n", length);
	}else{
		status = SUCCESS;
		strncpy(buffer, "testCompareRightShorter\n", length);
	}
	//memory cleanup
	myStringDestroy(&leftString);
	myStringDestroy(&rightString);
	//result
	return status;
}

Status testCompareRightIsLess(char* buffer, int length){
	MYSTRING leftString = myStringInitCString("test");
	MYSTRING rightString = myStringInitCString("tesr");
	Status status;
	//now for the test
	if(myStringCompare(leftString,rightString) != 2){
		status = FAILURE;
		printf("Expected 2 from myStringCompare with right string of 'tesr' and left string of 'test', got: %d", myStringCompare(leftString,rightString));
		strncpy(buffer, "testCompareRightIsLess did not receive 2 from myStringCompare\n", length);
	}else{
		status = SUCCESS;
		strncpy(buffer, "testCompareRightIsLess\n", length);
	}
	//memory cleanup
	myStringDestroy(&leftString);
	myStringDestroy(&rightString);
	//result
	return status;
}

Status testCompareBothSame(char* buffer, int length){
	MYSTRING leftString = myStringInitCString("test");
	MYSTRING rightString = myStringInitCString("test");
	Status status;
	//now for the test
	if(myStringCompare(leftString, rightString) != 0){
		status = FAILURE;
		printf("Expected 0, received: %d from stringCompare on two identical strings\n", myStringCompare(leftString, rightString));
		strncpy(buffer, "testCompareBothSame did not receive 0 from myStringCompare\n", length);
	}else{
		status = SUCCESS;
		strncpy(buffer, "testCompareBothSame\n", length);
	}
	//memory cleanup
	myStringDestroy(&leftString);
	myStringDestroy(&rightString);
	//result
	return status;
}

Status testDestroyAssignsPointerNULL(char* buffer, int length){
	MYSTRING testString = myStringInitDefault();
	Status status;
	//testing if the destroy works
	myStringDestroy(&testString);
	if(testString != NULL){
		status = FAILURE;
		printf("myStringDestroy did not set the pointer passed to it to NULL\n");
		strncpy(buffer, "testDestroyAssignsPointerNULL myStringDestroy did not set pointer to NULL\n", length);
	}else{
		status = SUCCESS;
		strncpy(buffer, "testDestroyAssignsPointerNULL\n",length);
	}
	return status;
}

Status testExtractionGetsWord(char* buffer, int length){
	FILE* fp = fopen("testText.txt", "w");
	if(fp == NULL){
		printf("ERROR failed to open file\n");
		strncpy(buffer, "testExtractionGetsWord failed to open file\n", length);
		return FAILURE;
	}
	fprintf(fp, "test");
	fclose(fp);
	fp = fopen("testText.txt", "r");
	if(fp == NULL){
		printf("ERROR failed to open file\n");
		strncpy(buffer, "testExtractionGetsWord failed to open file\n", length);
		return FAILURE;
	}
	MYSTRING extract = myStringInitDefault();
	if(myStringExtraction(extract, fp) == FAILURE){
		myStringDestroy(&extract);
		printf("myStringExtraction returned FAILURE\n");
		strncpy(buffer, "testExtractionGetsWord myStringExtraction returned FAILURE", length);
		fclose(fp);
		return FAILURE;
	}else{
		//might want to check it's the right string but don't necessarily need to
		strncpy(buffer,"testExtractionGetsWord\n",length);
		myStringDestroy(&extract);
		fclose(fp);
		return SUCCESS;
	}
}

Status testExtractionSkipsWhiteSpace(char* buffer, int length){
	FILE* fp = fopen("testText.txt", "w");
	if(fp == NULL){
		printf("ERROR failed to open file\n");
		strncpy(buffer, "testExtractionSkipsWhiteSpace failed to open file\n", length);
		return FAILURE;
	}
	fprintf(fp, " \t\ntest");
	fclose(fp);
	fp = fopen("testText.txt", "r");
	if(fp == NULL){
		printf("ERROR failed to open file\n");
		strncpy(buffer, "testExtractionGetsWord failed to open file\n", length);
		return FAILURE;
	}
	MYSTRING extract = myStringInitDefault();
	if(myStringExtraction(extract, fp) == FAILURE){
		//it failed to extract entirely
		myStringDestroy(&extract);
		printf("myStringExtract returned FAILURE in testExtractionSkipsWhiteSpace\n");
		strncpy(buffer, "testExtractionSkipsWhiteSpace myStringExtraction returned FAILURE\n",length);
		fclose(fp);
		return FAILURE;
	}//if it passes this it means that it worked and extraction says it extracted a string

	//now to test if it extracted 'test' correctly
	if(myStringAt(extract, 0)[0] != 't'){
		printf("myStringExtraction failed to skip whitespacem should have 't' at index 0, actually has: |%c|\n", myStringAt(extract, 0)[0]);
		strncpy(buffer, "testExtractionSkipsWhiteSpace index 0 was not 't'\n", length);
		myStringDestroy(&extract);
		fclose(fp);
		return FAILURE;
	}else{
		//if it gets to here it means everything executed smooth and [0] is 't' which is correct
		strncpy(buffer, "testExtractionSkipsWhiteSpace\n", length);
		fclose(fp);
		myStringDestroy(&extract);
		return SUCCESS;
	}
}

Status testInsertionPutsWord(char* buffer, int length){
	FILE* fp = fopen("testText.txt", "w");
	if(fp == NULL){//it can still fail to open the file
		printf("ERROR: testInsertionPutsWord failed to open file testText.txt\n");
		strncpy(buffer, "testInsertionPutsWord failed to open file\n", length);
		return FAILURE;
	}
	MYSTRING insert = myStringInitCString("test");
	//now test if insertion works
	if(myStringInsertion(insert,fp) == FAILURE){
		printf("myStringInsertion returned FAILURE\n");
		strncpy(buffer, "testInsertionPutsWord myStringInsertion returned FAILURE\n", length);
		fclose(fp);
		myStringDestroy(&insert);
		return FAILURE;
	}else{//meaning that it returned success
		strncpy(buffer, "testInsertionPutsWord\n",length);
		fclose(fp);
		myStringDestroy(&insert);
		return SUCCESS;
	}
}

Status testPushBackPutsAtBack(char* buffer, int length){
	MYSTRING testString = myStringInitCString("test");
	//initialize the string
	if(myStringPushBack(testString, 'a') == FAILURE){
		printf("myStringPushBack returned FAILURE in testPushBackPutsAtBack\n");
		strncpy(buffer, "testPushBackPutsAtBack myStringPushBack returned FAILURE", length);
		myStringDestroy(&testString);
		return FAILURE;
	}else{//else means that it did not return failure
		if(myStringAt(testString, 4)[0] != 'a'){
			printf("myStringPushBack did not place 'a' in the last index in the string, the last index is: |%c|\n", myStringAt(testString, 4)[0]);
			strncpy(buffer, "testPushBackPutsAtBack expected 'a' at the end of the string\n", length);
			myStringDestroy(&testString);
			return FAILURE;
		}else{//if it reaches this else it means everything executed smoothly and is chilling
			strncpy(buffer, "testPushBackPutsAtBack\n", length);
			myStringDestroy(&testString);
			return SUCCESS;
		}
	}
}

Status testPopBackDeletesBack(char* buffer, int length){	
	MYSTRING testString = myStringInitCString("test");
	if(myStringPopBack(testString) == FAILURE){
		printf("myStringPopBack returned FAILURE\n");
		strncpy(buffer, "testPopBackDeletesBack received FAILURE from myStringPopBack", length);
		myStringDestroy(&testString);
		return FAILURE;
	}else{
		if(myStringAt(testString, 4) != NULL){
			printf("after myStringPopBack char at index 3 is not null, it is: |%c|\n", myStringAt(testString, 4)[0]);
			strncpy(buffer, "testPopBackDeletesBack expected NULL at the end of the string\n", length);
			myStringDestroy(&testString);
			return SUCCESS;
		}else{//if it reaches here everything has worked smoothly and it passes the test
			strncpy(buffer,"testPopBackDeletesBack\n", length);
			myStringDestroy(&testString);
			return SUCCESS;	
		}
	}
return FAILURE;
}

Status testAtReturnsCorrectChar(char* buffer, int length){
	MYSTRING test = myStringInitCString("t");
	if(myStringAt(test, 0)[0] != 't'){
		printf("MyStringAt did not return the correct char, expected 't', received: |%c|", myStringAt(test, 0)[0]);
		strncpy(buffer, "testAtReturnsCorrectChar myStringAt did not return the correct char\n", length);
		myStringDestroy(&test);
		return FAILURE;
	}else{
		strncpy(buffer, "testAtReturnsCorrectChar\n", length);
		myStringDestroy(&test);
		return SUCCESS;
	}
}

Status testCStrReturnsCString(char* buffer, int length){
	MYSTRING test = myStringInitCString("test string");
	if(myStringCStr(test)[11] != '\0'){
		printf("myStringCStr failed to retrun a null termninated string, char at end is: |%c|\n", myStringAt(test, 12)[0]);
		strncpy(buffer, "testCStrReturnsCString FAILED\n", length);
		myStringDestroy(&test);
		return FAILURE;
	}else{
		strncpy(buffer, "testCStrReturnsCString\n", length);
		myStringDestroy(&test);
		return SUCCESS;
	}
}

Status testConcatWorks(char* buffer, int length){
	MYSTRING beginning = myStringInitCString("con");
	MYSTRING end = myStringInitCString("cat");
	char expected[6] = "concat";
	if(myStringConcat(beginning, end) == FAILURE){
		printf("myStringConcat returned FAILURE\n");
		strncpy(buffer, "testConcatWorks myStringConcat FAILED\n",length);
		myStringDestroy(&beginning);
		myStringDestroy(&end);
		return FAILURE;
	}else{//means concat itself returned success
		for (int i = 0; i < 6; i++){
			if(expected[i] != myStringAt(beginning,i)[0]){
				printf("concatenated string is not same as expected. expected char: |%c|, received char: |%c|\n", expected[i], myStringAt(beginning, i)[0]);
				strncpy(buffer, "testConcatWorks concat not same as expected\n", length);
				myStringDestroy(&beginning);
				myStringDestroy(&end);
				return FAILURE;
			}
		}//if it gets past the for loop, then it succeeded fine
	}
	strncpy(buffer,"testConcatWorks\n", length);
	myStringDestroy(&beginning);
	myStringDestroy(&end);
	return SUCCESS;
}

Status testEmptyReturnsTrueOnEmpty(char* buffer, int length){
	MYSTRING test = myStringInitDefault();
	if(myStringEmpty(test) != TRUE){
		//if it does NOT equal true (meaning failure)
		printf("myStringEmpty returned false on an empty string, FAILURE");
		strncpy(buffer, "testEmptyReturnsTrueOnEmpty received false on an empty string, FAILURE", length);
		myStringDestroy(&test);
		return FAILURE;
	}else{
		strncpy(buffer, "testEmptyReturnsTrueOnEmpty\n", length);
		myStringDestroy(&test);
		return SUCCESS;
	}
}

Status testEmptyReturnsFalseOnNotEmpty(char* buffer, int length){
	MYSTRING test = myStringInitCString("hello");
	if(myStringEmpty(test) == TRUE){
		//if it does equal true (meaning failure)
		printf("myStringEmpty returned true on a non empty string, FAILURE");
		strncpy(buffer, "testEmptyReturnFalseOnNonEmpty received true on a non empty string, FAILURE", length);
		myStringDestroy(&test);
		return FAILURE;
	}else{
		strncpy(buffer, "testEmptyReturnsFalseOnNotEmpty\n", length);
		myStringDestroy(&test);
		return SUCCESS;
	}
}

Status testPopBackReturnsFailureOnEmpty(char* buffer, int length){
	MYSTRING test = myStringInitDefault();
	if(myStringPopBack(test) != FAILURE){
		printf("myStringPopBack did NOT return failure on empty string\n");
		strncpy(buffer,"testPopBackReturnsFailureOnEmpty received SUCCESS on empty string\n", length);
		myStringDestroy(&test);
		return FAILURE;
	}else{
		strncpy(buffer, "testPopBackReturnsFailureOnEmpty\n", length);
		myStringDestroy(&test);
		return SUCCESS;
	}
}

Status testAtForOutOfBoundsIndex(char* buffer, int length){
	MYSTRING test = myStringInitDefault();
	if(myStringAt(test, 4) != NULL){
		printf("myStringAt returned non NULL at out of bounds index\n");
		strncpy(buffer,"testAtForOutOfBoundsIndex received not NULL from out of bounds index for myStringAt\n", length );
		myStringDestroy(&test);
		return FAILURE;
	}else{
		strncpy(buffer, "testAtForOutOfBoundsIndex\n", length);
		myStringDestroy(&test);
		return SUCCESS;
	}
}