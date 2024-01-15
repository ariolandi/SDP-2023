#include "graph.hpp"
#include <iostream>

int main ()
{
    int n, m;
    std::cin >> n >> m;

    std::vector<int> v;
    for (int i = 1; i <= n; i++) {
        v.push_back(i);
    }

    Graph<int> friends(v);

    for(int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        friends.add_edge(x, y);
    }

    std::vector<std::vector<int>> p = friends.components();
    int max_size = 0;

    for (int i = 0; i < p.size(); i++) {
        int s = 0;
        for(int j = 0; j < p[i].size(); j++) {
            std::cout << p[i][j] << " ";
            s++;
        } 
        std::cout << std::endl;
        if (s > max_size) max_size = s;
    }

    std::cout << max_size << std::endl;
   
    return 0;
}