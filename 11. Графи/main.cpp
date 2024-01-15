#include "graph.hpp"
#include <iostream>

/*
7
1 2
2 3
3 5
5 2
3 5
1 4
2 5
*/

int main ()
{
    std::vector<int> k;
    for(int i = 0; i < 5; i++) k.push_back(i + 5);

    Graph<int> g;

    int m;
    std::cin >> m;
    for(int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        g.add_edge(x, y);
    }

    std::vector<int> v = g.get_vertices();
    for (int i = 0; i < v.size(); i++) std::cout << v[i] << " ";
    std::cout << std::endl;


    return 0;
}