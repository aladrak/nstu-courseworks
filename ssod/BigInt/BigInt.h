#include <vector>
#include <stdexcept>

class BigInt {
private:
    std::vector<unsigned char> data;
    bool negative;
    
    void normalize();
    int compare(const BigInt& other) const;

public:
    // Конструкторы и деструктор
    BigInt();
    explicit BigInt(long long value);
    BigInt(const std::vector<unsigned char>& bytes, bool isNegative = false);
    BigInt(const BigInt& other);
    ~BigInt() = default;

    // Операторы присваивания
    BigInt& operator=(const BigInt& other);
    BigInt& operator=(long long value);

    // Арифметические операторы
    BigInt operator+(const BigInt& other) const;
    BigInt operator-(const BigInt& other) const;
    BigInt operator*(const BigInt& other) const;
    BigInt operator/(const BigInt& other) const;
    BigInt operator%(const BigInt& other) const;

    // Арифметика с нак accumulation
    BigInt& operator+=(const BigInt& other);
    BigInt& operator-=(const BigInt& other);

    // Унарные операторы
    BigInt operator-() const;
    BigInt& operator++();      // префиксный
    BigInt operator++(int);    // постфиксный
    BigInt& operator--();      // префиксный
    BigInt operator--(int);    // постфиксный

    // Операторы сравнения
    bool operator<(const BigInt& other) const;
    bool operator>(const BigInt& other) const;
    bool operator==(const BigInt& other) const;
    bool operator!=(const BigInt& other) const;
    bool operator<=(const BigInt& other) const;
    bool operator>=(const BigInt& other) const;

    // Доступ к байтам
    unsigned char& operator[](size_t index);
    const unsigned char& operator[](size_t index) const;

    // Операторы с базовыми типами (long long)
    friend BigInt operator+(long long lhs, const BigInt& rhs);
    friend BigInt operator-(long long lhs, const BigInt& rhs);
    friend BigInt operator*(long long lhs, const BigInt& rhs);
    friend BigInt operator/(long long lhs, const BigInt& rhs);

    BigInt operator+(long long rhs) const;
    BigInt operator-(long long rhs) const;
    BigInt operator*(long long rhs) const;
    BigInt operator/(long long rhs) const;

    // Преобразование к базовому типу
    explicit operator long long() const;

    // Дружественные функции ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const BigInt& num);
    friend std::istream& operator>>(std::istream& is, BigInt& num);
};

// Глобальные операторы для базовых типов слева
BigInt operator+(long long lhs, const BigInt& rhs);
BigInt operator-(long long lhs, const BigInt& rhs);
BigInt operator*(long long lhs, const BigInt& rhs);
BigInt operator/(long long lhs, const BigInt& rhs);