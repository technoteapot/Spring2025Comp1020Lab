//Author: Cullen Walsh
//Date: 2/7/2025
//

#include "status.h"
#include <stdio.h>
//typedef void* to MYSTRING, this enables us to use the opaque object methodology
typedef void* MYSTRING;

//precondition: none
//postcondition: Allocate space for a string object that represents the empty string. the string will have a capacity of y and size 0  by default. A copy of the address of the opaque object will be returned on success and NUll on failure
MYSTRING myStringInitDefault(void);

//PreCondition: phMYSTRING holds the address of a valid handle to a MYSTRING object
//PostCondition: The memory used for the MYSTRING objet has been reclaimed by the system and the handle referred to by the pointer phMyString has been set to NULL
void myStringDestroy(MYSTRING* phMyString);

//precondition: C_string is a valid null terminated C-string
//postcondition: allocate space for a string object that represents a string with the same value as the given c-string. The capacity of the string object will be set to one greater than is required to hold the string. As an example, the string "the" would set capacity to 4 instead of 3. A copy of the address of the opaque object will be returned on success and NULL on failure.
MYSTRING myStringInitCString(const char* CString);

//precondition: hMY_string is the handle of a valid My_string object
//Postcondition: returns a copy of the integer value of the object's capacity
int myStringGetCapacity(MYSTRING hMyString);

//precondition: hMyString is the handle of a valid MYSTRING object
//postcondition: Returns a copy of the integer value of the object's size
int myStringGetSize(MYSTRING hMyString);

//Precondition: hLeftString and hRightString are valid MYSTRING objects.
//PostCondition: returns an integer less than zero if the string represented by hLeftString is lexicographically smaller than hRightString. if one string is a prefix of the other string then the shorter string is considered to be the smaller one. (app is less than apple. Returns 0 if the strings are the same and returns a number greater than zero if the string representd by hLeftString is bigger than hRightString.
int myStringCompare(MYSTRING hLeftString, MYSTRING hRightString);

//Precondition: hMyString is the handle to a valid myString object
//Postcondition: hMyString will be the handle of a string object that contains the next string from the file stream fp according to the following rules:
//	1) leading whitespace will be ignored
//	2)All characters (after the first non-whitespace character is obtained and included) will be aded to the string until a stopping condition is met. The capacity of the string will continue to grow as needed until all characters are stored.
//	3) A stopping condition is met if we read a whitespace character after we have read at least one non-whitespace character or if we reach the end of the file
//function will return SUCCESS if a non-empty string is read successfully. and FAILURE otherwise. Remember that the incoming string may already contain some data and this function should replace the data but not necessarily resize the array unless needed.
Status myStringExtraction(MYSTRING hMyString, FILE* fp);

//Precondition: hMyString is the handle to a valid myString object.
//Postcondition: Writes the characters contained in the string object indicated by the handle hMyString to the file stream fp.
//function will return SUCCESS id it successfully writes the string and FAILURE otherwise.
Status myStringInsertion(MYSTRING hMyString, FILE* fp);

//Precondition: hMyString is the handle to a valid myString object
//Postcondition: if successful, places the character item at the end of the string and returns SUCCESS. if the string does not have enough room and cannot resize to accomodate the new character then the operation fails and FAILURE is returned. The resize operation will attempt to amortize the cost of a resize by making the string capacity somewhat larger than it was before (up to 2 times bigger).
Status myStringPushBack(MYSTRING hMyString, char item);

//Precondition: hMyString is the handle to a valid myString object
//Postcondition: removes the last character of a string in constant time. Guaranteed to not cause a resize operation of the internal data. returns SUCCESS on success and FAILURE if the string is empty.
Status myStringPopBack(MYSTRING hMyString);

//Precondition: hMyString is the handle to a valid myString object.
//Postcondition: returns the address of the character located at the given index if the index is in bounds but otherwise returns NULL. this address is not usable as a c-string since the data is not NULL ternminated and is intended to just provide access to the element at that index
char* myStringAt(MYSTRING hMyString, int index);

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: Returns the address of the first element of the string object
// for use as a c-string. The resulting c-string is guaranteed to be NULL
// terminated and the memory is still maintained by the string object though
// the NULL is not actually counted as part of the string (in size).
char* myStringCStr(MYSTRING hMyString);

//Precondition: hResult and hAppend are handles to valid My_string objects.
//Postcondition: hResult is the handle of a string that contains the original
// hResult object followed by the hAppend object concatenated together. This
// function should guarantee no change to the hAppend object and return
// SUCCESS if they operation is successful and FAILURE if the hResult object
// is unable to accomodate the characters in the hAppend string perhaps
// because of a failed resize operation. On FAILURE, no change to either
// string should be made.
Status myStringConcat(MYSTRING hResult, MYSTRING hAppend);

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: Returns an enumerated type with value TRUE if the string
// is empty and FALSE otherwise.
Boolean myStringEmpty(MYSTRING hMyString);

//precondition: hleft and hRight contain handles of valid myString objects
//postCondition: On Success hLeft will contain the handle to a valid MYSTRING object 
//that is a deep copy of the object indicated by hRight. the object indicated by the 
//handle at the address pLeft will attempt to resize to hold the data in Right. 
//if the object on the left already has enough space it will not attempt to resize. 
//hLeft will have the same size as hRight if the call succeeds but the capacities 
//may be different. the data in the dynamic arrays upto size number of elements will 
//be identical in both objects. on failure pLeft will be unchanged and a status of 
//FAILURE will be returned.
Status myStringAssignment(MYSTRING hLeft, MYSTRING hRight);

//precondition: hMyString is the handle to a valid MYSTRING object.
//postcondition: will return the handle to a valid MYSTRING object that is a deep copy
// of the object ndicated by hMyString. This means the copied object will be a 
//complete and independant copy and not share any data with the object we are 
//copying from. On failure the function will return NULL
MYSTRING myStringInitCopy(MYSTRING hMyString);

//precondition: hLeft and hRight are handles to valid MYSTRING objects.
//postcondition: after the function hLEft will contain the size capacity and data of
// the object indicated byhRight and hRight will contain the size capacity and data 
//of the object indicated by hLeft. This function will be much faster than making
// deep copies of the objects using myStringAssignment and attempting to swap them 
//in the traditional way calling myStringAssignment in place of the '=' below
//temp = a;
//a = b;
//b = temp;
void myStringSwap(MYSTRING hLeft, MYSTRING hRight);


