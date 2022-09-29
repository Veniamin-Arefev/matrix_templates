//
// Created by Veniamin_Arefev on 23.09.2022.
//

#include <stdexcept>
#include "StringLongArithmetic.h"


std::string sum_positive_strings(const std::string &first, const std::string &second) {
    std::string answer;

    std::string bigger_string = first.length() >= second.length() ? first : second;
    std::string smaller_string = first != bigger_string ? first : second;

    auto it_sm = smaller_string.rbegin();
    bool is_shift = false;
    for (auto it_big = bigger_string.rbegin(); it_big != bigger_string.rend(); it_big++) {
        int cur_char = *it_big + is_shift;
        if (it_sm != smaller_string.rend()) {
            cur_char += *it_sm - '0';
        }
        if (cur_char > '9') {
            is_shift = true;
            answer += static_cast<char>(cur_char - 10);
        } else {
            is_shift = false;
            answer += static_cast<char>(cur_char);
        }
        if (it_sm != smaller_string.rend()) {
            it_sm++;
        }
    }
    if (is_shift) {
        answer += '1';
    }
    std::reverse(answer.begin(), answer.end());
    return answer;
}


std::string sum_strings(const std::string &first, const std::string &second) {
    if (first[0] == '-' && second[0] != '-') {
        std::string normalize = first.substr(1);
        return subtract_positive_strings(second, normalize);
    } else if (first[0] != '-' && second[0] == '-') {
        std::string normalize = second.substr(1);
        return subtract_positive_strings(first, normalize);
    } else if (first[0] == '-' && second[0] == '-') {
        std::string normalize_first = first.substr(1);
        std::string normalize_second = second.substr(1);
        return "-" + sum_positive_strings(normalize_first, normalize_second);
    } else if (first[0] != '-' && second[0] != '-') {
        return sum_positive_strings(first, second);
    } else {
        throw std::invalid_argument("VERY VERY BAD!");
    }
}

std::string subtract_positive_strings(const std::string &first, const std::string &second) {
    std::string answer;

    std::string bigger_string = long_str_comparator(first, second) >= 0 ? first : second;
    std::string smaller_string = first != bigger_string ? first : second;


    auto it_sm = smaller_string.rbegin();
    bool is_shift = false;
    for (auto it_big = bigger_string.rbegin(); it_big != bigger_string.rend(); it_big++) {
        int cur_char = *it_big - is_shift;
        if (it_sm != smaller_string.rend()) {
            cur_char -= *it_sm - '0';
        }
        if (cur_char < '0') {
            is_shift = true;
            answer += static_cast<char>(cur_char + 10);
        } else {
            is_shift = false;
            answer += static_cast<char>(cur_char);
        }
        if (it_sm != smaller_string.rend()) {
            it_sm++;
        }
    }
    while (answer.ends_with('0')) {
        answer.pop_back();
    }
    if (answer.empty()) {
        answer = "0";
    }
    if (long_str_comparator(first, second) < 0) {
        answer += '-';
    }
    std::reverse(answer.begin(), answer.end());
    return answer;
}


std::string subtract_strings(const std::string &first, const std::string &second) {
    if (first[0] == '-' && second[0] != '-') {
        // -a - b = - (a + b)
        std::string normalize_first = first.substr(1);
        return "-" + sum_positive_strings(normalize_first, second);
    } else if (first[0] != '-' && second[0] == '-') {
        // a - -b = a + b
        std::string normalize_second = second.substr(1);
        return "-" + sum_positive_strings(first, normalize_second);
    } else if (first[0] == '-' && second[0] == '-') {
        // -a - -b = b - a
        std::string normalize_first = first.substr(1);
        std::string normalize_second = second.substr(1);
        return subtract_positive_strings(normalize_second, normalize_first);
    } else if (first[0] != '-' && second[0] != '-') {
        // a - b = a - b
        return subtract_positive_strings(first, second);
    } else {
        throw std::invalid_argument("VERY VERY BAD!");
    }
}

std::string multiply_positive_strings(const std::string &first, const std::string &second) {
    std::string answer = "0";
    std::string one = "1";

    std::string step = long_str_comparator(first, second) >= 0 ? first : second;
    std::string steps_to_go = first != step ? first : second;

    while (steps_to_go != "0") {
        answer = sum_strings(answer, step);
        steps_to_go = subtract_strings(steps_to_go, one);
    }

    return answer;
}

std::string multiply_strings(const std::string &first, const std::string &second) {
    if (first[0] == '-' && second[0] != '-') {
        // -a * b = - (a * b)
        std::string normalize_first = first.substr(1);
        std::string result = multiply_positive_strings(normalize_first, second);
        return (result == "0" ? result : "-" + result);
    } else if (first[0] != '-' && second[0] == '-') {
        // a * -b = - (a * b)
        std::string normalize_second = second.substr(1);
        std::string result = multiply_positive_strings(first, normalize_second);
        return (result == "0" ? result : "-" + result);
    } else if (first[0] == '-' && second[0] == '-') {
        // -a * -b =  a * b
        std::string normalize_first = first.substr(1);
        std::string normalize_second = second.substr(1);
        return multiply_positive_strings(normalize_first, normalize_second);
    } else if (first[0] != '-' && second[0] != '-') {
        // a * b = a * b
        return multiply_positive_strings(first, second);
    } else {
        throw std::invalid_argument("VERY VERY BAD!");
    }
}

std::string divide_positive_strings(const std::string &first, const std::string &second) {
    std::string answer = "0";
    std::string one = "1";

    std::string to_zero_string = first;

    while (to_zero_string != "0") {
        to_zero_string = subtract_strings(to_zero_string, second);
        answer = sum_positive_strings(answer, one);
    }

    return answer;
}

