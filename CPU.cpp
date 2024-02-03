#include "CPU.h"

const float CPU::DEFAULT_CLOCK_FREQ = 33.8688 * (10^6);

void CPU::start() {
	 
}

void CPU::reset() {
	PC = PC_RESET;
}

void CPU::setClockFreq(float newClockFreq) {
	clockFreq = newClockFreq;
	periodDuration = std::chrono::duration<float, std::milli>(1000/clockFreq);
}

void CPU::executeNextInstruction() {
	// uint32_t instruction = Get memory[PC]
	// Add 4 to PC and wrap to 0
	// executeInstruction(instruction)
}

void CPU::executeInstruction(uint32_t instruction) {

}

