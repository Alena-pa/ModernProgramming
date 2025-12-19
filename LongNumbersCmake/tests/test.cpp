#include <gtest/gtest.h>
#include "longNumber.hpp"

using biv::LongNumber;

TEST(LongNumberTest, DefaultConstructor) {
    LongNumber n;
    EXPECT_EQ(n.get_digits_number(), 1);
    EXPECT_EQ(n.get_rank_number(0), 0);
    EXPECT_FALSE(n.is_negative());
}

TEST(LongNumberTest, FromStringPositive) {
    LongNumber n("12345");
    EXPECT_EQ(n.get_digits_number(), 5);
    EXPECT_EQ(n.get_rank_number(0), 5);
    EXPECT_EQ(n.get_rank_number(4), 1);
    EXPECT_FALSE(n.is_negative());
}

TEST(LongNumberTest, FromStringNegative) {
    LongNumber n("-6789");
    EXPECT_TRUE(n.is_negative());
    EXPECT_EQ(n.get_digits_number(), 4);
    EXPECT_EQ(n.get_rank_number(0), 9);
}

TEST(LongNumberTest, LeadingZeros) {
    LongNumber n("00042");
    EXPECT_EQ(n.get_digits_number(), 2);
    EXPECT_EQ(n.get_rank_number(0), 2);
    EXPECT_EQ(n.get_rank_number(1), 4);
}

TEST(LongNumberTest, ZeroIsPositive) {
    LongNumber n1("-0");
    LongNumber n2("0");
    LongNumber n3("+0");
    EXPECT_FALSE(n1.is_negative());
    EXPECT_FALSE(n2.is_negative());
    EXPECT_FALSE(n3.is_negative());
    EXPECT_EQ(n1, n2);
    EXPECT_EQ(n2, n3);
}

TEST(LongNumberTest, Equality) {
    LongNumber a("123");
    LongNumber b("123");
    LongNumber c("-123");
    EXPECT_EQ(a, b);
    EXPECT_NE(a, c);
}

TEST(LongNumberTest, AdditionPositive) {
    LongNumber a("999");
    LongNumber b("1");
    LongNumber expected("1000");
    EXPECT_EQ(a + b, expected);
}

TEST(LongNumberTest, AdditionNegative) {
    LongNumber a("-500");
    LongNumber b("-300");
    LongNumber expected("-800");
    EXPECT_EQ(a + b, expected);
}

TEST(LongNumberTest, Subtraction) {
    LongNumber a("1000");
    LongNumber b("1");
    LongNumber expected("999");
    EXPECT_EQ(a - b, expected);
}

TEST(LongNumberTest, SubtractionNegativeResult) {
    LongNumber a("5");
    LongNumber b("10");
    LongNumber expected("-5");
    EXPECT_EQ(a - b, expected);
}

TEST(LongNumberTest, MultiplicationByZero) {
    LongNumber a("123456789");
    LongNumber b("0");
    LongNumber expected("0");
    EXPECT_EQ(a * b, expected);
    EXPECT_EQ(b * a, expected);
}

TEST(LongNumberTest, MultiplicationSimple) {
    LongNumber a("123");
    LongNumber b("3");
    LongNumber expected("369");
    EXPECT_EQ(a * b, expected);
}

TEST(LongNumberTest, DivisionExact) {
    LongNumber a("100");
    LongNumber b("4");
    LongNumber expected("25");
    EXPECT_EQ(a / b, expected);
}

TEST(LongNumberTest, DivisionTruncated) {
    LongNumber a("10");
    LongNumber b("3");
    LongNumber expected("3");
    EXPECT_EQ(a / b, expected);
}

TEST(LongNumberTest, Modulo) {
    LongNumber a("10");
    LongNumber b("3");
    LongNumber expected("1");
    EXPECT_EQ(a % b, expected);
}

TEST(LongNumberTest, DivisionByZeroThrows) {
    LongNumber a("42");
    LongNumber b("0");
    EXPECT_THROW(a / b, std::invalid_argument);
}

TEST(LongNumberTest, InvalidStringThrows) {
    EXPECT_THROW(LongNumber("12a3"), std::invalid_argument);
    EXPECT_THROW(LongNumber(""), std::invalid_argument);
    EXPECT_THROW(LongNumber("+"), std::invalid_argument);
    EXPECT_THROW(LongNumber("-"), std::invalid_argument);
    EXPECT_THROW(LongNumber(nullptr), std::invalid_argument);
}

TEST(LongNumberTest, AssignFromString) {
    LongNumber n;
    n = "98765";
    EXPECT_EQ(n.get_digits_number(), 5);
    EXPECT_EQ(n.get_rank_number(0), 5);
}

TEST(LongNumberTest, Comparisons) {
    LongNumber a("100");
    LongNumber b("99");
    LongNumber c("-100");
    LongNumber d("0");

    EXPECT_TRUE(a > b);
    EXPECT_TRUE(b < a);
    EXPECT_TRUE(a > d);
    EXPECT_TRUE(c < d);
    EXPECT_TRUE(c < a);
}

TEST(LongNumberTest, CopyAndMove) {
    LongNumber a("12345");
    LongNumber b = a;
    LongNumber c = std::move(a);

    EXPECT_EQ(b, LongNumber("12345"));
    EXPECT_EQ(c, LongNumber("12345"));
}