#include<iostream>
#include<vector>

void dijkstra(std::vector<std::vector<int>>& adj, int n){
    std::vector<int> dist(n, -1);
    std::vector<bool> visited(n, false);
    
    dist[0] = 0;
    
    for(int i = 0; i < n; i++){
        int u = -1;
        int minDist = -1;
        for(int v = 0; v < n; v++){
            if(!visited[v] && dist[v] != -1){
                if(u == -1 || dist[v] < minDist){
                    minDist = dist[v];
                    u = v;
                }
            }
        }
        
        if(u == -1) break;
        
        visited[u] = true;
        
        for(int v = 0; v < n; v++){
            if(adj[u][v] != 0){
                int newDist = dist[u] + adj[u][v];
                if(dist[v] == -1 || newDist < dist[v]){
                    dist[v] = newDist;
                }
            }
        }
    }
    
    for(int i = 0; i < n; i++){
        std::cout << i << " " << dist[i] << std::endl;
    }
}

int main(){
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> adj(n, std::vector<int>(n, 0));

    for(int i = 0; i < n; i++){
        int u, k;
        std::cin >> u >> k;
        for(int j = 0; j < k; j++){
            int v, c;
            std::cin >> v >> c;
            adj[u][v] = c;
        }
    }

    dijkstra(adj, n);
    return 0;
}