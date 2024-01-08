#ifndef __GRAPH_
#define __GRAPH__
#include <map>
#include <vector>
#include <algorithm>
#include <queue>

template <typename T>
class OrderedGraph {
    std::map<T, std::vector<T>> graph;

    std::vector<T> BFS_helper(const T& s, std::map<T, bool>& used) {
        std::vector<T> path;
        std::queue<T> q;
        q.push(s);
        used[s] = true;

        while (!q.empty()) {
            T v = q.front();
            q.pop();
            path.push_back(v);

            for (int i = 0; i < graph[v].size(); i++) {
                const T u = graph[v][i];
                if (!used[u]) {
                    q.push(u);
                    used[u] = true;
                }
            }
        }

        return path;
    }

    void DFS_helper(const T& v, std::map<T, bool>& used, std::vector<T>& path) {
        used[v] = true;
        path.push_back(v);

        for (int i = 0; i < graph[v].size(); i++) {
            const T u = graph[v][i];
            if (!used[u]) DFS_helper(u, used, path);
        }
    }

    int DFS_cycle_helper(const T& v, std::map<T, bool>& used, std::map<T, bool>& same_path) {
        used[v] = true;
        same_path[v] = true;
        int cycles = 0;

        for (int i = 0; i < graph[v].size(); i++) {
            const T u = graph[v][i];
            if (same_path[u]) cycles++;
            else cycles += DFS_cycle_helper(u, used, same_path);
        }

        same_path[v] = false;

        return cycles;
    }
public:
    OrderedGraph() {}
    OrderedGraph(const std::vector<T>& keys) {
        for (int i = 0; i < keys.size(); i++) {
           add_vertex(keys[i]);
        }
    }

    void add_vertex(const T& vertex) {
        if (graph.find(vertex) != graph.end()) return;

        graph[vertex] = std::vector<T>();
    }

    void add_edge(const T& from, const T& to) {
        add_vertex(from);
        add_vertex(to);

        if (find(graph[from].begin(), graph[from].end(), to) != graph[from].end()) return;
 
        graph[from].push_back(to);
    }   

    std::vector<T> get_vertices() const {
        std::vector<T> keys;
        for (auto it = graph.begin(); it != graph.end(); it++) {
            keys.push_back(it->first);
        }

        return keys;
    }

    std::vector<T> BFS(const T s) {
        std::map<T, bool> used;

        for (auto it = graph.begin(); it != graph.end(); it++) {
            used[it->first] = false;
        }

        return BFS_helper(s, used);
    }

    std::vector<T> DFS(const T s) {
        std::vector<T> path;
        std::map<T, bool> used;

        for (auto it = graph.begin(); it != graph.end(); it++) {
            used[it->first] = false;
        }

        DFS_helper(s, used, path);
        return path;
    }

    std::vector<std::vector<T>> components() {
        std::map<T, bool> used;
        std::vector<std::vector<T>> c;

        for (auto it = graph.begin(); it != graph.end(); it++) {
            used[it->first] = false;
        }

        for (auto it = graph.begin(); it != graph.end(); it++) {
            T v = it->first;
            if (!used[v]) {
                std::vector<T> path = BFS_helper(v, used);
                c.push_back(path);
            }
        }

        return c;
    }

    int cycles() {
        std::map<T, bool> used, same_path;
        int c = 0;

        for (auto it = graph.begin(); it != graph.end(); it++) {
            used[it->first] = false;
            same_path[it->first] = false;
        } 

        for (auto it = graph.begin(); it != graph.end(); it++) {
            T v = it->first;
            if (!used[v]) {
                c += DFS_cycle_helper(v, used, same_path);
            }
        }

        return c;
    }

    std::map<T, int> distances(const T s) {
        std::map<T, int> dist;
        std::queue<T> q;

        for (auto it = graph.begin(); it != graph.end(); it++) {
            dist[it->first] = -1;
        }

        dist[s] = 0;
        q.push(s);

        while (!q.empty()) {
            T v = q.front();
            q.pop();

            for (int i = 0; i < graph[v].size(); i++) {
                const T u = graph[v][i];
                if (dist[u] == -1) {
                    q.push(u);
                    dist[u] = dist[v] + 1;
                }
            }
        }

        return dist;
    }
};

template <typename T>
class Graph: public OrderedGraph<T> {
    public:
    Graph(): OrderedGraph<T>() {}
    Graph(const std::vector<T>& keys): OrderedGraph<T>(keys) {}

    void add_edge(const T& from, const T& to) {
       OrderedGraph<T>::add_edge(from, to);
       OrderedGraph<T>::add_edge(to, from);
    }
};


#endif // __GRAPH__
