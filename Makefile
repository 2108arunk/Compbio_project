SHELL = /bin/sh
CC = g++
INC_DIR = include
CFLAGS = -Wall -Wextra -pedantic -Wshadow -funroll-loops -O3 -DNDEBUG -std=c++14 -pthread 

all: hirschberg_edit naive_edit hirsch_archit

hirschberg_edit:
	$(CC) $(CFLAGS) -o ./bin/hirschberg_edit -Iinclude/ ./src/main_ha.cpp

naive_edit:
	$(CC) $(CFLAGS) -o ./bin/naive_edit -Iinclude/ ./src/basic_ed.cpp

hirsch_archit:
	$(CC) $(CFLAGS) -o ./bin/hirsch_archit -Iinclude/ ./src/hirshberg_as.cpp

clean:
	rm -f ./bin/*

nuclear:
	/bin/rm -f haalgo *.o
