all : server client

server : ./server/server.o ./server/gioco.o
	clang ./server/server.o -o ./server/server
server.o : ./server/server.c ./server/gioco.c ./server/headerServer.h ./server/headerGioco.h common.h
	clang ./server/server.c ./server/gioco.c 

client : ./client/client.o
	clang ./client/client.o -o ./client/client
client.o : ./client/client.c ./client/headerClient.h common.h
	clang ./client/client.c

clean :
	rm -f *.o ./server/server ./client/client 
