#include "queue.hpp"
#include "stack.hpp"
#include <iostream>


int main()
{
    int n, x, command;
    const int ADD = 1;
    Queue<int> queue;
    Stack<int> stack;

    bool can_be_stack = true, can_be_queue = true;

    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> command >> x;

        // при команда за слагане в кутия, съответният елемент се добавя и в двете кутии
        if(command == ADD) {
            queue.push(x);
            stack.push(x);
        } else {                    // при команда за изваждане от кутия, се разглеждат и двата изхода
            int from_queue = queue.front();
            queue.pop();
            int from_stack = stack.top();
            stack.pop();

            // и се преценява дали полученият елемент от съответната структура отговаря на търсения.
            can_be_stack &= (from_stack == x);
            can_be_queue &= (from_queue == x);
        }
    }

    if (can_be_queue && can_be_stack) std::cout << "both" << std::endl;
    else if (can_be_queue ) std::cout << "queue" << std::endl;
    else if (can_be_stack) std::cout << "stack" << std::endl;
    else  std::cout << "nothing" << std::endl;

    return 0;
}