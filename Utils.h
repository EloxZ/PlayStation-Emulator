#pragma once

#include <stdexcept>
#include <sstream>
#include <limits>

class Utils {
	public:
		const static std::string wordToString(uint32_t word);
		const static bool addWithSignedOverflowCheck(uint32_t a, uint32_t b, uint32_t& result);
		const static bool isSignedNegative(uint32_t a);
		const static uint32_t maskRegion(uint32_t address);
		const static uint32_t signedRightShift(uint32_t value, uint32_t shift);

	private:
		const static uint32_t REGION_MASK[8];
};

