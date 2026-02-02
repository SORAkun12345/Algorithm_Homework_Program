/*
辞書
以下の命令を実行する簡易的な「辞書」を実装してください。

insert 
: 辞書に 
 を追加する。
find 
: 辞書に 
 が含まれる場合 'yes'と、含まれない場合 'no'と出力する。
入力
最初の行に命令の数 
 が与えられます。続く 
 行に 
 件の命令が順番に与えられます。命令の形式は上記のとおりである。

出力
各 find 命令について、yes または no を１行に出力してください。

制約
与えられる文字列は、'A', 'C', 'G', 'T' の４種類の文字から構成される。
文字列の長さ
入力例 1
6
insert AAA
insert AAC
find AAA
find CCC
insert CCC
find CCC
出力例 1
yes
no
yes
入力例 2
13
insert AAA
insert AAC
insert AGA
insert AGG
insert TTT
find AAA
find CCC
find CCC
insert CCC
find CCC
insert T
find TTT
find T
出力例 2
yes
no
no
yes
yes
yes
*/

/*
辞書（ハッシュテーブル）の解説

【問題の特性】
- 文字列は'A', 'C', 'G', 'T'の4文字のみで構成
- 文字列長は最大12文字
- この制約を活かして効率的なハッシュ関数を設計可能

【ハッシュテーブルとは】
キーと値のペアを格納するデータ構造
ハッシュ関数でキーを数値（インデックス）に変換し、配列に格納
平均的にO(1)で挿入・検索が可能

【ハッシュ関数の設計】
各文字を以下のように数値化:
  'A' → 1, 'C' → 2, 'G' → 3, 'T' → 4
文字列全体を5進数とみなして数値化:
  例: "AC" → 1*5 + 2 = 7
  例: "ACG" → 1*5² + 2*5 + 3 = 38

【衝突（collision）の解決】
チェイン法: 同じハッシュ値を持つ要素を連結リストで管理
  例: hash(key1) == hash(key2) の場合、両方を同じリストに追加

【具体例】
insert AAA: hash("AAA") = 1*25 + 1*5 + 1 = 31
            H[31]のリストに"AAA"を追加
find AAA:   hash("AAA") = 31
            H[31]のリストを探索 → "AAA"が見つかる → "yes"
find CCC:   hash("CCC") = 2*25 + 2*5 + 2 = 62
            H[62]のリストを探索 → 空 → "no"

【ハッシュテーブルのサイズ】
文字列長12、4文字 → 最大4^12 = 16777216通り
実際にはそこまで必要ないので、適切なサイズ(1046527)を選択
素数を選ぶことで衝突を減らせる
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define M 1046527  // ハッシュテーブルのサイズ（素数）
#define L 14       // 文字列の最大長+2

// 連結リストのノード構造体
typedef struct Node {
    char key[L];
    struct Node *next;
} Node;

// ハッシュテーブル（連結リストの配列）
Node *H[M];

// 文字を数値に変換
int getChar(char ch) {
    if (ch == 'A') return 1;
    if (ch == 'C') return 2;
    if (ch == 'G') return 3;
    if (ch == 'T') return 4;
    return 0;
}

// 文字列をハッシュ値に変換
long long getKey(char str[]) {
    long long sum = 0, p = 1;
    for (int i = 0; i < strlen(str); i++) {
        sum += p * getChar(str[i]);
        p *= 5;
    }
    return sum;
}

// ハッシュ値からインデックスを計算
int h(long long key) {
    return key % M;
}

// 辞書に文字列を挿入
void insert(char str[]) {
    long long key = getKey(str);
    int index = h(key);
    
    // 既に存在するかチェック
    Node *cur = H[index];
    while (cur != NULL) {
        if (strcmp(cur->key, str) == 0) {
            return; // 既に存在する場合は何もしない
        }
        cur = cur->next;
    }
    
    // 新しいノードを作成して先頭に追加
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->key, str);
    newNode->next = H[index];
    H[index] = newNode;
}

// 辞書に文字列が存在するか検索
int find(char str[]) {
    long long key = getKey(str);
    int index = h(key);
    
    Node *cur = H[index];
    while (cur != NULL) {
        if (strcmp(cur->key, str) == 0) {
            return 1; // 見つかった
        }
        cur = cur->next;
    }
    return 0; // 見つからない
}

int main(void) {
    int n;
    scanf("%d", &n);
    
    // ハッシュテーブルの初期化
    for (int i = 0; i < M; i++) {
        H[i] = NULL;
    }
    
    for (int i = 0; i < n; i++) {
        char command[10], str[L];
        scanf("%s %s", command, str);
        
        if (strcmp(command, "insert") == 0) {
            insert(str);
        } else if (strcmp(command, "find") == 0) {
            if (find(str)) {
                printf("yes\n");
            } else {
                printf("no\n");
            }
        }
    }
    
    return 0;
}
