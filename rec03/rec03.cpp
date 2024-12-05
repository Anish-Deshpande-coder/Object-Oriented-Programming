#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

// Task 1
// Define an Account struct
struct Account {
    string name;
    int accountNumber;
};

// Task 2
// Define an Account class (use a different name than in Task 1)
class Account2 {
    friend ostream& operator<<(ostream& os, const Account2& account);
public:
    Account2(const string& name, int accountNumber)
        : name(name), accountNumber(accountNumber) {}
    const string& getName() const { return name; }
    int getAccountNumber() const { return accountNumber; }

private:
    string name;
    int accountNumber;
};
ostream& operator<<(ostream& os, const Account2& account) {
    os << "Name: " << account.name << ", Account Number: " << account.accountNumber;
    return os;
}

// Task 3
// Define another Account class (use a different name than in Task
// 1&2) and a Transaction class. The Transaction class is to be
// defined outside of the Account class, i.e. it is not "nested"
class Transaction {
    friend ostream& operator<<(ostream& os, const Transaction& trans);
public:
    Transaction(bool isDeposit, double amount) : isDeposit(isDeposit), amount(amount) {}

private:
    bool isDeposit;
    double amount;
};
ostream& operator<<(std::ostream& os, const Transaction& trans) {
    os << (trans.isDeposit ? "Deposit" : "Withdrawal") << " of " << trans.amount;
    return os;
}

class Account3 {
    friend ostream& operator<<(ostream& os, const Account3& account);
public:
    Account3(const std::string& name, int accountNumber)
        : name(name), accountNumber(accountNumber), balance(0) {}
    int getAccountNumber() const { return accountNumber; }
    void deposit(double amount) {
        transactions.emplace_back(true, amount);
        balance += amount;
    }
    void withdraw(double amount) {
        if (balance >= amount) {
            transactions.emplace_back(false, amount);
            balance -= amount;
        } else {
            cerr << "Error: Insufficient funds" << endl;
        }
    }
private:
    string name;
    int accountNumber;
    double balance;
    vector<Transaction> transactions;
};
ostream& operator<<(ostream& os, const Account3& account) {
    os << "Account: " << account.name << ", Number: " << account.accountNumber << ", Balance: " << account.balance << "\n";
    os << "Transactions:\n";
    for (const Transaction& trans : account.transactions) {
        os << trans << "\n";
    }
    return os;
}

// Task 4
// Define yet another Account class, this time with a nested public
// Transaction class. Again use a different name for the Account class
// than in the previous Tasks. Note that it is NOT necessary to rename
// the Transaction class, since it is nested.
class TaskFour {
public:
    class TransactionTwo {
    private:
        bool isDeposit;
        double amount;
    public:
        TransactionTwo(bool isDeposit, double amount) : isDeposit(isDeposit), amount(amount) {}
        friend ostream& operator<<(std::ostream& os, const TaskFour::TransactionTwo& trans);
    };
private:
    string name;
    int accountNumber;
    double balance;
    vector<TransactionTwo> transactions;
public:
    TaskFour(const std::string& name, int accountNumber)
        : name(name), accountNumber(accountNumber), balance(0) {}
    int getAccountNumber() const { return accountNumber; }

    void deposit(double amount) {
        transactions.emplace_back(true, amount);
        balance += amount;
    }
    void withdraw(double amount) {
        if (balance >= amount) {
            transactions.emplace_back(false, amount);
            balance -= amount;
        } else {
            cerr << "Error: Insufficient funds" << endl;
        }
    }
    friend ostream& operator<<(std::ostream& os, const TaskFour& account);
};
ostream& operator<<(ostream& os, const TaskFour::TransactionTwo& trans) {
    os << (trans.isDeposit ? "Deposit" : "Withdrawal") << " of " << trans.amount;
    return os;
}
ostream& operator<<(ostream& os, const TaskFour& account) {
    os << "Account: " << account.name << ", Number: " << account.accountNumber << ", Balance: " << account.balance << "\n";
    os << "Transactions:\n";
    for (const auto& trans : account.transactions) {
        os << trans << "\n";
    }
    return os;
}

