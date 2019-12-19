#include "headerServer.h"


void *creaPartita(void *fd)
{
    gestioneGioco(fd);
    return NULL;
}

void gestioneGioco(void *fd)
{
    //cast alla struct dove trovo i player
    t_coppia Players = *(t_coppia *) fd;
    t_partita stato; 

    //genero random le pile
    stato.PilaA = (2 + rand() % 48);
    stato.PilaB = (2 + rand() % 48);
    stato.PID_Vincitore = 0;

    inviaMessaggio(Players.FD_Player1,"Benvenuto nel NIM Server!");
    inviaMessaggio(Players.FD_Player2,"Benvenuto nel NIM Server!");

    aggiornaStatoPartita(stato,&Players);

    stato=riceviAzione(stato,Players.FD_Player1);
    aggiornaStatoPartita(stato,&Players);

    stato=riceviAzione(stato,Players.FD_Player2);
    aggiornaStatoPartita(stato,&Players);

    /*
    //TODO: impostare una guardia aggiuntiva->il gioco continua finché entrambi i client sono connessi
    while (stato.PID_Vincitore == 0 && controllaConnessioneGiocatori()==1 )
    { 
        //TODO:implementare aggiorna stato partita
        //aggiornaStatoPartita();//aggiorna i due client dello stato della partita

        //TODO: adattare e passare parametri, tipo socket
        //TODO: sistemare i parametri della funzione
        //riceviDaClient(Player1); //attende la risposta della mossa da player1
        
        //se l'azione compiuta dal player è corretta allora aggiorno lo stato della partita 
        //aggiornaStatoPartita();

        //Se il player1 non ha vinto con la mossa, turno player 2
        if (stato.PID_Vincitore == 0){
            //comunica con il player2: informa sullo stato partita
            //TODO: sistemare il passaggio dei parametri della funzione
            //riceviDaClient(Player2);

            //se l'azione compiuta dal player è corretta allora aggiorno lo stato della partita 
            //aggiornaStatoPartita();
        }


    }*/
}

void aggiornaStatoPartita( t_partita stato,t_coppia *fd){
    send(fd->FD_Player1, &stato, sizeof(t_partita), 0);
    send(fd->FD_Player2, &stato, sizeof(t_partita), 0);
}

void inviaMessaggio(int fd,char *msg){ 
    int lunghezza=strlen(msg);
    send(fd,&lunghezza,sizeof(int),0);
    send(fd,&msg,sizeof(char)*strlen(msg),0);
}

/*
    stato : contiene lo stato corrente della partita
    azione : contiene l'azione appena ricevuta dal client
    player : contiene il file descriptor del giocatore che compie l'azione
*/
t_partita riceviAzione(t_partita stato, int player)
{

    t_scelta azione;
    recv(player,&azione,sizeof(t_scelta),0);
    fprintf(stderr,"Azione del client-> \nPILA:%c\nnumPedine:%d",azione.Pila,azione.numPedine);

    
    //se "-1", mossa non valida
    //Avviene un doppio controllo, il primo se la pila scelta è valida
    //Il secondo se il numero di pedine da rimuovere è valido, nel caso Falso torna -1 e richiedo al client
    //riceve struct da inserire nella struct "scelta"

    if (azione.Pila == 'A')
    {
        azione.status = checkRimozione(stato.PilaA, azione.numPedine);
    }
    else if (azione.Pila == 'B')
    {
        azione.status = checkRimozione(stato.PilaB, azione.numPedine);
    }
    else
    {
        azione.status = 1;
        char errore[100] = "Errore, Pila errata o numero di pedine sbagliato";
        fprintf(stderr,"ERRORE");
        //send errore to client
    }


    //Rimuovo pedine dalla pila scelta
    if (azione.Pila == 'A')
    {
        stato.PilaA -= azione.numPedine;
    }
    else if (azione.Pila == 'B')
    {
        stato.PilaB -= azione.numPedine;
    }
    //checkVittoria(PIDplayer);*/
    return stato;
}

int checkRimozione(int Pila, int numPedine)
{
    if (numPedine <= Pila && numPedine != 0)
    {
        return 0;
    }
    return 1;
}


//TODO:da implementare
int controllaConnessioneGiocatori(){
    //utile solo per riuscire a compilare
    return 1;
}

/*
//TODO:passare struct stato partita alle due funzioni sotto
void checkVittoria(int PID_player){
    if (partita.PilaA == 0 && partita.PilaB == 0)
    {
        partita.PID_Vincitore = PID_player;
       
    }
}*/