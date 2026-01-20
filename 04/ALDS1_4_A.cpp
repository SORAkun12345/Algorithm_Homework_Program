/*
線形探索
 個の整数を含む数列 
 と、
 個の異なる整数を含む数列 
 を読み込み、
 に含まれる整数の中で 
 に含まれるものの個数 
 を出力するプログラムを作成してください。

入力
１行目に 
、２行目に 
 を表す 
 個の整数、３行目に 
、４行目に 
 を表す 
 個の整数が与えられます。

出力
 を１行に出力してください。

制約
の要素
の要素
 の要素は互いに異なる
入力例 1
5
1 2 3 4 5
3
3 4 1
出力例 1
3
入力例 2
3
3 1 2
1
5
出力例 2
0
入力例 3
5
1 1 2 2 3
2
1 2
出力例 3
2
*/

#include  <iostream>
#include <vector>

// 線形探索（番兵を使用）
// 見つかったら 1, 見つからなければ 0 を返す [cite: 1171-1179]
int linearSearch(int n, int A[], int key) {
    int i = 0;
    A[n] = key; // 配列の末尾に番兵をセット [cite: 1174]
    
    while (A[i] != key) { // 範囲チェック (i < n) が不要になる [cite: 1175, 1180]
        i++;
    }
    
    return i != n; // 見つかった位置が末尾（番兵）でなければ発見
}

int main() {
    int n, q, key;
    int count = 0;

    // 数列 S の読み込み
    scanf("%d", &n);
    int S[n + 1]; // 番兵のために 1 つ多めに確保
    for (int i = 0; i < n; i++) {
        scanf("%d", &S[i]);
    }

    // 数列 T の読み込みと同時に探索を行う
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        scanf("%d", &key);
        // S の中に key が存在するかチェック
        if (linearSearch(n, S, key)) {
            count++;
        }
    }

    // 合計数を出力
    printf("%d\n", count);

    return 0;
}