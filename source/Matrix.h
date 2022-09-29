//
// Created by Veniamin_Arefev on 23.09.2022.
//

#ifndef MATRIX_TEMPLATES_MATRIX_H
#define MATRIX_TEMPLATES_MATRIX_H

#include <utility>
#include <string>
#include <stdexcept>
#include <map>
#include <set>
#include <vector>
#include <memory>
#include <fstream>
#include <iostream>
#include <sstream>

#include "Rational_number.h"
#include "Complex_number.h"


constexpr double default_precision = 0.0000001;

class Matrix_coords {
public:
    /**
    * Coordinates for left upper corners
    */
    long long m1, n1;
    /**
    * Coordinates for right lower corner
    */
    long long m2, n2;

    /**
    * Main constructor from 4 values
    */
    Matrix_coords(long long r1, long long c1, long long r2, long long c2) : m1(r1), n1(c1), m2(r2), n2(c2) {
        if (r1 == -1) {
            this->m1 = 1;
        }
        if (c1 == -1) {
            this->n1 = 1;
        }
        if (r1 <= 0 || c1 <= 0 || (r2 < -1 || r2 == 0) || (c2 < -1 || c2 == 0)) {
            throw std::invalid_argument("Arguments must be positive or -1");
        }
        if (r1 > r2 && r2 != -1) {
            throw std::invalid_argument("Must m1 ≤ m2 but got " + std::to_string(r1) + " > " + std::to_string(r2));
        }
        if (c1 > c2 && c2 != -1) {
            throw std::invalid_argument("Must n1 ≤ n2 but got " + std::to_string(c1) + " > " + std::to_string(c2));
        }
    }

    /**
    * Constructor from 2 values, for submatrix from one element
    */
    Matrix_coords(long long r1, long long c1) : Matrix_coords(r1, c1, r1, c1) {}
};


template<typename Elem_type>
class Matrix_proxy;

template<typename Elem_type>
class ElementFixture;


template<typename Elem_type>
class Matrix {

    long long m;
    long long n;

    std::map<std::pair<long long, long long>, Elem_type> my_map;
    std::vector<ElementFixture<Elem_type> *> fixtures;
    std::vector<Matrix_proxy<Elem_type> *> proxies;


public:

    ~Matrix() {
//        for (auto &elem: fixtures) {
//            elem->destroy_main_matrix_ref();
//        }
//        for (auto &elem: proxies) {
//            elem->destroy_main_matrix_ref();
//        }
    }

    /**
    * Main constructor
    */
    explicit Matrix(long long m, long long n) : m(m), n(n) {};

    /**
    * Just copy constructor
    */
    Matrix(const Matrix &matrix) {
        m = matrix.m;
        n = matrix.n;
        my_map = matrix.my_map;
    }

    /**
    * Just copy operator
    */
    auto &operator=(const Matrix &matrix) {
        m = matrix.m;
        n = matrix.n;
        my_map = matrix.my_map;
        return *this;
    }

    /**
    * Just move constructor
    */
    Matrix(Matrix &&matrix) noexcept: m(std::move(matrix.m)), n(std::move(matrix.n)),
                                      my_map(std::move(matrix.my_map)) {}

    /**
    * Just move operator
    */
    auto &operator=(Matrix &&matrix) noexcept {
        m = matrix.m;
        n = matrix.n;
        my_map = std::move(matrix.my_map);
        return *this;
    }

    /**
    * Factory for creating identity matrix
    */
    static Matrix generateIdentity(long long m, double precision = default_precision) {
        if (m <= 0) {
            throw std::invalid_argument("Size must be positive");
        }
        Matrix<Elem_type> matrix(m, m, precision);
        for (int i = 1; i < m; i++) {
            matrix(i, i) = 1;
        }
        return matrix;
    }

    /**
    * Factory for creating matrix filled with specific value
    */
    static Matrix generateFullFilled(long long m, long long n, Elem_type elem, double precision = default_precision) {
        if (m <= 0) {
            throw std::invalid_argument("Size must be positive");
        }
        Matrix<Elem_type> matrix(m, n, precision);
        for (int m_i = 1; m_i < m; m_i++) {
            for (int n_i = 1; n_i < n; n_i++) {
                matrix(m_i, n_i) = elem;
            }
        }
        return matrix;
    }

