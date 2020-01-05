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
    printf("Benvenuto nel NIM SERVER\n");
    fflush(stdout);
    sleep(1);

    //riceve lo stato iniziale della partita
    int res = recv(server, &stato, sizeof(t_partita), 0);
    //stampaStato(stato);

    while (stato.Vincitore == NESSUNO)
    {
        if (stato.Turno == numeroAssegnato)
        {
            clearScreen();
            stampaStato(numeroAssegnato,stato);
            printf("Tocca a te!\n");
            //invia l'azione del client
            t_scelta bfr;
            bfr = prendiInput();
            send(server, &bfr, sizeof(t_scelta), 0);

            /*
            Aspetto la conferma dal server che la mossa sia corretta
            Nel caso positivo, ricevo il nuovo stato
            Nel caso negativo, il server non invia il nuovo stato quindi rieseguo il ciclo
            */
            if (isMossaValida(server) == OK)
            {
                recv(server, &stato, sizeof(t_partita), 0);
            }else{
                //aspetta che venga premuto un tasto per continuare
                while(getchar()!='\n');
            }
            
        }
        else
        {
            clearScreen();
            stampaStato(numeroAssegnato,stato);
            printf("Aspetta, non è ancora il tuo turno\n");
            recv(server, &stato, sizeof(t_partita), 0);
        }
    }

    clearScreen();
    //fine della partita
    esitoPartita(numeroAssegnato,stato);
    return 0;
}

void esitoPartita(int numeroAssegnato,t_partita stato){
    if(stato.Vincitore==numeroAssegnato){
        printf("\t\t_________________________________\n");
        printf("\t\t|                                |\n");
        printf("\t\t|     Complimenti, HAI VINTO!    |\n");
        printf("\t\t|________________________________|\n");
    }else{
        printf("\t\t_________________________________\n");
        printf("\t\t|                                |\n");
        printf("\t\t|     Mi dispiace, HAI PERSO!    |\n");
        printf("\t\t|________________________________|\n");
    }
}

int isMossaValida(int server)
{
    int flagErrore = OK;
    recv(server, &flagErrore, sizeof(int), 0);

    if (flagErrore == ERR_PILA)
    {
        printf("Attenzione! Errore nella scelta della pila, riprova!\n");
    }
    else if (flagErrore == ERR_PEDINE)
    {
        printf("Attenzione! Errore nel numero di pedine indicato, riprova!\n");
    }
    return flagErrore;
}

t_scelta prendiInput()
{
    t_scelta azione;
    //Pila
    printf("Scegli la pila: ");
    scanf("%c",&azione.Pila);
    printf("\n");
    getchar();

    //Num pedine
    printf("Indica il numero di pedine: ");
    if(scanf("%d", &azione.numPedine)==1){
        printf("\n");
        getchar();
    }else{
        getchar();
        getchar();
    }

    return azione;
}

void stampaStato(int numeroAssegnato,t_partita stato)
{
    printf("Tu sei il giocatore %d\n", numeroAssegnato);
    printf("\t\t _________________________________\n");
    printf("\t\t| Ora è il turno del giocatore %d |\n", stato.Turno);
    printf("\t\t| PILA A : %d \t\t\t |\n", stato.PilaA);
    printf("\t\t| PILA B : %d \t\t\t |\n", stato.PilaB);
    printf("\t\t|________________________________|\n\n");
}

void avvisaUscita()
{
    printf("Ok, bye bye! \n");
    kill(getpid(), 0);
    //comunicare al server l'uscita
    //Volendo si può fare un controllo, tipo "sicuro di uscire? Digita n" etc.
    //Però bah, è superfluo, cioè ctrl+c vuol dire che sai già di voler uscire ahah
}

void clearScreen()
{
    system("@cls||clear");
    fflush(stdout);
}