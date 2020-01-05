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
    int PID_Vincitore;
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
#define PLAYER1 1
#define PLAYER2 2

//Definisco i possibili errori delle azioni client
//Per comodità, in quanto sono comuni sia al server che al client
#define PILA_ERR 3
#define PEDINE_ERR 4

