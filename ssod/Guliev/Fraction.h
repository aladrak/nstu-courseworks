using namespace std;
#include <iostream>
#include <cmath> 

class Fraction {
private:
    long long num;  // числитель
    long long den;  // знаменатель (всегда > 0)

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

    // Арифметические операторы (члены)
    Fraction operator+(const Fraction& other) const;
    Fraction operator-(const Fraction& other) const;
    Fraction operator*(const Fraction& other) const;
    Fraction operator/(const Fraction& other) const;

    // Составные присваивания
    Fraction& operator+=(const Fraction& other);
    Fraction& operator-=(const Fraction& other);
    Fraction& operator*=(const Fraction& other);
    Fraction& operator/=(const Fraction& other);

    // Унарные инкремент/декремент
    Fraction& operator++();            // префиксный ++
    Fraction operator++(int);          // постфиксный ++
    Fraction& operator--();            // префиксный --
    Fraction operator--(int);          // постфиксный --

    // Логические операторы
    bool operator==(const Fraction& other) const;
    bool operator!=(const Fraction& other) const;
    bool operator<(const Fraction& other) const;
    bool operator>(const Fraction& other) const;
    bool operator<=(const Fraction& other) const;
    bool operator>=(const Fraction& other) const;

    // Операторы преобразования
    explicit operator double() const;
    explicit operator float() const;
    explicit operator long double() const;
    explicit operator int() const;
    explicit operator long long() const;

    // Вывод
    void print() const;

    // Дружественные функции (объявлены внутри класса)
    friend Fraction operator+(const Fraction& a, long long b);
    friend Fraction operator+(long long a, const Fraction& b);
    friend Fraction operator-(const Fraction& a, long long b);
    friend Fraction operator-(long long a, const Fraction& b);
    friend Fraction operator*(const Fraction& a, long long b);
    friend Fraction operator*(long long a, const Fraction& b);
    friend Fraction operator/(const Fraction& a, long long b);
    friend Fraction operator/(long long a, const Fraction& b);

    friend std::ostream& operator<<(std::ostream& os, const Fraction& f);
};
