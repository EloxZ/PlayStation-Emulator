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
	currentPC = PC;

	if (currentPC % 4 != 0) {
		exception(Exception::LOAD_ADDRESS_ERROR);
		return;
	}

	Instruction instruction(load32(PC));

	std::cout << "Fetching " << Utils::wordToString(instruction.getData()) << " with PC = " << Utils::wordToString(PC) << std::endl;
	
	// Delay
	delaySlot = branchOccured;
	branchOccured = false;

	PC = nextPC;
	nextPC += 4;

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
				case 0b000010:
					op_srl(instruction);
					break;
				case 0b000011:
					op_sra(instruction);
					break;
				case 0b000100:
					op_sllv(instruction);
					break;
				case 0b000110:
					op_srlv(instruction);
					break;
				case 0b000111:
					op_srav(instruction);
					break;
				case 0b001000:
					op_jr(instruction);
					break;
				case 0b001001:
					op_jalr(instruction);
					break;
				case 0b001100:
					op_syscall(instruction);
					break;
				case 0b001101:
					op_break(instruction);
					break;
				case 0b010000:
					op_mfhi(instruction);
					break;
				case 0b010001:
					op_mthi(instruction);
					break;
				case 0b010010:
					op_mflo(instruction);
					break;
				case 0b010011:
					op_mtlo(instruction);
					break;
				case 0b011000:
					op_mult(instruction);
					break;
				case 0b011001:
					op_multu(instruction);
					break;
				case 0b011010:
					op_div(instruction);
					break;
				case 0b011011:
					op_divu(instruction);
					break;
				case 0b100000:
					op_add(instruction);
					break;
				case 0b100001:
					op_addu(instruction);
					break;
				case 0b100010:
					op_sub(instruction);
					break;
				case 0b100011:
					op_subu(instruction);
					break;
				case 0b100100:
					op_and(instruction);
					break;
				case 0b100101:
					op_or(instruction);
					break;
				case 0b100110:
					op_xor(instruction);
					break;
				case 0b100111:
					op_nor(instruction);
					break;
				case 0b101010:
					op_slt(instruction);
					break;
				case 0b101011:
					op_sltu(instruction);
					break;
				default:
					op_illegal(instruction);
			}
			break;
		case 0b000001:
			op_bxx(instruction);
			break;
		case 0b000010:
			op_j(instruction);
			break;
		case 0b000011:
			op_jal(instruction);
			break;
		case 0b000100:
			op_beq(instruction);
			break;
		case 0b000101:
			op_bne(instruction);
			break;
		case 0b000110:
			op_blez(instruction);
			break;
		case 0b000111:
			op_bgtz(instruction);
			break;
		case 0b001000:
			op_addi(instruction);
			break;
		case 0b001001:
			op_addiu(instruction);
			break;
		case 0b001010:
			op_slti(instruction);
			break;
		case 0b001011:
			op_sltiu(instruction);
			break;
		case 0b001100:
			op_andi(instruction);
			break;
		case 0b001101:
			op_ori(instruction);
			break;
		case 0b001110:
			op_xori(instruction);
			break;
		case 0b001111:
			op_lui(instruction);
			break;
		case 0b010000:
			op_cop0(instruction);
			break;
		case 0b010001:
			op_cop1(instruction);
			break;
		case 0b010010:
			op_cop2(instruction);
			break;
		case 0b010011:
			op_cop3(instruction);
			break;
		case 0b100000:
			op_lb(instruction);
			break;
		case 0b100001:
			op_lh(instruction);
			break;
		case 0b100010:
			op_lwl(instruction);
			break;
		case 0b100011:
			op_lw(instruction);
			break;
		case 0b100100:
			op_lbu(instruction);
			break;
		case 0b100101:
			op_lhu(instruction);
			break;
		case 0b100110:
			op_lwr(instruction);
			break;
		case 0b101000:
			op_sb(instruction);
			break;
		case 0b101001:
			op_sh(instruction);
			break;
		case 0b101010:
			op_swl(instruction);
			break;
		case 0b101011:
			op_sw(instruction);
			break;
		case 0b101110:
			op_swr(instruction);
			break;
		case 0b110000:
			op_lwc0(instruction);
			break;
		case 0b110001:
			op_lwc1(instruction);
			break;
		case 0b110010:
			op_lwc2(instruction);
			break;
		case 0b110011:
			op_lwc3(instruction);
			break;
		case 0b111000:
			op_swc0(instruction);
			break;
		case 0b111001:
			op_swc1(instruction);
			break;
		case 0b111010:
			op_swc2(instruction);
			break;
		case 0b111011:
			op_swc3(instruction);
			break;
		default:
			op_illegal(instruction);
	}
}


