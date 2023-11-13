#include <iostream>
#include <string>

template <typename T>
struct Node {   
  T value;          // стойност на полето
  Node<T>* next;    // връзка към следващото поле
};

// създаване на елемент
template <typename T>
Node<T>* create(const T& value, Node<T>* next=nullptr) {
    return new Node<T>{value, next};
}

// добавяне на елемент
template <typename T>
void push(const T& value, Node<T>*& head) {
    if (!head) head = create(value);                    // празна опашка
    else if (!head->next) head->next = create(value);   // последен елемент на опашката
    else push(value, head->next);
}

// премахване на елемент
template <typename T>
void pop(Node<T>*& head) {
    if (!head) return;                                  // празна опашка

    Node<T>* to_be_deleted = head;
    head = head->next;
    delete to_be_deleted;
}

// изтриване на опашката
template <typename T>
void clear(Node<T>*& head) {
    while(head) pop(head);
}

template <typename T>
void reverse(Node<T>*& head) {
    if(!head) return;

    int value = head->value;
    pop(head);
    reverse(head);
    push(value, head);
} 

template <typename T>
void front(Node<T>*& head) {
    if(!head) std::cout << "No job for Anya" << std::endl;
    else {
        std::cout << head->value << std::endl;
        pop(head);
    }
} 

template <typename T>
void back(Node<T>*& head) {
    reverse(head);
    front(head);
    reverse(head);
} 


int main()
{ 
    Node<int>* jobs = nullptr;

    int n, x;
    std::string command;
    std::cin >> n;
    for(int i = 0; i < n; i++) {
        std::cin >> command;
        if (command == "add") {
            std::cin >> x;
            push(x, jobs);
        } else if (command == "reverse") {
            reverse(jobs);
        } else if (command == "front") {
            front(jobs);
        } else {
            back(jobs);
        }
    }

    clear(jobs);
    return 0;
}