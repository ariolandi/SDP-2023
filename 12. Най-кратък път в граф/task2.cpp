#include <iostream>
#include <vector>
#include <queue>

std::vector<int> dijkstra(const int start, const std::vector<std::vector<std::pair<int, int>>>& graph) {
        std::priority_queue<std::pair<int, int>> q;
        std::vector<int> distances(graph.size(), -1);

        distances[start] = 0;
        q.push(std::make_pair(distances[start], start));

        while(!q.empty()) {
            std::pair<int, int> p = q.top();
            q.pop();
            int v = p.second;

            for(int i = 0; i < graph[v].size(); i++) {
                int u = graph[v][i].first;
                int d = graph[v][i].second;

                if (distances[u] == -1 || distances[u] > distances[v] + d) {
                    distances[u] = distances[v] + d;
                    q.push(std::make_pair(distances[u], u));
                }
            }
        }

        return distances;
    }

int main ()
{
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<std::pair<int, int>>> graph(n+1);
    for(int i = 0; i < m; i++) {
        int x, y, z;
        std::cin >> x >> y >> z;
        graph[x].push_back(std::make_pair(y, z));
        graph[y].push_back(std::make_pair(x, z));
    }

    std::priority_queue<std::pair<int, int>> q;
    q.push(std::make_pair(0, 1));
    std::vector<bool> used(n, false);

    while (!q.empty()) {
        std::pair<int, int> p = q.top();
        q.pop();
        int v = p.second;
        if(!used[v]) {
            used[v] = true;
            std::vector<int> d = dijkstra(v, graph);

            for(int i = 1; i < d.size(); i++) {
                std::cout << v << " " << i << ": " << d[i] << std::endl;
                q.push(std::make_pair(d[i], i));
            }
        }
    }
    
   
   
    return 0;
}

/*
7 15 
1 2 4
1 3 1
1 4 13
1 5 6
1 6 11
1 7 5
2 3 4
2 6 3
2 7 9
3 4 4
3 5 5
4 6 5
4 7 2
5 6 2
5 7 3
*/