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

		const static uint32_t SPU_ADDRESS = 0x1f801c00;
		const static size_t SPU_SIZE = 640;

		const static uint32_t EXPANSION1_ADDRESS = 0x1f000000;
		const static size_t EXPANSION1_SIZE = 512 * 1024;

		const static uint32_t EXPANSION2_ADDRESS = 0x1f802000;
		const static size_t EXPANSION2_SIZE = 66;

		const static uint32_t IRQ_CONTROL_ADDRESS = 0x1f801070;
		const static size_t IRQ_CONTROL_SIZE = 8;

		const static uint32_t TIMERS_ADDRESS = 0x1f801104;
		const static size_t TIMERS_SIZE = 0x30;

		const static uint32_t DMA_ADDRESS = 0x1f801080;
		const static size_t DMA_SIZE = 0x80;

		const static uint32_t GPU_ADDRESS = 0x1f801080;
		const static size_t GPU_SIZE = 0x80;

		const static Range BIOS_RANGE;
		const static Range SYS_CONTROL_RANGE;
		const static Range RAM_CONFIG_REG_RANGE;
		const static Range CACHE_CONTROL_RANGE;
		const static Range RAM_RANGE;
		const static Range SPU_RANGE;
		const static Range EXPANSION1_RANGE;
		const static Range EXPANSION2_RANGE;
		const static Range IRQ_CONTROL_RANGE;
		const static Range TIMERS_RANGE;
		const static Range DMA_RANGE;
		const static Range GPU_RANGE;

};

