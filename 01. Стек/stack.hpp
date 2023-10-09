#ifndef _STACK_
#define _STACK_

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
    Stack& operator=(const Stack<T>&);
    ~Stack();

    // Основни методи за работа със стек
    void push(const T& value);
    void pop();
    const T& top() const;
    bool empty() const;
};

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

template <typename T>
void Stack<T>::push(const T& value) {
    Node* node = new Node(value);
    node->next = top_node;
    top_node = node;
}

template <typename T>
void Stack<T>::pop() {
    if (empty()) throw(std::logic_error("Stack is empty!"));

    Node* node = top_node;
    top_node = top_node->next;
    delete node;
}

template <typename T>
const T& Stack<T>::top() const {
    if (empty()) throw(std::logic_error("Stack is empty!"));

    return top_node->value;
}

template <typename T>
bool Stack<T>::empty() const {
    return top_node == nullptr;
}

#endif // _STACK_
