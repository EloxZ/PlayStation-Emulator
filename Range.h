#pragma once

#include <cstdint>
#include <optional>

class Range {
	public:
		Range(uint32_t start, uint32_t length);

		std::optional<uint32_t> contains(uint32_t address) const;
	
	private:
		uint32_t start = 0;
		uint32_t length = 0;
};

