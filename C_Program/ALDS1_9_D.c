/*
ヒープソート
以下のように、ソートアルゴリズムはそれらの計算量や安定性など、様々な特徴を持ちます。

アルゴリズム	計算量
（最悪）	計算量
（平均）	安定性	メモリ
効率	テクニック	特徴
挿入ソート
ALDS1_1_A	O(
)	O(
)	〇	〇	挿入	整列されたデータに対して高速。
バブルソート
ALDS1_2_A	O(
)	O(
)	〇	〇	スワップ	
選択ソート
ALDS1_2_B	O(
)	O(
)	×	〇	スワップ	
シェルソート
ALDS1_2_D	O(
)	O(
)	×	〇	挿入	
マージソート
ALDS1_5_A	O(
)	O(
)	〇	×	分割統治	安定で高速。
入力の配列に加えてメモリが必要。
計数ソート
ALDS1_6_A	O(
)	O(
)	〇	×	バケット	安定で高速。
要素の値に制限がある。
クイックソート
ALDS1_6_B	O(
)	O(
)	×	△	分割統治	データの隔たりに対する対策を実装すれば、高速でメモリ使用量も少ない。対策がなければ時間・メモリともに計算量が悪化する。
ヒープソート
ALDS1_9_D（この問題）	O(
)	O(
)	×	〇	ヒープ構造	高速で、入力の配列以外にメモリが必要ない。
安定ではなく、ランダムアクセスが多く発生する。

ヒープソート（Heap Sort）はヒープのデータ構造に基づくソートで、入力配列内でソート処理を達成できる（メモリ効率のよい）、高速なソートアルゴリズムです。ヒープソートは、次のように実装することができます。

1  maxHeapify(A, i)
2      l = left(i)
3      r = right(i)
4      // select the node which has the maximum value
5      if l ≤ heapSize and A[l] > A[i]
6          largest = l
7      else 
8          largest = i
9      if r ≤ heapSize and A[r] > A[largest]
10         largest = r
11
12     if largest ≠ i　
13         swap A[i] and A[largest]
14         maxHeapify(A, largest) 
15
16 heapSort(A):
17     // buildMaxHeap
18     for i = N/2 downto 1:
19         maxHeapify(A, i)
20     // sort
21     heapSize ← N
22     while heapSize ≥ 2:
23         swap(A[1], A[heapSize])
24         heapSize--
25         maxHeapify(A, 1)
一方、ヒープソートでは、離れた要素が頻繁にスワップされ、連続でない要素へのランダムアクセスが多く発生してしまいます。

要素の数列
が与えられます。最大ヒープを満たし、ヒープソートを行ったときに疑似コード25行目のmaxHeapifyにおけるスワップ回数の総数が最大となるような数列
の順列を１つ出力してください。

入力
1行目に、数列の長さを表す整数 
 が与えられます。２行目に、
 個の整数が空白区切りで与えられます。

出力
条件を満たす数列を 1 行に出力してください。数列の連続する要素は１つの空白で区切って出力してください。

この問題では、１つの入力に対して複数の解答があります。条件を満たす出力は全て正解となります。

制約
 
 の要素 
の要素は全て異なる
入出力例
入力例1
8
1 2 3 5 9 12 15 23
出力例1
23 9 15 2 5 3 12 1
*/

#include <stdio.h>

int A[500000];
int N;

int left(int i) {
    return 2 * i;
}

int right(int i) {
    return 2 * i + 1;
}

void maxHeapify(int A[], int i, int heapSize) {
    int l = left(i);
    int r = right(i);
    int largest;
    
    if (l <= heapSize && A[l] > A[i]) {
        largest = l;
    } else {
        largest = i;
    }
    
    if (r <= heapSize && A[r] > A[largest]) {
        largest = r;
    }
    
    if (largest != i) {
        int temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;
        maxHeapify(A, largest, heapSize);
    }
}

void buildMaxHeap(int A[], int n) {
    for (int i = n / 2; i >= 1; i--) {
        maxHeapify(A, i, n);
    }
}

void heapSort(int A[], int n) {
    buildMaxHeap(A, n);
    int heapSize = n;
    while (heapSize >= 2) {
        int temp = A[1];
        A[1] = A[heapSize];
        A[heapSize] = temp;
        heapSize--;
        maxHeapify(A, 1, heapSize);
    }
}

int main(void) {
    scanf("%d", &N);
    
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
    }
    

    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            if (A[i] < A[j]) {
                int temp = A[i];
                A[i] = A[j];
                A[j] = temp;
            }
        }
    }
    

    buildMaxHeap(A, N);
    
    for (int i = 1; i <= N; i++) {
        if (i > 1) printf(" ");
        printf("%d", A[i]);
    }
    printf("\n");
    
    return 0;
}