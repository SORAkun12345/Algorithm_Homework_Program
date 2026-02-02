/*
最小全域木（Minimum Spanning Tree）- プリム法

最小全域木とは、重み付き無向グラフの全頂点を含む木のうち、
辺の重みの総和が最小となるものです。

プリム法のアルゴリズム:
1. 始点を選び、その頂点を訪問済みとする
2. 訪問済み頂点から未訪問頂点への辺のうち、最小コストの辺を選ぶ
3. その辺で繋がる未訪問頂点を訪問済みにし、辺のコストを総和に加える
4. 全頂点が訪問済みになるまで2-3を繰り返す

時間計算量: O(V^2)（隣接行列使用時）
*/

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_N 100

int Weight[MAX_N+1][MAX_N+1];  // 隣接行列（重み）
int minCost[MAX_N+1];           // 各頂点への最小コスト
bool visited[MAX_N+1];          // 訪問済みフラグ

// プリム法による最小全域木のコスト計算
int prim(int n) {
    int totalCost = 0;
    
    // 初期化：全頂点の最小コストを無限大に設定
    for (int i = 1; i <= n; i++) {
        minCost[i] = INT_MAX;
        visited[i] = false;
    }
    
    // 始点（頂点1）のコストを0に設定
    minCost[1] = 0;
    
    // n個の頂点を順番に木に追加
    for (int i = 0; i < n; i++) {
        int u = -1;
        int minWeight = INT_MAX;
        
        // 未訪問の頂点の中で最小コストの頂点を選択
        for (int v = 1; v <= n; v++) {
            if (!visited[v] && minCost[v] < minWeight) {
                minWeight = minCost[v];
                u = v;
            }
        }
        
        // 選択した頂点を訪問済みにし、コストを加算
        visited[u] = true;
        totalCost += minWeight;
        
        // 選択した頂点から到達可能な未訪問頂点の最小コストを更新
        for (int v = 1; v <= n; v++) {
            if (!visited[v] && Weight[u][v] != -1 && Weight[u][v] < minCost[v]) {
                minCost[v] = Weight[u][v];
            }
        }
    }
    
    return totalCost;
}

int main() {
    int n;
    scanf("%d", &n);
    
    // 隣接行列の入力（-1は辺が存在しないことを表す）
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &Weight[i][j]);
        }
    }
    
    // 最小全域木のコストを計算して出力
    int result = prim(n);
    printf("%d\n", result);
    
    return 0;
}
