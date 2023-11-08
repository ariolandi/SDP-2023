#ifndef __DL_LIST__
#define __DL_LIST__

template <typename T>
class DL_List {
    struct Node
    {
        T value;
        Node* next;
        Node *previous;

        Node(const T& value, Node* next = nullptr, Node* previous): value(value), next(next), previous(previous) {}
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
    DL_List();
    DL_List(const DL_List<T>&);
    DL_List<T>& operator=(const DL_List<T>&);
    ~DL_List();


    bool empty() const;
    const T& front() const;
    const T& back() const;

    void push_back(const T&);
    void push_front(const T&);
    void pop_front();
    void pop_back();

    class Iterator;

    DL_List<T>::Iterator begin() const;
    DL_List<T>::Iterator end() const;

    void insert_after(const T&, const DL_List<T>::Iterator&);
    void delete_after(const DL_List<T>::Iterator&);

};


template <typename T>
DL_List<T>::DL_List(): first(nullptr), last(nullptr) {}

template <typename T>
DL_List<T>::DL_List(const DL_List<T>& other): first(nullptr), last(nullptr) {
    copy(other.first);
}

template <typename T>
DL_List<T>& DL_List<T>::operator=(const DL_List<T>& other) {
    if (this != &other) {
        clear();
        copy(other.first);
    }

    return *this;
}

template <typename T>
DL_List<T>::~DL_List() {
    clear();
}

template <typename T>
bool DL_List<T>::empty() const {
    return first == nullptr;
}

template <typename T>
const T& DL_List<T>::front() const {
    if (empty()) throw std::logic_error("List is empty!");
    return first->value;
}

template <typename T>
const T& DL_List<T>::back() const {
    if (empty()) throw std::logic_error("List is empty!");
    return last->value;
}

template <typename T>
void DL_List<T>::push_back(const T &value) {
    Node* new_node = new Node(value, nullptr, last);
    if (empty()) {
        first = new_node;
    } else {
        last->next = new_node;
    }

    last = new_node;
}

template <typename T>
void DL_List<T>::push_front(const T& value) {
    Node* new_node = new Node(value, first);
    if(empty()) last = new_node;
    first = new_node;
}

template <typename T>
void DL_List<T>::pop_front() {
    if (empty()) throw std::logic_error("List is empty!");

    Node* to_be_delete = first;
    first = first->next;
    if(empty()) last = nullptr;
    else first->previous = nullptr;

    delete to_be_delete;
}

template <typename T>
void DL_List<T>::pop_back() {
    if (empty()) throw std::logic_error("List is empty!");

    Node* to_be_delete = last;
    last = last->previous;
    if(last == nullptr) first = nullptr;
    else last->next = nullptr;

    delete to_be_delete;
}

template <typename T>
typename DL_List<T>::Iterator DL_List<T>::begin() const {
    return DL_List<T>::Iterator(first);
}

template <typename T>
typename DL_List<T>::Iterator DL_List<T>::end() const {
    return DL_List<T>::Iterator();
}

template <typename T>
void DL_List<T>::delete_after(const DL_List<T>::Iterator& position) {
    Node* delete_after_node = position.position;
    if (!delete_after_node) throw std::logic_error("Invalid operation!");
    Node* to_be_deleted = delete_after_node->next;
    if (!to_be_deleted) throw std::logic_error("Invalid operation!");
    Node* to_be_linked = to_be_deleted->next;

    delete_after_node->next = to_be_linked;
    if(to_be_linked) to_be_linked->previous = delete_after_node;
    delete to_be_deleted;
}

template <typename T>
void DL_List<T>::insert_after(const T& value, const DL_List<T>::Iterator& position) {
    Node* insert_after_node = position.position;
    if (!insert_after_node) throw std::logic_error("Invalid operation!");
    Node* insert_before_node = insert_after_node->next;
    Node* new_node = new Node(value, insert_before_node, insert_after_node);
    insert_after_node->next = new_node;
    if (insert_before_node) insert_before_node->previous = new_node;
}

template <typename T>
class DL_List<T>::Iterator {
    Node* position;

public:
    Iterator();
    Iterator(DL_List<T>::Node*);
    
    const T& value() const;
    void operator++();
    void operator--();
    bool operator !=(const DL_List<T>::Iterator&) const;

    friend class DL_List<T>;
};

template <typename T>
DL_List<T>::Iterator::Iterator(): position(nullptr) {}

template <typename T>
DL_List<T>::Iterator::Iterator(DL_List<T>::Node* position): position(position) {}

template <typename T>
const T& DL_List<T>::Iterator::value() const {
    if (!position) throw std::logic_error("Invalid operation!");
    return position->value;    
}

template <typename T>
void DL_List<T>::Iterator::operator++() {
    if (!position) throw std::logic_error("Invalid operation!");
    position = position->next;
}

template <typename T>
void DL_List<T>::Iterator::operator--() {
    if (!position) throw std::logic_error("Invalid operation!");
    position = position->previous;
}

template <typename T>
bool DL_List<T>::Iterator::operator!=(const DL_List<T>::Iterator& other) const {
    return position != other.position;
}

#endif // __DL_LIST__


