#include "Warrior.h"
#include "Noble.h"
#include <iostream>

namespace WarriorCraft {

    Warrior::Warrior(const std::string& name, int strength)
        : name(name), strength(strength), noble(nullptr) {}

    bool Warrior::isHired() const {
        return noble != nullptr;
    }

    int Warrior::getStrength() const {
        return strength;
    }

    void Warrior::setStrength(int newStrength) {
        strength = newStrength;
    }

    void Warrior::setNoble(Noble* newNoble) {
        noble = newNoble;
    }

    void Warrior::runaway() {
        if (noble) {
            std::cout << name << " flees in terror, abandoning his lord, "
                      << noble->getName() << std::endl;
            noble->fire(*this);  // Noble handles removing this warrior from its army
            noble = nullptr;     // Clear noble association after running away
        }
    }

    std::string Warrior::getName() const {
        return name;
    }

    std::ostream& operator<<(std::ostream& os, const Warrior& warrior) {
        os << warrior.name << ": " << warrior.strength;
        return os;
    }

}
