/*
木の巡回
以下に示すアルゴリズムで、与えられた２分木のすべての節点を体系的に訪問するプログラムを作成してください。

根節点、左部分木、右部分木の順で節点の番号を出力する。これを木の先行順巡回 (preorder tree walk) と呼びます。
左部分木、根節点、右部分木の順で節点の番号を出力する。これを木の中間順巡回 (inorder tree walk) と呼びます。
左部分木、右部分木、根節点の順で節点の番号を出力する。これを木の後行順巡回 (postorder tree walk) と呼びます。
与えられる２分木は 
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
) は -1 で与えられます。

出力
１行目に"Preorder"と出力し、２行目に先行順巡回を行った節点番号を順番に出力してください。

３行目に"Inorder"と出力し、４行目に中間順巡回を行った節点番号を順番に出力してください。

５行目に"Postorder"と出力し、６行目に後行順巡回を行った節点番号を順番に出力してください。

節点番号の前に１つの空白文字を出力してください。

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
Preorder
 0 1 2 3 4 5 6 7 8
Inorder
 2 1 3 0 6 5 7 4 8
Postorder
 2 3 1 6 7 5 8 4 0

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

int preorder(Node nodes[], int id) {
    if (id == -1) return 0;
    printf(" %d", id);
    preorder(nodes, nodes[id].left);
    preorder(nodes, nodes[id].right);
    return 0;
}

int inorder(Node nodes[], int id) {
    if (id == -1) return 0;
    inorder(nodes, nodes[id].left);
    printf(" %d", id);
    inorder(nodes, nodes[id].right);
    return 0;
}

int postorder(Node nodes[], int id) {
    if (id == -1) return 0;
    postorder(nodes, nodes[id].left);
    postorder(nodes, nodes[id].right);
    printf(" %d", id);
    return 0;
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
    printf("Preorder\n");
    preorder(nodes, root);
    printf("\n");
    printf("Inorder\n");
    inorder(nodes, root);
    printf("\n");
    printf("Postorder\n");
    postorder(nodes, root);
    printf("\n");
    
    /*
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
    */
    
    return 0;
}