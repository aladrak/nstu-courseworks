using namespace std;
#include <iostream>
#include <stdexcept>

class Date {
private:
    long days_;

    static bool isLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    static int daysInMonth(int year, int month) {
        if (month < 1 || month > 12)
            throw out_of_range("Month must be 1-12");
        static const int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        int d = days[month - 1];
        if (month == 2 && isLeapYear(year)) d++;
        return d;
    }

    static long dateToDays(int day, int month, int year) {
        if (year < 1970)
            throw out_of_range("Year must be >= 1970");
        if (month < 1 || month > 12)
            throw out_of_range("Month must be 1-12");
        if (day < 1 || day > daysInMonth(year, month))
            throw out_of_range("Invalid day for given month/year");
        long total = 0;
        for (int y = 1970; y < year; ++y)
            total += isLeapYear(y) ? 366 : 365;
        for (int m = 1; m < month; ++m)
            total += daysInMonth(year, m);
        total += day - 1;
        return total;
    }

    static void daysToDate(long days, int& day, int& month, int& year) {
        if (days < 0)
            throw out_of_range("Days cannot be negative");
        year = 1970;
        while (true) {
            long yearDays = isLeapYear(year) ? 366 : 365;
            if (days < yearDays) break;
            days -= yearDays;
            ++year;
        }
        month = 1;
        while (days >= daysInMonth(year, month)) {
            days -= daysInMonth(year, month);
            ++month;
        }
        day = static_cast<int>(days) + 1;
    }

public:
    // Констукторы
    Date() : days_(0) {}

    Date(int day, int month, int year) {
        days_ = dateToDays(day, month, year);
    }

    explicit Date(long days) {
        if (days < 0)
            throw out_of_range("Days cannot be negative");
        days_ = days;
    }

    Date(const Date& other) : days_(other.days_) {}

    // Деструкторы
    ~Date() = default;

    // Оператор присваивания
    Date& operator=(const Date& other) {
        if (this != &other) {
            days_ = other.days_;
        }
        return *this;
    }

    // Арифм операторы
    Date operator+(const Date& other) const {
        return Date(days_ + other.days_);
    }

    Date operator-(const Date& other) const {
        if (days_ < other.days_)
            throw underflow_error("Resulting date would be before 1970-01-01");
        return Date(days_ - other.days_);
    }

    Date operator*(long multiplier) const {
        if (multiplier < 0)
            throw invalid_argument("Multiplier must be non-negative");
        return Date(days_ * multiplier);
    }

    Date operator/(long divisor) const {
        if (divisor <= 0)
            throw invalid_argument("Divisor must be positive");
        return Date(days_ / divisor);
    }

    // Friend операторы
    friend Date operator+(long value, const Date& d) {
        return Date(value + d.days_);
    }

    friend Date operator-(long value, const Date& d) {
        if (value < d.days_)
            throw underflow_error("Resulting date would be before 1970-01-01");
        return Date(value - d.days_);
    }

    friend Date operator*(long value, const Date& d) {
        if (value < 0)
            throw invalid_argument("Multiplier must be non-negative");
        return Date(value * d.days_);
    }

    friend Date operator/(long value, const Date& d) {
        if (d.days_ == 0)
            throw domain_error("Division by zero date (1970-01-01)");
        if (value < 0)
            throw invalid_argument("Numerator must be non-negative");
        return Date(value / d.days_);
    }

    // арифм присваивание
    Date& operator+=(const Date& other) {
        days_ += other.days_;
        return *this;
    }

    Date& operator-=(const Date& other) {
        if (days_ < other.days_)
            throw underflow_error("Resulting date would be before 1970-01-01");
        days_ -= other.days_;
        return *this;
    }

    Date& operator*=(long multiplier) {
        if (multiplier < 0)
            throw invalid_argument("Multiplier must be non-negative");
        days_ *= multiplier;
        return *this;
    }

    Date& operator/=(long divisor) {
        if (divisor <= 0)
            throw invalid_argument("Divisor must be positive");
        days_ /= divisor;
        return *this;
    }

    // Префиксный инкремент
    Date& operator++() {
        ++days_;
        return *this;
    }

    // Постфиксный инкремент
    Date operator++(int) {
        Date temp(*this);
        ++(*this);
        return temp;
    }

    // Префиксный декрмент
    Date& operator--() {
        if (days_ == 0)
            throw underflow_error("Cannot decrement before 1970-01-01");
        --days_;
        return *this;
    }

    // Постфиксный декремент
    Date operator--(int) {
        Date temp(*this);
        --(*this);
        return temp;
    }

    // Операторы сравнения
    bool operator<(const Date& other) const { return days_ < other.days_; }
    bool operator>(const Date& other) const { return days_ > other.days_; }
    bool operator==(const Date& other) const { return days_ == other.days_; }
    bool operator!=(const Date& other) const { return days_ != other.days_; }
    bool operator<=(const Date& other) const { return days_ <= other.days_; }
    bool operator>=(const Date& other) const { return days_ >= other.days_; }

    // Оператор доступа
    int operator[](int index) const {
        int d, m, y;
        daysToDate(days_, d, m, y);
        switch (index) {
            case 0: return d;
            case 1: return m;
            case 2: return y;
            default: throw out_of_range("Index must be 0, 1, or 2");
        }
    }

    explicit operator long() const {
        return days_;
    }

    // Вывод
    void print() const {
        int d, m, y;
        daysToDate(days_, d, m, y);
        char fill = cout.fill('0');
        cout << y << '-';
        cout.width(2); cout << m << '-';
        cout.width(2); cout << d;
        cout.fill(fill);
    }
};