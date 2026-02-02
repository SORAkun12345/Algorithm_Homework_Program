/*
１５パズル
15 パズルは１つの空白を含む 
 のマス上に 15 枚のパネルが配置され、空白を使ってパネルを上下左右にスライドさせ、絵柄を揃えるパズルです。

この問題では、次のように空白を 0、各パネルを 1 から 15 の番号でパズルを表します。

1 2 3 4
6 7 8 0
5 10 11 12
9 13 14 15
1 回の操作で空白の方向に１つのパネルを移動することができ、ゴールは次のようなパネルの配置とします。

1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 0
15 パズルの初期状態が与えられるので、ゴールまでの最短手数を求めるプログラムを作成してください。

入力
入力はパネルの数字あるいは空白を表す 
　個の整数です。空白で区切られた 4 つの整数が 4 行で与えられます。

出力
最短手数を１行に出力してください。

制約
与えられるパズルは 45 手以内で解くことができる。
入力例
1 2 3 4
6 7 8 0
5 10 11 12
9 13 14 15
出力例
8
*/

#include <stdio.h>

typedef unsigned long long ull;

#define QMAX 100000
typedef struct { ull s; char x, v; char t; } QUE;
QUE que[QMAX]; int qsize;

#define PARENT(i) ((i)>>1)
#define LEFT(i)   ((i)<<1)
#define RIGHT(i)  (((i)<<1)+1)

void min_heapify(int i)
{
	int l, r;
	int min;

	l = LEFT(i), r = RIGHT(i);
	if (l < qsize && que[l].t < que[i].t) min = l; else min = i;
	if (r < qsize && que[r].t < que[min].t) min = r;
	if (min != i) {
		QUE t = que[i]; que[i] = que[min]; que[min] = t;
		min_heapify(min);
	}
}

void deq()
{
  que[0] = que[--qsize];
  min_heapify(0);
}

void enq(ull s, int x, int v, int t)
{
	int i, min;
	QUE qt;

	i = qsize++;
	que[i].s = s, que[i].x = x, que[i].v = v, que[i].t = t;
	while (i > 0 && que[min = PARENT(i)].t > que[i].t) {
		qt = que[i]; que[i] = que[min]; que[min] = qt;
		i = min;
	}
}

#define HASHSIZ 200003
typedef struct { ull s; char v; } HASH;
HASH hash [HASHSIZ+3], *hashend  = hash +HASHSIZ;

int lookup(ull s)
{
	HASH *hp = hash + (int)(s % HASHSIZ);
	while (hp->s) {
		if (hp->s == s) return hp->v;
		if (++hp == hashend) hp = hash;
	}
	return -1;
}


void insert(ull s, char v)
{
	HASH *hp = hash + (int)(s % HASHSIZ);
	while (hp->s) {
		if (hp->s == s) { hp->v = v; break; }
		if (++hp == hashend) hp = hash;
	}
	hp->s = s, hp->v = v;
}

#define GOAL 0x123456789ABCDEF0LL
#define ABS(a) ((a)>=0?(a):-(a))

int hi[16] = {2,3,3,2,3,4,4,3,3,4,4,3,2,3,3,2};
int to[16][4] = {
{1,4},{0,2,5},{1,3,6},{2,7},
{0,5,8},{1,4,6,9},{2,5,7,10},{3,6,11},
{4,9,12},{5,8,10,13},{6,9,11,14},{7,10,15},
{8,13},{9,12,14},{10,13,15},{11,14}};
double magic = 1;

void toArray(char *p16, ull s)
{
	int i;
	
	for (i = 15; i >= 0; i--) {
		p16[i] = s & 0xf, s >>= 4;
	}
}

ull swap(char *p16, int zero, int nx)
{
	int i;
	ull res;
	
	res = 0;
	for (i = 0; i < 16; i++) {
		res <<= 4;
		if      (i == zero) res |= p16[nx];
		else if (i == nx)   res |= p16[zero];
		else                res |= p16[i];
	}
	return res;
}

int eval(ull s)
{
	int i, r1, c1, r2, c2;
	int e, t;

	e = 0;
	for (i = 15; i >= 0; i--) {
		t = s & 0xf, s >>= 4;
		if (t) {
			t--;
			r1 = i >> 2, c1 = i & 3;
			r2 = t >> 2, c2 = t & 3;
			e += ABS(r1-r2) + ABS(c1-c2);
		}
	}
	return (int)(e*magic);

}

int main()
{
	int i, x, nx, v, nv, t;
	ull s, ns;
	char p16[16];

	s = 0; for (i = 0; i < 16; i++) {
		scanf("%d", &t);
		p16[i] = t, s <<= 4, s |= t;
		if (t == 0) x = i;
	}
	qsize = 0;
	t = eval(s);
	if      (t <= 22) magic = 1.12;
	else if (t <= 25) magic = 1.14;
	else              magic = 1.28;

	enq(s, x, 0, (int)(t*magic));

	insert(s, 0);
	while (qsize) {
		s = que[0].s, x = que[0].x, v = que[0].v, deq();
		if (s == GOAL) break;
		if (lookup(s) < v) continue;

		toArray(p16, s);
		for (i = 0; i < hi[x]; i++) {
			nx = to[x][i];
			ns = swap(p16, x, nx), nv = v+1;
			t = lookup(ns);
			if (t < 1 || nv < t) {
				enq(ns, nx, nv, eval(ns)+v);
				insert(ns,  nv);
			}
		}
	}
	printf("%d\n", v);
	return 0;
}