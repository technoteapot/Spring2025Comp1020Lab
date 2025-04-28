//Author: Cullen Walsh
//Date: 2/7/2025
//

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
