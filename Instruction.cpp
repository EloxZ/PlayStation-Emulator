#include "Instruction.h"

Instruction::Instruction(uint32_t data) : data(data) {

}

uint32_t Instruction::function() const {
	return data >> 26;
}

uint32_t Instruction::s() const {
	return (data >> 21) & 0x1f;
}

uint32_t Instruction::t() const {
	return (data >> 16) & 0x1f;
}

uint32_t Instruction::imm() const {
	return data & 0xffff;
}

uint32_t Instruction::getData() const {
	return data;
}
