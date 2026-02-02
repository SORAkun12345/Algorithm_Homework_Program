/*
最大の利益
FX取引では、異なる国の通貨を交換することで為替差の利益を得ることができます。
例えば、１ドル100円の時に 1000ドル買い、価格変動により 1ドル 108円になった時に売ると、
(108円 100円) 
 1000ドル 
 8000円の利益を得ることができます。

ある通貨について、時刻 
 における価格 
 (
)が入力として与えられるので、価格の差 
 (ただし、
 とする) の最大値を求めてください。

入力
最初の行に整数 
 が与えられます。続く 
 行に整数 
 (
) が順番に与えられます。

出力
最大値を１行に出力してください。

制約
入力例 1
6
5
3
1
3
4
3
入力例 1 に対する出力
3
入力例 2
3
4
3
2
入力例 2 に対する出力
-1
*/

#include<stdio.h>

int difference(int x[],int n);

int main(){
    int n;
    scanf("%d",&n);

    int x[n];

    for(int i = 0; i < n; i++){
        scanf("%d",&x[i]);
    }

    int differences = difference(x,n);
    printf("%d\n",differences);

    return 0;
}

int difference(int x[],int n){
    int minv = x[0];
    int maxv = x[1] - x[0];

    for(int i = 1; i < n; i++){
        if (maxv < x[i] - minv){
            maxv = x [i] - minv;
        }

        if (minv > x[i]){
            minv = x[i];
        }
    }
    return maxv;    
}