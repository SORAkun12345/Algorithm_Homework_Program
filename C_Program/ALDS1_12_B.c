/*
単一始点最短経路 I - ダイクストラ法

ダイクストラ法は、重み付き有向グラフにおいて、
始点から各頂点への最短経路を求めるアルゴリズムです。

アルゴリズムの流れ:
1. 始点の距離を0、他の頂点の距離を無限大(未確定)に初期化
2. 未訪問の頂点の中で、距離が最小の頂点uを選択
3. uを訪問済みにする
4. uから到達可能な各頂点vについて、距離を更新（緩和操作）
   dist[v] = min(dist[v], dist[u] + weight(u,v))
5. 全頂点が訪問済みになるまで2-4を繰り返す

時間計算量: O(V^2)（優先度付きキューなしの実装）
空間計算量: O(V^2)（隣接行列使用）

注意: このアルゴリズムは辺の重みが非負の場合のみ正しく動作します
*/

#include <stdio.h>
#include <stdbool.h>

#define MAX_N 100
#define INF -1  // 到達不可能を表す

int adj[MAX_N][MAX_N];  // 隣接行列（0は辺なし）
int dist[MAX_N];         // 始点からの最短距離
bool visited[MAX_N];     // 訪問済みフラグ

// ダイクストラ法による最短経路の計算
void dijkstra(int n) {
    // 初期化
    for (int i = 0; i < n; i++) {
        dist[i] = INF;       // 初期状態では到達不可能
        visited[i] = false;  // 未訪問
    }
    
    // 始点（頂点0）の距離を0に設定
    dist[0] = 0;
    
    // n回のループで全頂点を処理
    for (int i = 0; i < n; i++) {
        int u = -1;
        int minDist = INF;
        
        // 未訪問かつ距離が確定している頂点の中で最小距離の頂点を選択
        for (int v = 0; v < n; v++) {
            if (!visited[v] && dist[v] != INF) {
                if (u == -1 || dist[v] < minDist) {
                    minDist = dist[v];
                    u = v;
                }
            }
        }
        
        // 到達可能な未訪問頂点がなければ終了
        if (u == -1) break;
        
        // 選択した頂点を訪問済みにする
        visited[u] = true;
        
        // uから到達可能な頂点の距離を更新（緩和操作）
        for (int v = 0; v < n; v++) {
            if (adj[u][v] != 0) {  // 辺が存在する場合
                int newDist = dist[u] + adj[u][v];
                // より短い経路が見つかった場合、距離を更新
                if (dist[v] == INF || newDist < dist[v]) {
                    dist[v] = newDist;
                }
            }
        }
    }
    
    // 結果の出力
    for (int i = 0; i < n; i++) {
        printf("%d %d\n", i, dist[i]);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    
    // 隣接行列の初期化（0で初期化）
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adj[i][j] = 0;
        }
    }
    
    // グラフの入力（隣接リスト形式）
    for (int i = 0; i < n; i++) {
        int u, k;
        scanf("%d %d", &u, &k);  // 頂点番号uと隣接頂点の数k
        
        // k個の隣接頂点とその辺の重みを入力
        for (int j = 0; j < k; j++) {
            int v, c;
            scanf("%d %d", &v, &c);  // 隣接頂点vと辺の重みc
            adj[u][v] = c;
        }
    }
    
    // ダイクストラ法の実行
    dijkstra(n);
    
    return 0;
}
