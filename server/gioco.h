#include <stdio.h>
#include <time.h> //for random



/**
 * Player1, Player2 = PID dei giocatori(clients)
 * Metodo di creazione del gioco, si occupa di instanziare le variabili necessarie e di gestire lo sviluppo del gioco.
 * Crea un numero random di pedine per ogni pila(2)
 * Interagisce col client
 */
int creaGioco(int Player1, int Player2);

/**
 * Si occupa di ricevere la struttura scelta dal client e aggiornare quella locale
 * e di rimuovere il num di pedine scelto dalla pila selezionata
 */
void riceviDaClient(int PIDplayer);

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
