#include "Constants.h"

const float Constants::DEFAULT_CLOCK_FREQ = 33.8688 * (10 ^ 6);

const Range Constants::BIOS_RANGE = Range(BIOS_ADDRESS, BIOS_SIZE);
const Range Constants::SYS_CONTROL_RANGE = Range(SYS_CONTROL_ADDRESS, SYS_CONTROL_SIZE);
const Range Constants::RAM_CONFIG_REG_RANGE = Range(RAM_CONFIG_REG_ADDRESS, RAM_CONFIG_REG_SIZE);
const Range Constants::CACHE_CONTROL_RANGE = Range(CACHE_CONTROL_ADDRESS, CACHE_CONTROL_SIZE);
const Range Constants::RAM_RANGE = Range(RAM_ADDRESS, RAM_SIZE);