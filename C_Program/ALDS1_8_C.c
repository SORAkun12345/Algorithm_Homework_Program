/*
２分探索木III
B: Binary Search Tree II に、delete 命令を追加し、二分探索木 
 に対し、以下の命令を実行するプログラムを作成してください。

insert 
: 
 にキー 
 を挿入する。
find 
: 
 にキー 
 が存在するか否かを報告する。
delete 
: キー 
 を持つ節点を削除する。
print: キーを木の中間順巡回(inorder tree walk)と先行順巡回(preorder tree walk)アルゴリズムで出力する。
二分探索木 
 から与えられたキー 
 を持つ節点 
 を削除する delete k は以下の３つの場合を検討したアルゴリズムに従い、二分探索木条件を保ちつつ親子のリンク（ポインタ）を更新します：

 が子を持たない場合、
 の親 
 の子（つまり 
）を削除する。
 がちょうど１つの子を持つ場合、
 の親の子を 
 の子に変更、
 の子の親を 
 の親に変更し、
 を木から削除する。
 が子を２つ持つ場合、
 の次節点 
 のキーを 
 のキーへコピーし、
 を削除する。
 の削除では 1. または 2. を適用する。ここで、
 の次節点とは、中間順巡回で 
 の次に得られる節点である。
入力
入力の最初の行に、命令の数 
 が与えられます。続く
 行目に、insert 
、find 
、delete 
または print の形式で命令が１行に与えられます。

出力
find 
 命令ごとに、
 に 
 が含まれる場合 yes と、含まれない場合 no と１行に出力してください。

さらに print 命令ごとに、中間順巡回アルゴリズム、先行順巡回アルゴリズムによって得られるキーの順列をそれぞれ１行に出力してください。各キーの前に１つの空白を出力してください。

制約
命令の数は
を超えない。
print命令の数は
を超えない。
キー
上記の疑似コードのアルゴリズムに従う場合、木の高さは 
 を超えない。
二分探索木中のキーに重複は発生しない。
入力例 1
18
insert 8
insert 2
insert 3
insert 7
insert 22
insert 1
find 1
find 2
find 3
find 4
find 5
find 6
find 7
find 8
print
delete 3
delete 7
print
出力例 1
yes
yes
yes
no
no
no
yes
yes
 1 2 3 7 8 22
 8 2 1 3 7 22
 1 2 8 22
 8 2 1 22
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

Node *find_minimum(Node *x) {
    while (x->left != NULL) {
        x = x->left;
    }
    return x;
}

Node *find_successor(Node *x) {
    if (x->right != NULL) {
        return find_minimum(x->right);
    }
    Node *y = x->parent;
    while (y != NULL && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

void transplant(Node *u, Node *v) {
    if (u->parent == NULL) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != NULL) {
        v->parent = u->parent;
    }
}

void delete_node(Node *z) {
    if (z->left == NULL) {
        transplant(z, z->right);
    } else if (z->right == NULL) {
        transplant(z, z->left);
    } else {
        Node *y = find_minimum(z->right);
        if (y->parent != z) {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
    }
    free(z);
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
        } else if (strcmp(cmd, "delete") == 0) {
            int key;
            scanf("%d", &key);
            Node *z = find_node(key);
            if (z != NULL) {
                delete_node(z);
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