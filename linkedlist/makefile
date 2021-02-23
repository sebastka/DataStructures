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
all: ll

ll: linkedlist/bin/main.o
	$(CC) $(CFLAGS) linkedlist/bin/Node.o linkedlist/bin/Linkedlist.o linkedlist/bin/main.o -o ds

linkedlist/bin/main.o: linkedlist/bin/Linkedlist.o
	$(CC) $(CFLAGS) -c linkedlist/src/main.c -o linkedlist/bin/main.o

linkedlist/bin/Linkedlist.o: linkedlist/bin/Node.o
	$(CC) $(CFLAGS) -c linkedlist/src/Linkedlist.c -o linkedlist/bin/Linkedlist.o

linkedlist/bin/Node.o:
	mkdir -p linkedlist/bin/
	$(CC) $(CFLAGS) -c linkedlist/src/Node.c -o linkedlist/bin/Node.o

#
#	Check for memory leaks
#
memcheck: ll
	valgrind $(VFLAGS) ./ll

#
#	clean: Remove executables, .o files and *~ backup files
#
clean:
	$(RM) */bin/* ll vgcore.*
