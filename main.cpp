#include <iostream>
#include <clocale>

class Fighter {
    private:
        const char* name;
        int health;
        int maxHealth;
        int damage;

    public:
        Fighter(const char* name, int health, int damage) : name(name), health(health), maxHealth(health), damage(damage){}

    void TakeDamage(int amount){
        health -= amount;

        if(health < 0){
            health = 0;
        }
    }

    void Attack(Fighter& target) const{
        target.TakeDamage(damage);
    }

    bool IsAlive() const{
        return health > 0;
    }

    void PrintStatus() const{
        std::cout << "Fighter: " << name << '\n';
        std::cout << "Health: " << health << " / " << maxHealth << '\n';
        std::cout << "Damage: " << damage << '\n';
        std::cout << "Alive: " << (IsAlive() ? "Live" : "Died") << '\n';
    }
};

class Game {
    private:
        Fighter player;
        Fighter enemy;

    public:
        Game() : player("Player", 30, 8), enemy("Enemy", 12, 3) {}

    void PrintFighter(const Fighter& fighter) {
        fighter.PrintStatus();
    }

    void Run() {
        bool isPlay = true;
        while (isPlay) {
            PrintFighter(player);
            PrintFighter(enemy);
            char input;
            std::cin >> input;
            switch (input) {
                case '0':
                    isPlay = false;
                    break;
                case '1':
                    player.Attack(enemy);
                    if (enemy.IsAlive()) {
                        enemy.Attack(player);
                        std::cout << "Enemy attack you too\n";
                    }
                    else {
                        std::cout << "enemy is died!\n";
                        isPlay = false;
                    }
                    if (!player.IsAlive()) {
                        std::cout << "You are died\n";
                        isPlay = false;
                    }
                    break;
                default:
                    std::cout << "Неизвестная команда!\n";
                    break;
            }
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    Game game;
    game.Run();
    return 0;
}