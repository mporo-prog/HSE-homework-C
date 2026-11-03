#ifndef FIGHTER_H
#define FIGHTER_H
class Fighter {
private:
    int currentHp;
    int maxHp;
public:
    Fighter(int maxHp);
    void takeDamage(int amount);
    void heal(int amount);
    int hp() const;
    bool alive() const;
};
#endif