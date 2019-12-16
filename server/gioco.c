#include "gioco.h"
#include "../common.h"




int creaGioco(int Player1, int Player2)
{
    srand(time(NULL)); // Initialization, should only be called once.
    //Da 2 a 50 pedine.. 1 pedina rappresenterebbe la vincita certa dell'avversario
    partita.PilaA = 2 + rand() % 50;
    partita.PilaB = 2 + rand() % 50;
    partita.PID_Vincitore = 0;
   
    //TODO: impostare una guardia aggiuntiva->il gioco continua finché entrambi i client sono connessi
    while (partita.PID_Vincitore == 0)
    {
        //comunica con il player1: informa sullo stato partita
        riceviDaClient(Player1); //TODO: adattare e passare parametri, tipo socket

        //Se il player1 non ha vinto con la mossa, turno player 2
        if (partita.PID_Vincitore == 0){
            //comunica con il player2: informa sullo stato partita
            riceviDaClient(Player2);
        }   
    }
}

void riceviDaClient(int PIDplayer)
{
    int status = 1; //se "-1", mossa non valida
    /*Avviene un doppio controllo, il primo se la pila scelta è valida
        *Il secondo se il numero di pedine da rimuovere è valido, nel caso Falso torna -1 e richiedo al client
        */
    do{
        //riceve struct da inserire nella struct "scelta"

        if (scelta.Pila == 'A')
        {
            status = checkRimozione(partita.PilaA, scelta.numPedine);
        }
        else if (scelta.Pila == 'B')
        {
            status = checkRimozione(partita.PilaB, scelta.numPedine);
        }
        else
        {
            status = 1;
            char errore[100] = "Errore, Pila errata o numero di pedine sbagliato";
            //send errore to client
        }
    } while (status == 1); //finché scelta non valida


    //Rimuovo pedine dalla pila scelta
    if (scelta.Pila == 'A')
    {
        partita.PilaA -= scelta.numPedine;
    }
    else if (scelta.Pila == 'B')
    {
        partita.PilaB -= scelta.numPedine;
    }
    checkVittoria(PIDplayer);
}

int checkRimozione(int Pila, int numPedine)
{
    if (numPedine <= Pila && numPedine != 0)
    {
        return 0;
    }
    return 1;
}

void checkVittoria(int PID_player){
    if (partita.PilaA == 0 && partita.PilaB == 0)
    {
        partita.PID_Vincitore = PID_player;
       
    }
}

void printPile()
{
    printf("stato partita:\n");
    printf("Pila A: %d \n Pila B: %d \n", partita.PilaA, partita.PilaB);
}

int main(int argc, char const *argv[])
{   
    partita.PilaA=29;
    printf("%d",partita.PilaA);
    return 0;
}
