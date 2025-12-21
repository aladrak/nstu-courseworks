#include "String.hpp"

#include <algorithm>
#include <cstring>
#include <limits>
#include <utility>

void String::copyFrom(const char *s){
  if (s == nullptr)
  {
    len = 0;
    str = new char[1];
    str[0] = '\0';
    return;
  }
  len = std::strlen(s);
  str = new char[len + 1];
  std::strcpy(str, s);
}

String::String() noexcept{
  len = 0;
  str = new char[1];
  str[0] = '\0';
}

String::String(const char *s){
  copyFrom(s);
}

String::String(size_t count, char ch){
  if (count > std::numeric_limits<size_t>::max() / sizeof(char))
  {
    throw std::invalid_argument("Count too large");
  }
  len = count;
  str = new char[len + 1];
  for (size_t i = 0; i < len; ++i)
  {
    str[i] = ch;
  }
  str[len] = '\0';
}

String::String(const String &other) : str(new char[other.len + 1]), len(other.len){
  std::strcpy(str, other.str);
}

String::~String() noexcept{
  delete[] str;
}

void swap(String &lhs, String &rhs) noexcept{
  std::swap(lhs.str, rhs.str);
  std::swap(lhs.len, rhs.len);
}

String &String::operator=(String other) noexcept{
  swap(*this, other);
  return *this;
}

void String::print() const noexcept{
  std::cout << str;
}

String &String::operator+=(const String &other){
  if (other.len == 0)  {
    return *this;
  }
  if (other.len > std::numeric_limits<size_t>::max() - len)  {
    throw std::overflow_error("Resulting string too large");
  }
  char *new_str = new char[len + other.len + 1];
  std::strcpy(new_str, str);
  std::strcat(new_str, other.str);
  delete[] str;
  str = new_str;
  len += other.len;
  return *this;
}

String &String::operator+=(const char *other){
  return *this += String(other);
}

String &String::operator-=(const String &other){
  if (other.len == 0 || other.len > len) return *this;
  char *pos = std::strstr(str, other.str);
  if (pos)  {
    size_t offset = pos - str;
    size_t new_len = len - other.len;
    char *new_str = new char[new_len + 1];
    std::strncpy(new_str, str, offset);
    std::strcpy(new_str + offset, pos + other.len);
    delete[] str;
    str = new_str;
    len = new_len;
  }
  return *this;
}

String &String::operator-=(const char *other){
  return *this -= String(other);
}

char &String::operator[](size_t index){
  if (index >= len)  {
    throw std::out_of_range("Index out of range");
  }
  return str[index];
}

const char &String::operator[](size_t index) const{
  if (index >= len)  {
    throw std::out_of_range("Index out of range");
  }
  return str[index];
}

String::operator const char *() const noexcept{
  return str;
}

String::operator int() const noexcept{
  return static_cast<int>(len);
}

String::operator bool() const noexcept{
  return len > 0;
}

size_t String::length() const noexcept{
  return len;
}

const char *String::c_str() const noexcept{
  return str;
}

std::ostream &operator<<(std::ostream &os, const String &s){
  return os << s.str;
}

String operator+(String lhs, const String &rhs){
  lhs += rhs;
  return lhs;
}

String operator+(String lhs, const char *rhs){
  lhs += rhs;
  return lhs;
}

String operator+(const char *lhs, const String &rhs){
  String result(lhs);
  result += rhs;
  return result;
}

String operator+(String lhs, char rhs){
  lhs += String(1, rhs);
  return lhs;
}

String operator+(char lhs, const String &rhs){
  String result(1, lhs);
  result += rhs;
  return result;
}

String operator-(const String &lhs, const String &rhs){
  String result(lhs);
  result -= rhs;
  return result;
}

String operator-(const String &lhs, const char *rhs){
  String result(lhs);
  result -= rhs;
  return result;
}

String operator*(const String &lhs, int multiplier){
  if (multiplier <= 0 || lhs.length() == 0)  {
    return String();
  }
  size_t lhs_len = lhs.length();
  if (multiplier > 0 && lhs_len > std::numeric_limits<size_t>::max() / static_cast<size_t>(multiplier))  {
    throw std::overflow_error("Resulting string too large");
  }

  String result;
  for (int i = 0; i < multiplier; ++i)  {
    result += lhs;
  }
  return result;
}

String operator*(int multiplier, const String &rhs){
  return rhs * multiplier;
}

bool operator==(const String &lhs, const String &rhs) noexcept{
  return std::strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const String &lhs, const String &rhs) noexcept{
  return !(lhs == rhs);
}

bool operator<(const String &lhs, const String &rhs) noexcept{
  return std::strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator>(const String &lhs, const String &rhs) noexcept{
  return std::strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

bool operator==(const String &lhs, const char *rhs) noexcept{
  if (rhs == nullptr)
    return lhs.length() == 0;
  return std::strcmp(lhs.c_str(), rhs) == 0;
}

bool operator==(const char *lhs, const String &rhs) noexcept{
  if (lhs == nullptr)
    return rhs.length() == 0;
  return std::strcmp(lhs, rhs.c_str()) == 0;
}

bool operator!=(const String &lhs, const char *rhs) noexcept{
  return !(lhs == rhs);
}

bool operator!=(const char *lhs, const String &rhs) noexcept{
  return !(lhs == rhs);
}

bool operator<(const String &lhs, const char *rhs) noexcept{
  if (rhs == nullptr)
    return false;
  return std::strcmp(lhs.c_str(), rhs) < 0;
}

bool operator<(const char *lhs, const String &rhs) noexcept{
  if (lhs == nullptr)
    return rhs.length() > 0;
  return std::strcmp(lhs, rhs.c_str()) < 0;
}

bool operator>(const String &lhs, const char *rhs) noexcept{
  if (rhs == nullptr)
    return lhs.length() > 0;
  return std::strcmp(lhs.c_str(), rhs) > 0;
}

bool operator>(const char *lhs, const String &rhs) noexcept{
  if (lhs == nullptr)
    return false;
  return std::strcmp(lhs, rhs.c_str()) > 0;
}
