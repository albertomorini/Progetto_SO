#include "headerClient.h"

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
    //TODO:gestire eventuali errori di connesione valutando fd


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



