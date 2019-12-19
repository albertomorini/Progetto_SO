#include "headerClient.h"

void avvisaUscita()
{
    printf("Ok, bye bye! \n");
    //TODO: comunicare al server l'uscita
    //Volendo si può fare un controllo, tipo "sicuro di uscire? Digita n" etc.
    //Però bah, è superfluo, cioè ctrl+c vuol dire che sai già di voler uscire ahah
}
int main()
{
    //impostazione del socket locale
    int sock = socket(AF_LOCAL, SOCK_STREAM, 0);
    
    //contiene lo stato corrente della partita
    t_partita stato;
    
    //contiene la lunghezza dell'indirizzo del client
    socklen_t client_len = sizeof(addr);

    //casting obbligatorio dell'indirizzo del client
    //(const struct sockaddr *)&addr
    int fd = connect(sock, (const struct sockaddr *)&addr, client_len);

    //
    signal(SIGINT, avvisaUscita); //CTRL+C
    //Da provare, uno di questi, penso il "SIGQUIT" è nel caso si chiuda il terminale
    //da tenere anche SIGKILL e SIGTERM
    signal(SIGTERM, avvisaUscita);
    signal(SIGKILL, avvisaUscita);
    signal(SIGQUIT, avvisaUscita);
    
    signal(SIGABRT, avvisaUscita);
    signal(SIGSTOP, avvisaUscita);

    while(1){
        //riceve dati dalla struct e li salva nel buffet stato
        recv(sock, &stato, sizeof(t_partita), 0);
        printf("PilaA: %d\n", stato.PilaA);
        printf("PilaB: %d\n", stato.PilaB);
    }


    /*
    do
    {
        //ricezione stato partita e update della struttura partita
        prendiInput();
        //invia al server la struttura scelta
        //ricevi dal server
    } while (partita.PID_Vincitore == 0);
    */
    
    
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



