#pragma once

#include "Constants.h"
#include "Interconnect.h"
#include "Instruction.h"
#include "Utils.h"

#include <cstdint>
#include <chrono>
#include <thread>
#include <cstddef>

class CPU {
	public:
		CPU(Interconnect inter);

		void start();
		void reset();
		void executeNextInstruction();

		uint32_t getReg(uint32_t index) const;

		void setReg(uint32_t index, uint32_t value);
		void setClockFreq(float newClockFreq);

	private:
		uint32_t regs[32] = {0xfefefefe};
		Interconnect inter;
		uint32_t PC = Constants::BIOS_ADDRESS;
		float clockFreq = Constants::DEFAULT_CLOCK_FREQ;
		std::chrono::duration<float, std::milli> periodDuration = std::chrono::duration<float, std::milli>(1000/clockFreq);
		Instruction nextInstruction = Instruction(0);

		void executeInstruction(Instruction instruction);
		uint32_t load32(uint32_t address) const;
		void store32(uint32_t address, uint32_t value);

		void op_lui(Instruction instruction);
		void op_ori(Instruction instruction);
		void op_sw(Instruction instruction);
		void op_sll(Instruction instruction);
		void op_addiu(Instruction instruction);
		void op_j(Instruction instruction);
		void op_or(Instruction instruction);
};

