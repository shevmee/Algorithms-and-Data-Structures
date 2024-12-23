#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <vector>
#include <string>

class BigInteger {
private:
  std::vector<long long> digits_;
  bool is_negative_;
  static const size_t BASE = 1'000'000'000;
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

  friend void divide_by_2(BigInteger&);

  bool is_null(const BigInteger&) const;
  int length() const;
  bool is_negative() const;
  int operator[](std::size_t index) const;
  //int& operator[](std::size_t index);
  void add_magnitude(const BigInteger& other);
  void subtract_magnitude(const BigInteger& other);
  int compare_magnitude(const BigInteger& other) const;
  void normalize();

  friend BigInteger operator+(const BigInteger&, const BigInteger&);
  friend BigInteger operator-(const BigInteger&, const BigInteger&);
  friend BigInteger operator*(const BigInteger&, const BigInteger&);
  friend BigInteger operator/(const BigInteger&, const BigInteger&);
  friend BigInteger operator%(const BigInteger&, const BigInteger&);
  friend BigInteger operator^(BigInteger&, const BigInteger&);

  std::strong_ordering operator<=>(const BigInteger&) const;
  bool operator==(const BigInteger&) const;
  bool operator!=(const BigInteger&) const;
    
  friend BigInteger sqrt(BigInteger&);

  friend std::ostream& operator<<(std::ostream&, const BigInteger&);
  friend std::istream& operator>>(std::istream&, BigInteger&);

  friend BigInteger NthCatalan(int n);
  friend BigInteger NthFibonacci(int n);
  friend BigInteger factorial(int n);
};

#endif
