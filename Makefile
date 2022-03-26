#
# This is an example Makefile for a countwords program.  This
# program uses both the scanner module and a counter module.
# Typing 'make' or 'make count' will create the executable file.
#

# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
# for C++ define  CC = g++
CC = gcc
CFLAGS  = -g -Wall

# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
all: server client multi

# To create the executable file count we need the object files
# countwords.o, counter.o, and scanner.o:
#
server: nsx_server.o
	$(CC) $(CFLAGS) -o bin/server nsx_server.o
nsx_server.o: src/server/nsx_server.c src/server/nsx_server.h src/core/nsx_cmd.h src/core/nsx_conf.h
	$(CC) $(CFLAGS) -c src/server/nsx_server.c

client: nsx_client.o
	$(CC) $(CFLAGS) -o bin/client nsx_client.o
nsx_client.o:  src/client/nsx_client.c src/client/nsx_client.h src/core/nsx_cmd.h src/core/nsx_conf.h
	$(CC) $(CFLAGS) -c src/client/nsx_client.c

multi: nsx_server_multi.o
	$(CC) $(CFLAGS) -o bin/multi nsx_server_multi.o
nsx_server_multi.o:  src/server/nsx_server_multi.c src/server/nsx_server.h src/core/nsx_cmd.h src/core/nsx_conf.h
	$(CC) $(CFLAGS) -c src/server/nsx_server_multi.c

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) count *.o *~