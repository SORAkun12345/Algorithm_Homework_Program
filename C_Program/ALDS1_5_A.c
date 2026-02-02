/*
総当たり
長さ 
 の数列 
 と整数 
 に対して、
 の要素の中のいくつかの要素を足しあわせて 
 が作れるかどうかを判定するプログラムを作成してください。
 の各要素は１度だけ使うことができます。

数列 
 が与えられたうえで、質問として 
 個の 
 が与えれるので、それぞれについて "yes" または "no" と出力してください。

入力
１行目に 
、２行目に 
 を表す 
 個の整数、３行目に 
、４行目に 
 個の整数 
が与えられます。

出力
各質問について 
 の要素を足しあわせて 
 を作ることができれば yes と、できなければ no と出力してください。

制約
の要素
入力例 1
5
1 5 7 10 21
4
2 4 17 8
出力例 1
no
no
yes
yes
*/

/*
部分集合の和問題（動的計画法）の解説

【問題の本質】
配列Aの要素を0個以上使用して、各質問の数値を作れるかどうか判定
→ 「どの値が作れるか」を事前に計算する動的計画法

【アルゴリズムの仕組み】
1. possibleSums配列を用意（作れる値を記録）
2. possibleSums = [0]（何も足さない）からスタート
3. 配列Aの各要素について、現在作れる値に足した値も追加
4. 各質問について、possibleSumsに存在するか確認

【具体例】A = [1, 5, 7], 質問 = [1, 6, 8]
初期: possibleSums = [0]

i=0, A[0]=1:
  既存の値 [0] に1を足す → [1]
  possibleSums = [0, 1]

i=1, A[1]=5:
  既存の値 [0, 1] に5を足す → [5, 6]
  possibleSums = [0, 1, 5, 6]

i=2, A[2]=7:
  既存の値 [0, 1, 5, 6] に7を足す → [7, 8, 12, 13]
  possibleSums = [0, 1, 5, 6, 7, 8, 12, 13]

質問: 1 → possibleSumsに1がある → yes
質問: 6 → possibleSumsに6がある → yes
質問: 8 → possibleSumsに8がある → yes

【時間計算量】
- ループ回数: 要素数×作れる値の種類数
- 最悪の場合: O(n × n × max_sum)
  ※作れる値の最大数は2^n（2nビット未満）

【空間計算量】
- O(作れる値の総数) ≤ O(2^n)
  ※最大で2^n個の異なる値を作れる

【例】n=5, A=[1,5,7,10,21]
質問: 2 → 1+1は不可（1は1度だけ）→ no
質問: 4 → 1+5=6, 5+10=15... 作れない → no
質問: 17 → 7+10=17 → yes
質問: 8 → 1+7=8 → yes
*/

#include <stdio.h>
#include <string.h>

#define MAX_SUM 100001

int main(void) {
    int n;
    scanf("%d", &n);
    
    int A[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }
    
    // possibleSums[i] = iが作れるかどうか（1で作れる、0で作れない）
    int possibleSums[MAX_SUM];
    memset(possibleSums, 0, sizeof(possibleSums));
    possibleSums[0] = 1;  // 0は何も足さずに作れる
    
    // 配列Aの各要素について
    for (int i = 0; i < n; i++) {
        // 大きい値から小さい値へ更新（要素を2回以上使わないため）
        // 逆順でループして、既に計算された値を使わない
        for (int j = MAX_SUM - 1; j >= A[i]; j--) {
            // possibleSums[j-A[i]]が1なら、j も作れる
            if (possibleSums[j - A[i]]) {
                possibleSums[j] = 1;
            }
        }
    }
    
    // 質問処理
    int q;
    scanf("%d", &q);
    
    for (int i = 0; i < q; i++) {
        int query;
        scanf("%d", &query);
        
        if (query < MAX_SUM && possibleSums[query]) {
            printf("yes\n");
        } else {
            printf("no\n");
        }
    }
    
    return 0;
}
