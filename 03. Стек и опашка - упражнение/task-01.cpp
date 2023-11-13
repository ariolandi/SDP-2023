#include <iostream>
#include <queue>
#include <stack>

const int FROM_PRESENTS_TO_HELPER = 1;
const int FROM_HELPER_TO_PRESENTS = 3;
const int FOUND = 2;

void found_present(std::queue<int>& presents, std::stack<int>& helper, const int found) {
    // всички подаръци от улей 1 с по-голям или равен на търсения номер се прехвърлят в улей 2
    while(!presents.empty() && presents.front() >= found) {
        std::cout << FROM_PRESENTS_TO_HELPER;
        helper.push(presents.front());
        presents.pop();
    }

    // ако в улей 2 има подаръци с по-малък от търсения номер, те се прехвърлят в улей 1
    while(!helper.empty() && helper.top() < found) {
        std::cout << FROM_HELPER_TO_PRESENTS;
        presents.push(helper.top());
        helper.pop();
    }

    // ако намереният подарък е първи в улей 2, то го прехвърляме в улей 3 и го смятаме за намерен
    if(!helper.empty() && helper.top() == found) {
        std::cout << FOUND;
        helper.pop();
    }
}

int main ()
{ 
    std::queue<int> presents;
    std::stack<int> helper;
    std::queue<int> to_be_found;

    int n, present_id;
    std::cin >> n;
    for(int i = n; i > 0; i--) {
        std::cin >> present_id;
        to_be_found.push(present_id);
        presents.push(i);
    }

    while(!to_be_found.empty()) {
        found_present(presents, helper, to_be_found.front());
        to_be_found.pop();
    }


    return 0;
}