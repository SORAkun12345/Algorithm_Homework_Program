/*
幅優先探索の解説

【BFSとは】
グラフの全頂点を訪問し、始点から各頂点への最短距離を求めるアルゴリズム
「できるだけ浅く」層ごとに探索（DFSとの対比）

【最短距離とは】
パス上の辺の本数の最小値

【キューを使う理由】
BFSではキュー（FIFO）を使用：
1. 始点をキューに入れる
2. キューから頂点uを取り出す
3. uから隣接する未訪問の頂点をキューに追加
4. 距離をインクリメント
5. キューが空になるまで繰り返す

DFSではスタック（LIFO）を使うのに対し、
BFSではキュー（FIFO）を使うことで層ごとの処理が実現できる

【具体例】
グラフ: 1→2, 1→4, 2→4, 4→3

開始頂点: 1

■初期化
dist[1]=0（始点の距離）
dist[2]=dist[3]=dist[4]=-1（未訪問）
キュー: [1]

■ステップ1: u=1 を取り出す
  隣接: 2, 4
  訪問(2): dist[2]=0+1=1, キュー: [2, 4]
  訪問(4): dist[4]=0+1=1, キュー: [2, 4]

■ステップ2: u=2 を取り出す
  隣接: 4
  4は既に訪問済み, キュー: [4]

■ステップ3: u=4 を取り出す
  隣接: 3
  訪問(3): dist[3]=1+1=2, キュー: [3]

■ステップ4: u=3 を取り出す
  隣接: なし, キュー: []

結果:
1: 距離 0
2: 距離 1
3: 距離 2
4: 距離 1

【計算量】
時間: O(V + E) - 各頂点と各辺を1回訪問
空間: O(V) - キューと距離配列

【実装のポイント】
1. キューで層ごとの処理を実現
2. 訪問済みかどうかを距離配列で判定（-1=未訪問）
3. 隣接する全未訪問頂点を同じ距離でキューに追加
4. 到達不可能な頂点は-1で出力
*/

#include <stdio.h>
#include <string.h>

#define MAX_V 101
#define QUEUE_SIZE 10001

int dist[MAX_V];      // 距離配列
int Adj[MAX_V][MAX_V]; // 隣接行列
int queue[QUEUE_SIZE]; // キュー
int queue_front = 0;
int queue_rear = 0;

// キューに要素を追加
void enqueue(int x) {
    queue[queue_rear++] = x;
}

// キューから要素を取り出す
int dequeue(void) {
    return queue[queue_front++];
}

// キューが空かどうかを判定
int is_empty(void) {
    return queue_front >= queue_rear;
}

// 幅優先探索
void bfs(int start, int n) {
    // 距離の初期化（-1: 未訪問）
    for (int i = 1; i <= n; i++) {
        dist[i] = -1;
    }
    
    dist[start] = 0;  // 始点の距離は0
    enqueue(start);
    
    while (!is_empty()) {
        int u = dequeue();
        
        // u から隣接する全ての頂点を探索
        for (int v = 1; v <= n; v++) {
            if (Adj[u][v] == 1 && dist[v] == -1) {
                dist[v] = dist[u] + 1;
                enqueue(v);
            }
        }
    }
}

int main(void) {
    int n;
    scanf("%d", &n);
    
    // 隣接行列を初期化
    memset(Adj, 0, sizeof(Adj));
    
    // 隣接リスト形式の入力を読み込む
    for (int i = 0; i < n; i++) {
        int u, k;
        scanf("%d %d", &u, &k);
        
        for (int j = 0; j < k; j++) {
            int v;
            scanf("%d", &v);
            Adj[u][v] = 1;
        }
    }
    
    // 頂点1から幅優先探索を開始
    bfs(1, n);
    
    // 結果を出力
    for (int i = 1; i <= n; i++) {
        printf("%d %d\n", i, dist[i]);
    }
    
    return 0;
}