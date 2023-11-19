#ifndef _B_TREE_
#define _B_TREE_
#include <iostream>

template <typename T>
class BinaryTree{
    T value;
    BinaryTree<T>* left;
    BinaryTree<T>* right;

    void copy(const BinaryTree<T>& other);
    void clear();

public:
    BinaryTree(const T& value);
    BinaryTree(const BinaryTree<T>& other);
    BinaryTree<T>& operator=(const BinaryTree<T>& other);
    ~BinaryTree();

    void add_left(const T& successor);
    void add_right(const T& successor);
    void add_left(const BinaryTree<T>& successor);
    void add_right(const BinaryTree<T>& successor);

    void remove_left();
    void remove_right();

    const T& get_value() const;
    const BinaryTree<T>& get_left() const;
    const BinaryTree<T>& get_right() const;

    void print() const;

    bool is_leaf() const;
};

template <typename T>
void BinaryTree<T>::copy(const BinaryTree<T>& other) {
    value = other.value;
    left = nullptr;
    right = nullptr;

    if(other.left) add_left(*other.left);
    if(other.right) add_right(*other.right);
}

template <typename T>
void BinaryTree<T>::clear() {
    if(left) {
        left->clear();
        delete left;
    }
    if(right) {
        right->clear();
        delete right;
    }
}

template <typename T>
BinaryTree<T>::BinaryTree(const T &value) : value(value), left(nullptr), right(nullptr) {}

template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& other) {
    copy(other);
}

template <typename T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& other) {
    if (this != &other) {
        clear();
        copy(other);
    }

    return *this;
}

template <typename T>
BinaryTree<T>::~BinaryTree() {
    clear();
}

template <typename T>
void BinaryTree<T>::add_left(const T& successor) {
    BinaryTree<T> to_be_added(successor);
    add_left(to_be_added);
}

template <typename T>
void BinaryTree<T>::add_right(const T& successor) {
    BinaryTree<T> to_be_added(successor);
    add_right(to_be_added);
}

template <typename T>
void BinaryTree<T>::add_left(const BinaryTree<T>& successor) {
    remove_left();
    left = new BinaryTree<T>(successor);
}

template <typename T>
void BinaryTree<T>::add_right(const BinaryTree<T>& successor) {
    remove_right();
    right = new BinaryTree<T>(successor);
}

template <typename T>
void BinaryTree<T>::remove_left() {
    if (left) delete left;
    left = nullptr;
}

template <typename T>
void BinaryTree<T>::remove_right() {
    if (right) delete right;
    right = nullptr;
}

template <typename T>
const T& BinaryTree<T>::get_value() const {
    return value;
}


template <typename T>
const BinaryTree<T>& BinaryTree<T>::get_left() const {
    if(!left) throw std::logic_error("No left successor");
    return *left;
}

template <typename T>
const BinaryTree<T>& BinaryTree<T>::get_right() const {
    if(!right) throw std::logic_error("No right successor");
    return *right;
}

template <typename T>
void BinaryTree<T>::print() const {
    if(left) left->print();
    std::cout << value << " ";
    if(right) right->print();
}

template <typename T>
bool BinaryTree<T>::is_leaf() const {
    return (!left && !right);
}

#endif // _B_TREE_
