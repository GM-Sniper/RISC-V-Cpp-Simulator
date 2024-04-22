#include <iostream>
#include <map>
#include <string>
#include <bitset>
#include <iomanip>

void simulation(const std::map<std::string, uint32_t>& registers) {
    std::cout << "Register" << "\t" << "Decimal" << "\t" << "Hexadecimal" << "\t" << "Binary" << std::endl;
    std::cout << "------------------------------------------------------------------" << std::endl;

    for (auto it = registers.begin(); it != registers.end(); ++it) {
        std::cout << "       " <<  it->first<< "\t" << it->second<< "\t" << std::hex << it->second<< "\t" << std::bitset<32>(it->second) << std::dec << std::endl;
    }
}

int main() {
    std::map<std::string, uint32_t> registers;
    registers["x1"] = 100;
    registers["x2"] = 200;
    registers["x3"] = 300;

    // Call the printRegisters function to display register contents
    simulation(registers);

    return 0;
}