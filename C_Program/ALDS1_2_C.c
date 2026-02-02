/*
安定なソート
トランプのカードを整列しましょう。ここでは、４つの絵柄(S, H, C, D)と９つの数字(1, 2, ..., 9)から構成される計 36 枚のカードを用います。例えば、ハートの 8 は"H8"、ダイヤの 1 は"D1"と表します。

バブルソート及び選択ソートのアルゴリズムを用いて、与えられた N 枚のカードをそれらの数字を基準に昇順に整列するプログラムを作成してください。アルゴリズムはそれぞれ以下に示す疑似コードに従うものとします。数列の要素は 0 オリジンで記述されています。

1 BubbleSort(C, N)
2   for i = 0 to N-1
3     for j = N-1 downto i+1
4       if C[j].value < C[j-1].value
5         C[j] と C[j-1] を交換
6
7 SelectionSort(C, N)
8   for i = 0 to N-1
9     minj = i
10    for j = i to N-1
11      if C[j].value < C[minj].value
12        minj = j
13    C[i] と C[minj] を交換
また、各アルゴリズムについて、与えられた入力に対して安定な出力を行っているか報告してください。ここでは、同じ数字を持つカードが複数ある場合それらが入力に出現する順序で出力されることを、「安定な出力」と呼ぶことにします。（※常に安定な出力を行うソートのアルゴリズムを安定なソートアルゴリズムと言います。）

入力
1 行目にカードの枚数 N が与えられます。 2 行目に N 枚のカードが与えられます。各カードは絵柄と数字のペアを表す２文字であり、隣合うカードは１つの空白で区切られています。

出力
1 行目に、バブルソートによって整列されたカードを順番に出力してください。隣合うカードは１つの空白で区切ってください。
2 行目に、この出力が安定か否か（Stable またはNot stable）を出力してください。
3 行目に、選択ソートによって整列されたカードを順番に出力してください。隣合うカードは１つの空白で区切ってください。
4 行目に、この出力が安定か否か（Stable またはNot stable）を出力してください。

制約
1 ≤ N ≤ 36
入力例 1
5
H4 C9 S4 D2 C3
出力例 1
D2 C3 H4 S4 C9
Stable
D2 C3 S4 H4 C9
Not stable
入力例 2
2
S1 H1
出力例 2
S1 H1
Stable
S1 H1
Stable
*/

#include <stdio.h>

typedef struct {
	char suit;
	int value;
	int index;
} Card;

void printCards(Card A[], int N) {
	for (int i = 0; i < N; i++) {
		if (i > 0) printf(" ");
		printf("%c%d", A[i].suit, A[i].value);
	}
	printf("\n");
}

int isStable(Card A[], int N) {
	for (int i = 1; i < N; i++) {
		if (A[i - 1].value == A[i].value && A[i - 1].index > A[i].index) {
			return 0;
		}
	}
	return 1;
}

void bubbleSort(Card A[], int N) {
	for (int i = 0; i < N; i++) {
		for (int j = N - 1; j >= i + 1; j--) {
			if (A[j].value < A[j - 1].value) {
				Card tmp = A[j];
				A[j] = A[j - 1];
				A[j - 1] = tmp;
			}
		}
	}
}

void selectionSort(Card A[], int N) {
	for (int i = 0; i < N; i++) {
		int minj = i;
		for (int j = i; j < N; j++) {
			if (A[j].value < A[minj].value) {
				minj = j;
			}
		}
		if (i != minj) {
			Card tmp = A[i];
			A[i] = A[minj];
			A[minj] = tmp;
		}
	}
}

int main(void) {
	int N;
	scanf("%d", &N);

	Card original[36];
	for (int i = 0; i < N; i++) {
		char s;
		int v;
		scanf(" %c%d", &s, &v);
		original[i].suit = s;
		original[i].value = v;
		original[i].index = i;
	}

	Card bubble[36];
	Card select[36];
	for (int i = 0; i < N; i++) {
		bubble[i] = original[i];
		select[i] = original[i];
	}

	bubbleSort(bubble, N);
	printCards(bubble, N);
	printf(isStable(bubble, N) ? "Stable\n" : "Not stable\n");

	selectionSort(select, N);
	printCards(select, N);
	printf(isStable(select, N) ? "Stable\n" : "Not stable\n");

	return 0;
}