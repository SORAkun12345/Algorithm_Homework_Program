/*
Areas on the Cross-Section Diagram
地域の治水対策として、洪水の被害状況をシミュレーションで仮想してみよう。

図のように 
 の区画からなる格子上に表された地域の模式断面図が与えられるので、地域にできる各水たまりの面積を報告してください。



与えられた地域に対して限りなく雨が降り、地域から溢れ出た水は左右の海に流れ出ると仮定します。 例えば、図の断面図では、左から面積が 4、2、1、19、9 の水たまりができます。

入力
模式断面図における斜面を '/' と '\'、平地を '_' で表した文字列が１行に与えられます。例えば、図の模式断面図は文字列 \\///\_/\/\\\\/_/\\///__\\\_\\/_\/_/\ で与えられます。

出力
次の形式で水たまりの面積を出力してください。


 
 
 ... 

１行目に地域にできる水たまりの総面積を表す整数 
 を出力してください。

２行目に水たまりの数 
、各水たまりの面積 
 を断面図の左から順番に空白区切りで出力してください。

制約
文字列の長さ
ただし、得点の 50 点分は以下の条件を満たす。

水たまりの数は１つ以下であり (
)、かつ文字列の長さは 100 以下である。
入力例 1
\\//
出力例 1
4
1 4

入力例 2
\\///\_/\/\\\\/_/\\///__\\\_\\/_\/_/\
出力例 2
35
5 4 2 1 19 9
*/

/*
断面図の水たまり面積計算の解説

【アルゴリズムの仕組み】
スタックを2つ使って、'\' と '/' の対応関係から水たまりを検出

【基本原理】
1. '\' (下り坂) の位置をスタックに記録
2. '/' (上り坂) が来たら、対応する '\' とペアを作る
   → この間の距離が水たまりの面積
3. 同じ谷の中にある複数の水たまりを統合（マージ）

【具体例】\\//
位置:  0 1 2 3
文字:  \ \ / /

処理:
位置0: '\' → s1にpush(0)
位置1: '\' → s1にpush(1)
位置2: '/' → s1からpop(1), 面積 = 2-1 = 1
             s2にpush(1, 1) ※(開始位置, 面積)
位置3: '/' → s1からpop(0), 面積 = 3-0 = 3
             s2に(1,1)が残っていて1>0なので統合
             統合後の面積 = 3 + 1 = 4
             s2にpush(0, 4)

結果: 総面積=4, 水たまり1個(面積4)

【マージの必要性】
\\//\// の場合:
- 最初の \\// で1つの水たまり
- 次の \// でもう1つの水たまり
- しかし実際は大きな1つの水たまりなので統合が必要

【2つのスタック】
s1_stack: '\' の出現位置を記録
s2_stack: (水たまりの左端, 面積) のペアを記録
*/

#include <stdio.h>
#include <string.h>

#define MAX_LEN 20001

// スタック1: '\' の位置を記録
int s1_stack[MAX_LEN];
int s1_top = 0;

// スタック2: (位置, 面積) のペアを記録
typedef struct {
    int pos;
    int area;
} Pair;

Pair s2_stack[MAX_LEN];
int s2_top = 0;

// スタック1の操作
void s1_push(int x) {
    s1_stack[s1_top++] = x;
}

int s1_pop() {
    return s1_stack[--s1_top];
}

int s1_empty() {
    return s1_top == 0;
}

// スタック2の操作
void s2_push(int pos, int area) {
    s2_stack[s2_top].pos = pos;
    s2_stack[s2_top].area = area;
    s2_top++;
}

Pair s2_pop() {
    return s2_stack[--s2_top];
}

int s2_empty() {
    return s2_top == 0;
}

Pair s2_top_pair() {
    return s2_stack[s2_top - 1];
}

int main(void) {
    char s[MAX_LEN];
    
    if (scanf("%s", s) != 1) {
        return 0;
    }
    
    int total_area = 0;
    int len = strlen(s);
    
    for (int j = 0; j < len; j++) {
        if (s[j] == '\\') {
            // 下り坂の位置をスタックに記録
            s1_push(j);
        } else if (s[j] == '/' && !s1_empty()) {
            // 上り坂が来たら、対応する下り坂を取り出す
            int i = s1_pop();
            
            // 現在の断面で形成される面積を計算
            int current_area = j - i;
            total_area += current_area;
            
            // マージ処理: 範囲 (i, j) 内に含まれる水たまりを統合
            while (!s2_empty() && s2_top_pair().pos > i) {
                Pair p = s2_pop();
                current_area += p.area;
            }
            
            // 統合された水たまりを記録
            s2_push(i, current_area);
        }
    }
    
    // 出力1: 総面積
    printf("%d\n", total_area);
    
    // 出力2: 水たまりの数と各面積
    // スタックから取り出すと逆順になるので、一度配列に移す
    int results[MAX_LEN];
    int count = 0;
    
    while (!s2_empty()) {
        Pair p = s2_pop();
        results[count++] = p.area;
    }
    
    // 逆順になっているので反転
    printf("%d", count);
    for (int i = count - 1; i >= 0; i--) {
        printf(" %d", results[i]);
    }
    printf("\n");
    
    return 0;
}
