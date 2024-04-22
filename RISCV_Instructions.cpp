#include <iostream>
#include "RISCV_Instructions.h"
#include <iomanip>
#include <algorithm>
#include <map>
#include <cassert>
#include <string>
#include <bitset>

const int two_8 = 255;
const int two_16 = 65535;
using namespace std;
RISCV_Instructions::RISCV_Instructions()
{
    // Constructor implementation
}

RISCV_Instructions::~RISCV_Instructions()
{
    // Destructor implementation
}

void RISCV_Instructions::set_rs1(std::string temp_rs1)
{
    convert_to_xbase_register(temp_rs1);
    temp_rs1 = convert_to_binary(temp_rs1);
    rs1 = parseBinaryToFiveBit(temp_rs1);
}

void RISCV_Instructions::set_rs2(std::string temp_rs2)
{
    convert_to_xbase_register(temp_rs2);
    temp_rs2 = convert_to_binary(temp_rs2);
    rs2 = parseBinaryToFiveBit(temp_rs2);
}

void RISCV_Instructions::set_rd(std::string temp_rd)
{
    convert_to_xbase_register(temp_rd);
    temp_rd = convert_to_binary(temp_rd);
    rd = parseBinaryToFiveBit(temp_rd);
}

constexpr uint64_t MAX_MEMORY_ADDRESS = 0xFFFFFFFFULL; // 4GB in bytes
map<int, unsigned int> memory;

void RISCV_Instructions::LB(std::string rd, std::string rs1, int imm)
{
    if (rd == "x0")
        return;

    int k = registers[rs1];
    int r = (registers[rs1] + imm) % 4;
    int address = registers[rs1] + imm - r;

    // Check if the address is already in memory, if not, initialize it
    if (memory.find(address) == memory.end())
    {
        std::cerr << "Error: Memory access out of bounds" << std::endl;
        exit(100);
    }

    registers[rd] = (memory[address] << (8 * (3 - r)));
};
void RISCV_Instructions::LH(std::string rd, std::string rs1, int imm)
{
    if (rd == "x0")
        return;

    int r = (registers[rs1] + imm) % 4;
    int address = registers[rs1] + imm - r;

    if (memory.find(address) == memory.end())
    {
        std::cerr << "Error: Memory access out of bounds" << std::endl;
        exit(101);
    }

    registers[rd] = (memory[address] << (8 * (2 - r))) >> 16;
};
void RISCV_Instructions::LW(std::string rd, std::string rs1, int imm)
{
    if (rd == "xo")
        return;

    int address = registers[rs1] + imm;

    // Check if the address is within the valid memory range
    if (memory.find(address) == memory.end())
    {
        std::cerr << "Error: Memory access out of bounds" << std::endl;
        exit(102);
    }
    registers[rd] = memory[address];
}
void RISCV_Instructions::LBU(std::string rd, std::string rs1, int imm)
{
    if (rd == "x0")
        return;

    int r = (registers[rs1] + imm) % 4;
    int address = registers[rs1] + imm - r;

    if (memory.find(address) == memory.end())
    {
        std::cerr << "Error: Memory access out of bounds" << std::endl;
        exit(103);
    }

    registers[rd] = (memory[address] << (8 * (3 - r))) >> 24;
};

void RISCV_Instructions::LHU(std::string rd, std::string rs1, int imm)
{
    if (rd == "x0")
        return;

    int r = (registers[rs1] + imm) % 4;
    int address = registers[rs1] + imm - r;

    if (memory.find(address) == memory.end())
    {
        std::cerr << "Error: Memory access out of bounds" << std::endl;
        exit(104);
    }

    registers[rd] = (unsigned int)(memory[address] << (8 * (2 - r))) >> 16;
};
void RISCV_Instructions::SB(std::string rs1, std::string rs2, int imm)
{
    int address = registers[rs2] + imm;
    int r = address % 4;
    int final_address = address - r;

    if (memory.find(final_address) == memory.end())
    {
        std::cerr << "Error: Memory access out of bounds" << std::endl;
        exit(105);
    }

    unsigned int byte = registers[rs1] & 0xFF; // Extract the least significant byte

    // Shift the byte to the correct position based on the remainder
    byte <<= (8 * r);

    // Mask out the existing byte at the memory location
    unsigned int mask = ~(0xFF << (8 * r));
    memory[final_address] = (memory[final_address] & mask) | byte;
};
void RISCV_Instructions::SH(std::string rs1, std::string rs2, int imm)
{
    int address = registers[rs2] + imm;
    int r = address % 4;
    int final_address = address - r;

    if (memory.find(final_address) == memory.end())
    {
        std::cerr << "Error: Memory access out of bounds" << std::endl;
        exit(106);
    }

    unsigned int half = registers[rs1] & 0xFFFF; // Extract the least significant halfword

    // Shift the halfword to the correct position based on the remainder
    half <<= (8 * r);

    // Mask out the existing halfword at the memory location
    unsigned int mask = ~(0xFFFF << (8 * r));
    memory[final_address] = (memory[final_address] & mask) | half;
};

void RISCV_Instructions::SW(std::string rs1, std::string rs2, int imm)
{
    int final_address = registers[rs2] + imm;

    if (memory.find(final_address) == memory.end())
    {
        std::cerr << "Error: Memory access out of bounds" << std::endl;
        exit(107);
    }

    memory[final_address] = registers[rs1];
};

