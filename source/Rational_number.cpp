//
// Created by Veniamin_Arefev on 24.09.2022.
//

#include "Rational_number.h"
#include "StringLongArithmetic.h"

#include <limits>
#include <stdexcept>

void Rational_number::reduce() {
    String_with_long_arithmetic gcd = greatest_common_divisor(numerator, denominator);
    numerator /= gcd;
    denominator /= gcd;
}

Rational_number::Rational_number(const Rational_number &number) : numerator(number.numerator),
                                                                  denominator(number.denominator) {}


Rational_number &Rational_number::operator=(const Rational_number &number) {
    numerator = number.numerator;
    denominator = number.denominator;
    return *this;
}

Rational_number::Rational_number(Rational_number &&number) noexcept: numerator(std::move(number.numerator)),
                                                                     denominator(std::move(number.denominator)) {}

Rational_number &Rational_number::operator=(Rational_number &&number) noexcept {
    numerator = std::move(number.numerator);
    denominator = std::move(number.denominator);
    return *this;
}

Rational_number Rational_number::operator+=(const Rational_number &second) {
    String_with_long_arithmetic new_numerator = this->numerator * second.denominator +
                                                second.numerator * this->denominator;
    denominator *= second.denominator;
    numerator = new_numerator;
    return *this;
}

Rational_number operator+(Rational_number first, const Rational_number &second) {
    return first += second;
}

Rational_number Rational_number::operator-=(const Rational_number &second) {
    String_with_long_arithmetic new_numerator = this->numerator * second.denominator -
                                                second.numerator * this->denominator;
    denominator *= second.denominator;
    numerator = new_numerator;
    return *this;
}

Rational_number operator-(Rational_number first, const Rational_number &second) {
    return first -= second;
}

Rational_number Rational_number::operator*=(const Rational_number &second) {
    numerator *= second.numerator;
    denominator *= second.denominator;
    return *this;
}

Rational_number operator*(Rational_number first, const Rational_number &second) {
    return first *= second;
}

Rational_number Rational_number::operator/=(const Rational_number &second) {
    numerator *= second.denominator;
    denominator *= second.numerator;
    if (denominator < ZERO_STRING) {
        numerator *= MINUS_ONE_STRING;
        denominator *= MINUS_ONE_STRING;
    }
    return *this;
}

Rational_number operator/(Rational_number first, const Rational_number &second) {
    return first /= second;
}

bool operator<(const Rational_number &first, const Rational_number &second) {
    Rational_number difference = first - second;
    return difference.numerator < ZERO_STRING;
}

bool operator>(const Rational_number &first, const Rational_number &second) {
    return second < first;
}

bool operator<=(const Rational_number &first, const Rational_number &second) {
    return !(first > second);
}

bool operator>=(const Rational_number &first, const Rational_number &second) {
    return !(first < second);
}

bool operator==(const Rational_number &first, const Rational_number &second) {
    return first.numerator == second.numerator && first.denominator == second.denominator;
}

bool operator!=(const Rational_number &first, const Rational_number &second) {
    return !(first == second);
}

Rational_number Rational_number::operator++() {
    *this += Rational_number("1");
    return *this;
}

Rational_number Rational_number::operator++(int) {
    Rational_number copy = *this;
    ++*this;
    return copy;
}

Rational_number Rational_number::operator-() const {
    return Rational_number(-numerator, denominator);
}

Rational_number::operator int() {
    reduce();
    if (denominator != ONE_STRING) {
        throw std::invalid_argument("Denominator is not zero");
    }
    return std::stoi(std::string(numerator));
}

Rational_number::operator long() {
    reduce();
    if (denominator != ONE_STRING) {
        throw std::invalid_argument("Denominator is not zero");
    }
    return std::stol(std::string(numerator));
}

Rational_number::operator short() {
    int value = int(*this);
    if (value >= std::numeric_limits<short>::min() && value <= std::numeric_limits<short>::max()) {
        return short(value);
    } else {
        throw std::out_of_range("Numerator is out of short range");
    }
}


Rational_number::operator std::string() const {
    return std::string("<" + std::string(numerator) + "/" + std::string(denominator) + ">");
}

Rational_number Rational_number::from_string(std::string input) {
    std::string numerator;
    std::string denominator = "1";
    if (input.find('/') == std::string::npos) { //not found
        numerator = input.substr(input.find('<') + 1, input.find('>') - input.find('<') - 1);
    } else {
        numerator = input.substr(input.find('<') + 1, input.find('/') - input.find('<') - 1);
        denominator = input.substr(input.find('/') + 1, input.find('>') - input.find('/') - 1);
    }
    numerator.erase(remove_if(numerator.begin(), numerator.end(), isspace), numerator.end());
    denominator.erase(remove_if(denominator.begin(), denominator.end(), isspace), denominator.end());
    return Rational_number(numerator, denominator);
}

std::ostream &operator<<(std::ostream &out, const Rational_number &number) {
    std::string output = std::string(number);
    out << output;
    return out;
}


Rational_number Rational_number::floor() {
    String_with_long_arithmetic integer = String_with_long_arithmetic("0");
    String_with_long_arithmetic cur_numerator = numerator;
    while (cur_numerator > denominator) {
        integer -= ONE_STRING;
        cur_numerator -= denominator;
    }
    return Rational_number(std::string(integer));


}

Rational_number Rational_number::round() {
    Rational_number answer = floor();
    Rational_number leftover = *this - answer;
    if (leftover >= Rational_number("1", "2")) {
        answer++;
    }
    return answer;
}

Rational_number abs(const Rational_number &number) {
    if (number > 0) {
        return number;
    } else {
        return -number;
    }
}

