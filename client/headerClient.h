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


/*
imposto l'indirizzo del socket
"sun_path" contiene un file nel filesystem il cui nome, completo di percorso, è specificato come una stringa terminata da uno zero;
"sun_family" negli indirizzi locali contiene il percorso del file di tipo socket generato
*/
const struct sockaddr_un addr = {
  .sun_family = AF_LOCAL,
  .sun_path = SOCKADDR
};

//Comunica con l'utente per sapere la pila e il numero di pedine
void aggiornaStato();
