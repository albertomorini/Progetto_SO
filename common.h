// Header comune al Server e Client

//indirizzo dove verrà salvato il file temporaneo per la comunicazione socket
#define SOCKADDR "/tmp/upperserver.socket"


struct partitaGioco
{
    int PilaA;
    int PilaB;
    int PID_Vincitore;

} partita;

struct scelta
{
    char Pila;
    int numPedine;
    int status;
} scelta;
