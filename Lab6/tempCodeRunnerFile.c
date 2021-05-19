//per ogni occorrenza di sequenza in parola
            for(j=0; j<count && j + seq[i].counter<=maxSequenze; j++){
                seq[i].occorrenze[j + seq[i].counter + 1].posizione = word;
                strcpy(seq[i].occorrenze[j + seq[i].counter + 1].word, row);
            }
            seq[i].counter = (seq[i].counter >= maxSequenze) ? maxSequenze : seq[i].counter + count;