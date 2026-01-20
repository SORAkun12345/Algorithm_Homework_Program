/*
計数ソート
計数ソートは各要素が 0 以上 
 以下である要素数 
 の数列に対して線形時間(
)で動く安定なソーティングアルゴリズムです。

入力数列 
 の各要素 
 について、
 以下の要素の数をカウンタ配列 
 に記録し、その値を基に出力配列 
 における 
 の位置を求めます。同じ数の要素が複数ある場合を考慮して、要素 
 を出力（
 に入れる）した後にカウンタ 
 は修正する必要があります。詳しくは以下の疑似コードを参考にしてください。

1 CountingSort(A, B, k)
2     for i = 0 to k
3         C[i] = 0
4
5     C[i] に i の出現数を記録する 
6     for j = 1 to n
7         C[A[j]]++
8
9     C[i] に i 以下の数の出現数を記録する
10    for i = 1 to k
11        C[i] = C[i] + C[i-1]
12
13    for j = n downto 1
14        B[C[A[j]]] = A[j]
15        C[A[j]]--
数列 
 を読み込み、計数ソートのアルゴリズムで昇順に並び替え出力するプログラムを作成してください。上記疑似コードに従ってアルゴリズムを実装してください。

入力
入力の最初の行に、数列 
 の長さを表す整数 
 が与えられます。２行目に、
 個の整数が空白区切りで与えられます。

出力
整列された数列を1行に出力してください。数列の連続する要素は１つの空白で区切って出力してください。

制約
入力例 1
7
2 5 1 3 2 3 0
出力例 1
0 1 2 2 3 3 5
*/

#include<iostream>
#include<vector>


void CountingSort(std::vector<int>& A,std::vector<int>& B,int k,int n){
    std::vector<int> C(k+1,0);
    for(int i = 0;i <= k;i++){
        C[i] = 0;
    }

     //C[i] に i の出現数を記録する 
     for(int j = 1;j <= n;j++){
        C[A[j]]++;
     }

    //C[i] に i 以下の数の出現数を記録する
    for(int i = 1;i <= k;i++){
        C[i] = C[i] + C[i - 1];
    }

    for(int j = n;j >= 1;j--){
        B[C[A[j]]] = A[j];
        C[A[j]]--;
    }
}

int main(){
    int n;
    std::cin >> n;

    std::vector<int> in(n + 1);
    int k = 0;
    for (int i = 1; i <= n; i++) {
        std::cin >> in[i];
        if (in[i] > k) k = in[i]; 
    }
    std::vector<int> out(n + 1);

    CountingSort(in, out, k, n);
    
    for (int i = 1; i <= n; i++) {
        std::cout << (i == 1 ? "" : " ") << out[i];
    }
    std::cout << std::endl;

    return 0;
}