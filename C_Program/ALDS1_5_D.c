/*
反転数

数列 
 について、
 かつ 
 である組 
 の個数を反転数と言います。反転数は次のバブルソートの交換回数と等しくなります。

bubbleSort(A)
  cnt = 0 // 反転数
  for i = 0 to A.length-1
    for j = A.length-1 downto i+1
      if A[j] < A[j-1]
	swap(A[j], A[j-1])
	cnt++

  return cnt
数列 
 が与えられるので、
 の反転数を求めてください。上の疑似コードのアルゴリズムをそのまま実装するとTime Limit Exceeded になることに注意してください。

入力
１行目に数列 
 の長さ 
 が与えられます。２行目に 
 が空白区切りで与えられます。

出力
反転数を１行に出力してください。

制約
 はすべて異なる値である
入力例 1
5
3 5 2 1 4
出力例 1
6
入力例 2
3
3 1 2
出力例 2
2
*/

/*
反転数をマージソートで効率的に計算する解説

【反転数とは】
i < j かつ A[i] > A[j] である組(i, j)の個数
→ ソートに必要な交換回数と等しい

【なぜバブルソートではTLEか】
バブルソートのアルゴリズム:
  for i = 0 to n-1
    for j = n-1 downto i+1
      if A[j] < A[j-1]
        swap

時間計算量: O(n²) 
n=100000の場合、約10^10回の操作で間に合わない

【マージソートで効率化】
マージソートはO(n log n)で、その過程で反転数を計算できる

■分割フェーズで反転数をカウント:
マージ時、左配列の要素が右配列の要素より大きい場合、
左配列の残り全ての要素は反転を形成

■具体例: [3, 5, 2, 1, 4]
分割: [3, 5] [2, 1, 4]

[3, 5] → 反転数 1 (3>5でない, 5>3で反転1)
[2, 1, 4] → [2, 1] [4]
  [2, 1] → 反転数 1 (2>1)
  [4] → 反転数 0
  マージ [2, 1] と [4]: 反転数 0
  結果 [1, 2, 4]

マージ [3, 5] と [1, 2, 4]:
3 vs 1: 1 < 3 → 反転数 +2 (3,5)
2 vs 3: 2 < 3 → 反転数 +1 (3)
...

【マージでの反転数計算】
左配列のインデックスi、右配列のインデックスjで比較:
if (L[i] > R[j]) → 反転数 += (n1 - i)
  理由: i以降の左配列すべての要素がR[j]より大きい

【具体例】
[3, 5] と [2]
3 > 2: 反転数 += (2-0) = 2
*/

#include <stdio.h>
#include <string.h>

#define MAX_N 500000
#define INFTY 2000000001

int A[MAX_N];
int L[MAX_N / 2 + 1];
int R[MAX_N / 2 + 1];
long long inv_count = 0;

// マージしながら反転数をカウント
void merge(int left, int mid, int right) {
    int n1 = mid - left;      // 左側のサイズ
    int n2 = right - mid;     // 右側のサイズ
    
    // 左側をL配列にコピー
    for (int i = 0; i < n1; i++) {
        L[i] = A[left + i];
    }
    
    // 右側をR配列にコピー
    for (int i = 0; i < n2; i++) {
        R[i] = A[mid + i];
    }
    
    // 番兵を追加
    L[n1] = INFTY;
    R[n2] = INFTY;
    
    int i = 0;  // L配列のインデックス
    int j = 0;  // R配列のインデックス
    
    // マージ
    for (int k = left; k < right; k++) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
            
            // 反転数を追加
            // L[i]以降の要素がすべてR[j]より大きいので、
            // n1-i個の反転が存在する
            inv_count += (long long)(n1 - i);
        }
    }
}

// マージソート（反転数を記録）
void mergeSort(int left, int right) {
    if (left + 1 < right) {
        int mid = (left + right) / 2;
        
        // 左側をソート
        mergeSort(left, mid);
        
        // 右側をソート
        mergeSort(mid, right);
        
        // ソート済みの左右をマージ（反転数をカウント）
        merge(left, mid, right);
    }
}

int main(void) {
    int n;
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }
    
    // マージソート実行（反転数をカウント）
    mergeSort(0, n);
    
    // 反転数を出力
    printf("%lld\n", inv_count);
    
    return 0;
}
