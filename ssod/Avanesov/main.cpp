// g++ main.cpp -o Matrix.exe
using namespace std;
#include "Matrix.h"
#include <cassert>

int main() {
    try {
        cout << " Constuctors:\n";
        Matrix A(2, 3, 1.0);
        Matrix B(3, 2, 2.0);
        Matrix C; // пустая

        cout << "A (2x3):\n";
        A.print();

        cout << "B (3x2):\n";
        B.print();

        cout << " Matrics mult A * B\n";
        Matrix D = A * B;
        D.print();

        cout << " Sum and sub\n";
        Matrix E(2, 2, 3.0);
        Matrix F(2, 2, 1.0);
        Matrix G = E + F;
        Matrix H = E - F;
        cout << "E + F:\n"; G.print();
        cout << "E - F:\n"; H.print();

        cout << " Scalars:\n";
        Matrix I = G * 2.5;
        Matrix J = 0.4 * G;
        Matrix K = G / 2.0;
        cout << "G * 2.5:\n"; I.print();
        cout << "0.4 * G:\n"; J.print();
        cout << "G / 2.0:\n"; K.print();

        cout << " Operators with =\n";
        Matrix L = E;
        L += F;
        cout << "L = E; L += F -> L:\n"; L.print();

        L *= 0.5;
        cout << "L *= 0.5:\n"; L.print();

        cout << " Access to elem:\n";
        L(0, 0) = 99.9;
        cout << "L(0,0) = 99.9:\n"; L.print();

        cout << " Unary ops:\n";
        Matrix M(2, 2, 1.0);
        cout << "M before ++M:\n"; M.print();
        ++M;
        cout << "After ++M:\n"; M.print();

        Matrix N = M++;
        cout << "M after M++:\n"; M.print();
        cout << "N (old M):\n"; N.print();

        --M;
        cout << "After --M:\n"; M.print();

        cout << " Cheks:\n";
        assert(N == M);
        assert(N != (M + Matrix(2, 2, 1.0)));
        cout << "N == M + 1? true\n";
        cout << "N != M? true\n";

        cout << " Converting: \n";
        double sum = static_cast<double>(N);
        bool nonzero = static_cast<bool>(N);
        cout << "Sum of N: " << sum << "\n";
        cout << "N is non-zero? " << (nonzero ? "true" : "false") << "\n";

        cout << " Copy and =\n";
        Matrix P = D;        // копирование
        Matrix Q;
        Q = D;               // присваивание
        assert(P == Q);
        assert(P == D);
        cout << "Copy and assignment work correctly.\n";

        cout << " Exceptions:\n";
        try {
            Matrix X(2, 3);
            Matrix Y(4, 2);
            Matrix Z = X * Y;
        } catch (const exception& e) {
            cout << "Caught expected exception: " << e.what() << "\n";
        }

        try {
            Matrix bad(0, 5);
        } catch (const exception& e) {
            cout << "Caught expected exception: " << e.what() << "\n";
        }

        cout << "\nAll tests passed.\n";

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << '\n';
        return 1;
    }
}