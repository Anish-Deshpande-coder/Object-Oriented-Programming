#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

// Abstract base class: Noble
class Noble {
public:
    Noble(const string& name) : name(name), alive(true) {}

    virtual void battle(Noble& opponent) = 0; // Pure virtual
    virtual void display(ostream& os) const = 0; // Pure virtual
    virtual double getStrength() const = 0;  // Pure virtual
    virtual void adjustStrength(double ratio) = 0;  // Pure virtual

    bool isAlive() const { return alive; }
    void die() { alive = false; }

    const string& getName() const { return name; }

    virtual ~Noble() = default;

protected:
    string name;
    bool alive;
};

ostream& operator<<(ostream& os, const Noble& noble) {
    noble.display(os);
    return os;
}

// Forward declaration of Protector class
class Protector;

// Derived Noble class: Lord
class Lord : public Noble {
public:
    using Noble::Noble;

    bool hires(Protector& protector);
    void removeProtector(Protector* protector);
    void fires(Protector& protector);
    void battle(Noble& opponent) override;
    void display(ostream& os) const override;
    double getStrength() const override;
    void adjustStrength(double ratio) override;

private:
    vector<Protector*> protectors;
};

// Definition of Protector class
class Protector {
public:
    Protector(const string& name, double strength)
        : name(name), strength(strength), hired(false), lord(nullptr), alive(true) {}

    virtual void defend() const = 0; // Pure virtual

    const string& getName() const { return name; }

    double getStrength() const { return strength; }
    void setStrength(double newStrength) { strength = newStrength; }

    bool isHired() const { return hired; }
    bool isAlive() const { return alive; }

    void getHired(Lord* newLord) {
        lord = newLord;
        hired = true;
    }

    void runAway() {
        if (lord && alive) {
            cout << name << " flees in terror, abandoning their lord, " << lord->getName() << endl;
            lord->removeProtector(this);
            hired = false;
            lord = nullptr;
        }
    }

    virtual ~Protector() = default;

protected:
    string name;
    double strength;
    bool hired;
    Lord* lord;  // Pointer to a fully defined Lord
    bool alive;
};

ostream& operator<<(ostream& os, const Protector& protector) {
    os << protector.getName() << " has strength " << protector.getStrength();
    return os;
}

// Implementations of Lord methods
bool Lord::hires(Protector& protector) {
    if (isAlive() && !protector.isHired() && protector.isAlive()) {
        protector.getHired(this);
        protectors.push_back(&protector);
        return true;
    } else {
        cout << getName() << " failed to hire " << protector.getName() << endl;
        return false;
    }
}

void Lord::removeProtector(Protector* protector) {
    auto it = remove(protectors.begin(), protectors.end(), protector);
    if (it != protectors.end()) {
        protectors.erase(it, protectors.end());
    }
}

void Lord::fires(Protector& protector) {
    cout << protector.getName() << ", you don't work for me anymore! -- " << getName() << endl;
    removeProtector(&protector);
    protector.getHired(nullptr);
}

void Lord::battle(Noble& opponent) {
    cout << getName() << " battles " << opponent.getName() << endl;

    if (!isAlive() && !opponent.isAlive()) {
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
        return;
    }

    if (!isAlive()) {
        cout << "He's dead, " << opponent.getName() << endl;
        return;
    }

    if (!opponent.isAlive()) {
        cout << "He's dead, " << getName() << endl;
        return;
    }

    double myStrength = getStrength();
    double opponentStrength = opponent.getStrength();

    if (myStrength > opponentStrength) {
        cout << getName() << " defeats " << opponent.getName() << endl;
        adjustStrength(opponentStrength / myStrength);
        opponent.die();
    } else if (myStrength < opponentStrength) {
        cout << opponent.getName() << " defeats " << getName() << endl;
        opponent.adjustStrength(myStrength / opponentStrength);
        die();
    } else {
        cout << "Mutual annihilation: " << getName() << " and " << opponent.getName() << " die at each other's hands" << endl;
        die();
        opponent.die();
    }
}

void Lord::display(ostream& os) const {
    os << name << " has an army of size: " << protectors.size() << endl;
    for (const Protector* protector : protectors) {
        os << "\t" << *protector << endl;
    }
}

double Lord::getStrength() const {
    double total = 0;
    for (const Protector* protector : protectors) {
        total += protector->getStrength();
    }
    return total;
}

void Lord::adjustStrength(double ratio) {
    for (Protector* protector : protectors) {
        protector->setStrength(protector->getStrength() * (1 - ratio));
    }
}

// Derived Noble class: PersonWithStrengthToFight
class PersonWithStrengthToFight : public Noble {
public:
    PersonWithStrengthToFight(const string& name, double strength)
        : Noble(name), strength(strength) {}

    void battle(Noble& opponent) override {
        cout << getName() << " battles " << opponent.getName() << endl;
        if (!isAlive() && !opponent.isAlive()) {
            cout << "Oh, NO! They're both dead!" << endl;
        } else if (!isAlive()) {
            cout << getName() << " is already dead." << endl;
        } else if (!opponent.isAlive()) {
            cout << opponent.getName() << " is already dead." << endl;
        }
    }

    void display(ostream& os) const override {
        os << name << " has strength: " << strength << endl;
    }

    double getStrength() const override { return strength; }

    void adjustStrength(double ratio) override {
        strength *= (1 - ratio);
    }

private:
    double strength;
};

// Derived Protectors
class Archer : public Protector {
public:
    using Protector::Protector;

    void defend() const override {
        cout << "TWANG! " << name << " says: Take that in the name of my lord, " << lord->getName() << endl;
    }
};

class Swordsman : public Protector {
public:
    using Protector::Protector;

    void defend() const override {
        cout << "CLANG! " << name << " says: Take that in the name of my lord, " << lord->getName() << endl;
    }
};

class Wizard : public Protector {
public:
    using Protector::Protector;

    void defend() const override {
        cout << "POOF!" << endl;
    }
};

// Main Function
int main() {
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hires(samantha);
    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250);
    Lord janet("Janet");
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);
    janet.hires(stout);
    janet.hires(samantha);  // fails because samantha works for sam.
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);
    cout << "\n==========\nNobles: \n"
         << sam << endl
         << randy << endl
         << janet << endl
         << barclay << endl
         << joe << endl
         << "\n==========\n";
    joe.battle(randy);             // joe has no army and dies.
    joe.battle(sam);               // joe is dead
    janet.battle(barclay);         // barclay wins
    Archer pethora("Pethora", 50);
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hires(pethora);          // janet is dead, so can't hire
    sam.hires(thora);              // sam brings in reinforcements
    sam.hires(pethora);
    sam.hires(merlin);
    janet.battle(barclay);         // Silly janet
    sam.battle(barclay);           // Go Sam!
    samantha.runAway();            // Samantha has had enough
    sam.fires(thora);              // Sam fires thora.
    joe.battle(barclay);           // They're both dead already
    cout << "\n==========\"" << endl;
}