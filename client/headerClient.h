#ifndef HEADER_CLIENT_H
#define HEADER_CLIENT_H

#include "../common.h"
 
const struct sockaddr_un addr = {
  .sun_family = AF_LOCAL,
  .sun_path = SOCKADDR
};

//riceve in input l'azione del giocatore
t_scelta prendiInput();

//pulisce il terminale
void clearScreen();

//stampa lo stato della partita, quindi il numero di pedine correnti nelle pile
void stampaStato(int numeroAssegnato,t_partita stato);

//stampa l'errore relativo allo status
void stampaErrore(int statusAzione);

//riceve dal server la validità della mossa effettuata
int isMossaValida(int server);

//stampa l'esito finale della partita
void esitoPartita(int numeroAssegnato,t_partita stato);

//stampa i potenziali errori generati dalle funzioni socket
void check(int result, int exitval);

#endif