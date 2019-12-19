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
        t_coppia Players; 

        //accetto la connessione di player1
        int fd1 = accept(sock, (struct sockaddr *)&client_addr, &client_len);
<<<<<<< HEAD
        Players.FD_Player1 = fd1;
=======
        coppiaLoc.FD_Player1 = fd1;
>>>>>>> fafaa3a711cd78e1146c186ca124d464e3799d2b
        fprintf(stderr,"Player 1 connesso, attendo l'avversario..\n");
        
        //accetto la connessione del player2
        int fd2 = accept(sock, (struct sockaddr *)&client_addr, &client_len);
<<<<<<< HEAD
        Players.FD_Player2 = fd2;
        fprintf(stderr,"\nPlayer 2 connesso, avvio la partita..\n");
=======
        coppiaLoc.FD_Player2 = fd2;
        fprintf(stderr,"Player 2 connesso, avvio la partita..\n");
>>>>>>> fafaa3a711cd78e1146c186ca124d464e3799d2b

        //instanzio il thread che lancerà la procedura di partita
        pthread_t thread;

        coppiaLoc.SocketServer=sock;
        //lancio la partita
<<<<<<< HEAD
        pthread_create(&thread, NULL, creaPartita, (void *)&Players);
        
=======
        pthread_create(&thread, NULL, Partita, (void *)&coppiaLoc);
        //Chiudo le socket
        close(fd1);
        close(fd2);
>>>>>>> fafaa3a711cd78e1146c186ca124d464e3799d2b
    }
}