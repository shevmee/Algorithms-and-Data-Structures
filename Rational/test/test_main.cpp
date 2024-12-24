#include <gtest/gtest.h>
#include "Rational.hpp"

struct CoutRedirect {
    std::stringstream buffer;
    std::streambuf* old;
    CoutRedirect() : old(std::cout.rdbuf(buffer.rdbuf())) {}
    ~CoutRedirect() { std::cout.rdbuf(old); }
};

TEST(RationalTest, DisplayFraction) {
    Rational r(3, 4);
    CoutRedirect redirect;
    r.displayFraction();
    EXPECT_EQ(redirect.buffer.str(), "3/4\n");
}

TEST(RationalTest, DisplayDecimalFraction) {
    Rational r(3, 4);
    CoutRedirect redirect;
    r.displayDecimalFraction();
    EXPECT_EQ(redirect.buffer.str(), "0.7500000000\n");
}

TEST(RationalTest, ConversionToDouble) {
    Rational r(3, 4);
    double value = static_cast<double>(r);
    EXPECT_DOUBLE_EQ(value, 0.75);
}

TEST(RationalTest, ThreeWayComparison) {
    Rational r1(3, 4);
    Rational r2(6, 8);
    Rational r3(1, 2);

    EXPECT_EQ(r1 <=> r2, std::strong_ordering::equal);
    EXPECT_EQ(r1 <=> r3, std::strong_ordering::greater);
    EXPECT_EQ(r3 <=> r1, std::strong_ordering::less);
}

TEST(RationalTest, EqualityAndInequality) {
    Rational r1(3, 4);
    Rational r2(6, 8);
    Rational r3(1, 2);

    EXPECT_TRUE(r1 == r2);
    EXPECT_FALSE(r1 == r3);
    EXPECT_TRUE(r1 != r3);
    EXPECT_FALSE(r1 != r2);
}

TEST(RationalTest, AdditionOperator) {
    Rational r1(1, 2);
    Rational r2(1, 3);
    Rational result = r1 + r2;
    EXPECT_EQ(result, Rational(5, 6));
}

TEST(RationalTest, SubtractionOperator) {
    Rational r1(1, 2);
    Rational r2(1, 3);
    Rational result = r1 - r2;
    EXPECT_EQ(result, Rational(1, 6));
}

TEST(RationalTest, MultiplicationOperator) {
    Rational r1(2, 3);
    Rational r2(3, 4);
    Rational result = r1 * r2;
    EXPECT_EQ(result, Rational(1, 2));
}

TEST(RationalTest, DivisionOperator) {
    Rational r1(2, 3);
    Rational r2(3, 4);
    Rational result = r1 / r2;
    EXPECT_EQ(result, Rational(8, 9));
}

TEST(RationalTest, DivisionByZero) {
    Rational r1(1, 2);
    Rational r2(0, 1);
    EXPECT_THROW(r1 / r2, std::invalid_argument);
}
