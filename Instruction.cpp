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

uint32_t Instruction::imm_se() const {
	uint32_t result = data & 0xffff;

	if (result & 0x8000) {
		result |= 0xffff0000;
	}

	return result;
}

uint32_t Instruction::imm_jump() const {
	return data & 0x3ffffff;
}

uint32_t Instruction::d() const {
	return (data >> 11) & 0x1f;
}

uint32_t Instruction::subfunction() const {
	return data & 0x3f;
}

uint32_t Instruction::shift() const {
	return (data >> 6) & 0x1f;
}

uint32_t Instruction::getData() const {
	return data;
}
