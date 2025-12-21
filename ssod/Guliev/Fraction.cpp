#include "Fraction.h"
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

// Реализация приватных функций
long long Fraction::gcd(long long a, long long b) {
    a = abs(a);
    b = abs(b);
    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

void Fraction::normalize() {
    if (den == 0) {
        throw invalid_argument("Denominator cannot be zero.");
    }
    if (den < 0) {
        num = -num;
        den = -den;
    }
    long long g = gcd(num, den);
    if (g != 0) {
        num /= g;
        den /= g;
    }
}

// Конструкторы
Fraction::Fraction() : num(0), den(1) {}

Fraction::Fraction(long long n) : num(n), den(1) {}

Fraction::Fraction(long long n, long long d) : num(n), den(d) {
    normalize();
}

Fraction::Fraction(const Fraction& other) : num(other.num), den(other.den) {}

// Операторы присваивания
Fraction& Fraction::operator=(const Fraction& other) {
    if (this != &other) {
        num = other.num;
        den = other.den;
    }
    return *this;
}

Fraction& Fraction::operator=(long long n) {
    num = n;
    den = 1;
    return *this;
}

// Арифметические операторы
Fraction Fraction::operator+(const Fraction& other) const {
    return Fraction(num * other.den + other.num * den, den * other.den);
}

Fraction Fraction::operator-(const Fraction& other) const {
    return Fraction(num * other.den - other.num * den, den * other.den);
}

Fraction Fraction::operator*(const Fraction& other) const {
    return Fraction(num * other.num, den * other.den);
}

Fraction Fraction::operator/(const Fraction& other) const {
    if (other.num == 0) {
        throw domain_error("Division by zero.");
    }
    return Fraction(num * other.den, den * other.num);
}

// Составные присваивания
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

// Унарные операторы
Fraction& Fraction::operator++() {
    num += den;
    return *this;
}

Fraction Fraction::operator++(int) {
    Fraction tmp(*this);
    ++(*this);
    return tmp;
}

Fraction& Fraction::operator--() {
    num -= den;
    return *this;
}

Fraction Fraction::operator--(int) {
    Fraction tmp(*this);
    --(*this);
    return tmp;
}

// Логические операторы
bool Fraction::operator==(const Fraction& other) const {
    return num == other.num && den == other.den;
}

bool Fraction::operator!=(const Fraction& other) const {
    return !(*this == other);
}

bool Fraction::operator<(const Fraction& other) const {
    return num * other.den < other.num * den;
}

bool Fraction::operator>(const Fraction& other) const {
    return other < *this;
}

bool Fraction::operator<=(const Fraction& other) const {
    return !(*this > other);
}

bool Fraction::operator>=(const Fraction& other) const {
    return !(*this < other);
}

// Операторы преобразования
Fraction::operator double() const { return static_cast<double>(num) / den; }
Fraction::operator float() const { return static_cast<float>(num) / den; }
Fraction::operator long double() const { return static_cast<long double>(num) / den; }
Fraction::operator int() const { return static_cast<int>(static_cast<double>(*this)); }
Fraction::operator long long() const { return static_cast<long long>(static_cast<double>(*this)); }

// Вывод
void Fraction::print() const {
    cout << num << '/' << den;
}

// Дружественные функции (реализация вне класса)
Fraction operator+(const Fraction& a, long long b) { return a + Fraction(b); }
Fraction operator+(long long a, const Fraction& b) { return Fraction(a) + b; }
Fraction operator-(const Fraction& a, long long b) { return a - Fraction(b); }
Fraction operator-(long long a, const Fraction& b) { return Fraction(a) - b; }
Fraction operator*(const Fraction& a, long long b) { return a * Fraction(b); }
Fraction operator*(long long a, const Fraction& b) { return Fraction(a) * b; }
Fraction operator/(const Fraction& a, long long b) { return a / Fraction(b); }
Fraction operator/(long long a, const Fraction& b) { return Fraction(a) / b; }

ostream& operator<<(ostream& os, const Fraction& f) {
    os << f.num << '/' << f.den;
    return os;
}
