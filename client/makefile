all : client

client : client.o
	clang client.o -o client
client.o : client.c headerClient.h ../common.h
	clang -c -g client.c headerClient.h ../common.h

clean :
	rm -f *.o client 
