/*
 * Riccardo Rosin 284211
 * Lab 5 Es 1
*/
#include<stdio.h>
#include<string.h>
#define max 20

int addTxt(char s[]){    // return is 0 if string not long enough, else 1
    int l = strlen(s);
    if(s[l-1] != 't' || s[l-2] != 'x' || s[l-3] != 't' || s[l-4] != '.'){
        if(l+5 > max) return 0;
        s = strcat(s, ".txt");
    }
    return 1;
}

void stampa_matrice(int M[][max], int r, int c){
    int i, j;
    for(i=0; i<r; i++){
        for(j=0; j<c; j++)
            printf("%d\t", M[i][j]);
        printf("\n");
    }
}

int max_ind(int M[][max], int r){
    int i, indMax=0;
    for(i=1; i< r; i++)
        if(M[i][0] > M[indMax][0])
            indMax=i;
    return indMax;
}

int main(void){
    int A[max][max], r, c;
    unsigned int i, j;
    char str[max];
    
    printf("Inserisci il nome del file di input: "); scanf("%s", str);
    addTxt(str);
    
    FILE *fin;
    if ((fin = fopen(str, "r")) == NULL){
        printf("Errore nell'apertura del file di input");
        return 1;
    }
    
    if(fscanf(fin, " %d %d ", &r, &c)!=2) return 2;
    //printf("%d - %d\n", r, c);
    for(i=0; i<r && !feof(fin); i++)
        for(j=0; j<c; j++)
            fscanf(fin, "%d ", &A[i][j]);
    if(i!=r) return 3;
    fclose(fin);
    //iserita la matrice

    stampa_matrice(A, r, c);

    printf("Giornata 1 in cima alla classifica: %d\n", max_ind(A, r));
    for(j=1; j<c; j++){
        for(i=0; i<r; i++) A[i][0]+=A[i][j];
        //stampa_matrice(A, r, c);
        printf("Giornata %d in cima alla classifica: %d\n", j+1, max_ind(A, r));
    }

    return 0;
}