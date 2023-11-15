#include <iostream>
#include <list>

template <typename T>
std::list<std::list<T>> chunk(const std::list<T> l, const int k) {
    std::list<std::list<T>> matrix;

    typename std::list<T>::const_iterator it = l.begin();
    while(it != l.end()) {
        std::list<T> row;
        for(int i = 0; i < k && it != l.end(); i++, it++) {
            row.push_back(*it);
        }
        matrix.push_back(row);
    }

    return matrix;
}


int main ()
{ 
    int n, k;
    std::cin >> n;
    std::list<double> l;
    for(int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        l.push_back(x);
    }
    std::cin >> k;


    std::list<std::list<double>> m = chunk(l, k);
    for(auto it = m.begin(); it != m.end(); it++) {
        for(auto j = it->begin(); j != it->end(); j++) {
            std::cout << *j << " ";
        }
        std::cout << std::endl;
    }


    return 0;
}