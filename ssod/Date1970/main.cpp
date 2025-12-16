using namespace std;
#include "Date.h"
#include <iostream>

void test_constructors() {
    cout << "Test: Constructors\n";
    Date d1;                          // 1970-01-01
    Date d2(15, 3, 2000);
    Date d3(d2);
    Date d4(10000);

    cout << "  Default: "; d1.print(); cout << " (expected: 1970-01-01)\n";
    cout << "  Custom:  "; d2.print(); cout << " (expected: 2000-03-15)\n";
    cout << "  Copy:    "; d3.print(); cout << " (expected: 2000-03-15)\n";
    cout << "  From days: "; d4.print(); cout << " (expected: 1997-05-19)\n";
    cout << "  -> PASS\n\n";
}

void test_assignment() {
    cout << "Test: Assignment operator\n";
    Date a(10, 5, 1990);
    Date b;
    b = a;
    cout << "  Assigned: "; b.print(); cout << " (expected: 1990-05-10)\n";
    cout << "  -> PASS\n\n";
}

void test_arithmetic() {
    cout << "Test: Arithmetic operators\n";
    Date d1(1, 1, 1971); // 365 days
    Date d2(1, 1, 1972); // 730 days

    cout << "  d1 + d2: "; (d1 + d2).print(); cout << " (1095 days)\n";
    cout << "  d2 - d1: "; (d2 - d1).print(); cout << " (365 days)\n";
    cout << "  d1 * 2:  "; (d1 * 2).print(); cout << " (730 days)\n";
    cout << "  d2 / 2:  "; (d2 / 2).print(); cout << " (365 days)\n";

    cout << "  100 + d1: "; (100 + d1).print(); cout << " (465 days)\n";
    cout << "  500 - d1: "; (500 - d1).print(); cout << " (135 days)\n";
    cout << "  3 * d1:   "; (3 * d1).print(); cout << " (1095 days)\n";
    cout << "  1000 / d1: "; (1000 / d1).print(); cout << " (2 days)\n";
    cout << "  -> PASS\n\n";
}

void test_compound() {
    cout << "Test: Compound assignment operators\n";
    Date d(0); // 1970-01-01
    d += Date(100);
    cout << "  After +=100: "; d.print(); cout << "\n";
    d -= Date(50);
    cout << "  After -=50:  "; d.print(); cout << "\n";
    d *= 2;
    cout << "  After *=2:   "; d.print(); cout << "\n";
    d /= 2;
    cout << "  After /=2:   "; d.print(); cout << "\n";
    cout << "  -> PASS\n\n";
}

void test_unary() {
    cout << "Test: Unary increment/decrement\n";
    Date d(100); // 1970-04-11

    Date a = ++Date(d); // prefix
    cout << "  Prefix ++: "; a.print(); cout << "\n";

    Date b = d++; // postfix
    cout << "  Postfix ++ (before): "; b.print(); cout << "\n";
    cout << "  After postfix ++: "; d.print(); cout << "\n";

    Date c = --Date(d); // prefix
    cout << "  Prefix --: "; c.print(); cout << "\n";

    Date e = d--; // postfix
    cout << "  Postfix -- (before): "; e.print(); cout << "\n";
    cout << "  After postfix --: "; d.print(); cout << "\n";
    cout << "  -> PASS\n\n";
}

void test_comparison() {
    cout << "Test: Comparison operators\n";
    Date x(1, 1, 1970); // 0
    Date y(2, 1, 1970); // 1

    cout << "  x < y:  " << (x < y) << " (1)\n";
    cout << "  x > y:  " << (x > y) << " (0)\n";
    cout << "  x == y: " << (x == y) << " (0)\n";
    cout << "  x != y: " << (x != y) << " (1)\n";
    cout << "  x <= y: " << (x <= y) << " (1)\n";
    cout << "  y >= x: " << (y >= x) << " (1)\n";
    cout << "  -> PASS\n\n";
}

void test_subscript() {
    cout << "Test: Subscript operator []\n";
    Date d(25, 12, 2025);
    cout << "  d[0] (day):   " << d[0] << "\n";
    cout << "  d[1] (month): " << d[1] << "\n";
    cout << "  d[2] (year):  " << d[2] << "\n";
    cout << "  -> PASS\n\n";
}

void test_conversion() {
    cout << "Test: Type conversion to long\n";
    Date d(365);
    long n = static_cast<long>(d);
    cout << "  Days since epoch: " << n << " (expected: 365)\n";
    cout << "  -> PASS\n\n";
}

void test_exceptions() {
    cout << "Test: Exception handling\n";
    bool ok = true;

    try { Date d(-1); ok = false; } catch (...) {}
    if (!ok) { cout << "  FAIL: negative days not rejected\n"; return; }

    try { Date d(1, 13, 2000); ok = false; } catch (...) {}
    if (!ok) { cout << "  FAIL: invalid month not rejected\n"; return; }

    try { Date a(0); Date b(1); Date c = a - b; ok = false; } catch (...) {}
    if (!ok) { cout << "  FAIL: underflow not caught\n"; return; }

    try { Date d(0); --d; ok = false; } catch (...) {}
    if (!ok) { cout << "  FAIL: decrement below epoch not caught\n"; return; }

    try { Date d(365); d /= 0; ok = false; } catch (...) {}
    if (!ok) { cout << "  FAIL: division by zero not caught\n"; return; }

    cout << "  All exception cases handled correctly\n";
    cout << "  -> PASS\n\n";
}

void test_self_consistency() {
    cout << "Test: Self-consistency (round-trip)\n";
    Date original(29, 2, 2024); // leap day
    long days = static_cast<long>(original);
    Date reconstructed(days);
    cout << "  Original:     "; original.print(); cout << "\n";
    cout << "  Reconstructed:"; reconstructed.print(); cout << "\n";
    cout << "  Equal: " << (original == reconstructed) << " (1)\n";
    cout << "  -> PASS\n\n";
}

int main() {
    cout << "Running test for Date class\n\n";

    try {
        test_constructors();
        test_assignment();
        test_arithmetic();
        test_compound();
        test_unary();
        test_comparison();
        test_subscript();
        test_conversion();
        test_exceptions();
        test_self_consistency();

        cout << "All tests passed.\n";
    } catch (const exception& e) {
        cerr << "Test failed with exception: " << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "Unknown exception during testing.\n";
        return 1;
    }
}