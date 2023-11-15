#include <iostream>

template <typename T>
struct Node { 
    T value; 
    Node<T>* prev; 
    Node<T>* next; 
};

template <typename T>
Node<T>* create(const T& value, Node<T>* prev = nullptr, Node<T>* next = nullptr) {
    Node<T>* new_node = new Node<T>;
    new_node->value = value;
    new_node->prev = prev;
    new_node->next = next;
    return new_node;
}

template <typename T>
void connect(Node<T>* first, Node<T>* second) {
    if (!first && !second) return;
    if (second) second->prev = first;
    if (first) first->next = second;
}

template <typename T>
void push_front(const T& value, Node<T>*& list) {
    Node<T>* node = create(value);
    connect(node, list);
    list = node;
}


template <typename T>
void pop_front(Node<T>*& list) {
  if(!list) return;

  Node<T>* to_be_deleted = list;
  list = list->next;
  connect<T>(nullptr, list);
  delete to_be_deleted;
}

template <typename T>
void delete_after(Node<T>*& node) {
    Node<T>* next_node = node->next;
    if (!next_node) return;

    Node<T>* node_after = next_node->next;
    connect(node, node_after);
    delete next_node;
}


template <typename T>
void clear(Node<T>*& list) {
    while(list) {
        pop_front(list);
    }
}

template <typename T>
void print(Node<T>* list) {
    while(list) {
        std::cout << list->value << " ";
        list = list->next;
    }
    std::cout << std::endl;
}

template <typename T>
void print_reversed(Node<T>* list) {
    while(list) {
        std::cout << list->value << " ";
        list = list->prev;
    }
    std::cout << std::endl;
}

template <typename T>
void sort(Node<T>* list) {
    Node<T>* i = list;
    while (i) {
        Node<T>* j = list;
        while(i != j) {
            if (j->value > i->value) std::swap(i->value, j->value);
            j = j->next;
        }
        i = i->next;
    }
}

template <typename T>
Node<T>* merge(Node<T>* first, Node<T>* second) {
    Node<T>* arr = nullptr;

    Node<T> *i = first, *j = second;
    while(i && j) {
        T x = i->value, y = j->value;
        if (x < y) {
            push_front(x, arr);
            i = i->next;
        } else {
            push_front(y, arr);
            j = j->next;
        }
    }

    while(i) {
        push_front(i->value, arr);
        i = i->next;
    }

    while(j) {
        push_front(j->value, arr);
        j = j->next;
    }

    return arr;
}

template <typename T>
void unique(Node<T>*& list) {
    if (!list || !list->next) return;

    Node<T> *first = list, *second = list->next;
    while(second) {
        if(second->value == first->value) {
            delete_after(first);
            second = first;
        }
        first = first->next;
        second = second->next;
    }
}

template <typename T>
void remove_anomaly(Node<T>*& list) {
    if (!list || !list->next) return;

    Node<T> *prev = list, *it = list->next;
    while(it) {
        if(it->prev != prev) { 
            it->prev = prev;
        }
        it = it->next;
        prev = prev->next;
    }
}


int main ()
{
    Node<int> *a = nullptr, *b = nullptr;
    push_front(5, a);
    push_front(17, a);
    push_front(-1, a);
    push_front(5, a);

    push_front(6, b);
    push_front(-1, b);
    push_front(4, b);

    sort(a);
    sort(b);
    print(a);
    print(b);

    Node<int>* c = merge(a, b);
    print(c);

    unique(c);
    print(c);

    Node<char> *list_1 = create('a');
    Node<char> *list_2 = create('b');
    Node<char> *list_3 = create('c');
    Node<char> *list_4 = create('d');
    Node<char> *list_5 = create('e');
    Node<char> *list_6 = create('f');
    connect(list_1, list_2);
    connect(list_2, list_3);
    connect(list_3, list_5);
    connect(list_4, list_6);

    list_4->prev = list_3;
    list_5->next = list_4;
    print(list_1);
    print_reversed(list_6);

    remove_anomaly(list_1);
    print(list_1);
    print_reversed(list_6);

    clear(list_1);
    clear(a);
    clear(b);
    clear(c);
    return 0;
}