#include "pch.h"
#include "../longNumbers/longNumbers.hpp"
#include "gtest/gtest.h"

using biv::LongNumber;

// ???????? ???????????? ? ??????? ????????
TEST(LongNumberTest, Constructor) {
    LongNumber zero("0");
    LongNumber pos("123");
    LongNumber neg("-45");

    EXPECT_TRUE(zero == LongNumber("0"));
    EXPECT_TRUE(pos == LongNumber("123"));
    EXPECT_TRUE(neg == LongNumber("-45"));
}

// ???????? ????????? ??????? ?????
TEST(LongNumberTest, LeadingZeros) {
    EXPECT_TRUE(LongNumber("0000") == LongNumber("0"));
    EXPECT_TRUE(LongNumber("000123") == LongNumber("123"));
    EXPECT_TRUE(LongNumber("-000123") == LongNumber("-123"));
    EXPECT_TRUE(LongNumber("+00456") == LongNumber("456"));
}

// ????? ????????
TEST(LongNumberTest, Addition) {
    EXPECT_TRUE((LongNumber("2") + LongNumber("3")) == LongNumber("5"));
    EXPECT_TRUE((LongNumber("999") + LongNumber("1")) == LongNumber("1000"));
    EXPECT_TRUE((LongNumber("-5") + LongNumber("3")) == LongNumber("-2"));
    EXPECT_TRUE((LongNumber("5") + LongNumber("-3")) == LongNumber("2"));
    EXPECT_TRUE((LongNumber("-5") + LongNumber("-3")) == LongNumber("-8"));
    EXPECT_TRUE((LongNumber("0") + LongNumber("0")) == LongNumber("0"));
}

// ????? ?????????
TEST(LongNumberTest, Subtraction) {
    EXPECT_TRUE((LongNumber("5") - LongNumber("3")) == LongNumber("2"));
    EXPECT_TRUE((LongNumber("3") - LongNumber("5")) == LongNumber("-2"));
    EXPECT_TRUE((LongNumber("1000") - LongNumber("1")) == LongNumber("999"));
    EXPECT_TRUE((LongNumber("0") - LongNumber("5")) == LongNumber("-5"));
    EXPECT_TRUE((LongNumber("-5") - LongNumber("3")) == LongNumber("-8"));
    EXPECT_TRUE((LongNumber("-5") - LongNumber("-3")) == LongNumber("-2"));
    EXPECT_TRUE((LongNumber("123456789") - LongNumber("123456789")) == LongNumber("0"));
}

// ????? ?????????
TEST(LongNumberTest, Multiplication) {
    EXPECT_TRUE((LongNumber("0") * LongNumber("123")) == LongNumber("0"));
    EXPECT_TRUE((LongNumber("5") * LongNumber("6")) == LongNumber("30"));
    EXPECT_TRUE((LongNumber("12") * LongNumber("12")) == LongNumber("144"));
    EXPECT_TRUE((LongNumber("-3") * LongNumber("4")) == LongNumber("-12"));
    EXPECT_TRUE((LongNumber("-3") * LongNumber("-4")) == LongNumber("12"));
    EXPECT_TRUE((LongNumber("7") * LongNumber("0")) == LongNumber("0"));
}

// ????? ??????? (?????????????)
TEST(LongNumberTest, Division) {
    EXPECT_TRUE((LongNumber("10") / LongNumber("2")) == LongNumber("5"));
    EXPECT_TRUE((LongNumber("10") / LongNumber("3")) == LongNumber("3"));
    EXPECT_TRUE((LongNumber("-10") / LongNumber("3")) == LongNumber("-3"));
    EXPECT_TRUE((LongNumber("10") / LongNumber("-3")) == LongNumber("-3"));
    EXPECT_TRUE((LongNumber("-10") / LongNumber("-3")) == LongNumber("3"));
    EXPECT_TRUE((LongNumber("0") / LongNumber("5")) == LongNumber("0"));
    EXPECT_TRUE((LongNumber("123") / LongNumber("1")) == LongNumber("123"));
}

// ????? ??????? ?? ???????
TEST(LongNumberTest, Modulo) {
    EXPECT_TRUE((LongNumber("10") % LongNumber("3")) == LongNumber("1"));
    EXPECT_TRUE((LongNumber("10") % LongNumber("1")) == LongNumber("0"));
    EXPECT_TRUE((LongNumber("11") % LongNumber("5")) == LongNumber("1"));
}

// ????? ?????????
TEST(LongNumberTest, Comparison) {
    EXPECT_TRUE(LongNumber("5") == LongNumber("5"));
    EXPECT_TRUE(LongNumber("5") != LongNumber("6"));

    EXPECT_TRUE(LongNumber("3") < LongNumber("5"));
    EXPECT_TRUE(LongNumber("5") > LongNumber("3"));

    EXPECT_TRUE(LongNumber("-5") < LongNumber("0"));
    EXPECT_TRUE(LongNumber("0") > LongNumber("-1"));
    EXPECT_TRUE(LongNumber("-10") < LongNumber("-5"));
    EXPECT_TRUE(LongNumber("-5") > LongNumber("-10"));
}

// ??????? ?? ???? ?????? ?????? ??????????
TEST(LongNumberTest, DivisionByZero) {
    LongNumber five("5");
    LongNumber zero("0");

    EXPECT_THROW(five / zero, std::invalid_argument);
    EXPECT_THROW(zero / zero, std::invalid_argument);
}

// ???????? ??????????: (a + b) - b == a
TEST(LongNumberTest, AdditionSubtractionIdentity) {
    LongNumber a("9876543210987654321");
    LongNumber b("-1234567890123456789");

    LongNumber result1 = (a + b) - b;
    EXPECT_TRUE(result1 == a);

    LongNumber result2 = (a - b) + b;
    EXPECT_TRUE(result2 == a);
}