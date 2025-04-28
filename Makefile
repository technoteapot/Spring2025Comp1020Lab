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

lab3Check1.o: lab3Check1.c
	$(CC) $(CFLAGS) -c lab3Check1.c -o lab3Check1.o

#this cleans the directory
clean:
	rm -f stringDriver $(OBJECTS)
	#second rm is added by Cullen:
	rm -f stringTest $(TESTOBJECTS)
	rm -f lab3Check1 lab3Check1.o
	rm -f lab3Check2 lab3Check2.o
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

#this'll do lab3 checks:
check1Code: myString.h myString.c lab3Check1.c status.h
	$(CC) $(CFLAGS) -c myString.c -o myString.o
	$(CC) $(CFLAGS) -c lab3Check1.c -o lab3Check1.o
	$(CC) $(CFLAGS) -o lab3Check1 myString.o lab3Check1.o
check1:
	make check1Code
	./lab3Check1
check1Valgrind:
	make check1Code
	valgrind ./lab3Check1
#check 2:
check2Code: myString.h myString.c lab3Check2.c status.h
	$(CC) $(CLFAGS) -c myString.c -o myString.o
	$(CC) $(CFLAGS) -c lab3Check2.c -o lab3Check2.o
	$(CC) $(CLFAGS) -o lab3Check2 myString.o lab3Check2.o
check2:
	make check2Code
	./lab3Check2
check2Valgrind:
	make check2Code
	valgrind ./lab3Check2
