/*
 * Riccardo Rosin 284211
 * Lab 2 Es 1
*/
#include<stdio.h>

int eulero(unsigned int a,unsigned int b){
    if(a*b==0) return (a==0) ? b : a;
    return (a>b) ? eulero(a%b, b) : eulero(a, b%a);
}

int main(void){
    unsigned int a, b;
    printf("Inserisci due numeri interi positivi: ");
    scanf(" %d %d", &a, &b);
    if(a<=0 || b<=0){printf("I numeri devono essere interi positivi"); return 1;}
    printf("%d", eulero(a,b));
    return 0;
}