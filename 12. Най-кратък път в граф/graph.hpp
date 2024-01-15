#ifndef __GRAPH_
#define __GRAPH__
#include <map>
#include <vector>
#include <algorithm>
#include <queue>

template <typename T, typename S>
class WeightedOrderedGraph {
    std::map<T, std::vector<std::pair<T, S>>> graph;

public:
    WeightedOrderedGraph() {}
    WeightedOrderedGraph(const std::vector<T>& keys) {
        for (int i = 0; i < keys.size(); i++) {
           add_vertex(keys[i]);
        }
    }

    void add_vertex(const T& vertex) {
        if (graph.find(vertex) != graph.end()) return;

        graph[vertex] = std::vector<std::pair<T, S>>();
    }

    void add_edge(const T& from, const T& to, const S& weight) {
        add_vertex(from);
        add_vertex(to);

        if (find(graph[from].begin(), graph[from].end(), to) != graph[from].end()) return;
 
        graph[from].push_back(std::make_pair(to, weight));
    }   

    std::vector<T> get_vertices() const {
        std::vector<T> keys;
        for (auto it = graph.begin(); it != graph.end(); it++) {
            keys.push_back(it->first);
        }

        return keys;
    }

    std::vector<std::pair<T, S>> get_neighbours(const T& key) {
        // if (graph.find(vertex) == graph.end()) return std::vector<std::pair<T, S>>();
        return graph[key];
    }

    b
};

template <typename T, typename S>
class WeightedGraph: public WeightedOrderedGraph<T, S> {
    public:
    WeightedGraph(): WeightedOrderedGraph<T, S>() {}
    WeightedGraph(const std::vector<T>& keys): WeightedOrderedGraph<T, S>(keys) {}

    void add_edge(const T& from, const T& to, const S& weight) {
       WeightedOrderedGraph<T, S>::add_edge(from, to, weight);
       WeightedOrderedGraph<T, S>::add_edge(to, from, weight);
    }
};


#endif // __GRAPH__
