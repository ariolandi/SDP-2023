#include <iostream>
#include <vector>
#include <queue>

std::vector<std::pair<int, int>> dijkstra(const int start, const std::vector<std::vector<std::pair<int, int>>>& graph) {
        std::priority_queue<std::pair<int, int>> q;
        std::vector<std::pair<int, int>> distances(graph.size(), std::make_pair(-1, 0));

        distances[start] = std::make_pair(0, 1);
        q.push(std::make_pair(distances[start].first, start));

        while(!q.empty()) {
            std::pair<int, int> p = q.top();
            q.pop();
            int v = p.second;

            for(int i = 0; i < graph[v].size(); i++) {
                int u = graph[v][i].first;
                int d = graph[v][i].second;

                if(distances[u].first == distances[v].first + d) {
                    distances[u].second ++;
                    q.push(std::make_pair(distances[u].first, u));
                }
                else if (distances[u].first == -1 || distances[u].first > distances[v].first + d) {
                    distances[u] = std::make_pair(distances[v].first + d, distances[v].second);
                    q.push(std::make_pair(distances[u].first, u));
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

    std::vector<std::pair<int, int>> d = dijkstra(1, graph);
    for(int i = 0; i < d.size(); i++) {
        std::cout << "to " << i << ": distance=" << d[i].first << " paths=" << d[i].second << std::endl; 
    }
   
   
    return 0;
}

/*
6 8
1 2 5
1 4 4
2 3 1
2 4 1
2 5 4
3 6 1
4 5 4
5 6 2
*/