#include "stack.hpp"
#include <iostream>

// обръщане на стек
template <typename T>
void reverse(Stack<T>& stack) {
    Stack<T> reversed;
    while(!stack.empty()) {
        reversed.push(stack.top());
        stack.pop();
    }

    stack = reversed;
}

// симулация на един ден в рамките на задачата
// връща true, ако растение е умряло на този ход, false - в противен случай
bool kill_plants(Stack<int>& pesticides) {
    Stack<int> for_next_day;

    bool plant_has_been_killed = false;

    
    while(!pesticides.empty()) {
        int plant_pesticide = pesticides.top();                              // пестицидите за поредното растение
        pesticides.pop();
        if (!pesticides.empty() && plant_pesticide > pesticides.top()) {     // ако има вляво от него и то е третирано с по-малко пестициди
            plant_has_been_killed = true;                                    // текущото растение умира
        } else {                                                             // в противен случай, оживява
            for_next_day.push(plant_pesticide);
        }
    }       

    // стекът за следващия ход съдържа растенията от лехата в обърнат ред
    reverse(for_next_day);
    pesticides = for_next_day;

    return plant_has_been_killed;
}


int main ()
{
    int number_of_plants;
    Stack<int> pesticides;

    std::cin >> number_of_plants;
    for (int i = 0; i < number_of_plants; i++) {
        int plant_pesticide;
        std::cin >> plant_pesticide;
        pesticides.push(plant_pesticide);
    }

    int day = 0;
    while(kill_plants(pesticides)) {
        day++;
    }

    std::cout << day << std::endl;


    return 0;
}