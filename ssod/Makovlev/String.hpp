#include <cstddef>
#include <iostream>

class String{
private:
  char *str;
  size_t len;

  void copyFrom(const char *s);

public:
  String() noexcept;

  String(const char *s);

  String(size_t count, char ch);

  String(const String &other);

  ~String() noexcept;

  String &operator=(String other) noexcept;

  friend void swap(String &lhs, String &rhs) noexcept;

  void print() const noexcept;

  String &operator+=(const String &other);

  String &operator+=(const char *other);

  String &operator-=(const String &other);

  String &operator-=(const char *other);

  char &operator[](size_t index);

  const char &operator[](size_t index) const;

  explicit operator const char *() const noexcept;

  explicit operator int() const noexcept;

  explicit operator bool() const noexcept;

  size_t length() const noexcept;

  const char *c_str() const noexcept;

  friend std::ostream &operator<<(std::ostream &os, const String &s);
};

String operator+(String lhs, const String &rhs);

String operator+(String lhs, const char *rhs);

String operator+(const char *lhs, const String &rhs);

String operator+(String lhs, char rhs);

String operator+(char lhs, const String &rhs);

String operator-(const String &lhs, const String &rhs);

String operator-(const String &lhs, const char *rhs);

String operator*(const String &lhs, int multiplier);

String operator*(int multiplier, const String &rhs);

bool operator==(const String &lhs, const String &rhs) noexcept;

bool operator!=(const String &lhs, const String &rhs) noexcept;

bool operator<(const String &lhs, const String &rhs) noexcept;

bool operator>(const String &lhs, const String &rhs) noexcept;

bool operator==(const String &lhs, const char *rhs) noexcept;

bool operator==(const char *lhs, const String &rhs) noexcept;

bool operator!=(const String &lhs, const char *rhs) noexcept;

bool operator!=(const char *lhs, const String &rhs) noexcept;

bool operator<(const String &lhs, const char *rhs) noexcept;

bool operator<(const char *lhs, const String &rhs) noexcept;

bool operator>(const String &lhs, const char *rhs) noexcept;

bool operator>(const char *lhs, const String &rhs) noexcept;