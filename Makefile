# Makefile

CC = gcc
CFLAGS = -Wall -Werror -g -O2
LIBS = -lm

all: demoTfs

demoTfs: demoTfs.o libTinyFS.o libDisk.o singlyLinkedList.o
	$(CC) $(CFLAGS) -o $@ demoTfs.o libTinyFS.o libDisk.o singlyLinkedList.o $(LIBS)

demoTfs.o: demoTfs.c libTinyFS.o
	$(CC) $(CFLAGS) -c -o $@ $<

libTinyFS.o: libTinyFS.c libTinyFS.h libDisk.o singlyLinkedList.o
	$(CC) $(CFLAGS) -c -o $@ $<

libDisk.o: libDisk.c libDisk.h
	$(CC) $(CFLAGS) -c -o $@ $<

singlyLinkedList.o: singlyLinkedList.c singlyLinkedList.h libTinyFS.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o demoTfs

