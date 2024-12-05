/*
  rec01_start.cpp
  fall 2024
*/
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
//
// main
//
int main() { // Yes, it has to have an int for the return type
    //
    // Output
    //

    // Task 1. Printing hello ...  No use of "using namespace"
    cout << "hello ...";

    // Task 2  Printing hello ...  Using "using namespace"
    using namespace std;
    cout << "hello ..." << endl;


    //
    // Types and variables
    //

    // Task 3  Displaying uninitialized variable
    int x;
    cout << "The value of x is: " << x << endl;
    
    // Task 4 Use the sizeof function to see the size in bytes of
    //        different types on your machine.
    int y = 17;
    int z = 2000000017;
    int doublePie = 3.14159;
    cout << sizeof(y) << sizeof(z) << sizeof(doublePie) << endl;
    
    // Task 5  Attempt to assign the wrong type of thing to a variable
    //string x = "felix";
    // compilation error when ran




    //
    // Conditions
    //

    // Task 6  Testing for a range
    if (y < 20 && y > 10) {
        cout << "y = is between 10 and 20" << endl;
    }
    

    //
    // Loops and files
    //

    // Task 7  Looping, printing values 10 to 20 inclusive

    // First with a for loop
    for (int i = 10; i <= 20; i++) {
        std::cout << i << " ";
    }

    // Then with a while loop
    int i = 10;
    while (i <= 20) {
        std::cout << i << " ";
        i++;
    }

    // Finally with a do-while loop
    do {
        std::cout << i << " ";
        i++;
    } while (i <= 20);
    std::cout << std::endl;


    // Task 8  Looping to successfully open a file, asking user for the name
    string filename;
    ifstream ifs;
    while (true) {
        std::cout << "Please enter the file name: ";
        std::cin >> filename;
        ifs.open(filename);
        if (ifs.is_open()) {
            std::cout << "File opened successfully!" << std::endl;
            break;
        } else {
            std::cerr << "Error opening file. Please try again." << std::endl;
        }
    }

    // Task 9  Looping, reading file word by "word".
    ifs.open("text.txt");
    string word;
    while (ifs >> word) {
        std::cout << word << std::endl;
    }
    ifs.close();

    // Task 10 Open a file of integers, read it in, and display the sum.
    int number;
    int sum = 0;
    ifs.open("integers.txt");
    while (ifs >> number) {
        sum += number;
    }
    ifs.close();

    // Taks 11 Open and read a file of integers and words. Display the sum.
    ifs.open("integers.txt");
    while (ifs >> number) {
        sum += number;
    }
    std::cout << "sum is: " << word << std::endl;
    ifs.close();

    //
    // Vectors
    //

    // Task 12 Filling a vector of ints
    vector <int> evenNumbers;
    for (int i = 0; i <= 100; i+=2) {
        evenNumbers.push_back(i);
    }
    
    // Task 13 Displaying the vector THREE times
    //         a) using the indices,
    for (size_t i = 0; i < evenNumbers.size(); ++i) {
        std::cout << evenNumbers[i] << " ";
    }

    //         b) using a "ranged for"
    for (int num : evenNumbers) {
        std::cout << num << " ";
    }

    //         c) using indices again but backwards
    for (size_t i = evenNumbers.size(); i > 0; --i) {
        std::cout << evenNumbers[i - 1] << " ";
    }

    // Task 14. Initialize a vector with the primes less than 20. 
    vector <int> primes = {2, 3, 5, 7, 11, 13, 17, 19};
    std::cout << "Prime numbers less than 20:" << std::endl;
    for (int prime : primes) {
        std::cout << prime << " ";
    }
    std::cout << std::endl;
    
} // main

