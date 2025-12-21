using namespace std;
#include "Fraction.h"
#include <cmath>
#include <algorithm>

long long Fraction::gcd(long long a, long long b) {
    a = std::abs(a);
    b = std::abs(b);
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void Fraction::normalize() {
    if (denominator == 0) {
        throw std::invalid_argument("Denominator cannot be zero.");
    }
    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
    long long g = gcd(numerator, denominator);
    if (g != 0) {
        numerator /= g;
        denominator /= g;
    }
}

// Конструкторы
Fraction::Fraction() : numerator(0), denominator(1) {}

Fraction::Fraction(long long num, long long den) : numerator(num), denominator(den) {
    normalize();
}

Fraction::Fraction(const Fraction& other)
    : numerator(other.numerator), denominator(other.denominator) {}

// Операторы присваивания
Fraction& Fraction::operator=(const Fraction& other) {
    if (this != &other) {
        numerator = other.numerator;
        denominator = other.denominator;
    }
    return *this;
}

Fraction& Fraction::operator=(long long value) {
    numerator = value;
    denominator = 1;
    return *this;
}

// Арифметические операторы: дробь-дробь
Fraction operator+(const Fraction& lhs, const Fraction& rhs) {
    return Fraction(
        lhs.numerator * rhs.denominator + rhs.numerator * lhs.denominator,
        lhs.denominator * rhs.denominator
    );
}

Fraction operator-(const Fraction& lhs, const Fraction& rhs) {
    return Fraction(
        lhs.numerator * rhs.denominator - rhs.numerator * lhs.denominator,
        lhs.denominator * rhs.denominator
    );
}

Fraction operator*(const Fraction& lhs, const Fraction& rhs) {
    return Fraction(lhs.numerator * rhs.numerator, lhs.denominator * rhs.denominator);
}

Fraction operator/(const Fraction& lhs, const Fraction& rhs) {
    if (rhs.numerator == 0) {
        throw std::invalid_argument("Division by zero.");
    }
    return Fraction(lhs.numerator * rhs.denominator, lhs.denominator * rhs.numerator);
}

// Арифметика
Fraction operator+(const Fraction& lhs, long long rhs) {
    return lhs + Fraction(rhs);
}
Fraction operator+(long long lhs, const Fraction& rhs) {
    return Fraction(lhs) + rhs;
}

Fraction operator-(const Fraction& lhs, long long rhs) {
    return lhs - Fraction(rhs);
}
Fraction operator-(long long lhs, const Fraction& rhs) {
    return Fraction(lhs) - rhs;
}

Fraction operator*(const Fraction& lhs, long long rhs) {
    return lhs * Fraction(rhs);
}
Fraction operator*(long long lhs, const Fraction& rhs) {
    return Fraction(lhs) * rhs;
}

Fraction operator/(const Fraction& lhs, long long rhs) {
    return lhs / Fraction(rhs);
}
Fraction operator/(long long lhs, const Fraction& rhs) {
    return Fraction(lhs) / rhs;
}

// Арифметика с накоплением
Fraction& Fraction::operator+=(const Fraction& other) {
    *this = *this + other;
    return *this;
}
Fraction& Fraction::operator-=(const Fraction& other) {
    *this = *this - other;
    return *this;
}
Fraction& Fraction::operator*=(const Fraction& other) {
    *this = *this * other;
    return *this;
}
Fraction& Fraction::operator/=(const Fraction& other) {
    *this = *this / other;
    return *this;
}

Fraction& Fraction::operator+=(long long value) {
    *this += Fraction(value);
    return *this;
}
Fraction& Fraction::operator-=(long long value) {
    *this -= Fraction(value);
    return *this;
}
Fraction& Fraction::operator*=(long long value) {
    *this *= Fraction(value);
    return *this;
}
Fraction& Fraction::operator/=(long long value) {
    *this /= Fraction(value);
    return *this;
}

// Унарные операторы ++
Fraction& Fraction::operator++() {
    numerator += denominator;
    return *this;
}
Fraction Fraction::operator++(int) {
    Fraction temp(*this);
    ++(*this);
    return temp;
}

// Унарные операторы --
Fraction& Fraction::operator--() {
    numerator -= denominator;
    return *this;
}
Fraction Fraction::operator--(int) {
    Fraction temp(*this);
    --(*this);
    return temp;
}

// Логические операторы
bool operator==(const Fraction& lhs, const Fraction& rhs) {
    return lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator;
}

bool operator!=(const Fraction& lhs, const Fraction& rhs) {
    return !(lhs == rhs);
}

bool operator<(const Fraction& lhs, const Fraction& rhs) {
    return lhs.numerator * rhs.denominator < rhs.numerator * lhs.denominator;
}

bool operator>(const Fraction& lhs, const Fraction& rhs) {
    return rhs < lhs;
}

bool operator<=(const Fraction& lhs, const Fraction& rhs) {
    return !(lhs > rhs);
}

bool operator>=(const Fraction& lhs, const Fraction& rhs) {
    return !(lhs < rhs);
}

// Доступ по индексу
long long Fraction::operator[](size_t index) const {
    if (index == 0) return numerator;
    if (index == 1) return denominator;
    throw std::out_of_range("Index must be 0 (numerator) or 1 (denominator).");
}

// Операторы преобразования
Fraction::operator double() const {
    return static_cast<double>(numerator) / denominator;
}

Fraction::operator float() const {
    return static_cast<float>(numerator) / denominator;
}

Fraction::operator long long() const {
    return numerator / denominator;
}

// Функция вывода и дружественный оператор
void Fraction::print(std::ostream& os) const {
    os << numerator << '/' << denominator;
}

std::ostream& operator<<(std::ostream& os, const Fraction& f) {
    f.print(os);
    return os;
}