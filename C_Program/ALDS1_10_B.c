/*
連鎖行列積
 個の行列の連鎖 
 が与えられたとき、スカラー乗算の回数が最小になるように積 
 の計算順序を決定する問題を連鎖行列積問題(Matrix-Chain Multiplication problem)と言います。

 個の行列について、行列 
 の次元が与えられたとき、積 
 の計算に必要なスカラー乗算の最小の回数を求めるプログラムを作成してください。

入力
入力の最初の行に、行列の数 
 が与えられます。続く 
 行で行列 
 の次元が空白区切りの２つの整数 
、
 で与えられます。
 は行列の行の数、
 は行列の列の数を表します。

出力
最小の回数を１行に出力してください。

制約
入力例 1
6
30 35
35 15
15 5
5 10
10 20
20 25
出力例 1
15125
*/

#include <stdio.h>
#include <limits.h>

#define MAX_N 100

int p[MAX_N + 1];
int m[MAX_N + 1][MAX_N + 1];

int matrixChain(int n) {
    for (int i = 1; i <= n; i++) {
        m[i][i] = 0;
    }
    
    for (int l = 2; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                }
            }
        }
    }
    
    return m[1][n];
}

int main(void) {
    int n;
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        int r, c;
        scanf("%d %d", &r, &c);
        if (i == 0) {
            p[0] = r;
        }
        p[i + 1] = c;
    }
    
    printf("%d\n", matrixChain(n));
    
    return 0;
}