void RISCV_Instructions::LUI(string rd, int imm)
{
    if (rd == "x0")
        return;
    registers[rd] = (imm << 12);
}

void RISCV_Instructions::ADD(string rd, string rs1, string rs2)
{
    if (rd != "X0")
        registers[rd] = registers[rs1] + registers[rs2];
    else
    {
        cout << "Can't add to x0" << endl;
        exit(0);
    }
}

void RISCV_Instructions::ADDI(string rd, string rs1, int imm)
{
    if (rd != "x0")
        registers[rd] = registers[rs1] + imm;
    else
    {
        cout << "Can't add to x0" << endl;
        exit(1);
    }
}

void RISCV_Instructions::AND(string rd, string rs1, string rs2)
{
    if (rd != "X0")
        registers[rd] = registers[rs1] & registers[rs2];
    else
    {
        cout << "Can't and to x0" << endl;
        exit(2);
    }
}

void RISCV_Instructions::ANDI(string rd, string rs1, int imm)
{
    if (rd != "X0")
        registers[rd] = registers[rs1] & imm;
    else
    {
        cout << "Can't and to x0" << endl;
        exit(2);
    }
}

void RISCV_Instructions::SUB(string rd, string rs1, string rs2)
{
    if (rd != "X0")
        registers[rd] = registers[rs1] - registers[rs2];
    else
    {
        cout << "Can't change x0 - SUB" << endl;
        exit(0);
    }
}

void RISCV_Instructions::SLL(string rd, string rs1, string rs2)
{
}
void RISCV_Instructions::parsingAssemblyCode(string filename)
{
ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {

        // Trim leading and trailing whitespaces from the line
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);
        transform(line.begin(), line.end(), line.begin(), ::tolower);

        if (!line.empty()) {
              // Check if the line contains a label
        if (line.find(':') != string::npos) {
            // Extract label and initialize parts
            istringstream lineStream(line);
            string label;
            getline(lineStream, label, ':');
            if (isdigit(label[0])) {
                cerr << "First character of label cannot be a digit " << label << endl;
                return;
            }
             // Store label and its memory address
            labelMap[label] = programCounter;
        }
        else
        {
            // No label, just store the instruction and update memory address
            cout << "Instruction: " << line << ", Address: " << programCounter << endl;
            programCounter += 4; // Assuming each instruction takes 4 bytes in memory
        }
    }

    file.close();
}
}
void convert_to_xbase_register(std::string &reg)
{
    if (reg == "zero")
    {
        reg = "x0";
    }
    else if (reg == "ra")
    {
        reg = "x1";
    }
    else if (reg == "sp")
    {
        reg = "x2";
    }
    else if (reg == "gp")
    {
        reg = "x3";
    }
    else if (reg == "tp")
    {
        reg = "x4";
    }
    else if (reg == "t0")
    {
        reg == "x5";
    }
    else if (reg == "t1")
    {
        reg == "x6";
    }
    else if (reg == "t2")
    {
        reg == "x7";
    }
    else if (reg == "t3")
    {
        reg == "x28";
    }
    else if (reg == "t4")
    {
        reg == "x29";
    }
    else if (reg == "t5")
    {
        reg == "x30";
    }
    else if (reg == "t6")
    {
        reg == "x31";
    }
    else if (reg == "s0" || reg == "fp")
    {
        reg = "x8";
    }
    else if (reg == "s1")
    {
        reg = "x9";
    }
    else if (reg == "s2")
    {
        reg = "x18";
    }
    else if (reg == "s3")
    {
        reg = "x19";
    }
    else if (reg == "s4")
    {
        reg = "x20";
    }
    else if (reg == "s5")
    {
        reg = "x21";
    }
    else if (reg == "s6")
    {
        reg = "x22";
    }
    else if (reg == "s7")
    {
        reg = "x23";
    }
    else if (reg == "s8")
    {
        reg = "x24";
    }
    else if (reg == "s9")
    {
        reg = "x25";
    }
    else if (reg == "s10")
    {
        reg = "x26";
    }
    else if (reg == "s11")
    {
        reg = "x27";
    }
    else if (reg == "a0")
    {
        reg = "x10";
    }
    else if (reg == "a1")
    {
        reg == "x11";
    }
    else if (reg == "a2")
    {
        reg == "x12";
    }
    else if (reg == "a3")
    {
        reg = "x13";
    }
    else if (reg == "a4")
    {
        reg = "x14";
    }
    else if (reg == "a5")
    {
        reg = "x15";
    }
    else if (reg == "a6")
    {
        reg = "x16";
    }
    else if (reg == "a7")
    {
        reg = "x17";
    }
}

string convert_to_binary(std::string &rs)
{
    std::string substring = rs.substr(1);
    int num = std::stoi(substring);
    std::bitset<5> binaryNum(num);

    return binaryNum.to_string();
}

FiveBitValue parseBinaryToFiveBit(const std::string &binaryString)
{

    unsigned int parsedValue = std::bitset<5>(binaryString).to_ulong();

    FiveBitValue result;
    result.value = parsedValue;

    return result;
}
