/*
二分探索
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
 の要素は昇順に整列されている
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
1 2 3
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

#include <iostream>
#include <cstdio> // scanfのために必要

// プロトタイプ宣言（mainより前に関数の存在を知らせる）
int Search(int S[], int key, int n);

int main(){
    int n;
    if (scanf("%d", &n) != 1) return 0;

    int S[n]; // ※本来C++標準ではvector推奨ですが、このままいきます
    for(int i = 0; i < n; i++){
        scanf("%d", &S[i]);
    }

    int q;
    if (scanf("%d", &q) != 1) return 0;

    int T[q]; // ※ここも本来はvector推奨
    // 【修正】回数は n ではなく q
    for(int i = 0; i < q; i++){
        scanf("%d", &T[i]);
    }

    int c = 0;
    // 【修正】int i の宣言が必要
    for(int i = 0; i < q; i++){
        // 【修正】S[] ではなく S を渡す。n も渡す。
        c += Search(S, T[i], n);
    }

    // 【修正】 < ではなく <<
    std::cout << c << std::endl;
    
    return 0;
}

int Search(int S[], int key, int n){
    int left = 0;
    int right = n - 1;
    int mid;

    // 【修正】左端が右端を追い越すまで続ける
    while(left <= right){
        // 【修正】真ん中のインデックスの計算
        mid = (left + right) / 2;

        if(S[mid] == key){
            return 1; // 見つかった
        }
        // key の方が大きい -> 右側（大きい方）を探す
        else if(S[mid] < key){
            left = mid + 1; // 左端を mid の右隣へ
        }
        // key の方が小さい -> 左側（小さい方）を探す
        else {
            right = mid - 1; // 右端を mid の左隣へ
        }
    }
    
    return 0; // 最後まで見つからなかった
}