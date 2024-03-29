#include "Constants.h"

const float Constants::DEFAULT_CLOCK_FREQ = 33.8688 * (10 ^ 6);

const Range Constants::BIOS_RANGE = Range(BIOS_ADDRESS, BIOS_SIZE);
const Range Constants::SYS_CONTROL_RANGE = Range(SYS_CONTROL_ADDRESS, SYS_CONTROL_SIZE);
const Range Constants::RAM_CONFIG_REG_RANGE = Range(RAM_CONFIG_REG_ADDRESS, RAM_CONFIG_REG_SIZE);
const Range Constants::CACHE_CONTROL_RANGE = Range(CACHE_CONTROL_ADDRESS, CACHE_CONTROL_SIZE);
const Range Constants::RAM_RANGE = Range(RAM_ADDRESS, RAM_SIZE);
const Range Constants::SPU_RANGE = Range(SPU_ADDRESS, SPU_SIZE);
const Range Constants::EXPANSION1_RANGE = Range(EXPANSION1_ADDRESS, EXPANSION1_SIZE);
const Range Constants::EXPANSION2_RANGE = Range(EXPANSION2_ADDRESS, EXPANSION2_SIZE);
const Range Constants::IRQ_CONTROL_RANGE = Range(IRQ_CONTROL_ADDRESS, IRQ_CONTROL_SIZE);
const Range Constants::TIMERS_RANGE = Range(TIMERS_ADDRESS, TIMERS_SIZE);
const Range Constants::DMA_RANGE = Range(DMA_ADDRESS, DMA_SIZE);
const Range Constants::GPU_RANGE = Range(GPU_ADDRESS, GPU_SIZE);