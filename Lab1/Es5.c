/*
 * Riccardo Rosin 284211
 * Lab 1 Es 5
*/
#include<stdio.h>

int main(void){
    char c;
    float n1,n2, r;

    printf("Insersci l'operazione: ");
    scanf("%c", &c);
    while(getchar() != '\n');

    printf("Insersci i due numeri: ");
    scanf("%f %f", &n1, &n2);
    switch(c){
        case '+':
            r = n1 + n2; 
            break;
        case '-':
            r = n1 - n2;
            break;
        case '*':
            r = n1 * n2;
            break;
        case '/':
            if(n2 == 0){
                printf("Non e' possibile dividere per 0");
                return 1;
            }
            r = n1 / n2;
            break;
    }
    printf("%f%c%f = %f", n1, c, n2, r);
    return 0;
}