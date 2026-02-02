#include<iostream>
#include<vector>

int timer = 0; 

void dfs(int u, std::vector<std::vector<int>>& Adj, std::vector<bool>& visited, std::vector<int>& d, std::vector<int>& f){
    visited[u] = true;
    d[u] = ++timer;

    for(int v = 1; v < (int)Adj.size(); v++){
        if(Adj[u][v] == 1 && !visited[v]){
            dfs(v, Adj, visited, d, f);
        }
    }
    f[u] = ++timer;
}

int main(){
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> Adj(n+1, std::vector<int>(n+1));

    for(int i = 0; i < n; i++){
        int u, k;
        std::cin >> u >> k;
        for(int j = 0; j < k; j++){
            int v;
            std::cin >> v;

            Adj[u][v] = 1;
        }
    }

    std::vector<bool> visited(n+1, false);
    std::vector<int> d(n+1);
    std::vector<int> f(n+1);

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i, Adj, visited, d, f);
        }
    }

    for(int i = 1; i <= n; i++){
        std::cout << i << " " << d[i] << " " << f[i] << std::endl;
    }

    return 0;
}