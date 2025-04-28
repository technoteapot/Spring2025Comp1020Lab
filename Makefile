#default variables from lab
CC = gcc
CFLAGS = -g -Wall --std=c99
OBJECTS = main.o myString.o
#my variables:
TESTOBJECTS = stringTest.o myString.o

#this compils it into "stringDriver" using $(OBJECTS)
stringDriver: $(OBJECTS)
	$(CC) $(CFLAGS) -o stringDriver $(OBJECTS)

#this compiles myString.o (I think)
myString.o: myString.h myString.c
	$(CC) $(CFLAGS) -c myString.c -o myString.o 

#this compiles main.o (I think)
main.o: main.c
	$(CC) $(CFLAGS)  -c main.c -o main.o
#this cleans the directory
clean:
	rm -f stringDriver $(OBJECTS)
	#second rm is added by Cullen when making test file:
	rm -f stringTest $(TESTOBJECTS)
	rm -f lab4 lab4Test.o

#~~~~~~~~~~~~~~~~~~~~~~~~~~~EVERYTHING PAST HERE IS BY CULLEN~~~~~~~~~~~~~~~
#this is just a function to run the thing
run: 
	./stringDriver


#a function to compile a test file for myString
test: $(TESTOBJECTS)
	$(CC) $(CFLAGS) -o stringTest $(TESTOBJECTS)

#compile stringTest
stringTest.o: stringTest.h stringTest.c status.h
	$(CC) $(CFLAGS) -c stringTest.c -o stringTest.o

lab4: lab4Test.c myString.o
	$(CC) $(CFLAGS) -c lab4Test.c -o lab4Test.o
	$(CC) $(CFLAGS) -o lab4 lab4Test.o myString.o
