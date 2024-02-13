#pragma once

#include <stdexcept>
#include <sstream>
#include <limits>
#include <vector>
#include <iostream>
#include <iomanip>

class Utils {
	public:
		const static std::string wordToString(uint32_t word);
		const static bool addWithSignedOverflowCheck(uint32_t a, uint32_t b, uint32_t& result);
		const static bool isSignedNegative(uint32_t a);
		const static uint32_t maskRegion(uint32_t address);
		const static uint32_t signedRightShift(uint32_t value, uint32_t shift);
		const static void printBytes(const std::vector<uint8_t>& bytes);
		const static uint32_t getWordFromBytes(const std::vector<uint8_t>& bytes, uint32_t address);

	private:
		const static uint32_t REGION_MASK[8];
};

