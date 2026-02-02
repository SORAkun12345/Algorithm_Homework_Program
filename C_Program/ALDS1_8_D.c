/*
Treap
二分探索木は、挿入されるデータ列の特徴によっては、偏った木になり、検索・挿入・削除操作の効率が悪くなります。例えば、整列された
個のデータが順番に挿入されれば、木はリストのような形になり、その高さは
になります。挿入されるデータが固定されていれば、要素をランダムにシャッフルすることにより平衡な木を構築することができるでしょう。しかし、データ構造としての二分木では要求に応じて異なる操作が繰り返し行われるため、適宜データを一つずつ処理しながら、常に平衡な状態を保つ必要があります。

二分木の各節点に、ランダムに選択された優先度を割り当て、以下の条件を満たすように節点を順序付けることによって、平衡な二分木を保つことができます。ここで、各節点のキー(key)と優先度(priority)はそれぞれ重複がないものとします。

二分探索木条件. 
が
の左の子なら
 かつ 
が
の右の子なら 
ヒープ条件.
が
の子なら
このような木を、二分探索木とヒープの特徴からTreap ( tree + heap ) と呼びます。

例えば、次の図はTreapの例です。


挿入
Treapに新たにデータを挿入するには、キーに加えランダムに選択した優先度を割り当てた節点を、まずは通常の二分探索木と同様の方法で挿入します。例えば、上のTreapにkey = 6, priority = 90 である節点を挿入すると次のようになります。


このままの状態では、ヒープ条件を破ってしまうため、ヒープ条件を満たすまで回転を繰り返します。回転とは、次の図のように、二分探索木条件を満たしつつ、親子関係を逆転させる操作です。


回転は次のプログラムのようにポインタを繋ぎ変えます。

# 節点tを根とする部分木を右に回転する
def rotate_right(t): 
    s = t.left
    t.left = s.right
    s.right = t
    return s # 新しい部分木の根となる
# 節点tを根とする部分木を左に回転する
def rotate_left(t):
    s = t.right
    t.right = s.left
    s.left = t
    return s # 新しい部分木の根となる
上のTreapに回転操作を行うと以下のように二分探索木が構築されます。


条件を満たすようにTreapに新しい要素を挿入するinsert操作は以下のようになります。

# キーがkeyで優先度がpriの節点をTreapに挿入する
# t: 探索で訪問中の節点
def insert(t, key, pri):                     # 再帰的に探索する
    if t is NIL:
        return Node(key, pri)                # 葉に到達したら新しい節点を生成して返す
    if key == t.key:
        return t                             # 重複したkeyは無視する

    if key < t.key:                          # 左の子へ移動する
        t.left = insert(t.left, key, pri)    # 左の子へのポインタを更新する
        if t.pri < t.left.pri:               # 左の子の方が優先度が高い場合は右に回転
            t = rotate_right(t)
    else:                                    # 右の子へ移動する
        t.right = insert(t.right, key, pri)  # 右の子へのポインタを更新する
        if t.pri < t.right.pri:              # 右の子の方が優先度が高い場合は左に回転
            t = rotate_left(t)
    return t
削除
Treapの節点を削除する場合は、以下の手順で対象となる節点を回転によって葉まで移動した後、削除します。

def search_and_delete(t, key):
    if t is NIL:
        return NIL
    if key < t.key:                          # 削除対象を検索する
        t.left = search_and_delete(t.left, key)
    elif key > t.key:
        t.right = search_and_delete(t.right, key)
    else:                                    # 削除対象を発見
        return delete_target(t, key)
    return t

def delete_target(t, key):
    if t.left is NIL and t.right is NIL:     # 葉の場合
        return NIL
    elif t.left is NIL:                      # 右の子のみを持つ場合は左回転
        t = rotate_left(t)
    elif t.right is NIL:                     # 左の子のみを持つ場合は右回転
        t = rotate_right(t)
    else:                                    # 左の子と右の子を両方持つ場合
        if t.left.pri > t.right.pri:         # 優先度が高い方を持ち上げる
            t = rotate_right(t)
        else:
            t = rotate_left(t)
    return search_and_delete(t, key)  
Treap 
 に対して、以下の命令を、上記のアルゴリズムに基づいて実行するプログラムを作成してください。

insert (
, 
): 
 にキーが 
、優先度が
の要素 を挿入する。
find (
): 
 にキー 
 が存在するか否かを報告する。
delete (
): キー 
 を持つ節点を削除する。
print(): キーを木の中間順巡回(inorder tree walk)と先行順巡回(preorder tree walk)アルゴリズムで出力する。
入力
入力の最初の行に、命令の数 
 が与えられます。続く
 行に、insert 
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
上記のアルゴリズムに従う場合、木の高さは 
 を超えない。
二分探索木中のキーに重複は発生しない。
二分探索木中の優先度に重複は発生しない。
print命令の数は
を超えない。
出力のサイズは
 Mバイトを超えない。
入力例 1
16
insert 35 99
insert 3 80
insert 1 53
insert 14 25
insert 80 76
insert 42 3
insert 86 47
insert 21 12
insert 7 10
insert 6 90
print
find 21
find 22
delete 35
delete 99
print
出力例 1
 1 3 6 7 14 21 35 42 80 86
 35 6 3 1 14 7 21 80 42 86
yes
no
 1 3 6 7 14 21 42 80 86
 6 3 1 80 14 7 21 42 86
参考文献
Introduction to Algorithms, Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, and Clifford Stein. The MIT\ Press.
Randomized Search Trees, R. Seidel, C.R. Aragon.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int key;
    int priority;
    struct Node *left;
    struct Node *right;
} Node;

Node *root = NULL;

Node *create_node(int key, int priority) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        exit(1);
    }
    node->key = key;
    node->priority = priority;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node *rotate_right(Node *t) {
    Node *s = t->left;
    t->left = s->right;
    s->right = t;
    return s;
}

Node *rotate_left(Node *t) {
    Node *s = t->right;
    t->right = s->left;
    s->left = t;
    return s;
}

Node *insert(Node *t, int key, int priority) {
    if (t == NULL) {
        return create_node(key, priority);
    }
    if (key == t->key) {
        return t;
    }
    
    if (key < t->key) {
        t->left = insert(t->left, key, priority);
        if (t->priority < t->left->priority) {
            t = rotate_right(t);
        }
    } else {
        t->right = insert(t->right, key, priority);
        if (t->priority < t->right->priority) {
            t = rotate_left(t);
        }
    }
    return t;
}

Node *find_node(Node *t, int key) {
    if (t == NULL) return NULL;
    if (key == t->key) return t;
    if (key < t->key) {
        return find_node(t->left, key);
    } else {
        return find_node(t->right, key);
    }
}

Node *delete_target(Node *t, int key);

Node *search_and_delete(Node *t, int key) {
    if (t == NULL) {
        return NULL;
    }
    if (key < t->key) {
        t->left = search_and_delete(t->left, key);
    } else if (key > t->key) {
        t->right = search_and_delete(t->right, key);
    } else {
        return delete_target(t, key);
    }
    return t;
}

Node *delete_target(Node *t, int key) {
    if (t->left == NULL && t->right == NULL) {
        free(t);
        return NULL;
    } else if (t->left == NULL) {
        t = rotate_left(t);
    } else if (t->right == NULL) {
        t = rotate_right(t);
    } else {
        if (t->left->priority > t->right->priority) {
            t = rotate_right(t);
        } else {
            t = rotate_left(t);
        }
    }
    return search_and_delete(t, key);
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
            int key, priority;
            scanf("%d %d", &key, &priority);
            root = insert(root, key, priority);
        } else if (strcmp(cmd, "find") == 0) {
            int key;
            scanf("%d", &key);
            Node *result = find_node(root, key);
            if (result != NULL) {
                printf("yes\n");
            } else {
                printf("no\n");
            }
        } else if (strcmp(cmd, "delete") == 0) {
            int key;
            scanf("%d", &key);
            root = search_and_delete(root, key);
        } else if (strcmp(cmd, "print") == 0) {
            inorder(root);
            printf("\n");
            preorder(root);
            printf("\n");
        }
    }
    
    return 0;
}