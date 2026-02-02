/*
優先順位キュー
優先度付きキュー (priority queue) は各要素がキーを持ったデータの集合 
 を保持するデータ構造で、主に次の操作を行います：

: 集合 
 に要素 
 を挿入する
: 最大のキーを持つ 
 の要素を 
 から削除してその値を返す
優先度付きキュー 
 に対して 
、
を行うプログラムを作成してください。ここでは、キューの要素を整数とし、それ自身をキーとみなします。

入力
優先度付きキュー 
 への複数の命令が与えられます。各命令は、insert 
、extractまたはendの形式で命令が１行に与えられます。ここで 
 は挿入する整数を表します。

end命令が入力の終わりを示します。

出力
extract命令ごとに、優先度付きキュー 
から取り出される値を１行に出力してください。

制約
命令の数は
を超えない。
k
入力例 1
insert 8
insert 2
extract
insert 10
extract
insert 11
extract
extract
end
出力例 1
8
10
11
2
*/

#include <stdio.h>
#include <string.h>

int H[2000000];
int H_size = 0;

int parent(int i) {
    return i / 2;
}

int left(int i) {
    return 2 * i;
}

int right(int i) {
    return 2 * i + 1;
}

void maxHeapify(int i) {
    int l = left(i);
    int r = right(i);
    int largest;
    
    if (l <= H_size && H[l] > H[i]) {
        largest = l;
    } else {
        largest = i;
    }
    
    if (r <= H_size && H[r] > H[largest]) {
        largest = r;
    }
    
    if (largest != i) {
        int temp = H[i];
        H[i] = H[largest];
        H[largest] = temp;
        maxHeapify(largest);
    }
}

void insert(int key) {
    H_size++;
    int i = H_size;
    H[i] = key;
    
    while (i > 1 && H[parent(i)] < H[i]) {
        int temp = H[i];
        H[i] = H[parent(i)];
        H[parent(i)] = temp;
        i = parent(i);
    }
}

int extract() {
    if (H_size < 1) {
        return -1;
    }
    
    int max = H[1];
    H[1] = H[H_size];
    H_size--;
    maxHeapify(1);
    
    return max;
}

int main(void) {
    char cmd[10];
    
    while (1) {
        scanf("%s", cmd);
        
        if (strcmp(cmd, "insert") == 0) {
            int key;
            scanf("%d", &key);
            insert(key);
        } else if (strcmp(cmd, "extract") == 0) {
            printf("%d\n", extract());
        } else if (strcmp(cmd, "end") == 0) {
            break;
        }
    }
    
    return 0;
}