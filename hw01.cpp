#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


char decryptChar(char ch, const int rotation) {
    if (ch >= 'A' && ch <= 'Z') {
        ch = ch - rotation;
        if (ch < 'A') {
            ch += 26;
        }
    }
    return ch;
}


void decryptLine(string & line, int rotation) {
    for (size_t i = 0; i < line.length(); ++i) {
        line[i] = decryptChar(line[i], rotation);
    }
}

int main() {
    ifstream inFile("encrypted.txt");
    if (!inFile) {
        cerr << "Unable to open file";
        return 1;
    }
    int rotation;
    inFile >> rotation;
    vector <string> lines;
    string line;
    while (getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();
    for (int i = lines.size() - 1; i >= 0; --i) {
        decryptLine(lines[i], rotation);
        cout << lines[i] << endl;
    }
    return 0;
}
