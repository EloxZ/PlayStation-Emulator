#include "BIOS.h"

BIOS::BIOS(std::string path) {
	std::ifstream input(path, std::ios::binary);

	if (input.fail()) {
		throw std::runtime_error("Error reading BIOS file: " + path);
	}

	std::vector<char> bytes((std::istreambuf_iterator<char>(input)), (std::istreambuf_iterator<char>()));
	unsigned int i = 0;
	for (char byte : bytes) {
		data[i] = byte;
		i++;
	}

	input.close();
}

uint32_t BIOS::load32(uint32_t offset) const {
	size_t offsetAsSize = static_cast<size_t>(offset);

	uint32_t b0 = static_cast<uint32_t>(data[offsetAsSize + 0]);
	uint32_t b1 = static_cast<uint32_t>(data[offsetAsSize + 1]);
	uint32_t b2 = static_cast<uint32_t>(data[offsetAsSize + 2]);
	uint32_t b3 = static_cast<uint32_t>(data[offsetAsSize + 3]);

	return b0 | (b1 << 8) | (b2 << 16) | (b3 << 24);
}

const uint8_t* BIOS::getData() const {
	return data;
}
