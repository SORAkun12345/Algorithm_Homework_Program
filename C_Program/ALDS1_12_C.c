/*
単一始点最短経路 II
与えられた重み付き有向グラフ 
 について、単一始点最短経路のコストを求めるプログラムを作成してください。
 の頂点 
 を始点とし、
 から各頂点 
 について、最短経路上の辺の重みの総和 
 を出力してください。

入力
最初の行に 
 の頂点数 
 が与えられます。続く 
 行で各頂点 
 の隣接リストが以下の形式で与えられます：

 
 
 
 
 
 ... 
 

 の各頂点には 
 から 
 の番号がふられています。
 は頂点の番号であり、
 は 
 の出次数を示します。
 は 
 に隣接する頂点の番号であり、
 は 
 と 
 をつなぐ有向辺の重みを示します。

出力
各頂点の番号 
 と距離 
 を１つの空白区切りで順番に出力してください。

制約
0 から各ノードへは必ず経路が存在する
入力例 1
5
0 3 2 3 3 1 1 2
1 2 0 2 3 4
2 3 0 3 3 1 4 1
3 4 2 1 0 1 1 4 4 3
4 2 2 1 3 3
出力例 1
0 0
1 2
2 2
3 1
4 3

参考文献
Introduction to Algorithms, Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, and Clifford Stein. The MIT Press.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QMAX 35000
typedef struct { int t, s; } QUE;
QUE que[QMAX]; 
int qsize;

#define PARENT(i) ((i)>>1)
#define LEFT(i)   ((i)<<1)
#define RIGHT(i)  (((i)<<1)+1)

void min_heapify(int i) {
    int l, r, min;
    QUE qt;

    l = LEFT(i), r = RIGHT(i);
    if (l < qsize && que[l].t < que[i].t) min = l; else min = i;
    if (r < qsize && que[r].t < que[min].t) min = r;
    if (min != i) {
        qt = que[i], que[i] = que[min], que[min] = qt;
        min_heapify(min);
    }
}

void deq() {
    que[0] = que[--qsize];
    min_heapify(0);
}

void enq(int s, int t) {
    int i, min;
    QUE qt;

    i = qsize++;
    que[i].s = s, que[i].t = t;
    while (i > 0 && que[min = PARENT(i)].t > que[i].t) {
        qt = que[i], que[i] = que[min], que[min] = qt;
        i = min;
    }
}

#define INF   0x30303030
#define MAX_V 10002
int hi[MAX_V], *to[MAX_V], *dd[MAX_V];
int dist[MAX_V];

void dijkstra(int n, int start) {
    int i, s, e, t, nt;

    memset(dist, INF, n << 2);
    qsize = 0;
    dist[start] = 0, enq(start, 0);
    while (qsize) {
        s = que[0].s, t = que[0].t, deq();
        if (dist[s] < t) continue;
        for (i = 0; i < hi[s]; i++) {
            e = to[s][i], nt = t + dd[s][i];
            if (dist[e] > nt) dist[e] = nt, enq(e, nt);
        }
    }
}

#if 1
#define gc() getchar_unlocked()
#define pc(c) putchar_unlocked(c)
#else
#define gc() getchar()
#define pc(c) putchar(c)
#endif

int in() {
    int n = 0, c = gc();
    do n = 10*n + (c & 0xf), c = gc(); while (c >= '0');
    return n;
}

void out(int n) {
    int i;
    char ob[20];

    if (!n) { pc('0'); return; }
    i = 0; while (n) ob[i++] = n%10 + '0', n/=10;
    while (i--) pc(ob[i]); 
}

int main() {
    int n, i, j, k, u;

    n = in();
    for (i = 0; i < n; i++) {
        u = in(), hi[u] = k = in();
        to[u] = malloc(k<<2);
        dd[u] = malloc(k<<2);
        for (j = 0; j < k; j++) {
            to[u][j] = in(), dd[u][j] = in();
        }
    }
    dijkstra(n, 0);
    for (i = 0; i < n; i++) {
        out(i), pc(' '), out(dist[i]), pc('\n');
    }
    return 0;
}
