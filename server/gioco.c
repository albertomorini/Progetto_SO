#include <stdio.h>
#include <time.h> //for random
#define MAXDIMPILA 100


struct statoGioco{
    int PilaA;
    int PilaB;
    int PID_Vincitore;
}stato;
/**
 * Metodo di creazione del gioco, si occupa di instanziare le variabili necessarie e di gestire lo sviluppo del gioco.
 * Crea un numero random di pedine per ogni pila(2)
 * Interagisce col client
 */
int creaGioco()
{

    srand(time(NULL));  // Initialization, should only be called once.
    //Da 2 a 50 pedine.. 1 pedina rappresenterebbe la vincita certa dell'avversario
    int PilaA = 2 + rand() % 50; 
    int PilaB = 2 + rand() % 50;
    aggiornaStruct(PilaA,PilaB);

/*
    printf("%d \n", PilaA);
    printf("%d \n", PilaB);
    printf("%d", rimuoviPedina(PilaA, 8));
*/
    
}
/**
 * Rimuove le pedine dalla pila se possibile altrimenti torna "-1"
 * @param Pila è la Pila slezionata
 * @param numPedine numero pedine da togliere (<= Pila per aver successo)
 */
int rimuoviPedina(int Pila, int numPedine)
{
    if (numPedine <= Pila)
    {
        return Pila -= numPedine;
    }else{
        return -1;
    }
}
//Inserisce il PID del player che ha vinto nella struct
void setVincitore(int vincitore){
    stato.PID_Vincitore=vincitore;
}
//Aggiorna il numero di pedine nelle varie pile.
void aggiornaStruct(int PilaA, int PilaB){
    stato.PilaA= PilaA;
    stato.PilaB= PilaB;
}

void printStatoPartita(){
    printf("Stato partita:\n");
    prinf("Pila A: %d \n Pila B: %d \n",stato.PilaA,stato.PilaB);
}

