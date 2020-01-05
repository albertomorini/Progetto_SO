#include "headerClient.h"

int main()
{
    //TODO: da implementare meglio.
    //Avvio i segnali
    // signal(SIGINT, avvisaUscita); //CTRL+C

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
    recv(server, &temp, sizeof(int), 0);
    const int numeroAssegnato = temp;
    printf("Tu sei il giocatore %d\n", numeroAssegnato);

    int res = recv(server, &stato, sizeof(t_partita), 0);

    while (stato.PID_Vincitore == 0)
    {
        stampaStato(stato);
        if (stato.Turno == numeroAssegnato)
        {
            printf("Tocca a te! \n");
            t_scelta bfr = prendiInput();
            send(server, &bfr, sizeof(t_scelta), 0);

            /*
            Aspetto la conferma dal server che la mossa sia corretta
            Nel caso positivo, ricevo il nuovo stato
            Nel caso negativo, il server non invia il nuovo stato quindi rieseguo il ciclo
            */
            if (isMossaValida(server) == TRUE)
            {
                recv(server, &stato, sizeof(t_partita), 0);
            }
        }
        else
        {
            printf("Aspetta, non è ancora il tuo turno;\n");
            recv(server, &stato, sizeof(t_partita), 0);
        }
    }

    //TODO: ricever e stampare EsitoPartita(); da implementare

    return 0;
}

int isMossaValida(int server)
{
    int flagErrore = 0;
    recv(server, &flagErrore, sizeof(int), 0);

    if (flagErrore == PILA_ERR)
    {
        printf("Attenzione! Errore nella scelta della pila!\n");
        fflush(stdout);
        printf("Riprova\n");
        return FALSE;
    }
    else if (flagErrore == PEDINE_ERR)
    {
        printf("Attenzione! Errore nel numero di pedine indicato!\n");
        fflush(stdout);
        printf("Riprova\n");
        return FALSE;
    }
    return TRUE;
}

t_scelta prendiInput()
{
    t_scelta azione;
    //Pila
    printf("Scegli la pila: ");
    scanf("%c", &azione.Pila);
    fflush(stdout); //Svuoto l'output
    fflush(stdin);  //Svuoto l'input
    //Num pedine
    printf("Indica il numero di pedine: ");
    scanf("%d", &azione.numPedine);
    fflush(stdout); //Svuoto l'output
    fflush(stdin);  //Svuoto l'input

    return azione;
}

void stampaStato(t_partita stato)
{
    printf("\t\t _________________________________\n");
    printf("\t\t| Ora è il turno del giocatore %d |\n", stato.Turno);
    printf("\t\t| PILA A : %d \t\t\t |\n", stato.PilaA);
    printf("\t\t| PILA B : %d \t\t\t |\n", stato.PilaB);
    printf("\t\t|________________________________|\n");
}

void avvisaUscita()
{
    printf("Ok, bye bye! \n");
    kill(getpid(), 0);
    //comunicare al server l'uscita
    //Volendo si può fare un controllo, tipo "sicuro di uscire? Digita n" etc.
    //Però bah, è superfluo, cioè ctrl+c vuol dire che sai già di voler uscire ahah
}
