#include <stdio.h>
#include "myString.h"

int main(int argc, char* argv[]){
	MYSTRING hMy_string = NULL;
	FILE* fp;
	hMy_string = myStringInitDefault();
	fp = fopen("simple.txt", "r");
	while(myStringExtraction(hMy_string, fp)){
		myStringInsertion(hMy_string, stdout);
		printf("\n");
		if(fgetc(fp)== ' '){
			printf("Found a space after the string\n");
		}
	}
	myStringDestroy(&hMy_string);
	fclose(fp);
	return 0;
}
