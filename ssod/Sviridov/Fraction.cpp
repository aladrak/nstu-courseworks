#include "Fraction.h"

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

Fraction::Fraction() : num(0), den(1) {}

Fraction::Fraction(long long n) : num(n), den(1) {}

Fraction::Fraction(long long n, long long d) : num(n), den(d) {
    normalize();
}

Fraction::Fraction(const Fraction& other) : num(other.num), den(other.den) {}

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

Fraction operator+(const Fraction& a, const Fraction& b) {
    return Fraction(a.num * b.den + b.num * a.den, a.den * b.den);
}

Fraction operator-(const Fraction& a, const Fraction& b) {
    return Fraction(a.num * b.den - b.num * a.den, a.den * b.den);
}

Fraction operator*(const Fraction& a, const Fraction& b) {
    return Fraction(a.num * b.num, a.den * b.den);
}

Fraction operator/(const Fraction& a, const Fraction& b) {
    if (b.num == 0) {
        throw domain_error("Division by zero.");
    }
    return Fraction(a.num * b.den, a.den * b.num);
}

// Fraction и long long
Fraction operator+(const Fraction& a, long long b) { return a + Fraction(b); }
Fraction operator+(long long a, const Fraction& b) { return Fraction(a) + b; }
Fraction operator-(const Fraction& a, long long b) { return a - Fraction(b); }
Fraction operator-(long long a, const Fraction& b) { return Fraction(a) - b; }
Fraction operator*(const Fraction& a, long long b) { return a * Fraction(b); }
Fraction operator*(long long a, const Fraction& b) { return Fraction(a) * b; }
Fraction operator/(const Fraction& a, long long b) { return a / Fraction(b); }
Fraction operator/(long long a, const Fraction& b) { return Fraction(a) / b; }

Fraction& Fraction::operator+=(const Fraction& other) { return *this = *this + other; }
Fraction& Fraction::operator-=(const Fraction& other) { return *this = *this - other; }
Fraction& Fraction::operator*=(const Fraction& other) { return *this = *this * other; }
Fraction& Fraction::operator/=(const Fraction& other) { return *this = *this / other; }

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

bool operator==(const Fraction& a, const Fraction& b) {
    return a.num == b.num && a.den == b.den;
}

bool operator!=(const Fraction& a, const Fraction& b) {
    return !(a == b);
}

bool operator<(const Fraction& a, const Fraction& b) {
    return a.num * b.den < b.num * a.den;
}

bool operator>(const Fraction& a, const Fraction& b) {
    return b < a;
}

bool operator<=(const Fraction& a, const Fraction& b) {
    return !(a > b);
}

bool operator>=(const Fraction& a, const Fraction& b) {
    return !(a < b);
}

Fraction::operator double() const {
    return static_cast<double>(num) / den;
}

Fraction::operator float() const {
    return static_cast<float>(num) / den;
}

Fraction::operator long double() const {
    return static_cast<long double>(num) / den;
}

Fraction::operator int() const {
    return static_cast<int>(static_cast<double>(*this));
}

Fraction::operator long long() const {
    return static_cast<long long>(static_cast<double>(*this));
}

void Fraction::print() const {
    cout << num << '/' << den;
}

ostream& operator<<(ostream& os, const Fraction& f) {
    os << f.num << '/' << f.den;
    return os;
}