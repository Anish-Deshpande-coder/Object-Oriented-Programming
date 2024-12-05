// Doubly linked list
//  Test code

#include <cstdlib>
#include <iostream>
using namespace std;
#include <iostream>
using namespace std;

#include <iostream>
using namespace std;

class List {
private:
    // Nested Node class
    struct Node {
        int data;
        Node* next;
        Node* prev;
    };

    Node* header;  // Sentinel at the beginning
    Node* trailer; // Sentinel at the end
    size_t listSize;

public:
    // Default Constructor
    List() : listSize(0) {
        header = new Node{0, nullptr, nullptr};  // Dummy node
        trailer = new Node{0, nullptr, nullptr}; // Dummy node
        header->next = trailer;
        trailer->prev = header;
    }

    // Task 1: push_back
    void push_back(int data) {
        Node* newNode = new Node{data, trailer, trailer->prev};
        trailer->prev->next = newNode;
        trailer->prev = newNode;
        ++listSize;
    }

    // Task 1: pop_back
    void pop_back() {
        if (listSize == 0) return; // Nothing to pop
        Node* last = trailer->prev;
        last->prev->next = trailer;
        trailer->prev = last->prev;
        delete last;
        --listSize;
    }

    // Task 2: push_front
    void push_front(int data) {
        Node* newNode = new Node{data, header->next, header};
        header->next->prev = newNode;
        header->next = newNode;
        ++listSize;
    }

    // Task 2: pop_front
    void pop_front() {
        if (listSize == 0) return; // Nothing to pop
        Node* first = header->next;
        header->next = first->next;
        first->next->prev = header;
        delete first;
        --listSize;
    }

    // Task 3: clear
    void clear() {
        while (listSize > 0) {
            pop_front();
        }
    }

    // Task 1: front
    int& front() {
        return header->next->data;
    }

    const int& front() const {
        return header->next->data;
    }

    // Task 1: back
    int& back() {
        return trailer->prev->data;
    }

    const int& back() const {
        return trailer->prev->data;
    }

    // Task 1: size
    size_t size() const {
        return listSize;
    }

    // Task 1: Output operator
    friend ostream& operator<<(ostream& os, const List& lst) {
        Node* current = lst.header->next;
        while (current != lst.trailer) {
            os << current->data << " ";
            current = current->next;
        }
        return os;
    }

    // Task 4: Index operator
    int& operator[](size_t index) {
        Node* current = header->next;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    const int& operator[](size_t index) const {
        Node* current = header->next;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    // Task 5: Iterator class
    class iterator {
    private:
        Node* current;
        friend class List;
        friend bool operator==(const iterator& lhs, const iterator& rhs) {
            return lhs.current == rhs.current;
        }

        friend bool operator!=(const iterator& lhs, const iterator& rhs) {
            return lhs.current != rhs.current;
        }

    public:
        iterator(Node* node) : current(node) {}

        iterator& operator++() {
            current = current->next;
            return *this;
        }

        iterator& operator--() {
            current = current->prev;
            return *this;
        }


        int& operator*() {
            return current->data;
        }
    };

    // Begin and End for iterators
    iterator begin() {
        return iterator(header->next);
    }

    iterator end() {
        return iterator(trailer);
    }

    // Task 6: Insert
    iterator insert(iterator pos, int data) {
        Node* current = pos.current;
        Node* prevNode = current->prev;
        Node* newNode = new Node{data, current, prevNode};

        prevNode->next = newNode;
        current->prev = newNode;

        ++listSize;
        return iterator(newNode);
    }

    // Task 7: Erase
    iterator erase(iterator pos) {
        Node* current = pos.current;
        Node* prevNode = current->prev;
        Node* nextNode = current->next;

        prevNode->next = nextNode;
        nextNode->prev = prevNode;

        delete current;
        --listSize;
        return iterator(nextNode);
    }

    // Task 8: Copy constructor
    List(const List& other) {
        listSize = 0;
        header = new Node{0, nullptr, nullptr};  // Dummy node
        trailer = new Node{0, nullptr, nullptr}; // Dummy node
        header->next = trailer;
        trailer->prev = header;
        for (Node* current = other.header->next; current != other.trailer; current = current->next) {
            push_back(current->data);

        }
    }

    // Task 8: Assignment operator
    List& operator=(const List& other) {
        if (this != &other) {
            clear();
            delete header;
            delete trailer;
            header = new Node{0, nullptr, nullptr};  // Dummy node
            trailer = new Node{0, nullptr, nullptr}; // Dummy node
            header->next = trailer;
            trailer->prev = header;
            for (Node* current = other.header->next; current != other.trailer; current = current->next) {
                push_back(current->data);
            }
        }
        return *this;
    }

    // Task 8: Destructor
    ~List() {
        clear(); // Remove all nodes
        delete header; // Delete the sentinel header node
        delete trailer; // Delete the sentinel trailer node
    }
};

// Test helper functions
void printListInfo(const List& myList) {
    cout << "size: " << myList.size()
         << ", front: " << myList.front()
         << ", back(): " << myList.back()
         << ", list: " << myList << endl;
}


// The following should not compile. Check that it does not.
void changeFrontAndBackConst(List& theList) {
    theList.front() = 17;
    theList.back() = 42;
}

void changeFrontAndBack(List& theList) {
    theList.front() = 17;
    theList.back() = 42;
}

// Task 4
void printListSlow(const List& myList) {
    for (size_t i = 0; i < myList.size(); ++i) {
        cout << myList[i] << ' ';
    }
    cout << endl;
}

// Task 8
void doNothing(List aList) {
    cout << "In doNothing\n";
    printListInfo(aList);
    cout << "Leaving doNothing\n";
}

int main() {

    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";

    cout << "Modify the first and last items, and display the results\n";
    changeFrontAndBack(myList);
    printListInfo(myList);
    cout << "===================\n";

    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";

    // Task 2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    printListInfo(myList);
    cout << "===================\n";

    // Task 3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";

    // Task 4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Now calling a function, printListSlow, to do the same thing\n";
    printListSlow(myList);
    cout << "Finally, for this task, using the index operator to modify\n"
         << "the data in the third item in the list\n"
         << "and then using printListSlow to display it again\n";
    myList[2] = 42;
    printListSlow(myList);


    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    // Note you can choose to nest the iterator class or not, your choice.
    //for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
    for (List::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";

    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
         << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";

    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";

    // Task 8
    cout << "\n------Task Eight------\n";
    cout << "Copy control\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Calling doNothing(myList)\n";
    doNothing(myList);
    cout << "Back from doNothing(myList)\n";
    printListInfo(myList);

    cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
    List listTwo;
    for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
    printListInfo(listTwo);
    cout << "listTwo = myList\n";
    listTwo = myList;
    cout << "myList: ";
    printListInfo(myList);
    cout << "listTwo: ";
    printListInfo(listTwo);
    cout << "===================\n";
}
