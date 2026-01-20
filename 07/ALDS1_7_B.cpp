/*
二分木
与えられた二分木 
 の各節点 
 について、以下の情報を出力するプログラムを作成してください。

 の節点番号
 の親
 の兄弟
 の子の数
 の深さ
 の高さ
節点の種類（根、内部節点または葉）
ここでは、与えられる二分木は 
 個の節点を持ち、それぞれ 
 から 
 の番号が割り当てられているものとします。

入力
入力の最初の行に、節点の個数 
 が与えられます。続く 
 行目に、各節点の情報が以下の形式で１行に与えられます。

 
 

 は節点の番号、
 は左の子の番号、
 は右の子の番号を表します。子を持たない場合は 
 (
)は -1 で与えられます。

出力
次の形式で節点の情報を出力してください。

node 
: parent = 
, sibling = 
, degree = 
, depth = 
, height = 
, 


 は親の番号を表します。親を持たない場合は -1 とします。
 は兄弟の番号を表します。兄弟を持たない場合は -1 とします。

、
、
 はそれぞれ節点の子の数、深さ、高さを表します。

 は根、内部節点、葉をそれぞれ表す root、internal node、leaf の文字列のいずれかです。ただし、根が葉や内部節点の条件に該当する場合は root とします。

出力例にて、空白区切り等の出力形式を確認してください。

制約
入力例 1
9
0 1 4
1 2 3
2 -1 -1
3 -1 -1
4 5 8
5 6 7
6 -1 -1
7 -1 -1
8 -1 -1
出力例 1
node 0: parent = -1, sibling = -1, degree = 2, depth = 0, height = 3, root
node 1: parent = 0, sibling = 4, degree = 2, depth = 1, height = 1, internal node
node 2: parent = 1, sibling = 3, degree = 0, depth = 2, height = 0, leaf
node 3: parent = 1, sibling = 2, degree = 0, depth = 2, height = 0, leaf
node 4: parent = 0, sibling = 1, degree = 2, depth = 1, height = 2, internal node
node 5: parent = 4, sibling = 8, degree = 2, depth = 2, height = 1, internal node
node 6: parent = 5, sibling = 7, degree = 0, depth = 3, height = 0, leaf
node 7: parent = 5, sibling = 6, degree = 0, depth = 3, height = 0, leaf
node 8: parent = 4, sibling = 5, degree = 0, depth = 2, height = 0, leaf

参考文献
Introduction to Algorithms, Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, and Clifford Stein. The MIT Press.
*/

#include<iostream>
#include<vector>

struct Node {
    int p;
    int l;
    int r;
};

Node T[100005];
int D[100005];
int H[100005];

void setDepth(int u, int d) {
    if (u == -1) return;
    D[u] = d;
    setDepth(T[u].l, d + 1);
    setDepth(T[u].r, d + 1);
}

int setHeight(int u) {
    int h1 = 0, h2 = 0;
    if (T[u].l != -1) h1 = setHeight(T[u].l) + 1;
    if (T[u].r != -1) h2 = setHeight(T[u].r) + 1;
    return H[u] = std::max(h1, h2);
}

int getSibling(int u) {
    int c = T[u].p;
    if (c == -1) return -1;
    else if(T[c].l == u){
        return T[c].r;
    }
    else if(T[c].r == u){
        return T[c].l;
    }
    else return -1;
}

int main(){
    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++){
        T[i].p = T[i].l = T[i].r = -1;
    }

    for(int i = 0;i < n;i++){
        int id;
        std::cin >> id;
        int last_child = -1;
        for(int j = 0; j < 2; j++){
            int child;
            std::cin >> child;
            if(j == 0) T[id].l = child;
            else T[id].r = child;
            
            if (child != -1) T[child].p = id; 
        }
    }

    int root;
    for (int i = 0; i < n; i++) if (T[i].p == -1) root = i;

    setDepth(root, 0);
    setHeight(root);

    for (int i = 0; i < n; i++) {
        int deg = 0;
        if (T[i].l != -1) deg++;
        if (T[i].r != -1) deg++;

        std::cout << "node " << i << ": parent = " << T[i].p;
        std::cout << ", sibling = " << getSibling(i);
        std::cout << ", degree = " << deg;
        std::cout << ", depth = " << D[i];
        std::cout << ", height = " << H[i] << ", ";

        if (T[i].p == -1) std::cout << "root";
        else if (T[i].l == -1 && T[i].r == -1) std::cout << "leaf";
        else std::cout << "internal node";
        std::cout << std::endl;
    }
    return 0;
}
