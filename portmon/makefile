CC=g++
CFLAGS=-c -Wall

all: portmon

portmon: portmon.o rawpacket.o
	$(CC) portmon.o rawpacket.o -o portmon

portmon.o: portmon.cpp 
	$(CC) $(CFLAGS) portmon.cpp

rawpacket.o: rawpacket.cpp 
	$(CC) $(CFLAGS) rawpacket.cpp
