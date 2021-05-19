/*
 * Riccardo Rosin 284211
 * Lab 6 Es 1
*/
#include<stdio.h>
#include<string.h>
#define fileIn "log.txt"
#define maxRow 1000
#define maxWord 30

typedef struct data{
    char id[maxWord+1];
    char start[maxWord+1];
    char end[maxWord+1];
    char date[maxWord+1];
    char hourI[maxWord+1];
    char hourF[maxWord+1];
    int delay;
}data;

enum comando_e {r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine};
typedef enum bool_e{false, true} bool;

int insertLog(data log[]){
    int n, i;
    char tmp[maxWord] = {0};
    FILE *fin;
    if ((fin = fopen(fileIn, "r")) == NULL){
        printf("Errore nell'apertura del file: \"fileIn\"");
        return -1;
    }
    
    if(fscanf(fin, " %d ", &n)!=1) return -1;
    for(i=0; i<maxRow && !feof(fin); i++){
        fscanf(fin, "%s %s %s %s %s %s %d ", 
            log[i].id, 
            log[i].start, 
            log[i].end, 
            log[i].date, 
            log[i].hourI, 
            log[i].hourF, 
            &log[i].delay
        );
    }
    //if(i!=n) return -1;
    fclose(fin);
    return n;
}

void print_log_row(data log[], int i){
    printf("%d\n", i);
    printf("\tid: %s\n", log[i].id);
    printf("\tinizio: %s\n", log[i].start);
    printf("\tfine: %s\n", log[i].end);
    printf("\tdata: %s\n", log[i].date);
    printf("\tora inizio: %s\n", log[i].hourI);
    printf("\tora fine: %s\n", log[i].hourF);
    printf("\tritardo: %d\n\n", log[i].delay);
}

void print_log(data log[], int n){
    for(int i=0; i<n; i++) print_log_row(log, i);
}

int date_cmp(char date1[], char date2[]){
    /*   
     *   1 se 1 > 2
     *   0 se 1 = 2
     *  -1 se 1 < 2
     */
    int n1, n2;
    sscanf(date1, "%d", &n1);
    sscanf(date2, "%d", &n2);
    if(n1>n2) return 1;
    else if(n2>n1) return -1;
    sscanf(date1, "%*d/%d", &n1);
    sscanf(date2, "%*d/%d", &n2);
    if(n1>n2) return 1;
    else if(n2>n1) return -1;
    sscanf(date1, "%*d/%*d/%d", &n1);
    sscanf(date2, "%*d/%*d/%d", &n2);
    if(n1>n2) return 1;
    else if(n2>n1) return -1;
    return 0;
}

int get_cmd(char par1[], char par2[]){
    char str[maxWord];
    scanf("%s", str);
    if(strcmp("date", str) == 0){scanf("%s%s", par1, par2); return r_date;}
    if(strcmp("partenza", str) == 0){scanf("%s", par1); return r_partenza;}
    if(strcmp("capolinea", str) == 0){scanf("%s", par1); return r_capolinea;}
    if(strcmp("ritardo", str) == 0){scanf("%s%s", par1, par2); return r_ritardo;}
    if(strcmp("ritardo_tot", str) == 0){scanf("%s", par1); return r_ritardo_tot;}
    if(strcmp("fine", str) == 0) return r_fine;
    return -1;
}

int options(data log[], int lenLog, int comando, char par1[], char par2[]){
    int i;
    switch(comando){
        case r_date:
            for(i=0; i<lenLog; i++)
                if(date_cmp(par1, log[i].date)<=0 || date_cmp(par2, log[i].date)>=0)
                    print_log_row(log, i);
            break;
        case r_partenza:
            for(i=0; i<lenLog; i++)
                if(strcmp(par1, log[i].start)==0)
                    print_log_row(log, i);
            break;
        case r_capolinea:
            for(i=0; i<lenLog; i++)
                if(strcmp(par1, log[i].end)==0)
                    print_log_row(log, i);
            break;
        case r_ritardo:
            for(i=0; i<lenLog; i++)
                if((date_cmp(par1, log[i].date)<=0 || date_cmp(par2, log[i].date)>=0) && log[i].delay!=0)
                    print_log_row(log, i);
            break;
        case r_ritardo_tot:
            comando = 0;
            for(i=0; i<lenLog; i++)
                if(strcmp(par1, log[i].id)==0)
                    //usato per non dover creare un'altra variabile
                    comando+= log[i].delay;
            printf("Il ritardo totale dal mezzo \"%s\" e' di %d\n", par1, comando); 
            break;
        case r_fine:
            return true;
            break;
        default:
            printf("Comando non riconosciuto\n");
    }
    return false;
}

int main(int argc, char* argv){
    data log[maxRow];
    int lenLog = insertLog(log);
    if(lenLog==-1) return -1;

    printf("Inizio programma:\n");
    int comando;
    bool fine = false;
    char par1[maxWord], par2[maxWord];

    while(!fine){
        printf(">> ");
        comando = get_cmd(par1, par2);
        fflush(stdin);
        fine = options(log, lenLog, comando, par1, par2);
    }
    return 0;
}