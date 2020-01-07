#include "headerServer.h"

int main()
{   
    fprintf(stderr,"---Server ON---\n");

    //chiamata fatta una volta per inizializzare il random, così da evitare da avere random uguali ogni volta
    srand(time(NULL)); 
    //Inizializzo socket server
    int sock = socket(AF_LOCAL, SOCK_STREAM, 0);
    check(sock,SOCK_ERR_SOCKET);

    // imposto l'indirizzo del socket
    struct sockaddr_un addr = {
        .sun_family = AF_LOCAL,
        .sun_path = SOCKADDR};

    //rimuovo il file del socket precedente
    unlink(SOCKADDR);
    //assegno l'indirizzo locale ad un socket
    check(bind(sock, (struct sockaddr *)&addr, sizeof addr),SOCK_ERR_BIND);

    // pone il socket in attesa di una connessione, con un massimo di 20 client in attesa
    check(listen(sock, 20),SOCK_ERR_LISTEN);

    while (1)
    {   
        struct sockaddr_un client_addr;
        socklen_t client_len = sizeof(client_addr);

        //contiene la coppia di file descriptor
        int *fd; 

        //accetto la connessione di player1
        *fd = accept(sock, (struct sockaddr *)&client_addr, &client_len);
        check(*fd,SOCK_ERR_ACCEPT);
        fprintf(stderr,"\nUn giocatore si è connesso, attendo l'avversario..\n");
        
        //accetto la connessione del player2
        *(fd+1) = accept(sock, (struct sockaddr *)&client_addr, &client_len);
        check(*(fd+1),SOCK_ERR_ACCEPT);
        fprintf(stderr,"\nIl giocatore avversario si è connesso, avvio la partita..\n");

        //instanzio il thread che lancerà la procedura di partita
        pthread_t thread;
        
        //lancio la partita
        pthread_create(&thread, NULL, creaPartita, fd);

        // Informiamo il sistema del fatto che non verrà mai chiamata pthread_join()
        pthread_detach(thread);
    }
}

void check(int result, int exitval) {
  if(result == -1) {
    switch (exitval)
    {
    case SOCK_ERR_SOCKET:
        perror("Errore nella creazione del socket -> socket()");
        exit(exitval);
        break;
    case SOCK_ERR_BIND:
        perror("Errore nell'assegnazione dell'indirizzo al socket -> bind()");
        exit(exitval);
        break;
    case SOCK_ERR_LISTEN:
        perror("Socket non valido -> listen()");
        exit(exitval);
        break;
    case SOCK_ERR_ACCEPT:
        perror("Errore durante l'accettazione della connessione dal client -> accept()");
        exit(exitval);
        break;
    case SOCK_ERR_SEND:
        perror("Errore durante l'invio di dati -> send()");
        exit(exitval);
        break;
    case SOCK_ERR_RECV:
        perror("Errore durante la ricezione di dati -> recv()");
        exit(exitval);
        break;
    case SOCK_ERR_CONNECT:
        perror("Errore durante la connessione al server -> connect()");
        exit(exitval);
        break;
    default:
        break;
    }
  }
}