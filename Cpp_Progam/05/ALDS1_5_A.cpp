/*
総当たり
長さ 
 の数列 
 と整数 
 に対して、
 の要素の中のいくつかの要素を足しあわせて 
 が作れるかどうかを判定するプログラムを作成してください。
 の各要素は１度だけ使うことができます。

数列 
 が与えられたうえで、質問として 
 個の 
 が与えれるので、それぞれについて "yes" または "no" と出力してください。

入力
１行目に 
、２行目に 
 を表す 
 個の整数、３行目に 
、４行目に 
 個の整数 
が与えられます。

出力
各質問について 
 の要素を足しあわせて 
 を作ることができれば yes と、できなければ no と出力してください。

制約
の要素
入力例 1
5
1 5 7 10 21
4
2 4 17 8
出力例 1
no
no
yes
yes
*/

#include<iostream>
#include<vector>
#include<string>

std::vector<std::string> canMake(const std::vector<int>& A,const std::vector<int>& M){
    std::vector<std::string> isPossible(M.size(),"no");
    std::vector<int> possibleSums;

    possibleSums.push_back(0);
    for(int i = 0;i < A.size();i++){
        int currentSize = possibleSums.size();
        for(int j = 0;j < currentSize;j++){
            possibleSums.push_back(possibleSums[j] + A[i]);
        }
    }

    for(int i = 0;i < M.size();i++){
        for(int j = 0;j < possibleSums.size();j++){
            if(M[i] == possibleSums[j]){
                isPossible[i] = "yes";
                break;
            }
        }
    }
    return isPossible;
}

int main(){
    int n;
    std::cin >> n;

    std::vector<int> A(n);
    for(int i = 0;i < A.size();i++){
        std::cin >> A[i];
    }

    int q;
    std::cin >> q;

    std::vector<int> M(q);
    for(int i = 0;i < M.size();i++){
        std::cin >> M[i];
    }

    std::vector<std::string> results = canMake(A,M);
    
    for(int i = 0;i < results.size();i++){
        std::cout << results[i] << std::endl;
    }
}