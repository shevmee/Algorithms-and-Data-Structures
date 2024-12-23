#include <stdexcept>
#include <iostream>
#include <iomanip>

#include "BigInteger.hpp"

BigInteger::BigInteger(long long number) 
{
  if (number == 0) {
    digits_.push_back(0);
    is_negative_ = false;
  } else {
    if (number < 0) {
      is_negative_ = true;
      number = -number;
    } else {
      is_negative_ = false;
    }

    while (number > 0) {
      digits_.push_back(number % BASE);
      number /= BASE;
    }
  }
}

BigInteger::BigInteger(const std::string& number) 
{
  if (number.empty()) {
    throw std::invalid_argument("Empty string is not a valid number");
  }

  is_negative_ = (number[0] == '-');
  size_t start = is_negative_ ? 1 : 0;

  if (start == number.size()) {
    throw std::invalid_argument("Invalid number format");
  }

  size_t chunk = 0;
  size_t base_pow = 1;

  for (size_t i = number.size(); i-- > start;) {
    if (!std::isdigit(number[i])) {
        throw std::invalid_argument("String contains non-digit characters");
    }

    chunk += (number[i] - '0') * base_pow;
    base_pow *= 10;

    if (base_pow == BASE) {
      digits_.push_back(chunk);
      chunk = 0;
      base_pow = 1;
    }
  }

  if (chunk > 0) {
    digits_.push_back(chunk);
  }

  if (digits_.empty()) {
    digits_.push_back(0);
  }
}

BigInteger::BigInteger(const char* number) 
    : BigInteger(std::string(number)) {}

BigInteger::BigInteger(const BigInteger& other) 
    : digits_(other.digits_), is_negative_(other.is_negative_) {}

BigInteger& BigInteger::operator=(const BigInteger& other) & 
{
  if (this != &other) 
  {
    digits_ = other.digits_;
    is_negative_ = other.is_negative_;
  }
  return *this;
}

std::strong_ordering BigInteger::operator<=>(const BigInteger& other) const
{
  if (is_negative_ != other.is_negative_)
  {
    return is_negative_ ? std::strong_ordering::less : std::strong_ordering::greater;
  }

  if (length() != other.length())
  {
    if (is_negative_) {
      return digits_.size() > other.digits_.size() ? std::strong_ordering::less : std::strong_ordering::greater;
    } else {
      return digits_.size() < other.digits_.size() ? std::strong_ordering::less : std::strong_ordering::greater;
    }
  }

  for (size_t i = length(); i-- > 0;)
  {
    if (digits_[i] != other.digits_[i])
    {
      if (is_negative_) {
        return digits_[i] > other.digits_[i] ? std::strong_ordering::less : std::strong_ordering::greater;
      } else {
        return digits_[i] < other.digits_[i] ? std::strong_ordering::less : std::strong_ordering::greater;
      }
    }
  }
  return std::strong_ordering::equal;
}

bool BigInteger::operator==(const BigInteger &other) const
{
  return (*this <=> other) == std::strong_ordering::equal;
}

bool BigInteger::operator!=(const BigInteger& other) const
{
  return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const BigInteger& bi) {
  if (bi.is_negative_ && !(bi.digits_.size() == 1 && bi.digits_[0] == 0)) {
    os << '-';
  }

  if (bi.digits_.empty()) {
    os << '0';
    return os;
  }

  os << bi.digits_.back();

  for (size_t i = bi.digits_.size() - 1; i-- > 0;) {
    //os << std::setw(BigInteger::BASE) << std::setfill('0') << bi.digits_[i];
    os << bi.digits_[i];
  }

  return os;
}

std::istream& operator>>(std::istream& is, BigInteger& bi) {
  std::string input;
  is >> input;

  if (input.empty() || (input[0] != '-' && !std::isdigit(input[0]))) {
    is.setstate(std::ios::failbit);
    return is;
  }

  bi.digits_.clear();
  bi.is_negative_ = false;

  size_t start = 0;
  if (input[0] == '-') {
    bi.is_negative_ = true;
    start = 1;
  }

  for (size_t i = input.size(); i-- > start;) {
    if (!std::isdigit(input[i])) {
      is.setstate(std::ios::failbit);
      return is;
    }
    bi.digits_.push_back(input[i] - '0');
  }

    bi.normalize();
  
  return is;
}

BigInteger factorial(int n)
{
  if (n < 0)
  {
    throw std::invalid_argument("n must be non-negative");
  }

  BigInteger result = 1;
  for (size_t i = 2; i <= n; ++i)
  {
    result *= i;
  }

  return result;
}

BigInteger NthCatalan(int n)
{
  if (n < 0)
  {
    throw std::invalid_argument("n must be non-negative");
  }

  BigInteger num = factorial(2 * n);
  BigInteger denom = factorial(n + 1) + factorial(n);
  return num / denom;
}

int BigInteger::length() const
{
  return digits_.size();
}

bool BigInteger::is_negative() const
{
  return is_negative_;
}

int BigInteger::operator[](std::size_t index) const {
  if (index >= digits_.size()) {
    throw std::out_of_range("Index out of bounds");
  }
  return digits_[index];
}

