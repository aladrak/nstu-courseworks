using namespace std;
#include "ListMatrix.h"
#include <iostream>
#include <ctime>

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    try {
        cout << " Test 1: Constructors \n";
        ListMatrix A; // по умолчанию
        ListMatrix B(2, 3); // параметрический
        B.setValue(0, 0, 2.0);
        B.setValue(1, 2, -1.5);

        ListMatrix C(B); // копирования
        cout << "Matrix B:\n" << B << "\n";

        cout << " Test 2: Assignment \n";
        A = B;
        cout << "A = B:\n" << A << "\n";

        cout << " Test 3: access and setValue \n";
        cout << "B(0,0) = " << B(0, 0) << "\n";
        cout << "B(1,1) = " << B(1, 1) << "\n";
        B.setValue(0, 1, 3.0);
        cout << "after setValue(0,1,3.0):\n" << B << "\n";

        cout << " Test 4: Cheaks \n";
        ListMatrix D(3, 2);
        D.setValue(0, 0, 1.0);
        D.setValue(1, 1, 2.0);
        cout << "B can_multiply D? " << (B.can_multiply(D) ? "yes" : "no") << "\n";
        cout << "B equal_size C? " << (B.equal_size(C) ? "yes" : "no") << "\n";

        cout << " Test 5: Matrix multiplication \n";
        ListMatrix E = B * D;
        cout << "B * D =\n" << E << "\n";

        cout << " Test 6: Addition and subtraction of matrices \n";
        ListMatrix F(2, 3);
        F.setValue(0, 0, 1.0);
        F.setValue(0, 1, -3.0);
        ListMatrix G = B + F;
        ListMatrix H = B - F;
        cout << "B + F =\n" << G << "\n";
        cout << "B - F =\n" << H << "\n";

        cout << " Test 7: Arithmetic with scalar\n";
        ListMatrix I = B * 2.0;
        ListMatrix J = 0.5 * B;
        ListMatrix K = B + 10.0;
        ListMatrix L = 5.0 - B;
        cout << "B * 2 =\n" << I << "\n";
        cout << "0.5 * B =\n" << J << "\n";
        cout << "B + 10 =\n" << K << "\n";
        cout << "5 - B =\n" << L << "\n";

        cout << " Test 8: Accumulative arithmetic \n";
        ListMatrix M = B;
        M += F;
        cout << "M (B += F) =\n" << M << "\n";
        M -= 2.0;
        cout << "M -= 2.0:\n" << M << "\n";

        cout << " Test 9: Unary ops \n";
        ListMatrix N = B;
        ListMatrix N_post = N++;
        ListMatrix N_pre = ++N;
        cout << "N_post (before ++):\n" << N_post << "\n";
        cout << "N_pre (after ++):\n" << N_pre << "\n";

        ListMatrix O = B;
        --O;
        cout << "O after --:\n" << O << "\n";

        cout << " Test 10: logic ops \n";
        cout << "B == C? " << (B == C ? "yes" : "no") << "\n";
        cout << "B != F? " << (B != F ? "yes" : "no") << "\n";
        cout << "B < F? " << (B < F ? "yes" : "no") << "\n";
        cout << "B > F? " << (B > F ? "yes" : "no") << "\n";

        cout << " Test 11: to double \n";
        double sumB = static_cast<double>(B);
        cout << "sum B = " << sumB << "\n";

        cout << " Test 12: (operator<<) \n";
        cout << "cout << B:\n" << B << "\n";

        cout << "All Tests passed! \n";

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}