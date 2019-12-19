// Header comune al Server e Client

//indirizzo dove verrà salvato il file temporaneo per la comunicazione socket
#define SOCKADDR "/tmp/upperserver.socket"

/**
 * Struct utilizzata per salvare la mossa del player che verrà 
 * poi comunicata al server
 */
typedef struct partitaGioco
{
    int PilaA;
    int PilaB;
    int PID_Vincitore;

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
 * Con anche la socket del server per ricevere dal client
*/

typedef struct coppia
{
    int FD_Player1;
    int FD_Player2;
    int SocketServer;
}t_coppia;

