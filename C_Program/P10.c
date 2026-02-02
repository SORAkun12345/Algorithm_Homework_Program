#include<stdio.h>

int parent[100005];

int find(int x){
    if(parent[x] != x){
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unite(int x, int y){
    int px = find(x);
    int py = find(y);
    
    if(px != py){
        parent[px] = py;
    }
}

int main(){
    int v, e;
    scanf("%d %d", &v, &e);
    
    for(int i = 0; i < v; i++){
        parent[i] = i;
    }
    
    for(int i = 0; i < e; i++){
        int u, w;
        scanf("%d %d", &u, &w);
        unite(u, w);
    }
    
    int u, w;
    scanf("%d %d", &u, &w);
    
    if(find(u) == find(w)){
        printf("yes\n");
    } else {
        printf("no\n");
    }
    
    return 0;
}
