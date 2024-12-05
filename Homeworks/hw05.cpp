#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Warrior {
public:
    friend ostream& operator<<(ostream& os, const Warrior& warrior) {
        os << warrior.name << ": " << warrior.strength;
        return os;
    }

    Warrior(const string& name, int strength)
        : name(name), strength(strength), employed(false) {}

    string getName() const { return name; }
    int getStrength() const { return strength; }
    void setStrength(int newStrength) { strength = newStrength; }
    bool isEmployed() const { return employed; }
    void hire() { employed = true; }
    void fire() { employed = false; }

private:
    string name;
    int strength;
    bool employed;
};

class Noble {
public:
    friend ostream& operator<<(ostream& os, const Noble& noble) {
        os << noble.name << " has an army of " << noble.army.size() << endl;
        for (const Warrior* warrior : noble.army) {
            os << "    " << *warrior << endl;
        }
        return os;
    }

    Noble(const string& name) : name(name), alive(true) {}

    string getName() const { return name; }
    bool isAlive() const { return alive; }

    //hire method
    void hire(Warrior* warrior) {
        if (!warrior->isEmployed()) {
            army.push_back(warrior);
            warrior->hire();
        } else {
            cout << "Error: Warrior " << warrior->getName() << " is already employed!" << endl;
        }
    }

    //fire method
    void fire(Warrior* warrior) {
        for (size_t i = 0; i < army.size(); ++i) {
            if (army[i] == warrior) {
                warrior->fire();
                army.erase(army.begin() + i);
                cout << warrior->getName() << " has been fired by " << name << endl;
                return;
            }
        }
        cout << "Error: Warrior " << warrior->getName() << " not found in " << name << "'s army!" << endl;
    }


    // battle method
    void battle(Noble& otherNoble) {
        cout << name << " battles " << otherNoble.name << endl;
        if (!alive && !otherNoble.alive) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        } else if (!alive) {
            cout << "He's dead, " << otherNoble.name << endl;
        } else if (!otherNoble.alive) {
            cout << "He's dead, " << name << endl;
        } else {
            int myStrength = getArmyStrength();
            int otherStrength = otherNoble.getArmyStrength();

            if (myStrength > otherStrength) {
                cout << name << " defeats " << otherNoble.name << endl;
                adjustStrength(1.0 - (double(otherStrength) / myStrength));
                otherNoble.kill();
            } else if (myStrength < otherStrength) {
                cout << otherNoble.name << " defeats " << name << endl;
                otherNoble.adjustStrength(1.0 - (double(myStrength) / otherStrength));
                kill();
            } else {
                cout << "Mutual Annihilation: " << name << " and " << otherNoble.name << " die at each other's hands" << endl;
                kill();
                otherNoble.kill();
            }
        }
    }

    //adjustStrength method either enhances or reduces a warrior's strength
    void adjustStrength(double ratio) {
        for (Warrior* warrior : army) {
            warrior->setStrength(int(warrior->getStrength() * ratio));
        }
    }
    // kill method shows when the warrior has no strength
    void kill() {
        alive = false;
        for (Warrior* warrior : army) {
            warrior->setStrength(0);
        }
    }

    //This method gets and returns the total strength of the army
    int getArmyStrength() const {
        int totalStrength = 0;
        for (const Warrior* warrior : army) {
            totalStrength += warrior->getStrength();
        }
        return totalStrength;
    }

private:
    string name;
    vector<Warrior*> army;
    bool alive;
};

// Helper function to find Noble by name
Noble* findNoble(const vector<Noble*>& nobles, const string& name) {
    for (Noble* noble : nobles) {
        if (noble->getName() == name) {
            return noble;
        }
    }
    return nullptr;
}

// Helper function to find Warrior by name
Warrior* findWarrior(const vector<Warrior*>& warriors, const string& name) {
    for (Warrior* warrior : warriors) {
        if (warrior->getName() == name) {
            return warrior;
        }
    }
    return nullptr;
}

//main function that addresses all the possible inconsistencies
int main() {
    vector<Noble*> nobles;
    vector<Warrior*> warriors;

    ifstream file("nobleWarriors.txt");
    if (!file) {
        cerr << "Failed to open file!" << endl;
        return 1;
    }
    string command;
    while (file >> command) {
        if (command == "Noble") {
            string nobleName;
            file >> nobleName;
            if (findNoble(nobles, nobleName)) {
                cout << "Error: Noble " << nobleName << " already exists!" << endl;
            } else {
                nobles.push_back(new Noble(nobleName));
            }
        } else if (command == "Warrior") {
            string warriorName;
            int strength;
            file >> warriorName >> strength;
            if (findWarrior(warriors, warriorName)) {
                cout << "Error: Warrior " << warriorName << " already exists!" << endl;
            } else {
                warriors.push_back(new Warrior(warriorName, strength));
            }
        } else if (command == "Hire") {
            string nobleName, warriorName;
            file >> nobleName >> warriorName;
            Noble* noble = findNoble(nobles, nobleName);
            Warrior* warrior = findWarrior(warriors, warriorName);
            if (!noble) {
                cout << "Error: Noble " << nobleName << " does not exist!" << endl;
            } else if (!warrior) {
                cout << "Error: Warrior " << warriorName << " does not exist!" << endl;
            } else {
                noble->hire(warrior);
            }
        } else if (command == "Fire") {
            string nobleName, warriorName;
            file >> nobleName >> warriorName;
            Noble* noble = findNoble(nobles, nobleName);
            Warrior* warrior = findWarrior(warriors, warriorName);
            if (!noble) {
                cout << "Error: Noble " << nobleName << " does not exist!" << endl;
            } else if (!warrior) {
                cout << "Error: Warrior " << warriorName << " does not exist!" << endl;
            } else {
                noble->fire(warrior);
            }
        } else if (command == "Battle") {
            string noble1, noble2;
            file >> noble1 >> noble2;
            Noble* nobleA = findNoble(nobles, noble1);
            Noble* nobleB = findNoble(nobles, noble2);
            if (!nobleA) {
                cout << "Error: Noble " << noble1 << " does not exist!" << endl;
            } else if (!nobleB) {
                cout << "Error: Noble " << noble2 << " does not exist!" << endl;
            } else {
                nobleA->battle(*nobleB);
            }
        } else if (command == "Status") {
            cout << "Status\n========\n";
            for (Noble* noble : nobles) {
                cout << *noble;
            }
            cout << "Unemployed Warriors:\n";
            for (Warrior* warrior : warriors) {
                if (!warrior->isEmployed()) {
                    cout << *warrior << endl;
                }
            }
        } else if (command == "Clear") {
            for (Noble* noble : nobles) {
                delete noble;
            }
            for (Warrior* warrior : warriors) {
                delete warrior;
            }
            nobles.clear();
            warriors.clear();
        }
    }

    file.close();
    return 0;
}
