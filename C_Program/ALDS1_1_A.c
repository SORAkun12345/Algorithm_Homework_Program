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

/*
テスト用の解説メモ

入出力の流れ
- 入力: N の後に N 個の整数
- 出力: ソートの各ステップごとに配列全体を1行出力

出力タイミング
1) 初期配列を1行出力
2) i=1..N-1 の各挿入操作後に1行出力
    → 合計 N 行が出力される

手計算確認例
入力
6
5 2 4 6 1 3

出力
5 2 4 6 1 3
2 5 4 6 1 3
2 4 5 6 1 3
2 4 5 6 1 3
1 2 4 5 6 3
1 2 3 4 5 6

ポイント
- 挿入対象 v を左へずらし、v より大きい要素を右に1つずつ移動
- 既に整列済みの部分配列 [0..i-1] を保つのが目的
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