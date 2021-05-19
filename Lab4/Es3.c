/*
 * Riccardo Rosin 284211
 * Lab 4 Es 3
*/
#include<stdio.h>
#include<string.h>
#define MAX 20

int addTxt(char s[]){    // return is 0 if string not long enough, else 1
    int l = strlen(s);
    if(s[l-1] != 't' || s[l-2] != 'x' || s[l-3] != 't' || s[l-4] != '.'){
        if(l+5 > MAX) return 0;
        s = strcat(s, ".txt");
    }
    return 1;
}

void stampa_matrice(int M[][MAX], int r, int c){
    int i, j;
    for(i=0; i<r; i++){
        for(j=0; j<c; j++)
            printf("%d	", M[i][j]);
        printf("\n");
    }
}

int insMat(int mat[][MAX], int *nr, int *nc){
    int a, b;
    char str[MAX+1];
    FILE *fin;

    printf("Inserisci il nome del file di input: ");
    scanf("%s", str);
    addTxt(str);
    if ((fin = fopen(str, "r")) == NULL){
        printf("Errore nell'apertura del file di input");
        return -1;
    }

    if(fscanf(fin, " %d %d ", nr, nc) != 2) return -1;

    //inserimento matrice
    for(a = 0; a<*nr; a++)
        for(b = 0; b<*nc; b++)
            if(fscanf(fin, "%d ", &mat[a][b]) != 1) return -1;
    
    stampa_matrice(mat, *nr, *nc);
    
    fclose(fin);
}

int min(int a, int b){
    return (a < b)? a : b;
}

int printSubMat(int mat[][MAX], int startx, int starty, int dim){
    unsigned int c, d, tmpMax = 0;
    for(c = startx; c<startx+dim; c++){
        for(d = starty; d<starty+dim; d++){
            printf("%d ", mat[c][d]);
            tmpMax += mat[c][d];
        }
        printf("\n");
    }
    return tmpMax;
}

void printAllSub(int mat[][MAX], int nr, int nc, int dim){
    int max, tmpMax;
    unsigned int a, b, c, d, maxSubMat[2];

    tmpMax = max = 0;
    for(a = 0; a<=nr-dim; a++)
        for(b = 0; b<=nc-dim; b++){
            //stampa le sottomatrici
            tmpMax = printSubMat(mat, a, b, dim);

            if(tmpMax>max){
                max = tmpMax;
                maxSubMat[0] = a;
                maxSubMat[1] = b;
            }
            tmpMax = 0;
            printf("\n");
        }

    printf("La sottomatrice con somma degli elementi massima (%d) e':\n", max);
    for(a = maxSubMat[0]; a<maxSubMat[0]+dim; a++){
        for(b = maxSubMat[1]; b<maxSubMat[1]+dim; b++)
            printf("%d ", mat[a][b]);
        printf("\n");
    }
}

int main(void){
    int mat[MAX][MAX];
    unsigned int nr, nc, dim;
    
    if(insMat(mat, &nr, &nc) == -1) return -1;

    //richeista dimensione
    printf("\n\nInserisco la dimensione <= a %d: ", min(nr, nc));
    scanf("%d", &dim);
    while(dim > 0 && dim <= min(nr, nc)){
        printAllSub(mat, nr, nc, dim);

        printf("\n\nInserisco la dimensione <= a %d: ", min(nr, nc));
        scanf("%d", &dim);
    } 
    
    return 0;
}