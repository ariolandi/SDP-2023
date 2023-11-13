#include <iostream>
#include <vector>

struct Node {
    int value;
    Node* next;
    Node* prev;

    Node(const int value, Node* prev = nullptr, Node* next = nullptr): 
        value(value), next(next), prev(prev) {}
};

Node* create(const int value, Node* prev = nullptr, Node* next = nullptr) {
    return new Node(value, prev, next);
}

void pop_front(Node*& head) {
    if (!head) return;

    Node* to_delete = head;
    head = head->next;
    head->prev = nullptr;
    delete to_delete;
}

void push_front(const int value, Node*& head) {
    Node* node = create(value, nullptr, head);
    if(head) head->prev = node;
    head = node;
}

void clear(Node*& head) {
    while(head) {
        pop_front(head);
    }
}

Node* generate(const int size, const int value) {
    Node* list = nullptr;
    for (int i = 0; i < size; i++) push_front(value, list);

    return list;
}

void print(Node* list) {
    Node* i = list;
    while(i) {
        std::cout << i->value << " ";
        i = i->next;
    }
    std::cout << std::endl;
}

void increase_1(Node* head) {
    if(!head) return;

    head->value++;
    increase_1(head->next);
}

Node* find(const int position, Node* head) {
    if(position < 1 || !head) return nullptr;
    if (position == 1) return head;
    return find(position - 1, head->next);
}

void water(const int position, Node* head, const int watered_value) {
    if (!head) return;
    Node* to_be_watered = find(position, head);
    to_be_watered->value = watered_value;
}

void remove(Node*& to_delete) {
    if (!to_delete) return;

    Node *prev = to_delete->prev, *next = to_delete->next;
    if(prev) prev->next = next;
    if (next) next->prev = prev;

    delete to_delete;
    to_delete = next;
}

void remove_value(Node*& head, const int value) {
    // if(!head) return;
    // if(head->value == value) {
    //     remove(head);
        //    remove_value(head, value);
    // }
    // else remove_value(head->next, value);

    while(head->value == value) pop_front(head);

    Node *i = head;
    while(i) {
        if(i->value == value) remove(i);
        else i = i->next;
    }
}

void day(Node*& head, std::vector<int> to_water, const int watered_value, const int max_value) {
    increase_1(head);
    for(int i = 0; i < to_water.size(); i++) {
        int position = to_water[i];
        water(position, head, watered_value);
    }

    remove_value(head, max_value);
    print(head);
}

int main () {
    int n, m, watered = 0;
    std::cin >> n;
    Node* list = generate(n, watered);

    std::cin >> m;
    for(int i = 0; i < m; i++) {
        int count, position;
        std::vector<int> to_water;
        std::cin >> count;

        for(int j = 0; j < count; j++) {
            std::cin >> position;
            to_water.push_back(position);
        }

        day(list, to_water, watered, 3);
    }

    clear(list);
    return 0;
}

/*
20
4
3
7 14 8
1
6
12
14 19 12 17 10 15 8 13 6 11 4 9
4
1 20 4 13
*/