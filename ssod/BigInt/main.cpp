#include "BigInt.h"
#include <iostream>
#include <cassert>

void test_constructors() {
    std::cout << "\n=== Testing Constructors ===" << std::endl;
    BigInt a;                    // default
    BigInt b(123);               // from long long
    BigInt c(-456);              // negative
    BigInt d(b);                 // copy
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;
    std::cout << "d = " << d << std::endl;
}

void test_assignment() {
    std::cout << "\n=== Testing Assignment ===" << std::endl;
    BigInt a(100);
    BigInt b;
    b = a;
    std::cout << "b after b = a: " << b << std::endl;
    b = 200;
    std::cout << "b after b = 200: " << b << std::endl;
}

void test_arithmetic() {
    std::cout << "\n=== Testing Arithmetic ===" << std::endl;
    BigInt a(100), b(25);
    std::cout << "a + b = " << (a + b) << std::endl;
    std::cout << "a - b = " << (a - b) << std::endl;
    std::cout << "a * b = " << (a * b) << std::endl;
    std::cout << "a / b = " << (a / b) << std::endl;

    std::cout << "50 + a = " << (50 + a) << std::endl;
    std::cout << "a + 50 = " << (a + 50) << std::endl;
    std::cout << "a - 50 = " << (a - 50) << std::endl;
    std::cout << "a * 3 = " << (a * 3) << std::endl;
    std::cout << "a / 2 = " << (a / 2) << std::endl;
}

void test_compound_assignment() {
    std::cout << "\n=== Testing +=, -= ===" << std::endl;
    BigInt a(10);
    a += BigInt(5);
    std::cout << "a after += 5: " << a << std::endl;
}

void test_unary() {
    std::cout << "\n=== Testing Unary ++/-- ===" << std::endl;
    BigInt a(5);
    std::cout << "++a = " << ++a << std::endl;  // 6
    std::cout << "a++ = " << a++ << std::endl;  // 6, then 7
    std::cout << "a now = " << a << std::endl;  // 7
    std::cout << "--a = " << --a << std::endl;  // 6
    std::cout << "a-- = " << a-- << std::endl;  // 6, then 5
    std::cout << "a now = " << a << std::endl;  // 5

    BigInt b(-3);
    std::cout << "-b = " << (-b) << std::endl;  // 3
}

void test_comparison() {
    std::cout << "\n=== Testing Comparisons ===" << std::endl;
    BigInt a(10), b(20), c(-5);
    assert(a < b);
    assert(b > a);
    assert(a == BigInt(10));
    assert(c < a);
    assert(!(a != BigInt(10)));
    std::cout << "All comparisons passed." << std::endl;
}

void test_indexing() {
    std::cout << "\n=== Testing Indexing ===" << std::endl;
    BigInt a(0x12345678LL);
    std::cout << "a[0] = " << static_cast<int>(a[0]) << std::endl;
    std::cout << "a[3] = " << static_cast<int>(a[3]) << std::endl;
    try {
        unsigned char x = a[10]; // должно выбросить исключение
    } catch (const std::out_of_range& e) {
        std::cout << "Indexing exception caught: " << e.what() << std::endl;
    }
}

void test_conversion() {
    std::cout << "\n=== Testing Type Conversion ===" << std::endl;
    BigInt a(12345);
    long long x = static_cast<long long>(a);
    assert(x == 12345);
    std::cout << "Converted to long long: " << x << std::endl;

    BigInt b(-65536);
    x = static_cast<long long>(b);
    assert(x == -65536);
    std::cout << "Negative conversion: " << x << std::endl;
}

void test_io() {
    std::cout << "\n=== Testing I/O ===" << std::endl;
    BigInt a(0xA1B2C3);
    std::cout << "a (hex bytes) = " << a << std::endl;
}

void test_division_by_zero() {
    std::cout << "\n=== Testing Division by Zero ===" << std::endl;
    BigInt a(10), b(0);
    try {
        BigInt c = a / b;
    } catch (const std::runtime_error& e) {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "=== Full Test Suite for BigInt Class ===" << std::endl;

    test_constructors();
    test_assignment();
    test_arithmetic();
    test_compound_assignment();
    test_unary();
    test_comparison();
    test_indexing();
    test_conversion();
    test_io();
    test_division_by_zero();

    std::cout << "\nAll tests completed successfully!" << std::endl;
}