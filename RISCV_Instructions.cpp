
#include <iostream>

#include "RISCV_Instructions.h"

#include <string>
#include <bitset>

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
    temp_rd= convert_to_binary(temp_rd);
    rd= parseBinaryToFiveBit(temp_rd);
}

constexpr int m_size = 1024;
uint8_t memory[m_size];

int8_t LB(uint32_t address) {
    if (address >= m_size) {
        throw std::runtime_error("Memory access out of bounds");
    }

    int8_t value = static_cast<int8_t>(memory[address]);

    return value;
}
int16_t LH(uint32_t address) {
    if (address >= m_size - 1) {
        throw std::runtime_error("Memory access out of bounds");
    }

    int16_t value = static_cast<int16_t>((memory[address + 1] << 8) | memory[address]);

    return value;
}

int32_t LW(uint32_t address) {
    if (address >= m_size - 3) {
        throw std::runtime_error("Memory access out of bounds");
    }

    int32_t value = 0;
    for (int i = 3; i >= 0; --i) {
        value = (value << 8) | memory[address + i];
    }

    return value;
}

uint8_t LBU(uint32_t address) {
    if (address >= m_size) {
        throw std::runtime_error("Memory access out of bounds");
    }

    uint8_t value = memory[address];

    return value;
}

uint16_t LHU(uint32_t address) {
    if (address >= m_size - 1) {
        throw std::runtime_error("Memory access out of bounds");
    }

    uint16_t value = (memory[address + 1] << 8) | memory[address];

    return value;
}

void SB(uint32_t address, uint8_t value) {
    if (address >= m_size) {
        throw std::runtime_error("Memory access out of bounds");
    }

    memory[address] = value;
}

void SH(uint32_t address, uint16_t value) {
    if (address >= m_size - 1) {
        throw std::runtime_error("Memory access out of bounds");
    }

    memory[address] = static_cast<uint8_t>(value & 0xFF); // Lower byte
    memory[address + 1] = static_cast<uint8_t>((value >> 8) & 0xFF); // Upper byte
}

void SW(uint32_t address, uint32_t value) {
    if (address >= m_size - 3) {
        throw std::runtime_error("Memory access out of bounds");
    }

    memory[address] = static_cast<uint8_t>(value & 0xFF);           
    memory[address + 1] = static_cast<uint8_t>((value >> 8) & 0xFF);
    memory[address + 2] = static_cast<uint8_t>((value >> 16) & 0xFF);
    memory[address + 3] = static_cast<uint8_t>((value >> 24) & 0xFF);
}

uint32_t LUI(uint32_t imm) {
    uint32_t up_part = imm & 0xFFFFF000;

    return up_part;
}

int32_t addi(int32_t reg, int32_t imm) {
    return reg + imm;
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
