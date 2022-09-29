#include <iostream>
#include <iomanip>
#include "Rational_number.h"
#include "Matrix.h"
//#include <format>

int main() {

    Matrix matrix = Matrix<double>(4, 5);

    Matrix_coords coords = Matrix_coords(1, 1, 2, 2);

//    auto prox = matrix[coords];

//    auto test = matrix(1, 10);
//    matrix(1, 4) = 1;
//    matrix(1, 2) = 1;


    std::cout << matrix << std::endl;


    return 0;
}