// Task 5
// Same as Task 4, but make the Transaction nested class private.
// Yes, the Account class needs a new name but, again, the Transaction
// class does not.
/* class TaskFive {
private:
    string name;
    int accountNumber;
    double balance;
    class TransactionThree {
    private:
        bool isDeposit;
        double amount;

    public:
        TransactionThree(bool isDeposit, double amount) : isDeposit(isDeposit), amount(amount) {}
        friend ostream& operator<<(std::ostream& os, const TaskFive::TransactionThree& trans);
    };
    vector<TransactionThree> transactions;
public:
    TaskFive(const std::string& name, int accountNumber)
        : name(name), accountNumber(accountNumber), balance(0) {}
    void deposit(double amount) {
        transactions.emplace_back(true, amount);
        balance += amount;
    }
    void withdraw(double amount) {
        if (balance >= amount) {
            transactions.emplace_back(false, amount);
            balance -= amount;
        } else {
            cerr << "Error: Insufficient funds" << std::endl;
        }
    }
    friend ostream& operator<<(std::ostream& os, const TaskFive& account);
};
//ostream& operator<<(std::ostream& os, const TaskFive::TransactionThree& trans) {
 //   os << (trans.isDeposit ? "Deposit" : "Withdrawal") << " of " << trans.amount;
//    return os;

ostream& operator<<(std::ostream& os, const TaskFive& account) {
    os << "Account: " << account.name << ", Number: " << account.accountNumber << ", Balance: " << account.balance << "\n";
    os << "Transactions:\n";
    for (const auto& trans : account.transactions) {
        os << trans << "\n";
    }
    return os;
}
*/

