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
    stato.Vincitore = NESSUNO;
    stato.Turno=PLAYER1;

    //finché non c'è un vincitore
    while (stato.Vincitore == NESSUNO)
    {
        aggiornaStatoPartita(stato, Players);

        switch (stato.Turno){
            case PLAYER1:
                stato = riceviAzione(stato, Players.FD_Player1);
                //Se ha vinto, assengo la vittoria
                if (controllaVittoria(stato) == NESSUNO)
                {
                    stato.Vincitore = PLAYER1;
                }
                //turno al secondo giocatore
                stato.Turno = PLAYER2;
                break;
            case PLAYER2:
                stato = riceviAzione(stato, Players.FD_Player2);
                if (controllaVittoria(stato) == NESSUNO)
                {
                    stato.Vincitore = PLAYER2;
                }
                stato.Turno = PLAYER1;
                break;
            
            default:
                //non dovrebbe mai arrivare qui, ma in caso si potrebbe lanciare un errore generico
                break;
            }
    }

    //comunica la vittoria
    aggiornaStatoPartita(stato,Players);
    close(Players.FD_Player1);
    close(Players.FD_Player2);
}

void inviaInfo(t_coppia Players)
{
    int numeroAssegnato;

    numeroAssegnato = PLAYER1;
    check(send(Players.FD_Player1, &numeroAssegnato, sizeof(int), 0),SOCK_ERR_SEND);

    numeroAssegnato = PLAYER2;
    check(send(Players.FD_Player2, &numeroAssegnato, sizeof(int), 0),SOCK_ERR_SEND);
}

void inviaStatoPartita(t_partita stato, int player){
    check(send(player, &stato, sizeof(t_partita), 0),SOCK_ERR_SEND);
}

void aggiornaStatoPartita(t_partita stato, t_coppia Players)
{
    check(send(Players.FD_Player1, &stato, sizeof(t_partita), 0),SOCK_ERR_SEND);
    check(send(Players.FD_Player2, &stato, sizeof(t_partita), 0),SOCK_ERR_SEND);
}

t_partita riceviAzione(t_partita stato, int player)
{
    t_scelta azione;
    check(recv(player, &azione, sizeof(t_scelta), 0),SOCK_ERR_RECV);

    //se pari a 0, l'azione vuol dire che è valida.
    int flagErrore = OK;

    /* 
    Se la pila selezionata è corretta e la rimozione è possibile (checkRimozione)
    rimuovo le pedine, comunico al client il successo e torno lo stato partita aggiornato.

    Altrimenti, comunico al client l'errore e successivamente richiamo la procedura per attendere la "nuova azione
    */

    if (azione.Pila == 'A' && controllaRimozione(stato.PilaA, azione.numPedine) == TRUE)
    {
        //PILA A
        stato.PilaA -= azione.numPedine;
        check(send(player, &flagErrore, sizeof(int), 0),SOCK_ERR_SEND);
        return stato;
    }
    else if (azione.Pila == 'B' && controllaRimozione(stato.PilaB, azione.numPedine) == TRUE)
    {
        //PILA B
        stato.PilaB -= azione.numPedine;
        check(send(player, &flagErrore, sizeof(int), 0),SOCK_ERR_SEND);
        return stato;
    }
    else
    {   
        //ZONA DI ERRORE UTENTE
        //Se siamo in questa sezione il client ha indicato una mossa non valida
        //L'errore può essere: Pila errata || NumeroPedine non valido
        if (azione.Pila != 'A' && azione.Pila != 'B')
        {
            flagErrore=ERR_PILA;
        }else{
            flagErrore=ERR_PEDINE;
        }

        check(send(player, &flagErrore, sizeof(int), 0),SOCK_ERR_SEND);
        return riceviAzione(stato, player);
    }
}

int controllaRimozione(int pedinePila, int numPedine)
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

int controllaVittoria(t_partita stato)
{
    if (stato.PilaA == 0 && stato.PilaB == 0)
    {
        return TRUE;
    }
    return FALSE;
}
