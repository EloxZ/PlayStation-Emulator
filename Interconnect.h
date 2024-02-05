#pragma once

#include "BIOS.h"
#include "Range.h"
#include "Constants.h"
#include "Utils.h"

class Interconnect {
	public:
		Interconnect(BIOS bios);

		uint32_t load32(uint32_t address) const;
		uint8_t load8(uint32_t address) const;

		void store32(uint32_t address, uint32_t value);
		void store16(uint32_t address, uint16_t value);
		void store8(uint32_t address, uint8_t value);

	private:
		BIOS bios;
};

