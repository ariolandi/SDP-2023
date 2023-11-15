#include <iostream>

template <typename T>
struct Node { 
    T value; 
    Node<T>* next; 
};

template <typename T>
Node<T>* create(const T& value, Node<T>* next=nullptr) {
    return new Node<T>{value, next};
}

template <typename T>
void push_front(const T& value, Node<T>*& list) {
  list = create(value, list);
}


template <typename T>
void pop_front(Node<T>*& list) {
  if(!list) return;

  Node<T>* to_be_deleted = list;
  list = list->next;
  delete to_be_deleted;
}

template <typename T>
void delete_after(Node<T>*& node) {
    Node<T>* next_node = node->next;
    if (!next_node) return;

    node->next = next_node->next;
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
Node<T>* reverse(Node<T>* list) {
    Node<T>* reversed = nullptr;

    while(list){
        push_front(list->value, reversed);
        list = list->next;
    }

    return reversed;
}

template <typename T>
void erase(const T& value, Node<T>*& list) {
    while(list && list->value == value) {
        pop_front(list);
    } 

    Node<T>* iterator = list;
    while(iterator && iterator->next) {
        if(iterator->next->value == value) {
            delete_after(iterator);
        }
        iterator = iterator->next;
    }
}


int main()
{
    Node<int>* l = nullptr;
    push_front(5, l);
    push_front(6, l);
    push_front(5, l);
    push_front(-1, l);
    push_front(0, l);
    push_front(5, l);

    print(l);

    Node<int>* r = reverse(l);
    print(r);
    erase(5, l);
    print(l);


    clear(r);
    clear(l);
    return 0;
}