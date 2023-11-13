#include "stack.hpp"
#include <iostream>
#include <string>


// проверка дали две скоби образуват валидна двойка
bool is_pair (const char opening, const char closing) {
    return (opening == '(' && closing == ')') || 
           (opening == '[' && closing == ']') || 
           (opening == '{' && closing == '}');
}

// проверка дали скоба е затваряща
bool is_closing (const char bracket) {
    return bracket == ')' || bracket == '}' || bracket == ']';
}

int main () {
    // няма нужда да се пазят затварящите скоби
    Stack<char> opening_brackets;

    std::string input;
    std::cin >> input;

    bool valid = true;
    for(size_t i = 0; i < input.size(); i++) {
        char bracket = input[i];

        if (is_closing(bracket)) {                               // ако скобата е затваряща
            if (!opening_brackets.empty()) {                     // ако стекът с отварящи скоби не е празен
                char opening_bracket = opening_brackets.top();
                opening_brackets.pop();
                valid = is_pair(opening_bracket, bracket);        // се проверява дали се образува валидна двойка
            } else {                                              // ако стекът с отварящи скоби е празен
                valid  = false;                                   // това не е валидна поредица
            }
        } else {                                                  // ако скобата е отваряща, се добавя в стeка
            opening_brackets.push(bracket);
        }
    }

    // при наличие на остатъчни отворени скоби, това не е валидна поредица
    valid = valid && opening_brackets.empty();                  

    std::cout << (valid ? "yes" : "no") << std::endl;

    return 0;
}
