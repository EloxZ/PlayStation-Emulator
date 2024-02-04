#include "Test.h"

void runTests() {
    std::cout << "### Tests ###" << std::endl << std::endl;
    testFetching();
}

void testBIOS() {
    std::cout << "# BIOS Test #" << std::endl;
    const std::string biosPath = "./files/bios/scph5501.bin";

    try {
        std::cout << "Loading BIOS file in " << biosPath << std::endl;
        BIOS bios(biosPath);

        std::vector<uint8_t> biosData = bios.getData();

        std::cout << "BIOS Data (First Address):" << std::endl;
        for (size_t i = 0; i < 16; ++i) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(biosData[i]) << " ";
        }
        std::cout << std::endl;

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void testFetching() {
    std::cout << "# Fetching Test #" << std::endl;
    const std::string biosPath = "./files/bios/scph5501.bin";

    try {
        BIOS bios(biosPath);
        Interconnect inter(bios);
        CPU cpu(inter);

        while (true) {
            cpu.executeNextInstruction();
        }
        

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}