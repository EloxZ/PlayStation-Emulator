#pragma once

#include "Constants.h"
#include "Interconnect.h"
#include "Instruction.h"
#include "Utils.h"

#include <cstdint>
#include <chrono>
#include <thread>
#include <cstddef>
#include <algorithm>

class CPU {
	public:
		CPU(Interconnect inter);

		void start();
		void reset();
		void executeNextInstruction();

		void setClockFreq(float newClockFreq);

	private:
		uint32_t regs[32] = {0xfefefefe};
		uint32_t outRegs[32] = {0xfefefefe};
		std::tuple<uint32_t, uint32_t> load = std::make_tuple(0, 0);
		Interconnect inter;
		uint32_t PC = Constants::BIOS_ADDRESS;
		uint32_t SR = 0;
		float clockFreq = Constants::DEFAULT_CLOCK_FREQ;
		std::chrono::duration<float, std::milli> periodDuration = std::chrono::duration<float, std::milli>(1000/clockFreq);
		Instruction nextInstruction = Instruction(0);

		uint32_t getReg(uint32_t index) const;
		void setReg(uint32_t index, uint32_t value);

		void executeInstruction(Instruction instruction);
		uint32_t load32(uint32_t address) const;
		uint8_t load8(uint32_t address) const;
		void store32(uint32_t address, uint32_t value);
		void store16(uint32_t address, uint16_t value);
		void store8(uint32_t address, uint8_t value);

		void op_lui(Instruction instruction);
		void op_ori(Instruction instruction);
		void op_or(Instruction instruction);
		void op_andi(Instruction instruction);
		void op_sw(Instruction instruction);
		void op_sh(Instruction instruction);
		void op_sb(Instruction instruction);
		void op_lw(Instruction instruction);
		void op_lb(Instruction instruction);
		void op_sll(Instruction instruction);
		void op_sltu(Instruction instruction);
		void op_addiu(Instruction instruction);
		void op_addi(Instruction instruction);
		void op_addu(Instruction instruction);
		void op_j(Instruction instruction);
		void op_jal(Instruction instruction);
		void op_jr(Instruction instruction);

		void branch(uint32_t offset);
		void op_bne(Instruction instruction);
		void op_beq(Instruction instruction);

		void op_cop0(Instruction instruction);
		void op_mtc0(Instruction instruction);
};

