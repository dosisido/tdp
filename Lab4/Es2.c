/*
 * Riccardo Rosin 284211
 * Lab 4 Es 2
*/
#include<stdio.h>
#include<stdlib.h>
#define MAX 30

void inserisciArray(int V[], int N){
    for(int i = 0; i < N; i++){
        printf("Inserisci la posizione %d: ", i+1);
        scanf("%d", &V[i]);
    }
}

void stampaArray(int V[], int N){
    printf("[ ");
    for(int i = 0; i<N ; i++) printf("%d ", V[i]);
    printf("]\n");
}

int pos(int delta, int N){
    if(delta<0) delta = N+delta;
    if(delta>=N) delta = delta-N;
    /* if(delta<0) return N-delta;
    if(delta>=N) return delta-N; */
    printf("delta = %d\n", delta);
    return delta;
}

void ruota(int V[MAX], int N, int P, int dir){
    int a,b, tmp[N/*Oppure P se lo dichiari come const int*/];

    /* if(P>N/2){
        P=N-P;
        dir*=-1;
    }

    switch(dir){
        case 1:
            for(a=0; a<P; a++) tmp[a] = V[a];
            for(a=0; a<N-abs(P); a++) V[a] = V[a+P];
            for(b = 0; b<P;b++) V[a+b] = tmp[b];
            break;
        case -1:
            printf("rotazione inversa\n");
            for(a=0; a<P; a++) tmp[a] = V[a+N-P];     //salvo le ultime P posizioni di V nelle prime posizioni di tmp
            stampaArray(tmp, P);
            //for(a=N-1; a>=N-P; a--) tmp[a] = V[a];
            for(a=N-1; a>=0; a--) V[a] = V[a-P];
            for(a=0; a<P; a++) V[a] = tmp[a];
            break;
    } */
    
    int i;
    for (int iter = 0; iter < P; iter++) {
        for (i = (N+dir)%N-1; i != ((N-dir)%N)*dir; i += 1*dir) {
            V[i] = V[i+1] + V[i] - (V[i+1] = V[i]);
        }
    }
}

int main(void){
    int V[MAX], N, P, dir; 
    do{
        printf("Inserisci la dimensione dell'array (dim<30): ");
        scanf("%d", &N);
    }while(N<0 || N>MAX);

    //inserisciArray(V, N);
    for(dir=0; dir<N; dir++) V[dir] = dir+1;
    stampaArray(V, N);
    
    printf("Inserisci di quanti caratteri vuoi effettuare la rotazione: "); scanf("%d", &P);
    while(P!=0){
        printf("Inserisci '-1' per una rotazione a destra e '1' per una rotazione a sinistra: "); scanf("%d", &dir);
        switch(dir){
            case -1: case 1: ruota(V, N, P, dir); stampaArray(V, N); break;
            default: printf("Inserimento non valido\n");
        }    
        printf("Inserisci di quanti caratteri vuoi effettuare la rotazione: "); scanf("%d", &P);
    }

    return 0;
}