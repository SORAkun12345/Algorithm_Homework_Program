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

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

int main() {
    string s;
    // 断面図の文字列を一括で読み込む
    if (!(cin >> s)) return 0;

    stack<int> s1; // '\' の出現位置（インデックス）を保持するスタック
    stack<pair<int, int>> s2; // (水たまりの左端の位置, その水たまりの合計面積) を保持するスタック
    int total_area = 0;

    for (int j = 0; j < s.size(); j++) {
        if (s[j] == '\\') {
            // 下り坂の位置を記録
            s1.push(j);
        } else if (s[j] == '/' && !s1.empty()) {
            // 対応する下り坂を取り出す
            int i = s1.top();
            s1.pop();
            
            // 現在の高さで形成される断面積を計算
            int current_a = j - i;
            total_area += current_a;

            // マージ（結合）処理:
            // 今回計算した範囲 (i から j) の中に含まれる以前の水たまりを統合する
            while (!s2.empty() && s2.top().first > i) {
                current_a += s2.top().second;
                s2.pop();
            }
            // 統合された新しい水たまりを記録
            s2.push(make_pair(i, current_a));
        }
    }

    // 出力1: 総面積
    cout << total_area << endl;

    // 出力2: 水たまりの数と各面積（左から順）
    vector<int> results;
    while (!s2.empty()) {
        results.push_back(s2.top().second);
        s2.pop();
    }
    // スタックから取り出すと右から順になるため、反転させる
    reverse(results.begin(), results.end());

    cout << results.size();
    for (int i = 0; i < results.size(); i++) {
        cout << " " << results[i];
    }
    cout << endl;

    return 0;
}