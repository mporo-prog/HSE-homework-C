#ifndef GAME_H
#define GAME_H
#include <string>
#include "Fighter.h"
class Game {
private:
    Fighter player;
    Fighter enemy;
    int potions;

    void printState() const;
public:
    Game();
    void run();
};
#endif