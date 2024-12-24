#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <string>
#include <vector>

class BigInteger {
 private:
  std::vector<long long> digits_;
  bool is_negative_;
  static const size_t BASE = 1'000'000'000;

private:
  void normalize();
  void add_magnitude(const BigInteger&);
  void subtract_magnitude(const BigInteger&);
  int compare_magnitude(const BigInteger&) const;

 public:
  BigInteger(long long n = 0);
  BigInteger(const std::string&);
  BigInteger(const char*);
  BigInteger(const BigInteger&);

  BigInteger& operator=(const BigInteger&) &;
  BigInteger& operator+=(const BigInteger&);
  BigInteger& operator-=(const BigInteger&);
  BigInteger& operator*=(const BigInteger&);
  BigInteger& operator/=(const BigInteger&);
  BigInteger& operator%=(const BigInteger&);
  BigInteger& operator^=(const BigInteger&);

  BigInteger& operator++();
  BigInteger operator++(int);
  BigInteger& operator--();
  BigInteger operator--(int);

  int length() const;
  bool is_negative() const;
  int operator[](std::size_t) const;
  BigInteger abs() const;

  friend BigInteger operator+(const BigInteger&, const BigInteger&);
  friend BigInteger operator-(const BigInteger&, const BigInteger&);
  friend BigInteger operator*(const BigInteger&, const BigInteger&);
  friend BigInteger operator/(const BigInteger&, const BigInteger&);
  friend BigInteger operator%(const BigInteger&, const BigInteger&);
  friend BigInteger operator^(const BigInteger&, const BigInteger&);

  std::strong_ordering operator<=>(const BigInteger&) const;
  bool operator==(const BigInteger&) const;
  bool operator!=(const BigInteger&) const;

  friend BigInteger sqrt(const BigInteger&);

  friend std::ostream& operator<<(std::ostream&, const BigInteger&);
  friend std::istream& operator>>(std::istream&, BigInteger&);

  friend BigInteger NthCatalan(int n);
  friend BigInteger NthFibonacci(std::size_t n);
  friend BigInteger factorial(int n);
};

#endif
