/*
双方向連結リスト
以下の命令を受けつける双方向連結リストを実装してください。

insert x: 連結リストの先頭にキー x を持つ要素を継ぎ足す。
delete x: キー x を持つ最初の要素を連結リストから削除する。そのような要素が存在しない場合は何もしない。
deleteFirst: リストの先頭の要素を削除する。
deleteLast: リストの末尾の要素を削除する。
入力
入力は以下の形式で与えられます。

n
command1
command2
...
commandn
最初の行に命令数 n が与えられます。続く n 行に命令が与えられる。命令は上記4つの命令のいずれかです。キーは整数とします。

出力
全ての命令が終了した後の、連結リスト内のキーを順番に出力してください。連続するキーは１つの空白文字で区切って出力してください。

制約
命令数は 2,000,000 を超えない。
delete 命令の回数は 20 を超えない。
0 ≤ キーの値 ≤ 109。
命令の過程でリストの要素数は 106を超えない。
delete, deleteFirst, または deleteLast 命令が与えられるとき、リストには１つ以上の要素が存在する。
入力例 1
7
insert 5
insert 2
insert 3
insert 1
delete 3
insert 6
delete 5
出力例 1
6 1 2
入力例 2
9
insert 5
insert 2
insert 3
insert 1
delete 3
insert 6
delete 5
deleteFirst
deleteLast
出力例 2
1
*/

#include <cstdio>  // scanf, printf用
#include <list>    // 双方向連結リスト
#include <cstring> // strcmp用 (char配列の比較)
#include <algorithm> // std::find用

int main() {
    int n, x;
    char command[20]; // 文字列はchar配列で受けるのが高速で安全
    std::list<int> L; // vectorではなくlistを使う

    std::scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        std::scanf("%s", command); // まず命令だけ読む

        // insert x: 先頭に追加
        if (command[0] == 'i') {
            std::scanf("%d", &x); // ここで初めて数値が必要なら読む
            L.push_front(x);      // vectorにはない機能。爆速(O(1))
        }
        // deleteLast: 末尾削除 (deleteより先に判定しないと誤判定する)
        else if (std::strlen(command) > 6 && command[6] == 'L') {
            L.pop_back();
        }
        // deleteFirst: 先頭削除
        else if (std::strlen(command) > 6 && command[6] == 'F') {
            L.pop_front();
        }
        // delete x: 特定の値の削除
        else if (command[0] == 'd') {
            std::scanf("%d", &x); // 数値を読む
            // listはランダムアクセスできないのでイテレータで探す
            for (auto it = L.begin(); it != L.end(); ++it) {
                if (*it == x) {
                    L.erase(it);
                    break; // 【重要】「最初の要素」だけ消すのでbreak必須
                }
            }
        }
    }

    // 出力処理
    int i = 0;
    for (auto it = L.begin(); it != L.end(); ++it) {
        if (i > 0) std::printf(" "); // 最初以外は空白を入れる
        std::printf("%d", *it);
        i++;
    }
    std::printf("\n");

    return 0;
}