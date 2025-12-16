using namespace std;
#include "SparseMatrix.h"
#include <iostream>
#include <cassert>

int main() {
    try {
        // Test 1: конструкторы
        SparseMatrix A(3, 3);
        A.setValue(0, 0, 5.0);
        A.setValue(1, 2, -3.0);

        cout << "Matrix A:\n";
        A.print();

        // Test 2: копирование
        SparseMatrix B = A;
        cout << "\nMatrix B (copy of A):\n";
        B.print();

        // Test 3: присваивание
        SparseMatrix C(3, 3);
        C = A;
        cout << "\nMatrix C (assigned from A):\n";
        C.print();

        // Test 4: доступ
        cout << "\nA(0,0) = " << A(0,0) << "\n";
        cout << "A(2,2) = " << A(2,2) << "\n";

        // Test 5: сложение
        SparseMatrix D(3, 3);
        D.setValue(0, 0, 2.0);
        D.setValue(2, 1, 4.0);
        SparseMatrix E = A + D;
        cout << "\nA + D =\n";
        E.print();

        // Test 6: умножение на скаляр и матрицу
        SparseMatrix F = A * 2.0;
        cout << "\nA * 2 =\n";
        F.print();

        SparseMatrix Am(2, 3);
        Am.setValue(0, 0, 1.0);
        Am.setValue(0, 2, 2.0);
        Am.setValue(1, 1, 3.0);

        SparseMatrix Bm(3, 2);
        Bm.setValue(0, 0, 4.0);
        Bm.setValue(1, 1, 5.0);
        Bm.setValue(2, 0, 6.0);

        if (Am.can_multiply(Bm)) {
            SparseMatrix Cm = Am * Bm;
            cout << "\nA * B =\n";
            Cm.print(); // Ожидаем: [16, 0] и [0, 15]
        }

        // Test 7: скаляр слева
        SparseMatrix G = 0.5 * A;
        cout << "\n0.5 * A =\n";
        G.print();

        // Test 8: унарные ++
        SparseMatrix H = A;
        ++H;
        cout << "\n++A_copy =\n";
        H.print();

        // Test 9: логические
        cout << "\nA == B? " << (A == B ? "yes" : "no") << "\n";
        cout << "A < D? " << (A < D ? "yes" : "no") << "\n";

        // Test 10: преобразование к double
        double s = static_cast<double>(A);
        cout << "\nSum of A = " << s << "\n";

        // Test 11: исключения
        try {
        SparseMatrix bad(0, 5);
        } catch (const exception& e) {
            cout << "Caught expected error: " << e.what() << "\n";
        }
        try {
        A.setValue(10, 10, 1.0);
        } catch (const exception& e) {
            cout << "Caught expected error: " << e.what() << "\n";
        }

    } catch (const exception& e) {
        cerr << "Exception: " << e.what() << "\n";
        return 1;
    }

    return 0;
}