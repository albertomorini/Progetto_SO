all : client

client : client.o
	clang client.o -o client
client.o : client.c headerClient.h ../common.h
	clang client.c

clean :
	rm -f *.o client 
