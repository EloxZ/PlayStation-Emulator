#pragma once

#include <stdexcept>
#include <sstream>
#include <limits>

class Utils {
	public:
		const static std::string wordToString(uint32_t word);
		const static bool addWithSignedOverflowCheck(uint32_t a, uint32_t b, uint32_t& result);
		const static bool isSignedNegative(uint32_t a);
};

