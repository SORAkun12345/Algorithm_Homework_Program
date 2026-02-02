/*
1 insertionSort(A, N) // N個の要素を含む0-オリジンの配列A
2   for i が 1 から N-1 まで
3     v = A[i]
4     j = i - 1
5     while j >= 0 かつ A[j] > v
6       A[j+1] = A[j]
7       j--
8     A[j+1] = v

*/
#include <stdio.h>

void insertionSort(int A[], int N);
void printArray(int A[], int N);

int main(){
    int N;
    scanf("%d", &N);

    int A[N];

    for(int i = 0; i < N; i++){
        scanf("%d", &A[i]);
    }

    insertionSort(A, N);
}

void insertionSort(int A[], int N){
    printArray(A, N);
    for(int i = 1; i < N; i++){
        int v = A[i];
        int j = i - 1;
        while(j >= 0 && A[j] > v){
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = v;
        printArray(A, N);
    }
}

void printArray(int A[], int N){
    for(int i = 0; i < N; i++){
        if (i > 0) printf(" "); 
        printf("%d", A[i]);
    }
    printf("\n");
}