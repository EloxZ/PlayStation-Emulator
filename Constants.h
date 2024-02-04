#pragma once

#include "Range.h"

#include <cstdint>

class Constants {
	public:
		const static float DEFAULT_CLOCK_FREQ;

		// Memory ranges
		const static uint32_t BIOS_ADDRESS = 0xbfc00000;
		const static unsigned int BIOS_SIZE = 512 * 1024;

		const static uint32_t MEM_CONTROL_ADDRESS = 0x1f801000;
		const static unsigned int MEM_CONTROL_SIZE = 36;

		const static uint32_t RAM_CONFIG_REG_ADDRESS = 0x1f801060;
		const static unsigned int RAM_CONFIG_REG_SIZE = 4;

		const static uint32_t CACHE_CONTROL_ADDRESS = 0xfffe0130;
		const static unsigned int CACHE_CONTROL_SIZE = 4;

		const static Range BIOS_RANGE;
		const static Range MEM_CONTROL_RANGE;
		const static Range RAM_CONFIG_REG_RANGE;
		const static Range CACHE_CONTROL_RANGE;

};

