/*
 * Riccardo Rosin 284211
 * Lab 2 Es 4
*/
#include<stdio.h>
#include<string.h>
#define dim 20

int addTxt(char s[]){    // return is 0 if string not long enough, else 1
    int l = strlen(s);
    if(s[l-1] != 't' || s[l-2] != 'x' || s[l-3] != 't' || s[l-4] != '.'){
        if(l+5 > dim) return 0;
        s = strcat(s, ".txt");
    }
    return 1;
}

int isAlfa(char c){
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

/* int endCar(char c){//carattere terminale
    return (c >= 'a') ? 'z' : 'Z';
} */

int startCar(char c){//carattere di start
    //printf("car: %c, startCar: %c\t", c, (c >= 'a') ? 'a' : 'A');
    return (c >= 'a') ? 'a' : 'A';
}

int codifica(FILE *fin, FILE *fout){
    int k=0, righe = 0;
    char thisCar, oldCar = '0';
    while((thisCar = fgetc(fin)) != EOF){
        if(thisCar >= '0' && thisCar <= '9'){
            /* numero */
            thisCar+= (thisCar + k>'9') ? k-10 : k;
            k = ++k % 10;
        }else
            /* Non numero */
            if(isAlfa(thisCar) && isAlfa(oldCar)){
                /* Entrambi caratteri */
                oldCar-= startCar(oldCar);//ottengo la posizione della lettera: a=0, b = 1 ecc
                thisCar+= (thisCar + oldCar > startCar(thisCar)+25) ? oldCar - 26 : oldCar;
            }
        fprintf(fout, "%c", thisCar);
        righe++;
        oldCar = thisCar;
    }
    return righe;
}

int decodifica(FILE *fin, FILE *fout){
    int k=0, righe = 0;
    char thisCar, oldCar = '0';
    while((thisCar = fgetc(fin)) != EOF){
        if(thisCar >= '0' && thisCar <= '9'){
            /* numero */
            printf("%c\t%d\t%c\t", thisCar, k, thisCar-(thisCar - k < '0') ? k+10 : k);
            /* if(thisCar-k < '0'){
                thisCar = thisCar-k+10;
            }else{
                thisCar = thisCar-k;
            } */
            thisCar-= (thisCar - k < '0') ? k-10 : k;
            printf("%c", thisCar);
            k = ++k % 10;
            fprintf(fout, "%c", thisCar);
        }else
            /* Non numero */
            if(isAlfa(thisCar) && isAlfa(oldCar)){
                /* Entrambi caratteri */
                oldCar-= startCar(oldCar);//ottengo la posizione della lettera: a=0, b = 1 ecc
                //thisCar-= (thisCar - oldCar > startCar(thisCar)+25) ? oldCar - 26 : oldCar;
                /* if(thisCar - oldCar < startCar(thisCar)){
                    fprintf(fout, "%c", thisCar - oldCar + 26);
                }else{
                    fprintf(fout, "%c", thisCar - oldCar);
                } */
                fprintf(fout, "%c", thisCar - ((thisCar - oldCar < startCar(thisCar)) ? oldCar - 26 : oldCar));
            }else
                fprintf(fout, "%c", thisCar);
            
        oldCar = thisCar;
        righe++;
    }
    return righe;
}

int main(void){
    char str[dim];
    FILE *fin, *fout;
    printf("Inserisci il nome del file di input: ");
    scanf("%s", str);
    addTxt(str);
    //start
    
    //codifica
    printf("Inserisci il nome del file di output: ");
    scanf("%s", str);
    addTxt(str);
    if ((fout = fopen(str, "w")) == NULL){
        printf("Errore nell'apertura del file di scrittura");
        return 1;
    }

    printf("Inserisci c per codificare e d per decodificare: ");
    scanf(" ");
    switch(getchar()){
        case 'C': case 'c':
            str[0] = 1;
            break;
        case 'D': case 'd':
             str[0] = 0;
            break;
    }

    printf("Stampati %d caratteri", (str[0]) ? codifica(fin, fout) : decodifica(fin, fout));
    
    fclose(fin);fclose(fout);
    return 0;
}