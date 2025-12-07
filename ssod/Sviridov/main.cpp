// Разработка класса структуры данных: точные числа (дробь).
// g++ -o main.exe main.cpp Fraction.cpp
#include "Fraction.h"
#include <iomanip>

int main() {
    try {
        // Конструкторы
        Fraction f1;        // 0/1
        Fraction f2(5);     // 5/1
        Fraction f3(3, 4);  // 3/4
        Fraction f4(f3);    // копия

        cout << "f1 = " << f1 << "\n";
        cout << "f2 = " << f2 << "\n";
        cout << "f3 = " << f3 << "\n";
        cout << "f4 = " << f4 << "\n\n";

        // Присваивание
        f1 = f2;
        f2 = 10;
        cout << "After assignment: f1 = " << f1 << ", f2 = " << f2 << "\n\n";

        // Арифметика Fraction-Fraction
        Fraction sum = f3 + f4;
        Fraction diff = f3 - f4;
        Fraction prod = f3 * f4;
        Fraction quot = f3 / f4;
        cout << "f3 + f4 = " << sum << "\n";
        cout << "f3 - f4 = " << diff << "\n";
        cout << "f3 * f4 = " << prod << "\n";
        cout << "f3 / f4 = " << quot << "\n\n";

        // Арифметика с базовым типом
        Fraction a = f3 + 2;
        Fraction b = 2 + f3;
        Fraction c = f3 * 3LL;
        Fraction d = 5LL / f3;
        cout << "f3 + 2 = " << a << "\n";
        cout << "2 + f3 = " << b << "\n";
        cout << "f3 * 3 = " << c << "\n";
        cout << "5 / f3 = " << d << "\n\n";

        // Арифметика с накоплением
        Fraction x(1, 2);
        x += Fraction(1, 3);
        x *= 6;
        cout << "x after += and *=: " << x << "\n\n";

        // Унарные операторы
        Fraction y(3, 2);
        cout << "y = " << y << "\n";
        cout << "++y = " << ++y << "\n";
        cout << "y++ = " << y++ << "\n";
        cout << "y after post++ = " << y << "\n";
        cout << "--y = " << --y << "\n\n";

        // Логические операторы
        Fraction p(1, 2), q(2, 3);
        cout << "p == q: " << (p == q) << "\n";
        cout << "p != q: " << (p != q) << "\n";
        cout << "p < q: " << (p < q) << "\n";
        cout << "p > q: " << (p > q) << "\n\n";

        // Преобразования типов
        double dval = static_cast<double>(f3);
        int ival = static_cast<int>(Fraction(7, 3));
        cout << "double(f3) = " << fixed << setprecision(3) << dval << "\n";
        cout << "int(7/3) = " << ival << "\n\n";

        // Проверка исключений
        try {
            Fraction bad(1, 0);
        } catch (const exception& e) {
            cout << "Caught exception: " << e.what() << "\n";
        }

        try {
            Fraction zero(0, 1);
            Fraction one(1, 1);
            Fraction inv = one / zero;
        } catch (const exception& e) {
            cout << "Caught division exception: " << e.what() << "\n";
        }
    } catch (const exception& e) {
        cerr << "Unexpected error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}