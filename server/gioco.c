#include "headerServer.h"

void *creaPartita(void *fd)
{
    gestioneGioco(fd);
    return NULL;
}

void gestioneGioco(void *fd)
{
    //cast alla struct dove trovo i player
    t_coppia Players = *(t_coppia *)fd;
    t_partita stato;

    //genero random le pile
    stato.PilaA = (2 + rand() % 48);
    stato.PilaB = (2 + rand() % 48);
    stato.PID_Vincitore = 0;

    inviaMessaggio(Players.FD_Player1, "Benvenuto nel NIM Server!");
    inviaMessaggio(Players.FD_Player2, "Benvenuto nel NIM Server!");

    while ( (checkVittoria(stato) == FALSE) && stato.PID_Vincitore==0)
    {
        aggiornaStatoPartita(stato, &Players);
        //controllo connessione P1 -> se non c'è 
        //vittore all'altro giocatore
        stato = riceviAzione(stato, Players.FD_Player1);
        aggiornaStatoPartita(stato, &Players);
        //ceckVittoria(stato) -> se ha vinto stato.PID_Vincitore=Players.FD_Player1

        //controllo connessione P2
        stato = riceviAzione(stato, Players.FD_Player2);
        aggiornaStatoPartita(stato, &Players);
        //ceckVittoria(stato) -> se ha vinto stato.PID_Vincitore=Players.FD_Player1
    }

}

void aggiornaStatoPartita(t_partita stato, t_coppia *fd)
{
    send(fd->FD_Player1, &stato, sizeof(t_partita), 0);
    send(fd->FD_Player2, &stato, sizeof(t_partita), 0);
}

void inviaMessaggio(int fd, char *msg)
{
    int lunghezza = strlen(msg);
    send(fd, &lunghezza, sizeof(int), 0);
    send(fd, &msg, sizeof(char) * strlen(msg), 0);
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

    /* 
    Se azione.Pila è corretta(='A','B') e il numero di pedine è corretto
    segue la correttezza di checkRimozione
    allora rimuovo le pedine e imposto lo stato azione come positivo
    altrimenti identifico l'errore e lo comunico al client con "-1"
    */
    if (azione.Pila == 'A' && checkRimozione(stato.PilaA, azione.numPedine) == TRUE)
    {
        azione.status = 0;
        stato.PilaA -= azione.numPedine;
    }
    else if (azione.Pila == 'B' && checkRimozione(stato.PilaB, azione.numPedine) == TRUE)
    {
        azione.status = 0;
        stato.PilaB -= azione.numPedine;
    }
    else
    {
        //TODO: inserire le stringhe di errore segnate come commenti ora
        //Dentro una variabile che verrà mandata al client
        //String strErrore='';
        if (azione.Pila != 'A' || azione.Pila != 'B')
        {
            //strErrore +=ERRORE PILA INESISTENTE
        }
        else
        {
            //strErrore += ERRORE NUMERO PEDINE SBAGLIATO
        }
        azione.status = 1;
        fprintf(stderr, "ERRORE");
    }
    //send azione.status to client, se 0 ok 1 dovrà riprovare

    //TODO: Gestione enumerativi, io pensavo di comunicare al client un vettore di caratteri con l'errore.. Tu come pensavi?
    //Guarda common.h

    if (azione.status == 1)
    {
        //send anche il messaggio di errore al client
        //send in questo punto del codice in quanto il client sa già
        //che c'è stato un errore e così sarà pronto a ricevere la stringa d'errore
        //send strErrore
        return riceviAzione(stato, player);
    }
    else
    {
        return stato;
    }
}

int checkRimozione(int Pila, int numPedine)
{
    if (numPedine <= Pila && numPedine != 0)
    {
        return 0;
    }
    return 1;
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
        return 0;
    }
    return 1;
}
