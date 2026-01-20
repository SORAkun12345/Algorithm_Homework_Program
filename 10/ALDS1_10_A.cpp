#include<iostream>
#include<vector>

int main(){
    std::vector<int> v;

    v.push_back(1);
    v.push_back(1);

    int n;
    std::cin >> n;

    for(int i = 2;i <= n;i++){
        int x = v[i-1] + v[i-2];
        v.push_back(x);
    }

    std::cout << v[n] << std::endl;
    return 0;
}

