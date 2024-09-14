# Makefile for CS210 PA3
CC = g++
CFLAGS = -g -std=c++11
EXECUTABLES = RedBlackTree
HEADERS = RedBlackTree.h

all: $(EXECUTABLES)

RedBlackTree: RedBlackTree.h RedBlackTree.o TestDriver.o
	$(CC) $(CFLAGS) -o RedBlackTree RedBlackTree.o TestDriver.o

TestDriver.o: TestDriver.cpp
	$(CC) $(CFLAGS) -c TestDriver.cpp

RedBlackTree.o: RedBlackTree.cpp
	$(CC) $(CFLAGS) -c RedBlackTree.cpp

clean:
	rm -f *.o $(EXECUTABLES)
