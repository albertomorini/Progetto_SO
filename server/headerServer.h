#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/un.h> // per struct sockaddr_un
#include <sys/socket.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include <math.h>

#include "../common.h"

#include <time.h> //for random

void *creaPartita(void *fd);

/**
 * Player1, Player2 = file descriptor dei giocatori(clients)
 * Metodo di creazione del gioco, si occupa di instanziare le variabili necessarie e di gestire lo sviluppo del gioco.
 * Crea un numero random di pedine per ogni pila(2)
 * Interagisce col client
 */
void gestioneGioco(void *fd);


t_partita riceviAzione(t_partita stato, int player);


/*
    Invia gli aggiornamenti della partita ai due client
*/
void aggiornaStatoPartita(t_partita stato,t_coppia *fd);

/*
    Invia messaggi ai client
*/
void inviaMessaggio(int fd,char *msg);

/**
 * Si occupa di ricevere la struttura scelta dal client e aggiornare quella locale
 * e di rimuovere il num di pedine scelto dalla pila selezionata
 */
 //t_partita riceviDaClient(t_partita stato, t_scelta azione,int PIDplayer);

/**
 * Il numero di pedine non può essere maggiore del numero di pedine in pila o pari a zero
 * 1=FALSE, 0TRUE
 * @param Pila è la Pila slezionata
 * @param numPedine numero pedine da togliere (<= Pila per aver successo)
 */
int checkRimozione(int Pila, int numPedine);

/**
 * stampa su terminale le pile della struct Partita
 */
void printPile();

/**
 * Se le pile sono entrambe vuote(==0, non <0) assegno la vittoria al PID passato come parametro
 */
void checkVittoria(int PIDplayer);

/*
    Controlla che i giocatori siano online
*/
int controllaConnessioneGiocatori();




