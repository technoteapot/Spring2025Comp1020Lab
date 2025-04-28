//Author: Cullen Walsh

#ifndef UNITTESTH
#define UNITTESTH
#include "myString.h"

Status testInitDefaultReturnsNonNULL(char* buffer, int length);

Status testGetSizeOnInitDefaultReturns0(char* buffer, int length);

Status testInitDefaultCapacityIs7(char* buffer, int length);

Status testInitCStringReturnsNotNULL(char* buffer, int length);

Status testInitCStringCorrectSize(char* buffer, int length);

Status testInitCStringCorrectCapacity(char* buffer, int length);

Status testInitCStringAssignsCorrectly(char* buffer, int length);

Status testCompareLeftShorter(char* buffer, int length);

Status testCompareLeftIsLess(char* buffer, int length);

Status testCompareRightShorter(char* buffer, int length);

Status testCompareRightIsLess(char* buffer, int length);

Status testCompareBothSame(char* buffer, int length);

Status testDestroyAssignsPointerNULL(char* buffer, int length);

Status testExtractionGetsWord(char* buffer, int length);

Status testExtractionSkipsWhiteSpace(char* buffer, int length);

Status testInsertionPutsWord(char* buffer, int length);

Status testPushBackPutsAtBack(char* buffer, int length);

Status testPopBackDeletesBack(char* buffer, int length);

Status testAtReturnsCorrectChar(char* buffer, int length);

Status testCStrReturnsCString(char* buffer, int length);

Status testConcatWorks(char* buffer, int length);

Status testEmptyReturnsTrueOnEmpty(char* buffer, int length);

Status testEmptyReturnsFalseOnNotEmpty(char* buffer, int length);

Status testPopBackReturnsFailureOnEmpty(char* buffer, int length);

Status testAtForOutOfBoundsIndex(char* buffer, int length);

#endif

