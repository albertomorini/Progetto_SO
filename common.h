// Header comune al Server e Client

//indirizzo dove verrà salvato il file temporaneo per la comunicazione socket
#define SOCKADDR "/tmp/upperserver.socket"
#include <sys/types.h>
#include <signal.h>
#include <sys/socket.h>

/**
 * Struct utilizzata per salvare la mossa del player che verrà 
 * poi comunicata al server
 */
typedef struct partitaGioco
{
    int PilaA;
    int PilaB;
    int Vincitore;
    int Turno;
}t_partita;

/**
 * Struct utilizzata per salvare la mossa del player che verrà 
 * poi comunicata al server
 */
typedef struct scelta
{
    char Pila;
    int numPedine;
    int status;
}t_scelta;

/**
 * Struct di supporto che memorizza i FileDescriptor dei client
 * Il server la instanzia e la popola per poi "passarla" al thread che si occuperà di comunicare con i client
*/
typedef struct coppia
{
    int FD_Player1;
    int FD_Player2;
}t_coppia;

#define TRUE 0
#define FALSE 1

//definisce i giocatori
#define NESSUNO 0
#define PLAYER1 1
#define PLAYER2 2

//Definisco i possibili errori delle azioni client
//Per comodità, in quanto sono comuni sia al server che al client
#define OK 0
#define ERRORE 1
#define ERR_PILA 2
#define ERR_PEDINE 3
#define CONNESSIONE_ON 9

//Errori socket
#define SOCK_ERR_SOCKET 1
#define SOCK_ERR_BIND 2
#define SOCK_ERR_LISTEN 3
#define SOCK_ERR_ACCEPT 4
#define SOCK_ERR_SEND 5
#define SOCK_ERR_RECV 6
#define SOCK_ERR_CONNECT 7
