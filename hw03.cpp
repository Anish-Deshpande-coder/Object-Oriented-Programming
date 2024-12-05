#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Warrior {
    //Function prototype for statusReport function
    void statusReport(const std::vector<Warrior>& warriors);
public:
    Warrior(const string& name, const string& weaponName, int weaponStrength)
        : name(name), weapon(weaponName, weaponStrength) {}
    // Output operator to print the warrior's status
    friend ostream& operator<<(ostream& os, const Warrior& warrior);
    void battle(Warrior& opponent);
    const string& getName() const { return name; }

private:
    string name;
    // Nested Weapon class
    class Weapon {
    public:
        Weapon(const string& weaponName, int strength)
            : name(weaponName), strength(strength) {}
        // Methods to access and change warrior's weapon strength
        int getStrength() const {return strength;}
        void reduceStrength(int amount) { strength = max(0, strength - amount); }
        friend ostream& operator<<(ostream& os, const Weapon& weapon);
    private:
        string name;
        int strength;
    };
    Weapon weapon;
    // Method to get the warrior's current strength
    int getStrength() const { return weapon.getStrength(); }
    // Method to set the weapon's strength to 0 (for death scenario)
    void die() { weapon.reduceStrength(weapon.getStrength()); }
};
// Output operator for weapon class
ostream& operator<<(ostream& os, const Warrior::Weapon& weapon) {
    os << "weapon: " << weapon.name << ", " << weapon.strength;
    return os;
}
// Output operator for the warrior class
ostream& operator<<(ostream& os, const Warrior& warrior) {
    os << "Warrior: " << warrior.name << ", " << warrior.weapon;
    return os;
}

// Battle function
void Warrior::battle(Warrior& opponent) {
    cout << name << " battles " << opponent.name << endl;
    int strength1 = getStrength();
    int strength2 = opponent.getStrength();
    if (strength1 == 0 && strength2 == 0) {
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    } else if (strength1 == 0) {
        cout << "He's dead, " << name << endl;
    } else if (strength2 == 0) {
        cout << "He's dead, " << opponent.name << endl;
    } else if (strength1 > strength2) {
        cout << name << " defeats " << opponent.name << endl;
        weapon.reduceStrength(strength2); // Reduce based on opponent's strength
        opponent.die();
    } else if (strength2 > strength1) {
        cout << opponent.name << " defeats " << name << endl;
        opponent.weapon.reduceStrength(strength1); // Reduce based on opponent's strength
        die();
    } else {
        cout << "Mutual Annihilation: " << name << " and " << opponent.name
                  << " die at each other's hands" << endl;
        die();
        opponent.die();
    }
}
// Status report for the warriors and their status
void statusReport(const std::vector<Warrior>& warriors) {
    cout << "There are: " << warriors.size() << " warriors" << endl;
    for (const Warrior& warrior : warriors) {
        cout << warrior << endl;
    }
}

//Main function
int main() {
    ifstream infile("warriors.txt");
    string command;
    vector<Warrior> warriors;
    while (infile >> command) {
        if (command == "Warrior") {
            string name, weaponName;
            int weaponStrength;
            infile >> name >> weaponName >> weaponStrength;
            // Add warrior to the list
            warriors.emplace_back(name, weaponName, weaponStrength);
        } else if (command == "Battle") {
            string name1, name2;
            infile >> name1 >> name2;
            // Find the warriors by name and battle them using pointers
            Warrior* warrior1 = nullptr;
            Warrior* warrior2 = nullptr;
            for (Warrior& warrior : warriors) {
                if (warrior.getName() == name1) {
                    warrior1 = &warrior;
                }
                if (warrior.getName() == name2) {
                    warrior2 = &warrior;
                }
            }
            if (warrior1 && warrior2) {
                warrior1->battle(*warrior2);
            } else {
                cerr << "Error: One of the warriors does not exist." << endl;
            }
        } else if (command == "Status") {
            statusReport(warriors);
        }
    }
}