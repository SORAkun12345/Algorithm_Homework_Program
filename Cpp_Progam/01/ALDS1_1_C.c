/*
素数
約数が 1 とその数自身だけであるような自然数を素数と言います。
例えば、最初の8 つの素数は2, 3, 5, 7, 11, 13, 17, 19 となります。1 は素数ではありません。

n 個の整数を読み込み、それらに含まれる素数の数を出力するプログラムを作成してください。

入力
最初の行に n が与えられます。続く n 行に n 個の整数が与えられます。

出力
入力に含まれる素数の数を１行に出力してください。

制約
1 ≤ n ≤ 10,000
2 ≤ 与えられる整数 ≤ 108
入力例 1
6
2
3
4
5
6
7
入力例 1 に対する出力
4
*/
#include <stdio.h>

int isPrime(int x);

int main(){
    int n;
    scanf("%d", &n);

    int x[n];
    for(int i = 0; i < n; i++){
        scanf("%d", &x[i]);
    }

    int count = 0;
    for(int i = 0; i < n; i++){
        if(isPrime(x[i])){
            count++;
        }
    }
    printf("%d\n", count);
    return 0;
}

int isPrime(int x){
    if(x < 2) return 0;
    for(int i = 2; i * i <= x; i++){
        if(x % i == 0){
            return 0;
        }
    }
    return 1;
}