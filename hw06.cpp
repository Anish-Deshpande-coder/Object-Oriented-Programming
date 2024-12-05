#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class BigUnsigned {
    vector<int> digits;

public:
    // Default constructor
    BigUnsigned(int num = 0) {
        do {
            digits.push_back(num % 10);
            num /= 10;
        } while (num > 0);
    }

    // Constructor from string
    BigUnsigned(const string& str) {
        bool found_digit = false;
        for (char ch : str) {
            if (isdigit(ch)) {
                digits.push_back(ch - '0');
                found_digit = true;
            } else if (found_digit) {
                break;  // Stop at first non-digit after finding digits
            }
        }
        if (digits.empty()) {
            digits.push_back(0); // If no valid digits found, treat as if it was 0
        } else {
            // Remove leading zeros by reversing, trimming, and reversing again
            reverse(digits.begin(), digits.end());
            while (digits.size() > 1 && digits.back() == 0) {
                digits.pop_back();
            }
            reverse(digits.begin(), digits.end());
        }
    }

    // Output stream operator <<
    friend ostream& operator<<(ostream& os, const BigUnsigned& num) {
        for (auto it = num.digits.rbegin(); it != num.digits.rend(); ++it) {
            os << *it;
        }
        return os;
    }

    // Operator +
    BigUnsigned operator+(const BigUnsigned& other) const {
        BigUnsigned result;
        result.digits.clear();
        int carry = 0, sum;
        size_t maxSize = max(digits.size(), other.digits.size());
        for (size_t i = 0; i < maxSize || carry; ++i) {
            int digit1 = (i < digits.size()) ? digits[i] : 0;
            int digit2 = (i < other.digits.size()) ? other.digits[i] : 0;
            sum = digit1 + digit2 + carry;
            carry = sum / 10;
            result.digits.push_back(sum % 10);
        }
        return result;
    }

    // Operator +=
    BigUnsigned& operator+=(const BigUnsigned& other) {
        *this = *this + other;
        return *this;
    }

    // Pre-increment operator ++
    BigUnsigned& operator++() {
        *this += 1;
        return *this;
    }

    // Post-increment operator ++
    BigUnsigned operator++(int) {
        BigUnsigned temp = *this;
        ++(*this);
        return temp;
    }

    // Comparison operators
    bool operator==(const BigUnsigned& other) const {
        return digits == other.digits;
    }

    bool operator<(const BigUnsigned& other) const {
        if (digits.size() != other.digits.size())
            return digits.size() < other.digits.size();
        for (int i = digits.size() - 1; i >= 0; --i) {
            if (digits[i] != other.digits[i])
                return digits[i] < other.digits[i];
        }
        return false;
    }

    bool operator>(const BigUnsigned& other) const {
        return other < *this;
    }

    bool operator<=(const BigUnsigned& other) const {
        return !(other < *this);
    }

    bool operator>=(const BigUnsigned& other) const {
        return !(*this < other);
    }

    bool operator!=(const BigUnsigned& other) const {
        return !(*this == other);
    }

    // Operator to compare with int (for direct comparison)
    bool operator==(int num) const {
        return *this == BigUnsigned(num);
    }

    operator bool() const {
        return !(digits.size() == 1 && digits[0] == 0);
    }
};

// Main code
int main() {
    BigUnsigned zero;
    BigUnsigned one(1);

    cout << "zero: " << zero << endl;
    cout << "one: " << one << endl;

    BigUnsigned val = 1;
    cout << "val: " << val << endl;
    cout << "++val: " << ++val << endl;
    cout << "val: " << val << endl;
    cout << "val++: " << val++ << endl;
    cout << "val: " << val << endl;

    cout << "(one + zero): " << (one + zero) << endl;
    cout << "(one + one): " << (one + one) << endl;

    cout << boolalpha;
    cout << "one < one: " << (one < one) << endl;
    cout << "zero < one: " << (zero < one) << endl;

    BigUnsigned a = 123;
    BigUnsigned b = 1234;
    BigUnsigned c = 124;
    BigUnsigned d = 12345;

    cout << "a: " << a << ", b: " << b
         << ", c: " << c << ", d: " << d << endl;
    cout << "a + d: " << (a + d) << endl;
    cout << "d + d: " << (d + d) << endl;
    cout << "a < d: " << (a < d) << endl;
    cout << "d < a: " << (d < a) << endl;
    cout << "zero == zero: " << (zero == zero) << endl
         << "zero == one: " << (zero == one) << endl
         << "a == a: " << (a == a) << endl
         << "a == d: " << (a == d) << endl
         << "d == a: " << (d == a) << endl;

    cout << "(zero == 0): " << (zero == 0) << endl
         << "(one == 0): " << (one == 0) << endl
         << "(1 == one): " << (1 == one) << endl;

    // +=
    cout << "b: " << b << ", c: " << c << endl;
    cout << "(c += b): " << (c += b) << endl;
    cout << "b: " << b << ", c: " << c << endl;

    BigUnsigned x = a;
    cout << "x: " << x << ", a: " << a << endl
         << "x == a: " << (x == a) << endl
         << "a == x: " << (a == x) << endl
         << "a < x: " << (a < x) << endl
         << "a > x: " << (a > x) << endl;

    cout << "x > a: " << (x > a) << endl
         << "x >= a: " << (x >= a) << endl
         << "x <= a: " << (x <= a) << endl
         << "x != a: " << (x != a) << endl;

    BigUnsigned big("987654321");
    BigUnsigned big2("  ");
    BigUnsigned big3("felix");
    BigUnsigned big4("00987654321");

    cout << "big: " << big << endl
         << "big2: " << big2 << endl
         << "big3: " << big3 << endl
         << "big4: " << big4 << endl;

    BigUnsigned big5(98765);
    BigUnsigned big6(2457);
    cout << "big5: " << big5  << ", big6: " <<  big6 << endl
         << "(big5 + big6): " << (big5 + big6) << endl
         << "(big6 + big5): " << (big6 + big5) << endl;

    // How does this work?
    cout << zero << " is " << (zero ? "true" : "false") << endl;
    cout << one << " is " << (one ? "true" : "false") << endl;
    cout << big4 << " is " << (big4 ? "true" : "false") << endl;
}
