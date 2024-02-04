#pragma once

#include <cstdint>

class Instruction {
	public:
		Instruction(uint32_t data);

		uint32_t function() const;
		uint32_t s() const;
		uint32_t t() const;
		uint32_t imm() const;
		uint32_t getData() const;

	private:
		uint32_t data;
};

