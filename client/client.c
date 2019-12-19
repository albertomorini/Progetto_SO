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
<<<<<<< HEAD
    int server = connect(sock, (const struct sockaddr *)&addr, client_len);
    //TODO:gestire eventuali errori di connesione valutando fd

    riceviMessaggio(server);
=======
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
>>>>>>> fafaa3a711cd78e1146c186ca124d464e3799d2b

    while(1){
        //riceve lo stato della partita
        recv(server, &stato, sizeof(t_partita), 0);
        printf("\nPilaA: %d\n", stato.PilaA);
        printf("PilaB: %d\n", stato.PilaB);

        //invia l'azione al server
        t_scelta azione=prendiInput();
        send(server,&azione, sizeof(t_scelta),0);

    }

    
    
}

void riceviMessaggio(int server){
    int byteMessaggio;
    recv(server,&byteMessaggio,sizeof(int),0);
    byteMessaggio=byteMessaggio*sizeof(char);
    char *msg;
    recv(server,&msg,byteMessaggio,0);
    for(int i=0;i<strlen(msg);i++){
        printf("%c",*(msg + i));
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



