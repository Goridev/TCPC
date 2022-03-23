HEADERS = nsx_client.h ../core/nsx_cmd.h
default: nsx_client
nsx_client.o: nsx_client.c $(HEADERS)
	gcc -c nsx_client.c -o nsx_client.o
nsx_client: nsx_client.o
	gcc nsx_client.o -o ../../bin/nsx_client
clean:
	-rm -f nsx_client.o