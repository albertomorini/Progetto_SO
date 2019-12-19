#include "headerServer.h"

/**
 * Struct che memorizza i vari FileDescriptor dei client
 * così da poterli passare al thread.
 * NB: da mettere nella classe gioco.c e chiamare CreaPartita al posto di Partit.. ora ho fatto su questa classe per provare
*/

int main()
{
    fprintf(stderr,"Server ON");
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

    //pthread_t arrayThread[200]; //array di thread(fino a 200 partite ora)
    t_coppia coppiaLoc; 

    while (1)
    {
        struct sockaddr_un client_addr;
        socklen_t client_len = sizeof(client_addr);

        //accetto la connessione di player1
        int fd1 = accept(sock, (struct sockaddr *)&client_addr, &client_len);
        coppiaLoc.FD_Player1 = fd1;
        fprintf(stderr,"Player 1 connesso, attendo l'avversario..");
        
        int fd2 = accept(sock, (struct sockaddr *)&client_addr, &client_len);
        coppiaLoc.FD_Player2 = fd2;
        fprintf(stderr,"Player 2 connesso, avvio la partita..");

        pthread_t thread;
        //è compito del thread gestire le connessioni
        //lancio la partita
        pthread_create(&thread, NULL, Partita, (void *)&coppiaLoc);
        
    }
}