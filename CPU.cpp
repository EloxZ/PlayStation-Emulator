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
	regs[static_cast<size_t>(index)] = value;
	regs[0] = 0;
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

	executeInstruction(instruction);
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
	uint32_t imm_se = instruction.imm_se();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t addr = getReg(s) + imm_se;
	uint32_t v = getReg(t);

	store32(addr, v);
}

void CPU::op_sll(Instruction instruction) {
	// NOP, do nothing.
}

void CPU::op_addiu(Instruction instruction) {
	uint32_t imm_se = instruction.imm_se();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t v = getReg(s) + imm_se;

	setReg(t, v);
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

