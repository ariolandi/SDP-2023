#include "queue.hpp"
#include <iostream>

// първата карта в тестето се премества в края му
void move(Queue<int>& deck) {
    deck.push(deck.front());
    deck.pop();
}  

// първата карта в тестето се изхвърля
void remove(Queue<int>& deck) {
    int card = deck.front();
    deck.pop();

    // ако картата е последна, то тя се извежда сама на ред
    if(deck.empty()) std::cout << std::endl << card << std::endl;
    else std::cout << card << " ";
}


int main()
{
    int n;
    Queue<int> deck;

    std::cin >> n;
    for(int i = 1; i <= n; i++) {
        deck.push(i);
    }

    while(!deck.empty()) {
        remove(deck);
        if(!deck.empty()) move(deck);
    }


    return 0;
}