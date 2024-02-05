#pragma once

#include "Range.h"

#include <cstdint>

class Constants {
	public:
		const static float DEFAULT_CLOCK_FREQ;

		// Memory ranges
		const static uint32_t BIOS_ADDRESS = 0x1fc00000;
		const static size_t BIOS_SIZE = 512 * 1024;

		const static uint32_t SYS_CONTROL_ADDRESS = 0x1f801000;
		const static size_t SYS_CONTROL_SIZE = 36;

		const static uint32_t RAM_CONFIG_REG_ADDRESS = 0x1f801060;
		const static size_t RAM_CONFIG_REG_SIZE = 4;

		const static uint32_t CACHE_CONTROL_ADDRESS = 0xfffe0130;
		const static size_t CACHE_CONTROL_SIZE = 4;

		const static uint32_t RAM_ADDRESS = 0x00000000;
		const static size_t RAM_SIZE = 2 * 1024 * 1024;

		const static Range BIOS_RANGE;
		const static Range SYS_CONTROL_RANGE;
		const static Range RAM_CONFIG_REG_RANGE;
		const static Range CACHE_CONTROL_RANGE;
		const static Range RAM_RANGE;

};

