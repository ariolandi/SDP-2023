#ifndef _QUEUE_
#define _QUEUE_

template <typename T>
class Queue {
    // Динамично представяне чрез серия от възли
    struct Node {
        T value;                             // стойност
        Node* next;                          // връзка към следващия възел

        Node(const T& value, Node* next = nullptr): value(value), next(next) {}
    };
    
    Node *head, *end;                        // указатели към главата и края на опашката

    void copy(const Node*);
    void clear();
public:
    Queue();
    Queue(const Queue<T>&);
    Queue& operator=(const Queue<T>&);
    ~Queue();

    // Основни методи за работа с опашка
    void push(const T& value);
    void pop();
    const T& front() const;
    bool empty() const;
};

template <typename T>
void Queue<T>::copy(const Node* node) {
    if (node == nullptr) return;
    push(node->value);
    copy(node->next);
}

template <typename T>
void Queue<T>::clear() {
    while(head) {
        pop();
    }
}

template <typename T>
Queue<T>::Queue(): head(nullptr), end(nullptr) {}

template <typename T>
Queue<T>::Queue(const Queue<T>& other): head(nullptr), end(nullptr) {
    copy(other.head);
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other) {
    if (this != &other) {
        clear();
        copy(other.head);
    }

    return *this;
}

template <typename T>
Queue<T>::~Queue() {
    clear();
}

template <typename T>
void Queue<T>::push(const T& value) {
    Node* node = new Node(value);
    if (head) {
        end->next = node;
    } else {
        head = node;
    }
    end = node;
}

template <typename T>
void Queue<T>::pop() {
    if (empty()) throw(std::logic_error("Queue is empty!"));

    Node* node = head;
    head = head->next;
    if(empty()) end = nullptr;
    delete node;
}

template <typename T>
const T& Queue<T>::front() const {
    if (empty()) throw(std::logic_error("Queue is empty!"));

    return head->value;
}

template <typename T>
bool Queue<T>::empty() const {
    return head == nullptr;
}

#endif // _QUEUE_
