#pragma once
#include <stdint.h>
#include <iostream>
#include <string>

struct FiveBitValue {
    unsigned int value : 5; 
};
class RISCV_Instructions
{
public:
	RISCV_Instructions();
	~RISCV_Instructions();
	uint32_t opcode;
	void set_rs1(std::string rs1);
	void set_rs2(std::string rs2);
	void set_rd(std::string rd);
	void convert_to_xbase_register( std:: string & reg);
	std:: string convert_to_binary(std::string & rs);

private:
	uint32_t funct3;
	uint32_t funct7;
	FiveBitValue rs1;
	uint32_t rs2;
	uint32_t rd;
	uint32_t imm;
};
