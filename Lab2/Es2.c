/*
 * Riccardo Rosin 284211
 * Lab 2 Es 2
*/      
#include<stdio.h>
#define n1 0
#define n2 1
#define segno 0 //0 per '+' 1 per '*'

int main(void){
    unsigned int a = n1,b = n2, n, counter;
    printf("Inserisci quanti nuomeri visualizzare della serie di fibonacci: ");
    scanf("%d", &n);

    if(n > 1) printf("%d", a);
    if(n > 2) printf("\t%d", b);
    for(counter = 2; counter < n; counter++){
        for(counter = 2; counter < n; counter++){
            printf("\t%d", (a = (segno) ? a*b : a+b));
            a = b + a - (b=a);
        }
    }
    return 0;
}