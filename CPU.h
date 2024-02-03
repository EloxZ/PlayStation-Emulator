#pragma once

#include <cstdint>
#include <chrono>
#include <thread>

class CPU {
	public:
		const static uint32_t PC_RESET = 0xbfc00000;
		const static float DEFAULT_CLOCK_FREQ;

		void start();
		void reset();
		void setClockFreq(float newClockFreq);

	private:
		uint32_t PC = PC_RESET;
		float clockFreq = DEFAULT_CLOCK_FREQ;
		std::chrono::duration<float, std::milli> periodDuration = std::chrono::duration<float, std::milli>(1000/clockFreq);

		void executeNextInstruction();
		void executeInstruction(uint32_t instruction);
};

