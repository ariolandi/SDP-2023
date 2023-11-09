#include <iostream>
#include <string>

template <typename T>
struct Node {
    T value;
    Node<T>* next;
};

template <typename T>
Node<T>* create(const T& value, Node<T>* next = nullptr) {
    return new Node<T>{value, next};
}

template <typename T>
void pop(Node<T>*& head) {
    if (head == nullptr) return; // throw std::logic_error("Stack is empty");

    Node<T>* to_be_deleted = head;
    head = head->next;
    delete to_be_deleted;
}

template <typename T>
void clear(Node<T>*& head) {
    while(head != nullptr) {   // while(head) <-> nullptr == false
        pop(head);
    }
}

template <typename T>
void push(const T& value, Node<T>*& head) {
    Node<T>* new_head = create(value, head);
    head = new_head;
}


void extract(const std::string& input, Node<int>*& numbers, Node<char>*& operations) {
    bool is_number = true;
    int index = 0;
    int x = 0;

    // извличане на първото число
    while(input[index] != ' ' && index < input.size()) {
        x = x * 10 + (input[index] - '0'); 
        index++;
    }
    index++;
    push(x, numbers);

    while(index < input.size()) {
        if(is_number) {         // ако очакваме да прочетем число
            int x = 0;
            while(input[index] != ' ' && index < input.size()) {
                x = x * 10 + (input[index] - '0'); 
                index++;
            }
            push(x, numbers);
            is_number = false;
        } else {                // ако очакваме да прочетем операция
            push(input[index], operations);
            is_number = true;
            index++;
        }
        
        index++;                // пропускаме интервала
    }
}

int calculate(Node<int>* numbers, Node<char>* operations) {
    while(operations) {
        char op = operations->value;
        pop(operations);

        // x / y -> x y /
        int y = numbers->value; 
        pop(numbers);
        int x = numbers->value;
        pop(numbers);

        switch (op) {
            case '+': x += y; break;
            case '-': x -= y; break;
            case '*': x *= y; break;
            case '/': x /= y; break;
        }


        push(x, numbers);
    }

    return numbers->value;
}


int main() {
    Node<int>* numbers = nullptr;
    Node<char>* operations = nullptr;

    std::string input;
    getline(std::cin, input);   // != std::cin.getline() -> char*
    extract(input, numbers, operations);

    std::cout << calculate(numbers, operations) << std::endl;

    clear(numbers);
    clear(operations);
    return 0;
}