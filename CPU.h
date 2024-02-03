#pragma once

#include "Constants.h"
#include "Interconnect.h"

#include <cstdint>
#include <chrono>
#include <thread>

class CPU {
	public:
		CPU(Interconnect inter);

		void start();
		void reset();
		void setClockFreq(float newClockFreq);
		void executeNextInstruction();

	private:
		Interconnect inter;
		uint32_t PC = Constants::BIOS_ADDRESS;
		float clockFreq = Constants::DEFAULT_CLOCK_FREQ;
		std::chrono::duration<float, std::milli> periodDuration = std::chrono::duration<float, std::milli>(1000/clockFreq);

		
		void executeInstruction(uint32_t instruction);
		uint32_t load32(uint32_t address) const;
};

