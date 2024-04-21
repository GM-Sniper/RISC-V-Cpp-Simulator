#pragma once
#include <stdint.h>
#include <iostream>
#include <string>
#include <string>
#include <map>
using namespace std;
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
	RISCV_Instructions(map<std::string, uint32_t>& registers);
	~RISCV_Instructions();
	SevenBitValue opcode;
	void set_rs1(std::string temp_rs1);
	void set_rs2(std::string temp_rs2);
	void set_rd(std::string temp_rd);
	void add(string rd,string rs1,string rs2);
	void sub(string rd,string rs1,string rs2);
	void sll(string rd,string rs1,string rs2);
	void slt(string rd,string rs1,string rs2);
	void sltu(string rd,string rs1,string rs2);
	void xor(string rd,string rs1,string rs2);
	void srl(string rd,string rs1,string rs2);
	void sra(string rd,string rs1,string rs2);
	void or(string rd,string rs1,string rs2);
	void and(string rd,string rs1,string rs2);
	void addi(string rd,string rs1, int imm);
private:
	void holding();
	map<std::string, uint32_t> registers;
	ThreeBitValue funct3;
	SevenBitValue funct7;
	FiveBitValue rs1;
	FiveBitValue rs2;
	FiveBitValue rd;
	uint32_t imm;
};