    /**
    * Just operator +=
    */
    auto operator+=(const Matrix &second) {
        for (const auto &[key, value]: second.my_map) {
            (*this)(key.first, key.second) += value;
        }
        return *this;
    }

    /**
    * Just operator +
    */
    friend auto operator+(Matrix first, const Matrix &second) {
        return first += second;
    }

    /**
    * Just operator -=
    */
    auto operator-=(const Matrix &second) {
        for (const auto &[key, value]: second.my_map) {
            (*this)(key.first, key.second) -= value;
        }
        return *this;
    }

    /**
    * Just operator -
    */
    friend auto operator-(Matrix first, const Matrix &second) {
        return first -= second;
    }

    /**
    * Just operator *=
    */
    auto operator*=(const Matrix &second) {
        if (n != second.m) {
            throw std::invalid_argument("Cant multiply matrix with wrong sizes");
        }
        Matrix result = Matrix(m, second.n);
        for (const auto &[key_first, value_first]: my_map) {
            for (const auto &[key_second, value_second]: second.my_map) {
                if (key_first.second == key_second.first) {
                    result(key_first.first, key_second.second) += value_first * value_second;
                }
            }
        }
        return result;
    }

    /**
    * Just operator *
    */
    friend auto operator*(Matrix first, const Matrix &second) {
        return first *= second;
    }

    /**
    * Just  operator ==
    */
    friend bool operator==(const Matrix &first, const Matrix &second) {
        return (first.m == second.m) &&
               (first.n == second.n) &&
               (first.my_map == second.my_map);
    };

    /**
    * Just  operator !=
    */
    friend bool operator!=(const Matrix &first, const Matrix &second) {
        return !(first == second);
    };

    /**
    * Just unary operator -
    */
    auto operator-() {
        Matrix matrix(m, n);
        for (const auto &[key, value]: my_map) {
            matrix(key.first, key.second) = -value;
        }
        return matrix;
    }

    /**
    * Just unary transpose operator ~
    */
    Matrix operator~() {
        Matrix matrix(n, m);
        for (const auto &[key, value]: my_map) {
            matrix(key.second, key.first) = value;
        }
        return matrix;
    }

    /**
    * Get referenced submatrix from main matrix
    */
    auto operator[](Matrix_coords coords) {
        if (coords.m2 == -1) {
            coords.m2 = m;
        }
        if (coords.n2 == -1) {
            coords.n2 = n;
        }
        if (coords.m2 > m || coords.n2 > n) {
            throw std::out_of_range("Right lower corner out of the main matrix");
        }
        auto elem = Matrix_proxy<Elem_type>(this, coords);
        proxies.push_back(elem);
        return elem;
    }

    /**
    * Check element existence
    */
    bool hasElementOnIndexes(long long coord_m, long long coord_n) {
        return my_map.contains(std::make_pair(coord_m, coord_n));
    }

    /**
    * Get and modify element
    */
    auto operator()(long long coord_m, long long coord_n) {
        if (((coord_m > 0 && coord_m < m)) && ((coord_n > 0 && coord_n < n))) {
            auto elem = ElementFixture<Elem_type>(coord_m, coord_n, this);
            fixtures.push_back(&elem);
            return elem;
        } else {
            throw std::invalid_argument("Arguments must be (positive and less than matrix dimensions) or -1");
        }
    }

//    Elem_type &operator()(long long coord_m, long long coord_n) {
//        return my_map[std::make_pair(coord_m, coord_n)];
//    }

    /**
    * Element setter
    */
    void set_element_by_indexes(long long coord_m, long long coord_n, const Elem_type &elem) {
        if (((coord_m > 0 && coord_m < m)) && ((coord_n > 0 && coord_n < n))) {
            using namespace std;
            if (abs(elem) > default_precision) {
                my_map[std::make_pair(coord_m, coord_n)] = elem;
            } else {
                my_map.erase(std::make_pair(coord_m, coord_n));
            }
        } else {
            throw std::invalid_argument("Arguments must be (positive and less than matrix dimensions) or -1");
        }
    }

