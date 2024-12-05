#pragma once
#include <iostream>
#include <string>

namespace WarriorCraft {
    class Noble;  // Forward declaration

    class Warrior {
    public:
        Warrior(const std::string& name, int strength);
        bool isHired() const;
        int getStrength() const;
        void setStrength(int strength);
        void setNoble(Noble* noble);  // Sets or removes the noble association
        void runaway();
        friend std::ostream& operator<<(std::ostream& os, const Warrior& warrior);
        std::string getName() const;
    private:
        std::string name;
        int strength;
        Noble* noble;
    };
}
