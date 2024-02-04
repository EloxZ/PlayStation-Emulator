#include "Interconnect.h"

Interconnect::Interconnect(BIOS bios) : bios(bios) {

}

uint32_t Interconnect::load32(uint32_t address) const {
	if (address % 4 != 0) {
		throw std::runtime_error("Unaligned address at Interconnect::load32: " + Utils::wordToString(address));
	}

	Range biosRange(Constants::BIOS_ADDRESS, Constants::BIOS_SIZE);
	std::optional<uint32_t> offset = biosRange.contains(address);

	if (offset.has_value()) {
		return bios.load32(offset.value());
	}

	throw std::runtime_error("Error at Interconnect::load32 with address: " + Utils::wordToString(address));
}

void Interconnect::store32(uint32_t address, uint32_t value) {
	if (address % 4 != 0) {
		throw std::runtime_error("Unaligned address at Interconnect::store32: " + Utils::wordToString(address));
	}

	throw std::runtime_error("Interconnect::store32 not implemented, address: " + Utils::wordToString(address));
}
