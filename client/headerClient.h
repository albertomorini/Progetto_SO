#include "../common.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
 
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

//Se un segnale viene eseguito, viene invocata la procedura avvisaUscita che si occuperà di avvisare il server
void avvisaUscita();

//Si occupa di ricevere dal server l'esito della scelta inviata da client
//Inoltre traduce anche a video l'errore nel caso la mossa sia scorretta.
int isMossaValida(int server);

//stampa l'esito finale della partita
void esitoPartita(int numeroAssegnato,t_partita stato);

void check(int result, int exitval);