uint32_t CPU::load32(uint32_t address) const {
	return inter.load32(address);
}

uint16_t CPU::load16(uint32_t address) const {
	return inter.load16(address);
}

uint8_t CPU::load8(uint32_t address) const {
	return inter.load8(address);
}


void CPU::store32(uint32_t address, uint32_t value) {
	inter.store32(address, value);
}

void CPU::store16(uint32_t address, uint16_t value) {
	inter.store16(address, value);
}

void CPU::store8(uint32_t address, uint8_t value) {
	inter.store8(address, value);
}


void CPU::exception(Exception exception) {
	uint32_t handler = (SR & (1 << 22))? 0xbfc00180 : 0x80000080;
	uint32_t mode = SR & 0x3f;

	SR &= ~0x3f;
	SR |= (mode << 2) & 0x3f;

	cause = static_cast<uint32_t>(static_cast<int32_t>(exception) << 2);
	EPC = currentPC;

	if (delaySlot) {
		EPC -= 4;
		cause |= 1 << 31;
	}

	PC = handler;
	nextPC = PC + 4;
}

void CPU::op_syscall(Instruction instruction) {
	std::cout << "SYS_CALL exception " << Utils::wordToString(instruction.getData()) << std::endl;
	exception(Exception::SYS_CALL);
}

void CPU::op_break(Instruction instruction) {
	std::cout << "BREAK exception " << Utils::wordToString(instruction.getData()) << std::endl;
	exception(Exception::BREAK);
}

void CPU::op_illegal(Instruction instruction) {
	std::cout << "Illegal instruction " << Utils::wordToString(instruction.getData()) << std::endl;
	exception(Exception::ILLEGAL_INSTRUCTION);
}

