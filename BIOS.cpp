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

void BIOS::load32(uint32_t offset) {

}

uint8_t* BIOS::getData() {
	return data;
}
