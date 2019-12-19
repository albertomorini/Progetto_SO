// Header comune al Server e Client

//indirizzo dove verrà salvato il file temporaneo per la comunicazione socket
#define SOCKADDR "/tmp/upperserver.socket"


typedef struct partitaGioco
{
    int PilaA;
    int PilaB;
    int PID_Vincitore;

}t_partita;

typedef struct scelta
{
    char Pila;
    int numPedine;
    int status;
}t_scelta;

typedef struct coppia
{
    int FD_Player1;
    int FD_Player2;
}t_coppia;
