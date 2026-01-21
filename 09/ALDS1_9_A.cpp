#include<iostream>
#include<vector>

int main(){
    int H;
    std::cin >> H;

    std::vector<long long> key(H+1);
    for(int i = 1;i <= H;i++){
        std::cin >> key[i];
    }

    for (int i = 1; i <= H; i++) {
        printf("node %d: key = %lld, ", i, key[i]);

        if (i > 1) {
            printf("parent key = %lld, ", key[i / 2]);
        }
        
        if (2 * i <= H) {
            printf("left key = %lld, ", key[2 * i]);
        }

        if (2 * i + 1 <= H) {
            printf("right key = %lld, ", key[2 * i + 1]);
        }
        std::cout << "\n";
    }

    return 0;
}

/*
node 1: key = 7, left key = 8, right key = 1, 
node 2: key = 8, parent key = 7, left key = 2, right key = 3, 
node 3: key = 1, parent key = 7, 
node 4: key = 2, parent key = 8, 
node 5: key = 3, parent key = 8, 


node 1: key = 7, left key = 8, right key = 1, 
node 2: key = 8, parent key = 7, left key = 2, right key = 3, 
node 3: key = 1, parent key = 7, 
node 4: key = 2, parent key = 8, 
node 5: key = 3, parent key = 8, 

*/