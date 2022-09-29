//
// Created by Veniamin_Arefev on 25.09.2022.
//

#include "gtest/gtest.h"
#include <Rational_number.h>

TEST(Rational_numberTestSuite, Rational_number1) {
    Rational_number first = Rational_number("123", "16");
    Rational_number second = Rational_number("124", "12");
    EXPECT_EQ(first + second, Rational_number("3460", "192"));
    EXPECT_EQ(first - second, Rational_number("-508", "192"));
    EXPECT_EQ(first * second, Rational_number("15252", "192"));
    EXPECT_EQ(first / second, Rational_number("1476", "1984"));
}

TEST(Rational_numberTestSuite, Rational_number2) {
    Rational_number first = Rational_number("123", "16");
    Rational_number second = Rational_number("-124", "12");
    EXPECT_EQ(first + second, Rational_number("-508", "192"));
    EXPECT_EQ(first - second, Rational_number("-3460", "192"));
    EXPECT_EQ(first * second, Rational_number("-15252", "192"));
    EXPECT_EQ(first / second, Rational_number("-1476", "1984"));
}

TEST(Rational_numberTestSuite, Rational_number3) {
    Rational_number first = Rational_number("123", "16");
    EXPECT_EQ(-first, Rational_number("-123", "16"));
}

TEST(Rational_numberTestSuite, Rational_number4) {
    Rational_number first = Rational_number("123", "16");
    EXPECT_EQ(++first, Rational_number("139", "16"));
}

TEST(Rational_numberTestSuite, Rational_number5) {
    Rational_number first = Rational_number("123", "16");
    EXPECT_EQ(first++, Rational_number("123", "16"));
    EXPECT_EQ(first, Rational_number("139", "16"));
}


TEST(Rational_numberTestSuite, Rational_number_comparison) {
    Rational_number number = Rational_number("1");
    Rational_number first = Rational_number("1", "3");
    Rational_number second = Rational_number("1", "4");
    EXPECT_EQ(first < second, false);
    EXPECT_EQ(first > second, true);
    EXPECT_EQ(first <= second, false);
    EXPECT_EQ(first >= second, true);
    EXPECT_EQ(first == second, false);
    EXPECT_EQ(first != second, true);
}