using namespace std;

#include <iostream>
#include <stdexcept>

class Date {
private:
    int day;
    int month;
    int year;

    static bool isLeapYear(int y); // Определение високосного года
    static int daysInMonth(int m, int y);
    void normalize();

public:
    // Конструкторы
    Date();
    Date(int d, int m, int y);
    Date(const Date& other);

    // Деструктор
    ~Date() = default;

    // Операторы присваивания
    Date& operator=(const Date& other);

    // Арифметические операторы
    Date operator+(int days) const;
    Date operator-(int days) const;
    int operator-(const Date& other) const;
    Date& operator+=(int days);
    Date& operator-=(int days);

    // Унарные операторы
    Date& operator++();       // префиксный ++
    Date operator++(int);     // постфиксный ++
    Date& operator--();       // префиксный --
    Date operator--(int);     // постфиксный --

    // Логические операторы
    bool operator<(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;
    bool operator<=(const Date& other) const;
    bool operator>=(const Date& other) const;

    // Операторы доступа
    int operator[](int index) const; // 0 день, 1 месяц, 2 год

    // Преобразование к базовому типу
    explicit operator long long() const; // количество дней с эпохи

    // Вывод
    void print(std::ostream& os = std::cout) const;
    friend std::ostream& operator<<(std::ostream& os, const Date& d);
};