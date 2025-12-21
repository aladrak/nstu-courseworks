#include "BigInt.h"
#include <algorithm>
#include <sstream>

void BigInt::normalize() {
    while (!data.empty() && data.back() == 0)
        data.pop_back();
    if (data.empty()) {
        negative = false;
        data.push_back(0);
    }
}

int BigInt::compare(const BigInt& other) const {
    if (negative && !other.negative) return -1;
    if (!negative && other.negative) return 1;
    if (data.size() != other.data.size())
        return (negative ? -1 : 1) * (data.size() < other.data.size() ? -1 : 1);

    for (size_t i = data.size(); i-- > 0;) {
        if (data[i] != other.data[i])
            return (negative ? -1 : 1) * (data[i] < other.data[i] ? -1 : 1);
    }
    return 0;
}

// Конструкторы и деструктор
BigInt::BigInt() : negative(false) {
    data.push_back(0);
}

BigInt::BigInt(long long value) : negative(value < 0) {
    unsigned long long abs_val = std::abs(value);
    if (abs_val == 0) {
        data.push_back(0);
    } else {
        while (abs_val > 0) {
            data.push_back(static_cast<unsigned char>(abs_val & 0xFF));
            abs_val >>= 8;
        }
    }
}

BigInt::BigInt(const std::vector<unsigned char>& bytes, bool isNegative)
    : data(bytes), negative(isNegative) {
    normalize();
}

BigInt::BigInt(const BigInt& other)
    : data(other.data), negative(other.negative) {}

// Операторы присваивания
BigInt& BigInt::operator=(const BigInt& other) {
    if (this != &other) {
        data = other.data;
        negative = other.negative;
    }
    return *this;
}

BigInt& BigInt::operator=(long long value) {
    *this = BigInt(value);
    return *this;
}

// Арифметические операторы
BigInt BigInt::operator+(const BigInt& other) const {
    if (negative == other.negative) {
        std::vector<unsigned char> res;
        size_t max_size = std::max(data.size(), other.data.size());
        unsigned int carry = 0;
        for (size_t i = 0; i < max_size || carry; ++i) {
            unsigned int sum = carry;
            if (i < data.size()) sum += data[i];
            if (i < other.data.size()) sum += other.data[i];
            res.push_back(static_cast<unsigned char>(sum & 0xFF));
            carry = sum >> 8;
        }
        return BigInt(res, negative);
    } else {
        BigInt a(*this), b(other);
        a.negative = false;
        b.negative = false;
        if (a < b) {
            BigInt result = b - a;
            result.negative = !negative;
            return result;
        } else {
            BigInt result = a - b;
            result.negative = negative;
            return result;
        }
    }
}

BigInt BigInt::operator-(const BigInt& other) const {
    if (!negative && other.negative) {
        return (*this) + BigInt(other.data, false);
    }
    if (negative && !other.negative) {
        BigInt sum = BigInt(data, false) + BigInt(other.data, false);
        return -sum;
    }
    if (negative && other.negative) {
        BigInt a_pos(data, false);
        BigInt b_pos(other.data, false);
        return b_pos - a_pos;
    }
    if (*this < other) {
        BigInt diff = other - (*this);
        diff.negative = true;
        return diff;
    }
    std::vector<unsigned char> res;
    unsigned int borrow = 0;
    for (size_t i = 0; i < data.size(); ++i) {
        unsigned int a = data[i];
        unsigned int b = (i < other.data.size()) ? other.data[i] : 0;
        if (a < b + borrow) {
            res.push_back(static_cast<unsigned char>(a + 256 - b - borrow));
            borrow = 1;
        } else {
            res.push_back(static_cast<unsigned char>(a - b - borrow));
            borrow = 0;
        }
    }
    BigInt result(res, false);
    result.normalize();
    return result;
}

BigInt BigInt::operator*(const BigInt& other) const {
    if (data.size() == 1 && data[0] == 0) return BigInt(0);
    if (other.data.size() == 1 && other.data[0] == 0) return BigInt(0);

    std::vector<unsigned char> res(data.size() + other.data.size(), 0);
    for (size_t i = 0; i < data.size(); ++i) {
        unsigned int carry = 0;
        for (size_t j = 0; j < other.data.size() || carry; ++j) {
            unsigned long long cur = res[i + j] + carry;
            if (j < other.data.size())
                cur += static_cast<unsigned long long>(data[i]) * other.data[j];
            res[i + j] = static_cast<unsigned char>(cur & 0xFF);
            carry = static_cast<unsigned int>(cur >> 8);
        }
    }
    while (!res.empty() && res.back() == 0)
        res.pop_back();
    if (res.empty()) res.push_back(0);
    return BigInt(res, negative != other.negative);
}

BigInt BigInt::operator/(const BigInt& other) const {
    if (other.data.size() == 1 && other.data[0] == 0)
        throw std::runtime_error("Division by zero");

    BigInt dividend(*this);
    BigInt divisor(other);
    bool result_negative = dividend.negative != divisor.negative;

    dividend.negative = false;
    divisor.negative = false;

    if (dividend < divisor)
        return BigInt(0);

    BigInt quotient(0);
    BigInt current(0);

    for (int i = static_cast<int>(dividend.data.size()) - 1; i >= 0; --i) {
        current.data.insert(current.data.begin(), dividend.data[i]);
        current.normalize();

        BigInt temp_divisor = divisor;
        long long count = 0;
        while (current >= temp_divisor) {
            current = current - temp_divisor;
            ++count;
        }
        quotient = quotient * BigInt(256) + BigInt(count);
    }

    quotient.negative = result_negative;
    quotient.normalize();
    return quotient;
}

