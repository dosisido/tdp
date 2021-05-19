#include<stdio.h>
#include<limits.h>
#define inFile "numeri.txt"

int isPossibleOperation(int a, int b, int c){
    if(a+b == c) return 1;
    if(a-b == c) return 2;
    if(a*b == c) return 3;
    if(b !=0 && a/b == c) return 4;
    return 0;
}

int main(void){
    int max, min, thisNum, lastNum, lastLastNum;
    unsigned int scarto;
    //char thisChar;
    FILE *fin;
    if ((fin = fopen(inFile, "r")) == NULL){
        printf("Errore nell'apertura del file di input");
        return 1;
    }
    if(fscanf(fin, " %d", &lastLastNum) !=1){printf("Errore, file di input vuoto"); return 1;}
    max = min = lastLastNum;
    if(fscanf(fin, " %d", &lastNum) !=1){printf("Errore, insufficenti parametnri nel file di input"); return 2;}
    if(lastNum>max)max = lastNum;
    if(lastNum<min)min = lastNum;

    //for(fscanf(fin, "%d", &thisNum); thisNum != EOF; fscanf(fin, "%d", &thisNum))
    while(fscanf(fin, " %d", &thisNum) == 1){
        if(isPossibleOperation(lastLastNum, lastNum, thisNum)){
            if(thisNum>max)max = thisNum;
            if(thisNum<min)min = thisNum;
            lastLastNum = lastNum;
            lastNum = thisNum;
        }else scarto++;
    }
    printf("Numero massimo: %d\n", max);
    printf("Numero minimo: %d\n", min);
    printf("Numeri scartati: %d\n", scarto);

    fclose(fin);
    return 0;
}