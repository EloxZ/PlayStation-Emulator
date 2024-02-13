#include "BUS.h"

BUS::BUS(BIOS bios, RAM ram) : bios(bios), ram(ram) {

}

uint32_t BUS::load32(uint32_t address) const {
	if (address % 4 != 0) {
		throw std::runtime_error("Unaligned address at BUS::load32: " + Utils::wordToString(address));
	}

	uint32_t absAddress = Utils::maskRegion(address);
	std::optional<uint32_t> offset = Constants::BIOS_RANGE.contains(absAddress);

	if (offset.has_value()) {
		////std::cout << "Loading 32 bits from BIOS, offset=" << offset.value() << std::endl;
		return bios.load32(offset.value());
	}

	offset = Constants::RAM_RANGE.contains(absAddress);

	if (offset.has_value()) {
		//std::cout << "Loading 32 bits from RAM, offset=" << offset.value() << std::endl;
		return ram.load32(offset.value());
	}

	offset = Constants::IRQ_CONTROL_RANGE.contains(absAddress);

	if (offset.has_value()) {
		// IRQ control read
		return 0;
	}

	offset = Constants::DMA_RANGE.contains(absAddress);

	if (offset.has_value()) {
		// DMA read
		return 0;
	}

	offset = Constants::GPU_RANGE.contains(absAddress);

	if (offset.has_value()) {
		switch (offset.value()) {
			case 4:
				return 0x10000000;
			default:
				return 0;
		}
	}

	//std::cout << "Error at BUS::load32 with address: " << Utils::wordToString(address) << std::endl;
}

uint16_t BUS::load16(uint32_t address) const {
	uint32_t absAddress = Utils::maskRegion(address);
	std::optional<uint32_t> offset = Constants::SPU_RANGE.contains(absAddress);

	if (offset.has_value()) {
		// Unhandled read from SPU register
		return 0;
	}

	offset = Constants::RAM_RANGE.contains(absAddress);

	if (offset.has_value()) {
		return ram.load16(offset.value());
	}

	offset = Constants::IRQ_CONTROL_RANGE.contains(absAddress);

	if (offset.has_value()) {
		// IRQ control read
		return 0;
	}

	//std::cout << "Error at BUS::load16 with address: " << Utils::wordToString(address) << std::endl;
}

uint8_t BUS::load8(uint32_t address) const {
	uint32_t absAddress = Utils::maskRegion(address);
	std::optional<uint32_t> offset = Constants::RAM_RANGE.contains(absAddress);

	if (offset.has_value()) {
		return ram.load8(offset.value());
	}

	offset = Constants::BIOS_RANGE.contains(absAddress);

	if (offset.has_value()) {
		return bios.load8(offset.value());
	}

	offset = Constants::EXPANSION1_RANGE.contains(absAddress);

	if (offset.has_value()) {
		// Expansion 1 not implemented.
		return 0xff;
	}


	//std::cout << "Error at BUS::load8 with address: " << Utils::wordToString(address) << std::endl;
}


void BUS::store32(uint32_t address, uint32_t value) {
	if (address % 4 != 0) {
		throw std::runtime_error("Unaligned address at BUS::store32: " + Utils::wordToString(address));
	}

	uint32_t absAddress = Utils::maskRegion(address);
	std::optional<uint32_t> offset = Constants::SYS_CONTROL_RANGE.contains(absAddress);

	if (offset.has_value()) {
		switch (offset.value()) {
			case 0:
				if (value != 0x1f000000) {
					throw std::runtime_error("Bad expansion 1: " + Utils::wordToString(value));
				}
				break;
			case 4:
				if (value != 0x1f802000) {
					throw std::runtime_error("Bad expansion 2: " + Utils::wordToString(value));
				}
				break;
			default:
				// Unhandled write to SYS_CONTROL
				break;
		}
		return;
	}

	offset = Constants::RAM_RANGE.contains(absAddress);

	if (offset.has_value()) {
		ram.store32(offset.value(), value);
		return;
	}

	offset = Constants::IRQ_CONTROL_RANGE.contains(absAddress);

	if (offset.has_value()) {
		// IRQ CONTROL not implemented.
		return;
	}

	offset = Constants::RAM_CONFIG_REG_RANGE.contains(absAddress);

	if (offset.has_value()) {
		// Ram config not implemented
		return;
	}

	offset = Constants::DMA_RANGE.contains(absAddress);

	if (offset.has_value()) {
		// DMA write
		return;
	}

	offset = Constants::GPU_RANGE.contains(absAddress);

	if (offset.has_value()) {
		// GPU write
		return;
	}

	offset = Constants::TIMERS_RANGE.contains(absAddress);

	if (offset.has_value()) {
		// Timers write
		return;
	}

	offset = Constants::CACHE_CONTROL_RANGE.contains(absAddress);

	if (offset.has_value()) {
		// Cache write
		return;
	}

	throw std::runtime_error("Error at BUS::store32 with address: " + Utils::wordToString(address));
}

void BUS::store16(uint32_t address, uint16_t value) {
	if (address % 2 != 0) {
		throw std::runtime_error("Unaligned address at BUS::store16: " + Utils::wordToString(address));
	}

	uint32_t absAddress = Utils::maskRegion(address);
	std::optional<uint32_t> offset = Constants::SPU_RANGE.contains(absAddress);

	if (offset.has_value()) {
		// Unhandled write to SPU
		return;
	}

	offset = Constants::TIMERS_RANGE.contains(absAddress);

	if (offset.has_value()) {
		// Unhandled write to timer register
		return;
	}

	offset = Constants::RAM_RANGE.contains(absAddress);

	if (offset.has_value()) {
		ram.store16(offset.value(), value);
		return;
	}

	offset = Constants::IRQ_CONTROL_RANGE.contains(absAddress);

	if (offset.has_value()) {
		// Unhandled write to IRQ
		return;
	}

	throw std::runtime_error("Error at BUS::store16 with address: " + Utils::wordToString(address));
}

void BUS::store8(uint32_t address, uint8_t value) {
	uint32_t absAddress = Utils::maskRegion(address);
	std::optional<uint32_t> offset = Constants::RAM_RANGE.contains(absAddress);

	if (offset.has_value()) {
		ram.store8(offset.value(), value);
		return;
	}

	offset = Constants::EXPANSION2_RANGE.contains(absAddress);

	if (offset.has_value()) {
		// Unhandled write to EXPANSION 2
		return;
	}

	throw std::runtime_error("Error at BUS::store8 with address: " + Utils::wordToString(address));
}
