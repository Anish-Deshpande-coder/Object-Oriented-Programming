/*
hw04_start.cpp
  Association: Noble - Warrior
  Test code for hw04
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Your Noble and Warrior classes should go here.
// ...
class Warrior {
public:
    Warrior(const string& name, double strength) : name(name), strength(strength), employed(false) {}
    const string& getName() const { return name; }
    double getStrength() const { return strength; }
    bool isEmployed() const { return employed; }
    void setEmployed(bool status) { employed = status; }
    void setStrength(double newStrength) { strength = newStrength; }
    void display(ostream& os) const {
        os << name << ": " << strength;
    }
private:
    string name;
    double strength;
    bool employed;
};
ostream& operator<<(ostream& os, const Warrior& warrior) {
    warrior.display(os);
    return os;
}
class Noble {
public:
    Noble(const string& name) : name(name), alive(true) {}
    const string& getName() const { return name; }
    bool hire(Warrior& warrior) {
        if (!alive) {
            cout << name << " is dead and cannot hire " << warrior.getName() << endl;
            return false;
        }
        if (warrior.isEmployed()) {
            cout << warrior.getName() << " is already employed!" << endl;
            return false;
        }
        army.push_back(&warrior);
        warrior.setEmployed(true);
        return true;
    }

    bool fire(Warrior& warrior) {
        if (!alive) {
            cout << name << " is dead and cannot fire " << warrior.getName() << endl;
            return false;
        }
        for (size_t i = 0; i < army.size(); ++i) {
            if (army[i] == &warrior) {
                warrior.setEmployed(false);
                army.erase(army.begin() + i);
                cout << warrior.getName() << ", you're fired! -- " << name << endl;
                return true;
            }
        }
        return false;
    }

    double getArmyStrength() const {
        double totalStrength = 0;
        for (const Warrior* warrior : army) {
            totalStrength += warrior->getStrength();
        }
        return totalStrength;
    }

    void battle(Noble& opponent) {
        cout << name << " battles " << opponent.getName() << endl;

        if (!alive && !opponent.alive) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
            return;
        }
        if (!alive) {
            cout << "He's dead, " << opponent.getName() << endl;
            return;
        }
        if (!opponent.alive) {
            cout << "He's dead, " << name << endl;
            return;
        }
        double strength1 = getArmyStrength();
        double strength2 = opponent.getArmyStrength();
        if (strength1 == strength2) {
            cout << "Mutual Annihilation: " << name << " and " << opponent.getName()
                 << " die at each other's hands" << endl;
            die();
            opponent.die();
        } else if (strength1 > strength2) {
            cout << name << " defeats " << opponent.getName() << endl;
            reduceArmyStrength(strength2 / strength1);
            opponent.die();
        } else {
            cout << opponent.getName() << " defeats " << name << endl;
            opponent.reduceArmyStrength(strength1 / strength2);
            die();
        }
    }

    void die() {
        alive = false;
        for (Warrior* warrior : army) {
            warrior->setStrength(0);
        }
    }

    void reduceArmyStrength(double ratio) {
        for (Warrior* warrior : army) {
            double newStrength = warrior->getStrength() * (1 - ratio);
            warrior->setStrength(newStrength);
        }
    }

    void display(ostream& os) const {
        os << name << " has an army of " << army.size() << endl;
        for (const Warrior* warrior : army) {
            os << "\t" << *warrior << endl;
        }
    }

private:
    string name;
    vector<Warrior*> army;
    bool alive;
};
ostream& operator<<(ostream& os, const Noble& noble) {
    noble.display(os);
    return os;
}


int main()
{

    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);
    art.hire(nimoy);

    cout << "==========\n\n"
         << "Status before all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n\n";

    art.fire(cheetah);
    cout << art << endl;

    lance.fire(nimoy);
    cout << lance << endl;
    cout << "==========\n\n";

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "==========\n\n"
         << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";

} // main
