HEADERS = nsx_server.h ../core/nsx_cmd.h
default: nsx_server
nsx_server.o: nsx_server.c $(HEADERS)
	gcc -c nsx_server.c -o nsx_server.o
nsx_server: nsx_server.o
	gcc nsx_server.o -o ../../bin/nsx_server
clean:
	-rm -f nsx_server.o