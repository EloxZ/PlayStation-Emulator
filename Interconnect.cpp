#include "Interconnect.h"

Interconnect::Interconnect(BIOS bios, RAM ram) : bios(bios), ram(ram) {

}

uint32_t Interconnect::load32(uint32_t address) const {
	if (address % 4 != 0) {
		throw std::runtime_error("Unaligned address at Interconnect::load32: " + Utils::wordToString(address));
	}

	uint32_t absAddress = Utils::maskRegion(address);
	std::optional<uint32_t> offset = Constants::BIOS_RANGE.contains(absAddress);

	if (offset.has_value()) {
		return bios.load32(offset.value());
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

	throw std::runtime_error("Error at Interconnect::load32 with address: " + Utils::wordToString(address));
}

uint16_t Interconnect::load16(uint32_t address) const {
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

	throw std::runtime_error("Error at Interconnect::load16 with address: " + Utils::wordToString(address));
}

uint8_t Interconnect::load8(uint32_t address) const {
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


	throw std::runtime_error("Error at Interconnect::load32 with address: " + Utils::wordToString(address));
}


void Interconnect::store32(uint32_t address, uint32_t value) {
	if (address % 4 != 0) {
		throw std::runtime_error("Unaligned address at Interconnect::store32: " + Utils::wordToString(address));
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

	offset = Constants::IRQ_CONTROL_RANGE.contains(absAddress);

	if (offset.has_value()) {
		// IRQ CONTROL not implemented.
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

	throw std::runtime_error("Error at Interconnect::store32 with address: " + Utils::wordToString(address));
}

void Interconnect::store16(uint32_t address, uint16_t value) {
	if (address % 2 != 0) {
		throw std::runtime_error("Unaligned address at Interconnect::store16: " + Utils::wordToString(address));
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

	throw std::runtime_error("Error at Interconnect::store16 with address: " + Utils::wordToString(address));
}

void Interconnect::store8(uint32_t address, uint8_t value) {
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

	throw std::runtime_error("Error at Interconnect::store8 with address: " + Utils::wordToString(address));
}
