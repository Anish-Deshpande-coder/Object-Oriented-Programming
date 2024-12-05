#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm> // For swap
#include <utility>   // For std::swap

using namespace std;

struct Hydrocarbon {
    vector<string> names;
    int carbon;
    int hydrogen;
};

void openFile(ifstream &fileStream);
void fillVector(ifstream &fileStream, vector<Hydrocarbon> &hydrocarbons);
void insertHydrocarbon(vector<Hydrocarbon> &hydrocarbons, const string &name, int carbon, int hydrogen);
size_t findHydrocarbon(const vector<Hydrocarbon> &hydrocarbons, int carbon, int hydrogen);
void printingHydrocarbon(const Hydrocarbon &hydrocarbon);
void displayHydrocarbons(const vector<Hydrocarbon> &hydrocarbons);
void sortHydrocarbons(vector<Hydrocarbon> &hydrocarbons);

int main() {
    ifstream fileStream;
    vector<Hydrocarbon> hydrocarbons;
    openFile(fileStream);
    fillVector(fileStream, hydrocarbons);
    fileStream.close();
    cout << "Unsorted Hydrocarbons:\n";
    displayHydrocarbons(hydrocarbons);
    sortHydrocarbons(hydrocarbons);
    cout << "\nSorted Hydrocarbons:\n";
    displayHydrocarbons(hydrocarbons);
    return 0;
}

void openFile(ifstream &fileStream) {
    string filename;
    do {
        cout << "Enter the file name: ";
        cin >> filename;
        fileStream.open(filename);
    } while (!fileStream);
}

void fillVector(ifstream &fileStream, vector<Hydrocarbon> &hydrocarbons) {
    string name;
    int carbon, hydrogen;
    char c, h;

    while (fileStream >> name >> c >> carbon >> h >> hydrogen) {
        insertHydrocarbon(hydrocarbons, name, carbon, hydrogen);
    }
}

void insertHydrocarbon(vector<Hydrocarbon> &hydrocarbons, const string &name, int carbon, int hydrogen) {
    size_t index = findHydrocarbon(hydrocarbons, carbon, hydrogen);
    if (index != hydrocarbons.size()) {
        hydrocarbons[index].names.push_back(name);
    } else {
        Hydrocarbon newHydrocarbon;
        newHydrocarbon.names.push_back(name);
        newHydrocarbon.carbon = carbon;
        newHydrocarbon.hydrogen = hydrogen;
        hydrocarbons.push_back(newHydrocarbon);
    }
}

size_t findHydrocarbon(const vector<Hydrocarbon> &hydrocarbons, int carbon, int hydrogen) {
    for (size_t i = 0; i < hydrocarbons.size(); ++i) {
        if (hydrocarbons[i].carbon == carbon && hydrocarbons[i].hydrogen == hydrogen) {
            return i;
        }
    }
    return hydrocarbons.size();
}

void printingHydrocarbon(const Hydrocarbon &hydrocarbon) {
    cout << "C" << hydrocarbon.carbon << "H" << hydrocarbon.hydrogen << " ";
    for (const string &name : hydrocarbon.names) {
        cout << name << " ";
    }
    cout << endl;
}

void displayHydrocarbons(const vector<Hydrocarbon> &hydrocarbons) {
    for (const Hydrocarbon &hc : hydrocarbons) {
        printingHydrocarbon(hc);
    }
    cout << endl;
}

void sortHydrocarbons(vector<Hydrocarbon> &hydrocarbons) {
    for (size_t i = 0; i < hydrocarbons.size() - 1; ++i) {
        for (size_t j = 0; j < hydrocarbons.size() - i - 1; ++j) {
            if (hydrocarbons[j].carbon > hydrocarbons[j + 1].carbon ||
               (hydrocarbons[j].carbon == hydrocarbons[j + 1].carbon &&
                hydrocarbons[j].hydrogen > hydrocarbons[j + 1].hydrogen)) {
                swap(hydrocarbons[j], hydrocarbons[j + 1]);
            }
        }
    }
}

