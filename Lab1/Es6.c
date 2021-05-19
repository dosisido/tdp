/* 
 * Riccardo Rosin 284211
 * Lab 1 Es 6
 */
#include<stdio.h>
#define nameIn "Operations.txt"
#define nameOut "Results.txt"

int main(void){
    FILE *fin, *fout;
    char op;
    float n1, n2;
    if ((fin = fopen(nameIn, "r")) == NULL){
        printf("Errore nell'apertura del file di input");
        return 1;
    }
    if ((fout = fopen(nameOut, "w")) == NULL){
        printf("Errore nell'apertura del file di scrittura");
        return 1;
    }

    while(fscanf(fin, "%c%f%f ", &op, &n1, &n2)==3)
        switch(op){
            case '+':
                fprintf(fout, "%c %.2f\n", op, n1 + n2);
                break;
            case '-':
                fprintf(fout, "%c %.2f\n", op, n1 - n2);
                break;
            case '*':
                fprintf(fout, "%c %.2f\n", op, n1 * n2);
                break;
            case '/':
                if(n2 == 0)
                    fprintf(fout, "\\ impossibile\n");
                fprintf(fout, "%c %.2f\n", op, n1 / n2);
                break;
            }

    fclose(fin);
    fclose(fout);
    return 0;
}