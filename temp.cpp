#include <iostream>
#include <map>
#include <string>
#include <cstdint>
using namespace std;
std::map<uint32_t, uint32_t> memory; 
std::map<std::string, uint32_t> registers;

void SW(std::string rs1, std::string rs2, int imm) {
    uint32_t final_address = registers[rs2] + imm;

    constexpr uint64_t MAX_MEMORY_ADDRESS = 0xFFFFFFFFULL; // 4GB in bytes

    if (final_address <= MAX_MEMORY_ADDRESS) {
        memory[final_address] = registers[rs1];
    } else {
        std::cerr << "Error: Memory access out of bounds" << std::endl;
        exit(107);
    }
}

int main() {
    
    registers["x1"] = 100;  
    registers["x2"] = 200;  

    
    SW("x1", "x2", 2000); 

    uint32_t storedValue = memory[registers["x2"] + 2000];
    std::cout << "Memory at address " << registers["x2"] + 2000 << ": " << storedValue << std::endl;

    return 0;
}
