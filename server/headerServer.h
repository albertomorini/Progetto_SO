
#ifndef HEADER_SERVER_H
#define HEADER_SERVER_H

#include "../common.h"

#include <time.h> //for random

//funzione invocata dal thread, chiama "gestioneGioco(...)" per avviare la partita
void *creaPartita(void *socketGiocatori);

//funzione che gestisce la partita
void gestioneGioco(int *socketGiocatori);

//riceve un'azione compiuta da un giocatore e ne controlla la validità
t_partita riceviAzione(t_partita stato, int playerAttuale,int playerAvversario);

//invia gli aggiornamenti della partita ai client
void aggiornaStatoPartita(t_partita stato, t_coppia giocatori);

//controlla se la rimozione di una pedina è valida
int controllaRimozione(int Pila, int numPedine);
 
//invia lo stato della partita ad un giocatore specifico
void inviaStatoPartita(t_partita stato, int player);

//comunica ad entrambi i client il numero progressivo assegnato loro dal server
void inviaInfo(t_coppia giocatori);

//controlla se uno dei giocatori ha vinto
int controllaVittoria(t_partita stato);

//stampa i potenziali errori generati dalle funzioni socket
void check(int result, int exitval);

#endif