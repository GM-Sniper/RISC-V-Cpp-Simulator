#pragma once
#include <stdint.h>
#include <iostream>


class RISCV_Instructions
{
public:
	RISCV_Instructions();
	~RISCV_Instructions();

private:
	uint32_t opcode;
	uint32_t funct3;
	uint32_t funct7;
	uint32_t rs1;
	uint32_t rs2;
	uint32_t rd;
	uint32_t imm;
};

