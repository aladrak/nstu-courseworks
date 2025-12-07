// g++ -std=c++17 -o date_app main.cpp Date.cpp
#include "Date.h" 
#include <cassert>

int main() {
    try {
        // Конструкторы
        Date d1;              // по умолчанию
        Date d2(15, 8, 2025); // с параметрами
        Date d3(d2);          // копирования

        std::cout << "d1: " << d1 << "\n";
        std::cout << "d2: " << d2 << "\n";
        std::cout << "d3: " << d3 << "\n";

        // Присваивание
        d1 = d2;
        std::cout << "After assignment d1 = d2: " << d1 << "\n";

        // Арифметика
        Date d4 = d2 + 10;
        std::cout << "d2 + 10 days: " << d4 << "\n";

        d4 -= 5;
        std::cout << "After -=5: " << d4 << "\n";

        int diff = d2 - d4;
        std::cout << "d2 - d4 = " << diff << " days\n";

        // Инкремент/декремент
        Date d5 = d2;
        std::cout << "Pre-increment: " << ++d5 << "\n";
        std::cout << "Post-decrement: " << d5-- << "\n";
        std::cout << "After post-decrement: " << d5 << "\n";

        // Логические операторы
        std::cout << "d2 == d3: " << (d2 == d3 ? "true" : "false") << "\n";
        std::cout << "d2 < d4: " << (d2 < d4 ? "true" : "false") << "\n";

        // Оператор []
        std::cout << "d2[0] (day): " << d2[0] << "\n";
        std::cout << "d2[1] (month): " << d2[1] << "\n";
        std::cout << "d2[2] (year): " << d2[2] << "\n";

        // Преобразование к long long
        long long daysSinceEpoch = static_cast<long long>(d2);
        std::cout << "Days since epoch: " << daysSinceEpoch << "\n";

        // Проверка исключений
        try {
            Date invalid(32, 13, 2025);
        } catch (const std::exception& e) {
            std::cout << "Caught expected exception: " << e.what() << "\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}