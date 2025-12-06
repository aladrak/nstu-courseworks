using namespace std;
#include "LongNumber.h"
#include <cassert>

int main() {
    try {
        // Конструкторы
        LongNumber a;                     // "0"
        LongNumber b("12345678901234567890");
        LongNumber c(9876543210ULL);
        LongNumber d(b);                  // копия

        cout << "a = " << a << "\n";
        cout << "b = " << b << "\n";
        cout << "c = " << c << "\n";
        cout << "d = " << d << "\n";

        // Присваивание
        a = "99999999999999999999";
        cout << "a after assign string: " << a << "\n";
        a = 123ULL;
        cout << "a after assign ull: " << a << "\n";

        // Арифметика
        LongNumber sum = b + c;
        LongNumber diff = b - c;
        LongNumber prod = b * c;
        LongNumber quot = b / c;

        cout << "b + c = " << sum << "\n";
        cout << "b - c = " << diff << "\n";
        cout << "b * c = " << prod << "\n";
        cout << "b / c = " << quot << "\n";

        // Арифметика с накоплением
        LongNumber x("100");
        x += LongNumber("50");
        x -= LongNumber("25");
        cout << "x = " << x << "\n"; // 125

        // Унарные операторы
        LongNumber y("5");
        cout << "y++ = " << y++ << "\n"; // 5
        cout << "y = " << y << "\n";     // 6
        cout << "++y = " << ++y << "\n"; // 7

        LongNumber z("3");
        cout << "--z = " << --z << "\n"; // 2
        cout << "z-- = " << z-- << "\n"; // 2
        cout << "z = " << z << "\n";     // 1

        // Сравнения
        assert(b > c);
        assert(c < b);
        assert(b != c);
        assert(b == d);
        assert(LongNumber("0") <= LongNumber("1"));

        // Доступ по индексу
        cout << "b[0] = " << b[0] << "\n"; // '1'

        // Преобразования
        unsigned long long conv = static_cast<unsigned long long>(c);
        cout << "c as ull = " << conv << "\n";

        string str = static_cast<string>(b);
        cout << "b as string = " << str << "\n";

        // Арифметика с базовым типом
        LongNumber r = 1000ULL + b;
        LongNumber s = b + 2000ULL;
        LongNumber t = 100ULL * b;
        LongNumber u = b / 10ULL;

        cout << "1000 + b = " << r << "\n";
        cout << "b + 2000 = " << s << "\n";
        cout << "100 * b = " << t << "\n";
        cout << "b / 10 = " << u << "\n";

        // Исключения
        try {
            LongNumber bad("12a3");
        } catch (const exception& e) {
            cout << "Caught expected error: " << e.what() << "\n";
        }

        try {
            LongNumber zero("0");
            --zero;
        } catch (const exception& e) {
            cout << "Caught expected error: " << e.what() << "\n";
        }

    } catch (const exception& ex) {
        cerr << "Error: " << ex.what() << "\n";
        return 1;
    }

    cout << "All tests passed.\n";
    return 0;
}