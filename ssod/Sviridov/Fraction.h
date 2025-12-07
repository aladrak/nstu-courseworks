using namespace std;
#include <iostream>

class Fraction {
private:
    long long num;   // числитель
    long long den;   // знаменатель (всегда > 0)

    static long long gcd(long long a, long long b);
    void normalize();

public:
    // Конструкторы
    Fraction();
    Fraction(long long n);
    Fraction(long long n, long long d);
    Fraction(const Fraction& other);

    // Деструктор
    ~Fraction() = default;

    // Операторы присваивания
    Fraction& operator=(const Fraction& other);
    Fraction& operator=(long long n);

    // Арифметические операторы (бинарные)
    friend Fraction operator+(const Fraction& a, const Fraction& b);
    friend Fraction operator-(const Fraction& a, const Fraction& b);
    friend Fraction operator*(const Fraction& a, const Fraction& b);
    friend Fraction operator/(const Fraction& a, const Fraction& b);

    // Арифметика между Fraction и базовым типом
    friend Fraction operator+(const Fraction& a, long long b);
    friend Fraction operator+(long long a, const Fraction& b);
    friend Fraction operator-(const Fraction& a, long long b);
    friend Fraction operator-(long long a, const Fraction& b);
    friend Fraction operator*(const Fraction& a, long long b);
    friend Fraction operator*(long long a, const Fraction& b);
    friend Fraction operator/(const Fraction& a, long long b);
    friend Fraction operator/(long long a, const Fraction& b);

    // Арифметика с накоплением
    Fraction& operator+=(const Fraction& other);
    Fraction& operator-=(const Fraction& other);
    Fraction& operator*=(const Fraction& other);
    Fraction& operator/=(const Fraction& other);

    // Унарные операторы
    Fraction& operator++();            // префиксный ++
    Fraction operator++(int);          // постфиксный ++
    Fraction& operator--();            // префиксный --
    Fraction operator--(int);          // постфиксный --

    // Логические операторы
    friend bool operator==(const Fraction& a, const Fraction& b);
    friend bool operator!=(const Fraction& a, const Fraction& b);
    friend bool operator<(const Fraction& a, const Fraction& b);
    friend bool operator>(const Fraction& a, const Fraction& b);
    friend bool operator<=(const Fraction& a, const Fraction& b);
    friend bool operator>=(const Fraction& a, const Fraction& b);

    // Операторы преобразования
    explicit operator double() const;
    explicit operator float() const;
    explicit operator long double() const;
    explicit operator int() const;
    explicit operator long long() const;

    // Вывод
    void print() const;
    friend ostream& operator<<(ostream& os, const Fraction& f);
};