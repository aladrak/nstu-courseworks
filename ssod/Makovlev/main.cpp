#include <cassert>
#include <cstring>
#include <iostream>

#include "String.hpp"

int main(){
  std::cout << "1. Default constructor: ";
  String s1;
  s1.print();
  std::cout << " (len=" << s1.length() << ")\n";
  assert(s1.length() == 0);

  std::cout << "2. From C-string: ";
  String s2 = "Hello";
  s2.print();
  std::cout << "\n";
  assert(s2.length() == 5);

  std::cout << "2b. From nullptr: ";
  String s3 = String(nullptr);
  s3.print();
  std::cout << "\n";
  assert(s3.length() == 0);

  std::cout << "3. Repeated char: ";
  String s4(5, 'X');
  s4.print();
  std::cout << "\n";
  assert(s4.length() == 5);

  std::cout << "4. Copy constructor: ";
  String s4_copy = s4;
  s4_copy.print();
  std::cout << " (len=" << s4_copy.length() << ")\n";
  assert(s4_copy.length() == 5);

  std::cout << "5. Destructor: OK\n";

  std::cout << "6. Assignment operator: ";
  String s5;
  s5 = s2;
  s5.print();
  std::cout << "\n";
  assert(s5.length() == 5);

  std::cout << "7. Print method: ";
  s5.print();
  std::cout << "\n";

  std::cout << "8. Operator +=: ";
  String s6 = "World";
  s5 += " ";
  s5 += s6;
  s5.print();
  std::cout << "\n";
  assert(s5.length() == 11);

  std::cout << "9. Operator -=: ";
  s5 -= "World";
  s5.print();
  std::cout << "\n";
  assert(s5.length() == 6);

  std::cout << "10. Operator [] (non-const): ";
  s5[0] = 'J';
  s5.print();
  std::cout << "\n";
  assert(s5[0] == 'J');

  std::cout << "11. Operator [] (const): ";
  const String s10 = "Test";
  std::cout << s10[1];
  std::cout << "\n";
  assert(s10[1] == 'e');

  std::cout << "12. Conversion to const char*: ";
  const char *c_str = static_cast<const char *>(s5);
  std::cout << c_str << "\n";
  assert(std::strcmp(c_str, "Jello ") == 0);

  std::cout << "13. Conversion to int: ";
  int len = static_cast<int>(s5);
  std::cout << len << "\n";
  assert(len == 6);

  std::cout << "14. Conversion to bool: ";
  bool is_empty = static_cast<bool>(s1);
  bool is_not_empty = static_cast<bool>(s5);
  std::cout << "Empty: " << is_empty << ", Not empty: " << is_not_empty << "\n";
  assert(!is_empty && is_not_empty);

  std::cout << "15. Length method: ";
  std::cout << s5.length() << "\n";
  assert(s5.length() == 6);

  std::cout << "16. C_str method: ";
  std::cout << s5.c_str() << "\n";
  assert(std::strcmp(s5.c_str(), "Jello ") == 0);

  std::cout << "17. Operator <<: ";
  std::cout << s5 << "\n";

  std::cout << "18. Binary operator +: ";
  String s11 = s2 + " " + s6 + "!";
  std::cout << s11 << "\n";
  assert(s11.length() == 12);

  std::cout << "19. Binary operator -: ";
  String s12 = "abcXXXdef";
  String s13 = s12 - "XXX";
  std::cout << s13 << "\n";
  assert(s13.length() == 6);

  std::cout << "20. Operator * (String * int): ";
  String s14 = s2 * 3;
  std::cout << s14 << "\n";
  assert(s14.length() == 15);

  std::cout << "21. Operator * (int * String): ";
  String s15 = 2 * s6;
  std::cout << s15 << "\n";
  assert(s15.length() == 10);

  std::cout << "22. Logical operator ==: ";
  bool eq1 = (s2 == "Hello");
  bool eq2 = (s5 == String("Jello "));
  std::cout << "s2 == \"Hello\": " << eq1 << ", s5 == \"Jello \": " << eq2 << "\n";
  assert(eq1 && eq2);

  std::cout << "23. Logical operator !=: ";
  bool ne1 = (s2 != "World");
  bool ne2 = (s5 != s2);
  std::cout << "s2 != \"World\": " << ne1 << ", s5 != s2: " << ne2 << "\n";
  assert(ne1 && ne2);

  std::cout << "24. Logical operator <: ";
  bool lt1 = (s2 < "HelloWorld");
  bool lt2 = ("Apple" < s2);
  std::cout << "\"Hello\" < \"HelloWorld\": " << lt1 << ", \"Apple\" < \"Hello\": " << lt2 << "\n";
  assert(lt1 && lt2);

  std::cout << "25. Logical operator >: ";
  bool gt1 = (s6 > "World!");
  bool gt2 = ("Zebra" > s2);
  std::cout << "\"World\" > \"World!\": " << gt1 << ", \"Zebra\" > \"Hello\": " << gt2 << "\n";
  assert(!gt1 && gt2);

  return 0;
}
