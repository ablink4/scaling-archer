CC=g++
CFLAGS=-c -Wall

all: portmon

portmon: portmon.o 
	$(CC) portmon.o -o portmon

portmon.o: portmon.cpp 
	$(CC) $(CFLAGS) portmon.cpp

