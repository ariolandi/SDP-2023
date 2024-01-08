#include "graph.hpp"
#include <iostream>
const int SIZE = 8;
const char CSIZE = 'h';

std::vector<std::pair<char, int>> get_neighbours(const std::pair<char, int>& p) {
    char x = p.first;
    int y = p.second;
    std::vector<std::pair<char, int>> n;
    char x1 = x - 1, x2 = x + 1, x3 = x - 2, x4 = x + 2;
    int y1 = y - 1, y2 = y + 1, y3 = y - 2, y4 = y + 2;

    if (x1 >= 'a') {
        if (y3 >= 1) n.push_back(std::make_pair(x1, y3));
        if (y4 <= SIZE) n.push_back(std::make_pair(x1, y4));
    }
    if (x2 <= CSIZE) {
        if (y3 >= 1) n.push_back(std::make_pair(x2, y3));
        if (y4 <= SIZE) n.push_back(std::make_pair(x2, y4));
    }
    if (x3 >= 'a') {
        if (y1 >= 1) n.push_back(std::make_pair(x3, y1));
        if (y2 <= SIZE) n.push_back(std::make_pair(x3, y2));
    }
    if (x4 <= CSIZE) {
        if (y1 >= 1) n.push_back(std::make_pair(x4, y1));
        if (y2 <= SIZE) n.push_back(std::make_pair(x4, y2));
    }

    return n;
}


int main ()
{
    Graph<std::pair<char, int>> knight;


    for (char i = 'a'; i <= CSIZE; i++) {
        for (int j = 1; j <= SIZE; j++) {
            std::pair<char, int> from(i, j);
            std::vector<std::pair<char, int>> n = get_neighbours(from);
            for (auto to: n) {
                knight.add_edge(from, to);
            }
        }
    }

    char s[3], e[3];
    std::cin >> s >> e;
    std::pair<char, int> p(s[0], s[1] - '0'), q(e[0], e[1] - '0');
    std::cout << "(" << p.first << ", " << p.second << ") (" << q.first <<", " << q.second << ")" << std::endl;

    std::map<std::pair<char, int>, int> moves = knight.distances(p);
    int d = -1;
    for(auto it = moves.begin(); it != moves.end(); it++) {
        std::pair<char, int> p = it->first;
        std::cout << "(" << p.first << ", " << p.second << "): " << it->second << std::endl;
        if(q == p) d = it->second;
    }

    std::cout << d << std::endl;
    

    
   
    return 0;
}