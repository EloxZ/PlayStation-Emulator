#pragma once

#include "BIOS.h"
#include "CPU.h"
#include "BUS.h"

#include <iostream>
#include <cstdint>
#include <iomanip>

void runTests();
void testReadBIOSFile();
void testExecuteBIOS();
void testCPUoperations();

void testAddWithSignedOverflowCheck();