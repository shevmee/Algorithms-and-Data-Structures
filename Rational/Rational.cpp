#include <stdexcept>
#include <iostream>
#include <iomanip>

#include "Rational.h"

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

Rational Rational::add(const Rational& other) const
{
    int num = m_numerator * other.getDenomerator() + m_denomenator * other.getNumerator();
    int denom = m_denomenator * other.getDenomerator();

    return Rational(num, denom);
}

Rational Rational::subtract(const Rational& other) const
{
    int num = m_numerator * other.getDenomerator() - m_denomenator * other.getNumerator();
    int denom = m_denomenator * other.getDenomerator();

    return Rational(num, denom);
}

Rational Rational::multiply(const Rational& other) const
{
    int num = m_numerator * other.getNumerator();
    int denom = m_denomenator * other.getDenomerator();

    return Rational(num, denom);
}

Rational Rational::divide(const Rational& other) const 
{
    if (other.m_numerator == 0) {
        throw std::invalid_argument("Cannot divide by zero");
    }
    int num = m_numerator * other.getDenomerator();
    int denom = m_denomenator * other.getNumerator();

    return Rational(num, denom);
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
