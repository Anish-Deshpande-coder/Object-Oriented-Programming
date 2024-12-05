#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace WarriorCraft {
    class Warrior;

    class Noble {
    public:
        Noble(const string& name) : name(name), alive(true) {}
        bool hire(Warrior& warrior);
        bool fire(Warrior& warrior);
        void battle(Noble& opponent);
        friend ostream& operator<<(ostream& os, const Noble& noble);
        string getName() const { return name; }
    private:
        string name;
        bool alive;
        vector<Warrior*> army;
        int getArmyStrength() const;
        void updateArmyStrength(double ratio);
    };

    class Warrior {
    public:
        Warrior(const string& name, int strength) : name(name), strength(strength), noble(nullptr) {}
        bool isHired() const { return noble != nullptr; }
        int getStrength() const { return strength; }
        void setStrength(int newStrength) { strength = newStrength; }
        void setNoble(Noble* newNoble) { noble = newNoble; }
        void runaway();
        string getName() const { return name; }
        friend ostream& operator<<(ostream& os, const Warrior& warrior);
    private:
        string name;
        int strength;
        Noble* noble;
    };

    bool Noble::hire(Warrior& warrior) {
        if (!warrior.isHired() && alive) {
            army.push_back(&warrior);
            warrior.setNoble(this);  // Set noble to this Noble
            return true;
        }
        cout << name << " failed to hire " << warrior.getName() << endl;
        return false;
    }

    bool Noble::fire(Warrior& warrior) {
        for (size_t i = 0; i < army.size(); ++i) {
            if (army[i] == &warrior) {
                cout << warrior.getName() << ", you don't work for me anymore! -- " << name << endl;
                army[i] = army.back();
                army.pop_back();
                warrior.setNoble(nullptr);  // Remove noble association
                return true;
            }
        }
        return false;
    }

    void Warrior::runaway() {
        if (noble) {
            cout << name << " flees in terror, abandoning his lord, " << noble->getName() << endl;
            noble->fire(*this);
            noble = nullptr;
        }
    }

    void Noble::battle(Noble& opponent) {
        cout << name << " battles " << opponent.name << endl;

        int myStrength = getArmyStrength();
        int opponentStrength = opponent.getArmyStrength();

        if (!alive && !opponent.alive) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        else if (myStrength == opponentStrength) {
            cout << "Mutual Annihilation: " << name << " and " << opponent.name
                 << " die at each other's hands" << endl;
            updateArmyStrength(0);
            opponent.updateArmyStrength(0);
            alive = opponent.alive = false;
        }
        else if (myStrength > opponentStrength) {
            cout << name << " defeats " << opponent.name << endl;
            updateArmyStrength(1 - static_cast<double>(opponentStrength) / myStrength);
            opponent.updateArmyStrength(0);
            opponent.alive = false;
        }
        else {
            cout << opponent.name << " defeats " << name << endl;
            opponent.updateArmyStrength(1 - static_cast<double>(myStrength) / opponentStrength);
            updateArmyStrength(0);
            alive = false;
        }
    }

    int Noble::getArmyStrength() const {
        int totalStrength = 0;
        for (Warrior* warrior : army) {
            totalStrength += warrior->getStrength();
        }
        return totalStrength;
    }

    void Noble::updateArmyStrength(double ratio) {
        for (Warrior* warrior : army) {
            warrior->setStrength(static_cast<int>(warrior->getStrength() * ratio));
        }
    }

    ostream& operator<<(ostream& os, const Noble& noble) {
        os << noble.name << " has an army of " << noble.army.size() << endl;
        for (Warrior* warrior : noble.army) {
            os << "\t" << *warrior << endl;
        }
        return os;
    }

    ostream& operator<<(ostream& os, const Warrior& warrior) {
        os << warrior.name << ": " << warrior.strength;
        return os;
    }
}

//I added the test code here because it wouldn't work in separate compilation but I will submit the test code as well
using namespace WarriorCraft;

int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 4);
    Warrior sky("Leia", 6);
    Warrior wizard("Merlin", 9);
    Warrior jaffa("Teal'c", 9);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(jaffa);
    art.hire(cheetah);
    art.hire(wizard);
    art.hire(sky);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(nimoy);

    cout << "================ Initial Status ===============" << endl;
    cout << art << endl
         << lance << endl
         << jim << endl
         << linus << endl
         << billie << endl;
    cout << "===============================================\n\n";

    art.fire(cheetah);
    wizard.runaway();
    cout << endl << art << endl;

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "\n================ Final Status ===============" << endl;
    cout << art << endl
         << lance << endl
         << jim << endl
         << linus << endl
         << billie << endl;

    // Tarzan and Merlin should be unemployed
    cout << "Tarzan's Hire Status: " << boolalpha
         << cheetah.isHired() << endl;
    cout << "Merlin's Hire Status: " << boolalpha
         << wizard.isHired() << endl;
    cout << "===============================================\n\n";
}
