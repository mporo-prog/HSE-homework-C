#include "Fighter.h"
Fighter::Fighter(int maxHp)
    : currentHp(maxHp), maxHp(maxHp) {
}
void Fighter::takeDamage(int amount) {
    if (amount <= 0) {
        return;
    }
    if (amount >= currentHp) {
        currentHp = 0;
    } else {
        currentHp -= amount;
    }
}
void Fighter::heal(int amount) {
    if (amount <= 0) {
        return;
    }
    if (currentHp + amount > maxHp) {
        currentHp = maxHp;
    } else {
        currentHp += amount;
    }
}
int Fighter::hp() const {
    return currentHp;
}
bool Fighter::alive() const {
    return currentHp > 0;
}
