all : client server

client : client.o
	clang client.o -o nimclient
client.o : ./client/client.c ./client/headerClient.h common.h
	clang -c -g ./client/client.c ./client/headerClient.h common.h

server : server.o gioco.o
	clang -lpthread server.o gioco.o -o nimserver
server.o : ./server/server.c ./server/gioco.c ./server/headerServer.h common.h
	clang -c -g ./server/server.c ./server/gioco.c ./server/headerServer.h common.h

clean :
	rm -f *.o *.gch