int main() {
    // Task 1: account as struct
    //      1a
    ifstream inFile("accounts.txt");
    vector<Account> accounts;
    string name;
    int accountNumber;
    while (inFile >> name >> accountNumber) {
        Account acc;
        acc.name = name;
        acc.accountNumber = accountNumber;
        accounts.push_back(acc);
    }
    cout << "Task1a:\n Filling vector of struct objects, define a local struct instance\n"
     << "and set fields explicitly:\n";
    for (const Account& acc : accounts) {
        cout << "Name: " << acc.name << ", Account Number: " << acc.accountNumber << std::endl;
    }
    inFile.close();
    accounts.clear();
    inFile.open("accounts.txt");
    while (inFile >> name >> accountNumber) {
        //      1b
        accounts.push_back(Account {name, accountNumber});
    }
    cout << "Task1b:\n Filling vector of struct objects, using {} initialization:\n";
    for (const Account& acc : accounts) {
        cout << "Name: " << acc.name << ", Account Number: " << acc.accountNumber << endl;
    }
    inFile.close();

    //==================================
    // Task 2: account as class
    ifstream fileTwo("accounts.txt");
    if (!fileTwo) {
        std::cerr << "File could not be opened!" << endl;
        return 1;
    }
    cout << "==============\n";
    cout << "\nTask2a:"
         << "\nFilling vector of class objects, using local class object:\n";
    vector<Account2> vectorTwo;
    string nameTwo;
    int numberTwo;
    while (fileTwo >> nameTwo >> numberTwo) {
        Account2 accc(nameTwo, numberTwo);
        //      2a

        // accc.nameTwo = nameTwo;
        vectorTwo.push_back(accc);
    }
    fileTwo.close();
    cout << "\nTask2b:\n";
    cout << "output using output operator with getters\n";
    for (const Account2& accc : vectorTwo) {

        cout << accc << endl;
    }

    cout << "\nTask2c:\n"
     << "output using output operator as friend without getters\n";
    for (const Account2& accc : vectorTwo) {

        cout << accc << endl;
    }
    vectorTwo.clear();

    cout << "\nTask2d:\n"
        << "Filling vector of class objects, using temporary class object:\n";
    fileTwo.open("accounts.txt");
    if (!fileTwo) {
        cerr << "File could not be reopened!" << endl;
        return 1;
    }
    vectorTwo.clear();
    while (fileTwo >> nameTwo >> numberTwo) {
        vectorTwo.emplace_back(nameTwo, numberTwo);
    }
    fileTwo.close();
    for (const Account2& accc : vectorTwo) {

        cout << accc << endl;
    }
    vectorTwo.clear();

    cout << "\nTask2e:\n"
        << "Filling vector of class objects, using emplace_back:\n";
    fileTwo.open("accounts.txt");
    if (!fileTwo) {
        cerr << "File could not be reopened!" << endl;
        return 1;
    }
    while (fileTwo >> nameTwo >> numberTwo) {
        vectorTwo.emplace_back(nameTwo, numberTwo);
    }
    fileTwo.close();
    for (const Account2& accc : vectorTwo) {

        cout << accc << endl;
    }
    //return 0;

    cout << "==============\n"
         << "\nTask 3:\nAccounts and Transaction:\n";
    ifstream fileThree("transactions.txt");
    if (!fileThree) {
        cerr << "File could not be opened!" << endl;
        return 1;
    }
    vector<Account3> vectorThree;
    string command;
    string nameThree;
    int numberThree;
    double amount;

    // Reading from the file and handling commands
    while (fileThree >> command) {
        if (command == "Account") {
            fileThree >> nameThree >> numberThree;
            vectorThree.emplace_back(nameThree, numberThree);
        } else if (command == "Deposit") {
            fileThree >> accountNumber >> amount;
            for (Account3& acccc : vectorThree) {
                if (acccc.getAccountNumber() == numberThree) {
                    acccc.deposit(amount);
                }
            }
        } else if (command == "Withdraw") {
            fileThree >> accountNumber >> amount;
            for (Account3& acccc : vectorThree) {
                if (acccc.getAccountNumber() == numberThree) {
                    acccc.withdraw(amount);
                }
            }
        }
    }
    fileThree.close();
    for (const Account3& acccc : vectorThree) {
        cout << acccc << endl;
    }
    //return 0;

    cout << "==============\n"
         << "\nTask 4:\nTransaction nested in public section of Account:\n";
    ifstream fileFour("transactions.txt");
    if (!fileFour) {
        cerr << "File could not be opened!" << endl;
        return 1;
    }
    vector<TaskFour> vectorFour;
    string commandTwo;
    string nameFour;
    int numberFour;
    double amountTwo;

    while (fileFour >> commandTwo) {
        if (commandTwo == "Account") {
            fileFour >> nameFour >> numberFour;
            vectorFour.emplace_back(nameFour, numberFour);
        } else if (commandTwo == "Deposit") {
            fileFour >> numberFour >> amountTwo;
            for (TaskFour& accccc : vectorFour) {
                if (accccc.getAccountNumber() == numberFour) {
                    accccc.deposit(amountTwo);
                }
            }
        } else if (commandTwo == "Withdraw") {
            fileFour >> numberFour >> amountTwo;
            for (TaskFour& accccc : vectorFour) {
                if (accccc.getAccountNumber() == numberFour) {
                    accccc.withdraw(amountTwo);
                }
            }
        }
    }
    fileFour.close();
    for (const TaskFour& accccc : vectorFour) {
        cout << accccc << endl;
    }
    return 0;
/*
    cout << "==============\n"
     << "\nTask 5:\nTransaction nested in private section of Account:\n";
    // Simulating reading from file (replace with actual file reading)
    vector<TaskFive> vectorFive;
    vectorFive.emplace_back("John", 101);
    vectorFive.emplace_back("Jane", 102);
    for (const TaskFive& acccccc : vectorFive) {
        cout << acccccc << endl;
    }
    return 0;
    */
}