// Арифметика с накоплением
BigInt& BigInt::operator+=(const BigInt& other) {
    *this = *this + other;
    return *this;
}

BigInt& BigInt::operator-=(const BigInt& other) {
    *this = *this - other;
    return *this;
}

// Унарные операторы
BigInt BigInt::operator-() const {
    BigInt res(*this);
    if (res.data.size() == 1 && res.data[0] == 0)
        res.negative = false;
    else
        res.negative = !res.negative;
    return res;
}

BigInt& BigInt::operator++() {
    *this += BigInt(1);
    return *this;
}

BigInt BigInt::operator++(int) {
    BigInt old(*this);
    ++(*this);
    return old;
}

BigInt& BigInt::operator--() {
    *this -= BigInt(1);
    return *this;
}

BigInt BigInt::operator--(int) {
    BigInt old(*this);
    --(*this);
    return old;
}

// Логические операторы
bool BigInt::operator<(const BigInt& other) const { return compare(other) < 0; }
bool BigInt::operator>(const BigInt& other) const { return compare(other) > 0; }
bool BigInt::operator==(const BigInt& other) const { return compare(other) == 0; }
bool BigInt::operator!=(const BigInt& other) const { return !(*this == other); }
bool BigInt::operator<=(const BigInt& other) const { return !(*this > other); }
bool BigInt::operator>=(const BigInt& other) const { return !(*this < other); }

// Операторы индексации
unsigned char& BigInt::operator[](size_t index) {
    if (index >= data.size())
        throw std::out_of_range("Index out of range");
    return data[index];
}

const unsigned char& BigInt::operator[](size_t index) const {
    if (index >= data.size())
        throw std::out_of_range("Index out of range");
    return data[index];
}

// Операторы с long long
BigInt BigInt::operator+(long long rhs) const { return *this + BigInt(rhs); }
BigInt BigInt::operator-(long long rhs) const { return *this - BigInt(rhs); }
BigInt BigInt::operator*(long long rhs) const { return *this * BigInt(rhs); }
BigInt BigInt::operator/(long long rhs) const { return *this / BigInt(rhs); }

BigInt operator+(long long lhs, const BigInt& rhs) { return BigInt(lhs) + rhs; }
BigInt operator-(long long lhs, const BigInt& rhs) { return BigInt(lhs) - rhs; }
BigInt operator*(long long lhs, const BigInt& rhs) { return BigInt(lhs) * rhs; }
BigInt operator/(long long lhs, const BigInt& rhs) { return BigInt(lhs) / rhs; }

// Преобразование к базовому типу
BigInt::operator long long() const {
    if (data.size() > sizeof(long long))
        throw std::overflow_error("BigInt too large to convert to long long");
    unsigned long long val = 0;
    for (size_t i = 0; i < data.size(); ++i) {
        val |= static_cast<unsigned long long>(data[i]) << (i * 8);
    }
    if (negative) {
        if (val > static_cast<unsigned long long>(LLONG_MAX) + 1)
            throw std::overflow_error("BigInt too large to convert to long long");
        return -static_cast<long long>(val);
    } else {
        if (val > static_cast<unsigned long long>(LLONG_MAX))
            throw std::overflow_error("BigInt too large to convert to long long");
        return static_cast<long long>(val);
    }
}

// Дружественные функции ввода/вывода
std::ostream& operator<<(std::ostream& os, const BigInt& num) {
    if (num.data.size() == 1 && num.data[0] == 0) {
        os << "0";
        return os;
    }
    if (num.negative)
        os << "-";
    // Вывод в шестнадцатеричном виде для простоты (можно заменить на десятичный при желании)
    for (auto it = num.data.rbegin(); it != num.data.rend(); ++it) {
        os << std::hex << static_cast<int>(*it);
        if (it + 1 != num.data.rend())
            os << " ";
    }
    return os;
}

std::istream& operator>>(std::istream& is, BigInt& num) {
    std::string s;
    is >> s;
    if (s.empty()) {
        num = BigInt(0);
        return is;
    }

    bool neg = (s[0] == '-');
    size_t start = neg ? 1 : 0;
    std::vector<unsigned char> bytes;
    std::stringstream ss;
    ss << std::hex;

    size_t pos = start;
    while (pos < s.length()) {
        if (std::isspace(s[pos])) {
            ++pos;
            continue;
        }
        if (pos + 1 >= s.length()) {
            is.setstate(std::ios::failbit);
            return is;
        }
        std::string byte_str = s.substr(pos, 2);
        int byte_val;
        ss.clear();
        ss.str(byte_str);
        if (!(ss >> byte_val)) {
            is.setstate(std::ios::failbit);
            return is;
        }
        bytes.push_back(static_cast<unsigned char>(byte_val));
        pos += 2;
    }
    std::reverse(bytes.begin(), bytes.end());
    num = BigInt(bytes, neg);
    return is;
}