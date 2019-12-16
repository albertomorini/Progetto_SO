#include "headerClient.h"

int main()
{
    //Creazione socket
    //connessione al server

    do
    {
        //ricezione stato partita e update della struttura partita
        prendiInput();
        //invia al server la struttura scelta
        //ricevi dal server
    } while (partita.PID_Vincitore == 0);

    
    
}

void prendiInput()
{

    printf("Scegli la pila:");
    scanf("%c",&scelta.Pila);
    printf("Indica il numero di pedine: ");
    scanf("%d",&scelta.numPedine);
}



