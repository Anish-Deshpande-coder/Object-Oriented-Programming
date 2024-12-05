#include "Noble.h"
#include "Warrior.h"
#include <iostream>

namespace WarriorCraft {

    Noble::Noble(const std::string& name) : name(name), alive(true) {}

    bool Noble::hire(Warrior& warrior) {
        if (!warrior.isHired() && alive) {
            army.push_back(&warrior);
            warrior.setNoble(this);  // Set noble to this Noble
            return true;
        }
        std::cout << name << " failed to hire " << warrior.getName() << std::endl;
        return false;
    }

    bool Noble::fire(Warrior& warrior) {
        for (size_t i = 0; i < army.size(); ++i) {
            if (army[i] == &warrior) {
                std::cout << warrior.getName() << ", you don't work for me anymore! -- " << name << std::endl;
                army[i] = army.back();
                army.pop_back();
                warrior.setNoble(nullptr);  // Remove noble association
                return true;
            }
        }
        return false;
    }

    void Noble::battle(Noble& opponent) {
        std::cout << name << " battles " << opponent.name << std::endl;

        int myStrength = getArmyStrength();
        int opponentStrength = opponent.getArmyStrength();

        if (!alive && !opponent.alive) {
            std::cout << "Oh, NO! They're both dead! Yuck!" << std::endl;
        }
        else if (myStrength == opponentStrength) {
            std::cout << "Mutual Annihilation: " << name << " and " << opponent.name
                      << " die at each other's hands" << std::endl;
            updateArmyStrength(0);
            opponent.updateArmyStrength(0);
            alive = opponent.alive = false;
        }
        else if (myStrength > opponentStrength) {
            std::cout << name << " defeats " << opponent.name << std::endl;
            double ratio = 1 - static_cast<double>(opponentStrength) / myStrength;
            updateArmyStrength(ratio);
            opponent.updateArmyStrength(0);
            opponent.alive = false;
        }
        else {
            std::cout << opponent.name << " defeats " << name << std::endl;
            double ratio = 1 - static_cast<double>(myStrength) / opponentStrength;
            opponent.updateArmyStrength(ratio);
            updateArmyStrength(0);
            alive = false;
        }
    }

    int Noble::getArmyStrength() const {
        int totalStrength = 0;
        for (const Warrior* warrior : army) {
            totalStrength += warrior->getStrength();
        }
        return totalStrength;
    }

    void Noble::updateArmyStrength(double ratio) {
        for (Warrior* warrior : army) {
            warrior->setStrength(warrior->getStrength() * ratio);
        }
    }

    std::ostream& operator<<(std::ostream& os, const Noble& noble) {
        os << noble.name << " has an army of " << noble.army.size() << std::endl;
        for (const Warrior* warrior : noble.army) {
            os << "\t" << *warrior << std::endl;
        }
        return os;
    }
}