    /**
    * Element getter
    */
    Elem_type get_element_by_indexes(long long coord_m, long long coord_n) {
        if (hasElementOnIndexes(coord_m, coord_n)) {
            return my_map[std::make_pair(coord_m, coord_n)];
        } else {
            throw std::runtime_error("Element doesnt exist");
        }
    }

    /**
    * Size getter
    */
    long long get_m() {
        return m;
    }

    /**
    * Size getter
    */
    long long get_n() {
        return n;
    }

    /**
    * Just operator for converting to string
    */
    explicit operator std::string() const {
        std::ostringstream os;
        os << "matrix" << " ";
        if (typeid(Elem_type) == typeid(Rational_number)) {
            os << "rational";
        } else if (typeid(Elem_type) == typeid(Complex_number<>)) {
            os << "complex";
        } else if (typeid(Elem_type) == typeid(bool)) {
            os << "bit";
        } else {
            os << std::string(typeid(Elem_type).name());
        }
        os << std::string(" ") << std::to_string(m)
           << std::string(" ") << std::to_string(n)
           << std::endl;

        for (const auto &[key, value]: my_map) {
            os << std::setfill(' ') << std::setw(10) << (key.first)
               << std::setfill(' ') << std::setw(10) << (key.second)
               << std::string("   ") << value << std::endl;
        }
        return os.str();
    };

    friend std::ostream &operator<<(std::ostream &out, const Matrix &number) {
        out << std::string(number);
        return out;
    }

    void delete_proxy_object(ElementFixture<Elem_type> *elem) {
        std::remove(fixtures.begin(), fixtures.end(), elem);
    }
};


template<typename Elem_type>
class ElementFixture {
    Matrix<Elem_type> *main_matrix;

    long long coord_m, coord_n;

    void set_element(const Elem_type &elem) {
        if (main_matrix != nullptr) {
            main_matrix->set_element_by_indexes(coord_m, coord_n, elem);
        } else {
            throw std::runtime_error("Main matrix is already deleted");
        }
    }

    Elem_type get_element() {
        if (main_matrix != nullptr) {
            if (main_matrix->hasElementOnIndexes(coord_m, coord_n)) {
                return main_matrix->get_element_by_indexes(coord_m, coord_n);
            } else {
                throw std::runtime_error("Element doesnt exist in main matrix");
            }
        } else {
            throw std::runtime_error("Main matrix is already deleted");
        }
    }

    bool check_elem_exists() {
        if (main_matrix != nullptr) {
            if (main_matrix->hasElementOnIndexes(coord_m, coord_n)) {
                return true;
            } else {
                return false;
            }
        } else {
            throw std::runtime_error("Main matrix is already deleted");
        }
    }

public:

    ~ElementFixture() {
        main_matrix->delete_proxy_object(this);
    }

    void destroy_main_matrix_ref() {
        main_matrix = nullptr;
    }

    ElementFixture(const ElementFixture &elem) : main_matrix(elem.main_matrix),
                                                 coord_m(elem.coord_m), coord_n(elem.coord_n) {}

    ElementFixture(long long coord_m, long long coord_n, Matrix<Elem_type> *main_matrix) :
            main_matrix(main_matrix), coord_m(coord_m), coord_n(coord_n) {}


    ElementFixture &operator=(const Elem_type &elem) {
        set_element(elem);
        return *this;
    }

    ElementFixture &operator+=(const Elem_type &elem) {
        set_element(check_elem_exists() ? get_element() + elem : elem);
        return *this;
    }

    ElementFixture &operator-=(const Elem_type &elem) {
        set_element(check_elem_exists() ? get_element() - elem : -elem);
        return *this;
    }

    ElementFixture &operator*=(const Elem_type &elem) {
        set_element(check_elem_exists() ? get_element() * elem : 0);
        return *this;
    }

    ElementFixture &operator/=(const Elem_type &elem) {
        set_element(check_elem_exists() ? get_element() / elem : 0);
        return *this;
    }

