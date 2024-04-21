#pragma once
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
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
	RISCV_Instructions();
	~RISCV_Instructions();
	SevenBitValue opcode;
	void set_rs1(std::string temp_rs1);
	void set_rs2(std::string temp_rs2);
	void set_rd(std::string temp_rd);
	void ADD(string rd,string rs1,string rs2);
	void SUB(string rd,string rs1,string rs2);
	void SLL(string rd,string rs1,string rs2);
	void SLT(string rd,string rs1,string rs2);
	void SLTU(string rd,string rs1,string rs2);
	void XOR(string rd,string rs1,string rs2);
	void SRL(string rd,string rs1,string rs2);
	void SRA(string rd,string rs1,string rs2);
	void OR(string rd,string rs1,string rs2);
	void AND(string rd,string rs1,string rs2);
	void ADDI(string rd,string rs1, int imm);
	void SLTI(string rd,string rs1, int imm);
	void SLTIU(string rd,string rs1, int imm);
	void XORI(string rd,string rs1, int imm);
	void ORI(string rd,string rs1, int imm);
	void ANDI(string rd,string rs1, int imm);
	void SLLI(string rd,string rs1, int imm);
	void SRLI(string rd,string rs1, int imm);
	void SRAI(string rd,string rs1, int imm);
	void BEQ(string rs1, string rs2,string label);
	void BNE(string rs1, string rs2,string label);
	void BGE(string rs1, string rs2,string label);
	void BLTU(string rs1, string rs2,string label);
	void BGEU(string rs1, string rs2,string label);
	void LB(string rd,string rs1,int imm);
	void LH(string rd,string rs1,int imm);
	void LBU(string rd,string rs1,int imm);
	void LW(string rd,string rs1,int imm);
	void LHU(string rd,string rs1,int imm);
	void SB(string rd,string rs1,int imm);
	void SH(string rd,string rs1,int imm);
	void SW(string rd,string rs1,int imm);
	void JALR(string rd,string rs1,int imm);
	void JAL(string rd,int imm);
	void LUI(string rd,int imm);
	void AUIPC(string rd,int imm);

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
