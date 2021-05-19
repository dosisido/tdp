#include<stdio.h>
#define pi 3.1415
//stdin stdout

int main(void){
    char c;
    float n;
    printf("Inserisci Q per quadrato e C per cerchio: ");
    c = getchar();
    getchar();
    switch(c){
        case 'q':
        case 'Q':
            printf("Inserisci D per diagonale e L per lato: ");
            c = getchar();
            getchar();
            printf("Inserisci il valore: ");
            scanf("%f", &n);
            switch(c){
                case 'd':
                case 'D':
                    n = n * n /2;
                    break;
                case 'l':
                case 'L':
                    n = n * n;
                    break;
            }
            printf("L'area del quadrato vale %f", n);
            break;
        case 'c':
        case 'C':
            printf("Inserisci D per diametro e R per raggio: ");
            c = getchar();
            getchar();
            printf("Inserisci il valore: ");
            scanf("%f", &n);
            switch(c){
                case 'd':
                case 'D':
                    n = (pi * n * n)/4;
                    break;
                case 'l':
                case 'L':
                    n = pi * n * n;
                    
                    break;
            }
            printf("L'area del cerchio vale %f", n);
            break;
        
    }
    return 0;
}