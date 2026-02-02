#include<iostream>
#include<vector>

/*maxHeapify(A, i)
2      l = left(i)
3      r = right(i)
4      // 左の子、自分、右の子で値が最大のノードを選ぶ
5      if l ≤ H and A[l] > A[i]
6          largest = l
7      else 
8          largest = i
9      if r ≤ H and A[r] > A[largest]
10         largest = r
11
12     if largest ≠ i　// i の子の方が値が大きい場合
13         A[i] と A[largest] を交換
14         maxHeapify(A, largest) // 再帰的に呼び出し
*/

void maxHeapify(std::vector<long long> &key,int i,int H){
    int l = i*2;
    int r = i*2+1;
    int largest;

    if(l <= H && key[l] > key[i]){
        largest = l;
    }
    else{
        largest = i;
    }

    if(r <= H && key[r] > key[largest]){
        largest = r;
    }

    if(largest != i){
        int tmp;
        tmp = key[i];
        key[i] = key[largest];
        key[largest] = tmp;

        maxHeapify(key, largest, H);
    }
}

int main(){
    int H;
    std::cin >> H;

    std::vector<long long> key(H+1);
    for(int i = 1;i <= H;i++){
        std::cin >> key[i];
    }

    for(int i = H/2; i >= 1;i--){
         maxHeapify(key, i, H);
    }

    for (int i = 1; i <= H; i++) {
        std::cout << " " << key[i]; 
    }
    std::cout << std::endl;

    return 0;
}