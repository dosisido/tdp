#include<stdio.h>
#include<string.h>
#define maxWord 30
#define tabFormat 4

int addTxt(char s[]){
    int l = strlen(s);
    if(s[l-1] != 't' || s[l-2] != 'x' || s[l-3] != 't' || s[l-4] != '.'){
        if(l+5 > maxWord) return 0;
        s = strcat(s, ".txt");
    }
    return 1;
}

int main(void){
    char nameIn[maxWord], c;
    int space = 0, newLine = 1, i;
    FILE *fin;
    printf("Inserisci il nome del file: ");
    scanf("%s", nameIn);
    addTxt(nameIn);
    if ((fin = fopen(nameIn, "r")) == NULL){
        printf("Errore nell'apertura del file: \"nameIn\"");
        return 1;
    }
    
    printf("\n\n\n");

    while((c = getc(fin)) != EOF){
        if(newLine && c != ' '){
            for(i=0; i<space; i++) printf(" ");
            printf("\""); newLine = 0;
            for(i=0; i<space/tabFormat; i++) printf("\\t");
            space = 0;
        }
        switch(c){
            case '\\':
                printf("\\\\");
                break;
            case '\n':
                printf("\",\n");
                newLine = 1;
                break;
            case '"': case '$':
                printf("\\%c",c);
                break;
            case ' ':
                if(newLine) space++; else printf(" ");
                break;
            case '\t':
                space = tabFormat;
                break;
            default:
                printf("%c", c);
        }
    }
    if(!newLine) printf("\",");

    printf("\n\n\n");

    fclose(fin);
    return 0;
}