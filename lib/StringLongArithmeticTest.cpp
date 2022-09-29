//
// Created by Veniamin_Arefev on 23.09.2022.
//

#include "gtest/gtest.h"
#include "StringLongArithmetic.h"

TEST(SumStringsTestSuite, SumStrings) {
    std::string first = "123";
    std::string second = "123";
    std::string result = "246";
    EXPECT_EQ(sum_strings(first, second), result);
    EXPECT_EQ(sum_strings(second, first), result);
}

TEST(SumStringsTestSuite, SumStringsOverflow) {
    std::string first = "999";
    std::string second = "111";
    std::string result = "1110";
    EXPECT_EQ(sum_strings(first, second), result);
    EXPECT_EQ(sum_strings(second, first), result);
}

TEST(SumStringsTestSuite, SumStringsDifferentLen) {
    std::string first = "1";
    std::string second = "123456788";
    std::string result = "123456789";
    EXPECT_EQ(sum_strings(first, second), result);
    EXPECT_EQ(sum_strings(second, first), result);
}


TEST(SubtractStringsTestSuite, SubtractStrings) {
    std::string first = "123";
    std::string second = "1";
    std::string result = "122";
    EXPECT_EQ(subtract_strings(first, second), result);
}

TEST(SubtractStringsTestSuite, SubtractStringsToZero) {
    std::string first = "123";
    std::string second = "123";
    std::string result = "0";
    EXPECT_EQ(subtract_strings(first, second), result);
}

TEST(SubtractStringsTestSuite, SubtractStringsOverflow) {
    std::string first = "1000";
    std::string second = "1";
    std::string result = "999";
    EXPECT_EQ(subtract_strings(first, second), result);
}

TEST(SubtractStringsTestSuite, SubtractStringsToNegative1) {
    std::string first = "1";
    std::string second = "2";
    std::string result = "-1";
    EXPECT_EQ(subtract_strings(first, second), result);
}

TEST(SubtractStringsTestSuite, SubtractStringsToNegative2) {
    std::string first = "123456789";
    std::string second = "9999999999";
    std::string result = "-9876543210";
    EXPECT_EQ(subtract_strings(first, second), result);
}

TEST(ComparatorTestSuite, ComparatorPosivite1) {
    std::string first = "1";
    std::string second = "2";
    EXPECT_EQ(long_str_comparator(first, second), -1);
    EXPECT_EQ(long_str_comparator(second, first), 1);
}

TEST(ComparatorTestSuite, ComparatorPosivite2) {
    std::string first = "1";
    std::string second = "12";
    EXPECT_EQ(long_str_comparator(first, second), -1);
    EXPECT_EQ(long_str_comparator(second, first), 1);
}

TEST(ComparatorTestSuite, ComparatorPosivite3) {
    std::string first = "90909090";
    std::string second = "99900000";
    EXPECT_EQ(long_str_comparator(first, second), -1);
    EXPECT_EQ(long_str_comparator(second, first), 1);
}

TEST(ComparatorTestSuite, ComparatorNegative1) {
    std::string first = "-1";
    std::string second = "-2";
    EXPECT_EQ(long_str_comparator(first, second), 1);
    EXPECT_EQ(long_str_comparator(second, first), -1);
}

TEST(ComparatorTestSuite, ComparatorNegative2) {
    std::string first = "-1";
    std::string second = "-12";
    EXPECT_EQ(long_str_comparator(first, second), 1);
    EXPECT_EQ(long_str_comparator(second, first), -1);
}

TEST(ComparatorTestSuite, ComparatorNegative3) {
    std::string first = "-90909090";
    std::string second = "-99900000";
    EXPECT_EQ(long_str_comparator(first, second), 1);
    EXPECT_EQ(long_str_comparator(second, first), -1);
}

TEST(ComparatorTestSuite, Comparator1) {
    std::string first = "90909090";
    std::string second = "-99900000";
    EXPECT_EQ(long_str_comparator(first, second), 1);
    EXPECT_EQ(long_str_comparator(second, first), -1);
}

TEST(MultiplyStringsTestSuite, MultiplyPositive1) {
    std::string first = "100";
    std::string second = "20";
    std::string result = "2000";
    EXPECT_EQ(multiply_strings(first, second), result);
    EXPECT_EQ(multiply_strings(second, first), result);
}

TEST(MultiplyStringsTestSuite, MultiplyPositive2) {
    std::string first = "100000000000";
    std::string second = "20";
    std::string result = "2000000000000";
    EXPECT_EQ(multiply_strings(first, second), result);
    EXPECT_EQ(multiply_strings(second, first), result);
}

TEST(MultiplyStringsTestSuite, MultiplyNegative1) {
    std::string first = "-100";
    std::string second = "-20";
    std::string result = "2000";
    EXPECT_EQ(multiply_strings(first, second), result);
    EXPECT_EQ(multiply_strings(second, first), result);
}

TEST(MultiplyStringsTestSuite, MultiplyNegative2) {
    std::string first = "-100000000000";
    std::string second = "-20";
    std::string result = "2000000000000";
    EXPECT_EQ(multiply_strings(first, second), result);
    EXPECT_EQ(multiply_strings(second, first), result);
}

TEST(MultiplyStringsTestSuite, MultiplyToZero1) {
    std::string first = "100000000000";
    std::string second = "0";
    std::string result = "0";
    EXPECT_EQ(multiply_strings(first, second), result);
    EXPECT_EQ(multiply_strings(second, first), result);
}

TEST(MultiplyStringsTestSuite, MultiplyToZero2) {
    std::string first = "-100000000000";
    std::string second = "0";
    std::string result = "0";
    EXPECT_EQ(multiply_strings(first, second), result);
    EXPECT_EQ(multiply_strings(second, first), result);
}

TEST(DivisorTestSuite, DivisorPositive1) {
    std::string first = "100";
    std::string second = "20";
    std::string result = "5";
    EXPECT_EQ(divide_strings(first, second), result);
}

TEST(DivisorTestSuite, DivisorPositive2) {
    std::string first = "333";
    std::string second = "3";
    std::string result = "111";
    EXPECT_EQ(divide_strings(first, second), result);
}

TEST(DivisorTestSuite, DivisorPositive3) {
    std::string first = "1";
    std::string second = "1";
    std::string result = "1";
    EXPECT_EQ(divide_strings(first, second), result);
}

TEST(DivisorTestSuite, DivisorNegative1) {
    std::string first = "-100";
    std::string second = "-20";
    std::string result = "5";
    EXPECT_EQ(divide_strings(first, second), result);
}

TEST(DivisorTestSuite, DivisorNegative2) {
    std::string first = "-333";
    std::string second = "-3";
    std::string result = "111";
    EXPECT_EQ(divide_strings(first, second), result);
}

TEST(DivisorTestSuite, DivisorNegative3) {
    std::string first = "-1";
    std::string second = "-1";
    std::string result = "1";
    EXPECT_EQ(divide_strings(first, second), result);
}

TEST(DivisorTestSuite, Divisor1) {
    std::string first = "-100";
    std::string second = "20";
    std::string result = "-5";
    EXPECT_EQ(divide_strings(first, second), result);
}

TEST(DivisorTestSuite, Divisor2) {
    std::string first = "-333";
    std::string second = "3";
    std::string result = "-111";
    EXPECT_EQ(divide_strings(first, second), result);
}

TEST(DivisorTestSuite, Divisor3) {
    std::string first = "-1";
    std::string second = "1";
    std::string result = "-1";
    EXPECT_EQ(divide_strings(first, second), result);
}




