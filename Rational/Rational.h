#ifndef RATIONAL_H
#define RATIONAL_H

#include <compare>

class Rational
{
private:
    int m_numerator;
    int m_denomenator;

    void normalize();
    int gcd(int a, int b) const;
public:
    Rational(int numerator = 0, int denomenator = 1);

    int getNumerator() const;
    int getDenomerator() const;

    void setNumerator(int numerator);
    void setDenomerator(int denomenator);

    void displayFraction() const;
    void displayDecimalFraction() const;

    Rational add(const Rational& other) const;
    Rational subtract(const Rational& other) const;
    Rational multiply(const Rational& other) const;
    Rational divide(const Rational& other) const;

    auto operator<=>(const Rational& other) const {
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
};

#endif