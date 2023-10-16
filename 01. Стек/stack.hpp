#ifndef _STACK_
#define _STACK_

template <typename T>
class Queue {
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
    Queue();
    Queue(const Queue<T>&);
    Queue& operator=(const Queue<T>&);
    ~Queue();

    // Основни методи за работа със стек
    void push(const T& value);
    void pop();
    const T& front() const;
    bool empty() const;
};

template <typename T>
void Queue<T>::copy(const Node* node) {
    if (node == nullptr) return;
    copy(node->next);
    push(node->value);
}

template <typename T>
void Queue<T>::clear() {
    while(top_node) {
        pop();
    }
}

template <typename T>
Queue<T>::Queue(): top_node(nullptr) {}

template <typename T>
Queue<T>::Queue(const Queue<T>& other): top_node(nullptr) {
    copy(other.top_node);
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other) {
    if (this != &other) {
        clear();
        copy(other.top_node);
    }

    return *this;
}

template <typename T>
Queue<T>::~Queue() {
    clear();
}

template <typename T>
void Queue<T>::push(const T& value) {
    Node* node = new Node(value, top_node);
    top_node = node;
}

template <typename T>
void Queue<T>::pop() {
    if (empty()) throw(std::logic_error("Stack is empty!"));

    Node* node = top_node;
    top_node = top_node->next;
    delete node;
}

template <typename T>
const T& Queue<T>::front() const {
    if (empty()) throw(std::logic_error("Stack is empty!"));

    return top_node->value;
}

template <typename T>
bool Queue<T>::empty() const {
    return top_node == nullptr;
}

#endif // _STACK_
