/*
マージソート
マージソート（Merge Sort）は分割統治法に基づく高速なアルゴリズムで、次のように実装することができます。

merge(A, left, mid, right)
  n1 = mid - left;
  n2 = right - mid;
  L[0...n1], R[0...n2] を生成
  for i = 0 to n1-1
    L[i] = A[left + i]
  for i = 0 to n2-1
    R[i] = A[mid + i]
  L[n1] = INFTY
  R[n2] = INFTY
  i = 0
  j = 0
  for k = left to right-1
    if L[i] <= R[j]
      A[k] = L[i]
      i = i + 1
    else 
      A[k] = R[j]
      j = j + 1

mergeSort(A, left, right)
  if left+1 < right
    mid = (left + right)/2;
    mergeSort(A, left, mid)
    mergeSort(A, mid, right)
    merge(A, left, mid, right)
 個の整数を含む数列 
 を上の疑似コードに従ったマージソートで昇順に整列するプログラムを作成してください。また、mergeにおける比較回数の総数を報告してください。

入力
１行目に 
、２行目に 
 を表す 
 個の整数が与えられます。

出力
１行目に整列済みの数列 
 を出力してください。数列の隣り合う要素は１つの空白で区切ってください。２行目に比較回数を出力してください。

制約
の要素
入力例 1
10
8 5 9 2 6 3 7 1 10 4
出力例 1
1 2 3 4 5 6 7 8 9 10
34
*/

/*
マージソートの解説

【マージソートとは】
分割統治法に基づく高速ソートアルゴリズム
時間計算量: O(n log n) - 最悪の場合でも保証される
メモリ効率: O(n) - 補助配列が必要

【アルゴリズムの流れ】
1. 配列を左右に分割（分割フェーズ）
2. 各半分を再帰的にソート
3. ソート済みの両配列をマージ（併合フェーズ）

【具体例】[8, 5, 9, 2, 6, 3, 7, 1]

■分割フェーズ:
[8, 5, 9, 2, 6, 3, 7, 1]
  ↓分割
[8, 5, 9, 2] [6, 3, 7, 1]
  ↓分割
[8, 5] [9, 2] [6, 3] [7, 1]
  ↓分割
[8] [5] [9] [2] [6] [3] [7] [1]

■マージフェーズ（ボトムアップ）:
[8] [5] → [5, 8]
[9] [2] → [2, 9]
[6] [3] → [3, 6]
[7] [1] → [1, 7]
  ↓マージ
[5, 8] [2, 9] → [2, 5, 8, 9]
[3, 6] [1, 7] → [1, 3, 6, 7]
  ↓マージ
[2, 5, 8, 9] [1, 3, 6, 7] → [1, 2, 3, 5, 6, 7, 8, 9]

【マージ処理のポイント】
1. 左右の配列に番兵（INFTY）を追加
2. 両配列の先頭を比較
3. より小さい方を結果配列に追加
4. すべての要素が処理されるまで繰り返す

【なぜO(n log n)か】
- 分割の深さ: log n
- 各レベルでのマージ処理: 全体でO(n)
- 合計: O(n × log n)

【比較回数の計算例】
n=10の場合、マージソートの比較回数は約n log n ≈ 33〜34回
（実際には若干異なる可能性がある）
*/

#include <stdio.h>
#include <string.h>

#define INFTY 2000000000
#define MAX_N 500000

int A[MAX_N];
int L[MAX_N / 2 + 1];
int R[MAX_N / 2 + 1];
long long compare_count = 0;

// leftからmid-1とmidからright-1の2つのソート済み配列をマージ
void merge(int left, int mid, int right) {
    int n1 = mid - left;     // 左側のサイズ
    int n2 = right - mid;    // 右側のサイズ
    
    // 左側をL配列にコピー
    for (int i = 0; i < n1; i++) {
        L[i] = A[left + i];
    }
    
    // 右側をR配列にコピー
    for (int i = 0; i < n2; i++) {
        R[i] = A[mid + i];
    }
    
    // 番兵を追加（これにより範囲チェックが不要になる）
    L[n1] = INFTY;
    R[n2] = INFTY;
    
    int i = 0;  // L配列のインデックス
    int j = 0;  // R配列のインデックス
    
    // 2つのソート済み配列をマージ
    for (int k = left; k < right; k++) {
        compare_count++;  // 比較1回を記録
        
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
    }
}

// マージソート本体
void mergeSort(int left, int right) {
    // 要素が2個以上ある場合のみ分割
    if (left + 1 < right) {
        int mid = (left + right) / 2;
        
        // 左側をソート
        mergeSort(left, mid);
        
        // 右側をソート
        mergeSort(mid, right);
        
        // ソート済みの左右をマージ
        merge(left, mid, right);
    }
}

int main(void) {
    int n;
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }
    
    // マージソート実行
    mergeSort(0, n);
    
    // ソート結果の出力
    for (int i = 0; i < n; i++) {
        if (i > 0) printf(" ");
        printf("%d", A[i]);
    }
    printf("\n");
    
    // 比較回数の出力
    printf("%lld\n", compare_count);
    
    return 0;
}
