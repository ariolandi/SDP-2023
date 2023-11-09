#include <iostream>
#include <list>

// сливане на списък от списъци до редица
template <typename T>
std::list<T> flatten(std::list<std::list<T>> matrix) {
    std::list<T> array;

    // обхождане на списъка от списъци
    for(typename std::list<std::list<T>>::iterator i = matrix.begin(); i != matrix.end(); i++) {
        // обхождане на всеки списък
        for(typename std::list<T>::iterator j = i->begin(); j != i->end(); j++) {
            array.push_back(*j);            // *j -> стойността на позиция j
        }
    }

    return array;
}

template <typename T>
std::list<T> unique(std::list<T> array) {
    std::list<T> unique_array;

    for(typename std::list<T>::iterator i = array.begin(); i != array.end(); i++) {
        bool to_add = true;
        for(auto j = array.begin(); j != i && to_add; j++) {
            to_add = (*i != *j);
        }
        if (to_add) unique_array.push_back(*i);
    }

    return unique_array;
}

template <typename T>
std::list<T> flatten_unique(std::list<std::list<T>> matrix) {
    return unique(flatten(matrix));
}

int main(){
    std::list<std::list<int>> l;
    int n;
    std::cin >> n;
    for(int i = 0; i < n; i++) {
        int m;
        std::cin>> m;
        std::list<int> t;
        for(int j = 0; j < m; j++) {
            int x;
            std::cin >> x;
            t.push_back(x);
        }
        l.push_back(t);
    }

    std::list<int> a = flatten_unique(l);

    for (auto i = a.begin(); i != a.end(); i++) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;

    return 0;
}

/*
{{1, 3, 1}, {}, {2}, {3, 3, 56, -1}} 
4
3
1 3 1
0
1
2
4
3 3 56 -1
*/