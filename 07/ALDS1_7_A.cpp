/*
根付き木
与えられた根付き木 
 の各節点 
 について、以下の情報を出力するプログラムを作成してください。

 の節点番号
 の親の節点番号
 の深さ
 の節点の種類（根、内部節点または葉）
 の子のリスト
ここでは、与えられる木は 
 個の節点を持ち、それぞれ 
 から 
 の番号が割り当てられているものとします。

入力
入力の最初の行に、節点の個数 
 が与えられます。続く 
 行目に、各節点の情報が次の形式で１行に与えられます。

 
 
 
 ... 

 は節点の番号、
 は次数を表します。
 
 ...
 は 1 番目の子の節点番号、... 
 番目の子の節点番号を示します。

出力
次の形式で節点の情報を出力してください。節点の情報はその番号が小さい順に出力してください。

node 
: parent = 
, depth = 
, 
, [
...
]

 は親の番号を示します。ただし、親を持たない場合は -1 とします。
 は節点の深さを示します。

は根、内部節点、葉をそれぞれあらわす root、internal node、leaf の文字列のいずれかです。ただし、根が葉や内部節点の条件に該当する場合は root とします。

...
 は子のリストです。順序木とみなし入力された順に出力してください。カンマ空白区切りに注意してください。出力例にて出力形式を確認してください。

制約
節点の深さは 20 を超えない。
任意の２つの節点間には必ず経路が存在する。
入力例 1
13
0 3 1 4 10
1 2 2 3
2 0
3 0
4 3 5 6 7
5 0
6 0
7 2 8 9
8 0
9 0
10 2 11 12
11 0
12 0
出力例 1
node 0: parent = -1, depth = 0, root, [1, 4, 10]
node 1: parent = 0, depth = 1, internal node, [2, 3]
node 2: parent = 1, depth = 2, leaf, []
node 3: parent = 1, depth = 2, leaf, []
node 4: parent = 0, depth = 1, internal node, [5, 6, 7]
node 5: parent = 4, depth = 2, leaf, []
node 6: parent = 4, depth = 2, leaf, []
node 7: parent = 4, depth = 2, internal node, [8, 9]
node 8: parent = 7, depth = 3, leaf, []
node 9: parent = 7, depth = 3, leaf, []
node 10: parent = 0, depth = 1, internal node, [11, 12]
node 11: parent = 10, depth = 2, leaf, []
node 12: parent = 10, depth = 2, leaf, []
入力例 2
4
1 3 3 2 0
0 0
3 0
2 0
出力例 2
node 0: parent = 1, depth = 1, leaf, []
node 1: parent = -1, depth = 0, root, [3, 2, 0]
node 2: parent = 1, depth = 1, leaf, []
node 3: parent = 1, depth = 1, leaf, []
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

void setDepth(int u, int p) {
    D[u] = p;
    if (T[u].r != -1) setDepth(T[u].r, p);
    if (T[u].l != -1) setDepth(T[u].l, p + 1);
}

void printChildren(int u) {
    int c = T[u].l;
    bool first = true;
    while (c != -1) {
        if (!first) std::cout << ", ";
        std::cout << c;
        first = false;
        c = T[c].r;
    }
}

int main(){
    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++){
        T[i].p = T[i].l = T[i].r = -1;
    }

    for(int i = 0;i < n;i++){
        int id,k;
        std::cin >> id >> k;
        int last_child = -1;
        for(int j = 0;j < k;j++){
            int child;
            std::cin >> child;
            if(j == 0){
                T[id].l = child;
            }
            else{
                T[last_child].r = child;
            }
            last_child = child;
            T[child].p = id;
        }
    }

        int root;
        for (int i = 0; i < n; i++) if (T[i].p == -1) root = i;

        setDepth(root, 0);

        for (int i = 0; i < n; i++) {
            std::cout << "node " << i << ": parent = " << T[i].p << ", depth = " << D[i] << ", ";
            if (T[i].p == -1) std::cout << "root, [";
            else if (T[i].l == -1) std::cout << "leaf, [";
            else std::cout << "internal node, [";
            printChildren(i);
            std::cout << "]" << std::endl;
        }
        return 0;
    }
