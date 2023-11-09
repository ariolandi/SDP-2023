#include <iostream>
#include <stack>
#include <string>
#include <vector>

int main ()
{   
    std::vector<std::stack<int> > presents;
    int n;
    std::cin >> n;
    
    std::stack<int> null_index;  
    presents.push_back(null_index);

    std::vector<int> output;

    for(int i = 0; i < n; i++) {
        std::string command;
        int x, y;
        std::cin >> command;
        if (command == "join") {                    // присъединява се ново джудже
            std::stack<int> empty;
            presents.push_back(empty);
        } else if (command == "add") {              // добавяме нов подарък
            std::cin >> x >> y;
            presents[x].push(y);
        } else {                                     // джудже е готово с подаръка си
            std::cin >> x;
            output.push_back(presents[x].top());
            presents[x].pop();
        }
    }


    for(int i = 0; i < output.size(); i++) std::cout << output[i] << std::endl;

    return 0;
}