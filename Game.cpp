#include "Game.h"
#include <iostream>
Game::Game()
    : player(20), enemy(24), potions(2) {
}
void Game::printState() const {
    std::cout << "STATE "
              << player.hp() << " "
              << enemy.hp() << " "
              << potions << '\n';
}
void Game::run() {
    std::string command;
    while (std::getline(std::cin, command)) {
        if (command == "QUIT") {
            std::cout << "BYE\n";
            return;
        }
        if (command == "STATUS") {
            printState();
        }
        else if (command == "ATTACK") {
            enemy.takeDamage(6);
            if (!enemy.alive()) {
                std::cout << "WIN\n";
                return;
            }
            player.takeDamage(5);
            if (!player.alive()) {
                std::cout << "LOSE\n";
                return;
            }
            printState();
        }
        else if (command == "HEAL") {
            if (potions <= 0) {
                std::cout << "NO_POTIONS\n";
                continue;
            }
            potions--;
            player.heal(8);
            player.takeDamage(5);
            if (!player.alive()) {
                std::cout << "LOSE\n";
                return;
            }
            printState();
        }
        else{
            std::cout << "ERROR\n";
        }
    }
}
