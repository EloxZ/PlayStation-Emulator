#pragma once

#include "BIOS.h"
#include "Range.h"
#include "Constants.h"

class Interconnect {
	public:
		Interconnect(BIOS bios);

		uint32_t load32(uint32_t address) const;

	private:
		BIOS bios;
};

