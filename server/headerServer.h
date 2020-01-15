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
void gestioneGioco(int *fd);


t_partita riceviAzione(t_partita stato, int playerAttuale,int playerAvversario);


/*
    Invia gli aggiornamenti della partita ai due client
*/
void aggiornaStatoPartita(t_partita stato, t_coppia fd);

/*
    invia lo stato ad entrambi i giocatori
*/
void inviaMessaggio(int fd,char *msg);

/**
 * Si occupa di ricevere la struttura scelta dal client e aggiornare quella locale
 * e di rimuovere il num di pedine scelto dalla pila selezionata
 */
/**
 * @require numero di pedine NON può essere maggiore del numero di pedine in pila o pari a zero
 * @param Pila è la Pila slezionata
 * @param numPedine numero pedine da togliere (<= Pila per aver successo)
 * @return TRUE se si possono togliere le pedine
 */
int controllaRimozione(int Pila, int numPedine);
 
//invia lo stato ad un giocatore specifico
void inviaStatoPartita(t_partita stato, int player);

/**
 * comunica ad entrambi i client il numero assegnato a loro dal server
 */
void inviaInfo();

//ritorna TRUE se entrambe le pile sono vuote, altrimenti FALSE
int controllaVittoria(t_partita stato);

//stampa i potenziali errori generati dalle funzioni socket
void check(int result, int exitval);
