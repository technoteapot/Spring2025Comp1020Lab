#include <stdio.h>
#include "myString.h"

int main(int argc, char* argv[]){
	MYSTRING hMyString = NULL;
	FILE* fp;
	hMyString = myStringInitDefault();
	fp = fopen("dictionary.txt", "r");
	while(myStringExtraction(hMyString, fp)){
		if(myStringGetSize(hMyString) == 5){
			myStringInsertion(hMyString, stdout);
			printf(", ");
		}
	}
	myStringDestroy(&hMyString);
	fclose(fp);

	printf("\n\n~~~~~~~~~~~~now for the 29 letter words thing~~~~~~~~~~~~~~~~\n\n");
	fp = fopen("dictionary.txt", "r");
	hMyString = myStringInitDefault();
	while(myStringExtraction(hMyString, fp)){
		if(myStringGetSize(hMyString) == 29){
			myStringInsertion(hMyString, stdout);
			printf(", ");
		}
	}


	return 0;
}
