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

void testAddWithSignedOverflowCheck() {
    std::cout << "# addWithSignedOverflowCheck Test #" << std::endl;
    
    uint32_t r;

    uint32_t a = 0x4; // +4
    uint32_t b = 0xffffffff; // -1
    bool t = Utils::addWithSignedOverflowCheck(a, b, r);
    std::cout << Utils::wordToString(a) << " + "
        << Utils::wordToString(b) << " = "
        << Utils::wordToString(r) << " [Bool: "
        << t << "] and should be 0." << std::endl;

    a = 0x80000000; // -MAX
    b = 0x7fffffff; // +MAX
    t = Utils::addWithSignedOverflowCheck(a, b, r);
    std::cout << Utils::wordToString(a) << " + "
        << Utils::wordToString(b) << " = "
        << Utils::wordToString(r) << " [Bool: "
        << t << "] and should be 0." << std::endl;

    a = 0x1; // +1
    b = 0x7fffffff; // +MAX
    t = Utils::addWithSignedOverflowCheck(a, b, r);
    std::cout << Utils::wordToString(a) << " + "
        << Utils::wordToString(b) << " = "
        << Utils::wordToString(r) << " [Bool: "
        << t << "] and should be 1." << std::endl;

    a = 0x80000000; // -MAX
    b = 0xffffffff; // -1
    t = Utils::addWithSignedOverflowCheck(a, b, r);
    std::cout << Utils::wordToString(a) << " + "
        << Utils::wordToString(b) << " = "
        << Utils::wordToString(r) << " [Bool: "
        << t << "] and should be 1." << std::endl;


}
