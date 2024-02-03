#include "Range.h"

Range::Range(uint32_t start, uint32_t length) : start(start), length(length) {

}

std::optional<uint32_t> Range::contains(uint32_t address) const {
	if (address >= start && address < start + length) {
		return address - start;
	} else {
		return std::nullopt;
	}
}
