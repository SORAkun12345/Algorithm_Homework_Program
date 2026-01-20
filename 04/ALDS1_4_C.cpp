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

#include<iostream>
#include<string>
#include <unordered_set>

std::unordered_set<std::string> dictionary;

void makeDictionary(std::string inst,std::string str){
    if(inst == "insert"){
        dictionary.insert(str);
    }
    else if(inst == "find"){
        if(dictionary.count(str)){
            std::cout << "yes" << std::endl;
        }
        else{
            std::cout << "no" << std::endl;
        }
    }

}

int main(){
    int n;
    std::cin >> n;

    std::string inst,str; 
    for(int i = 0;i < n;i++){
        std::cin >> inst >> str;
        makeDictionary(inst,str);
    }
    return 0;
}