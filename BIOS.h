#pragma once

#include "Constants.h"

#include <cstdint>
#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <bitset>

class BIOS {
	public:
		BIOS(std::string path); // Throws Runtime Error

		uint32_t load32(uint32_t offset) const;
		const std::vector<uint8_t>& getData() const;
	
	private:
		std::vector<uint8_t> data;
};

