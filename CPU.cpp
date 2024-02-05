#include "CPU.h"

CPU::CPU(Interconnect inter) : inter(inter) {
	regs[0] = 0;
}

void CPU::start() {
	 
}

void CPU::reset() {
	PC = Constants::BIOS_ADDRESS;
}


uint32_t CPU::getReg(uint32_t index) const {
	return regs[static_cast<size_t>(index)];
}


void CPU::setReg(uint32_t index, uint32_t value) {
	outRegs[static_cast<size_t>(index)] = value;
	outRegs[0] = 0;
}

void CPU::setClockFreq(float newClockFreq) {
	clockFreq = newClockFreq;
	periodDuration = std::chrono::duration<float, std::milli>(1000/clockFreq);
}


void CPU::executeNextInstruction() {
	Instruction instruction = nextInstruction;
	uint32_t nextInstructionData = load32(PC);
	nextInstruction = Instruction(nextInstructionData);

	PC += 4;

	// Pending load
	setReg(std::get<0>(load), std::get<1>(load));
	load = std::make_tuple(0, 0);

	executeInstruction(instruction);

	// regs = outRegs
	std::copy(std::begin(outRegs), std::end(outRegs), std::begin(regs));
}

void CPU::executeInstruction(Instruction instruction) {
	switch (instruction.function()) {
		case 0b000000:
			switch (instruction.subfunction()) {
				case 0b000000:
					op_sll(instruction);
					break;
				default:
					throw std::runtime_error("Error executing instruction: " + Utils::wordToString(instruction.getData()));
			}
			break;
		case 0b001111:
			op_lui(instruction);
			break;
		case 0b001101:
			op_ori(instruction);
			break;
		case 0b101011:
			op_sw(instruction);
			break;
		case 0b010000:
			op_cop0(instruction);
			break;
		default:
			throw std::runtime_error("Error executing instruction: " + Utils::wordToString(instruction.getData()));
	}
}

uint32_t CPU::load32(uint32_t address) const {
	return inter.load32(address);
}

void CPU::store32(uint32_t address, uint32_t value) {
	inter.store32(address, value);
}


void CPU::op_lui(Instruction instruction) {
	uint32_t imm = instruction.imm();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t v = imm << 16;

	setReg(t, v);
}

void CPU::op_ori(Instruction instruction) {
	uint32_t imm = instruction.imm();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t v = getReg(s) | imm;

	setReg(t, v);
}

void CPU::op_sw(Instruction instruction) {
	if ((SR & 0x10000) != 0) {
		// Cache is isolated, ignore write.
		return;
	}

	uint32_t imm_se = instruction.imm_se();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t addr = getReg(s) + imm_se;
	uint32_t v = getReg(t);

	store32(addr, v);
}

void CPU::op_lw(Instruction instruction) {
	if ((SR & 0x10000) != 0) {
		// Cache is isolated, ignore write.
		return;
	}

	uint32_t imm_se = instruction.imm_se();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t addr = getReg(s) + imm_se;
	uint32_t v = load32(addr);

	load = std::make_tuple(t, v);
}

void CPU::op_sll(Instruction instruction) {
	// NOP, do nothing.
}

void CPU::op_sltu(Instruction instruction) {
	uint32_t d = instruction.d();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t v = getReg(s) < getReg(t);

	setReg(d, v);
}

void CPU::op_addiu(Instruction instruction) {
	uint32_t imm_se = instruction.imm_se();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t v = getReg(s) + imm_se;

	setReg(t, v);
}

void CPU::op_addi(Instruction instruction) {
	uint32_t imm_se = instruction.imm_se();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t v;

	if (Utils::addWithSignedOverflowCheck(getReg(s), imm_se, v)) {
		throw std::overflow_error("Overflow during addition at op_addi: " + Utils::wordToString(getReg(s)) + " + " + Utils::wordToString(imm_se) + " = " + Utils::wordToString(v));
	}

	setReg(t, v);
}

void CPU::op_addu(Instruction instruction) {
	uint32_t d = instruction.d();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t v = getReg(s) + getReg(t);

	setReg(d, v);
}

void CPU::op_j(Instruction instruction) {
	uint32_t imm_jump = instruction.imm_jump();
	PC = (PC & 0xf0000000) | (imm_jump << 2);
}

void CPU::op_or(Instruction instruction) {
	uint32_t d = instruction.d();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t v = getReg(s) | getReg(t);

	setReg(d, v);
}

void CPU::branch(uint32_t offset) {
	uint32_t alignedOffset = offset << 2;
	uint32_t calculatedPC = PC;

	calculatedPC += alignedOffset - 4;

	PC = calculatedPC;
}

void CPU::op_bne(Instruction instruction) {
	uint32_t imm_se = instruction.imm_se();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	if (getReg(s) != getReg(t)) {
		branch(imm_se);
	}
}

void CPU::op_cop0(Instruction instruction) {
	switch (instruction.s()) {
		case 0b00100:
			op_mtc0(instruction);
			break;
		default:
			throw std::runtime_error("Error executing instruction: " + Utils::wordToString(instruction.getData()));
	}
}

void CPU::op_mtc0(Instruction instruction) {
	uint32_t cpu_r = instruction.t();
	uint32_t cop_r = instruction.d();

	uint32_t v = getReg(cpu_r);

	switch (cop_r) {
		case 3: case 5: case 6: case 7: case 9: case 11:
			if (v != 0) {
				throw std::runtime_error("Unhandled write to Cop0 register: " + Utils::wordToString(cop_r));
			}
			break;
		case 12:
			SR = v;
			break;
		case 13:
			if (v != 0) {
				throw std::runtime_error("Unhandled write to CAUSE register: " + Utils::wordToString(cop_r));
			}
			break;
		default:
			throw std::runtime_error("Unhandled mtc0 register: " + Utils::wordToString(cop_r));
	}
}

