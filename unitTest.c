//Author: Cullen Walsh

#include "unitTest.h"

int main(int argc,  char* argv[]){
	Status(*tests[])(char*, int) = {
		testInitDefaultReturnsNonNULL,
		testGetSizeOnInitDefaultReturns0,
		testInitDefaultCapacityIs7,
		testInitCStringReturnsNotNULL,
		testInitCStringCorrectSize,
		testInitCStringCorrectCapacity,
		testInitCStringAssignsCorrectly,
		testCompareLeftShorter,
		testCompareLeftIsLess,
		testCompareRightShorter,
		testCompareRightIsLess,
		testCompareBothSame,
		testDestroyAssignsPointerNULL,
		testExtractionGetsWord,
		testExtractionSkipsWhiteSpace,
		testInsertionPutsWord,
		testPushBackPutsAtBack,
		testPopBackDeletesBack,
		testAtReturnsCorrectChar,
		testCStrReturnsCString,
		testConcatWorks,
		testEmptyReturnsTrueOnEmpty,
		testEmptyReturnsFalseOnNotEmpty,
		testPopBackReturnsFailureOnEmpty,
		testAtForOutOfBoundsIndex
	};
	int numberOfFunctions = sizeof(tests) / sizeof(tests[0]);
	int i;
	char buffer[500];
	int successCount = 0;
	int failureCount = 0;
	for(i = 0; i < numberOfFunctions; i++){
		if(tests[i](buffer, 500) == FAILURE){
			printf("FAILED: Test %d failed\n", i);
			printf("\t%s\n", buffer);
			failureCount++;
		}else{
			//printf("PASS: Test %d passed\n", i);
			//printf("\t%s\n", buffer);
			successCount++;
		}
	}
	printf("Total number of tests: %d\n", numberOfFunctions);
	printf("%d/%d Pass, %d/%d Fail\n", successCount, numberOfFunctions, failureCount, numberOfFunctions);
	return 0;
}
