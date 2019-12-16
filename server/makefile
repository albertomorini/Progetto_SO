all : server

server : server.o gioco.o
	clang server.o gioco.o -o server
server.o : server.c gioco.c headerServer.h headerGioco.h ../common.h
	clang server.c gioco.c 

clean :
	rm -f *.o server 