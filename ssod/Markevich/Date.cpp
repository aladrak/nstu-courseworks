#include "Date.h"
#include <iomanip>

namespace {
    const int DAYS_FROM_EPOCH_TO_0001 = -719528; // для расчёта
}

bool Date::isLeapYear(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int Date::daysInMonth(int m, int y) {
    static const int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (m < 1 || m > 12) return 0;
    int d = days[m - 1];
    if (m == 2 && isLeapYear(y)) d++;
    return d;
}

void Date::normalize() {
    if (month < 1 || month > 12)
        throw invalid_argument("Invalid month");
    if (day < 1 || day > daysInMonth(month, year))
        throw invalid_argument("Invalid day for given month/year");
}

Date::Date() : day(1), month(1), year(1999) {}

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {
    normalize();
}

Date::Date(const Date& other) : day(other.day), month(other.month), year(other.year) {}

Date& Date::operator=(const Date& other) {
    if (this != &other) {
        day = other.day;
        month = other.month;
        year = other.year;
    }
    return *this;
}

long long daysFromEpoch(int y, int m, int d) {
    if (m <= 2) {
        y--;
        m += 12;
    }
    long long era = (long long)(y / 400);
    int yoe = (int)(y - era * 400); // [0, 399]
    int doy = (153 * (m - 3) + 2) / 5 + d - 1; // [0, 365]
    int doe = yoe * 365 + yoe / 4 - yoe / 100 + doy; // [0, 146096]
    return era * 146097LL + doe - DAYS_FROM_EPOCH_TO_0001;
}

Date dateFromDays(long long days) {
    days += DAYS_FROM_EPOCH_TO_0001;
    long long era = (days >= 0 ? days : days - 146096) / 146097;
    unsigned doe = (unsigned)(days - era * 146097); // [0, 146096]
    unsigned yoe = (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365; // [0, 399]
    int y = (int)(yoe + era * 400);
    unsigned doy = doe - (365 * yoe + yoe / 4 - yoe/100); // [0, 365]
    unsigned mp = (5 * doy + 2) / 153; // [0, 11]
    unsigned d = doy - (153 * mp + 2) / 5 + 1; // [1, 31]
    unsigned m = mp + (mp < 10 ? 3 : -9); // [1, 12]
    y += (m <= 2);
    return Date((int)d, (int)m, y);
}

Date Date::operator+(int days) const {
    long long total = daysFromEpoch(year, month, day) + days;
    return dateFromDays(total);
}

Date Date::operator-(int days) const {
    return *this + (-days);
}

int Date::operator-(const Date& other) const {
    return (int)(daysFromEpoch(year, month, day) - daysFromEpoch(other.year, other.month, other.day));
}

Date& Date::operator+=(int days) {
    *this = *this + days;
    return *this;
}

Date& Date::operator-=(int days) {
    *this = *this - days;
    return *this;
}

Date& Date::operator++() {
    *this += 1;
    return *this;
}

Date Date::operator++(int) {
    Date temp(*this);
    ++(*this);
    return temp;
}

Date& Date::operator--() {
    *this -= 1;
    return *this;
}

Date Date::operator--(int) {
    Date temp(*this);
    --(*this);
    return temp;
}

bool Date::operator<(const Date& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    return day < other.day;
}

bool Date::operator>(const Date& other) const { return other < *this; }
bool Date::operator<=(const Date& other) const { return !(other < *this); }
bool Date::operator>=(const Date& other) const { return !(*this < other); }
bool Date::operator==(const Date& other) const {
    return day == other.day && month == other.month && year == other.year;
}
bool Date::operator!=(const Date& other) const { return !(*this == other); }

int Date::operator[](int index) const {
    switch (index) {
        case 0: return day;
        case 1: return month;
        case 2: return year;
        default: throw out_of_range("Index must be 0 (day), 1 (month), or 2 (year)");
    }
}

Date::operator string() const {
    ostringstream oss;
    oss << setfill('0')
        << year << "-"
        << setw(2) << month << "-"
        << setw(2) << day;
    return oss.str();
}

void Date::print(ostream& os) const {
    os << setfill('0')
       << setw(2) << day << "."
       << setw(2) << month << "."
       << year;
}

ostream& operator<<(ostream& os, const Date& d) {
    d.print(os);
    return os;
}