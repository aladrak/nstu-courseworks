#include "LongNumber.h"
#include <algorithm>
#include <string>
#include <vector>

string reverseStr(const string& s) {
    return string(s.rbegin(), s.rend());
}

// == ПРИВАТНЫЕ МЕТОДЫ ==

string LongNumber::normalizeString(string s) {
    if (s.empty()) return "0";
    size_t start = 0;
    while (start < s.size() - 1 && s[start] == '0')
        ++start;
    return s.substr(start);
}

string LongNumber::addStrings(const string& a, const string& b) {
    string ra = reverseStr(a), rb = reverseStr(b);
    string res;
    int carry = 0;
    size_t n = max(ra.size(), rb.size());
    for (size_t i = 0; i < n || carry; ++i) {
        int d = carry;
        if (i < ra.size()) d += ra[i] - '0';
        if (i < rb.size()) d += rb[i] - '0';
        res.push_back('0' + (d % 10));
        carry = d / 10;
    }
    return reverseStr(res);
}

string LongNumber::subtractStrings(const string& a, const string& b) {
    if (!lessThan(a, b)) {
        string ra = reverseStr(a), rb = reverseStr(b);
        string res;
        int borrow = 0;
        for (size_t i = 0; i < ra.size(); ++i) {
            int d = (ra[i] - '0') - borrow;
            if (i < rb.size()) d -= (rb[i] - '0');
            if (d < 0) {
                d += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            res.push_back('0' + d);
        }
        reverse(res.begin(), res.end());

        size_t start = 0;
        while (start < res.size() - 1 && res[start] == '0')
            ++start;
        return res.substr(start);
    } else {
        throw runtime_error("Subtraction would result in negative number");
    }
}

string LongNumber::multiplyStrings(const string& a, const string& b) {
    if (a == "0" || b == "0") return "0";
    size_t na = a.size(), nb = b.size();
    vector<int> res(na + nb, 0);
    for (size_t i = 0; i < na; ++i) {
        for (size_t j = 0; j < nb; ++j) {
            res[i + j + 1] += (a[i] - '0') * (b[j] - '0');
        }
    }
    for (int i = static_cast<int>(res.size()) - 1; i > 0; --i) {
        res[i - 1] += res[i] / 10;
        res[i] %= 10;
    }
    string s;
    size_t start = (res[0] == 0) ? 1 : 0;
    for (size_t i = start; i < res.size(); ++i)
        s.push_back('0' + res[i]);
    return s;
}

string LongNumber::divideStrings(const string& a, const string& b) {
    if (b == "0") throw runtime_error("Division by zero");
    if (lessThan(a, b)) return "0";
    string quotient, current;
    for (char c : a) {
        current += c;
        current = normalizeString(current);
        size_t cnt = 0;
        while (!lessThan(current, b) && current != "0") {
            current = subtractStrings(current, b);
            ++cnt;
        }
        quotient += ('0' + cnt);
    }

    size_t start = 0;
    while (start < quotient.size() - 1 && quotient[start] == '0')
        ++start;
    return quotient.substr(start);
}

bool LongNumber::lessThan(const string& a, const string& b) {
    if (a.size() != b.size()) return a.size() < b.size();
    return a < b;
}

bool LongNumber::equals(const string& a, const string& b) {
    return a == b;
}

// == ПУБЛИЧНЫЕ МЕТОДЫ ==

LongNumber::LongNumber() : digits("0") {}

LongNumber::LongNumber(const string& s) {
    if (s.empty()) throw invalid_argument("Empty string");
    for (char c : s)
        if (!isdigit(static_cast<unsigned char>(c)))
            throw invalid_argument("Invalid digit in string");
    digits = s;
    digits = normalizeString(s);
}

LongNumber::LongNumber(unsigned long long n) {
    if (n == 0) {
        digits = "0";
        return;
    }
    while (n) {
        digits = char('0' + (n % 10)) + digits;
        n /= 10;
    }
}

LongNumber::LongNumber(const LongNumber& other) : digits(other.digits) {}

LongNumber& LongNumber::operator=(const LongNumber& other) {
    if (this != &other) digits = other.digits;
    return *this;
}

LongNumber& LongNumber::operator=(const string& s) { return *this = LongNumber(s); }

LongNumber& LongNumber::operator=(unsigned long long n) { return *this = LongNumber(n); }

LongNumber LongNumber::operator+(const LongNumber& other) const {
    return LongNumber(addStrings(digits, other.digits));
}

LongNumber LongNumber::operator-(const LongNumber& other) const {
    return LongNumber(subtractStrings(digits, other.digits));
}

LongNumber LongNumber::operator*(const LongNumber& other) const {
    return LongNumber(multiplyStrings(digits, other.digits));
}

LongNumber LongNumber::operator/(const LongNumber& other) const { return LongNumber(divideStrings(digits, other.digits)); }


LongNumber& LongNumber::operator+=(const LongNumber& other) {
    digits = addStrings(digits, other.digits);
    return *this;
}

LongNumber& LongNumber::operator-=(const LongNumber& other) {
    digits = subtractStrings(digits, other.digits);
    return *this;
}

LongNumber& LongNumber::operator++() {
    *this = *this + LongNumber(1ULL);
    return *this;
}

LongNumber LongNumber::operator++(int) {
    LongNumber tmp(*this);
    ++(*this);
    return tmp;
}

LongNumber& LongNumber::operator--() {
    if (digits == "0")
        throw runtime_error("Cannot decrement zero");
    return *this = *this - LongNumber(1ULL);
}

LongNumber LongNumber::operator--(int) {
    LongNumber tmp(*this);
    --(*this);
    return tmp;
}

bool LongNumber::operator<(const LongNumber& other) const { return lessThan(digits, other.digits); }

bool LongNumber::operator>(const LongNumber& other) const { return other < *this; }

bool LongNumber::operator==(const LongNumber& other) const { return equals(digits, other.digits); }

bool LongNumber::operator!=(const LongNumber& other) const { return !(*this == other); }

bool LongNumber::operator<=(const LongNumber& other) const { return !(*this > other); }

bool LongNumber::operator>=(const LongNumber& other) const { return !(*this < other); }

char LongNumber::operator[](size_t index) const {
    if (index >= digits.size())
        throw out_of_range("Index out of range");
    return digits[index];
}

LongNumber::operator unsigned long long() const {
    if (digits.size() > 20)
        throw overflow_error("Value too large for unsigned long long");
    unsigned long long res = 0;
    for (char c : digits) {
        if (res > ULLONG_MAX / 10)
            throw overflow_error("Value too large for unsigned long long");
        res = res * 10 + (c - '0');
    }
    return res;
}

LongNumber::operator string() const {
    return digits;
}

void LongNumber::print() const {
    cout << digits;
}

ostream& operator<<(ostream& os, const LongNumber& ln) {
    os << ln.digits;
    return os;
}

// ОПЕРАТОРЫ

LongNumber operator+(unsigned long long lhs, const LongNumber& rhs) {
    return LongNumber(lhs) + rhs;
}

LongNumber operator-(unsigned long long lhs, const LongNumber& rhs) {
    return LongNumber(lhs) - rhs;
}

LongNumber operator*(unsigned long long lhs, const LongNumber& rhs) {
    return LongNumber(lhs) * rhs;
}

LongNumber operator/(unsigned long long lhs, const LongNumber& rhs) {
    return LongNumber(lhs) / rhs;
}

LongNumber operator+(const LongNumber& lhs, unsigned long long rhs) {
    return lhs + LongNumber(rhs);
}

LongNumber operator-(const LongNumber& lhs, unsigned long long rhs) {
    return lhs - LongNumber(rhs);
}

LongNumber operator*(const LongNumber& lhs, unsigned long long rhs) {
    return lhs * LongNumber(rhs);
}

LongNumber operator/(const LongNumber& lhs, unsigned long long rhs) {
    return lhs / LongNumber(rhs);
}