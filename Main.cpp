#include "BIOS.h"
#include "CPU.h"
#include "Test.h"

#include <iostream>
#include <cstdint>
#include <iomanip>

int main() {
    std::cout << "PlayStation Emulator" << std::endl << std::endl;

    runTests();

    return 0;
}