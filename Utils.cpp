#include "Utils.h"

const std::string Utils::wordToString(uint32_t word) {
    std::stringstream wordStream;
    wordStream << "0x" << std::hex << word;

    return wordStream.str();
}

const bool Utils::addWithSignedOverflowCheck(uint32_t a, uint32_t b, uint32_t& result) {
    result = a + b;

    bool negativeOverflow = isSignedNegative(a) && isSignedNegative(b) && !isSignedNegative(result);
    bool positiveOverflow = !isSignedNegative(a) && !isSignedNegative(b) && isSignedNegative(result);

    return negativeOverflow || positiveOverflow;
}

const bool Utils::isSignedNegative(uint32_t a) {
    return (a & 0x80000000) != 0;
}
