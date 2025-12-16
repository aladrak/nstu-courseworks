using namespace std;
#include <iostream>
#include <cmath>

class Fraction {
private:
    long long num;  // числитель
    long long den;  // знаменатель (всегда > 0)

    // Вспомогательная функция: НОД
    static long long gcd(long long a, long long b) {
        a = abs(a);
        b = abs(b);
        while (b != 0) {
            long long t = b;
            b = a % b;
            a = t;
        }
        return a;
    }

    // Нормализация: знаменатель > 0, дробь несократима
    void normalize() {
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

public:
    // Конструкторы
    Fraction() : num(0), den(1) {}

    Fraction(long long n) : num(n), den(1) {}

    Fraction(long long n, long long d) : num(n), den(d) {
        normalize();
    }

    Fraction(const Fraction& other) : num(other.num), den(other.den) {}

    // Деструктор (по умолчанию)
    ~Fraction() = default;

    // Операторы присваивания
    Fraction& operator=(const Fraction& other) {
        if (this != &other) {
            num = other.num;
            den = other.den;
        }
        return *this;
    }

    Fraction& operator=(long long n) {
        num = n;
        den = 1;
        return *this;
    }

    // Арифметические операторы (члены)
    Fraction operator+(const Fraction& other) const {
        return Fraction(num * other.den + other.num * den, den * other.den);
    }

    Fraction operator-(const Fraction& other) const {
        return Fraction(num * other.den - other.num * den, den * other.den);
    }

    Fraction operator*(const Fraction& other) const {
        return Fraction(num * other.num, den * other.den);
    }

    Fraction operator/(const Fraction& other) const {
        if (other.num == 0) {
            throw domain_error("Division by zero.");
        }
        return Fraction(num * other.den, den * other.num);
    }

    // Составные присваивания
    Fraction& operator+=(const Fraction& other) {
        *this = *this + other;
        return *this;
    }

    Fraction& operator-=(const Fraction& other) {
        *this = *this - other;
        return *this;
    }

    Fraction& operator*=(const Fraction& other) {
        *this = *this * other;
        return *this;
    }

    Fraction& operator/=(const Fraction& other) {
        *this = *this / other;
        return *this;
    }

    // Унарные инкремент/декремент
    Fraction& operator++() {        // префиксный ++
        num += den;
        return *this;
    }

    Fraction operator++(int) {      // постфиксный ++
        Fraction tmp(*this);
        ++(*this);
        return tmp;
    }

    Fraction& operator--() {        // префиксный --
        num -= den;
        return *this;
    }

    Fraction operator--(int) {      // постфиксный --
        Fraction tmp(*this);
        --(*this);
        return tmp;
    }

    // Логические операторы
    bool operator==(const Fraction& other) const {
        return num == other.num && den == other.den;
    }

    bool operator!=(const Fraction& other) const {
        return !(*this == other);
    }

    bool operator<(const Fraction& other) const {
        return num * other.den < other.num * den;
    }

    bool operator>(const Fraction& other) const {
        return other < *this;
    }

    bool operator<=(const Fraction& other) const {
        return !(*this > other);
    }

    bool operator>=(const Fraction& other) const {
        return !(*this < other);
    }

    // Операторы преобразования
    explicit operator double() const { return static_cast<double>(num) / den; }
    explicit operator float() const { return static_cast<float>(num) / den; }
    explicit operator long double() const { return static_cast<long double>(num) / den; }
    explicit operator int() const { return static_cast<int>(static_cast<double>(*this)); }
    explicit operator long long() const { return static_cast<long long>(static_cast<double>(*this)); }

    // Вывод
    void print() const {
        cout << num << '/' << den;
    }

    // Дружественные операторы для смешанных операций и потоков
    friend Fraction operator+(const Fraction& a, long long b) { return a + Fraction(b); }
    friend Fraction operator+(long long a, const Fraction& b) { return Fraction(a) + b; }
    friend Fraction operator-(const Fraction& a, long long b) { return a - Fraction(b); }
    friend Fraction operator-(long long a, const Fraction& b) { return Fraction(a) - b; }
    friend Fraction operator*(const Fraction& a, long long b) { return a * Fraction(b); }
    friend Fraction operator*(long long a, const Fraction& b) { return Fraction(a) * b; }
    friend Fraction operator/(const Fraction& a, long long b) { return a / Fraction(b); }
    friend Fraction operator/(long long a, const Fraction& b) { return Fraction(a) / b; }

    friend ostream& operator<<(ostream& os, const Fraction& f) {
        os << f.num << '/' << f.den;
        return os;
    }
};