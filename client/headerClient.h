#ifndef HEADER_CLIENT_H
#define HEADER_CLIENT_H

#include "../common.h"
 
/*
imposto l'indirizzo del socket
"sun_path" contiene un file nel filesystem il cui nome, completo di percorso, è specificato come una stringa terminata da uno zero;
"sun_family" negli indirizzi locali contiene il percorso del file di tipo socket generato
*/
const struct sockaddr_un addr = {
  .sun_family = AF_LOCAL,
  .sun_path = SOCKADDR
};

/*
  Si occupa di prendere l'input da tastiera dell'utente.
  Quindi la scelta della Pila e il numero di pedine.
*/
t_scelta prendiInput();

//pulisce il terminale
void clearScreen();

//Stampa lo stato della partita, quindi il numero di pedine correnti nelle pile
void stampaStato(int numeroAssegnato,t_partita stato);

//riceve lo stato della partita dal server
t_partita riceviStato(int server);

//Comunica con l'utente per sapere la pila e il numero di pedine
void aggiornaStato();

//stampa l'errore relativo allo status
void stampaErrore(int statusAzione);

/*
  Si occupa di ricevere dal server l'esito della scelta inviata da client
  Inoltre traduce anche a video l'errore nel caso la mossa sia scorretta.
*/
int isMossaValida(int server);

//stampa l'esito finale della partita
void esitoPartita(int numeroAssegnato,t_partita stato);

//stampa i potenziali errori generati dalle funzioni socket
void check(int result, int exitval);

#endif