//@author: Cullen Walsh
//purpose: making test functions for myString
#ifndef STRING_TEST_H
#define STRING_TEST_H
#include "myString.h"
#include "status.h"
#include <stdlib.h>

//test the get capactiy function
Status testGetCapacity(int capacity);

//test the get size function
Status testGetSize(int size);

//test compare strings
Status testCompareStrings(char* left, char* right, int expected);

#endif
