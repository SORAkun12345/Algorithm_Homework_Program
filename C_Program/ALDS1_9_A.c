/*
完全二分木
すべての葉が同じ深さを持ち、すべての内部節点の次数が 2 であるような二分木を完全二分木と呼びます。また、二分木の最下位レベル以外のすべてのレベルは完全に埋まっており、最下位レベルは最後の節点まで左から順に埋まっているような木も（おおよそ）完全二分木と呼びます。

二分ヒープは、次の図のように、木の各節点に割り当てられたキーが１つの配列の各要素に対応した完全二分木で表されたデータ構造です。



二分ヒープを表す配列を 
、二分ヒープのサイズ（要素数）を 
 とすれば、
 に二分ヒープの要素が格納されます。木の根の添え字は 
 であり、節点の添え字 
 が与えられたとき、その親 
、左の子 
、右の子 
 はそれぞれ 
、
、
 で簡単に算出することができます。

完全二分木で表された二分ヒープを読み込み、以下の形式で二分ヒープの各節点の情報を出力するプログラムを作成してください。

node 
: key = 
, parent key = 
, left key = 
, right key = 
,

ここで、
 は節点の番号（インデックス）、
 は節点の値、
 は親の値、
 は左の子の値、
 は右の子の値を示します。これらの情報をこの順番で出力してください。ただし、該当する節点が存在しない場合は、出力を行わないものとします。

入力
入力の最初の行に、二分ヒープのサイズ 
 が与えられます。続いて、ヒープの節点の値（キー）を表す 
 個の整数がそれらの節点の番号順に空白区切りで与えられます。

出力
上記形式で二分ヒープの節点の情報をインデックスが 1 から 
 に向かって出力してください。各行の最後が空白となることに注意してください。

制約
節点のキー
入力例 1
5
7 8 1 2 3
出力例 1
node 1: key = 7, left key = 8, right key = 1, 
node 2: key = 8, parent key = 7, left key = 2, right key = 3, 
node 3: key = 1, parent key = 7, 
node 4: key = 2, parent key = 8, 
node 5: key = 3, parent key = 8, 

参考文献
Introduction to Algorithms, Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, and Clifford Stein. The MIT Press.
*/

#include <stdio.h>

int H[250000];
int H_size;

int parent(int i) {
    return i / 2;
}

int left(int i) {
    return 2 * i;
}

int right(int i) {
    return 2 * i + 1;
}

int main(void) {
    scanf("%d", &H_size);
    
    for (int i = 1; i <= H_size; i++) {
        scanf("%d", &H[i]);
    }
    
    for (int i = 1; i <= H_size; i++) {
        printf("node %d: key = %d, ", i, H[i]);
        
        if (parent(i) >= 1) {
            printf("parent key = %d, ", H[parent(i)]);
        }
        
        if (left(i) <= H_size) {
            printf("left key = %d, ", H[left(i)]);
        }
        
        if (right(i) <= H_size) {
            printf("right key = %d, ", H[right(i)]);
        }
        
        printf("\n");
    }
    
    return 0;
}