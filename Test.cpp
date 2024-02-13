#include "Test.h"

void runTests() {
    std::cout << "### Tests ###" << std::endl << std::endl;
    //testReadBIOSFile();
    testCPUoperations();
}

void testReadBIOSFile() {
    std::cout << "# Read BIOS File Test #" << std::endl;
    const std::string biosPath = "./files/bios/scph5501.bin";

    try {
        std::cout << "Loading BIOS file in " << biosPath << std::endl;
        BIOS bios(biosPath);

        std::vector<uint8_t> biosData = bios.getData();

        Utils::printBytes(biosData);

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void testExecuteBIOS() {
    std::cout << "# Execute BIOS Test #" << std::endl;
    const std::string biosPath = "./files/bios/scph5501.bin";

    try {
        BIOS bios(biosPath);
        RAM ram;
        BUS bus(bios, ram);
        CPU cpu(bus);

        while (true) {
            cpu.executeNextInstruction();
        }
        

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void testCPUoperations() {
    std::cout << "# Test CPU operations #" << std::endl;
    const std::string biosPath = "./files/bios/scph5501.bin";
    const std::string testPath = "./files/tests/cpu/psxtest_cpu.exe";

    try {
        BIOS bios(biosPath);
        RAM ram;
        BUS bus(bios, ram);
        CPU cpu(bus);

        cpu.loadExecutable(testPath);

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
