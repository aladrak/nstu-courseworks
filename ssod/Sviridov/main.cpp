using namespace std;
#include "Fraction.h"
#include <iostream>
#include <sstream>

void testConstructorsAndAssignment() {
    cout << "Testing constructors and assignment...\n";

    Fraction f1;
    cout << "Default: " << f1 << " (expected 0/1)\n";

    Fraction f2(3, 4);
    cout << "3/4: " << f2 << "\n";

    Fraction f3(-6, -9);
    cout << "-6/-9 normalized: " << f3 << " (expected 2/3)\n";

    Fraction f4(8, -12);
    cout << "8/-12 normalized: " << f4 << " (expected -2/3)\n";

    Fraction f5(f2);
    cout << "Copy of 3/4: " << f5 << "\n";
    f5 = f3;
    cout << "After assignment (f5 = f3): " << f5 << "\n";
    f5 = 7;
    cout << "After f5 = 7: " << f5 << " (expected 7/1)\n";
    cout << "Constructors and assignment test completed.\n\n";
}

void testArithmeticOperators() {
    cout << "Testing arithmetic operators...\n";

    Fraction a(1, 2);
    Fraction b(1, 3);
    
    cout << "1/2 + 1/3 = " << a + b << " (expected 5/6)\n";
    cout << "1/2 - 1/3 = " << a - b << " (expected 1/6)\n";
    cout << "1/2 * 1/3 = " << a * b << " (expected 1/6)\n";
    cout << "1/2 / 1/3 = " << a / b << " (expected 3/2)\n";
    cout << "1/2 + 3 = " << a + 3 << " (expected 7/2)\n";
    cout << "5 - 1/3 = " << 5 - b << " (expected 14/3)\n";
    cout << "4 * 2/3 = " << 4 * Fraction(2, 3) << " (expected 8/3)\n";
    cout << "3 / (3/4) = " << 3 / Fraction(3, 4) << " (expected 4/1)\n";

    Fraction c(1, 4);
    c += Fraction(1, 4);
    cout << "1/4 += 1/4 -> " << c << " (expected 1/2)\n";
    c *= 3;
    cout << "1/2 *= 3 -> " << c << " (expected 3/2)\n";
    c -= 1;
    cout << "3/2 -= 1 -> " << c << " (expected 1/2)\n";
    c /= 2;
    cout << "1/2 /= 2 -> " << c << " (expected 1/4)\n";
    cout << "Arithmetic operators test completed.\n\n";
}

void testUnaryOperators() {
    cout << "Testing unary operators (++, --)...\n";

    Fraction f(3, 2);
    Fraction f_post = f++;
    cout << "Postfix ++: f was " << f_post << ", now f = " << f << "\n";
    Fraction f_pre = ++f;
    cout << "Prefix ++: f = " << f_pre << "\n";
    Fraction g(5, 3);
    Fraction g_post = g--;
    cout << "Postfix --: g was " << g_post << ", now g = " << g << "\n";
    Fraction g_pre = --g;
    cout << "Prefix --: g = " << g_pre << "\n";
    cout << "Unary operators test completed.\n\n";
}

void testComparisonOperators() {
    cout << "Testing comparison operators...\n";

    Fraction x(1, 2);
    Fraction y(2, 4);
    Fraction z(3, 5);

    cout << "1/2 == 2/4 -> " << (x == y ? "true" : "false") << "\n";
    cout << "1/2 != 3/5 -> " << (x != z ? "true" : "false") << "\n";
    cout << "1/2 < 3/5 -> " << (x < z ? "true" : "false") << " (0.5 < 0.6)\n";
    cout << "1/2 > 3/5 -> " << (x > z ? "true" : "false") << "\n";
    cout << "1/2 <= 2/4 -> " << (x <= y ? "true" : "false") << "\n";
    cout << "3/5 >= 1/2 -> " << (z >= x ? "true" : "false") << "\n";
    cout << "Comparison operators test completed.\n\n";
}

void testAccessAndConversions() {
    cout << "Testing [] operator and type conversions...\n";
    Fraction f(7, -3);  
    cout << "f[0] (numerator) = " << f[0] << "\n";
    cout << "f[1] (denominator) = " << f[1] << "\n";
    float fl = static_cast<float>(f);
    cout << "As float: " << fl << "\n";
    long long ll = static_cast<long long>(f);
    cout << "As long long (truncated): " << ll << " (expected -2)\n";
    cout << "Access and conversions test completed.\n\n";
}

void testExceptions() {
    cout << "Testing exception handling...\n";
    
    try {
        Fraction bad(5, 0);
        cout << "ERROR: Exception not thrown for zero denominator!\n";
    } catch (const invalid_argument& e) {
        cout << "Caught exception for Fraction(5, 0): " << e.what() << "\n";
    }
    
    try {
        Fraction a(1, 2);
        Fraction b(0, 1);
        Fraction result = a / b;
        cout << "ERROR: Exception not thrown for division by zero!\n";
    } catch (const invalid_argument& e) {
        cout << "Caught exception for division by zero: " << e.what() << "\n";
    }


    try {
        Fraction f(2, 3);
        long long val = f[5];  
        cout << "ERROR: Exception not thrown for invalid index!\n";
    } catch (const out_of_range& e) {
        cout << "Caught exception for invalid index: " << e.what() << "\n";
    }

    cout << "Exception handling test completed.\n\n";
}

void testOutput() {
    cout << "Testing output (operator<<)...\n";

    stringstream ss;
    ss << Fraction(-4, 6);
    cout << "Stringstream output of -4/6: \"" << ss.str() << "\" (expected \"-2/3\")\n";
    cout << "Direct cout: ";
    cout << Fraction(10, -15) << " (expected -2/3)\n";
    cout << "Output test completed.\n\n";
}

int main() {
    cout << "=== Test Fraction Class ===\n\n";

    testConstructorsAndAssignment();
    testArithmeticOperators();
    testUnaryOperators();
    testComparisonOperators();
    testAccessAndConversions();
    testExceptions();
    testOutput();

    cout << "=== All tests finished. ===\n";
}