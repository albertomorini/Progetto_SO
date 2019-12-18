#include "headerServer.h"

/**
 * Struct che memorizza i vari FileDescriptor dei client
 * così da poterli passare al thread.
 * NB: da mettere nella classe gioco.c e chiamare CreaPartita al posto di Partit.. ora ho fatto su questa classe per provare
 */
struct structCoppia
{
    //TODO: save socket player1 and player2?
    //Per comunicare dal client a server, ho socket diverse??
    //Cioè una per client? O no?
    int FD_Player1;
    
    int FD_Player2;

};

void *Partita(void *fd)
{

    //cast alla struct dove trovo i player
    struct structCoppia coppiataLoc = *(struct structCoppia *)fd;

    //genero random le pile
    partita.PilaA = 2 + rand() % 48;
    partita.PilaB = 2 + rand() % 48;
    partita.PID_Vincitore = 0;

    //invio, ho provato anche con il while, mi va a volte
    while(1){
        send(coppiataLoc.FD_Player1, &partita, sizeof(coppiataLoc), 0); // Invio lunghezza del
        send(coppiataLoc.FD_Player2, &partita, sizeof(coppiataLoc), 0); // Invio lunghezza
    }
   

    return NULL;
}

int main()
{
    printf("Server ON"); //TODO: Non stampa a me
    

    //Inizializzo socket
    int sock = socket(AF_LOCAL, SOCK_STREAM, 0);

    // imposto l'indirizzo del socket
    struct sockaddr_un addr = {
        .sun_family = AF_LOCAL,
        .sun_path = SOCKADDR};

    unlink(SOCKADDR);
    // lego l'indirizzo al socket di ascolto
    if (bind(sock, (struct sockaddr *)&addr, sizeof addr) == -1)
    {
        perror("bind()");
        return 2;
    }

    // Abilito effettivamente l'ascolto, con un massimo di 20 client in attesa
    listen(sock, 20);

    pthread_t arrayThread[200]; //array di thread(fino a 200 partite ora)
    int counter = 0;
    struct structCoppia coppiaLoc; 

    while (1)
    {
        struct sockaddr_un client_addr;
        socklen_t client_len = sizeof(client_addr);

        //accetto la connessione
        int fd = accept(sock, (struct sockaddr *)&client_addr, &client_len);

        
        if (counter % 2 == 0)
        {   
            //player 1
            coppiaLoc.FD_Player1 = fd;
        }
        else
        {   
            //player 2

            coppiaLoc.FD_Player2 = fd;
            //creo il thread (è corretto)
            pthread_create(&arrayThread[counter], NULL, Partita, (void *)&coppiaLoc);
        }

        counter++;

        close(fd);
    }
}