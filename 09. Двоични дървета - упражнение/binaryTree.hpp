#ifndef _B_TREE_
#define _B_TREE_
#include <stack>
#include <iostream>
#include <vector>
#include <queue>

template <typename T>
class BTree {
    T value;
    BTree<T>* left;
    BTree<T>* right;

    void add(BTree<T>*& child, const BTree<T>* other) {
        if(child) {
            delete child;
            child = nullptr;
        }
        if(!other) return;
        child = new BTree<T>(other->value);
        if(other->left) child->add_left(other->left);
        if(other->right) child->add_right(other->right);
    }

    void copy(const BTree<T>& other) {
        this->value = other.value;
        add_left(other.left);
        add_right(other.right);
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
    BTree(const T& value): value(value), left(nullptr), right(nullptr) {}
    BTree(const BTree<T>& other) {
        copy(other);
    }
    BTree<T>& operator=(const BTree<T>& other) {
        if(this != &other) {
            clear();
            copy(other);
        }

        return *this;
    }
    ~BTree() {
        clear();
    }

    void add_left(const BTree<T>* left_tree) {
        add(this->left, left_tree);
    }
    void add_right(const BTree<T>* right_tree) {
        add(this->right, right_tree);
    }

    void add_left(const T& value) {
        BTree<T> tree(value);
        add_left(&tree);
    }

    void add_right(const T& value) {
        BTree<T> tree(value);
        add_right(&tree);
    }

    std::vector<T> bfs() const {
        std::queue<BTree*> order;
        std::vector<T> values;
        order.push(this);
        while(!order.empty()) {
            BTree<T>* i = order.front();
            order.pop();
            if(i->left) order.push(i->left);
            if(i->right) order.push(i->right);
            values.push_back(i->value);
        }

        return values;
    }

    std::vector<T> dfs() const {
        std::vector<T> values;
        values.push_back(value);
        if(left) {
            std::vector<T> l = left->dfs();
            for(int i = 0; i < l.size(); i++) {
                values.push(l[i]);
            }
        }
        if(right) {
            std::vector<T> r = right->dfs();
            for(int i = 0; i < r.size(); i++) {
                values.push(r[i]);
            }
        }

        return values;
    }

    void print() const {
        if(left) left->print();
        std::cout << value << " ";
        if(right) right->print();
    }

    class Iterator;
    friend class Iterator;

    typename BTree<T>::Iterator begin() {
        BTree<T>::Iterator it;
        it.begin(this);
        return it;
    }

    typename BTree<T>::Iterator end() {
        return BTree<T>::Iterator();
    }
};

template <typename T>
class BTree<T>::Iterator {
    std::stack<BTree<T>*> it;

    void most_left(BTree<T>* tree) {
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
    void begin(BTree<T>* tree) {
        most_left(tree);
    }

    bool operator!=(const BTree<T>::Iterator& other) const {
        return it != other.it;
    }

    void operator++() {
        BTree<T>* tree = it.top();
        it.pop();
        most_left(tree->right);
    }

    const T& value() const {
        return it.top()->value;
    }
};

#endif // _B_TREE_
