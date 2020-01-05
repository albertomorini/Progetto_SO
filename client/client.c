#include "headerClient.h"

int main()
{   
    //Avvio i segnali
    signal(SIGINT, avvisaUscita); //CTRL+C
    //Da provare, uno di questi, penso il "SIGQUIT" è nel caso si chiuda il terminale
    //da tenere anche SIGKILL e SIGTERM
    signal(SIGTERM, avvisaUscita);
    signal(SIGKILL, avvisaUscita);
    signal(SIGQUIT, avvisaUscita);
    
    signal(SIGABRT, avvisaUscita);
    signal(SIGSTOP, avvisaUscita);

    //impostazione del socket locale
    int server = socket(AF_LOCAL, SOCK_STREAM, 0);
    
    //contiene lo stato corrente della partita
    t_partita stato;
    
    //contiene la lunghezza dell'indirizzo del client
    socklen_t client_len = sizeof(addr);

    //casting obbligatorio dell'indirizzo del client
    //(const struct sockaddr *)&addr
    connect(server, (const struct sockaddr *)&addr, client_len);
    
    //riceve il numero di giocatore assegnato dal server
    int temp;
    recv(server,&temp, sizeof(int), 0);
    const int numeroAssegnato=temp;
    printf("Tu sei il giocatore %d\n",numeroAssegnato);
    //riceve lo stato iniziale della partita
    stato=riceviStato(server);
    stampaStato(stato);

    while(stato.Vincitore==NESSUNO){       
        while(stato.Turno!=numeroAssegnato){
            printf("Aspetta, non è ancora il tuo turno;\n");
            fflush(stdout);
            sleep(5);
            }
        //riceve lo stato dopo la modifica dell'altro giocatore
        stato=riceviStato(server);
        stampaStato(stato);
        //invia l'azione al server
        int statusAzione=OK;
        do{
            t_scelta azione=prendiInput();
            send(server,&azione, sizeof(t_scelta),0);

            recv(server,&statusAzione,sizeof(int),0);
            if(statusAzione!=OK){
                stampaErrore(statusAzione);
            }

        }while(statusAzione!=OK);
        printf("\n");
    }
        
}

void stampaErrore(int statusAzione){
    switch (statusAzione)
    {
    case ERR_PEDINE:
        printf("ERRORE: inserire un numero di pedine corretto\n");
        break;
    case ERR_PILA:
        printf("ERRORE: selezionare la pila corretta\n");
        break;
    default:
        break;
    }
}

t_scelta prendiInput()
{
    t_scelta azione;
    printf("Scegli la pila: ");
    scanf("%c",&azione.Pila);
    printf("Indica il numero di pedine: ");
    scanf("%d",&azione.numPedine);
    return azione;
}

t_partita riceviStato(int server){
    t_partita stato;
    int res=recv(server,&stato, sizeof(t_partita), 0);
    return stato;
}

void stampaStato(t_partita stato){
    printf("Ora è il turno del giocatore %d\n",stato.Turno);
    printf("PILA A : %d\n",stato.PilaA);
    printf("PILA B : %d\n",stato.PilaB);
}

void avvisaUscita()
{
    printf("Ok, bye bye! \n");
    //TODO: comunicare al server l'uscita
    //Volendo si può fare un controllo, tipo "sicuro di uscire? Digita n" etc.
    //Però bah, è superfluo, cioè ctrl+c vuol dire che sai già di voler uscire ahah
}

