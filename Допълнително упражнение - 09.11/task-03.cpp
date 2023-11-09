#include <iostream>
#include <queue>
#include <string>

struct Player {
    int id;
    std::string ability;

    Player(const int id, const std::string& ability): id(id), ability(ability) {}
    void disable() { ability = "_"; }
    bool action() { return ability != "_"; }
};


// намиране дали даден идентификационен номер е в масив/вектор
bool find(const std::vector<int> players, const int id) {
    for (int i = 0; i < players.size(); i++) {
        if (players[i] == id) return true;
    }

    return false;
}


// изиграване на един рунд от играта
void play_round(std::queue<Player>& players, std::queue<int>& round) {
    std::vector<int> killed, away, pass;

    std::queue<Player> next_round;

    while(!players.empty()) {                                    // всички участници се изреждат
        Player player = players.front();
        players.pop();
        int enemy_id = round.front();
        round.pop();

        if (player.action()) {                                  // ако участникът има право на ход 
            if (find(killed, player.id)) player.disable();      // ако е бил изваден от игра, отнемаме действието
            else if(find(pass, player.id)) {}                   // ако е накаран да пасува, не правим нищо
            else {
                std::string ability = player.ability;
                if (ability == "KILL") {                        // прилагаме действие "kill"
                    killed.push_back(enemy_id);
                } else if (ability == "PASS") {                 // прилагаме действие "pass"
                    pass.push_back(enemy_id);
                } else away.push_back(enemy_id);                // прилагаме действие "away"
            }
            
            if (find(away, player.id)) player.disable();        // ако е бил изваден от игра след края на рунда, отнемаме действието
        }
        next_round.push(player);                                // всички участници се прехвърлят за следващия рунд
    }

    players = next_round;

    std::cout << "killed: ";
    for(int i = 0; i < killed.size(); i++) {
        std::cout << killed[i] << " ";
    }
    std::cout << std::endl << "away: ";
    for(int i = 0; i < away.size(); i++) {
        std::cout << away[i] << " ";
    }
    std::cout << std::endl;
}


void play(std::queue<Player> players, std::queue<std::queue<int> > game) {
    while (!game.empty()) {
        std::queue<int> round = game.front();
        game.pop();
        play_round(players, round);
    }
}

int main() 
{
    int n;
    std::cin >> n;
    std::queue<Player> players;
    for(int i = 0; i < n; i++) {
        int id;
        std::string ability;
        std::cin >> id >> ability;
        players.push(Player(id, ability));
    }

    std::queue<std::queue<int> > game;
    int m;
    std::cin >> m;
    for (int i = 0; i < m; i++) {
        std::queue<int> round;
        for (int j = 0; j < n; j++) {
            int x;
            std::cin >> x;
            round.push(x);
        }
        game.push(round);
    }

    play(players, game);

    return 0;
}