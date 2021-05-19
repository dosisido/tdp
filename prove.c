#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<windows.h>
#define N 100000

void ShellSort(int A[], int n) {
    int i, j, x, l=0, r=N-1, h=1;
    while (h < n/3) h = 3*h+1;
    while(h >= 1) {
        for (i = l+h; i <= r; i++) {
            j = i;
            x = A[i];
            while(j >= l+h && x < A[j-h]) {
                A[j] = A[j-h];
                j-=h;
            }
            A[j] = x;
        }
        h = h/3;
    }
}
void quicksort(int a[],int primo,int ultimo){
    int i, j, pivot, temp;
    /*  
        pivot -- inizialmente il pivot è il primo elemento
        primo e ultimo sono le due variabili che servono per scorrere l'array
    */
    if(primo<ultimo){
        pivot=primo;
        i=primo;
        j=ultimo;     
        
        while(i<j){
            while(a[i]<=a[pivot]&&i<ultimo) i++;
            while(a[j]>a[pivot]) j--;
            if(i<j){   
                temp=a[i];
                a[i]=a[j];
                a[j]=temp;
            }
        }

        temp=a[pivot];
        a[pivot]=a[j];
        a[j]=temp;
        quicksort(a,primo,j-1);
        quicksort(a,j+1,ultimo);
    }
}


void startArray(int a[], int b[], int n){
    int i;
	srand(time(0)); 
    for(i=0;i<n;i++){
	   a[i] = b[i] =1+rand()%100; //numeri casuali tra 1 e 100
	   //printf("%d\t", a[i]);
   	}
}

void printArray(int a[], int n){
    int i;
    for(i=0;i<n;i++){
        printf("%d\t", a[i]);
    }
}

int main(int argc, char* argv){
    int a[N], b[N];
	int i, time;
    startArray(a, b, N);
    //printArray(a, N);
    
    time = timeGetTime;
    quicksort(a, 0, N-1);
    time = timeGetTime - time;
    printf("Quicksort: %d", time);


    time = timeGetTime;
    ShellSort(b, N);
    time = timeGetTime - time;
    printf("Quicksort: %d", time);
    
    
    
    printf("\n\n\n");
    //printArray(a, N);


    return 0;
}