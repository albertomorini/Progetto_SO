all : server

server : server.o gioco.o
	clang -lpthread server.o gioco.o -o server
server.o : server.c gioco.c headerServer.h ../common.h
	clang -c -g server.c gioco.c headerServer.h ../common.h


clean :
	rm -f *.o *.gch server 