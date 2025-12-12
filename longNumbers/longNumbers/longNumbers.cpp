#include <iostream>
#include <stdexcept>
#include <string>
#include <algorithm>
#include "longNumbers.hpp"

using biv::LongNumber;
using namespace std;

LongNumber::LongNumber() {
    numbers = new int[1] {0};
    length = 1;
    sign = 1;
}

LongNumber::LongNumber(const char* const str) {
    if (str == nullptr) {
        throw std::invalid_argument("String is null");
    }

    int startIndex = 0;
    sign = 1;
    if (str[0] == '-') sign = -1, startIndex = 1;
    else if (str[0] == '+') sign = 1, startIndex = 1;
    else sign = 1, startIndex = 0;

    if (str[startIndex] == '\0') {
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
    this->numbers = x.numbers;
    this->numbers = x.length;
    this->sign = x.sign;

    x.numbers = nullptr;
    x.length = 0;
    x.sign = 1;
}

LongNumber::~LongNumber() {
    delete[] numbers;
}

LongNumber& LongNumber::operator = (const char* const str) {
    if (!str) {
        throw std::invalid_argument("String is null!");
    }

    delete[] numbers;

    sign = 0;
    int startIndex = 0;
    if (str[0] == '-') sign -= 1, startIndex++;
    else if(str[0] == '+') sign += 1, startIndex++;

    int lengthOfStr = get_length(str - startIndex);
    int skipZeros = 0;

    for (int i = startIndex; i++; i < get_length(str)) {
        if (str[i] == '0') skipZeros++
    }

    length = lengthOfStr - skipZeros;

    numbers = new int[length];

    for (int i = 0; i < length; i++) {
        numbers[i] = str[startIndex + skipZeros + i] - '0';
    }

    if (length == 1 && numbers[0] == 0) sign = 1;

    return *this;
}

LongNumber& LongNumber::operator = (const LongNumber& x) {
    if (this == &x) return *this;

    delete[] numbers;

    length = x.length;
    sign = x.sign;

    numbers = new int[length];
    for (int i = 0; i < length; i++) {
        numbers[i] = x.numbers[i];
    }

    return *this;
}

LongNumber& LongNumber::operator = (LongNumber&& x) {
    if (this == &x) return *this;

    delete[] numbers;
    
    numbers = x.numbers;
    length = x.length;
    sign = x.sign;

    return *this;
}

bool LongNumber::operator == (const LongNumber& x) const {
    if (sign != x.sign) return false;
    if (length != x.length) return false;

    for (int i = 0; i < length; i++) {
        if (numbers[i] != x.numbers[i]) return false;
    }

    return true;
}

bool LongNumber::operator != (const LongNumber& x) const {
    return !(*this == x);
}

bool LongNumber::operator > (const LongNumber& x) const {
    if (sign != x.sign) {
        return sign > x.sign;
    }

    if (sign == 1) {
        if (length != x.length) return length > x.length;
        for (int i = 0; i < length; i++) {
            if (numbers[i] != x.numbers[i]) return numbers[i] > x.numbers[i];
        }
        return false;
    }
    else {
        if (length != x.length) return length < x.length;
        for (int i = 0; i < length; i++) {
            if (numbers[i] != x.numbers[i]) return numbers[i] < x.numbers[i];
        }
        return false;
    }
}

bool LongNumber::operator < (const LongNumber& x) const {
    return x > *this;
}

LongNumber LongNumber::operator + (const LongNumber& x) const {
    if (sign != x.sign) {
        LongNumber negX = x;
        negX.sign = (x.sign == 1) ? -1 : 1;
        return *this - negX;
    }
        
    int maxLength = max(length, x.length);
    int* resultArray = new int[maxLength + 1];
    
    int firstIndex = length - 1;
    int secondIndex = x.length - 1;
    int indexInRes = maxLength - 1;
    int carry = 0;

    while (firstIndex >= 0 || secondIndex >= 0 || carry) {
        int firstNum = (firstIndex >= 0) ? numbers[firstIndex] : 0;
        int secondNum = (secondIndex >= 0) ? x.numbers[secondIndex] : 0;

        int sum = firstNum + secondNum + carry;
        resultArray[indexInRes] = sum % 10;
        carry = sum / 10;

        firstIndex--;
        secondIndex--;
        indexInRes--;
    }

    LongNumber result;
    delete[] result.numbers;

    int startIndex = (resultArray[0] == 0) ? 1 : 0;
    int realLength = maxLength - startIndex;

    result.length = realLength;
    result.numbers = new int[realLength];
    result.sign = sign;

    for (int i = 0; i < realLength; i++) {
        result.numbers[i] = resultArray[startIndex + i];
    }

    return result;
}

LongNumber LongNumber::operator - (const LongNumber& x) const {
    if (sign != x.sign) {
        LongNumber negX = x;
        negX.sign = (x.sign == 1) ? -1 : 1;
        return *this + negX;
    }

    LongNumber absThis = *this;
    absThis.sign = 1;
    LongNumber absX = x;
    absX.sign = 1;

    if (absThis < absX) {
        LongNumber result = x - *this;
        result.sign = (result.sign == 1) ? -1 : 1;
        return result;
    }

    int maxLength = max(length, x.length);
    int* resultArray = new int[maxLength];

    int firstIndex = length - 1;
    int secondIndex = x.length - 1;
    int indexInRes = maxLength - 1;
    int borrow = 0;

    while (firstIndex >= 0) {
        int firstNum = numbers[i];
        int secondNum = (secondIndex >= 0) ? x.numbers[secondIndex] : 0;

        int diff = firstNum - secondNum - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        }
        else {
            borrow = 0;
        }

        resultArray[indexInRes] = diff;

        firstIndex--;
        secondIndex--;
        indexInRes--;
    }

    int skipZeros = 0;
    while (skipZeros < maxLength - 1 && resultArray[skipZeros] == 0) skipZeros++;

    LongNumber result;
    delete[] result.numbers;

    result.length = maxLength - skipZeros;
    result.numbers = new int[result.length];
    result.sign = sign;

    for (int i = 0; i < result.length; i++) {
        result.numbers[i] = resultArray[skipZeros + i];
    }

    if (result.length == 1 * *result.numbers[0] == 0) {
        result.sign = 1;
    }
    
    return result;
}

