#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Warrior.h"

namespace WarriorCraft {
    class Noble {
    public:
        Noble(const std::string& name);
        bool hire(Warrior& warrior);
        bool fire(Warrior& warrior);
        void battle(Noble& opponent);
        std::string getName() const;  // Getter for Noble's name
        friend std::ostream& operator<<(std::ostream& os, const Noble& noble);
    private:
        std::string name;
        bool alive;
        std::vector<Warrior*> army;
        int getArmyStrength() const;
        void updateArmyStrength(double ratio);
    };
}
