#include <stdio.h>
#include <stdlib.h>
#include "myString.h"
#include "genericVector.h"
int main(int argc, char* argv[]){
	Boolean gameContinue = TRUE;
	//the core gameplay loop
	while (gameContinue) {
		/*~~~set up the first parts for gameplay~~~*/
		//prompt the user for a word length, re prompting as necessary until she enters a number such that there's at least one word that's exactly that long
		int wordLength = 0;
		printf("\nHow many letters long is the word you would like to guess going to be?\n");
		fscanf(stdin, "\n\t %d", &wordLength);
		while( wordLength < 2 || wordLength == 23 || wordLength == 25 || wordLength == 26 || wordLength == 27 || wordLength > 29) {
			printf("\nThe are no words with exactly that many letters please enter a different number\n");
			fflush(stdin);
			fscanf(stdin, "\n\t %d", &wordLength);
		}
		//setupt all the possible words
		GENERICVECTOR allPossibleWords = genericVectorInitDefault(myStringInitCopy, myStringDestroy);
		FILE* dict = fopen("dictionary.txt", "r");
		if(dict == NULL){
			perror("\n\n\t\t~~FAILED TO OPEN DICTIONARY~~~\n\n");
			exit(-1);
		}
		MYSTRING cursor = myStringInitDefault();
		while(myStringExtraction(cursor, dict)){
			if(myStringGetSize(cursor) == wordLength){
				genericVectorPushBack(allPossibleWords, cursor);
			}
		}
		myStringDestroy(&cursor);
		fclose(dict);
		//now to set the number of guesses the user will get
		int guesses = 0;
		printf("\nHow many guesses would you like to guess the word?\n");
		fflush(stdin);
		fscanf(stdin, "\t\n %d", &guesses);
		while(guesses < 1) {
			printf("\nPlease enter a positive number for your number of guesses\n");
			fflush(stdin);
			fscanf(stdin, "\t\n %d", &guesses);
		}
		//ask the user if they would like to see the remaining word families and their numbers
		Boolean showWordFamilies = FALSE;
		char input = 'm';
		printf("\nWould you like to see the remaining word families?(y/n)\n");
		fflush(stdin);
		fscanf(stdin, "\n\t %c", &input);
		while(input != 'y' && input != 'n') {
			printf("\nInvalid input, please enter (y)es or (n)o");
			fflush(stdin);
			fscanf(stdin, "\n\t %c", &input);
		}
		if(input == 'y') {
			showWordFamilies = TRUE;
		}else if(input == 'n') {
			showWordFamilies = FALSE;
		}
		//the word length has been chosen
		//grab the vector containing all qualifying words, when based on length it's just the word length -1 and that's the index in vectors[]
		//GENERICVECTOR allPossibleWords = genericVectorInitCopy(vectors[wordLength - 1]);
		//cleanup the setup variables
		//for(int i = 0; i < 30; i++){
		//	genericVectorDestroy(&vectors[i]);
		//}
		//myStringDestroy(&cursor);

		//make blankCode MyString to check against
		char blankCode[wordLength+1];
		//populate it with _
		int j;
		for(j = 0; j < wordLength; j++) {
			blankCode[j] = '_';
		}
		blankCode[j] = '\0';
		MYSTRING previousFamilyCodeString = myStringInitCString(blankCode);
		//string to hold the guessed letters
		MYSTRING guessedLetters = myStringInitDefault();
		//list of correct guesses. whenever there is a correct letter guessed, it is added to correct guesses
		MYSTRING correctGuesses = myStringInitDefault();
		//for if the player won
		Boolean playerWin = FALSE;
		//the guessing game loop time
		while(guesses > 0) {
			//hold all the word families
			GENERICVECTOR wordFamilies = genericVectorInitDefault(genericVectorInitCopy, genericVectorDestroy);
			/*~~~~~~~~~tell the player relevant information, like what they're currently at, number of guesses etc*/
			printf("\nYou have %d guesses remaining", guesses);
			printf("\nYour already guessed letters are: {%s}", myStringCStr(guessedLetters));
			printf("\nYour current guess progress: %s", myStringCStr(previousFamilyCodeString));
			Boolean validGuess = TRUE;
			//get the guess from the user that is not already guessed
			char guess;
			do{
				if(validGuess){
					printf("\nWhat letter do you guess?\n");
					fflush(stdin);
					fscanf(stdin, " \n\t%c", &guess);
					//check if it guess is already in guessed letters
					for(int i = 0; myStringAt(guessedLetters, i) != NULL; i++) {
						if(myStringAt(guessedLetters, i)[0] == guess) {
							//if guess is in guessed letters
							validGuess = FALSE;
							break;
						}
					}
				}else {
					//set valid guess to true, so if it goes through the for loop without getting set to false, it can exit the do While()
					validGuess = TRUE;
					printf("\nYou've already guessed that letter, please guess a letter you haven't guessed yet\n");
					fflush(stdin);
					fscanf(stdin, " \n\t%c", &guess);
					//check if the guess is already in guessed letters
					for(int i = 0; myStringAt(guessedLetters, i) != NULL; i++) {
						if(myStringAt(guessedLetters, i)[0] == guess) {
							//if guess is in guessed letters
							validGuess = FALSE;
							break;
						}
					}
				}
			}while(!validGuess);
			//now that we have a guess we can check the stuffs
			//go through all the words in possible words
			for(int i = 0; genericVectorAt(allPossibleWords, i) != NULL; i++) {
				//the word family code that is being built for current word
				MYSTRING currentFamily = myStringInitDefault();
				//genericVectorAt(i) returns a nonNULL pointer to a MYSTRING object
				MYSTRING currentWord = genericVectorAt(allPossibleWords, i)[0];//pointer to the current word
				//check if any guessed letters are in the word
				Boolean inWord = FALSE;
				for(int k = 0; myStringAt(currentWord, k) != NULL; k++) {
					inWord = FALSE;
					//~~~~~~~~~~~~make the code
					if(myStringAt(currentWord, k)[0] == guess) {
						inWord = TRUE;
						//put this letter into the current family code
						myStringPushBack(currentFamily, guess);
					}else {
						//check if the letter we're currently looking at is already a correct guess
						for(int h = 0; myStringAt(correctGuesses, h) != NULL; h++) {
							//if it is in correct guesses, add it into the code
							if(myStringAt(correctGuesses, h)[0] == myStringAt(currentWord, k)[0]) {
								myStringPushBack(currentFamily, myStringAt(correctGuesses, h)[0]);
								//now it is in the code
								inWord = TRUE;
							}
						}
						if(!inWord) {
							//if in word is still false by now then put '_' in this place for the code
							myStringPushBack(currentFamily, '_');
						}
					}
				}//this for loop builds a family code
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~PUT INTO THE FAMILIES VECTOR
				Boolean notThereYet = TRUE;
				//check if the family code is already in family codes, if so, add current word to the vector with that code
				for(int c = 0; genericVectorAt(wordFamilies, c) != NULL; c++) {
					//go into this word family vector, and check if the first my String in that vector is the same as currentFamily, if so put current word into that vector and set notThereYet to FALSE
					if(myStringCompare(genericVectorAt(genericVectorAt(wordFamilies, c)[0], 0)[0], currentFamily) == 0) {
						//myStringCompare = 0 means that current family matches a family already there, so add current word to that family
						notThereYet = FALSE;
						genericVectorPushBack(genericVectorAt(wordFamilies, c)[0], currentWord);
						break;
					}
				}//looked through all the word families to find a match, if none have been found make a new family
				if(notThereYet) {
					//make a new family vector
					GENERICVECTOR newFamily = genericVectorInitDefault(myStringInitCopy, myStringDestroy);
					//put the code in the first place
					genericVectorPushBack(newFamily, currentFamily);
					//put the current word in there too
					genericVectorPushBack(newFamily, currentWord);
					//then finally put the new family into the wordFamilies vector
					genericVectorPushBack(wordFamilies, newFamily);
					//then destroy new family bc it made a copy and put it in
					genericVectorDestroy(&newFamily);
				}
				myStringDestroy(&currentFamily);
			}//after ALLLLL that, possibleWords has been searched through, now it is time to pick the word family with the most words in it
			int indexOfMost = 0;
			int max = 0;
			for(int i = 0; genericVectorAt(wordFamilies, i) != NULL; i++) {
				if(genericVectorGetSize(genericVectorAt(wordFamilies, i)[0]) > max) {
					indexOfMost = i;
					max = genericVectorGetSize(genericVectorAt(wordFamilies, i)[0]);
				}
			}
			myStringPushBack(guessedLetters, guess);
			//check if the biggest word family is the same as the previous biggest word family, if so decrement guesses
			if(myStringCompare(previousFamilyCodeString, genericVectorAt(genericVectorAt(wordFamilies, indexOfMost)[0] , 0)[0]) == 0) {
				//if true it means that previousFamilyCodeString is the same as the biggest family now
				guesses--;
				printf("\nUh Oh! That letter is not in the word\n");
			}else{//guess found a letter
				printf("\nAwesome you found a letter!\n");
				myStringPushBack(correctGuesses, guess);
					playerWin = TRUE;
					//thoroughly check
					for(int i = 0; myStringAt(genericVectorAt(genericVectorAt(wordFamilies, indexOfMost)[0], 0)[0], i) !=NULL; i++) {
						if (myStringAt(genericVectorAt(genericVectorAt(wordFamilies, indexOfMost)[0], 0)[0], i)[0] == '_') {
							playerWin = FALSE;
						}
					}
					if(playerWin) {
						//this could cause seg faults
						printf("CONGRATS you figured out the word!, the word was: {%s}", myStringCStr(genericVectorAt(genericVectorAt(wordFamilies, indexOfMost)[0], 0)[0]));
						//player won the game
						playerWin = TRUE;
						break;
					}

			}
			//show the word families or not
			if(showWordFamilies) {
				for(int i = 0; genericVectorAt(wordFamilies, i) != NULL; i++) {
					printf("\nWord Family: {%s} number of words: %d", myStringCStr(genericVectorAt(genericVectorAt(wordFamilies, i)[0], 0)[0]), genericVectorGetSize(genericVectorAt(wordFamilies, i)[0])-1);
				}
			}
			//now fix the scope of allPossibleWords
			genericVectorDestroy(&allPossibleWords);
			allPossibleWords = genericVectorInitDefault(myStringInitCopy, myStringDestroy);
			for(int i = 1; genericVectorAt(genericVectorAt(wordFamilies,indexOfMost)[0], i) != NULL; i++) {
				genericVectorPushBack(allPossibleWords, genericVectorAt(genericVectorAt(wordFamilies,indexOfMost)[0], i)[0]);
			}
			//now all possible words holds the fixed scope of words
			//fix the value for previous familyCodeString
			myStringAssignment(previousFamilyCodeString, genericVectorAt(genericVectorAt(wordFamilies,indexOfMost)[0], 0)[0]);
			genericVectorDestroy(&wordFamilies);
		}
		if(playerWin){}
		else {
			printf("\n\t\tHAHA you lost and ran out of guesses, the word was: %s", myStringCStr(genericVectorAt(allPossibleWords, 0)[0]));
		}
		//~~~~~~~~~~~~~memory cleanupStep
		myStringDestroy(&guessedLetters);
		//genericVectorDestroy(&wordFamilies);
		genericVectorDestroy(&allPossibleWords);
		myStringDestroy(&correctGuesses);
		myStringDestroy(&previousFamilyCodeString);
		printf("\n\n\t\t~~~GAME OVER~~~\n\n");
		printf("\n\nwould you like to play again?(y/n)");
		fflush(stdin);
		fscanf(stdin, " \n\t%c", &input);
		while(input != 'y' && input != 'n') {
			printf("\ninvalid input, please answer (y)es or (n)o");
			fflush(stdin);
			fscanf(stdin, "\n \t%c", &input);
		}
		if(input == 'y') {
			gameContinue = TRUE;
		}else if(input == 'n') {
			gameContinue = FALSE;
		}
	}
	return 0;
}