void CPU::op_rfe(Instruction instruction) {
	if ((instruction.getData() & 0x3f) != 0b010000) {
		// Invalid cop0 instruction
	}

	uint32_t mode = SR & 0x3f;
	SR &= ~0x3f;
	SR |= mode >> 2;
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

void CPU::op_or(Instruction instruction) {
	uint32_t d = instruction.d();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t v = getReg(s) | getReg(t);

	setReg(d, v);
}

void CPU::op_xori(Instruction instruction) {
	uint32_t imm = instruction.imm();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t v = getReg(s) ^ imm;

	setReg(t, v);
}

void CPU::op_xor(Instruction instruction) {
	uint32_t d = instruction.d();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t v = getReg(s) ^ getReg(t);

	setReg(d, v);
}

void CPU::op_nor(Instruction instruction) {
	uint32_t d = instruction.d();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t v = ~(getReg(s) | getReg(t));

	setReg(d, v);
}

void CPU::op_andi(Instruction instruction) {
	uint32_t imm = instruction.imm();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t v = getReg(s) & imm;

	setReg(t, v);
}

void CPU::op_and(Instruction instruction) {
	uint32_t d = instruction.d();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t v = getReg(s) & getReg(t);

	setReg(d, v);
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

	if (addr % 4 == 0) {
		uint32_t v = getReg(t);
		store32(addr, v);
	} else {
		exception(Exception::STORE_ADDRESS_ERROR);
	}
}

void CPU::op_swl(Instruction instruction) {
	uint32_t imm_se = instruction.imm_se();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t addr = getReg(s) + imm_se;
	uint32_t v = getReg(t);

	uint32_t alignedAddr = addr & ~3;
	uint32_t currMem = load32(alignedAddr);

	uint32_t mem;

	switch (addr & 3) {
		case 0:
			mem = (currMem & 0xffffff00) | (v >> 24);
			break;
		case 1:
			mem = (currMem & 0xffff0000) | (v >> 16);
			break;
		case 2:
			mem = (currMem & 0xff000000) | (v >> 8);
			break;
		case 3:
			mem = v;
			break;
		default:
			throw std::runtime_error("Unreachable op_lwl.");
	}

	store32(addr, mem);
}

void CPU::op_swr(Instruction instruction) {
	uint32_t imm_se = instruction.imm_se();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t addr = getReg(s) + imm_se;
	uint32_t v = getReg(t);

	uint32_t alignedAddr = addr & ~3;
	uint32_t currMem = load32(alignedAddr);

	uint32_t mem;

	switch (addr & 3) {
		case 0:
			mem = v;
			break;
		case 1:
			mem = (currMem & 0x000000ff) | (v << 8);
			break;
		case 2:
			mem = (currMem & 0x0000ffff) | (v << 16);
			break;
		case 3:
			mem = (currMem & 0x00ffffff) | (v << 24);
			break;
		default:
			throw std::runtime_error("Unreachable op_lwl.");
	}

	store32(addr, mem);
}

void CPU::op_sh(Instruction instruction) {
	if ((SR & 0x10000) != 0) {
		// Cache is isolated, ignore write.
		return;
	}

	uint32_t imm_se = instruction.imm_se();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t addr = getReg(s) + imm_se;

	if (addr % 2 == 0) {
		uint32_t v = getReg(t);
		store16(addr, static_cast<uint16_t>(v));
	} else {
		exception(Exception::STORE_ADDRESS_ERROR);
	}
}

void CPU::op_sb(Instruction instruction) {
	if ((SR & 0x10000) != 0) {
		// Cache is isolated, ignore write.
		return;
	}

	uint32_t imm_se = instruction.imm_se();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t addr = getReg(s) + imm_se;
	uint32_t v = getReg(t);

	store8(addr, static_cast<uint8_t>(v));
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

	if (addr % 4 == 0) {
		uint32_t v = load32(addr);
		load = std::make_tuple(t, v);
	} else {
		exception(Exception::LOAD_ADDRESS_ERROR);
	}
}

void CPU::op_lwl(Instruction instruction) {
	uint32_t imm_se = instruction.imm_se();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t addr = getReg(s) + imm_se;
	uint32_t currV = outRegs[t];

	uint32_t alignedAddr = addr & ~3;
	uint32_t alignedWord = load32(alignedAddr);

	uint32_t v;

	switch (addr & 3) {
		case 0:
			v = (currV & 0x00ffffff) | (alignedWord << 24);
			break;
		case 1:
			v = (currV & 0x0000ffff) | (alignedWord << 16);
			break;
		case 2:
			v = (currV & 0x000000ff) | (alignedWord << 8);
			break;
		case 3:
			v = alignedWord;
			break;
		default:
			throw std::runtime_error("Unreachable op_lwl.");
	}

	load = std::make_tuple(t, v);
}

void CPU::op_lwr(Instruction instruction) {
	uint32_t imm_se = instruction.imm_se();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t addr = getReg(s) + imm_se;
	uint32_t currV = outRegs[t];

	uint32_t alignedAddr = addr & ~3;
	uint32_t alignedWord = load32(alignedAddr);

	uint32_t v;

	switch (addr & 3) {
		case 0:
			v = alignedWord;
			break;
		case 1:
			v = (currV & 0xff000000) | (alignedWord >> 8);
			break;
		case 2:
			v = (currV & 0xffff0000) | (alignedWord >> 16);
			break;
		case 3:
			v = (currV & 0xffffff00) | (alignedWord >> 24);
			break;
		default:
			throw std::runtime_error("Unreachable op_lwr.");
	}

	load = std::make_tuple(t, v);
}

void CPU::op_lh(Instruction instruction) {
	uint32_t imm_se = instruction.imm_se();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t addr = getReg(s) + imm_se;

	if (addr % 2 == 0) {
		int16_t v = static_cast<int16_t>(load16(addr));
		load = std::make_tuple(t, static_cast<uint32_t>(v));
	} else {
		exception(Exception::LOAD_ADDRESS_ERROR);
	}
}

void CPU::op_lhu(Instruction instruction) {
	uint32_t imm_se = instruction.imm_se();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t addr = getReg(s) + imm_se;

	if (addr % 2 == 0) {
		uint32_t v = load16(addr);
		load = std::make_tuple(t, v);
	} else {
		exception(Exception::LOAD_ADDRESS_ERROR);
	}
}

void CPU::op_lb(Instruction instruction) {
	uint32_t imm_se = instruction.imm_se();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t addr = getReg(s) + imm_se;
	uint32_t v = load8(addr);

	if (v & 0x80) {
		v |= 0xffffff00;
	}

	load = std::make_tuple(t, v);
}

void CPU::op_lbu(Instruction instruction) {
	uint32_t imm_se = instruction.imm_se();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t addr = getReg(s) + imm_se;
	uint32_t v = load8(addr);

	load = std::make_tuple(t, v);
}

void CPU::op_sll(Instruction instruction) {
	// NOP, do nothing.
}

void CPU::op_sllv(Instruction instruction) {
	uint32_t d = instruction.d();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t v = getReg(t) << (getReg(s) & 0x1f);

	setReg(d, v);
}

void CPU::op_slt(Instruction instruction) {
	uint32_t d = instruction.d();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	int32_t ss = static_cast<int32_t>(getReg(s));
	int32_t st = static_cast<int32_t>(getReg(t));

	uint32_t v = ss < st;

	setReg(d, v);
}

void CPU::op_sltu(Instruction instruction) {
	uint32_t d = instruction.d();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t v = getReg(s) < getReg(t);

	setReg(d, v);
}

void CPU::op_slti(Instruction instruction) {
	uint32_t imm_se = instruction.imm_se();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	int32_t ss = static_cast<int32_t>(getReg(s));
	int32_t si = static_cast<int32_t>(imm_se);

	uint32_t v = ss < si;

	setReg(t, v);
}

void CPU::op_sltiu(Instruction instruction) {
	uint32_t imm_se = instruction.imm_se();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t v = getReg(s) < imm_se;

	setReg(t, v);
}

void CPU::op_add(Instruction instruction) {
	uint32_t d = instruction.d();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t v;

	if (Utils::addWithSignedOverflowCheck(getReg(s), getReg(t), v)) {
		exception(Exception::OVER_FLOW);
		return;
	}

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
		exception(Exception::OVER_FLOW);
		return;
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

void CPU::op_sub(Instruction instruction) {
	uint32_t d = instruction.d();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t v;
	uint32_t rt = static_cast<uint32_t>(-static_cast<int32_t>(getReg(t)));

	if (Utils::addWithSignedOverflowCheck(getReg(s), getReg(t), v)) {
		exception(Exception::OVER_FLOW);
		return;
	}

	setReg(d, v);
}

void CPU::op_subu(Instruction instruction) {
	uint32_t d = instruction.d();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t v = getReg(s) - getReg(t);

	setReg(d, v);
}

void CPU::op_sra(Instruction instruction) {
	uint32_t shift = instruction.shift();
	uint32_t t = instruction.t();
	uint32_t d = instruction.d();

	uint32_t v = Utils::signedRightShift(getReg(t), shift);

	setReg(d, v);
}

void CPU::op_srav(Instruction instruction) {
	uint32_t t = instruction.t();
	uint32_t d = instruction.d();
	uint32_t s = instruction.s();

	int32_t v = static_cast<int32_t>(getReg(t)) >> (getReg(s) & 0x1f);

	setReg(d, static_cast<uint32_t>(v));
}

void CPU::op_srl(Instruction instruction) {
	uint32_t shift = instruction.shift();
	uint32_t t = instruction.t();
	uint32_t d = instruction.d();

	uint32_t v = getReg(t) >> shift;

	setReg(d, v);
}

void CPU::op_srlv(Instruction instruction) {
	uint32_t t = instruction.t();
	uint32_t d = instruction.d();
	uint32_t s = instruction.s();

	uint32_t v = getReg(t) >> (getReg(s) & 0x1f);

	setReg(d, v);
}

void CPU::op_j(Instruction instruction) {
	uint32_t imm_jump = instruction.imm_jump();
	nextPC = (nextPC & 0xf0000000) | (imm_jump << 2);
}

void CPU::op_jal(Instruction instruction) {
	uint32_t ra = nextPC;
	
	setReg(31, ra);
	
	op_j(instruction);
}

void CPU::op_jalr(Instruction instruction) {
	uint32_t d = instruction.d();
	uint32_t s = instruction.s();
	uint32_t ra = nextPC;

	setReg(d, ra);

	nextPC = getReg(s);
}

void CPU::op_jr(Instruction instruction) {
	uint32_t s = instruction.s();
	nextPC = getReg(s);
}

void CPU::op_div(Instruction instruction) {
	uint32_t s = instruction.s();
	uint32_t t = instruction.t();

	int32_t n = static_cast<int32_t>(getReg(s));
	int32_t d = static_cast<int32_t>(getReg(t));

	if (d == 0) {
		HI = static_cast<uint32_t>(n);

		if (n >= 0) {
			LO = 0xffffffff;
		} else {
			LO = 1;
		}
	} else if (static_cast<uint32_t>(n) == 0x80000000 && d == -1) {
		HI = 0;
		LO = 0x80000000;
	} else {
		HI = static_cast<uint32_t>(n % d);
		LO = static_cast<uint32_t>(n / d);
	}
}

void CPU::op_divu(Instruction instruction) {
	uint32_t s = instruction.s();
	uint32_t t = instruction.t();

	uint32_t n = getReg(s);
	uint32_t d = getReg(t);

	if (d == 0) {
		HI = n;
		LO = 0xffffffff;
	} else {
		HI = n % d;
		LO = n / d;
	}
}

void CPU::op_mult(Instruction instruction) {
	uint32_t s = instruction.s();
	uint32_t t = instruction.t();

	int64_t a = static_cast<int64_t>(getReg(s));
	int64_t b = static_cast<int64_t>(getReg(t));

	uint64_t v = static_cast<uint64_t>(a * b);

	HI = static_cast<uint32_t>(v >> 32);
	LO = static_cast<uint32_t>(v);
}

void CPU::op_multu(Instruction instruction) {
	uint32_t s = instruction.s();
	uint32_t t = instruction.t();

	uint64_t a = static_cast<uint64_t>(getReg(s));
	uint64_t b = static_cast<uint64_t>(getReg(t));

	uint64_t v = a * b;

	HI = static_cast<uint32_t>(v >> 32);
	LO = static_cast<uint32_t>(v);
}

void CPU::op_mflo(Instruction instruction) {
	uint32_t d = instruction.d();
	setReg(d, LO);
}

void CPU::op_mfhi(Instruction instruction) {
	uint32_t d = instruction.d();
	setReg(d, HI);
}

void CPU::op_mtlo(Instruction instruction) {
	uint32_t s = instruction.s();
	LO = getReg(s);
}

void CPU::op_mthi(Instruction instruction) {
	uint32_t s = instruction.s();
	HI = getReg(s);
}


void CPU::branch(uint32_t offset) {
	uint32_t alignedOffset = offset << 2;
	uint32_t calculatedPC = nextPC;

	calculatedPC += alignedOffset - 4;

	branchOccured = true;
	nextPC = calculatedPC;
}

void CPU::op_bne(Instruction instruction) {
	uint32_t imm_se = instruction.imm_se();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	if (getReg(s) != getReg(t)) {
		branch(imm_se);
	}
}

void CPU::op_beq(Instruction instruction) {
	uint32_t imm_se = instruction.imm_se();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	if (getReg(s) == getReg(t)) {
		branch(imm_se);
	}
}

void CPU::op_bgtz(Instruction instruction) {
	uint32_t imm_se = instruction.imm_se();
	uint32_t s = instruction.s();

	uint32_t v = getReg(s);

	if (!Utils::isSignedNegative(v) && v != 0) {
		branch(imm_se);
	}
}

void CPU::op_blez(Instruction instruction) {
	uint32_t imm_se = instruction.imm_se();
	uint32_t s = instruction.s();

	uint32_t v = getReg(s);

	if (Utils::isSignedNegative(v) || v == 0) {
		branch(imm_se);
	}
}

void CPU::op_bxx(Instruction instruction) {
	uint32_t imm_se = instruction.imm_se();
	uint32_t s = instruction.s();
	uint32_t instructionData = instruction.getData();

	uint32_t v = getReg(s);

	bool isBgez = (instructionData >> 16) & 1;
	bool isLink = (instructionData >> 20) & 1;

	bool test = Utils::isSignedNegative(v);
	test ^= isBgez;

	if (test) {
		if (isLink) {
			uint32_t ra = nextPC;
			setReg(31, ra);
		}

		branch(imm_se);
	}
}


void CPU::op_cop0(Instruction instruction) {
	switch (instruction.s()) {
		case 0b00000:
			op_mfc0(instruction);
			break;
		case 0b00100:
			op_mtc0(instruction);
			break;
		case 0b10000:
			op_rfe(instruction);
			break;
		default:
			throw std::runtime_error("Error executing instruction: " + Utils::wordToString(instruction.getData()));
	}
}

void CPU::op_lwc0(Instruction instruction) {
	exception(Exception::COPROCESSOR_ERROR);
}

void CPU::op_swc0(Instruction instruction) {
	exception(Exception::COPROCESSOR_ERROR);
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

void CPU::op_mfc0(Instruction instruction) {
	uint32_t cpu_r = instruction.t();
	uint32_t cop_r = instruction.d();

	uint32_t v;

	switch (cop_r) {
		case 12:
			v = SR;
			break;
		case 13:
			v = cause;
			break;
		case 14:
			v = EPC;
			break;
		default:
			throw std::runtime_error("Unhandled read from cop0r: " + Utils::wordToString(cop_r));
	}

	load = std::make_tuple(cpu_r, v);
}


void CPU::op_cop1(Instruction instruction) {
	exception(Exception::COPROCESSOR_ERROR);
}

void CPU::op_lwc1(Instruction instruction) {
	exception(Exception::COPROCESSOR_ERROR);
}

void CPU::op_swc1(Instruction instruction) {
	exception(Exception::COPROCESSOR_ERROR);
}


void CPU::op_cop2(Instruction instruction) {
	throw std::runtime_error("Unhandled GTE instruction: " + Utils::wordToString(instruction.getData()));
}

void CPU::op_lwc2(Instruction instruction) {
	throw std::runtime_error("Unhandled GTE lwc instruction: " + Utils::wordToString(instruction.getData()));
}

void CPU::op_swc2(Instruction instruction) {
	throw std::runtime_error("Unhandled GTE swc instruction: " + Utils::wordToString(instruction.getData()));
}


void CPU::op_cop3(Instruction instruction) {
	exception(Exception::COPROCESSOR_ERROR);
}

void CPU::op_lwc3(Instruction instruction) {
	exception(Exception::COPROCESSOR_ERROR);
}

void CPU::op_swc3(Instruction instruction) {
	exception(Exception::COPROCESSOR_ERROR);
}



