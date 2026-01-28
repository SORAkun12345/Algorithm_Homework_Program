#include<iostream>
#include<vector>

int prim(std::vector<std::vector<int>>& Weight, int n){
    std::vector<int> minCost(n+1, INT_MAX);
    std::vector<bool> visited(n+1, false);
    int totalCost = 0;
    
    minCost[1] = 0;
    
    for(int i = 1; i <= n; i++){
        int u = -1;
        int minWeight = INT_MAX;
        
        for(int v = 1; v <= n; v++){
            if(!visited[v] && Weight[i][v] < minWeight){
                minWeight = Weight[i][v];
                u = v;
            }
        }
        
        visited[u] = true;
        totalCost += minWeight;
        
        for(int v = 1; v <= n; v++){
            if(!visited[v] && Weight[u][v] != -1 && Weight[u][v] < minCost[v]){
                minCost[v] = Weight[u][v];
            }
        }
    }
    
    return totalCost;
}

int main(){
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> Weight(n+1, std::vector<int>(n+1));

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            std::cin >> Weight[i][j];
        }
    }

    int minCost = prim(Weight, n);
    std::cout << minCost << std::endl;
    return 0;
}