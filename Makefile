SHELL = /bin/sh
CC = g++
INC_DIR = include
CFLAGS = -Wall -Wextra -pedantic -Wshadow -funroll-loops -O3 -DNDEBUG -std=c++14 -pthread 

all: bin_create hirschberg_edit naive_edit generate_string edlib_edit align_edit archit

bin_create:
	mkdir -p bin

generate_string:
	$(CC) $(CFLAGS) -o ./bin/generate_string -Iinclude/ ./src/generate_string.cpp

hirschberg_edit:
	$(CC) $(CFLAGS) -o ./bin/hirschberg_edit -Iinclude/ ./src/main_ha.cpp

naive_edit:
	$(CC) $(CFLAGS) -o ./bin/naive_edit -Iinclude/ ./src/basic_ed.cpp

edlib_edit:
	$(CC) $(CFLAGS) -o ./bin/edlib_edit -Iinclude/ ./src/edlib.cpp ./src/edlibmain.cpp

align_edit:
	$(CC) $(CFLAGS) -o ./bin/align_edit -Iinclude/ ./src/edlib.cpp ./src/aligner.cpp 

archit:
	$(CC) $(CFLAGS) -o ./bin/archit -Iinclude/ ./src/hirshberg_as.cpp


clean:
	rm -f ./bin/*