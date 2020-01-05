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
    Players.FD_Player1=*fd;
    Players.FD_Player2=*(fd+1);

    //comunica ad entrambi i client quale numero gli è stato assegnato dal server
    inviaInfo(Players);

    //dove è memorizzato lo stato della partita
    t_partita stato;

    //genero random le pile
    stato.PilaA = (2 + rand() % 48);
    stato.PilaB = (2 + rand() % 48);
    stato.Vincitore = NESSUNO;
    stato.Turno=PLAYER1;

    //invia stato partita INIZIALE
    aggiornaStatoPartita(stato, Players);

    while (stato.Vincitore==NESSUNO)
    {
        switch (stato.Turno)
        {
            case PLAYER1:
                inviaStatoPartita(stato,Players.FD_Player1);
                stato=riceviAzione(stato,Players.FD_Player1);
                inviaStatoPartita(stato,Players.FD_Player2);
            break;

            case PLAYER2:
                inviaStatoPartita(stato,Players.FD_Player2);
                stato=riceviAzione(stato,Players.FD_Player2);
                inviaStatoPartita(stato,Players.FD_Player1);
            break;

            default:
                break;
        }
        aggiornaStatoPartita(stato, Players);
    }

}

void inviaInfo(t_coppia Players){
    int numeroAssegnato;

    numeroAssegnato=PLAYER1;
    send(Players.FD_Player1, &numeroAssegnato, sizeof(int), 0);

    numeroAssegnato=PLAYER2;
    send(Players.FD_Player2, &numeroAssegnato, sizeof(int), 0);
}

void inviaStatoPartita(t_partita stato, int player){
    send(player, &stato, sizeof(t_partita), 0);
}

void aggiornaStatoPartita(t_partita stato, t_coppia Players)
{
    send(Players.FD_Player1, &stato, sizeof(t_partita), 0);
    send(Players.FD_Player2, &stato, sizeof(t_partita), 0);
}

t_partita riceviAzione(t_partita stato, int player)
{
    t_scelta azione;
    recv(player, &azione, sizeof(t_scelta), 0);

    //indica lo stato dell'azione
    int statusAzione=OK;

    /* 
    Se azione.Pila è corretta(='A','B') e il numero di pedine è corretto
    segue la correttezza di checkRimozione
    allora rimuovo le pedine e imposto lo stato azione come positivo
    altrimenti identifico l'errore e lo comunico al client con "-1"
    */
    if (azione.Pila == 'A' && controllaRimozione(stato.PilaA, azione.numPedine) == TRUE)
    {
        stato.PilaA -= azione.numPedine;
    }
    else if (azione.Pila == 'B' && controllaRimozione(stato.PilaB, azione.numPedine) == TRUE)
    {
        stato.PilaB -= azione.numPedine;
    }
    else
    {
        if (azione.Pila != 'A' || azione.Pila != 'B')
        {
            statusAzione=ERR_PILA;
        }
        else
        {
            statusAzione=ERR_PEDINE;
        }
    }

    //invia il numero di errore al client, poi lui stamperà il messaggio di errore
    send(player,&statusAzione,sizeof(int),0);
    if (statusAzione != OK)
    {
        return riceviAzione(stato, player);
    }
    else
    {
        return stato;
    }
}

int controllaRimozione(int Pila, int numPedine)
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
