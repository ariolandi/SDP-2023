#ifndef __LIST__
#define __LIST__

template <typename T>
class List {
    struct Node
    {
        T value;
        Node* next;

        Node(const T& value, Node* next = nullptr): value(value), next(next) {}
    };
    Node *first, *last;
    
    void copy(const Node* node) {
        if(!node) return;
        push_back(node->value);
        copy(node->next);
    }

    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

public:
    List();
    List(const List<T>&);
    List<T>& operator=(const List<T>&);
    ~List();


    bool empty() const;
    const T& front() const;
    const T& back() const;

    void push_back(const T&);
    void push_front(const T&);
    void pop_front();

    class Iterator;

    List<T>::Iterator begin() const;
    List<T>::Iterator end() const;

    void insert_after(const T&, const List<T>::Iterator&);
    void delete_after(const List<T>::Iterator&);

};


template <typename T>
List<T>::List(): first(nullptr), last(nullptr) {}

template <typename T>
List<T>::List(const List<T>& other): first(nullptr), last(nullptr) {
    copy(other.first);
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& other) {
    if (this != &other) {
        clear();
        copy(other.first);
    }

    return *this;
}

template <typename T>
List<T>::~List() {
    clear();
}

template <typename T>
bool List<T>::empty() const {
    return first == nullptr;
}

template <typename T>
const T& List<T>::front() const {
    if (empty()) throw std::logic_error("List is empty!");
    return first->value;
}

template <typename T>
const T& List<T>::back() const {
    if (empty()) throw std::logic_error("List is empty!");
    return last->value;
}

template <typename T>
void List<T>::push_back(const T &value) {
    Node* new_node = new Node(value);
    if (empty()) {
        first = new_node;
    } else {
        last->next = new_node;
    }

    last = new_node;
}

template <typename T>
void List<T>::push_front(const T& value) {
    Node* new_node = new Node(value, first);
    first = new_node;
}

template <typename T>
void List<T>::pop_front() {
    if (empty()) throw std::logic_error("List is empty!");

    Node* to_be_delete = first;
    first = first->next;
    delete to_be_delete;
}

template <typename T>
typename List<T>::Iterator List<T>::begin() const {
    return List<T>::Iterator(first);
}

template <typename T>
typename List<T>::Iterator List<T>::end() const {
    return List<T>::Iterator();
}

template <typename T>
void List<T>::delete_after(const List<T>::Iterator& position) {
    Node* delete_after_node = position.position;
    if (!delete_after_node) throw std::logic_error("Invalid operation!");
    Node* to_be_deleted = delete_after_node->next;
    if (!to_be_deleted) throw std::logic_error("Invalid operation!");

    delete_after_node->next = to_be_deleted->next;
    delete to_be_deleted;
}

template <typename T>
void List<T>::insert_after(const T& value, const List<T>::Iterator& position) {
    Node* insert_after_node = position.position;
    if (!insert_after_node) throw std::logic_error("Invalid operation!");
    Node* new_node = new Node(value, insert_after_node->next);
    insert_after_node->next = new_node;
}

template <typename T>
class List<T>::Iterator {
    Node* position;

public:
    Iterator();
    Iterator(List<T>::Node*);
    
    const T& value() const;
    void operator++();
    bool operator !=(const List<T>::Iterator&) const;

    friend class List<T>;
};

template <typename T>
List<T>::Iterator::Iterator(): position(nullptr) {}

template <typename T>
List<T>::Iterator::Iterator(List<T>::Node* position): position(position) {}

template <typename T>
const T& List<T>::Iterator::value() const {
    if (!position) throw std::logic_error("Invalid operation!");
    return position->value;    
}

template <typename T>
void List<T>::Iterator::operator++() {
    if (!position) throw std::logic_error("Invalid operation!");
    position = position->next;
}

template <typename T>
bool List<T>::Iterator::operator!=(const List<T>::Iterator& other) const {
    return position != other.position;
}

#endif // __LIST__


