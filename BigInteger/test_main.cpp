#include <gtest/gtest.h>

#include "BigInteger.hpp"

TEST(BigIntegerTest, DefaultConstructor) {
    BigInteger num;
    EXPECT_EQ(num.is_negative(), false);
    EXPECT_EQ(num.length(), 1);
    EXPECT_EQ(num[0], 0);
}

TEST(BigIntegerTest, ConstructorFromLongLong) {
    BigInteger num(1'234'567'890ll);
    EXPECT_EQ(num.is_negative(), false);
    EXPECT_EQ(num.length(), 2);
    EXPECT_EQ(num[0], 234'567'890ll);
    EXPECT_EQ(num[1], 1);

    BigInteger num_neg(-9'876'543'210ll);
    EXPECT_EQ(num_neg.is_negative(), true);
    EXPECT_EQ(num_neg.length(), 2);
    EXPECT_EQ(num_neg[0], 876'543'210ll);
    EXPECT_EQ(num_neg[1], 9ll);

    BigInteger num_zero(0ll);
    EXPECT_EQ(num_zero.is_negative(), false);
    EXPECT_EQ(num_zero.length(), 1);
    EXPECT_EQ(num_zero[0], 0);
}

TEST(BigIntegerTest, ConstructorFromString) {
    BigInteger num(std::string("1234567890123456789"));
    EXPECT_EQ(num.is_negative(), false);
    EXPECT_EQ(num.length(), 3);
    EXPECT_EQ(num[0], 123456789);
    EXPECT_EQ(num[1], 234567890);
    EXPECT_EQ(num[2], 1);

    BigInteger num_neg(std::string("-9876543210987654321"));
    EXPECT_EQ(num_neg.is_negative(), true);
    EXPECT_EQ(num_neg.length(), 3);
    EXPECT_EQ(num_neg[0], 987654321);
    EXPECT_EQ(num_neg[1], 876543210);
    EXPECT_EQ(num_neg[2], 9);

    BigInteger num_leading_zeros(std::string("00000000012345"));
    EXPECT_EQ(num_leading_zeros.is_negative(), false);
    EXPECT_EQ(num_leading_zeros.length(), 1);
    EXPECT_EQ(num_leading_zeros[0], 12345);

    BigInteger num_zero(std::string("0"));
    EXPECT_EQ(num_zero.is_negative(), false);
    EXPECT_EQ(num_zero.length(), 1);
    EXPECT_EQ(num_zero[0], 0);

    EXPECT_THROW(BigInteger("not_a_number"), std::invalid_argument);
}

TEST(BigIntegerTest, ConstructorFromCString) {
    BigInteger num("1234567890123456789");
    EXPECT_EQ(num.is_negative(), false);
    EXPECT_EQ(num.length(), 3);
    EXPECT_EQ(num[0], 123456789);
    EXPECT_EQ(num[1], 234567890);
    EXPECT_EQ(num[2], 1);

    BigInteger num_neg("-9876543210987654321");
    EXPECT_EQ(num_neg.is_negative(), true);
    EXPECT_EQ(num_neg.length(), 3);
    EXPECT_EQ(num_neg[0], 987654321);
    EXPECT_EQ(num_neg[1], 876543210);
    EXPECT_EQ(num_neg[2], 9);

    BigInteger num_leading_zeros("00000000012345");
    EXPECT_EQ(num_leading_zeros.is_negative(), false);
    EXPECT_EQ(num_leading_zeros.length(), 1);
    EXPECT_EQ(num_leading_zeros[0], 12345);

    BigInteger num_zero("0");
    EXPECT_EQ(num_zero.is_negative(), false);
    EXPECT_EQ(num_zero.length(), 1);
    EXPECT_EQ(num_zero[0], 0);

    EXPECT_THROW(BigInteger("not_a_number"), std::invalid_argument);
}

TEST(BigIntegerTest, CopyConstructor) {
    BigInteger original("1234567890");
    BigInteger copy = original;
    EXPECT_EQ(copy.is_negative(), original.is_negative());
    EXPECT_TRUE(copy == original);
}

TEST(BigIntegerTest, LargeNumbers) {
    std::string large_number = "1234567890123456789012345678901234567890";
    BigInteger num_large(large_number);
    
    EXPECT_EQ(num_large.is_negative(), false);
    EXPECT_EQ(num_large.length(), 5);
    EXPECT_EQ(num_large[0], 234567890);
    EXPECT_EQ(num_large[1], 345678901);
    EXPECT_EQ(num_large[2], 456789012);
    EXPECT_EQ(num_large[3], 567890123);
    EXPECT_EQ(num_large[4], 1234);
}

TEST(BigIntegerTest, SmallNumber) {
    BigInteger num(5);
    EXPECT_EQ(num.is_negative(), false);
    EXPECT_EQ(num.length(), 1);
    EXPECT_EQ(num[0], 5);
}

TEST(BigIntegerTest, AssignmentOperator) {
    BigInteger num1("1234567890");
    BigInteger num2;
    
    num2 = num1;

    EXPECT_EQ(num1, num2);
}

TEST(BigIntegerTest, TestEquality) {
    BigInteger num1("12345");
    BigInteger num2("12345");
    BigInteger num3("54321");

    EXPECT_TRUE(num1 == num2);
    EXPECT_FALSE(num1 == num3);
}

TEST(BigIntegerTest, TestInequality) {
    BigInteger num1("12345");
    BigInteger num2("12345");
    BigInteger num3("54321");

    EXPECT_FALSE(num1 != num2);
    EXPECT_TRUE(num1 != num3);
}

TEST(BigIntegerTest, TestThreeWayComparison) {
    BigInteger num1("12345");
    BigInteger num2("12345");
    BigInteger num3("54321");

    EXPECT_EQ((num1 <=> num2), std::strong_ordering::equal);
    EXPECT_EQ((num1 <=> num3), std::strong_ordering::less);
    EXPECT_EQ((num3 <=> num1), std::strong_ordering::greater);
}

TEST(BigIntegerTest, TestStringComparison) {
    BigInteger num1("1000");
    BigInteger num2("999");

    // num1 is greater than num2
    EXPECT_TRUE(num1 > num2);  // Should be true
    EXPECT_TRUE(num2 < num1);  // Should be true
}


TEST(BigIntegerTest, AdditionAssignmentOperator) {
    BigInteger num1("1234567890");
    BigInteger num2("9876543210");
    
    num1 += num2;

    EXPECT_EQ(num1, BigInteger("11111111100"));
}

TEST(BigIntegerTest, AddPositiveNumbers) {
    BigInteger a("123456789");
    BigInteger b("987654321");
    
    a += b;
    
    BigInteger expected("1111111110");
    EXPECT_TRUE(a == expected);
}

TEST(BigIntegerTest, AddNegativeNumbers) {
    BigInteger a("-123456789");
    BigInteger b("-987654321");
    
    a += b;
    
    BigInteger expected("-1111111110");
    EXPECT_TRUE(a == expected);
}

TEST(BigIntegerTest, AddPositiveAndNegativeNumbers_PositiveLarger) {
    BigInteger a("987654321");
    BigInteger b("-123456789");
    
    a += b;
    
    BigInteger expected("864197532");
    EXPECT_TRUE(a == expected);
}

TEST(BigIntegerTest, AddPositiveAndNegativeNumbers_NegativeLarger) {
    BigInteger a("-123456789");
    BigInteger b("987654321");
    
    a += b;
    
    BigInteger expected("864197532");
    EXPECT_TRUE(a == expected);
}

TEST(BigIntegerTest, AddPositiveAndNegativeNumbers_EqualMagnitude) {
    BigInteger a("123456789");
    BigInteger b("-123456789");
    
    a += b;
    
    BigInteger expected("0");
    EXPECT_TRUE(a == expected);
}

TEST(BigIntegerTest, AddZeroAndPositive) {
    BigInteger a("0");
    BigInteger b("987654321");
    
    a += b;
    
    BigInteger expected("987654321");
    EXPECT_TRUE(a == expected);
}

TEST(BigIntegerTest, AddZeroAndNegative) {
    BigInteger a("0");
    BigInteger b("-987654321");
    
    a += b;
    
    BigInteger expected("-987654321");
    EXPECT_TRUE(a == expected);
}

TEST(BigIntegerTest, AddLargeNumbers) {
    BigInteger a("1000000000000000");
    BigInteger b("1000000000000000");
    
    a += b;
    
    BigInteger expected("2000000000000000");
    EXPECT_TRUE(a == expected);
}

TEST(BigIntegerTest, AddLargePositiveAndLargeNegative) {
    BigInteger a("1000000000000000");
    BigInteger b("-1000000000000000");
    
    a += b;
    
    BigInteger expected("0");
    EXPECT_TRUE(a == expected);
}

TEST(BigIntegerTest, AddNegativeToZero) {
    BigInteger a("0");
    BigInteger b("-123456789");
    
    a += b;
    
    BigInteger expected("-123456789");
    EXPECT_TRUE(a == expected);
}

TEST(BigIntegerTest, SubtractionAssignmentOperator) {
    BigInteger num1("9876543210");
    BigInteger num2("1234567890");

    num1 -= num2;

    EXPECT_EQ(num1, BigInteger("8641975320"));

    BigInteger num3("100");
    BigInteger num4("200");
    num3 -= num4;

    EXPECT_EQ(num3, BigInteger("-100"));
}

TEST(BigIntegerTest, StreamInsertionOperator) {
    BigInteger num("1234567890");

    std::ostringstream oss;
    oss << num;

    EXPECT_EQ(oss.str(), "1234567890");
}

TEST(BigIntegerTest, ReadPositiveNumber) {
    std::istringstream input("1234567890");
    BigInteger bi;
    input >> bi;
    std::cout << bi << " " << BigInteger("1234567890");
    EXPECT_EQ(bi, BigInteger("1234567890"));
}

TEST(BigIntegerTest, ReadNegativeNumber) {
    std::istringstream input("-987654321");
    BigInteger bi;
    input >> bi;
    EXPECT_EQ(bi, BigInteger("-987654321"));
}

TEST(BigIntegerTest, ReadZero) {
    std::istringstream input("0");
    BigInteger bi;
    input >> bi;
    EXPECT_EQ(bi, BigInteger("0"));
}

TEST(BigIntegerTest, ReadWithLeadingZeros) {
    std::istringstream input("00001234");
    BigInteger bi;
    input >> bi;
    EXPECT_EQ(bi, BigInteger("1234"));
}

TEST(BigIntegerTest, ReadInvalidInput) {
    std::istringstream input("abc123");
    BigInteger bi;
    input >> bi;
    EXPECT_TRUE(input.fail());
}

TEST(BigIntegerTest, ReadNegativeZero) {
    std::istringstream input("-0");
    BigInteger bi;
    input >> bi;
    EXPECT_EQ(bi, BigInteger("0"));
}

TEST(BigIntegerTest, Addition) {
    BigInteger a("1234567890");
    BigInteger b("9876543210");
    BigInteger expected("11111111100");

    EXPECT_EQ(a + b, expected);

    BigInteger negative("-1234567890");
    BigInteger result = a + negative;
    EXPECT_EQ(result, BigInteger(0LL));
}

TEST(BigIntegerTest, Subtraction) {
    BigInteger a("9876543210");
    BigInteger b("1234567890");
    BigInteger expected("8641975320");

    EXPECT_EQ(a - b, expected);

    BigInteger negative("-1234567890");
    BigInteger result = a - negative;
    EXPECT_EQ(result, BigInteger("11111111100"));
}

TEST(BigIntegerTest, PrefixIncrement) {
    BigInteger a("999");
    ++a;
    EXPECT_EQ(a, BigInteger("1000"));

    BigInteger b("-1");
    ++b;
    EXPECT_EQ(b, BigInteger("0"));
}

TEST(BigIntegerTest, PostfixIncrement) {
    BigInteger a("999");
    BigInteger original = a++;
    EXPECT_EQ(original, BigInteger("999"));
    EXPECT_EQ(a, BigInteger("1000"));

    BigInteger b("-1");
    original = b++;
    EXPECT_EQ(original, BigInteger("-1"));
    EXPECT_EQ(b, BigInteger("0"));
}

TEST(BigIntegerTest, PrefixDecrement) {
    BigInteger a("1000");
    --a;
    EXPECT_EQ(a, BigInteger("999"));

    BigInteger b("0");
    --b;
    EXPECT_EQ(b, BigInteger("-1"));
}

TEST(BigIntegerTest, PostfixDecrement) {
    BigInteger a("1000");
    BigInteger original = a--;
    EXPECT_EQ(original, BigInteger("1000"));
    EXPECT_EQ(a, BigInteger("999"));

    BigInteger b("0");
    original = b--;
    EXPECT_EQ(original, BigInteger("0"));
    EXPECT_EQ(b, BigInteger("-1"));
}

TEST(BigIntegerTest, EdgeCases) {
    BigInteger zero("0");
    BigInteger one("1");

    EXPECT_EQ(zero + zero, BigInteger("0"));
    EXPECT_EQ(zero - zero, BigInteger("0"));
    EXPECT_EQ(zero + one, one);
    EXPECT_EQ(zero - one, BigInteger("-1"));

    BigInteger negative("-999");
    EXPECT_EQ(--negative, BigInteger("-1000"));
    EXPECT_EQ(++negative, BigInteger("-999"));
}

TEST(BigIntegerTest, Multiplication) {
    BigInteger a("12345");
    BigInteger b("6789");
    BigInteger expected("-835047");

    EXPECT_EQ(a * b, BigInteger("83810205"));

    BigInteger zero("0");
    EXPECT_EQ(a * zero, zero);
    EXPECT_EQ(zero * b, zero);

    BigInteger negative("-123");
    BigInteger expectedNegative("-1518435");
    EXPECT_EQ(a * negative, expectedNegative);
    EXPECT_EQ(negative * b, expected);

    BigInteger negativeResult("15129");
    EXPECT_EQ(negative * negative, negativeResult);
}
