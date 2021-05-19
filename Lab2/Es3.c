/*
 * Riccardo Rosin 284211
 * Lab 2 Es 3
*/
#include<stdio.h>
#define nameIn "sorgente.txt"
#define comp "compresso.txt"
#define decomp "decompresso.txt"

int isNum(int c){
    return c >= '0' && c <= '9';
}

int comprimi(FILE *fin, FILE *fout){
    int count, righe=0;
    char thisCar, oldCar;
    if((oldCar = fgetc(fin)) == EOF) return 0;
    for(;(thisCar = fgetc(fin)) && oldCar != EOF; oldCar = thisCar){
        if(thisCar == oldCar){
            count++;
            if(count==9){
                fprintf(fout,"%c$%d", thisCar, count);
                righe+= 3;
                count = 0;
                oldCar = thisCar;
                if((thisCar = fgetc(fin)) && oldCar == EOF) break;
            }
        }else{
            fprintf(fout, (count==0) ? "%c" : "%c$%d" , oldCar, count);
            righe+=(count==0) ? 1 : 3;
            count = 0;
        }
    }
    return righe;
}

int decomprimi(FILE *fin, FILE *fout){
    int righe =0, n;
    char thisCar, oldCar;
    if((oldCar = fgetc(fin)) == EOF) return 0;
    for(;(thisCar = fgetc(fin)) && oldCar != EOF; oldCar = thisCar){
        if(thisCar == '$'){
            //procedura di estensione
            n= (int)fgetc(fin);
            if(!isNum(n)){
                printf("Errore nel file di input\n");
                return 0;
            }
            n-='0';
            for(thisCar = 0; thisCar<=n; thisCar++){
                fprintf(fout, "%c", oldCar);
                righe++;
            }
            if((thisCar = fgetc(fin)) == EOF) break;
        }else{
            //stampa e basta
            fprintf(fout, "%c", oldCar);
            righe++;
        }
    }
    return righe;
}

int main(void){
    FILE *fin, *fout;
    int bool;
    if ((fin = fopen(nameIn, "r")) == NULL){
        printf("Errore nell'apertura del file di input");
        return 1;
    }
    printf("Insrisci c per comprimi e d per decomprimi: ");
    scanf(" ");
    switch(getchar()){
        case 'C': case 'c':
            bool = 1;
            break;
        case 'D': case 'd':
            bool = 0;   
            break;
    }
    if ((fout = fopen((bool) ? comp : decomp, "w")) == NULL){
        printf("Errore nell'apertura del file di scrittura");
        return 1;
    }
    printf("Modificati %d caratteri", (bool) ? comprimi(fin, fout) : decomprimi(fin, fout));
    fclose(fout);fclose(fin);
    return 0;
}