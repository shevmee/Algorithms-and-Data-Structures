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

    explicit operator double() const;

    Rational& operator+= (const Rational&);
    Rational& operator-= (const Rational&);
    Rational& operator/= (const Rational&);
    Rational& operator*= (const Rational&);

    std::strong_ordering operator<=>(const Rational&) const;
    bool operator== (const Rational&) const;
    bool operator!= (const Rational&) const;

    friend Rational operator+ (const Rational&, const Rational&);
    friend Rational operator- (const Rational&, const Rational&);
    friend Rational operator/ (const Rational&, const Rational&);
    friend Rational operator* (const Rational&, const Rational&);
};

#endif