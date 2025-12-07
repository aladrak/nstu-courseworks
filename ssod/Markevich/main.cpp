// g++ -o date_app main.cpp Date.cpp
#include "Date.h"

int main() {
    try {
        // Конструкторы
        Date d1;              // по умолчанию
        Date d2(15, 8, 2025); // с параметрами
        Date d3(d2);          // копирования

        cout << "d1: " << d1 << "\n";
        cout << "d2: " << d2 << "\n";
        cout << "d3: " << d3 << "\n";

        // Присваивание
        d1 = d2;
        cout << "After assignment d1 = d2: " << d1 << "\n";

        // Арифметика
        Date d4 = d2 + 10;
        cout << "d2 + 10 days: " << d4 << "\n";

        d4 -= 5;
        cout << "After -=5: " << d4 << "\n";

        int diff = d2 - d4;
        cout << "d2 - d4 = " << diff << " days\n";

        // Инкремент/декремент
        Date d5 = d2;
        cout << "Pre-increment: " << ++d5 << "\n";
        cout << "Post-decrement: " << d5-- << "\n";
        cout << "After post-decrement: " << d5 << "\n";

        // Логические операторы
        cout << "d2 == d3: " << (d2 == d3 ? "true" : "false") << "\n";
        cout << "d2 < d4: " << (d2 < d4 ? "true" : "false") << "\n";

        // Оператор []
        cout << "d2[0] (day): " << d2[0] << "\n";
        cout << "d2[1] (month): " << d2[1] << "\n";
        cout << "d2[2] (year): " << d2[2] << "\n";

        // Преобразование к string
        cout << "String Date: " << static_cast<string>(d2) << "\n";

        // Проверка исключений
        try {
            Date invalid(32, 13, 2025);
        } catch (const exception& e) {
            cout << "Caught expected exception: " << e.what() << "\n";
        }

    } catch (const exception& e) {
        cerr << "Unexpected error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}