#include "headerServer.h"

void *creaPartita(void *socketGiocatori){
    gestioneGioco((int *)socketGiocatori);
    return NULL;
}

void gestioneGioco(int *socketGiocatori){
    t_coppia giocatori;
    giocatori.g1 = socketGiocatori[0];
    giocatori.g2 = socketGiocatori[1];

    //comunica ad entrambi i client quale numero gli è stato assegnato dal server
    inviaInfo(giocatori);

    //lo stato della partita
    t_partita stato;

    //genero random le pile
    stato.pilaA = (2 + rand() % 48);
    stato.pilaB = (2 + rand() % 48);
    stato.vincitore = NESSUNO;
    stato.turno=PLAYER1;
    stato.status=OK;

    //finché non c'è un vincitore
    while (stato.vincitore == NESSUNO){
        aggiornaStatoPartita(stato, giocatori);

        switch (stato.turno){
            case PLAYER1:
                stato = riceviAzione(stato, giocatori.g1 ,PLAYER2);
                //se g1 ha vinto assegno la vittoria
                if (controllaVittoria(stato) == NESSUNO){
                    stato.vincitore = PLAYER1;
                }
                //assegno il turno a g2
                stato.turno = PLAYER2;
                break;

            case PLAYER2:
                stato = riceviAzione(stato, giocatori.g2,PLAYER1);
                if (controllaVittoria(stato) == NESSUNO){
                    stato.vincitore = PLAYER2;
                }
                stato.turno = PLAYER1;
                break;
    
            default:
                fprintf(stderr,"Errore, qualcosa è andato storto");
                break;
            }
    }

    //comunica la vittoria ai client
    aggiornaStatoPartita(stato,giocatori);
    
    //chiudo le connessioni con i client
    close(giocatori.g1);
    close(giocatori.g2);

    //libero la memoria allocata
    free(socketGiocatori);

    fprintf(stderr,"\n---Una partita è terminata, le connessioni sono state chiuse---\n");
}

void inviaInfo(t_coppia giocatori)
{
    int numeroAssegnato;

    numeroAssegnato = PLAYER1;
    check(send(giocatori.g1, &numeroAssegnato, sizeof(int), 0),SOCK_ERR_SEND);

    numeroAssegnato = PLAYER2;
    check(send(giocatori.g2, &numeroAssegnato, sizeof(int), 0),SOCK_ERR_SEND);
}

void inviaStatoPartita(t_partita stato, int player){
    check(send(player, &stato, sizeof(t_partita), 0),SOCK_ERR_SEND);
}

void aggiornaStatoPartita(t_partita stato, t_coppia giocatori)
{
    /*
    Ignoro il segnale SIGPIPE tornato dalla funzione send(),
    in modo tale da non far cadere il server nel caso di
    errore (client disconnesso). 
    */
    sigignore(SIGPIPE);
    send(giocatori.g1, &stato, sizeof(t_partita), 0);
    send(giocatori.g2, &stato, sizeof(t_partita), 0);
}

t_partita riceviAzione(t_partita stato, int playerAttuale,int playerAvversario)
{
    t_scelta azione;

    //controllo la ricezione dal client, se 0 -> client disconnesso
    if(recv(playerAttuale, &azione, sizeof(t_scelta), 0)==0){
        //client disconnesso, assegno la vittoria all'avversario
        fprintf(stderr,"Un client si è disconnesso");
        stato.vincitore=playerAvversario;
        stato.turno=playerAvversario;
        stato.status=DISCONNESSIONE;
        return stato;
    }

    //segnala eventuali errori nell'azione ricevuta dal client
    int flagErrore = OK;

    /* 
    se la pila selezionata è corretta e la rimozione è possibile 
    rimuovo le pedine, comunico al client il successo e torno lo stato partita aggiornato

    altrimenti comunico al client l'errore ed attendo una nuova azione
    */

    if (azione.pila == 'A' && controllaRimozione(stato.pilaA, azione.numPedine) == TRUE){
        stato.pilaA -= azione.numPedine;
        check(send(playerAttuale, &flagErrore, sizeof(int), 0),SOCK_ERR_SEND);
        return stato;
    }
    else if (azione.pila == 'B' && controllaRimozione(stato.pilaB, azione.numPedine) == TRUE){
        stato.pilaB -= azione.numPedine;
        check(send(playerAttuale, &flagErrore, sizeof(int), 0),SOCK_ERR_SEND);
        return stato;
    }else{   
        //se siamo in questa sezione il client ha indicato una mossa non valida
        //l'errore può essere: Pila errata oppure NumeroPedine non valido
        if (azione.pila != 'A' && azione.pila != 'B'){
            flagErrore=ERR_PILA;
        }else{
            flagErrore=ERR_PEDINE;
        }

        check(send(playerAttuale, &flagErrore, sizeof(int), 0),SOCK_ERR_SEND);
        return riceviAzione(stato, playerAttuale,playerAvversario);
    }
}

int controllaRimozione(int pedinePila, int numPedine){
    if (numPedine <= pedinePila && numPedine != 0){
        return TRUE;
    }
    return FALSE;
}

int controllaVittoria(t_partita stato){
    if (stato.pilaA == 0 && stato.pilaB == 0){
        return TRUE;
    }
    return FALSE;
}
