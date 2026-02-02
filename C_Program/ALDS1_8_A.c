/*
二分探索木I
探索木は、挿入、検索、削除などの操作が行えるデータ構造で、辞書あるいは優先度付きキューとして用いることができます。探索木の中でも最も基本的なものが二分探索木です。二分探索木は、各節点にキーを持ち、次に示す二分探索木条件(Binary search tree property) を常に満たすように構築されます：

 を２分探索木に属するある節点とする。 
 を 
 の左部分木に属する節点とすると、
 のキー 
のキーである。また、
 を 
 の右部分木に属する節点とすると、
 のキー 
 のキーである。
次の図は二分探索木の例です。



例えば、キーが80の節点の左部分木に属する節点のキーは80以下であり、右部分木に属する節点のキーは80以上になっています。二分探索木に中間順巡回を行うと、昇順に並べられたキーの列を得ることができます。

二分探索木は、データの挿入や削除が行われても常にこのような条件が全ての節点で成り立つように実装しなければなりません。リストと同様に、節点をポインタで連結することで木を表し、各節点には値（キー）に加えその親、左の子、右の子へのポインタを持たせます。

二分探索木 
 に新たに値 
 を挿入するには以下の疑似コードに示す insert を実行します。insert は、キーが 
、左の子が 
、右の子が 
 であるよな節点 
 を受け取り、
 の正しい位置に挿入します。

1 insert(T, z)
2     y = NIL // x の親
3     x = 'T の根'
4     while x ≠ NIL
5         y = x // 親を設定
6         if z.key < x.key
7             x = x.left // 左の子へ移動
8         else 
9             x = x.right // 右の子へ移動
10    z.p = y
11
12    if y == NIL // T が空の場合
13        'T の根' = z
14    else if z.key < y.key
15        y.left = z // z を y の左の子にする
16    else 
17        y.right = z // z を y の右の子にする
二分探索木 
 に対し、以下の命令を実行するプログラムを作成してください。

insert 
: 
にキー 
 を挿入する。
print: キーを木の中間順巡回(inorder tree walk)と先行順巡回(preorder tree walk)アルゴリズムで出力する。
挿入のアルゴリズムは上記疑似コードに従ってください。

入力
入力の最初の行に、命令の数 
 が与えられます。続く 
 行目に、insert 
 または print の形式で命令が１行に与えられます。

出力
print命令ごとに、中間順巡回アルゴリズム、先行順巡回アルゴリズムによって得られるキーの順列をそれぞれ１行に出力してください。各キーの前に１つの空白を出力してください。

制約
命令の数は 
 を超えない。
print 命令の数は 
 を超えない。
キー
上記の疑似コードのアルゴリズムに従う場合、木の高さは 100 を超えない。
二分探索木中のキーに重複は発生しない。
入力例 1
8
insert 30
insert 88
insert 12
insert 1
insert 20
insert 17
insert 25
print
出力例 1
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

// 新しいノードを作成して初期化する
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

// 擬似コードの insert に従って BST に挿入する
void insert_node(Node *z) {
	Node *y = NULL;
	Node *x = root;

	// 挿入位置を探索
	while (x != NULL) {
		y = x;
		if (z->key < x->key) {
			x = x->left;
		} else {
			x = x->right;
		}
	}

	// 親を設定し、親の左/右にぶら下げる
	z->parent = y;
	if (y == NULL) {
		root = z;
	} else if (z->key < y->key) {
		y->left = z;
	} else {
		y->right = z;
	}
}

// 中間順巡回（昇順に出力される）
void inorder(Node *u) {
	if (u == NULL) return;
	inorder(u->left);
	printf(" %d", u->key);
	inorder(u->right);
}

// 先行順巡回（根→左→右）
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
			// insert x: x を BST に挿入
			int key;
			scanf("%d", &key);
			Node *z = create_node(key);
			insert_node(z);
		} else if (strcmp(cmd, "print") == 0) {
			// print: 中間順 → 先行順 の順に出力
			inorder(root);
			printf("\n");
			preorder(root);
			printf("\n");
		}
	}

	return 0;
}