// int& BigInteger::operator[](std::size_t index) {
//   if (index >= digits_.size()) {
//     throw std::out_of_range("Index out of bounds");
//   }
//   return digits_[index];
// }

BigInteger &BigInteger::operator+=(const BigInteger &other)
{
  if (is_negative_ == other.is_negative_)
    {
      // Same sign, so we simply add the magnitudes
      add_magnitude(other);
    } else {
    // Different signs, we need to subtract magnitudes
    if (compare_magnitude(other) >= 0) {
      subtract_magnitude(other);
    } else {
      BigInteger temp = other;
      temp.subtract_magnitude(*this);
      *this = temp;
    }
  }
  normalize();
  return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& other) {
  if (is_negative_ != other.is_negative_) {
    // Different signs, so we add magnitudes
    add_magnitude(other);
  } else {
    // Same sign, we need to subtract magnitudes
    if (compare_magnitude(other) >= 0) {
      subtract_magnitude(other);
    } else {
      BigInteger temp = other;
      temp.subtract_magnitude(*this);
      temp.is_negative_ = !temp.is_negative_;
      *this = temp;
    }
  }
  normalize();
  return *this;
}

BigInteger& BigInteger::operator*=(const BigInteger& other) {
  BigInteger result;
  result.digits_.resize(length() + other.length(), 0);

  for (size_t i = 0; i < length(); ++i) {
    long long carry = 0;
    for (size_t j = 0; j < other.length() || carry; ++j) {
      long long current = result.digits_[i + j] +
        static_cast<long long>(operator[](i)) * (j < other.length() ? other[j] : 0) + carry;
      
      result.digits_[i + j] = current % BASE;
      carry = current / BASE;
    }
  }

  result.is_negative_ = is_negative() != other.is_negative();
  result.normalize();
  *this = result;
  return *this;
}

BigInteger &BigInteger::operator/=(const BigInteger& other)
{
  if (other == BigInteger(0LL))
  {
    throw std::invalid_argument("Division by zero");
  }

  BigInteger result;
  BigInteger current;

  result.digits_.resize(length(), 0);

  for (size_t i = length(); i-- > 0;)
  {
    current = current * BASE + digits_[i];
    int x = 0;
    int left = 0;
    int right = BASE;

    while (left <= right)
    {
      int mid = (right + left) / 2;
      BigInteger temp = other * BigInteger(mid);
      if (temp <= current)
      {
        x = mid;
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
    result.digits_[i] = x;
    current = current - other * BigInteger(x);
  }

  result.is_negative_ = is_negative() != other.is_negative();
  result.normalize();
  *this = result;
  return *this;
}

void BigInteger::add_magnitude(const BigInteger& other) {
  size_t max_length = std::max(length(), other.length());
  digits_.resize(max_length, 0);
  int carry = 0;
  for (size_t i = 0; i < max_length || carry != 0; ++i) {
    if (i == digits_.size()) {
      digits_.push_back(0);
    }
    digits_[i] += (i < other.length() ? other.digits_[i] : 0) + carry;
    carry = digits_[i] >= BASE;
    if (carry) {
      digits_[i] -= BASE;
    }
  }
}

void BigInteger::subtract_magnitude(const BigInteger& other) {
  int borrow = 0;
  for (size_t i = 0; i < length(); ++i) {
    digits_[i] -= (i < other.length() ? other.digits_[i] : 0) + borrow;
    if (digits_[i] < 0) {
      digits_[i] += BASE;
      borrow = 1;
    } else {
      borrow = 0;
    }
  }
}

int BigInteger::compare_magnitude(const BigInteger& other) const {
  if (length() != other.length()) {
    return length() < other.length() ? -1 : 1;
  }
  for (size_t i = length(); i-- > 0;) {
    if (digits_[i] != other.digits_[i]) {
      return digits_[i] < other.digits_[i] ? -1 : 1;
    }
  }
  return 0;
}

void BigInteger::normalize() {
  while (digits_.size() > 1 && digits_.back() == 0) {
    digits_.pop_back();
  }
  if (digits_.size() == 1 && digits_[0] == 0) {
    is_negative_ = false;
  }
}

BigInteger operator+(const BigInteger& lhs, const BigInteger& rhs)
{
  BigInteger result = lhs;
  result += rhs;
  return result;
}

BigInteger operator-(const BigInteger& lhs, const BigInteger& rhs)
{
  BigInteger result = lhs;
  result -= rhs;
  return result;
}

BigInteger operator*(const BigInteger& lhs, const BigInteger& rhs)
{
  BigInteger copy = lhs;
  copy *= rhs;
  return copy;
}

BigInteger operator/(const BigInteger& lhs, const BigInteger& rhs)
{
  BigInteger copy = lhs;
  copy /= rhs;
  return copy;
}

BigInteger& BigInteger::operator++()
{
  *this += BigInteger(1);
  return *this;
}

BigInteger BigInteger::operator++(int) 
{
  BigInteger copy = *this;
  ++(*this);
  return copy;
}

BigInteger& BigInteger::operator--()
{
  *this -= BigInteger(1);
  return *this;
}

BigInteger BigInteger::operator--(int)
{
  BigInteger copy = *this;
  --(*this);
  return copy;
}
