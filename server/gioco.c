#include "headerServer.h"

void *creaPartita(void *fd)
{
    gestioneGioco((int *)fd);
    return NULL;
}

void gestioneGioco(int *fd)
{
    //dove sono memorizzati gli fd dei giocatori
    t_coppia Players;
    Players.FD_Player1 = *fd;
    Players.FD_Player2 = *(fd + 1);

    //comunica ad entrambi i client quale numero gli è stato assegnato dal server
    inviaInfo(Players);

    //dove è memorizzato lo stato della partita
    t_partita stato;

    //genero random le pile
    stato.PilaA = (2 + rand() % 48);
    stato.PilaB = (2 + rand() % 48);
    stato.PID_Vincitore = 0;
    //La prima mossa va al primo client connesso
    stato.Turno = PLAYER1;

    //finché non c'è un vincitore
    while (stato.PID_Vincitore == 0)
    {
        aggiornaStatoPartita(stato, Players);

        if (stato.Turno == PLAYER1)
        {
            stato = riceviAzione(stato, Players.FD_Player1);
            //Se ha vinto, assengo la vittoria
            if (checkVittoria(stato) == 0)
            {
                stato.PID_Vincitore = Players.FD_Player1;
            }
            //turno al secondo giocatore
            stato.Turno = PLAYER2;
        }
        else
        {
            stato = riceviAzione(stato, Players.FD_Player2);
            if (checkVittoria(stato) == 0)
            {
                stato.PID_Vincitore = Players.FD_Player2;
            }
            stato.Turno = PLAYER1;
        }
    }

}

void inviaInfo(t_coppia Players)
{
    int numeroAssegnato;

    numeroAssegnato = PLAYER1;
    send(Players.FD_Player1, &numeroAssegnato, sizeof(int), 0);

    numeroAssegnato = PLAYER2;
    send(Players.FD_Player2, &numeroAssegnato, sizeof(int), 0);
}

void aggiornaStatoPartita(t_partita stato, t_coppia Players)
{
    send(Players.FD_Player1, &stato, sizeof(t_partita), 0);
    send(Players.FD_Player2, &stato, sizeof(t_partita), 0);
}

/*
    stato : contiene lo stato corrente della partita
    azione : contiene l'azione appena ricevuta dal client
    player : contiene il file descriptor del giocatore che compie l'azione
*/
t_partita riceviAzione(t_partita stato, int player)
{

    t_scelta azione;
    recv(player, &azione, sizeof(t_scelta), 0);
    fprintf(stderr, "Azione del client-> \nPILA:%c\nnumPedine:%d", azione.Pila, azione.numPedine);

    //se pari a 0, l'azione vuol dire che è valida.
    int flagErrore = 0;

    /* 
    Se la pila selezionata è corretta e la rimozione è possibile (checkRimozione)
    rimuovo le pedine, comunico al client il successo e torno lo stato partita aggiornato.

    Altrimenti, comunico al client l'errore e successivamente richiamo la procedura per attendere la "nuova azione
    */

    //TODO: azione.status è inutilizzato, cioè alla fine uso flagErrore
    if (azione.Pila == 'A' && checkRimozione(stato.PilaA, azione.numPedine) == TRUE)
    {
        //PILA A
        azione.status = 0;
        stato.PilaA -= azione.numPedine;
        send(player, &flagErrore, sizeof(int), 0);
        return stato;
    }
    else if (azione.Pila == 'B' && checkRimozione(stato.PilaB, azione.numPedine) == TRUE)
    {
        //PILA B
        azione.status = 0;
        stato.PilaB -= azione.numPedine;
        send(player, &flagErrore, sizeof(int), 0);
        return stato;
    }
    else
    {   
        //ZONA DI ERRORE UTENTE
        //Se siamo in questa sezione il client ha indicato una mossa non valida
        //L'errore può essere: Pila errata || NumeroPedine non valido
        if (azione.Pila != 'A' && azione.Pila != 'B')
        {
            flagErrore=PILA_ERR;
        }else{
            flagErrore=PEDINE_ERR;
        }

        send(player, &flagErrore, sizeof(int), 0);
        return riceviAzione(stato, player);
    }
}

int checkRimozione(int pedinePila, int numPedine)
{
    if (numPedine <= pedinePila && numPedine != 0)
    {
        return TRUE;
    }
    return FALSE;
}

//TODO:da implementare
int controllaConnessioneGiocatori()
{
    //utile solo per riuscire a compilare
    return 1;
}

int checkVittoria(t_partita stato)
{
    if (stato.PilaA == 0 && stato.PilaB == 0)
    {
        return TRUE;
    }
    return FALSE;
}
