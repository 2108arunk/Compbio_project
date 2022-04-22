SHELL = /bin/sh
CC = g++
INC_DIR = include
CFLAGS = -Wall -Wextra -pedantic -Wshadow -funroll-loops -O3 -DNDEBUG   -std=c++11 -pthread 

all: haalgo

haalgo:
	$(CC) $(CFLAGS) -o ./bin/haalgo -Iinclude/ ./src/main.cpp ./src/naive.cpp 

clean:
	rm -f ./bin/*

nuclear:
	/bin/rm -f haalgo *.o
