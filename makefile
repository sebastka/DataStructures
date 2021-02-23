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
CFLAGS = -std=c89 -Wall -Wextra -Wpedantic -Wmissing-prototypes -Wstrict-prototypes # -g
VFLAGS = -s --leak-check=full --track-origins=yes --show-leak-kinds=all

.PHONY: all memcheck clean

#
# Targets
#
all: ds

ds: bin/main.o
	$(CC) $(CFLAGS) bin/Node.o bin/Linkedlist.o bin/test_linkedlist.o bin/main.o -o ds

bin/main.o: bin/test_linkedlist.o
	$(CC) $(CFLAGS) -c src/main.c -o bin/main.o

bin/test_linkedlist.o: bin/Linkedlist.o
	$(CC) $(CFLAGS) -c src/test_linkedlist.c -o bin/test_linkedlist.o

bin/Linkedlist.o: bin/Node.o
	$(CC) $(CFLAGS) -c src/Linkedlist.c -o bin/Linkedlist.o

bin/Node.o:
	mkdir -p bin/
	$(CC) $(CFLAGS) -c src/Node.c -o bin/Node.o

#
#	Check for memory leaks
#
memcheck: ds
	valgrind $(VFLAGS) ./ds

#
#	clean: Remove executables, .o files and *~ backup files
#
clean:
	$(RM) bin/* ds vgcore.*
