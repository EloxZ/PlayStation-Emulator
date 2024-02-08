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
#include <iostream>

class CPU {
	public:
		CPU(Interconnect inter);

		enum Exception {
			SYS_CALL = 0x8,
			OVER_FLOW = 0xc,
			LOAD_ADDRESS_ERROR = 0x4,
			STORE_ADDRESS_ERROR = 0x5,
			BREAK = 0x9,
			COPROCESSOR_ERROR = 0xb,
			ILLEGAL_INSTRUCTION = 0xa
		};

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
		uint32_t currentPC = PC; // In case of exception
		uint32_t nextPC = PC + 4;
		uint32_t cause = 0;
		uint32_t EPC = 0;
		uint32_t SR = 0;
		uint32_t HI = 0;
		uint32_t LO = 0;
		bool branchOccured = false;
		bool delaySlot = false;
		float clockFreq = Constants::DEFAULT_CLOCK_FREQ;
		std::chrono::duration<float, std::milli> periodDuration = std::chrono::duration<float, std::milli>(1000/clockFreq);

		uint32_t getReg(uint32_t index) const;
		void setReg(uint32_t index, uint32_t value);

		void executeInstruction(Instruction instruction);

		uint32_t load32(uint32_t address) const;
		uint16_t load16(uint32_t address) const;
		uint8_t load8(uint32_t address) const;

		void store32(uint32_t address, uint32_t value);
		void store16(uint32_t address, uint16_t value);
		void store8(uint32_t address, uint8_t value);

		void exception(Exception exception);
		void op_syscall(Instruction instruction);
		void op_break(Instruction instruction);
		void op_illegal(Instruction instruction);
		void op_rfe(Instruction instruction);

		void op_lui(Instruction instruction);
		void op_ori(Instruction instruction);
		void op_or(Instruction instruction);
		void op_xori(Instruction instruction);
		void op_xor(Instruction instruction);
		void op_nor(Instruction instruction);
		void op_andi(Instruction instruction);
		void op_and(Instruction instruction);
		void op_sw(Instruction instruction);
		void op_swl(Instruction instruction);
		void op_swr(Instruction instruction);
		void op_sh(Instruction instruction);
		void op_sb(Instruction instruction);
		void op_lw(Instruction instruction);
		void op_lwl(Instruction instruction);
		void op_lwr(Instruction instruction);
		void op_lh(Instruction instruction);
		void op_lhu(Instruction instruction);
		void op_lb(Instruction instruction);
		void op_lbu(Instruction instruction);
		void op_sll(Instruction instruction);
		void op_sllv(Instruction instruction);
		void op_slt(Instruction instruction);
		void op_sltu(Instruction instruction);
		void op_slti(Instruction instruction);
		void op_sltiu(Instruction instruction);
		void op_add(Instruction instruction);
		void op_addiu(Instruction instruction);
		void op_addi(Instruction instruction);
		void op_addu(Instruction instruction);
		void op_sub(Instruction instruction);
		void op_subu(Instruction instruction);
		void op_sra(Instruction instruction);
		void op_srav(Instruction instruction);
		void op_srl(Instruction instruction);
		void op_srlv(Instruction instruction);
		void op_j(Instruction instruction);
		void op_jal(Instruction instruction);
		void op_jalr(Instruction instruction);
		void op_jr(Instruction instruction);
		void op_div(Instruction instruction);
		void op_divu(Instruction instruction);
		void op_mult(Instruction instruction);
		void op_multu(Instruction instruction);
		void op_mflo(Instruction instruction);
		void op_mfhi(Instruction instruction);
		void op_mtlo(Instruction instruction);
		void op_mthi(Instruction instruction);

		void branch(uint32_t offset);
		void op_bne(Instruction instruction);
		void op_beq(Instruction instruction);
		void op_bgtz(Instruction instruction);
		void op_blez(Instruction instruction);
		void op_bxx(Instruction instruction); // bgez bltz bgezal bltzal

		void op_cop0(Instruction instruction);
		void op_lwc0(Instruction instruction); // not supported
		void op_swc0(Instruction instruction); // not supported
		void op_mtc0(Instruction instruction);
		void op_mfc0(Instruction instruction);
		
		void op_cop1(Instruction instruction); // not supported
		void op_lwc1(Instruction instruction); // not supported
		void op_swc1(Instruction instruction); // not supported

		void op_cop2(Instruction instruction);
		void op_lwc2(Instruction instruction);
		void op_swc2(Instruction instruction);

		void op_cop3(Instruction instruction); // not supported
		void op_lwc3(Instruction instruction); // not supported
		void op_swc3(Instruction instruction); // not supported
};

