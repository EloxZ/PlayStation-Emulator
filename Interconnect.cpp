#include "Interconnect.h"

Interconnect::Interconnect(BIOS bios) : bios(bios) {

}

uint32_t Interconnect::load32(uint32_t address) const {
	if (address % 4 != 0) {
		throw std::runtime_error("Unaligned address at Interconnect::load32: " + Utils::wordToString(address));
	}

	std::optional<uint32_t> offset = Constants::BIOS_RANGE.contains(address);

	if (offset.has_value()) {
		return bios.load32(offset.value());
	}

	throw std::runtime_error("Error at Interconnect::load32 with address: " + Utils::wordToString(address));
}

void Interconnect::store32(uint32_t address, uint32_t value) {
	if (address % 4 != 0) {
		throw std::runtime_error("Unaligned address at Interconnect::store32: " + Utils::wordToString(address));
	}

	std::optional<uint32_t> offset = Constants::SYS_CONTROL_RANGE.contains(address);

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
				throw std::runtime_error("Unhandled Interconnect::store32 with address: " + Utils::wordToString(address));
		}
		return;
	}

	throw std::runtime_error("Error at Interconnect::store32 with address: " + Utils::wordToString(address));
}
