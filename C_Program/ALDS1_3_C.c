/*
双方向連結リスト
以下の命令を受けつける双方向連結リストを実装してください。

insert x: 連結リストの先頭にキー x を持つ要素を継ぎ足す。
delete x: キー x を持つ最初の要素を連結リストから削除する。そのような要素が存在しない場合は何もしない。
deleteFirst: リストの先頭の要素を削除する。
deleteLast: リストの末尾の要素を削除する。

入力
入力は以下の形式で与えられます。

n
command1
command2
...
commandn
最初の行に命令数 n が与えられます。続く n 行に命令が与えられる。命令は上記4つの命令のいずれかです。キーは整数とします。

出力
全ての命令が終了した後の、連結リスト内のキーを順番に出力してください。連続するキーは１つの空白文字で区切って出力してください。

制約
命令数は 2,000,000 を超えない。
delete 命令の回数は 20 を超えない。
0 ≤ キーの値 ≤ 10^9。
命令の過程でリストの要素数は 10^6を超えない。
delete, deleteFirst, または deleteLast 命令が与えられるとき、リストには１つ以上の要素が存在する。

入力例 1
7
insert 5
insert 2
insert 3
insert 1
delete 3
insert 6
delete 5
出力例 1
6 1 2

入力例 2
9
insert 5
insert 2
insert 3
insert 1
delete 3
insert 6
delete 5
deleteFirst
deleteLast
出力例 2
1
*/

/*
双方向連結リストの解説

【双方向連結リストとは】
各要素が「次の要素」と「前の要素」の両方へのポインタを持つデータ構造
先頭からも末尾からもアクセスでき、挿入・削除がO(1)で可能

【構造体の定義】
typedef struct Node {
    int key;              // データ
    struct Node *next;    // 次の要素へのポインタ
    struct Node *prev;    // 前の要素へのポインタ
} Node;

【基本操作】
1. insert(x): 先頭に新しい要素を追加
   - 新しいノードを作成
   - head の前に挿入
   
2. delete(x): 指定された値を持つ最初の要素を削除
   - リストを先頭から探索
   - 見つかったら前後のポインタを繋ぎ直す
   
3. deleteFirst(): 先頭の要素を削除
   - head を次の要素に移動
   
4. deleteLast(): 末尾の要素を削除
   - tail を前の要素に移動

【メモリ管理】
- insert時: malloc()で新しいノードを確保
- delete時: free()でメモリを解放（メモリリーク防止）
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 双方向連結リストのノード構造体
typedef struct Node {
    int key;
    struct Node *next;
    struct Node *prev;
} Node;

// ダミーノード（番兵）
Node *nil;

// 新しいノードを作成
Node* createNode(int key) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->next = nil;
    node->prev = nil;
    return node;
}

// リストの初期化（ダミーノードを使う方式）
void init() {
    nil = (Node *)malloc(sizeof(Node));
    nil->next = nil;
    nil->prev = nil;
}

// 先頭に挿入
void insert(int key) {
    Node *x = createNode(key);
    x->next = nil->next;
    nil->next->prev = x;
    nil->next = x;
    x->prev = nil;
}

// 指定したキーを持つ最初の要素を削除
void deleteKey(int key) {
    Node *cur = nil->next;
    while (cur != nil) {
        if (cur->key == key) {
            cur->prev->next = cur->next;
            cur->next->prev = cur->prev;
            free(cur);
            return;  // 最初の要素だけ削除
        }
        cur = cur->next;
    }
}

// 先頭の要素を削除
void deleteFirst() {
    if (nil->next == nil) return;
    Node *x = nil->next;
    nil->next = x->next;
    x->next->prev = nil;
    free(x);
}

// 末尾の要素を削除
void deleteLast() {
    if (nil->prev == nil) return;
    Node *x = nil->prev;
    x->prev->next = nil;
    nil->prev = x->prev;
    free(x);
}

// リストの内容を出力
void printList() {
    Node *cur = nil->next;
    int first = 1;
    while (cur != nil) {
        if (!first) printf(" ");
        printf("%d", cur->key);
        first = 0;
        cur = cur->next;
    }
    printf("\n");
}

int main(void) {
    int n, key;
    char command[20];
    
    scanf("%d", &n);
    init();
    
    for (int i = 0; i < n; i++) {
        scanf("%s", command);
        
        if (strcmp(command, "insert") == 0) {
            scanf("%d", &key);
            insert(key);
        } else if (strcmp(command, "delete") == 0) {
            scanf("%d", &key);
            deleteKey(key);
        } else if (strcmp(command, "deleteFirst") == 0) {
            deleteFirst();
        } else if (strcmp(command, "deleteLast") == 0) {
            deleteLast();
        }
    }
    
    printList();
    
    return 0;
}
