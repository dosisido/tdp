/*
 * Riccardo Rosin 284211
 * Lab 4 Es 1
*/
#include<stdio.h>
#define MAX 30
#define fileIn "input.txt"

int leggiArray(int V[]){
    int i;
    FILE *fin;
    if ((fin = fopen(fileIn, "r")) == NULL){
        printf("Errore nell'apertura del file di input");
        return 1;
    }

    for(i=0; fscanf(fin, "%d", &V[i]) ==1 && i<MAX; i++);
    
    fclose(fin);
    return i;
}

void stampaArray(int V[], int start, int end){
    printf("[ ");
    for(start; start <= end; start++) printf("%d ", V[start]);
    printf("]\n");
}

void sottoSequenze(int V[], int N){
    unsigned int maxS = 0, i, counter = 0;
    //prendo la dimensione massima
    for(i=0; i<N; i++){
        if(V[i] != 0) {if(++counter >  maxS) maxS = counter;}
        else counter = 0;
    }

    //printf("Massima dimensione: %d\n", maxS);

    counter = 0;
    for(i=0; i<N; i++){
        //printf("i = %d, counter = %d\n", i, counter);
        if(i-counter == maxS-1){
            stampaArray(V, counter, i);
            counter=i+2;
        }
        if(V[i] == 0) counter = i+1;
    }
}

int main(void){
    int V[MAX], N;

    N = leggiArray(V);
    sottoSequenze(V, N);

    return 0;
}   