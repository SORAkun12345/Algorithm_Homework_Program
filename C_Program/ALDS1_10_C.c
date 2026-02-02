/*
最長共通部分列
最長共通部分列問題 (Longest Common Subsequence problem: LCS)は、２つの与えられた列 
 と 
 の最長共通部分列を求める問題です。

ある列 
 が 
 と 
 両方の部分列であるとき、
 を 
 と
 の共通部分列と言います。例えば、
, 
 とすると、列 
 は 
 と 
 の共通部分列です。一方、列 
 は 
 と 
 の最長共通部分列ではありません。なぜなら、その長さは 3 であり、長さ 4 の共通部分列 
 が存在するからです。長さが 5 以上の共通部分列が存在しないので、列 
 は 
 と 
 の最長共通部分列の１つです。

与えられた２つの文字列 
、
に対して、最長共通部分列 
 の長さを出力するプログラムを作成してください。与えられる文字列は英文字のみで構成されています。

入力
複数のデータセットが与えられます。最初の行にデータセットの数 
 が与えられます。続く 
 行にデータセットが与えられます。各データセットでは２つの文字列 
, 
 がそれぞれ１行に与えられます。

出力
各データセットについて 
, 
 の最長共通部分列 
 の長さを１行に出力してください。

制約
の長さ
 または 
 の長さが 100 を超えるデータセットが含まれる場合、
 は 20 以下である。
入力例 1
3
abcbdab
bdcaba
abc
abc
abc
bc
出力例 1
4
3
2
参考文献
Introduction to Algorithms, Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, and Clifford Stein. The MIT Press.
*/

#include <stdio.h>
#include <string.h>

#define MAX_LEN 1001

int dp[MAX_LEN][MAX_LEN];
char X[MAX_LEN];
char Y[MAX_LEN];

int max(int a, int b) {
    return (a > b) ? a : b;
}

int lcs(char *X, char *Y) {
    int m = strlen(X);
    int n = strlen(Y);
    
    for (int i = 0; i <= m; i++) {
        dp[i][0] = 0;
    }
    for (int j = 0; j <= n; j++) {
        dp[0][j] = 0;
    }
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    
    return dp[m][n];
}

int main(void) {
    int q;
    scanf("%d", &q);
    
    for (int i = 0; i < q; i++) {
        scanf("%s", X);
        scanf("%s", Y);
        printf("%d\n", lcs(X, Y));
    }
    
    return 0;
}