#include <iostream>

// цикличен списък
template <typename T>
struct Node {
    T value;
    Node<T>* next;
};

template <typename T>
Node<T>* create(const T& value, Node<T>* next = nullptr) {
    Node<T>* node = new Node<T>{value, next};
    if(node->next == nullptr) node->next = node;
    return node;
}

template <typename T>
bool only(Node<T>* head) {              // проеряваме дали списъка се състои от само един елемент
    return head->next == head;
}

template <typename T>
void pop(Node<T>*& head) {
    if (head == nullptr) return; // throw std::logic_error("Stack is empty");
    if (only(head)) {
        delete head;
        head = nullptr;
        return;
    } 

    Node<T>* iterator = head;
    while(iterator->next != head && iterator->next->next != head) iterator = iterator->next;
    delete iterator->next;
    iterator->next = head;
}

template <typename T>
void pop_front(Node<T>*& head) {
    if (head == nullptr) return; // throw std::logic_error("Stack is empty");
    if (only(head)) {
        delete head;
        head = nullptr;
        return;
    } 

    Node<T>* iterator = head;
    while(iterator->next != head) iterator = iterator->next;
    iterator->next = head->next;
    delete head;
    head = iterator->next;
}

template <typename T>
void clear(Node<T>*& head) {
    while(head != nullptr) {   // while(head) <-> nullptr == false
        pop(head);
    }
}

template <typename T>
void push(const T& value, Node<T>*& head) {
    Node<T>* node = create(value, head);
    if(head == nullptr) {
        node->next = node;
        head = node;
        return;
    }

    Node<T>* iterator = head;
    while(iterator->next != head) iterator = iterator->next;
    iterator->next = node;
}

template <typename T>
void print(Node<T>* head) {
    std::cout << head->value << " ";

    if (only(head)) {
        std::cout << std::endl;
        return;
    }

    Node<T>* iterator = head->next;
    while(iterator != head) {   // while(head) <-> nullptr == false
        std::cout << iterator->value << " ";
        iterator = iterator->next;
    }
    std::cout << std::endl;
}


// намираме дадена позиция в списъка
// при следващо завъртане ще продължим от същата позиция
template <typename T>
int find(int position, Node<T>*& head) {
    if(position == 1) {
        int to_return = head->value;
        pop_front(head);
        return to_return;
    }

    head = head->next;
    return find(position-1, head);
}



int main()
{
    int n;
    std::cin >> n;
    Node<int>* knights = nullptr;
    for(int i = 0; i <n; i++) {
        int x;
        std::cin >> x;
        push(x, knights);
    }

    int position = (((n % 2) * 4 + 8) / 2) % n;
    
    while(!only(knights)) {
        std::cout << "found: " << position << std::endl;
        print(knights); 
        position = find(position, knights);

    }

    std::cout << knights->value << std::endl;


    clear(knights);
    return 0;
}