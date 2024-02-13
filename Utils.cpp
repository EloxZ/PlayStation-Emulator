#include "Utils.h"

const uint32_t Utils::REGION_MASK[8] = {
    // KUSEG: 2048 MB
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    // KSEG0: 512 MB
    0x7fffffff,
    // KSEG1: 512 MB
    0x1fffffff,
    // KSEG2: 1024 MB
    0xffffffff, 0xffffffff
};

const std::string Utils::wordToString(uint32_t word) {
    std::stringstream wordStream;
    wordStream << "0x" << std::hex << std::setfill('0') << std::setw(8) << word;

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

const uint32_t Utils::maskRegion(uint32_t address) {
    size_t index = static_cast<size_t>(address >> 29);

    return address & REGION_MASK[index];
}

const uint32_t Utils::signedRightShift(uint32_t value, uint32_t shift) {
    if (shift > 32) shift = 32;
    if (isSignedNegative(value)) {
        uint32_t shiftedValue = value >> shift;
        uint32_t sign = 0xffffffff << (32 - shift);

        return shiftedValue | sign;
    } else {
        return value >> shift;
    }
}

const void Utils::printBytes(const std::vector<uint8_t>& bytes) {
    std::stringstream ss;
    unsigned int i = 0;

    for (const uint8_t& byte : bytes) {
       ss << std::setfill('0') << std::setw(2) << std::hex << +byte;
       i++;
       if (i % 4 == 0) {
           ss << std::endl;
       }
       if (i == 64) {
           break;
       }
    }
    
    std::cout << ss.str() << std::endl;
}

const uint32_t Utils::getWordFromBytes(const std::vector<uint8_t>& bytes, uint32_t address) {
    uint32_t word = 0;

    for (unsigned int i = 0; i < 4; i++) {
        word |= static_cast<uint32_t>(bytes[address + i]) << (8 * i);
    }

    return word;
}
