#include "Registers.h"
Registers::Registers() {
    // Initialize registers to zero
    for (int i = 0; i < 32; ++i) {
        registers["x" + std::to_string(i)] = 0;
    }
}

uint32_t Registers::readRegister(const std::string& regName) const {
    // Check if register exists
    if (registers.find(regName) != registers.end()) {
        return registers.at(regName);
    }
    else {
        // Handle error: Register not found
        // For simplicity, you might choose to return 0 or throw an exception
        return 0;
    }
}

void Registers::writeRegister(const std::string& regName, uint32_t value) {
    // Update register value or insert new register
    registers[regName] = value;
}