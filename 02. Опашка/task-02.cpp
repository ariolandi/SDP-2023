#include "queue.hpp"
#include "stack.hpp"
#include <iostream>

bool can_exit(Queue<int>& street, Stack<int>& detour, const int number) {
    // от отбивката може да се изведе само автомобилът, разположен най-отпред
    if(!detour.empty() && detour.top() == number) {
        detour.pop();
        return true;
    }

    while(!street.empty()) {                        // докато улицата не е празна
        int car_id = street.front();                // се взима следващия автомобил от нея
        street.pop();
        if (car_id == number) return true;          // ако е търсеният номер, то може да бъде изведен
        detour.push(car_id);                        // в противен случай, се премества в отбивката
    }

    // ако улицата е празна, то следващият номер автомобил не може да бъде изведен
    return false;
}


int main()
{
    Queue<int> street;
    Stack<int> detour;

    int number_of_cars;
    std::cin >> number_of_cars;
    for(int i = 0; i < number_of_cars; i++) {
        int car_id;
        std::cin >> car_id;
        street.push(car_id);
    }

    
    int next = 1;
    
    // докато не всички автомобили са изведени от парада
    // и докато следващия поред автомобил може да излезе
    while(next <= number_of_cars && can_exit(street, detour, next)) {
        // се преминава към следващия пореден номер
        next++;
    }

    // ако не всички автомобили са изведени, то отговорът е "no"
    std::cout << (next > number_of_cars ? "yes" : "no") << std::endl;

    return 0;
}