#pragma once

#include <cstdint>
#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <bitset>

class BIOS {
	public:
		const static unsigned int BIOS_SIZE = 512 * 1024;

		BIOS(std::string path); // Throws Runtime Error

		void load32(uint32_t offset);
		uint8_t* getData();
	
	private:
		uint8_t data[BIOS_SIZE] = {0};
};

