//
// Created by Veniamin_Arefev on 23.09.2022.
//

#ifndef MATRIX_TEMPLATES_STRING_LONG_ARITHMETIC_H
#define MATRIX_TEMPLATES_STRING_LONG_ARITHMETIC_H

#include <string>
#include <utility>


/**
 * Summing positive string
 */
std::string sum_positive_strings(const std::string &first, const std::string &second);

/**
 * Summing string
 */
std::string sum_strings(const std::string &first, const std::string &second);

/**
 * Subtract positive string
 */
std::string subtract_positive_strings(const std::string &first, const std::string &second);

/**
 * Positive string
 */
std::string subtract_strings(const std::string &first, const std::string &second);

/**
 * Multiply positive string
 */
std::string multiply_positive_strings(const std::string &first, const std::string &second);

/**
 * Multiply string
 */
std::string multiply_strings(const std::string &first, const std::string &second);

/**
 * Divide positive string
 */
std::string divide_positive_strings(const std::string &first, const std::string &second);

/**
 * Divide  string
 */
std::string divide_strings(const std::string &first, const std::string &second);

/**
 * Find the greatest common divisor of two strings
 */
std::string greatest_common_divisor(const std::string &first, const std::string &second);

/**
 * Just compare two string.
 * return -1 if first < second
 *         1 if first > second
 *         0 if first == second
 */
int long_str_comparator(const std::string &first, const std::string &second);


class String_with_long_arithmetic {
    std::string my_string;
public:

    /**
     * Main constructor
     */
    explicit String_with_long_arithmetic(std::string in_string) : my_string(std::move(in_string)) {}

    /**
     * Constructor for char *
     */
    explicit String_with_long_arithmetic(const char *in_char_str) : my_string(std::string(in_char_str)) {}

    /**
     * Just operator +=
     */
    String_with_long_arithmetic operator+=(const String_with_long_arithmetic &second);

    /**
    * Just operator +
    */
    friend String_with_long_arithmetic
    operator+(String_with_long_arithmetic first, const String_with_long_arithmetic &second);

    /**
    * Just operator -=
    */
    String_with_long_arithmetic operator-=(const String_with_long_arithmetic &second);

    /**
    * Just operator -
    */
    friend String_with_long_arithmetic
    operator-(String_with_long_arithmetic first, const String_with_long_arithmetic &second);

    /**
    * Just operator *=
    */
    String_with_long_arithmetic operator*=(const String_with_long_arithmetic &second);

    /**
    * Just operator *
    */
    friend String_with_long_arithmetic operator*(String_with_long_arithmetic first,
                                                 const String_with_long_arithmetic &second);

    /**
    * Just operator /=
    */
    String_with_long_arithmetic operator/=(const String_with_long_arithmetic &second);

    /**
    * Just operator /
    */
    friend String_with_long_arithmetic operator/(String_with_long_arithmetic first,
                                                 const String_with_long_arithmetic &second);

    /**
    * Just operator <
    */
    friend bool operator<(const String_with_long_arithmetic &first, const String_with_long_arithmetic &second);
    /**
    * Just operator >
    */
    friend bool operator>(const String_with_long_arithmetic &first, const String_with_long_arithmetic &second);
    /**
    * Just operator <=
    */
    friend bool operator<=(const String_with_long_arithmetic &first, const String_with_long_arithmetic &second);
    /**
    * Just operator >=
    */
    friend bool operator>=(const String_with_long_arithmetic &first, const String_with_long_arithmetic &second);
    /**
    * Just operator ==
    */
    friend bool operator==(const String_with_long_arithmetic &first, const String_with_long_arithmetic &second);
    /**
    * Just operator !=
    */
    friend bool operator!=(const String_with_long_arithmetic &first, const String_with_long_arithmetic &second);
    /**
    * Just prefix operator ++
    */
    String_with_long_arithmetic operator++();
    /**
    * Just postfix operator ++
    */
    String_with_long_arithmetic operator++(int);
    /**
    * Just unary operator -
    */
    String_with_long_arithmetic operator-() const;
    /**
    * Just operator for finding greatest common divisor
    */
    String_with_long_arithmetic friend greatest_common_divisor(const String_with_long_arithmetic &first,
                                                               const String_with_long_arithmetic &second);
    /**
    * Just operator for converting to string
    */
    explicit operator std::string() const;

};

extern String_with_long_arithmetic ZERO_STRING;
extern String_with_long_arithmetic ONE_STRING;
extern String_with_long_arithmetic MINUS_ONE_STRING;


#endif //MATRIX_TEMPLATES_STRING_LONG_ARITHMETIC_H
