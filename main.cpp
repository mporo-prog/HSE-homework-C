

#include <iostream>
#include <clocale>
#include <cstddef>

class Fighter {
private:
    const char* name;
    int health;
    int maxHealth;
    int damage;

public:
    Fighter(const char* name, int health, int damage) : name(name), health(health), maxHealth(health), damage(damage) {}

    void TakeDamage(int amount) {
        health -= amount;
        if (health < 0) {
            health = 0;
        }
    }

    void Heal(int amount) {
        health += amount;
        if (health > maxHealth) {
            health = maxHealth;
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
    int medkits = 1;

public:
    Game()
        : player("Hero", 20, 8),
          enemies{{"Enemy 1", 12, 3},
                  {"Enemy 2", 18, 4},
                  {"Enemy 3", 24, 5}} {}

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

    void PrintFighter(const Fighter& fighter) const {
        fighter.PrintStatus();
    }

    bool AllEnemiesDefeated() const {
        for (std::size_t i = 0; i < 3; i++) {
            if (enemies[i].IsAlive()) {
                return false;
            }
        }

        return true;
    }

    void PrintAllStatus() const {
        std::cout << "\n--- Player ---\n";
        PrintFighter(player);

        std::cout << "Medkits: " << medkits << '\n';

        for (int i = 0; i < 3; i++) {
            std::cout << "\n--- Enemy " << i + 1 << " ---\n";
            PrintFighter(enemies[i]);
        }

        if (currentTarget != nullptr) {
            std::cout << "\nCurrent target:\n";
            currentTarget->PrintStatus();
        } else {
            std::cout << "\nNo target selected.\n";
        }
    }

    void Run() {
        bool isPlay = true;

        while (isPlay) {
            PrintAllStatus();

            std::cout << "\n1 - Select target\n";
            std::cout << "2 - Attack selected target\n";
            std::cout << "3 - Use medkit\n";
            std::cout << "0 - Exit\n";
            std::cout << "Command: ";

            int input;

            if (!(std::cin >> input)) {
                break;
            }

            switch (input) {
                case 0:
                    isPlay = false;
                    break;

                case 1: {
                    int number;
                    std::cout << "\nEnter target number (1-3): ";

                    if (!(std::cin >> number)) {
                        isPlay = false;
                        break;
                    }

                    if (TrySelectTarget(number, currentTarget)) {
                        std::cout << "\nTarget selected: " << number << '\n';
                    } else {
                        currentTarget = nullptr;
                        std::cout << "\nInvalid target or enemy is dead!\n";
                    }
                    break;
                }

                case 2:
                    if (currentTarget == nullptr ||
                        !currentTarget->IsAlive()) {
                        currentTarget = nullptr;
                        std::cout << "\nSelect a living target first!\n";
                        break;
                    }

                    player.Attack(*currentTarget);
                    std::cout << "\nYou attacked the enemy!\n";

                    if (currentTarget->IsAlive()) {
                        currentTarget->Attack(player);
                        std::cout << "\nEnemy attacks you back!\n";
                    } else {
                        std::cout << "\nEnemy is dead!\n";
                        currentTarget = nullptr;
                    }

                    if (!player.IsAlive()) {
                        std::cout << "\nYou are dead! Game over!\n";
                        isPlay = false;
                    } else if (AllEnemiesDefeated()) {
                        std::cout << "\nYou defeated all enemies! You win!\n";
                        isPlay = false;
                    }
                    break;

                case 3:
                    if (currentTarget == nullptr ||
                        !currentTarget->IsAlive()) {
                        currentTarget = nullptr;
                        std::cout << "\nSelect a living target first!\n";
                        break;
                    }

                    if (medkits == 0) {
                        std::cout << "\nNo medkits left!\n";
                        break;
                    }

                    player.Heal(8);
                    medkits--;
                    std::cout << "\nYou used a medkit!\n";

                    currentTarget->Attack(player);
                    std::cout << "\nEnemy attacks you back!\n";

                    if (!player.IsAlive()) {
                        std::cout << "\nYou are dead! Game over!\n";
                        isPlay = false;
                    }
                    break;

                default:
                    std::cout << "\nUnknown command!\n";
                    break;
            }
        }

        std::cout << "\nGame finished.\n";
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    Game game;
    game.Run();

    return 0;
}
