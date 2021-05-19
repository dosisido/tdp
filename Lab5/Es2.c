/*
 * Riccardo Rosin 284211
 * Lab 5 Es 2
 */
#include<stdio.h>
#include<string.h>
#define inFile "sorgente.txt"
#define dictFile "dizionario.txt"
#define outFile "ricodificato.txt"
#define max 30
#define maxXRow 200

typedef struct{
    char id[max+1], str[max+1];
} diz;  

int loadDict(diz elenco[]){
    int row, i;
    FILE *dict;
    if ((dict = fopen(dictFile, "r")) == NULL){
        printf("Errore nell'apertura del file dizionario");
        return -1;
    }
    //load dict
    if(fscanf(dict, " %d ", &row)!=1) return 2;
    for(i=0; i<row && !feof(dict); i++)
        fscanf(dict, "%s %s ", elenco[i].id, elenco[i].str);
    if(i!=row) return -1;

    fclose(dict);
    return row;
}

void loadRow(FILE *fin, char row[]){
    int i;
    for(i=0; i<maxXRow || row[i-1]=='\n'; i++){
        fscanf(fin, "%c", &row[i]);
    }
    row[i-1] = '\0';
}

int isSubEqual(char a[], char b[], int car){
    int i;
    for(i=0; i<car; i++){
        if(a[i]!=b[i]) return 0;
    }
    return 1;
}

//restituisce il primo indice dell'elemento che ha il carattere c in posizione car e con la parte precedente nell'indice pos in comunue
int findFirstIndInDiz(diz elenco[], int r, char c, int pos, int car){
    for(int i = 0; i<r; i++)
        if(elenco[i].str[car] == c && isSubEqual(elenco[i].str, elenco[pos].str, car))    //il carattere attuale corrisponde
            return i;
    return -1;
}

void codifica(FILE *fin, FILE *fout, diz elenco[], int r){
    //load row
    unsigned int i, j, car, pos;
    char row[maxXRow+1];
    while (!feof(fin)){
        loadRow(fin, row);
        car = pos = 0;
        for(i=0; i<strlen(row); i++){
            //printf("i:%d, car: %d, pos: %d, char: %c\n", i, car, pos, row[i]);
            pos = findFirstIndInDiz(elenco, r, row[i], pos, car);
            if(pos!=-1){
                car++;
                if(strlen(elenco[pos].str) == car){
                    //stampa la parola perché hai trovato l'occorrenza
                    fprintf(fout, "%s", elenco[pos].id);
                    car = pos = 0;
                }
            }else{
                i=i-car;
                car = pos = 0;
                fprintf(fout, "%c", row[i]);
            }
        }
        fprintf(fout, "\n");
    }
}

int main(void){
    unsigned int row, i;
    diz elenco[max];
    FILE *fin, *dict, *fout;
    if ((fin = fopen(inFile, "r")) == NULL){
        printf("Errore nell'apertura del file di input");
        return -1;
    }
    if ((fout = fopen(outFile, "w")) == NULL){
        printf("Errore nell'apertura del file di output");
        return -1;
    }

    row = loadDict(elenco);
    if(row==-1) return -1;

    //load row
    codifica(fin, fout, elenco, row);
    printf("File ricodificato");

    fclose(fin);fclose(fout);
    return 0;
}