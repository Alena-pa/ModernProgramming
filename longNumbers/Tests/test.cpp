#include "pch.h"
#include <random>
#include <string>
#include <algorithm>
#include "gtest/gtest.h"


using biv::LongNumber;

class LongNumberTest : public ::testing::Test {
protected:
    LongNumber zero;
    LongNumber smallPositive;
    LongNumber largePositive;
    LongNumber smallNegative;
    LongNumber largeNegative;

    void SetUp() override {
        zero = LongNumber("0");
        smallPositive = LongNumber("123");
        largePositive = LongNumber("9876543210987654321");
        smallNegative = LongNumber("-45");
        largeNegative = LongNumber("-100000000000000000");
    }
};

biv::LongNumber generateRandomLongNumber() {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<> len_dist(1, 50);
    int length = len_dist(gen);

    std::uniform_int_distribution<> sign_dist(0, 1);
    bool isNegative = sign_dist(gen);

    std::uniform_int_distribution<> digit_dist(0, 9);

    std::string numStr = "";

    if (isNegative) {
        numStr += '-';
    }

    for (int i = 0; i < length; ++i) {
        int digit = digit_dist(gen);

        if (i == 0 && length > 1 && digit == 0) {
            digit = 1;
        }

        numStr += std::to_string(digit);
    }

    if (numStr == "0" || numStr == "-0") {
        return biv::LongNumber("0");
    }

    return biv::LongNumber(numStr.c_str());
}

TEST_F(LongNumberTest, Random_AdditionSubtractionIdentity) {
    const int NUM_TESTS = 100;

    for (int i = 0; i < NUM_TESTS; ++i) {
        LongNumber A = generateRandomLongNumber();
        LongNumber B = generateRandomLongNumber();

        LongNumber result = (A + B) - B;
        EXPECT_EQ(A, result);

        result = (A - B) + B;
        EXPECT_EQ(A, result);
    }
}

TEST_F(LongNumberTest, Random_MultiplicationIdentity) {
    const int NUM_TESTS = 100;
    LongNumber one("1");
    LongNumber zero("0");

    for (int i = 0; i < NUM_TESTS; ++i) {
        LongNumber A = generateRandomLongNumber();

        LongNumber resultOne = A * one;
        EXPECT_EQ(A, resultOne);

        LongNumber resultZero = A * zero;
        EXPECT_EQ(zero, resultZero);
    }
}

TEST_F(LongNumberTest, Division_ByZero_Throws) {
    EXPECT_THROW(largePositive / zero, std::invalid_argument);
}