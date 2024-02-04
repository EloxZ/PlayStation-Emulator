#include "Utils.h"

const std::string Utils::wordToString(uint32_t word) {
    std::stringstream wordStream;
    wordStream << "0x" << std::hex << word;

    return wordStream.str();
}
