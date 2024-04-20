
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

void RISCV_Instructions::set_rs1(std::string rs1)
{
    
}

void RISCV_Instructions::convert_to_xbase_register(std::string &reg)
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

string RISCV_Instructions::convert_to_binary(std::string &rs)
{
    std::string substring = rs.substr(1);
    int num = std::stoi(substring);
    std::bitset<32> binaryNum(num);

    return binaryNum.to_string();
}
