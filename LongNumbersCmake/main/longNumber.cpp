#include <iostream>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <vector>
#include "longNumber.hpp"

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

    int rawLength = get_length(str + startIndex);

    for (int i = 0; i < rawLength; i++) {
        if (str[startIndex + i] < '0' || str[startIndex + i] > '9') {
            throw std::invalid_argument("Non-digit character in number");
        }
    }

    int skipZeros = 0;
    while (skipZeros < rawLength - 1 && str[startIndex + skipZeros] == '0') skipZeros++;

    length = rawLength - skipZeros;
    numbers = new int[length];
    for (int i = 0; i < length; i++) {
        numbers[i] = str[startIndex + skipZeros + i] - '0';
    }

    if (length == 1 && numbers[0] == 0) sign = 1;
}

LongNumber::LongNumber(const LongNumber& x) {
    length = x.length;
    sign = x.sign;

    numbers = new int[length];

    for (int i = 0; i < length; i++) numbers[i] = x.numbers[i];
}

LongNumber::LongNumber(LongNumber&& x) {
    this->numbers = x.numbers;
    this->length = x.length;
    this->sign = x.sign;

    x.numbers = nullptr;
    x.length = 0;
    x.sign = 1;
}

LongNumber::~LongNumber() {
    if (numbers != nullptr) {
        delete[] numbers;
        numbers = nullptr;
    }
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

    int lengthOfStr = get_length(str + startIndex);
    int skipZeros = 0;
    int totalLength = get_length(str + startIndex);
    while (skipZeros < totalLength - 1 && str[startIndex + skipZeros] == '0') {
        ++skipZeros;
    }
    length = totalLength - skipZeros;

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

    x.numbers = nullptr;
    x.length = 0;
    x.sign = 1;

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
        negX.sign *= -1;
        return *this - negX;
    }

    int maxLen = std::max(length, x.length);
    int* temp = new int[maxLen + 1];
    int i = length - 1, j = x.length - 1, k = maxLen, carry = 0;

    while (i >= 0 || j >= 0 || carry) {
        int sum = carry + (i >= 0 ? numbers[i--] : 0) + (j >= 0 ? x.numbers[j--] : 0);
        temp[k--] = sum % 10;
        carry = sum / 10;
    }

    int start = k + 1;
    int newLen = (maxLen + 1) - start;

    LongNumber result;
    delete[] result.numbers;
    result.length = newLen;
    result.sign = sign;
    result.numbers = new int[newLen];
    for (int idx = 0; idx < newLen; ++idx) result.numbers[idx] = temp[start + idx];

    delete[] temp;
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
        int firstNum = numbers[firstIndex];
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

    result.length = maxLength - skipZeros;
    result.numbers = new int[result.length];
    result.sign = sign;

    for (int i = 0; i < result.length; i++) {
        result.numbers[i] = resultArray[skipZeros + i];
    }

    if (result.length == 1 && result.numbers[0] == 0) {
        result.sign = 1;
    }
    
    return result;
}

LongNumber LongNumber::operator * (const LongNumber& x) const {
    if ((length == 1 && numbers[0] == 0) || (x.length == 1 && x.numbers[0] == 0)) {
        return LongNumber("0");
    }

    int resLen = length + x.length;
    int* resArr = new int[resLen]();

    for (int i = length - 1; i >= 0; i--) {
        for (int j = x.length - 1; j >= 0; j--) {
            int mul = numbers[i] * x.numbers[j] + resArr[i + j + 1];
            resArr[i + j + 1] = mul % 10;
            resArr[i + j] += mul / 10;
        }
    }

    int skip = 0;
    while (skip < resLen - 1 && resArr[skip] == 0) skip++;

    LongNumber result;
    delete[] result.numbers;
    result.length = resLen - skip;
    result.sign = (sign == x.sign) ? 1 : -1;
    result.numbers = new int[result.length];
    for (int i = 0; i < result.length; i++) result.numbers[i] = resArr[skip + i];

    delete[] resArr;
    return result;
}

LongNumber LongNumber::operator / (const LongNumber& x) const {
    if (x.length == 1 && x.numbers[0] == 0) throw std::invalid_argument("Division by zero");

    LongNumber absThis = *this; absThis.sign = 1;
    LongNumber absX = x; absX.sign = 1;

    if (absThis < absX) return LongNumber("0");

    int* resArr = new int[length]();
    int resIdx = 0;
    LongNumber currentChunk("0");

    for (int i = 0; i < length; i++) {
        char dStr[2] = { (char)(numbers[i] + '0'), '\0' };
        LongNumber digit(dStr);
        
        currentChunk = currentChunk * LongNumber("10") + digit;

        int count = 0;
        while (!(currentChunk < absX)) {
            currentChunk = currentChunk - absX;
            count++;
        }
        resArr[resIdx++] = count;
    }

    int skip = 0;
    while (skip < resIdx - 1 && resArr[skip] == 0) skip++;

    LongNumber result;
    delete[] result.numbers;
    result.length = resIdx - skip;
    result.numbers = new int[result.length];
    result.sign = (sign == x.sign) ? 1 : -1;
    for (int i = 0; i < result.length; i++) result.numbers[i] = resArr[skip + i];

    delete[] resArr;
    return result;
}

LongNumber LongNumber::operator % (const LongNumber& x) const {
    LongNumber quotient = *this / x;
    return *this - (quotient * x);
}

int LongNumber::get_digits_number() const noexcept {
    return length;
}

int LongNumber::get_rank_number(int rank) const {
    if (rank < 0 || rank >= length) {
        return 0;
    }

    int index = length - 1 - rank;

    return numbers[index];
}

bool LongNumber::is_negative() const noexcept {
    return sign == -1;
}

// ----------------------------------------------------------
// PRIVATE
// ----------------------------------------------------------
int LongNumber::get_length(const char* const str) const noexcept {
    if (!str) return 0;

    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// ----------------------------------------------------------
// FRIENDLY
// ----------------------------------------------------------
namespace biv {
    std::ostream& operator << (std::ostream& os, const LongNumber& x) {
        if (x.sign == -1) {
            os << '-';
        }
        for (int i = 0; i < x.length; i++) {
            os << x.numbers[i];
        }

        return os;
    }
}