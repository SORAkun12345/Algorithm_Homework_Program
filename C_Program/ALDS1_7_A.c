/*
根付き木
与えられた根付き木 $T$ の各節点 $u$ について、以下の情報を出力するプログラムを作成してください。

$u$ の節点番号
$u$ の親の節点番号
$u$ の深さ
$u$ の節点の種類（根、内部節点または葉）
$u$ の子のリスト
ここでは、与えられる木は $n$ 個の節点を持ち、それぞれ $0$ から $n − 1$ の番号が割り当てられているものとします。

入力
入力の最初の行に、節点の個数 $n$ が与えられます。続く $n$ 行目に、各節点の情報が次の形式で１行に与えられます。

$id$ $k$ $c_1$ $c_2$ ... $c_k$

$id$ は節点の番号、$k$ は次数を表します。$c_1$ $c_2$ ...$c_k$ は 1 番目の子の節点番号、... $k$ 番目の子の節点番号を示します。

出力
次の形式で節点の情報を出力してください。節点の情報はその番号が小さい順に出力してください。

node $id$: parent = $p$, depth = $d$, $type$, [$c_1$...$c_k$]

$p$ は親の番号を示します。ただし、親を持たない場合は -1 とします。$d$ は節点の深さを示します。

$type$は根、内部節点、葉をそれぞれあらわす root、internal node、leaf の文字列のいずれかです。ただし、根が葉や内部節点の条件に該当する場合は root とします。

$c_1$...$c_k$ は子のリストです。順序木とみなし入力された順に出力してください。カンマ空白区切りに注意してください。出力例にて出力形式を確認してください。

制約
$1 \leq n \leq 100,000$
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

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

typedef struct Node {
    int parent;
    int depth;
    int *children;  // 動的配列へのポインタ
    int num_children;
} Node;

void setDepth(Node nodes[], int id, int depth) {
    nodes[id].depth = depth;
    for (int i = 0; i < nodes[id].num_children; i++) {
        setDepth(nodes, nodes[id].children[i], depth + 1);
    }
}

int main(){
    int n;
    scanf("%d", &n);

    Node nodes[n];

    // 配列の初期化
    for (int i = 0; i < n; i++) {
        nodes[i].parent = -1;
        nodes[i].depth = 0;
        nodes[i].num_children = 0;
        nodes[i].children = NULL;
    }

    int id, k;
    for(int i = 0;i < n;i++){
        scanf("%d %d", &id, &k);
        nodes[id].num_children = k;
        if (k > 0) {
            nodes[id].children = (int*)malloc(sizeof(int) * k);
        }
        for(int j = 0;j < k;j++){
            int child;
            scanf("%d", &child);
            nodes[id].children[j] = child;
            nodes[child].parent = id;
        }
    }

    // ルートノードを見つけて深さを設定
    int root = -1;
    for (int i = 0; i < n; i++) {
        if (nodes[i].parent == -1) {
            root = i;
            break;
        }
    }
    setDepth(nodes, root, 0);

    for(int i = 0;i < n;i++){
        printf("node %d: parent = %d, depth = %d, ", i, nodes[i].parent, nodes[i].depth);
        if(nodes[i].parent == -1)
            printf("root, [");
        else if(nodes[i].num_children == 0)
            printf("leaf, [");
        else
            printf("internal node, [");

        for(int j = 0;j < nodes[i].num_children;j++){
            if(j > 0)
                printf(", ");
            printf("%d", nodes[i].children[j]);
        }
        printf("]\n");
    }

    // メモリ解放
    for (int i = 0; i < n; i++) {
        if (nodes[i].children != NULL) {
            free(nodes[i].children);
        }
    }

    return 0;
}