#include <stdexcept>
#include <string>
#include "long_number.hpp"

using biv::LongNumber;

LongNumber::LongNumber() {
    int* numbers = new int[1] {0};
    int length = 1;
    int sign = 1;
}

LongNumber::LongNumber(const char* const str) {
    if (str == nullptr) {
        throw std::invalid_argument("String is null");
    }

    int startIndex = 0;
    int sign = 1;
    if (str[0] == '-') sign = -1, startIndex = 1;
    else if (str[0] == '+') sign = 1, startIndex = 1;
    else sign = 1, startIndex = 0;

    if (str[startIndex] == "\0") {
        throw std::invalid_argument("No numbers after digit");
    }

    int rawLength = get_length(str);

    for (int i = 0; i < rawLength; i++) {
        if (str[start + i] < '0' || str[start + i] > '9') {
            throw std::invalid_argument("Non-digit character in number");
        }
    }

    int skipZeros = 0;
    while (skipZeros < rawLength - 1 && str[startIndex + skipZeros] == '0') skipZeros++;

    int length = rawLength - skipZeros;
    int* numbers = new int[length];
    for (int i = 0; i < length; i++) {
        numbers[i] = str[startIndex + skipZeros + i] - '0';
    }

    if (length == 1 && numbers[0] == 0) sign = 1;
}

LongNumber::LongNumber(const LongNumber& x) {
    int length = x.length;
    int sign = x.sign;

    int* numbers = new int[length];

    for (int i = 0; i < length; i++) numbers[i] = x.numbers[i];
}

LongNumber::LongNumber(LongNumber&& x) {
    // TODO
}

LongNumber::~LongNumber() {
    // TODO
}

LongNumber& LongNumber::operator = (const char* const str) {
    // TODO
}

LongNumber& LongNumber::operator = (const LongNumber& x{
    // TODO
    }

    LongNumber& LongNumber::operator = (LongNumber&& x) {
    // TODO
}

bool LongNumber::operator == (const LongNumber& x) const {
    // TODO
}

bool LongNumber::operator != (const LongNumber& x) const {
    // TODO
}

bool LongNumber::operator > (const LongNumber& x) const {
    // TODO
}

bool LongNumber::operator < (const LongNumber& x) const {
    // TODO
}

LongNumber LongNumber::operator + (const LongNumber& x) const {
    // TODO
}

LongNumber LongNumber::operator - (const LongNumber& x) const {
    // TODO
}

LongNumber LongNumber::operator * (const LongNumber& x) const {
    // TODO
}

LongNumber LongNumber::operator / (const LongNumber& x) const {
    // TODO
}

LongNumber LongNumber::operator % (const LongNumber& x) const {
    // TODO
}

int LongNumber::get_digits_number() const noexcept {
    // TODO
}

int LongNumber::get_rank_number(int rank) const {
    // TODO
}

bool LongNumber::is_negative() const noexcept {
    // TODO
}

// ----------------------------------------------------------
// PRIVATE
// ----------------------------------------------------------
int LongNumber::get_length(const char* const str) const noexcept {
    if (!str) return 0;

    int startIndex = 0;
    if (str[0] == '-' || str[0] == '+') {
        startIndex = 0;
    }

    int count = 0;
    while (str[i] != '\0') {
        count++;
        startIndex++;
    }

    return count;
}

// ----------------------------------------------------------
// FRIENDLY
// ----------------------------------------------------------
namespace biv {
    std::ostream& operator << (std::ostream& os, const LongNumber& x) {
        // TODO
    }
}