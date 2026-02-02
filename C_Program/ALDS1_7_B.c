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

#include <stdio.h>

typedef struct Node {
    int parent;
    int depth;
    int height;
    int left;
    int right;
} Node;

void setDepth(Node nodes[], int id, int depth) {
    if (id == -1) return;
    nodes[id].depth = depth;
    setDepth(nodes, nodes[id].left, depth + 1);
    setDepth(nodes, nodes[id].right, depth + 1);
}

int setHeight(Node nodes[], int id) {
    if (id == -1) return -1;
    int h1 = setHeight(nodes, nodes[id].left);
    int h2 = setHeight(nodes, nodes[id].right);
    int height = (h1 > h2 ? h1 : h2) + 1;
    nodes[id].height = height;
    return height;
}

int main(){
    int n;
    scanf("%d", &n);
    
    Node nodes[n];
    
    // 初期化
    for (int i = 0; i < n; i++) {
        nodes[i].parent = -1;
        nodes[i].depth = 0;
        nodes[i].height = 0;
        nodes[i].left = -1;
        nodes[i].right = -1;
    }
    
    // 入力読み込み
    for (int i = 0; i < n; i++) {
        int id, left, right;
        scanf("%d %d %d", &id, &left, &right);
        nodes[id].left = left;
        nodes[id].right = right;
        if (left != -1) {
            nodes[left].parent = id;
        }
        if (right != -1) {
            nodes[right].parent = id;
        }
    }
    
    // ルートを見つける
    int root = -1;
    for (int i = 0; i < n; i++) {
        if (nodes[i].parent == -1) {
            root = i;
            break;
        }
    }
    
    // 深さと高さを計算
    setDepth(nodes, root, 0);
    setHeight(nodes, root);
    
    // 出力
    for (int i = 0; i < n; i++) {
        // 兄弟を見つける
        int sibling = -1;
        if (nodes[i].parent != -1) {
            int p = nodes[i].parent;
            if (nodes[p].left == i) {
                sibling = nodes[p].right;
            } else {
                sibling = nodes[p].left;
            }
        }
        
        // 子の数（degree）
        int degree = 0;
        if (nodes[i].left != -1) degree++;
        if (nodes[i].right != -1) degree++;
        
        // タイプ
        const char *type;
        if (nodes[i].parent == -1) {
            type = "root";
        } else if (degree == 0) {
            type = "leaf";
        } else {
            type = "internal node";
        }
        
        printf("node %d: parent = %d, sibling = %d, degree = %d, depth = %d, height = %d, %s\n",
               i, nodes[i].parent, sibling, degree, nodes[i].depth, nodes[i].height, type);
    }
    
    return 0;
}