    operator Elem_type() {
        return get_element();
    }
};

template<typename Elem_type>
class Matrix_proxy {
    Matrix<Elem_type> *main_matrix;

    Matrix_coords coords;
public:

    ~Matrix_proxy() {
        main_matrix->delete_proxy_object(this);
    }

    void destroy_main_matrix_ref() {
        main_matrix = nullptr;
    }

    Matrix_proxy(const Matrix_proxy &elem) : main_matrix(elem.main_matrix), coords(coords) {}

    Matrix_proxy(Matrix_coords coords, Matrix<Elem_type> *main_matrix) : main_matrix(main_matrix), coords(coords) {}

    auto operator()(long long coord_m, long long coord_n) {
        if (main_matrix != nullptr) {
            if (coord_m > 0 && coord_m < (coords.m2 - coords.m1) && coord_n > 0 && coord_m < (coords.n2 - coords.n1)) {
                return main_matrix->operator()(coord_m + coords.m1, coord_n + coords.n1);
            } else {
                throw std::out_of_range("Matrix proxy coords is out of range");
            }
        } else {
            throw std::runtime_error("Main matrix is already deleted");
        }
    }
};

std::string preprocess_string(std::istream &input_stream) {
    std::string input_string(std::istreambuf_iterator<char>(input_stream), {});

    char prev_char;
    bool was_comment = false;

    std::ostringstream processed;
    for (auto &cur_char: input_string) {
        if (was_comment) {
            if (cur_char != '\n') {
                continue;
            } else {
                was_comment = false;
                prev_char = cur_char;
                continue;
            }
        }
        if (cur_char == '#') {
            was_comment = true;
            continue;
        }
        if (cur_char == ' ' && prev_char == ' ') {
            continue;
        }
        if (cur_char == '\n' && prev_char == '\n') {
            continue;
        }
        processed << cur_char;
        prev_char = cur_char;
    }
    return processed.str();
}

template<typename Elem_type>
Matrix<Elem_type> create_Matrix_from_stream(std::istream &input_stream) {
    std::string prepared_string = preprocess_string(input_stream);

    std::istringstream istringstream(prepared_string);
    std::string line;
    std::getline(istringstream, line);
    std::string matrix_or_vector = line.substr(0, line.find(' '));
    line.erase(0, line.find(' ') + 1);

    if (matrix_or_vector != "matrix") {
        throw std::runtime_error("File type is not matrix");
    }

    std::string expected_elem_type = line.substr(0, line.find(' '));
    line.erase(0, line.find(' ') + 1);

    if (expected_elem_type != "complex" && expected_elem_type != "rational" && expected_elem_type != "bit") {
        throw std::runtime_error("Element type is not supported");
    }

    long long size1 = std::stoll(line.substr(0, line.find(' ')));
    line.erase(0, line.find(' ') + 1);
    long long size2;
    if (line.find(' ') == std::string::npos) {
        size2 = std::stoll(line);
    } else {
        size2 = std::stoll(line.substr(0, line.find(' ')));
    }
    Matrix<Elem_type> matrix(size1, size2);
    while (std::getline(istringstream, line)) {
        long long index1 = std::stoll(line.substr(0, line.find(' ')));
        line.erase(0, line.find(' ') + 1);
        long long index2 = std::stoll(line.substr(0, line.find(' ')));
        line.erase(0, line.find(' ') + 1);
        if (expected_elem_type == "complex") {
            throw std::runtime_error("Not implemented yet");
        } else if (expected_elem_type == "rational") {
            Rational_number number = Rational_number::from_string(line);
            matrix(index1, index2) = number;
        } else if (expected_elem_type == "bit") {
            throw std::runtime_error("Not implemented yet");
        }
    }
    return matrix;
}

template<typename Elem_type>
Matrix<Elem_type> create_Matrix_from_file(std::string &filename) {
    std::ifstream ifstream(filename);
    return create_Matrix_from_stream<Elem_type>(ifstream);
}

#endif //MATRIX_TEMPLATES_MATRIX_H
