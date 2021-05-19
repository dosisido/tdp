#include<stdio.h>
#define fileIn "matrix.txt"
#define maxMat 50

typedef struct n_output{
    short int x, y, h, l, a;
} out;

enum caselle {Bianco, Nero};

int initMatrice(unsigned int A[][maxMat], unsigned int *r, unsigned int *c){
    int i, j;
    FILE *fin;
    if ((fin = fopen(fileIn, "r")) == NULL){
        printf("Errore nell'apertura del file di input");
        return -1;
    }
    if(fscanf(fin, " %u %u ", r, c)!=2) return -1;
    for(i=0; i<*r && !feof(fin); i++)
        for(j=0; j<*c; j++)
            fscanf(fin, "%u ", &A[i][j]);
    if(i!=*r) return -1;
    fclose(fin);
}

void stampa_matrice(unsigned int M[][maxMat], unsigned int r, unsigned int c){
    int i, j;
    for(i=0; i<r; i++){
        for(j=0; j<c; j++)
            printf("%u	", M[i][j]);
        printf("\n");
    }
}

void resetStruct(out *s){
    (*s).x = (*s).y = (*s).h = (*s).l = (*s).a = 0;
}

void setStruct(out *s, unsigned int x, unsigned int y, unsigned int h, unsigned int l, unsigned int a){
    (*s).x = x;
    (*s).y = y;
    (*s).h = h;
    (*s).l = l;
    (*s).a = a;
}

void HLA(unsigned int mat[][maxMat], unsigned int r, unsigned int c, unsigned int i, unsigned int j,  out *maxH, out *maxL, out *maxA){
    unsigned int ti, tj, h, l, a;
    for(ti=i; ti<r && mat[ti][j]!=Bianco; ti++); ti--;
    for(tj=j; tj<c && mat[ti][tj]!=Bianco; tj++); tj--;
    h = ti-i+1;
    l = tj-j+1;
    a = h*l;

    if(h>(*maxH).h) setStruct(maxH, i, j, h, l, a);
    if(l>(*maxL).l) setStruct(maxL, i, j, h, l, a);
    if(a>(*maxA).a) setStruct(maxA, i, j, h, l, a);
    
    printf("Inizio: %u, %u\n", i, j);
    printf("Fine: %u, %u\n", ti, tj);
    printf("Altezza: %u\n", h);
    printf("Largezza: %u\n", l);
    printf("Area: %u\n", a);
    printf("\n"); 
}

void find(unsigned int mat[][maxMat], unsigned int r, unsigned int c){
    unsigned int i, j;
    out maxH, maxL, maxA;
    resetStruct(&maxH);resetStruct(&maxL);resetStruct(&maxA);
    for(i=0; i<r; i++)
        for(j=0; j<c; j++){
            if(mat[i][j]==Nero  &&  (i==0 || mat[i-1][j]==Bianco)  &&  (j==0 || mat[i][j-1]==Bianco)) HLA(mat, r, c++, i, j, &maxH, &maxL, &maxA);
        }
    printf("Max altezza: estremo=(%u,%u), altezza=%u, larghezza=%u, area=%u\n", maxH.x, maxH.y, maxH.h, maxH.l, maxH.a);
    printf("Max largezza: estremo=(%u,%u), altezza=%u, larghezza=%u, area=%u\n", maxL.x, maxL.y, maxL.h, maxL.l, maxL.a);
    printf("Max area: estremo=(%u,%u), altezza=%u, larghezza=%u, area=%u\n", maxA.x, maxA.y, maxA.h, maxA.l, maxA.a);
}

int main(int argc, char* argv){
    unsigned int mat[maxMat][maxMat], nr, nc;
    if(initMatrice(mat, &nr, &nc) == -1) return -1;
    //printf("%d, %d", nr, nc);
    //stampa_matrice(mat, nr, nc);
    find(mat, nr, nc);
    return 0;
}