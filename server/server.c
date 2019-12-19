#include "headerServer.h"


/**
 * Struct che memorizza i vari FileDescriptor dei client
 * così da poterli passare al thread.
 * NB: da mettere nella classe gioco.c e chiamare CreaPartita al posto di Partit.. ora ho fatto su questa classe per provare
*/

int main()
{
    fprintf(stderr,"In ascolto..\n");
    //Inizializzo socket
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

    while (1)
    {
        //inizializzo parametri di connessione
        struct sockaddr_un client_addr;
        socklen_t client_len = sizeof(client_addr);

        //contiene la coppia di file descriptor
        t_coppia Players; 

        //accetto la connessione di player1
        int fd1 = accept(sock, (struct sockaddr *)&client_addr, &client_len);
        Players.FD_Player1 = fd1;
        fprintf(stderr,"Player 1 connesso, attendo l'avversario..\n");
        
        int fd2 = accept(sock, (struct sockaddr *)&client_addr, &client_len);
        Players.FD_Player2 = fd2;
        fprintf(stderr,"\nPlayer 2 connesso, avvio la partita..\n");

        pthread_t thread;
        //è compito del thread gestire le connessioni
        //lancio la partita
        pthread_create(&thread, NULL, creaPartita, (void *)&Players);
        
    }
}