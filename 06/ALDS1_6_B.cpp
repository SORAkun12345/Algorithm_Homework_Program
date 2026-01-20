/*
Partition
partition ( A, p, r )は、配列 A[ p..r ] を A[ p..q − 1] の各要素が A[q] 以下で、A[ q +1.. r ] の各要素が 
A[ q ] より大きい A[ p..q − 1] と A[q + 1..r ] に分割し、
インデックス q を戻り値として返します。

数列 
 を読み込み、次の疑似コードに基づいた partition を行うプログラムを作成してください。

1 partition(A, p, r)
2   x = A[r]
3   i = p-1
4   for j = p to r-1
4     if A[j] <= x
5       i = i+1
6       A[i] と A[j] を交換
7   A[i+1] と A[r] を交換
8   return i+1
ここで、
 は配列 
 の最後の要素を指す添え字で、
 を基準として配列を分割することに注意してください。

入力
入力の最初の行に、数列 
 の長さを表す整数 
 が与えられます。２行目に、
 個の整数 
 (
) が空白区切りで与えられます。

出力
分割された数列を1行に出力してください。数列の連続する要素は１つの空白で区切って出力してください。また、partition の基準となる要素を [   ]で示してください。

制約
入力例 1
12
13 19 9 5 12 8 7 4 21 2 6 11
出力例 1
9 5 8 7 4 2 6 [11] 21 13 19 12
*/

#include<iostream>
#include<vector>
#include<algorithm>

int  partition(std::vector<int>& A,int p,int r){
    int x = A[r];
    int i = p - 1;
    for(int j = p;j < r;j++){
        if(A[j] <= x){
            i = i + 1;
            std::swap(A[i],A[j]);
        }
    }
    std::swap(A[i+1],A[r]);
    return i+1;
}

int main(){
    int n;
    std::cin >> n;

    std::vector<int> X(n);
    for(int i = 0;i < n;i++){
        std::cin >> X[i];
    }

    int q = partition(X,0,n-1);

    for (int i = 0; i < n; ++i) {
        if (i > 0) std::cout << " ";

        if (i == q) {
            std::cout << "[" << X[i] << "]";
        } else {
            std::cout << X[i];
        }
    }
    std::cout << std::endl;
    return 0;
}