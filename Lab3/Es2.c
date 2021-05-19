#include<stdio.h>
#define fileIn "expr.txt"

int isNumber(char c){
    return (c >= '0' && c <= '9');
}

int isOperators(char c){
    switch(c){
        case '+': case '-': case '*': case '/': case '%': 
            return 1;
        default: return 0;
    }
}

int main(void){
    int row=1, parentesi = 0, spazio = 0;
    unsigned short int error = 0;  /*   0 = none
                                        1 = numeri interrotti
                                        2 = segni mancanti
                                        3 = fine riga*/
    char oldCar = '\n', thisCar;
    FILE *fin;
    if ((fin = fopen(fileIn, "r")) == NULL){
        printf("Errore nell'apertura del file di input");
        return 1;
    }
    printf("Inizio programma\n");
    //if((oldCar = fgetc(fin)) == EOF) return 2;
    for(;(thisCar = fgetc(fin)) != EOF || oldCar != EOF;oldCar=thisCar){
        printf("thisCar = %c\n", thisCar);
        switch(thisCar){
            case '(':
                if(oldCar != '\n' && !isOperators(oldCar) && oldCar != '(') error = 1;
                parentesi++;
                break;
            case ')':
                if(!isNumber(oldCar) && !isOperators(oldCar)) error = 1;
                parentesi--;
                break;
            case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
                if(isNumber(oldCar) && spazio) error = 1; 
                break;
            case '+': case '-': case '*': case '/': case '%': 
                if(!isNumber(oldCar) && oldCar != ')') error = 2;
                //  true
                break;
            case ' ': 
                spazio=1;
                thisCar = oldCar;
                break;
            case '\n':
                //reset buffer
                error = 3;
                break;
        }
        if(parentesi<0){
            printf("Errore nelle parentesi (espressione %d)\n", row);
        }
        if(error > 0){
            switch(error){
                case 1:
                    //numeri interrotti
                    printf("Errore nella lettua di un numero (espressione %d)\n", row);
                    break;
                case 2:
                    // segni mancanti
                    printf("Errore nella lettua di un operando (espressione %d)\n", row);
                    break;
            }
            if(thisCar != '\n') while((oldCar = fgetc(fin)) != '\n' && oldCar != EOF) printf("%c", oldCar); //butta la riga
            row++;
            parentesi = 0;
            error = 0;
            //if((oldCar = fgetc(fin)) == EOF) break;
        }
    }
    printf("Fine programma");

    fclose(fin);
    return 0;
}