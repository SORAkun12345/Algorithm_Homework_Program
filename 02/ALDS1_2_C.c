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

#include<stdio.h>
#include<string.h>

typedef struct{
    char suit;
    int value;
} Card;

// 関数のプロトタイプ宣言（mainやisStableから呼ぶために必要）
void bubbleSort(Card x[], int n);
void selectionSort(Card x[], int n);

// ソート実行と安定性判定を行う関数
void runSortsAndCheck(Card x[], int n){
    Card b[n], s[n];
    
    // 配列のコピーを作成
    for(int i = 0; i < n; i++){
        b[i] = x[i];
        s[i] = x[i];
    }

    // それぞれソートを実行
    bubbleSort(b, n);
    selectionSort(s, n);

    // --- バブルソートの結果出力 ---
    for(int i = 0; i < n; i++){
        if(i > 0) printf(" ");
        printf("%c%d", b[i].suit, b[i].value);
    }
    printf("\n");
    // バブルソートは常に安定なので無条件でStable
    printf("Stable\n");

    // --- 選択ソートの結果出力 ---
    for(int i = 0; i < n; i++){
        if(i > 0) printf(" ");
        printf("%c%d", s[i].suit, s[i].value);
    }
    printf("\n");

    // --- 選択ソートの安定性チェック ---
    // バブルソート（安定）の結果と比較して、全く同じならStable
    int isSelectionStable = 1;
    for(int i = 0; i < n; i++){
        // 絵柄が違っていたら、順序が変わってしまったということ
        if(b[i].suit != s[i].suit){
            isSelectionStable = 0;
            break;
        }
    }

    if(isSelectionStable){
        printf("Stable\n");
    } else {
        printf("Not stable\n");
    }
}

void bubbleSort(Card x[], int n){
    int flag = 1;
    while(flag){
        flag = 0;
        for(int i = n - 1; i > 0; i--){
            if(x[i].value < x[i - 1].value){
                // 【重要】構造体ごと交換する
                Card temp = x[i];
                x[i] = x[i - 1];
                x[i - 1] = temp;
                flag = 1;
            }
        }
    }
}

void selectionSort(Card x[], int n){
    int minj;
    for(int i = 0; i < n; i++){
        minj = i;
        for(int j = i; j < n; j++){
            if(x[j].value < x[minj].value){
                minj = j;
            }
        }
        if(i != minj){ // 交換が必要なときだけ
            // 【重要】構造体ごと交換する
            Card temp = x[minj];
            x[minj] = x[i];
            x[i] = temp;
        }
    }
}

int main(){
    int n;
    scanf("%d", &n);

    Card x[n];
    for(int i = 0; i < n; i++){
        // " %c" の前のスペースが空白読み飛ばしのカギ
        scanf(" %c%d", &x[i].suit, &x[i].value);
    }

    runSortsAndCheck(x, n);

    return 0;
}