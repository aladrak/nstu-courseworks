using namespace std;
#include "LongNumber.h"
#include <iostream>
#include <cassert>

int main() {
    cout << " Testing LongNumber \n";

    try {
        // Конструкторы
        LongNumber a;                          // "0"
        LongNumber b("12345678901234567890"); // из строки
        LongNumber c(9876543210ULL);           // из ULL
        LongNumber d(b);                       // копия

        cout << "a = " << a << "\n";
        cout << "b = " << b << "\n";
        cout << "c = " << c << "\n";
        cout << "d = " << d << "\n";

        // Присваивание
        a = "555";
        cout << "a = " << a << " (after string assign)\n";
        a = 777ULL;
        cout << "a = " << a << " (after ULL assign)\n";

        // Арифметика LongNumber + LongNumber
        LongNumber sum = b + c;
        LongNumber diff = b - c;
        LongNumber prod = b * c;
        LongNumber quot = b / c;

        cout << "b + c = " << sum << "\n";
        cout << "b - c = " << diff << "\n";
        cout << "b * c = " << prod << "\n";
        cout << "b / c = " << quot << "\n";

        // Составные операторы
        LongNumber x("100");
        x += LongNumber("50");
        x -= LongNumber("25");
        cout << "x = " << x << " (expected 125)\n";

        // Инкремент/декремент
        LongNumber y("3");
        cout << "y++ = " << y++ << "\n"; // 3
        cout << "y = " << y << "\n";     // 4
        cout << "++y = " << ++y << "\n"; // 5

        LongNumber z("2");
        cout << "--z = " << --z << "\n"; // 1
        cout << "z-- = " << z-- << "\n"; // 1
        cout << "z = " << z << "\n";     // 0

        // Сравнения
        assert(b > c);
        assert(c < b);
        assert(b == d);
        assert(b != c);
        assert(LongNumber("0") <= LongNumber("1"));
        assert(LongNumber("5") >= LongNumber("5"));

        // Доступ по индексу
        assert(b[0] == '1');
        assert(b[1] == '2');

        // Приведение типов
        unsigned long long c_ull = static_cast<unsigned long long>(c);
        cout << "c as ULL = " << c_ull << "\n";
        string b_str = static_cast<string>(b);
        assert(b_str == "12345678901234567890");

        // Арифметика с ULL слева и справа
        LongNumber r1 = 1000ULL + b;
        LongNumber r2 = b + 2000ULL;
        LongNumber r3 = 10ULL * b;
        LongNumber r4 = b / 10ULL;

        cout << "1000 + b = " << r1 << "\n";
        cout << "b + 2000 = " << r2 << "\n";
        cout << "10 * b = " << r3 << "\n";
        cout << "b / 10 = " << r4 << "\n";

        // Сравнения с ULL
        assert(b > 1000ULL);
        assert(500ULL < b);
        assert(c == 9876543210ULL);
        assert(b != 123ULL);

        // Исключения: некорректная строка
        try {
            LongNumber bad("12a3");
            assert(false && "Should not reach here");
        } catch (const invalid_argument&) {
            cout << "Caught invalid_argument as expected\n";
        }

        // Исключения: деление на ноль
        try {
            LongNumber zero("0");
            LongNumber test = b / zero;
            assert(false);
        } catch (const runtime_error&) {
            cout << "Caught division by zero as expected\n";
        }

        // Исключения: вычитание с отрицательным результатом
        try {
            LongNumber small("100");
            LongNumber big("200");
            LongNumber neg = small - big;
            assert(false);
        } catch (const runtime_error&) {
            cout << "Caught negative subtraction as expected\n";
        }

        // Исключения: декремент нуля
        try {
            LongNumber zero;
            --zero;
            assert(false);
        } catch (const runtime_error&) {
            cout << "Caught decrement of zero as expected\n";
        }

        // Переполнение при приведении
        try {
            LongNumber huge("18446744073709551616"); // 2^64
            unsigned long long v = static_cast<unsigned long long>(huge);
        } catch (const overflow_error&) {
            cout << "Caught overflow during conversion as expected\n";
        }

        cout << "\nAll Test passed!\n";

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}