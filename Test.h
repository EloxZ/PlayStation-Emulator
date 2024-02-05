#include "BIOS.h"
#include "CPU.h"
#include "Interconnect.h"

#include <iostream>
#include <cstdint>
#include <iomanip>

void runTests();
void testBIOS();
void testFetching();
void testAddWithSignedOverflowCheck();