#
#	Makefile
#

# 	Define some Makefile variables for the compiler and compiler flags
# 	to use Makefile variables later in the Makefile:
#
#	-g						adds debugging information to the executable file
#	-Wall					turns on most, but not all, compiler warnings
#	-x c					c code
#	-std=c89				coding in ansi c for extra challenge
#	-Wall					turns on extra warnings
#	-Wextra					turns on extra warnings
#	-Wpedantic				issue all the warnings demanded by strict ISO C and ISO C++
#							and reject forbidden extensions
#	-Wmissing-prototypes	extra warnings
#	-Wstrict-prototypes		extra warnings
#

CC = gcc
CFLAGS = -g -std=c89 -x c -Wall -Wextra -Wpedantic -Wmissing-prototypes -Wstrict-prototypes
VFLAGS = -s --leak-check=full --track-origins=yes --show-leak-kinds=all

.PHONY: all ds memcheck archive reset clean

#
# Targets
#
all: ds

ds: bin/main.o
	$(CC) $(CFLAGS) bin/*.o -o ds

bin/main.o: linkedlist
	$(CC) $(CFLAGS) -c src/main.c src -o bin/main.o

bin/linkedlist.o: src/linkedlist/linkedlist.c
	$(CC) $(CFLAGS) -c src/linkedlist/linkedlist.c -o bin/linkedlist.o


#
#	Check for memory leaks
#
memcheck1: ds
	valgrind $(VFLAGS) ./ds

#
#	clean: Remove executables, .o files and *~ backup files
#
clean:
	$(RM) bin/* ds
