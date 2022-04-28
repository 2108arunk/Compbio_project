SHELL = /bin/sh
CC = g++
INC_DIR = include
CFLAGS = -Wall -Wextra -pedantic -Wshadow -funroll-loops -O3 -DNDEBUG -std=c++14 -pthread 

all: bin_create hirschberg_edit naive_edit generate_string

bin_create:
	mkdir -p bin

generate_string:
	$(CC) $(CFLAGS) -o ./bin/generate_string -Iinclude/ ./src/generate_string.cpp

hirschberg_edit:
	$(CC) $(CFLAGS) -o ./bin/hirschberg_edit -Iinclude/ ./src/main_ha.cpp

naive_edit:
	$(CC) $(CFLAGS) -o ./bin/naive_edit -Iinclude/ ./src/basic_ed.cpp

clean:
	rm -f ./bin/*

nuclear:
	/bin/rm -f haalgo *.o
