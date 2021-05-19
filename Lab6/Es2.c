/*
 * Riccardo Rosin 284211
 * Lab 6 Es 2
*/
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#define fileLoad "sequenze.txt"
#define fileIn "testo.txt"
#define maxSequenze 20
#define maxWorld 25
#define maxRow 200
#define maxOccorrenze 10

typedef struct t_occorrenze{
    int posizione;
    char word[maxWorld];
}s_occorenze;

typedef struct t_sequenze{
    char text[maxWorld];
    int counter;
    s_occorenze occorrenze[maxOccorrenze];
}s_sequenze;

int loadFile(s_sequenze seq[]){
    int r, i;
    FILE *fin;
    if ((fin = fopen(fileLoad, "r")) == NULL){
        printf("Errore nell'apertura del file: \"fileLoad\"");
        return -1;
    }
    
    if(fscanf(fin, " %d ", &r)!=1) return -1;
    for(i=0; i<maxRow && !feof(fin); i++){
        fscanf(fin, "%s", seq[i].text);
        seq[i].counter = 0;
    }

    fclose(fin);
    return r;
}

void printOccorrenze(s_occorenze occ[], int max){
    int i;
    for(i=0; i<max; i++){
        printf("\tOccorrenza: %d\n", i);
        printf("\t\tPosizione: %d\n", occ[i].posizione);
        printf("\t\tParola: %s\n", occ[i].word);
    }
}

void printSeq(s_sequenze seq[], int n){
    int i;
    for(i=0; i<n; i++){
        printf("%d:\n", i);
        printf("\tSequenza: %s\n", seq[i].text);
        printf("\tContatore: %d\n", seq[i].counter);
        printOccorrenze(seq[i].occorrenze, seq[i].counter);
        printf("\n");
    }
}

int isSubstring(char str1[], char str2[]){
    int i=0, j=0;
    for(i;i<strlen(str1);i++)
        if(tolower(str1[i])==tolower(str2[j])){
            j++;
            if(j == strlen(str2)) return 1;
        }else{
            i=i-j;
            j=0;
        }
    return 0;
}

/* int countSubstring(char str1[], char str2[]){
    int i=-1, count = 0;
    do{
        i = isSubstring(str1, str2, i++);
        if(i!=-1) count++;
    }while(i!=-1);
    return count;
} */

void readRow(FILE *fin, char row[]){
    fscanf(fin, "%s ", row);
    //fgets(row, 100, fin);
    /* int i=0;
    char c;
    while((c = fgetc(fin)) != '\n')
        if(isspace(c) && !isspace(row[i+1]) || isalnum(c)) row[i++] = c;
    row[i] = '\n'; */
}

void findSequenze(s_sequenze seq[], int n_seq){
    FILE *fin;
    if ((fin = fopen(fileIn, "r")) == NULL){
        printf("Errore nell'apertura del file: \"fileIn\"");
        return;
    }

    char row[maxWorld];
    int word=1, i, j;
    fscanf(fin, " ");
    while(!feof(fin)){
        readRow(fin, row);  //legge la parola
        
        //per ogni sequnza analizzo con parola
        for(i=0; i<n_seq; i++){
            printf("%s - %s\t", row, seq[i].text);
            if(isSubstring(row, seq[i].text) && seq[i].counter < maxOccorrenze){
                seq[i].occorrenze[seq[i].counter].posizione = word;
                strcpy(seq[i].occorrenze[seq[i].counter].word, row);
                printf("E' substring");
                seq[i].counter++;
            }
            printf("\n");
        }

        printf("\n");
        word++;
    }

    fclose(fin);
}

int main(int argc, char* argv){
    s_sequenze seq[maxSequenze];
    int n_seq = loadFile(seq);
    if(n_seq == -1) return -1;
    //printSeq(seq, n_seq);

    //printf("Analizzo occorrenze\n\n");
    findSequenze(seq, n_seq);

    printf("Stampo la struct\n");
    printSeq(seq, n_seq);

    

    return 0;
}