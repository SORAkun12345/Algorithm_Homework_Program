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

// カード構造体: 絵柄、数字、入力時の元々の位置を記録
typedef struct {
	char suit;  // カードの絵柄 (S, H, C, D)
	int value;  // カードの数字 (1-9)
	int index;  // 入力時の元々の位置（安定性判定に使用）
} Card;

// カード配列を画面に出力する関数
void printCards(Card A[], int N) {
	for (int i = 0; i < N; i++) {
		if (i > 0) printf(" ");  // 1番目以降の前にスペースを挿入
		printf("%c%d", A[i].suit, A[i].value);  // 絵柄と数字を出力
	}
	printf("\n");
}

// ソート結果が安定か判定する関数
// 安定: 同じ値を持つ要素が入力順を保持している
// 不安定: 同じ値を持つ要素の相対順位が変わっている
int isStable(Card A[], int N) {
	for (int i = 1; i < N; i++) {
		// 隣接するカードが同じ数字を持つ場合
		if (A[i - 1].value == A[i].value && A[i - 1].index > A[i].index) {
			// 後ろのカードが前のカードより元々前にあった = 順序が入れ替わった = 不安定
			return 0;
		}
	}
	// すべてのチェックをパスした = 安定
	return 1;
}

// バブルソートでカード配列を数字で昇順に並び変える
void bubbleSort(Card A[], int N) {
	// 外側ループ: 各位置で1つのカードをソート済み部分に確定させる
	for (int i = 0; i < N; i++) {
		// 内側ループ: 末尾から i+1 までを比較し、小さい値を前に移動させる
		for (int j = N - 1; j >= i + 1; j--) {
			// 隣接するカードの数字を比較
			if (A[j].value < A[j - 1].value) {
				// 数字が小さい方を前に移す（交換）
				Card tmp = A[j];
				A[j] = A[j - 1];
				A[j - 1] = tmp;
			}
		}
	}
}

// 選択ソートでカード配列を数字で昇順に並び変える
void selectionSort(Card A[], int N) {
	for (int i = 0; i < N; i++) {
		// i 番目の位置に置くカードを探す
		int minj = i;  // 現在の最小値の位置を i に初期化
		// i から N-1 までの範囲で最小値を探す
		for (int j = i; j < N; j++) {
			if (A[j].value < A[minj].value) {
				minj = j;  // より小さい値が見つかれば位置を更新
			}
		}
		// 最小値を i 番目に移動（交換）
		if (i != minj) {
			Card tmp = A[i];
			A[i] = A[minj];
			A[minj] = tmp;
		}
	}
}

int main(void) {
	int N;
	// カードの枚数を読み込む
	scanf("%d", &N);

	// 元のカード配列（バブルソートと選択ソート用のコピー元）
	Card original[36];
	// 各カードのデータを読み込む
	for (int i = 0; i < N; i++) {
		char s;
		int v;
		scanf(" %c%d", &s, &v);  // 絵柄と数字を読み込む
		original[i].suit = s;
		original[i].value = v;
		original[i].index = i;  // 元々の位置を記録（安定性判定用）
	}

	// バブルソート用、選択ソート用のコピー配列
	Card bubble[36];
	Card select[36];
	// 元の配列をコピー
	for (int i = 0; i < N; i++) {
		bubble[i] = original[i];
		select[i] = original[i];
	}

	// バブルソートを実行
	bubbleSort(bubble, N);
	printCards(bubble, N);  // ソート済みカードを出力
	printf(isStable(bubble, N) ? "Stable\n" : "Not stable\n");  // 安定性を判定・出力

	// 選択ソートを実行
	selectionSort(select, N);
	printCards(select, N);  // ソート済みカードを出力
	printf(isStable(select, N) ? "Stable\n" : "Not stable\n");  // 安定性を判定・出力

	return 0;
}