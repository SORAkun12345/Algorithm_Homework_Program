/*
連結成分分解
SNS の友達関係を入力し、双方向の友達リンクを経由してある人からある人へたどりつけるかどうかを判定するプログラムを作成してください。

入力
１行目にSNS のユーザ数を表す整数 
 と友達関係の数 
 が空白区切りで与えられます。SNS の各ユーザには 0 から 
 までのID が割り当てられています。

続く 
 行に１つの友達関係が各行に与えられます。１つの友達関係は空白で区切られた２つの整数 
、
 で与えられ、
 と 
 が友達であることを示します。

続く１行に、質問の数 
 が与えられます。続く
 行に質問が与えられます。 各質問は空白で区切られた２つの整数 
、
 で与えられ、「
 から 
 へたどり着けますか？」という質問を意味します。

出力
各質問に対して 
 から 
 にたどり着ける場合は yes と、たどり着けない場合は no と１行に出力してください。

制約
入力例
10 9
0 1
0 2
3 4
5 7
5 6
6 7
6 8
7 8
8 9
3
0 1
5 9
1 3
出力例
yes
yes
no
*/

/*
連結成分分解の解説

【問題の本質】
SNSの友達関係をグラフで表現
→ 2人が同じ連結成分に属しているかを高速に判定

【Union-Find（素集合データ構造）とは】
複数のグループ（連結成分）を管理するデータ構造

操作:
1. find(x): xが属するグループの代表元を返す
2. union(x, y): xとyを同じグループに統合

【Union-Findの原理】

親ポインタ配列 parent[] を使用：
- parent[i] = i の親ノード番号
- parent[x] = x の場合、xが根（代表元）

例: 0-1, 0-2, 3-4 の友達関係

初期状態:
parent = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]

union(0, 1):
  root(0)=0, root(1)=1
  parent[1] = 0
  parent = [0, 0, 2, 3, 4, 5, 6, 7, 8, 9]

union(0, 2):
  root(0)=0, root(2)=2
  parent[2] = 0
  parent = [0, 0, 0, 3, 4, 5, 6, 7, 8, 9]

union(3, 4):
  root(3)=3, root(4)=4
  parent[4] = 3
  parent = [0, 0, 0, 3, 3, 5, 6, 7, 8, 9]

質問 find(0) == find(1):
  root(0) = 0, root(1) = 0
  → 同じグループ → yes

質問 find(1) == find(3):
  root(1) = 0, root(3) = 3
  → 異なるグループ → no

【最適化: 経路圧縮（Path Compression）】
find(x) を呼び出すとき、パス上の全ノードを直接根に繋ぎ直す
→ 次回以降の find が高速化

【計算量（経路圧縮なし）】
find: O(n) - 最悪の場合、チェーン全体を走査
union: O(n) - find を2回呼び出し

【計算量（経路圧縮あり）】
find: ほぼ O(1) - 平均的に高速
union: ほぼ O(1) - 平均的に高速

【具体例: 10ユーザー、9つの友達関係】

入力:
0-1, 0-2, 3-4, 5-7, 5-6, 6-7, 6-8, 7-8, 8-9

処理:
union(0,1) → {0,1}
union(0,2) → {0,1,2}
union(3,4) → {3,4}
union(5,7) → {5,7}
union(5,6) → {5,6,7}
union(6,7) → {5,6,7}（既に同じグループ）
union(6,8) → {5,6,7,8}
union(7,8) → {5,6,7,8}（既に同じグループ）
union(8,9) → {5,6,7,8,9}

連結成分: {0,1,2}, {3,4}, {5,6,7,8,9}

質問:
0と1: find(0)==find(1) → yes
5と9: find(5)==find(9) → yes
1と3: find(1)==find(3) → no
*/

#include <stdio.h>

#define MAX_N 100001

int parent[MAX_N];

// 代表元（根）を見つける関数
// 経路圧縮を使用して最適化
int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);  // 経路圧縮
    }
    return parent[x];
}

// 2つの要素を同じグループに統合
void unite(int x, int y) {
    int root_x = find(x);
    int root_y = find(y);
    
    if (root_x != root_y) {
        parent[root_x] = root_y;  // xの根をyの根に繋ぎ替え
    }
}

int main(void) {
    int n, m;
    scanf("%d %d", &n, &m);
    
    // 初期化: 各要素が独立したグループ
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }
    
    // 友達関係を処理（グループ化）
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        unite(x, y);
    }
    
    // 質問に答える
    int q;
    scanf("%d", &q);
    
    for (int i = 0; i < q; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        
        if (find(x) == find(y)) {
            printf("yes\n");
        } else {
            printf("no\n");
        }
    }
    
    return 0;
}