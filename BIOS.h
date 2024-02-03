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
		const uint8_t* getData() const;
	
	private:
		uint8_t data[Constants::BIOS_SIZE] = {0};
};

