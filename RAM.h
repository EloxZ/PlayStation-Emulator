#pragma once

#include "Constants.h"

#include <cstdint>
#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <bitset>

class RAM {
	public:
		RAM();

		uint32_t load32(uint32_t offset) const;
		uint8_t load8(uint32_t offset) const;

		void store32(uint32_t offset, uint32_t value);
		void store16(uint32_t offset, uint16_t value);
		void store8(uint32_t offset, uint8_t value);

		const std::vector<uint8_t>& getData() const;

	private:
		std::vector<uint8_t> data;
};

