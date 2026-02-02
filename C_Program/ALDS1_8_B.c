/*
二分探索木II
A: Binary Search Tree I に、find 命令を追加し、二分探索木 
 に対し、以下の命令を実行するプログラムを作成してください。

insert 
: 
にキー 
 を挿入する。
find 
: 
にキー 
 が存在するか否かを報告する。
print: キーを木の中間順巡回(inorder tree walk)と先行順巡回(preorder tree walk)アルゴリズムで出力する。
入力
入力の最初の行に、命令の数 
 が与えられます。続く
 行目に、insert 
、find 
 またはprintの形式で命令が１行に与えられます。

出力
find 
 命令ごとに、
 に 
 が含まれる場合 yes と、含まれない場合 no と１行に出力してください。

さらに print 命令ごとに、中間順巡回アルゴリズム、先行順巡回アルゴリズムによって得られるキーの順列をそれぞれ１行に出力してください。各キーの前に１つの空白を出力してください。

制約
命令の数は 
 を超えない。
print 命令の数は 
 を超えない。
キー
上記の疑似コードのアルゴリズムに従う場合、木の高さは 
 を超えない。
２分探索木中のキーに重複は発生しない。
入力例 1
10
insert 30
insert 88
insert 12
insert 1
insert 20
find 12
insert 17
insert 25
find 16
print
出力例 1
yes
no
 1 12 17 20 25 30 88
 30 12 1 20 17 25 88
参考文献
Introduction to Algorithms, Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, and Clifford Stein. The MIT Press.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int key;
    struct Node *parent;
    struct Node *left;
    struct Node *right;
} Node;

Node *root = NULL;

Node *create_node(int key) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        exit(1);
    }
    node->key = key;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void insert_node(Node *z) {
    Node *y = NULL;
    Node *x = root;
    
    while (x != NULL) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    
    z->parent = y;
    
    if (y == NULL) {
        root = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }
}

Node *find_node(int key) {
    Node *x = root;
    
    while (x != NULL && key != x->key) {
        if (key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    
    return x;
}

void inorder(Node *u) {
    if (u == NULL) return;
    inorder(u->left);
    printf(" %d", u->key);
    inorder(u->right);
}

void preorder(Node *u) {
    if (u == NULL) return;
    printf(" %d", u->key);
    preorder(u->left);
    preorder(u->right);
}

int main(void) {
    int m;
    if (scanf("%d", &m) != 1) {
        return 0;
    }
    
    for (int i = 0; i < m; i++) {
        char cmd[10];
        scanf("%s", cmd);
        
        if (strcmp(cmd, "insert") == 0) {
            int key;
            scanf("%d", &key);
            Node *z = create_node(key);
            insert_node(z);
        } else if (strcmp(cmd, "find") == 0) {
            int key;
            scanf("%d", &key);
            Node *result = find_node(key);
            if (result != NULL) {
                printf("yes\n");
            } else {
                printf("no\n");
            }
        } else if (strcmp(cmd, "print") == 0) {
            inorder(root);
            printf("\n");
            preorder(root);
            printf("\n");
        }
    }
    
    return 0;
}
