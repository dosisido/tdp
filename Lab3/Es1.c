/*
 * Riccardo Rosin 284211
 * Lab 3 Es 1
*/
#include<stdio.h>
#include<ctype.h>
#define inFile "input.txt"
#define outFile "testo.txt"
#define maxLength 25
#define spazio 1
#define spazioMaiuscola 2
#define maiuscola 3

int endRow(FILE*fout, int actualCar){
    for (actualCar; actualCar<maxLength; actualCar++){
        fprintf(fout, " ");
    }   
    return maxLength-actualCar;
}

int main(void){
    char modify = 0;
    short unsigned int limit = 0, actualCar = 0;
    char thisCar;

    FILE *fin, *fout;
    if ((fin = fopen(inFile, "r")) == NULL){
        printf("Errore nell'apertura del file di input");
        return 1;
    }
    if ((fout = fopen(outFile, "w")) == NULL){
        printf("Errore nell'apertura del file di output");
        return 2;
    }

    while((thisCar = fgetc(fin)) != EOF){
        if((modify==spazio || modify == spazioMaiuscola)  && !isspace(thisCar)){
            fprintf(fout, " ");
            limit++; actualCar++;
            if(limit==maxLength){
                fprintf(fout, "| c:%d\n", actualCar);
                limit = 0;
                actualCar = 0;
            }
        }
        modify = (modify == spazio) ? 0 : modify;
        modify = (modify == spazioMaiuscola) ? maiuscola : 0;
        if(thisCar == '\n'){
            endRow(fout, actualCar);
            limit = maxLength;
            actualCar++;
        }else if(isdigit(thisCar)){
            fprintf(fout, "*");
            limit++;actualCar++;
        }else if(ispunct(thisCar)){
            //gestisce se stampare solo spazio o anche la maiuscola
            modify = (thisCar=='.' || thisCar=='!' || thisCar=='?')? spazioMaiuscola : spazio;
            fprintf(fout, "%c", thisCar);
            limit++;actualCar++;
        }else{
            if(isalpha(thisCar) && modify > spazioMaiuscola) modify = 0;
            fprintf(fout, "%c" ,(modify>spazioMaiuscola)? toupper(thisCar) : thisCar);
            limit++; actualCar++;
        }
        if(limit==maxLength){
            fprintf(fout, "| c:%d\n", actualCar);
            limit = 0;
            actualCar = 0;
        }
        if(limit==maxLength){
            fprintf(fout, "| c:%d\n", actualCar);
            limit = 0;
            actualCar = 0;
        }
    }
    if(limit!=0){
        endRow(fout, actualCar);
        fprintf(fout, "| c:%d", actualCar);
        limit = 0;
        actualCar = 0;
    }
    
    fclose(fout);fclose(fin);    
    return 0;
}