//
// Created by Veniamin_Arefev on 24.09.2022.
//

#ifndef MATRIX_TEMPLATES_RATIONAL_NUMBER_H
#define MATRIX_TEMPLATES_RATIONAL_NUMBER_H

#include <string>
#include <utility>
#include "StringLongArithmetic.h"

class Rational_number {
    String_with_long_arithmetic numerator;
    String_with_long_arithmetic denominator;

    void reduce();


public:

    /**
    * Main constructor from String_with_long_arithmetic
    */
    explicit Rational_number(const String_with_long_arithmetic & numerator,
                             const String_with_long_arithmetic & denominator) :
            numerator(numerator), denominator(denominator) {}

    /**
    * Main constructor from string
    */
    explicit Rational_number(const std::string & numerator = "0",
                             const std::string & denominator = "1") :
            Rational_number(String_with_long_arithmetic(numerator),
                            String_with_long_arithmetic(denominator)) {}

    /**
    * Just copy constructor
    */
    Rational_number(const Rational_number &number);

    /**
    * Just copy operator
    */
    Rational_number &operator=(const Rational_number &number);

    /**
    * Just move constructor
    */
    Rational_number(Rational_number &&number) noexcept;

    /**
    * Just move operator
    */
    Rational_number &operator=(Rational_number &&number) noexcept;

    /**
    * Main constructor from short
    */
    explicit Rational_number(short number) : Rational_number(std::to_string(number)) {}

    /**
    * Constructor from int
    */
    explicit Rational_number(int number) : Rational_number(std::to_string(number)) {}

    /**
    * Constructor from long
    */
    explicit Rational_number(long number) : Rational_number(std::to_string(number)) {}

    /**
    * Main constructor from long long
    */
    Rational_number(long long number) : Rational_number(std::to_string(number)) {}

    /**
    * Constructor from unsigned short
    */
    explicit Rational_number(unsigned short number) : Rational_number(std::to_string(number)) {}

    /**
    * Constructor from unsigned int
    */
    explicit Rational_number(unsigned int number) : Rational_number(std::to_string(number)) {}

    /**
    * Constructor from unsigned long
    */
    explicit Rational_number(unsigned long number) : Rational_number(std::to_string(number)) {}

    /**
    * Constructor from unsigned long long
    */
    explicit Rational_number(unsigned long long number) : Rational_number(std::to_string(number)) {}

    /**
     * Just operator +=
     */
    Rational_number operator+=(const Rational_number &second);

    /**
     * Just operator +
     */
    friend Rational_number operator+(Rational_number first, const Rational_number &second);

    /**
     * Just operator -=
    */
    Rational_number operator-=(const Rational_number &second);

    /**
     * Just operator -
     */
    friend Rational_number operator-(Rational_number first, const Rational_number &second);

    /**
     * Just operator *=
     */
    Rational_number operator*=(const Rational_number &second);

    /**
     * Just operator *
     */
    friend Rational_number operator*(Rational_number first, const Rational_number &second);

    /**
     * Just operator /=
     */
    Rational_number operator/=(const Rational_number &second);

    /**
     * Just operator /
     */
    friend Rational_number operator/(Rational_number first, const Rational_number &second);

    /**
    * Just operator <
    */
    friend bool operator<(const Rational_number &first, const Rational_number &second);

    /**
    * Just operator >
    */
    friend bool operator>(const Rational_number &first, const Rational_number &second);

    /**
    * Just operator <=
    */
    friend bool operator<=(const Rational_number &first, const Rational_number &second);

    /**
    * Just operator >=
    */
    friend bool operator>=(const Rational_number &first, const Rational_number &second);

    /**
    * Just operator ==
    */
    friend bool operator==(const Rational_number &first, const Rational_number &second);

    /**
    * Just operator !=
    */
    friend bool operator!=(const Rational_number &first, const Rational_number &second);

    /**
    * Just prefix operator ++
    */
    Rational_number operator++();

    /**
    * Just postfix operator ++
    */
    Rational_number operator++(int);

    /**
    * Just unary operator -
    */
    Rational_number operator-() const;

    /**
    * Get integer from Rational_number
    */
    Rational_number floor();

    /**
    * Round Rational_number to integer
    */
    Rational_number round();

    /**
    * Convert to int
    */
    explicit operator int();

    /**
    * Convert to long
    */
    explicit operator long();

    /**
    * Convert to short
    */
    explicit operator short();

    /**
    * Convert to string
    */
    explicit operator std::string() const;

    /**
    * Convert from string
    */
    static Rational_number from_string(std::string);

    /**
    * Calculate absolute value
    */
    friend Rational_number abs(const Rational_number &number);

    /**
    * Print Rational_number to stream
    */
    friend std::ostream &operator<<(std::ostream &out, const Rational_number &number);
};

#endif //MATRIX_TEMPLATES_RATIONAL_NUMBER_H
