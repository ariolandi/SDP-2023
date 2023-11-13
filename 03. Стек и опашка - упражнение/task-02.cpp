#include <iostream>
#include <stack>
#include <vector>
#include <cmath>

// помощна структура, съдържаща трите стека
struct Hanoi {
    std::stack<int> source, auxiliary, destination;

    Hanoi() {
        source = std::stack<int>();
        auxiliary = std::stack<int>();
        destination = std::stack<int>();
    }
};

// source -> reception; auxiliary -> cart; destination -> automobile
const int RECEPTION_TO_CART = 1;
const int RECEPTION_TO_AUTO = 2;
const int CART_TO_AUTO = 3;
const int AUTO_TO_CART = 4;
const int AUTO_TO_RECEPTION = 5;
const int CART_TO_RECEPTION = 6;

// реалното преместване и извеждане на кода на действието
void move(std::stack<int>& from, std::stack<int>& to, const int move_code) {
    int book = from.top();
    from.pop();
    to.push(book);
    std::cout << move_code << " " << book << std::endl;
}

// преместване между два стека
void move_between(std::stack<int>& first, std::stack<int>& second, const int first_to_second, const int second_to_first) {
    // ако единият е празен, то преместването се извършва от другия към празния
    if(second.empty()) {
        move(first, second, first_to_second);
        return;
    }
    if(first.empty()) {
        move(second, first, second_to_first);
        return;
    }

    // ако никой един от двата не е празен
    // преместването е възможно от по-малък към по-голям елемент
    int x = second.top();
    int y = first.top();
    if (x < y) move(second, first, second_to_first);
    else move(first, second, first_to_second);
} 

// редица помощни функции
void move_between_reception_and_cart(Hanoi& hanoi_tower) {
    move_between(hanoi_tower.source, hanoi_tower.auxiliary, RECEPTION_TO_CART, CART_TO_RECEPTION);
}

void move_between_reception_and_automobile(Hanoi& hanoi_tower) {
    move_between(hanoi_tower.source, hanoi_tower.destination, RECEPTION_TO_AUTO, AUTO_TO_RECEPTION);
}

void move_between_cart_and_automobile(Hanoi& hanoi_tower) {
    move_between(hanoi_tower.auxiliary, hanoi_tower.destination, CART_TO_AUTO, AUTO_TO_CART);
}

// решаване на проблема за ханойските кули
void solve(Hanoi& hanoi_towers) {
    // ако елементите са N на брой, то необходимите ходове са точно 2^N - 1
    const int number_of_elements = hanoi_towers.source.size();
    const int number_of_moves = std::pow(2, number_of_elements) - 1;
    std::vector<void(*)(Hanoi&)> moves;

    // ако броят на елементите е нечетно число, то:
    // - първото преместване е между началния стълб и крайния
    // - второто преместване е между началния стълб и помощния
    // - третото преместване е между помощния стълб и крайния
    // ако броят на елементите е четно число, то помощния и крайния стълб се разменят
    if (number_of_elements % 2) {
        moves.push_back(move_between_reception_and_automobile);
        moves.push_back(move_between_reception_and_cart);
        moves.push_back(move_between_cart_and_automobile);
    } else {
        moves.push_back(move_between_reception_and_cart);
        moves.push_back(move_between_reception_and_automobile);
        moves.push_back(move_between_cart_and_automobile);
    }

    for (int i = 0; i < number_of_moves; i++) {
        int step = i % 3;
        moves[step](hanoi_towers);
    }
}


int main() 
{
    int n;
    Hanoi hanoi_towers;

    std::cin >> n;
    for (int i = n; i > 0; i--) {
        hanoi_towers.source.push(i);
    }

    solve(hanoi_towers);

    return 0;
}
