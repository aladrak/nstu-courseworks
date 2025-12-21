using namespace std;

#include <iostream>
#include <stdexcept>

class Fraction {
private:
    long long numerator;
    long long denominator;

    void normalize();
    static long long gcd(long long a, long long b);

public:
    // Конструкторы
    Fraction();
    Fraction(long long num, long long den = 1);
    Fraction(const Fraction& other);

    // Деструктор
    ~Fraction() = default;

    // Операторы присваивания
    Fraction& operator=(const Fraction& other);
    Fraction& operator=(long long value);

    // Арифметические операторы: бинарные (+, -, *, /)
    friend Fraction operator+(const Fraction& lhs, const Fraction& rhs);
    friend Fraction operator-(const Fraction& lhs, const Fraction& rhs);
    friend Fraction operator*(const Fraction& lhs, const Fraction& rhs);
    friend Fraction operator/(const Fraction& lhs, const Fraction& rhs);

    // Аримфетика с базовым типом (long long)
    friend Fraction operator+(const Fraction& lhs, long long rhs);
    friend Fraction operator+(long long lhs, const Fraction& rhs);
    friend Fraction operator-(const Fraction& lhs, long long rhs);
    friend Fraction operator-(long long lhs, const Fraction& rhs);
    friend Fraction operator*(const Fraction& lhs, long long rhs);
    friend Fraction operator*(long long lhs, const Fraction& rhs);
    friend Fraction operator/(const Fraction& lhs, long long rhs);
    friend Fraction operator/(long long lhs, const Fraction& rhs);

    // Арифметика с накоплением
    Fraction& operator+=(const Fraction& other);
    Fraction& operator-=(const Fraction& other);
    Fraction& operator*=(const Fraction& other);
    Fraction& operator/=(const Fraction& other);

    Fraction& operator+=(long long value);
    Fraction& operator-=(long long value);
    Fraction& operator*=(long long value);
    Fraction& operator/=(long long value);

    // Унарные операторы ++
    Fraction& operator++();      // Префиксный
    Fraction operator++(int);    // Постфиксный

    // Унарные операторы --
    Fraction& operator--();      // Префиксный
    Fraction operator--(int);    // Постфиксный

    // Логические операторы
    friend bool operator==(const Fraction& lhs, const Fraction& rhs);
    friend bool operator!=(const Fraction& lhs, const Fraction& rhs);
    friend bool operator<(const Fraction& lhs, const Fraction& rhs);
    friend bool operator>(const Fraction& lhs, const Fraction& rhs);
    friend bool operator<=(const Fraction& lhs, const Fraction& rhs);
    friend bool operator>=(const Fraction& lhs, const Fraction& rhs);

    // Доступ по индексу: [0] — числитель, [1] — знаменатель
    long long operator[](size_t index) const;

    // Операторы преобразования к базовому типу
    explicit operator double() const;
    explicit operator float() const;
    explicit operator long long() const;

    // Функция вывода
    void print(std::ostream& os = std::cout) const;

    // Дружественный оператор потока
    friend std::ostream& operator<<(std::ostream& os, const Fraction& f);
};