std::string divide_strings(const std::string &first, const std::string &second) {
    if (first[0] == '-' && second[0] != '-') {
        // -a / b = - (a / b)
        std::string normalize_first = first.substr(1);
        std::string result = divide_positive_strings(normalize_first, second);
        return (result == "0" ? result : "-" + result);
    } else if (first[0] != '-' && second[0] == '-') {
        // a / -b = - (a / b)
        std::string normalize_second = second.substr(1);
        std::string result = divide_positive_strings(first, normalize_second);
        return (result == "0" ? result : "-" + result);
    } else if (first[0] == '-' && second[0] == '-') {
        // -a / -b =  a / b
        std::string normalize_first = first.substr(1);
        std::string normalize_second = second.substr(1);
        return divide_positive_strings(normalize_first, normalize_second);
    } else if (first[0] != '-' && second[0] != '-') {
        // a / b = a / b
        return divide_positive_strings(first, second);
    } else {
        throw std::invalid_argument("VERY VERY BAD!");
    }
}

std::string greatest_common_divisor(const std::string &first, const std::string &second) {
    std::string bigger_string = long_str_comparator(first, second) >= 0 ? first : second;
    std::string smaller_string = first != bigger_string ? first : second;

    while (bigger_string != smaller_string) {
        if (long_str_comparator(bigger_string, smaller_string) >= 0) {
            bigger_string = subtract_strings(bigger_string, smaller_string);
        } else {
            smaller_string = subtract_strings(smaller_string, bigger_string);
        }
    }
    return bigger_string;
}

int long_str_comparator(const std::string &first, const std::string &second) {
    if (first[0] != '-' && second[0] == '-') {
        return 1;
    } else if (first[0] == '-' && second[0] != '-') {
        return -1;
    } else if (first[0] == '-' && second[0] == '-') {
        std::string normalize_first = first.substr(1);
        std::string normalize_second = second.substr(1);
        return -long_str_comparator(normalize_first, normalize_second);
    } else if (first[0] != '-' && second[0] != '-') {
        if (first.length() != second.length()) {
            return first.length() > second.length() ? 1 : -1;
        }
        int index = 0;
        while ((first[index] == second[index]) && first.length() > index) {
            index++;
        }
        if (index == first.length()) {
            return 0;
        } else {
            return first[index] > second[index] ? 1 : -1;
        }
    } else {
        throw std::invalid_argument("VERY VERY BAD!");
    }
}


String_with_long_arithmetic String_with_long_arithmetic::operator+=(const String_with_long_arithmetic &second) {
    my_string = sum_strings(my_string, second.my_string);
    return *this;
}

String_with_long_arithmetic operator+(String_with_long_arithmetic first, const String_with_long_arithmetic &second) {
    return first += second;
}

String_with_long_arithmetic String_with_long_arithmetic::operator-=(const String_with_long_arithmetic &second) {
    my_string = subtract_strings(my_string, second.my_string);
    return *this;
}

String_with_long_arithmetic operator-(String_with_long_arithmetic first, const String_with_long_arithmetic &second) {
    return first -= second;
}

String_with_long_arithmetic String_with_long_arithmetic::operator*=(const String_with_long_arithmetic &second) {
    my_string = multiply_strings(my_string, second.my_string);
    return *this;
}

String_with_long_arithmetic operator*(String_with_long_arithmetic first, const String_with_long_arithmetic &second) {
    return first *= second;
}

String_with_long_arithmetic String_with_long_arithmetic::operator/=(const String_with_long_arithmetic &second) {
    my_string = divide_strings(my_string, second.my_string);
    return *this;
}

String_with_long_arithmetic operator/(String_with_long_arithmetic first, const String_with_long_arithmetic &second) {
    return first /= second;
}

bool operator<(const String_with_long_arithmetic &first, const String_with_long_arithmetic &second) {
    return long_str_comparator(first.my_string, second.my_string) == -1;
}

bool operator>(const String_with_long_arithmetic &first, const String_with_long_arithmetic &second) {
    return second < first;
}

bool operator<=(const String_with_long_arithmetic &first, const String_with_long_arithmetic &second) {
    return !(first > second);
}

bool operator>=(const String_with_long_arithmetic &first, const String_with_long_arithmetic &second) {
    return !(first < second);
}

bool operator==(const String_with_long_arithmetic &first, const String_with_long_arithmetic &second) {
    return long_str_comparator(first.my_string, second.my_string) == 0;
}

bool operator!=(const String_with_long_arithmetic &first, const String_with_long_arithmetic &second) {
    return !(first == second);
}

String_with_long_arithmetic String_with_long_arithmetic::operator++() {
    *this += String_with_long_arithmetic("1");
    return *this;
}

String_with_long_arithmetic String_with_long_arithmetic::operator++(int) {
    String_with_long_arithmetic copy = *this;
    ++*this;
    return copy;
}

String_with_long_arithmetic String_with_long_arithmetic::operator-() const{
    return String_with_long_arithmetic(my_string.starts_with('-') ? my_string.substr(1) : "-" + my_string);
}

String_with_long_arithmetic greatest_common_divisor(const String_with_long_arithmetic &first,
                                                    const String_with_long_arithmetic &second) {
    return String_with_long_arithmetic(greatest_common_divisor(first.my_string, second.my_string));
}

String_with_long_arithmetic::operator std::string() const {
    return my_string;
}

String_with_long_arithmetic ZERO_STRING = String_with_long_arithmetic("0");
String_with_long_arithmetic ONE_STRING = String_with_long_arithmetic("1");
String_with_long_arithmetic MINUS_ONE_STRING = String_with_long_arithmetic("-1");


