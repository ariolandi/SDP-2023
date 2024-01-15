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

    OrderedGraph<int> wormhole(v);

    for(int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        wormhole.add_edge(x, y);
    }


    std::vector<int> p = wormhole.DFS(1);
    for(int i = 0; i < p.size(); i++) {
        std::cout << p[i] << " ";
    } 
    std::cout << std::endl;

    int c = wormhole.cycles();
    std::cout << c << std::endl;

   
    return 0;
}