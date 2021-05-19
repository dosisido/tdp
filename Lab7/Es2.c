#include<stdio.h>
#define max 100
#define fileIn "sort.txt"

typedef struct n_arr{
    int a[max];
}arr;

void printArr(arr *var, int n){
    int i;
    printf("[");
    for(i=0; i<n; i++) printf(" %d ", (*var).a[i]);
    printf("]\n");
}

void selSort(arr var, int n) {
    int i, j, l=0, r=n-1, min, scambi = 0, cicloEx = 0, cicloIn, iterazioni = 0;
    int temp;
    printf("selSort:\n");
    for (i = l; i < r; i++) {
        cicloEx++;
        cicloIn = 0;
        min = i;
        for (j = i+1; j <= r; j++){
            cicloIn++;
            if (var.a[j] < var.a[min])
                min = j;
        }
        printf("\tIterazione %d ex -> %d\n", cicloEx, cicloIn);
        iterazioni+=cicloEx;
        if (min != i) {
            scambi++;
            temp = var.a[i];
            var.a[i] = var.a[min];
            var.a[min] = temp;
        }
    }
    printf("Iterazioni totali ex: %d\n", cicloEx);
    printf("Numero di scambi: %d\n", scambi);
    printf("Iterazioni totali: %d\n", iterazioni);
    printf("\n");
    //printArr(&var, n);
    return;
}

void inSort(arr var, int n) {
    int i, j, l=0, r=n-1, x, scambi = 0, cicloEx = 0, cicloIn, iterazioni = 0;
    printf("inSort:\n");
    for (i = l+1; i <= r; i++) {
        cicloEx++;
        cicloIn=0;
        x = var.a[i];
        j = i - 1;
        while (j >= l && x < var.a[j]){
            scambi++;
            cicloIn++;
            var.a[j+1] = var.a[j];
            j--;
        }
        iterazioni+=cicloIn;
        printf("\tIterazione %d ex -> %d\n", cicloEx, cicloIn);
        var.a[j+1] = x;
    }
    printf("Iterazioni totali ex: %d\n", cicloEx);
    printf("Numero di scambi: %d\n", scambi);
    printf("Iterazioni totali: %d\n", iterazioni);
    printf("\n");
    //printArr(&var, n);
}

void shellSort(arr var, int n) {
    int i, j, x, l=0, r=n-1, h=1, scambi = 0, cicloEx = 0, cicloIn, iterazioni = 0;
    printf("shellSort:\n");
    while (h < n/3){
        iterazioni++;
        h = 3*h+1;
    }    
    while(h >= 1) {
        cicloEx++;cicloIn=0;
        for (i = l+h; i <= r; i++) {
            cicloIn++;
            j = i;
            x = var.a[i];
            while(j >= l+h && x < var.a[j-h]) {
                scambi++;
                iterazioni++;
                var.a[j] = var.a[j-h];
                j-=h;
            }
            var.a[j] = x;
        }
        printf("\tIterazione %d ex -> %d\n", cicloEx, cicloIn);
        var.a[j+1] = x;
        h = h/3;
    }
    printf("Iterazioni totali ex: %d\n", cicloEx);
    printf("Numero di scambi: %d\n", scambi);
    printf("Iterazioni totali: %d\n", iterazioni);
    printf("\n");
    //printArr(&var, n);
}

int main(int argc, char* argv){
    arr var;
    unsigned int i, j, r, l;
    FILE *fin;
    if ((fin = fopen(fileIn, "r")) == NULL){
        printf("Errore nell'apertura del file: \"fileIn\"");
        return 1;
    }
    if(fscanf(fin, " %u ", &r)!=1) return -1;
    for(i=0; i<r && !feof(fin); i++){
        fscanf(fin, " %u ", &l);
        for(j=0; j<l; j++)
            fscanf(fin, " %d ", &var.a[j]);
        
        selSort(var, l);
        inSort(var, l);
        shellSort(var, l);
        
        printf("\n\n\n");
    }
    fclose(fin);
    return 0;
}