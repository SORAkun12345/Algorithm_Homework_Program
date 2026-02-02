/*
フィボナッチ数列
フィボナッチ数列の第 
 項の値を出力するプログラムを作成してください。ここではフィボナッチ数列を以下の再帰的な式で定義します：

　	
　	
 
入力
１つの整数 
 が与えられます。

出力
フィボナッチ数列の第 
 項の値を出力してください。

制約
入力例 1
3
出力例 1
3
*/

#include <stdio.h>

long long fib[50];

long long fibonacci(int n) {
    if (n == 0) return 1;
    if (n == 1) return 1;
    
    if (fib[n] != 0) {
        return fib[n];
    }
    
    fib[n] = fibonacci(n - 1) + fibonacci(n - 2);
    return fib[n];
}

int main(void) {
    int n;
    scanf("%d", &n);
    
    printf("%lld\n", fibonacci(n));
    
    return 0;
}