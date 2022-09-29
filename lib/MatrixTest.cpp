//
// Created by Veniamin_Arefev on 23.09.2022.
//
#include "gtest/gtest.h"

#include "Matrix.h"
#include <string>

TEST(MatrixTestSuite, Matrix_munus_and_transpose) {
    Matrix matrix = Matrix<double>(4, 11);

    matrix(1, 10) = 1;
    matrix(1, 4) = 1;
    matrix(1, 2) = 1;

    std::string result1 = "matrix double 4 11\n         1         2   1\n         1         4   1\n         1        10   1\n";
    std::string result2 = "matrix double 4 11\n         1         2   -1\n         1         4   -1\n         1        10   -1\n";
    std::string result3 = "matrix double 11 4\n         2         1   1\n         4         1   1\n        10         1   1\n";

    EXPECT_EQ(std::string(matrix), result1);
    EXPECT_EQ(std::string(-matrix), result2);
    EXPECT_EQ(std::string(~matrix), result3);
}

TEST(MatrixTestSuite, Matrix_double_transpose) {
    Matrix matrix = Matrix<double>(4, 11);

    matrix(1, 10) = 1;
    matrix(1, 4) = 1;
    matrix(1, 2) = 1;

    Matrix matrix1 = -matrix;
    matrix1 = -matrix1;

    EXPECT_EQ(matrix, matrix1);
}

TEST(MatrixTestSuite, Matrix_sum) {
    Matrix matrix1 = Matrix<double>(4, 5);
    Matrix matrix2 = Matrix<double>(4, 5);

    matrix1(1, 2) = 10;
    matrix1(1, 3) = 12;
    matrix1(2, 1) = 1;
    matrix1(2, 3) = 2;

    matrix2(1, 1) = 2;
    matrix2(1, 3) = 8;
    matrix2(2, 1) = 5;
    matrix2(2, 2) = 1;

    std::string expected_result = "matrix double 4 5\n         1         1   2\n         1         2   10\n         1         3   20\n         2         1   6\n         2         2   1\n         2         3   2\n";

    EXPECT_EQ(std::string(matrix1 + matrix2), expected_result);
}

TEST(MatrixTestSuite, Matrix_substruct) {
    Matrix matrix1 = Matrix<double>(4, 5);
    Matrix matrix2 = Matrix<double>(4, 5);

    matrix1(1, 2) = 10;
    matrix1(1, 3) = 12;
    matrix1(2, 1) = 1;
    matrix1(2, 3) = 2;

    matrix2(1, 1) = 2;
    matrix2(1, 3) = 8;
    matrix2(2, 1) = 5;
    matrix2(2, 2) = 1;

    std::string expected_result = "matrix double 4 5\n         1         1   -2\n         1         2   10\n         1         3   4\n         2         1   -4\n         2         2   -1\n         2         3   2\n";

    EXPECT_EQ(std::string(matrix1 - matrix2), expected_result);
}

TEST(MatrixTestSuite, Matrix_myltiply) {
    Matrix matrix1 = Matrix<double>(3, 4);
    Matrix matrix2 = Matrix<double>(4, 3);

    matrix1(1, 2) = 10;
    matrix1(1, 3) = 12;
    matrix1(2, 1) = 1;
    matrix1(2, 3) = 2;

    matrix2(1, 1) = 2;
    matrix2(1, 2) = 5;
    matrix2(2, 2) = 1;
    matrix2(3, 1) = 8;

    std::string expected_result = "matrix double 3 3\n         1         1   96\n         1         2   10\n         2         1   18\n         2         2   5\n";

    EXPECT_EQ(std::string(matrix1 * matrix2), expected_result);
}