#include "headerServer.h"

int main()
{   
    fprintf(stderr,"---Server ON---\n");

    //chiamata fatta una volta per inizializzare il random, così da evitare da avere random uguali ogni volta
    srand(time(NULL)); 
    //Inizializzo socket server
    int sock = socket(AF_LOCAL, SOCK_STREAM, 0);

    // imposto l'indirizzo del socket
    struct sockaddr_un addr = {
        .sun_family = AF_LOCAL,
        .sun_path = SOCKADDR};

    unlink(SOCKADDR);

    // lego l'indirizzo al socket di ascolto
    if (bind(sock,(struct sockaddr *)&addr, sizeof addr) == -1)
    {
        perror("bind()");
        return 2;
    }

    // Abilito effettivamente l'ascolto, con un massimo di 20 client in attesa
    listen(sock, 20);

    //Istanzio la struct t_coppia per mantenere i FileDescriptor dei client che si connetteranno
    //per poi passarla a gioco.c che gestirà la partita e comunicherà con i client

    while (1)
    {   
        struct sockaddr_un client_addr;
        socklen_t client_len = sizeof(client_addr);

        //contiene la coppia di file descriptor
        int *fd; 

        //accetto la connessione di player1
        *fd = accept(sock, (struct sockaddr *)&client_addr, &client_len);
        fprintf(stderr,"Player 1 connesso, attendo l'avversario..\n");
        
        //accetto la connessione del player2
        *(fd+1) = accept(sock, (struct sockaddr *)&client_addr, &client_len);
        fprintf(stderr,"\nPlayer 2 connesso, avvio la partita..\n");


        //instanzio il thread che lancerà la procedura di partita
        pthread_t thread;
        
        //lancio la partita
        pthread_create(&thread, NULL, creaPartita, fd);
        
        //ATTENZIONE: Non ha senso chiudere le socket qui, perchè?
        //close(fd1);
        //close(fd2);
    }
}