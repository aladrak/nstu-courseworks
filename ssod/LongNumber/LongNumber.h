using namespace std;
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

class LongNumber {
private:
    string digits;

    // удаляет ведущие нули
    static string normalizeString(string s) {
        if (s.empty()) return "0";
        size_t start = 0;
        while (start < s.size() - 1 && s[start] == '0')
            ++start;
        return s.substr(start);
    }

    // Сравнение строк как чисел
    static bool lessThan(const string& a, const string& b) {
        if (a.length() != b.length()) return a.length() < b.length();
        return a < b;
    }

    // Сложение строк
    static string addStrings(const string& a, const string& b) {
        string ra(a.rbegin(), a.rend());
        string rb(b.rbegin(), b.rend());
        string res;
        int carry = 0;
        size_t n = max(ra.size(), rb.size());
        for (size_t i = 0; i < n || carry; ++i) {
            int sum = carry;
            if (i < ra.size()) sum += ra[i] - '0';
            if (i < rb.size()) sum += rb[i] - '0';
            res.push_back('0' + (sum % 10));
            carry = sum / 10;
        }
        reverse(res.begin(), res.end());
        return res;
    }

    // Вычитание строк (требуется a >= b)
    static string subtractStrings(const string& a, const string& b) {
        if (lessThan(a, b))
            throw runtime_error("Result of subtraction would be negative");
        string ra(a.rbegin(), a.rend());
        string rb(b.rbegin(), b.rend());
        string res;
        int borrow = 0;
        for (size_t i = 0; i < ra.size(); ++i) {
            int digit = (ra[i] - '0') - borrow;
            if (i < rb.size()) digit -= (rb[i] - '0');
            if (digit < 0) {
                digit += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            res.push_back('0' + digit);
        }
        reverse(res.begin(), res.end());
        return normalizeString(res);
    }

    // Умножение строк
    static string multiplyStrings(const string& a, const string& b) {
        if (a == "0" || b == "0") return "0";
        size_t na = a.size(), nb = b.size();
        vector<int> prod(na + nb, 0);
        for (size_t i = 0; i < na; ++i)
            for (size_t j = 0; j < nb; ++j)
                prod[i + j + 1] += (a[i] - '0') * (b[j] - '0');
        for (int i = static_cast<int>(prod.size()) - 1; i > 0; --i) {
            prod[i - 1] += prod[i] / 10;
            prod[i] %= 10;
        }
        string res;
        size_t start = (prod[0] == 0) ? 1 : 0;
        for (size_t i = start; i < prod.size(); ++i)
            res.push_back('0' + prod[i]);
        return res;
    }

    // Целочисленное деление строк (a / b)
    static string divideStrings(const string& a, const string& b) {
        if (b == "0")
            throw runtime_error("Division by zero");
        if (lessThan(a, b))
            return "0";
        string quotient, current;
        for (char c : a) {
            current += c;
            current = normalizeString(current);
            if (lessThan(current, b)) {
                quotient += '0';
                continue;
            }
            int cnt = 0;
            while (!lessThan(current, b)) {
                current = subtractStrings(current, b);
                ++cnt;
            }
            quotient += ('0' + cnt);
        }
        return normalizeString(quotient);
    }

    // Преобразование ull -> string
    static string fromULL(unsigned long long n) {
        if (n == 0) return "0";
        string s;
        while (n) {
            s = char('0' + (n % 10)) + s;
            n /= 10;
        }
        return s;
    }

public:
    // Конструкторы
    LongNumber() : digits("0") {}

    explicit LongNumber(const string& s) {
        if (s.empty())
            throw invalid_argument("Empty string is not a valid number");
        for (char c : s)
            if (!isdigit(static_cast<unsigned char>(c)))
                throw invalid_argument("String contains non-digit character");
        digits = normalizeString(s);
    }
    explicit LongNumber(unsigned long long n) : digits(fromULL(n)) {}
    LongNumber(const LongNumber& other) : digits(other.digits) {}

    // Деструктор
    ~LongNumber() = default;

    // Операторы присваивания
    LongNumber& operator=(const LongNumber& other) {
        if (this != &other) digits = other.digits;
        return *this;
    }

    LongNumber& operator=(const string& s) {
        *this = LongNumber(s);
        return *this;
    }

    LongNumber& operator=(unsigned long long n) {
        *this = LongNumber(n);
        return *this;
    }

    // Арифметические операторы (члены класса)
    LongNumber operator+(const LongNumber& rhs) const { return LongNumber(addStrings(digits, rhs.digits)); }
    LongNumber operator-(const LongNumber& rhs) const { return LongNumber(subtractStrings(digits, rhs.digits)); }
    LongNumber operator*(const LongNumber& rhs) const { return LongNumber(multiplyStrings(digits, rhs.digits)); }
    LongNumber operator/(const LongNumber& rhs) const { return LongNumber(divideStrings(digits, rhs.digits)); }

    // Составные операторы
    LongNumber& operator+=(const LongNumber& rhs) { digits = addStrings(digits, rhs.digits); return *this; }
    LongNumber& operator-=(const LongNumber& rhs) { digits = subtractStrings(digits, rhs.digits); return *this; }

    // Инкремент и декремент
    LongNumber& operator++() { *this = *this + LongNumber(1ULL); return *this; }
    LongNumber operator++(int) { LongNumber tmp(*this); ++(*this); return tmp; }
    LongNumber& operator--() {
        if (digits == "0")
            throw runtime_error("Cannot decrement zero");
        *this = *this - LongNumber(1ULL);
        return *this;
    }
    LongNumber operator--(int) { LongNumber tmp(*this); --(*this); return tmp; }

    // Операторы сравнения
    bool operator<(const LongNumber& rhs) const { return lessThan(digits, rhs.digits); }
    bool operator>(const LongNumber& rhs) const { return rhs < *this; }
    bool operator<=(const LongNumber& rhs) const { return !(rhs < *this); }
    bool operator>=(const LongNumber& rhs) const { return !(*this < rhs); }
    bool operator==(const LongNumber& rhs) const { return digits == rhs.digits; }
    bool operator!=(const LongNumber& rhs) const { return !(*this == rhs); }

    // Доступ по индексу (только чтение)
    char operator[](size_t idx) const {
        if (idx >= digits.size())
            throw out_of_range("LongNumber index out of range");
        return digits[idx];
    }

    // Приведение типов
    explicit operator unsigned long long() const {
        if (digits.size() > 20)
            throw overflow_error("Number too large for unsigned long long");
        unsigned long long res = 0;
        for (char c : digits) {
            if (res > numeric_limits<unsigned long long>::max() / 10)
                throw overflow_error("Overflow during conversion to unsigned long long");
            res = res * 10 + (c - '0');
        }
        return res;
    }

    explicit operator string() const {
        return digits;
    }

    // Вывод
    void print() const {
        cout << digits;
    }

    // Оператор вывода в поток
    friend ostream& operator<<(ostream& os, const LongNumber& ln) {
        os << ln.digits;
        return os;
    }

    // Арифметические friend-функции: LongNumber и unsigned long long
    friend LongNumber operator+(unsigned long long lhs, const LongNumber& rhs) {
        return LongNumber(lhs) + rhs;
    }
    friend LongNumber operator-(unsigned long long lhs, const LongNumber& rhs) {
        return LongNumber(lhs) - rhs;
    }
    friend LongNumber operator*(unsigned long long lhs, const LongNumber& rhs) {
        return LongNumber(lhs) * rhs;
    }
    friend LongNumber operator/(unsigned long long lhs, const LongNumber& rhs) {
        return LongNumber(lhs) / rhs;
    }

    friend LongNumber operator+(const LongNumber& lhs, unsigned long long rhs) {
        return lhs + LongNumber(rhs);
    }
    friend LongNumber operator-(const LongNumber& lhs, unsigned long long rhs) {
        return lhs - LongNumber(rhs);
    }
    friend LongNumber operator*(const LongNumber& lhs, unsigned long long rhs) {
        return lhs * LongNumber(rhs);
    }
    friend LongNumber operator/(const LongNumber& lhs, unsigned long long rhs) {
        return lhs / LongNumber(rhs);
    }

    // Дружественные операторы сравнения с unsigned long long
    friend bool operator<(unsigned long long lhs, const LongNumber& rhs) { return LongNumber(lhs) < rhs; }
    friend bool operator>(unsigned long long lhs, const LongNumber& rhs) { return LongNumber(lhs) > rhs; }
    friend bool operator<=(unsigned long long lhs, const LongNumber& rhs) { return LongNumber(lhs) <= rhs;}
    friend bool operator>=(unsigned long long lhs, const LongNumber& rhs) { return LongNumber(lhs) >= rhs; }
    friend bool operator==(unsigned long long lhs, const LongNumber& rhs) { return LongNumber(lhs) == rhs; }
    friend bool operator!=(unsigned long long lhs, const LongNumber& rhs) { return LongNumber(lhs) != rhs; }

    friend bool operator<(const LongNumber& lhs, unsigned long long rhs) { return lhs < LongNumber(rhs); }
    friend bool operator>(const LongNumber& lhs, unsigned long long rhs) { return lhs > LongNumber(rhs); }
    friend bool operator<=(const LongNumber& lhs, unsigned long long rhs) { return lhs <= LongNumber(rhs); }
    friend bool operator>=(const LongNumber& lhs, unsigned long long rhs) { return lhs >= LongNumber(rhs); }
    friend bool operator==(const LongNumber& lhs, unsigned long long rhs) { return lhs == LongNumber(rhs); }
    friend bool operator!=(const LongNumber& lhs, unsigned long long rhs) { return lhs != LongNumber(rhs); }
};