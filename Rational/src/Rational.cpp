#include <stdexcept>
#include <iostream>
#include <iomanip>

#include "Rational.hpp"

int Rational::gcd(int a, int b) const
{
    while (b != 0) {
        int tmp = b;
        b = a % b;
        a = tmp;
    }
    return a;
}

void Rational::normalize() {
    int gcd_value = gcd(std::abs(m_numerator), m_denomenator);
    m_numerator /= gcd_value;
    m_denomenator /= gcd_value;
}

Rational::Rational(int numerator, int denomenator)
{
    if (denomenator == 0) {
        throw std::invalid_argument("Denominator cannot be zero");
    }

    if (denomenator < 0) {
        m_numerator = -numerator;
        m_denomenator = -denomenator;
    } else {
        m_numerator = numerator;
        m_denomenator = denomenator;
    }
    normalize();
}

int Rational::getNumerator() const
{
    return m_numerator;
}

int Rational::getDenomerator() const 
{
    return m_denomenator;
}

void Rational::setNumerator(int numenator) 
{
    m_numerator = numenator;
    normalize();
}

void Rational::setDenomerator(int denomenator) 
{
    if (denomenator == 0) {
        throw std::invalid_argument("Denominator cannot be zero");
    }
    m_denomenator = denomenator;
    normalize();
}

Rational& Rational::operator+= (const Rational& other)
{
    m_numerator = m_numerator * other.getDenomerator() + m_denomenator * other.getNumerator();
    m_denomenator *= other.getDenomerator();
    normalize();
    return *this;
}

Rational& Rational::operator-= (const Rational& other)
{
    m_numerator = m_numerator * other.getDenomerator() - m_denomenator * other.getNumerator();
    m_denomenator *= other.getDenomerator();
    normalize();
    return *this;
}

Rational& Rational::operator/= (const Rational& other)
{
    if (other.m_numerator == 0) {
        throw std::invalid_argument("Cannot divide by zero");
    }
    m_numerator *= other.getDenomerator();
    m_denomenator *= other.getNumerator();
    normalize();
    return *this;
}

Rational& Rational::operator*= (const Rational& other)
{
    m_numerator *= other.getNumerator();
    m_denomenator *= other.getDenomerator();
    normalize();
    return *this;
}

std::strong_ordering Rational::operator<=>(const Rational& other) const {
    long long lhs = static_cast<long long>(m_numerator) * other.m_denomenator;
    long long rhs = static_cast<long long>(m_denomenator) * other.m_numerator;

    if (lhs < rhs) {
        return std::strong_ordering::less;
    } else if (lhs > rhs) {
        return std::strong_ordering::greater;
    } else {
        return std::strong_ordering::equal;
    }
}

bool Rational::operator== (const Rational& other) const
{
 return (*this <=> other) == std::strong_ordering::equal;
}

bool Rational::operator!= (const Rational& other) const
{
    return !(*this == other);
}

void Rational::displayFraction() const 
{
    std::cout << m_numerator << "/" << m_denomenator << std::endl;
}

void Rational::displayDecimalFraction() const 
{
    double decimalValue = static_cast<double>(m_numerator) / static_cast<double>(m_denomenator);
    std::cout << std::fixed << std::setprecision(10) << decimalValue << std::endl;
}

Rational::operator double() const {
    return static_cast<double>(m_numerator) / static_cast<double>(m_denomenator);
}

Rational operator+ (const Rational& lhs, const Rational& rhs)
{
    Rational copy = lhs;
    copy += rhs;
    return copy;
}

Rational operator- (const Rational& lhs, const Rational& rhs)
{
    Rational copy = lhs;
    copy -= rhs;
    return copy;
}

Rational operator/ (const Rational& lhs, const Rational& rhs)
{
    Rational copy = lhs;
    copy /= rhs;
    return copy;
}

Rational operator* (const Rational& lhs, const Rational& rhs)
{
    Rational copy = lhs;
    copy *= rhs;
    return copy;
}
