#pragma once
#include <stdint.h>
#include <iostream>
#include <string>

struct FiveBitValue
{
	unsigned int value : 5;
};
struct SevenBitValue
{
	unsigned int value : 7;
};

struct ThreeBitValue
{
	unsigned int value : 3;
};

class RISCV_Instructions
{
public:
	RISCV_Instructions();
	~RISCV_Instructions();
	SevenBitValue opcode;
	void set_rs1(std::string temp_rs1);
	void set_rs2(std::string temp_rs2);
	void set_rd(std::string temp_rd);

private:
	ThreeBitValue funct3;
	SevenBitValue funct7;
	FiveBitValue rs1;
	FiveBitValue rs2;
	FiveBitValue rd;
	uint32_t imm;
};
