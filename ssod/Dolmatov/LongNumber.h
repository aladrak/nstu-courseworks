using namespace std;
#include <iostream>

class LongNumber {
private:
    string digits;

    static string normalizeString(string s);
    static string addStrings(const string& a, const string& b);
    static string subtractStrings(const string& a, const string& b);
    static string multiplyStrings(const string& a, const string& b);
    static string divideStrings(const string& a, const string& b);
    static bool lessThan(const string& a, const string& b);
    static bool equals(const string& a, const string& b);

public:
    // Конструкторы
    LongNumber();
    explicit LongNumber(const string& s);
    explicit LongNumber(unsigned long long n);
    LongNumber(const LongNumber& other);

    // Деструктор
    ~LongNumber() = default;

    // Операторы присваивания
    LongNumber& operator=(const LongNumber& other);
    LongNumber& operator=(const string& s);
    LongNumber& operator=(unsigned long long n);

    // Арифметические операторы
    LongNumber operator+(const LongNumber& other) const;
    LongNumber operator-(const LongNumber& other) const;
    LongNumber operator*(const LongNumber& other) const;
    LongNumber operator/(const LongNumber& other) const;

    // Арифметика с накоплением
    LongNumber& operator+=(const LongNumber& other);
    LongNumber& operator-=(const LongNumber& other);

    // Унарные операторы
    LongNumber& operator++();
    LongNumber operator++(int);
    LongNumber& operator--();
    LongNumber operator--(int);

    // Сравнения
    bool operator<(const LongNumber& other) const;
    bool operator>(const LongNumber& other) const;
    bool operator==(const LongNumber& other) const;
    bool operator!=(const LongNumber& other) const;
    bool operator<=(const LongNumber& other) const;
    bool operator>=(const LongNumber& other) const;

    // Доступ к цифре по индексу (0 — старший разряд)
    char operator[](size_t index) const;

    // Преобразование к базовым типам
    explicit operator unsigned long long() const;
    explicit operator string() const;

    // Вывод
    void print() const;
    friend ostream& operator<<(ostream& os, const LongNumber& ln);
};

LongNumber operator+(unsigned long long lhs, const LongNumber& rhs);
LongNumber operator-(unsigned long long lhs, const LongNumber& rhs);
LongNumber operator*(unsigned long long lhs, const LongNumber& rhs);
LongNumber operator/(unsigned long long lhs, const LongNumber& rhs);

LongNumber operator+(const LongNumber& lhs, unsigned long long rhs);
LongNumber operator-(const LongNumber& lhs, unsigned long long rhs);
LongNumber operator*(const LongNumber& lhs, unsigned long long rhs);
LongNumber operator/(const LongNumber& lhs, unsigned long long rhs);