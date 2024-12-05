#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

struct Node {
    int data = 0;
    Node* next = nullptr;
};

Node* reverse(const Node* hp) {
    Node* newHead = nullptr;
    while (hp) {
        Node* newNode = new Node{hp->data, newHead};
        newHead = newNode;
        hp = hp->next;
    }
    return newHead;
}

void reverseInPlace(Node*& hp) {
    Node* prev = nullptr;
    Node* curr = hp;
    Node* next = nullptr;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    hp = prev;
}

const Node* isSublist(const Node* pattern, const Node* target) {
    if (!pattern) return target;
    while (target) {
        const Node* tarIt = target;
        const Node* patIt = pattern;
        while (tarIt && patIt && tarIt->data == patIt->data) {
            tarIt = tarIt->next;
            patIt = patIt->next;
        }
        if (!patIt) return target;
        target = target->next;
    }
    return nullptr;
}

const Node* sharedListBruteForce(const Node* listA, const Node* listB) {
    for (const Node* a = listA; a; a = a->next) {
        for (const Node* b = listB; b; b = b->next) {
            if (a == b) return a;
        }
    }
    return nullptr;
}

const Node* sharedListUsingSet(const Node* listA, const Node* listB) {
    unordered_set<const Node*> nodes;
    while (listA) {
        nodes.insert(listA);
        listA = listA->next;
    }
    while (listB) {
        if (nodes.find(listB) != nodes.end()) return listB;
        listB = listB->next;
    }
    return nullptr;
}

void listAddHead(Node*& headPtr, int entry) {
    headPtr = new Node{entry, headPtr};
}

void listPrint(const Node* headPtr) {
    while (headPtr) {
        cout << headPtr->data << ' ';
        headPtr = headPtr->next;
    }
    cout << endl;
}

void listClear(Node*& headPtr) {
    while (headPtr) {
        Node* next = headPtr->next;
        delete headPtr;
        headPtr = next;
    }
}

Node* listBuild(const vector<int>& vals) {
    Node* result = nullptr;
    for (size_t index = vals.size(); index > 0; --index) {
        listAddHead(result, vals[index-1]);
    }
    return result;
}

void match(const Node* target, const Node* pattern) {
    cout << "Attempt pattern: ";
    listPrint(pattern);
    const Node* result = isSublist(pattern, target);
    if (result)
        listPrint(result);
    else
        cout << "Failed to match\n";
    cout << endl;
}

int main() {
    cout << "Part one: \n\n";

    Node* original = listBuild({6, 3, 2, 5});
    cout << "original: ";
    listPrint(original);
    Node* reversed = reverse(original);
    cout << "Calling reverse:\n";
    cout << "original: ";
    listPrint(original);
    cout << "Reversed: ";
    listPrint(reversed);

    cout << "Calling reverseInPlace on the original:\n";
    cout << "original before: ";
    listPrint(original);
    reverseInPlace(original);
    cout << "original after: ";
    listPrint(original);

    cout << "=====================\n\n"
         << "Part two: \n\n";

    Node* target = listBuild({1, 2, 3, 2, 3, 2, 4, 5, 6});
    cout << "Target: ";
    listPrint(target);
    cout << endl;

    Node* m1 = listBuild({1});
    match(target, m1);
    listClear(m1);

    Node* m2 = listBuild({3, 9});
    match(target, m2);
    listClear(m2);

    Node* m3 = listBuild({2, 3});
    match(target, m3);
    listClear(m3);

    Node* m4 = listBuild({2, 4, 5, 6});
    match(target, m4);
    listClear(m4);

    Node* m5 = listBuild({2, 3, 2, 4});
    match(target, m5);
    listClear(m5);

    Node* m6 = listBuild({5, 6, 7});
    match(target, m6);
    listClear(m6);

    m1 = listBuild({6});
    match(target, m1);
    listClear(m1);

    m1 = nullptr;
    match(target, m1);

    cout << "Task Three\n";
    cout << "Target: ";
    listPrint(target);

    cout << "Matching target against self:\n";
    cout << "Brute force: ";
    listPrint(sharedListBruteForce(target, target));
    cout << "Using Set:   ";
    listPrint(sharedListUsingSet(target, target));

    Node* dupOfTarget = listBuild({1, 2, 3, 2, 3, 2, 4, 5, 6});
    cout << "Matching target against dup of self:\n";
    cout << "Brute force: ";
    listPrint(sharedListBruteForce(target, dupOfTarget));
    cout << "Using Set:   ";
    listPrint(sharedListUsingSet(target, dupOfTarget));
    listClear(dupOfTarget);

    cout << "Matching target against part of self from fourth node:\n";
    cout << "Brute force: ";
    listPrint(sharedListBruteForce(target, target->next->next->next));
    cout << "Using Set:   ";
    listPrint(sharedListUsingSet(target, target->next->next->next));

    Node* another = target->next->next->next->next;
    listAddHead(another, 7);
    listAddHead(another, 6);
    listAddHead(another, 5);
    cout << "other list:\n";
    listPrint(another);

    cout << "Brute force: ";
    const Node* startOfShared = sharedListBruteForce(target, another);
    listPrint(startOfShared);

    cout << "Using Set:   ";
    startOfShared = sharedListUsingSet(target, another);
    listPrint(startOfShared);

    listClear(target);
    for (Node* p = another; p != startOfShared; ) {
        Node* pNext = p->next;
        delete p;
        p = pNext;
    }
    return 0;
}
