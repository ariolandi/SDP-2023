#include "stack.hpp"
#include <iostream>
#include <vector>

// генератор за N на брой прости числа
std::vector<int> generate_n_primes(const int n) {
    std::vector<int> primes;

    for(int number = 2; primes.size() < n; number++) {
        bool is_prime = true;                                   // в началото всяко число се приема за просто
        for(int j = 0; j < primes.size() && is_prime; j++) {
            // дали число е просто зависи от това дали се дели без остатък на друго по-малко просто число
            is_prime = (number % primes[j]);                    
        }

        if (is_prime) primes.push_back(number);
    }

    return primes;
}

template <typename T>
void print(Stack<T> stack) {
    while(!stack.empty()) {
        std::cout << stack.top() << " ";
        stack.pop();
    }
}

void round(Stack<int>& pile_of_plates, const int prime_number) {
    Stack<int> next_round, to_serve;

    while(!pile_of_plates.empty()) {                
        int plate = pile_of_plates.top();
        pile_of_plates.pop();

        // ако поредната чиния се дели на съответното просто число без остатък, то тя се сервира
        // в противен случай - ще се разгледа на следващата итерация
        if (plate % prime_number) next_round.push(plate);
        else to_serve.push(plate);
    }

    print(to_serve);
    pile_of_plates = next_round;
}


int main ()
{
    int number_of_plates, iterations;
    Stack<int> pile_of_plates;

    std::cin >> number_of_plates >> iterations;
    for(int i = 0; i < number_of_plates; i++) {
        int plate;
        std::cin >> plate;
        pile_of_plates.push(plate);
    }

    // необходими са точно толкова прости числа, колкото итерации се разглеждат
    std::vector<int> primes = generate_n_primes(iterations);

    for(int i = 0; i < iterations; i++) {
        round(pile_of_plates, primes[i]);
    }

    print(pile_of_plates);

    return 0;
}