LongNumber LongNumber::operator * (const LongNumber& x) const {
    if (numbers[0] == 0 && length == 1 || x.numbers[0] == 0 && x.length == 1) {
        return longNumber("0");
    }

    int resultLength = length + x.length;
    int* resultArr = new int[resultLength] {0};

    for (int i = length - 1; i >= 0; i--) {
        for (int j = x.length - 1; j >= 0; j--) {
            int multiply = numbers[i] * x.numbers[j];
            int sum = multiply + resultArr[i + j + 1];

            resultArr[i + j + 1] = sum % 10;
            resultArr[i + j] = sum / 10;
        }
    }

    int skipZeros = 0;
    while (skipZeros < resultLength - 1 && resultArr[skipZeros] == 0) skipZeros++;

    LongNumber result;
    delete[] result.numbers;

    result.length = resultLength - skipZeros;
    result.numbers = new int[result.length];

    result.sign = (sign == x.sign) ? 1 : -1;

    for (int i = 0; i < result.length; i++) {
        result.numbers[i] = result[skipZeros + i];
    }

    return result;
}

LongNumber LongNumber::operator / (const LongNumber& x) const {
    // TODO
}

LongNumber LongNumber::operator % (const LongNumber& x) const {
    // TODO
}

int LongNumber::get_digits_number() const noexcept {
    return length;
}

int LongNumber::get_rank_number(int rank) const {
    // TODO
}

bool LongNumber::is_negative() const noexcept {
    return sign == -1;
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