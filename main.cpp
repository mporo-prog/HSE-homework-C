
#include <iostream>
#include <clocale>

class Fighter {
private:
    const char* name;
    int health;
    int maxHealth;
    int damage;

public:
    Fighter(const char* name, int health, int damage)
        : name(name), health(health), maxHealth(health), damage(damage) {}

    void TakeDamage(int amount) {
        health -= amount;

        if (health < 0) {
            health = 0;
        }
    }

    void Attack(Fighter& target) const {
        target.TakeDamage(damage);
    }

    bool IsAlive() const {
        return health > 0;
    }

    void PrintStatus() const {
        std::cout << "Fighter: " << name << '\n';
        std::cout << "Health: " << health << " / " << maxHealth << '\n';
        std::cout << "Damage: " << damage << '\n';
        std::cout << "Alive: " << (IsAlive() ? "Live" : "Died") << '\n';
    }
};

class Game {
private:
    Fighter player;
    Fighter enemies[3];
    Fighter* currentTarget = nullptr;

public:
    Game()
        : player("Hero", 30, 8),
          enemies{
              {"Enemy 1", 12, 3},
              {"Enemy 2", 18, 4},
              {"Enemy 3", 24, 5}
          } {}
    
    bool TrySelectTarget(int number, Fighter*& outTarget) {
        outTarget = nullptr;
        if (number < 1 || number > 3) {
            return false;
        }
        Fighter& target = enemies[number - 1];

        if (!target.IsAlive()) {
            return false;
        }
        outTarget = &target;
        return true;
    }

    void PrintFighter(const Fighter& fighter) {
        fighter.PrintStatus();
    }

    void Run() {
        bool isPlay = true;
        while (isPlay) {
            std::cout << "\n--- Player ---\n";
            PrintFighter(player);
            for (int i = 0; i < 3; i++) {
                std::cout << "\n--- Enemy " << i + 1 << " ---\n";
                PrintFighter(enemies[i]);
            }
            std::cout << "\n1 - Select target\n";
            std::cout << "2 - Attack selected target\n";
            std::cout << "0 - Exit\n";
            char input;
            std::cin >> input;
            switch (input) {
                case '0':
                    isPlay = false;
                    break;
                case '1': {
                    int number;
                    std::cout << "Enter target number (1-3): ";
                    std::cin >> number;
                    if (TrySelectTarget(number, currentTarget)) {
                        std::cout << "Target selected: " << number << '\n';
                    }
                    else {
                        currentTarget = nullptr;
                        std::cout << "Invalid target or enemy is dead!\n";
                    }
                    break;
                }

                case '2':
                    if (currentTarget == nullptr) {
                        std::cout << "Select a target first!\n";
                        break;
                    }
                    player.Attack(*currentTarget);

                    if (currentTarget->IsAlive()) {
                        currentTarget->Attack(player);
                        std::cout << "Enemy attacks you back!\n";
                    }
                    else {
                        std::cout << "Enemy is dead!\n";
                        currentTarget = nullptr;
                    }

                    if (!player.IsAlive()) {
                        std::cout << "You are dead!\n";
                        isPlay = false;
                    }
                    break;
                default:
                    std::cout << "Unknown command!\n";
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
