#ifndef _ORDER_TREE_
#define _ORDER_TREE_
#include <stack>
#include <iostream>

template <typename T>
class SearchTree {
    T value;
    SearchTree<T>* left;
    SearchTree<T>* right;

    void copy(const SearchTree<T>& other) {
        this->value = other.value;
        // add_left(other.left);
        // add_right(other.right);
    }

    void clear() {
        if(left) {
            left->clear();
            delete left;
        }
        if(right) {
            right->clear();
            delete right;
        }

    }

public:
    SearchTree(const T& value): value(value), left(nullptr), right(nullptr) {}
    SearchTree(const SearchTree<T>& other) {
        copy(other);
    }
    SearchTree<T>& operator=(const SearchTree<T>& other) {
        if(this != &other) {
            clear();
            copy(other);
        }

        return *this;
    }
    ~SearchTree() {
        clear();
    }

    void add(const T& value) {
        if(value <= this->value) {
            if(left) left->add(value);
            else left = new SearchTree(value);
        } else {
             if(right) right->add(value);
            else right = new SearchTree(value);
        }
    }

    void print() const {
        if(left) left->print();
        std::cout << value << " ";
        if(right) right->print();
    }

    class Iterator;
    friend class Iterator;

    typename SearchTree<T>::Iterator begin() {
        SearchTree<T>::Iterator it;
        it.begin(this);
        return it;
    }

    typename SearchTree<T>::Iterator end() {
        return SearchTree<T>::Iterator();
    }
};

template <typename T>
class SearchTree<T>::Iterator {
    std::stack<SearchTree<T>*> it;

    void most_left(SearchTree<T>* tree) {
        if(!tree) return;
        it.push(tree);
        most_left(tree->left);

        // BTree<T>* i = tree;
        // while(i) {
        //     it.push(i);
        //     i = i->left;
        // }
    }
public:
    void begin(SearchTree<T>* tree) {
        most_left(tree);
    }

    bool operator!=(const SearchTree<T>::Iterator& other) const {
        return it != other.it;
    }

    void operator++() {
        SearchTree<T>* tree = it.top();
        it.pop();
        most_left(tree->right);
    }

    const T& value() const {
        return it.top()->value;
    }
};

#endif // _ORDER_TREE_
