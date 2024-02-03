#include "CPU.h"

CPU::CPU(Interconnect inter) : inter(inter) {

}

void CPU::start() {
	 
}

void CPU::reset() {
	PC = Constants::BIOS_ADDRESS;
}

void CPU::setClockFreq(float newClockFreq) {
	clockFreq = newClockFreq;
	periodDuration = std::chrono::duration<float, std::milli>(1000/clockFreq);
}

void CPU::executeNextInstruction() {
	uint32_t instruction = load32(PC);
	PC += 4;

	executeInstruction(instruction);
}

void CPU::executeInstruction(uint32_t instruction) {
	throw std::runtime_error("Error executing instruction: " + instruction);
}

uint32_t CPU::load32(uint32_t address) const {
	return inter.load32(address);
}

