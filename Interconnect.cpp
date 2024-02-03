#include "Interconnect.h"

Interconnect::Interconnect(BIOS bios) : bios(bios) {

}

uint32_t Interconnect::load32(uint32_t address) const {
	Range biosRange(Constants::BIOS_ADDRESS, Constants::BIOS_SIZE);
	std::optional<uint32_t> offset = biosRange.contains(address);

	if (offset.has_value()) {
		return bios.load32(offset.value());
	}

	throw std::runtime_error("Error at Interconnect load32 with address: " + address);
}
