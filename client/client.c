#include "headerClient.h"


int main()
{
    //Creazione socket
    //connessione al server

    int sock = socket(AF_LOCAL, SOCK_STREAM, 0);

    socklen_t client_len = sizeof(addr);
    int fd_accettato = connect(sock, (const struct sockaddr *)&addr, client_len);


    while(1){

    recv(sock, &partita, sizeof(partita), 0);
    fprintf(stdout, "PilaA: %d\n", partita.PilaA);
    fprintf(stdout, "PilaB: %d\n", partita.PilaB);
    }


    /*
    do
    {
        //ricezione stato partita e update della struttura partita
        prendiInput();
        //invia al server la struttura scelta
        //ricevi dal server
    } while (partita.PID_Vincitore == 0);
    */
    
    
}

void prendiInput()
{

    printf("Scegli la pila:");
    scanf("%c",&scelta.Pila);
    printf("Indica il numero di pedine: ");
    scanf("%d",&scelta.numPedine);
}



