/*
  rec06_begin.cpp
  CS2124

  Focus: Dynamic arrays and copy control
 */

#include <string>
#include <iostream>
#include <stdexcept>  // for std::invalid_argument
using namespace std;

// Position class
class Position {
    friend ostream& operator<<(ostream& os, const Position& rhs) {
        os << '[' << rhs.title << ',' << rhs.salary << ']';
        return os;
    }
public:
    Position(const string& aTitle, double aSalary)
        : title(aTitle), salary(aSalary) {}
    const string& getTitle() const { return title; }
    double getSalary() const { return salary; }
    void changeSalaryTo(double d) { salary = d; }
private:
    string title;
    double salary;
};

// Directory class
class Directory {
    // Overload Directory's output operator
    friend ostream& operator<<(ostream& os, const Directory& dir) {
        for (size_t i = 0; i < dir.size; ++i) {
            os << *(dir.entries[i]) << endl;
        }
        return os;
    }
    // Nested Entry class
    class Entry {
        friend ostream& operator<<(ostream& os, const Entry& rhs) {
            os << rhs.name << ' ' << rhs.room
               << ' ' << rhs.phone << ", " << *rhs.pos;
            return os;
        }
    public:
        Entry(const string& name, unsigned room, unsigned phone, Position& position)
            : name(name), room(room), phone(phone), pos(&position) {}
        const string& getName() const { return name; }
        unsigned getPhone() const { return phone; }
    private:
        string name;
        unsigned room;
        unsigned phone;
        Position* pos;
    };


public:
    // Constructor
    Directory(const string& companyName)
        : size(0), capacity(2), company(companyName) {
        entries = new Entry*[capacity];
    }

    // Destructor
    ~Directory() {
        cout << "Destructor called" << endl;
        for (size_t i = 0; i < size; ++i) {
            delete entries[i];
        }
        delete[] entries;
    }

    // Copy Constructor
    Directory(const Directory& other)
        : size(other.size), capacity(other.capacity), company(other.company) {
        cout << "Copy constructor called" << endl;
        entries = new Entry*[capacity];
        for (size_t i = 0; i < size; ++i) {
            entries[i] = new Entry(*(other.entries[i]));
        }
    }

    // Assignment Operator
    Directory& operator=(const Directory& other) {
        cout << "Assignment operator called" << endl;
        if (this != &other) {
            for (size_t i = 0; i < size; ++i) {
                delete entries[i];
            }
            delete[] entries;
            size = other.size;
            capacity = other.capacity;
            company = other.company;
            entries = new Entry*[capacity];
            for (size_t i = 0; i < size; ++i) {
                entries[i] = new Entry(*(other.entries[i]));
            }
        }
        return *this;
    }

    // Add method
    void add(const string& name, unsigned room, unsigned ph, Position& pos) {
        if (size == capacity) {
            capacity *= 2;
            Entry** newEntries = new Entry*[capacity];
            for (size_t i = 0; i < size; ++i) {
                newEntries[i] = entries[i];
            }
            delete[] entries;
            entries = newEntries;
        }
        entries[size] = new Entry(name, room, ph, pos);
        ++size;
    }

    // Overload [] operator to look up a person's phone number by name
    unsigned operator[](const string& name) const {
        for (size_t i = 0; i < size; ++i) {
            if (entries[i]->getName() == name) {
                return entries[i]->getPhone();
            }
        }
        return 0;  // Assuming 0 is not a valid phone number.
    }


private:
    Entry** entries;  // Pointer to dynamic array of Entry pointers
    size_t size;
    size_t capacity;
    string company;
};

void doNothing(Directory dir) {
    // You need to overload the Directory output operator before
    // uncommenting the next line.
    cout << dir << endl;
}

int main() {
    Position boss("Boss", 3141.59);
    Position pointyHair("Pointy Hair", 271.83);
    Position techie("Techie", 14142.13);
    Position peon("Peonissimo", 34.79);
    // Creating a Directory
    Directory d("HAL");
    // Add someone
    d.add("Marilyn", 123, 4567, boss);
    // Printing the directory
    cout << d << endl;
    // Using the square bracket operator to access someone's phone extension.
    cout << "d[\"Marilyn\"]: " << d["Marilyn"] << endl;
    cout << "======\n\n";
    // Copy constructor test
    Directory d2 = d;
    d2.add("Gallagher", 111, 2222, techie);
    d2.add("Carmack", 314, 1592, techie);
    cout << "Directory d:\n" << d << endl;
    cout << "Directory d2:\n" << d2 << endl;
    cout << "Calling doNothing\n";
    doNothing(d2);
    cout << "Back from doNothing\n";
    // Should display 1592
    cout << d2["Carmack"] << endl;
    // Assignment operator test
    Directory d3("IBM");
    d3.add("Torvalds", 628, 3185, techie);
    d3.add("Ritchie", 123, 5813, techie);
    d2 = d3;
    cout << d2["Ritchie"] << endl;
    cout << d2 << endl;
}
