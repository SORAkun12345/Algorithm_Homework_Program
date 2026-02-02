/*
８パズル
8 パズルは１つの空白を含む 
 のマス上に 8 枚のパネルが配置され、空白を使ってパネルを上下左右にスライドさせ、絵柄を揃えるパズルです。

この問題では、次のように空白を 0、各パネルを 1 から 8 の番号でパズルを表します。

1 3 0
4 2 5
7 8 6
1 回の操作で空白の方向に１つのパネルを移動することができ、ゴールは次のようなパネルの配置とします。

1 2 3
4 5 6
7 8 0
８パズルの初期状態が与えられるので、ゴールまでの最短手数を求めるプログラムを作成してください。

入力
入力はパネルの数字あるいは空白を表す 
　個の整数です。空白で区切られた 3 つの整数が 3 行で与えられます。

出力
最短手数を１行に出力してください。

制約
与えられるパズルは必ず解くことができる。
入力例
1 3 0
4 2 5
7 8 6
出力例
4
*/

#include <stdio.h>

typedef unsigned char uchar;

#define HASHSIZ 543217
typedef struct { unsigned s; char x, v; } HASH;
HASH hash[HASHSIZ+3], *hashend = hash+HASHSIZ;

int lookup(unsigned s, int x)
{
	long long t = ((long long)x << 32) + s;
	HASH *hp = hash + (int)(t % HASHSIZ);
	while (hp->s) {
		if (hp->s == s && hp->x == x) return hp->v;
		if (++hp == hashend) hp = hash;
	}
	return 0;
}

void insert(unsigned s, int x, char v)
{
	long long t = ((long long)x << 32) + s;
	HASH *hp = hash + (int)(t % HASHSIZ);
	while (hp->s) {
		if (hp->s == s && hp->x == x) { hp->v = v; break; }
		if (++hp == hashend) hp = hash;
	}
	hp->s = s, hp->x = x, hp->v = v;
}

#define QMAX 50000
typedef struct { unsigned s; char x, v; } T;
T s[QMAX+3]; int top, end;
int hi[9] = {2,3,2,3,4,3,2,3,2};
int to[9][4] = {{1,3},{0,2,4},{1,5},{0,4,6},{1,3,5,7},{2,4,8},{3,7},{4,6,8},{5,7}};

void toArray(char *nine, unsigned s, int x)
{
	int i;
	
	for (i = 8; i >= 0; i--) {
		if (i == x) nine[i] = 0;
		else nine[i] = s & 0xf, s >>= 4;
	}
}

unsigned swap(char *nine, int zero, int nx)
{
	int i;
	unsigned res;
	
	res = 0;
	for (i = 0; i < 9; i++) {
		if      (i == zero) res <<= 4, res |= nine[nx];
		else if (i != nx)   res <<= 4, res |= nine[i];
	}
	return res;
}

#define MAGIC 20

int main()
{
	int i, x, nx, v, nv, t;
	unsigned a, na;
	unsigned gs; int gx;
	char nine[9];
	
	gs = 0; for (i = 0; i < 9; i++) {
		scanf("%d", &t);
		if (t == 0) gx = i;
		else gs <<= 4, gs |= t;
	}
	s[0].s = 0x12345678, s[0].x = 8;
	s[1].x = -1;
	top = 0, end = 2;
	insert(s[0].s, s[0].x, 0);
	v = 0;
	while (top != end) {
		a = s[top].s, x = s[top].x;
		if (++top == QMAX) top = 0; 
		if (x < 0) {
			if (v == MAGIC) break;
			v++;
			s[end].x = -1; if (++end == QMAX) end = 0;
			continue;
		}
		if (x == gx && a == gs) goto done;
		if (lookup(a, x) < v) continue;

		toArray(nine, a, x);
		for (i = 0; i < hi[x]; i++) {
			nx = to[x][i];
			na = swap(nine, x, nx), nv = v+1;
			t = lookup(na, nx);
			if (!t || nv < t) {
				s[end].s = na, s[end].x = nx;
				if (++end == QMAX) end = 0;
				insert(na, nx, nv);
			}
		}
	}

	s[0].s = gs, s[0].x = gx, s[1].x = -1;
	top = 0, end = 2;
	v = 0;
	while (top != end) {
		a = s[top].s, x = s[top].x;
		if (++top == QMAX) top = 0; 
		if (x < 0) {
			v++;
			s[end].x = -1; if (++end == QMAX) end = 0;
			continue;
		}
		if ((t = lookup(a, x)) > 0) { v += t; break; }

		toArray(nine, a, x);
		for (i = 0; i < hi[x]; i++) {
			nx = to[x][i];
			na = swap(nine, x, nx), nv = v+1;
			t = lookup(na, nx);
			if (!t || nv < t) {
				s[end].s = na, s[end].x = nx;
				if (++end == QMAX) end = 0;
			}
		}
	}
done:
	printf("%d\n", v);
	return 0;
}