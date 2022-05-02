SHELL = /bin/sh
CC = g++
INC_DIR = include
CFLAGS = -Wall -Wextra -pedantic -Wshadow -DNDEBUG -std=c++11 -pthread

all: bin_create hirschbergString naive_edit generate_string edlib_edit hirschberg

bin_create:
	mkdir -p bin

generate_string:
	$(CC) $(CFLAGS) -o ./bin/generate_string -Iinclude/ ./src/generate_string.cpp

hirschbergString:
	$(CC) $(CFLAGS) -o ./bin/hirschberg_string -Iinclude/ ./src/hirschbergString.cpp

naive_edit:
	$(CC) $(CFLAGS) -o ./bin/naive_edit -Iinclude/ ./src/basic_ed.cpp

edlib_edit:
	$(CC) $(CFLAGS) -o ./bin/edlib_edit -Iinclude/ ./src/edlib.cpp ./src/aligner.cpp 

hirschberg:
	$(CC) $(CFLAGS) -o ./bin/hirschberg -Iinclude/ ./src/hirschberg.cpp

clean:
	rm -f ./bin/*