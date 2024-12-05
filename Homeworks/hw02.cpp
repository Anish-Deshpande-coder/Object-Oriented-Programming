#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct Warrior {
    string name;
    int strength;
};

//listed the function prototypes
void addWarrior(vector<Warrior>& warriors, const string& name, int strength);
void battleWarriors(vector<Warrior>& warriors, const string& name1, const string& name2);
void showStatus(const vector<Warrior>& warriors);
int findWarrior(const vector<Warrior>& warriors, const string& name);

// main function that reads from warriors.txt and not a user input and has the
// three different commands.
int main() {
    ifstream file("warriors.txt");
    if (!file) {
        cerr << "Failed to open warriors.txt";
        return 1;
    }
    vector<Warrior> warriors;
    string command;
    while (file >> command) {
        if (command == "Warrior") {
            string name;
            int strength;
            file >> name >> strength;
            addWarrior(warriors, name, strength);
        } else if (command == "Battle") {
            string name1, name2;
            file >> name1 >> name2;
            battleWarriors(warriors, name1, name2);
        } else if (command == "Status") {
            showStatus(warriors);
        }
    }
    return 0;
}

//This function adds a warrior name to the vector but checks to make sure
// that the warrior name isn't already there, if it is, an error message is outputted
void addWarrior(vector<Warrior>& warriors, const string& name, int strength) {
    if (findWarrior(warriors, name) != -1) {
        cerr << "Warrior " << name << " already exists!\n";
        return;
    }
    Warrior newWarrior = {name, strength};
    warriors.push_back(newWarrior);
}

// finds the index of the warrior we are looking for in the warrior vector
/* tried to make this function return a type size_t but it showed an error
 so I had to keep it so that it returned an integer */
int findWarrior(const vector<Warrior>& warriors, const string& name) {
    for (size_t i = 0; i < warriors.size(); ++i) {
        if (warriors[i].name == name) {
            return i;
        }
    }
    return -1;
}

// battle function between the warriors based on strength
void battleWarriors(vector<Warrior>& warriors, const string& firstName, const string& secondName) {
    int index1 = findWarrior(warriors, firstName);
    int index2 = findWarrior(warriors, secondName);
    if (index1 == -1 || index2 == -1) {
        cerr << "One or both warriors not found!\n";
        return;
    }
    Warrior& warrior1 = warriors[index1];
    Warrior& warrior2 = warriors[index2];
    cout << warrior1.name << " battles " << warrior2.name << endl;
    if (warrior1.strength == 0 && warrior2.strength == 0) {
        cout << "Oh, NO! They're both dead! Yuck!\n";
    } else if (warrior1.strength == 0) {
        cout << "He's dead, " << warrior2.name << endl;
    } else if (warrior2.strength == 0) {
        cout << "He's dead, " << warrior1.name << endl;
    } else if (warrior1.strength == warrior2.strength) {
        cout << "Mutual Annihilation: " << warrior1.name << " and " << warrior2.name << " die at each other's hands\n";
        warrior1.strength = 0;
        warrior2.strength = 0;
    } else if (warrior1.strength > warrior2.strength) {
        cout << warrior1.name << " defeats " << warrior2.name << endl;
        warrior1.strength -= warrior2.strength;
        warrior2.strength = 0;
    } else {
        cout << warrior2.name << " defeats " << warrior1.name << endl;
        warrior2.strength -= warrior1.strength;
        warrior1.strength = 0;
    }
}

// shows the names and strengths of each warrior
void showStatus(const vector<Warrior>& warriors) {
    cout << "There are: " << warriors.size() << " warriors\n";
    for (const Warrior& warrior : warriors) {
        cout << "Warrior: " << warrior.name << ", strength: " << warrior.strength << endl;
    }
}