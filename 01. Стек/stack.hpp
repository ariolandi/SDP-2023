#ifndef _STACK_
#define _STACK_
#include <stdexcept>
template <typename T>
class Stack {
    // Динамично представяне чрез серия от възли
    struct Node {
        T value;                             // стойност
        Node* next;                          // връзка към следващия възел

        Node(const T& value, Node* next = nullptr): value(value), next(next) {}
    };
    
    Node* top_node;                          // указател към върха на стека

    void copy(const Node*);
    void clear();
public:
    Stack();
    Stack(const Stack<T>&);
    Stack<T>& operator=(const Stack<T>&);
    ~Stack();

    // Основни методи за работа със стек
    void push(const T& value);
    void pop();
    const T& top() const;
    bool empty() const;
};

// рекурсивно копиране на стек
template <typename T>
void Stack<T>::copy(const Node* node) {
    if (node == nullptr) return;
    copy(node->next);
    push(node->value);
}

template <typename T>
void Stack<T>::clear() {
    while(top_node) {
        pop();
    }
}

template <typename T>
Stack<T>::Stack(): top_node(nullptr) {}

template <typename T>
Stack<T>::Stack(const Stack<T>& other): top_node(nullptr) {
    copy(other.top_node);
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
    if (this != &other) {
        clear();
        copy(other.top_node);
    }

    return *this;
}

template <typename T>
Stack<T>::~Stack() {
    clear();
}

// добавяне на елемент на върха на стека
template <typename T>
void Stack<T>::push(const T& value) {
    top_node = new Node(value, top_node);
}

// изваждане на елемент от върха на стека
template <typename T>
void Stack<T>::pop() {
    if (empty()) throw(std::logic_error("Stack is empty!"));

    Node* to_delete = top_node;
    top_node = top_node->next;
    delete to_delete;
}

// достъп до стойността на елемента на върха на стека
template <typename T>
const T& Stack<T>::top() const {
    if (empty()) throw(std::logic_error("Stack is empty!"));

    return top_node->value;
}

// проверка дали стекът е празен
template <typename T>
bool Stack<T>::empty() const {
    return top_node == nullptr;
}

#endif // _STACK_
