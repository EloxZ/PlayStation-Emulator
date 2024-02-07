#include "RAM.h"

RAM::RAM() : data(Constants::RAM_SIZE, 0) {

}

uint32_t RAM::load32(uint32_t offset) const {
	size_t offsetAsSize = static_cast<size_t>(offset);

	uint32_t b0 = static_cast<uint32_t>(data[offsetAsSize + 0]);
	uint32_t b1 = static_cast<uint32_t>(data[offsetAsSize + 1]);
	uint32_t b2 = static_cast<uint32_t>(data[offsetAsSize + 2]);
	uint32_t b3 = static_cast<uint32_t>(data[offsetAsSize + 3]);

	return b0 | (b1 << 8) | (b2 << 16) | (b3 << 24);
}

uint8_t RAM::load8(uint32_t offset) const {
	return data[static_cast<size_t>(offset)];
}


void RAM::store32(uint32_t offset, uint32_t value) {
	size_t offsetAsSize = static_cast<size_t>(offset);

	uint8_t b0 = static_cast<uint8_t>(value);
	uint8_t b1 = static_cast<uint8_t>(value >> 8);
	uint8_t b2 = static_cast<uint8_t>(value >> 16);
	uint8_t b3 = static_cast<uint8_t>(value >> 24);

	data[offsetAsSize + 0] = b0;
	data[offsetAsSize + 1] = b1;
	data[offsetAsSize + 2] = b2;
	data[offsetAsSize + 4] = b3;
}

void RAM::store16(uint32_t offset, uint16_t value) {
	size_t offsetAsSize = static_cast<size_t>(offset);

	uint8_t b0 = static_cast<uint8_t>(value);
	uint8_t b1 = static_cast<uint8_t>(value >> 8);

	data[offsetAsSize + 0] = b0;
	data[offsetAsSize + 1] = b1;
}

void RAM::store8(uint32_t offset, uint8_t value) {
	data[static_cast<size_t>(offset)] = value;
}


const std::vector<uint8_t>& RAM::getData() const {
	return data;
}

