#include "headerServer.h"


void *Partita(void *fd)
{

    //cast alla struct dove trovo i player
    t_coppia coppiataLoc = *(struct coppia *)fd;
    t_partita stato;
    //genero random le pile
    stato.PilaA = (2 + rand() % 48);
    stato.PilaB = (2 + rand() % 48);
    stato.PID_Vincitore = 0;

    //invia ai due client la struct con lo stato della partita
    send(coppiataLoc.FD_Player1, &stato, sizeof(t_partita), 0);
    send(coppiataLoc.FD_Player2, &stato, sizeof(t_partita), 0);

    return NULL;
}

int controllaConnessioneGiocatori(){
    //utile solo per riuscire a compilare
    return 1;
}

int creaGioco(int Player1, int Player2)
{
    srand(time(NULL)); // Initialization, should only be called once.
    //Da 2 a 50 pedine.. 1 pedina rappresenterebbe la vincita certa dell'avversario
    //partita.PilaA = 2 + rand() % 50;
    //partita.PilaB = 2 + rand() % 50;
    t_partita stato;
    stato.PID_Vincitore = 0;
   

    //TODO: impostare una guardia aggiuntiva->il gioco continua finché entrambi i client sono connessi
    while (stato.PID_Vincitore == 0 && controllaConnessioneGiocatori()==1 )
    { 
        //TODO:implementare aggiorna stato partita
        //aggiornaStatoPartita();//aggiorna i due client dello stato della partita

        //TODO: adattare e passare parametri, tipo socket
        //TODO: sistemare i parametri della funzione
        //riceviDaClient(Player1); //attende la risposta della mossa da player1
        
        //se l'azione compiuta dal player è corretta allora aggiorno lo stato della partita 
        //aggiornaStatoPartita();

        //Se il player1 non ha vinto con la mossa, turno player 2
        if (stato.PID_Vincitore == 0){
            //comunica con il player2: informa sullo stato partita
            //TODO: sistemare il passaggio dei parametri della funzione
            //riceviDaClient(Player2);

            //se l'azione compiuta dal player è corretta allora aggiorno lo stato della partita 
            //aggiornaStatoPartita();
        }


    }
    return 1;
}
 
/*
    stato : contiene lo stato corrente della partita
    azione : contiene l'azione appena ricevuta dal client
*/
t_partita riceviDaClient(t_partita stato, t_scelta azione, int PIDplayer)
{
    azione.status = 1;
     //se "-1", mossa non valida
    //Avviene un doppio controllo, il primo se la pila scelta è valida
    //Il secondo se il numero di pedine da rimuovere è valido, nel caso Falso torna -1 e richiedo al client
        
    do{
        //riceve struct da inserire nella struct "scelta"

        if (azione.Pila == 'A')
        {
            azione.status = checkRimozione(stato.PilaA, azione.numPedine);
        }
        else if (azione.Pila == 'B')
        {
            azione.status = checkRimozione(stato.PilaB, azione.numPedine);
        }
        else
        {
            azione.status = 1;
            char errore[100] = "Errore, Pila errata o numero di pedine sbagliato";
            //send errore to client
        }
    } while (azione.status == 1); //finché scelta non valida


    //Rimuovo pedine dalla pila scelta
    if (azione.Pila == 'A')
    {
        stato.PilaA -= azione.numPedine;
    }
    else if (azione.Pila == 'B')
    {
        stato.PilaB -= azione.numPedine;
    }
    //checkVittoria(PIDplayer);
    return stato;
}

int checkRimozione(int Pila, int numPedine)
{
    if (numPedine <= Pila && numPedine != 0)
    {
        return 0;
    }
    return 1;
}
/*
//TODO:passare struct stato partita alle due funzioni sotto
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
*/