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
        reg = "x5";
    }
    else if (reg == "t1")
    {
        reg = "x6";
    }
    else if (reg == "t2")
    {
        reg = "x7";
    }
    else if (reg == "t3")
    {
        reg = "x28";
    }
    else if (reg == "t4")
    {
        reg = "x29";
    }
    else if (reg == "t5")
    {
        reg = "x30";
    }
    else if (reg == "t6")
    {
        reg = "x31";
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

string removeCommas(const string &input)
{
    string result = input;
    result.erase(remove(result.begin(), result.end(), ','), result.end());
    return result;
}

// Function to remove brackets from a string
string removeBrackets(const string &input)
{
    string result = input;
    result.erase(remove(result.begin(), result.end(), '('), result.end());
    result.erase(remove(result.begin(), result.end(), ')'), result.end());
    return result;
}
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
    programCounter += 4;
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
    programCounter += 4;
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
    programCounter += 4;
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
    programCounter += 4;
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
    programCounter += 4;
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
    programCounter += 4;
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
    programCounter += 4;
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
    programCounter += 4;
};

void RISCV_Instructions::LUI(string rd, int imm)
{
    if (rd == "x0")
        return;
    registers[rd] = (imm << 12);
    programCounter += 4;
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
    programCounter += 4;
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
    programCounter += 4;
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
    programCounter += 4;
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
    programCounter += 4;
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
    programCounter += 4;
}
void RISCV_Instructions::SLL(string rd, string rs1, string rs2)
{
    if (rd != "X0")
        registers[rd] = registers[rs1] << registers[rs2];
    else
    {
        cout << "Can't change x0 - SLL" << endl;
        exit(0);
    }
    programCounter += 4;
}

void RISCV_Instructions::SRL(string rd, string rs1, string rs2)
{
    if (rd != "X0")
        registers[rd] = registers[rs1] >> registers[rs2];
    else
    {
        cout << "Can't change x0 - SLL" << endl;
        exit(0);
    }
    programCounter += 4;
}
void RISCV_Instructions::SLT(string rd, string rs1, string rs2)
{
    if (rd != "X0")
    {
        if (registers[rs1] < registers[rs2])
            registers[rd] = 1;
    }
    else
    {
        cout << "Can't change x0 - SLT" << endl;
        exit(0);
    }
    programCounter += 4;
}

void RISCV_Instructions::SLTU(string rd, string rs1, string rs2)
{
    if (rd != "X0")
    {
        if ((unsigned int)registers[rs1] < (unsigned int)registers[rs2])
            registers[rd] = 1;
    }
    else
    {
        cout << "Can't change x0 - SLTU" << endl;
        exit(0);
    }
    programCounter += 4;
}

void RISCV_Instructions::XOR(string rd, string rs1, string rs2)
{
    if (rd != "X0")
    {
        registers[rd] = registers[rs1] ^ registers[rs2];
    }
    else
    {
        cout << "Can't change x0 - SLT" << endl;
        exit(0);
    }
    programCounter += 4;
}

void RISCV_Instructions::SRA(string rd, string rs1, string rs2)
{
    if (rd != "X0")
        registers[rd] = registers[rs1] << registers[rs2];
    else
    {
        cout << "Can't change x0 - SRA" << endl;
        exit(0);
    }
    programCounter += 4;
}

//void RISCV_Instructions::SRL(string rd, string rs1, string rs2)
//{
   // if (rd != "X0")
      //  registers[rd] = registers[rs1] << registers[rs2];
    //else
    //{
        //cout << "Can't change x0 - SRL" << endl;
     //   exit(0);
   // }
  //  programCounter += 4;
//}

void RISCV_Instructions::OR(string rd, string rs1, string rs2)
{
    if (rd != "X0")
        registers[rd] = registers[rs1] | registers[rs2];
    else
    {
        cout << "Can't change x0 - OR" << endl;
        exit(0);
    }
    programCounter += 4;
}
void RISCV_Instructions::SLTI(string rd, string rs1, int imm)
{
    if (rd != "X0")
    {
        if (registers[rs1] < imm)
            registers[rd] = 1;
    }
    else
    {
        cout << "Can't change x0 - SLTI" << endl;
        exit(0);
    }
    programCounter += 4;
}
void RISCV_Instructions::SLTIU(string rd, string rs1, int imm)
{
    if (rd != "X0")
    {
        if ((unsigned int)registers[rs1] < imm)
            registers[rd] = 1;
    }
    else
    {
        cout << "Can't change x0 - SLTIU" << endl;
        exit(0);
    }
    programCounter += 4;
}

void RISCV_Instructions::XORI(string rd, string rs1, int imm)
{
    if (rd != "X0")
    {
        registers[rd] = registers[rs1] ^ imm;
    }
    else
    {
        cout << "Can't change x0 - XORI" << endl;
        exit(0);
    }
    programCounter += 4;
}

void RISCV_Instructions::ORI(string rd, string rs1, int imm)
{
    if (rd != "X0")
    {
        registers[rd] = registers[rs1] | imm;
    }
    else
    {
        cout << "Can't change x0 - ORI" << endl;
        exit(0);
    }
    programCounter += 4;
}

void RISCV_Instructions::SLLI(string rd, string rs1, int imm)
{
    if (rd != "X0")
        registers[rd] = registers[rs1] << imm;
    else
    {
        cout << "Can't change x0 - SLLI" << endl;
        exit(0);
    }
    programCounter += 4;
}

void RISCV_Instructions::SRLI(string rd, string rs1, int imm)
{
    if (rd != "X0")
        registers[rd] = registers[rs1] >> imm;
    else
    {
        cout << "Can't change x0 - SRLI" << endl;
        exit(0);
    }
    programCounter += 4;
}

void RISCV_Instructions::SRAI(string rd, string rs1, int imm)
{
    if (rd != "X0")
        registers[rd] = registers[rs1] >> imm;
    else
    {
        cout << "Can't change x0 - SRAI" << endl;
        exit(0);
    }
    programCounter += 4;
}
void RISCV_Instructions::BEQ(string rs1, string rs2, string label)
{
    if (!labelMap.count(label))
    {
        cerr << "Trying to jump to a non existing label- BEQ " << endl;
        exit(200);
    }
    if (registers[rs1] == registers[rs2])
        programCounter = labelMap[label];
    else
        programCounter += 4;
}

void RISCV_Instructions::BGE(string rs1, string rs2, string label)
{
    if (!labelMap.count(label))
    {
        cerr << "Trying to jump to a non existing label- BGE " << endl;
        exit(201);
    }
    if (registers[rs1] >= registers[rs2])
        programCounter = labelMap[label];
    else
        programCounter += 4;
}

void RISCV_Instructions::BNE(string rs1, string rs2, string label)
{
    if (!labelMap.count(label))
    {
        cerr << "Trying to jump to a non existing label- BGE " << endl;
        exit(201);
    }
    if (registers[rs1] != registers[rs2])
        programCounter = labelMap[label];
    else
        programCounter += 4;
}

void RISCV_Instructions::BGEU(string rs1, string rs2, string label)
{
    if (!labelMap.count(label))
    {
        cerr << "Trying to jump to a non existing label- BGEU" << endl;
        exit(202);
    }
    if ((unsigned int)(registers[rs1]) >= (unsigned int)(registers[rs2]))
        programCounter = labelMap[label];
    else
        programCounter += 4;
}

void RISCV_Instructions::BLTU(string rs1, string rs2, string label)
{
    if (!labelMap.count(label))
    {
        cerr << "Trying to jump to a non existing label- BGEU" << endl;
        exit(203);
    }
    if ((unsigned int)(registers[rs1]) < (unsigned int)(registers[rs2]))
        programCounter = labelMap[label];
    else
        programCounter += 4;
}

void RISCV_Instructions::JALR(string rd, string rs1, int imm) // Still need to check the restrictions on changing X0
{
    registers[rd] = programCounter + 4;
    programCounter = registers[rs1] + imm;
}

void RISCV_Instructions::JAL(string rd, string label)
{
    if (!labelMap.count(label))
    {
        cerr << "Trying to jump to a non existing label- jal" << endl;
        exit(205);
    }
    if (rd != "X0")
    {
        registers[rd] = programCounter + 4;
        programCounter = labelMap[label];
    }
    else
    {
        cout << "Can't Change X0 - JAL " << endl;
        exit(210);
    }
}

void RISCV_Instructions::AUIPC(string rd, int imm)
{
    if (rd != "X0")
    {
        registers[rd] = programCounter + (imm << 12);
        programCounter += 4;
    }
    else
    {
        cout << "Can't Change X0 - AUIPC" << endl;
        exit(211);
    }
}
void RISCV_Instructions::processOpcode(map<std::string, uint8_t> &opcodes)
{
    string filename = "Opcodes.txt";
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        string instruction;
        int opcode;
        if (getline(iss, instruction, ',') && (iss >> opcode))
        {
            opcodes[instruction] = opcode;
        }
        else
        {
            cerr << "Invalid line: " << line << endl;
        }
    }

    file.close();
}

void RISCV_Instructions::parsingAssemblyCode(string filename, vector<Instruction> &instructions, map<string, int> &labelMap)
{   processOpcode(opcodes);
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {   if(line[0]=='#')
        {
            continue;
        }
        // Trim leading and trailing whitespaces from the line
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);
        transform(line.begin(), line.end(), line.begin(), ::tolower);

        if (!line.empty())
        {

            // Check if the line contains a label
            if (line.find(':') != string::npos)
            {
                line.erase(remove(line.begin(), line.end(), ' '), line.end());
                int position = -1;
                for (int i = 0; i < line.size(); i++)
                {
                    if (line[i] == ':')
                    {
                        position = i;
                    }
                }
                if (line.at(position + 1) != '\n' || line.at(position + 1) != '\t')
                {
                    cerr << "Cannot write Insturction after Label, please rewrite the syntex error" << endl;
                    exit(51);
                }
                // Extract label and its memory address
                istringstream lineStream(line);
                string label;
                getline(lineStream, label, ':');
                if (isdigit(label[0]))
                {
                    cerr << "First character of label cannot be a digit " << label << endl;
                    return;
                }
                // Store label and its memory address
                labelMap[label] = programCounter;
            }
            else
            {
                Instruction instr;
                // No label, just store the instruction and update memory address
                cout << "Instruction: " << line << ", Address: " << programCounter << endl;
                istringstream iss(line);
                string instructionName;
                if (iss >> instructionName)
                {

                    // Converting the instruction name into lowercase to avoid any error while reading from file
                    transform(instructionName.begin(), instructionName.end(), instructionName.begin(), [](unsigned char c)
                              { return tolower(c); });
                    cout << "Instruction Name: " << instructionName << endl;
                    int opcode = opcodes[instructionName];
                    switch (opcode)
                    {
                    case 0x33: // R-type instructions
                        // Parse the operands for R-type instructions
                        // Example: "add x10, x11, x12"
                        if (iss >> instr.rd && iss.ignore() && iss >> instr.rs1 && iss.ignore() && iss >> instr.rs2)
                        {
                            // Set the immediate field to 0 for R-type instructions
                            instr.imm = 0;
                            // Remove commas from the operands
                            instr.rd = removeCommas(instr.rd);
                            instr.rs1 = removeCommas(instr.rs1);
                            instr.rs2 = removeCommas(instr.rs2);

                            // Converting all registers used to X based
                            // Example a0 will be mapped to x0
                            convert_to_xbase_register(instr.rd);
                            convert_to_xbase_register(instr.rs1);
                            convert_to_xbase_register(instr.rs2);

                            if (instructionName == "add")
                                ADD(instr.rd, instr.rs1, instr.rs2);
                            else if (instructionName == "sub")
                                SUB(instr.rd, instr.rs1, instr.rs2);
                            else if (instructionName == "sll")
                                SLL(instr.rd, instr.rs1, instr.rs2);
                            else if (instructionName == "slt")
                                SLT(instr.rd, instr.rs1, instr.rs2);
                            else if (instructionName == "sltu")
                                SLTU(instr.rd, instr.rs1, instr.rs2);
                            else if (instructionName == "xor")
                                XOR(instr.rd, instr.rs1, instr.rs2);
                            else if (instructionName == "srl")
                                SRL(instr.rd, instr.rs1, instr.rs2);
                            else if (instructionName == "sra")
                                SRA(instr.rd, instr.rs1, instr.rs2);
                            else if (instructionName == "or")
                                OR(instr.rd, instr.rs1, instr.rs2);
                            else if (instructionName == "and")
                                AND(instr.rd, instr.rs1, instr.rs2);
                        }
                        else
                        {
                            cerr << "Invalid R-type instruction line: " << line << endl;
                        }
                        break;
                        // Add cases for other instruction types
                    case 0x13: // I-type instructions
                        // Parse the operands for I-type instructions
                        // Example: "addi x10, x11, 10"
                        if (iss >> instr.rd && iss.ignore() && iss >> instr.rs1 && iss.ignore() && iss >> instr.imm)
                        {
                            // Set the rs2 field to 0 for I-type instructions
                            instr.rs2 = "";
                            // Remove commas from the operands
                            instr.rd = removeCommas(instr.rd);
                            instr.rs1 = removeCommas(instr.rs1);

                            convert_to_xbase_register(instr.rd);
                            convert_to_xbase_register(instr.rs1);
                            if (instructionName == "addi")
                                ADDI(instr.rd, instr.rs1, instr.imm);
                            else if (instructionName == "slti")
                                SLTI(instr.rd, instr.rs1, instr.imm);
                            else if (instructionName == "sltiu")
                                SLTIU(instr.rd, instr.rs1, instr.imm);
                            else if (instructionName == "xori")
                                XORI(instr.rd, instr.rs1, instr.imm);
                            else if (instructionName == "ori")
                                ORI(instr.rd, instr.rs1, instr.imm);
                            else if (instructionName == "andi")
                                ANDI(instr.rd, instr.rs1, instr.imm);
                            else if (instructionName == "slli")
                                SLLI(instr.rd, instr.rs1, instr.imm);
                            else if (instructionName == "srli")
                                SRLI(instr.rd, instr.rs1, instr.imm);
                            else if (instructionName == "srai")
                                SRAI(instr.rd, instr.rs1, instr.imm);
                        }
                        else
                        {
                            cerr << "Invalid I-type instruction line: " << line << endl;
                        }
                        break;
                    case 0x23: // S-type instructions
                        // Parse the operands for S-type instructions
                        // Example: "sw x10, 10(x11)"
                        char comma;
                        int offset;
                        if (iss >> instr.rs2 >> offset >> comma >> instr.rs1)
                        {
                            // Extract the immediate value from the offset
                            instr.imm = offset;
                            // Set the rd field to 0 for S-type instructions
                            instr.rd = "";
                            // Remove commas from the operands
                            instr.rs2 = removeCommas(instr.rs2);
                            instr.rs1 = removeCommas(instr.rs1);
                            // Remove brackets from the operands
                            instr.rs2 = removeBrackets(instr.rs2);
                            instr.rs1 = removeBrackets(instr.rs1);

                            if (instructionName == "sw")
                                SW(instr.rs1, instr.rs2, instr.imm);
                            else if (instructionName == "sb")
                                SB(instr.rs1, instr.rs2, instr.imm);
                            else if (instructionName == "sh")
                                SH(instr.rs1, instr.rs2, instr.imm);
                        }
                        else
                        {
                            cerr << "Invalid S-type instruction line: " << line << endl;
                        }
                        break;
                    case 0x3: // Load Instructions
                        // Parse the operands for Load instructions
                        // Example: "lw x10, 10(x11)"
                        if (iss >> instr.rd >> comma >> offset >> instr.rs1)
                        {
                            // Extract the immediate value from the offset
                            instr.imm = offset;
                            // Set the rs2 field to 0 for Load instructions
                            instr.rs2 = "";
                            // Remove commas from the operands
                            instr.rd = removeCommas(instr.rd);
                            instr.rs1 = removeCommas(instr.rs1);
                            // Remove brackets from the operands
                            instr.rs1 = removeBrackets(instr.rs1);

                            convert_to_xbase_register(instr.rd);
                            convert_to_xbase_register(instr.rs1);

                            if (instructionName == "lw")
                                LW(instr.rd, instr.rs1, instr.imm);
                            else if (instructionName == "lb")
                                LB(instr.rd, instr.rs1, instr.imm);
                            else if (instructionName == "lbu")
                                LBU(instr.rd, instr.rs1, instr.imm);
                            else if (instructionName == "lh")
                                LH(instr.rd, instr.rs1, instr.imm);
                            else if (instructionName == "lhu")
                                LHU(instr.rd, instr.rs1, instr.imm);
                        }
                        else
                        {
                            cerr << "Invalid Load instruction line: " << line << endl;
                        }
                        break;
                    case 0x63: // Branch Instructions
                        // Parse the operands for Branch instructions
                        // Example: "beq x10, x11, label"
                        if (iss >> instr.rs1 >> instr.rs2 >> instr.label)
                        {
                            // Set the rd field to 0 for Branch instructions
                            instr.rd = "";
                            // Remove commas from the operands
                            instr.rs1 = removeCommas(instr.rs1);
                            instr.rs2 = removeCommas(instr.rs2);

                            convert_to_xbase_register(instr.rs2);
                            convert_to_xbase_register(instr.rs1);

                            if (instructionName == "beq")
                                BEQ(instr.rs1, instr.rs2, instr.label);
                            else if (instructionName == "bne")
                                BNE(instr.rs1, instr.rs2, instr.label);
                            else if (instructionName == "bge")
                                BGE(instr.rs1, instr.rs2, instr.label);
                            else if (instructionName == "bltu")
                                BLTU(instr.rs1, instr.rs2, instr.label);
                            else if (instructionName == "bgeu")
                                BGEU(instr.rs1, instr.rs2, instr.label);
                        }
                        else
                        {
                            cerr << "Invalid Branch instruction line: " << line << endl;
                        }
                        break;

                    case 0x67: // JALR instruction
                        // Parse the operands for jalr instruction
                        // Example: "jalr x10, x20, 0"
                        if (iss >> instr.rd && iss.ignore() && iss >> instr.rs1 && iss.ignore() && iss >> instr.imm)
                        {
                            // Remove commas from the operands
                            instr.rd = removeCommas(instr.rd);
                            instr.rs1 = removeCommas(instr.rs1);

                            convert_to_xbase_register(instr.rd);
                            convert_to_xbase_register(instr.rs1);

                            JALR(instr.rd, instr.rs1, instr.imm);
                        }
                        else
                        {
                            cerr << "Invalid jalr instruction line: " << line << endl;
                        }
                        break;
                    case 0x69: // JAL instruction
                        // Parse the operands for jal instruction
                        // Example: "jal x10, label"
                        if (iss >> instr.rd >> instr.label)
                        {
                            // Remove commas from the operands
                            instr.rd = removeCommas(instr.rd);
                            convert_to_xbase_register(instr.rd);
                            JAL(instr.rd, instr.label);
                        }
                        else
                        {
                            cerr << "Invalid jal instruction line: " << line << endl;
                        }
                        break;
                    case 0x17: // AUIPC instruction
                        // Parse the operands for auipc instruction
                        // Example: "auipc x10, 100"
                        if (iss >> instr.rd >> instr.imm)
                        {
                            // Remove commas from the operands
                            instr.rd = removeCommas(instr.rd);

                            convert_to_xbase_register(instr.rd);

                            AUIPC(instr.rd, instr.imm);
                        }
                        else
                        {
                            cerr << "Invalid auipc instruction line: " << line << endl;
                        }
                        break;
                    case 0x37: // LUI instruction
                        // Parse the operands for lui instruction
                        // Example: "lui x10, 100"
                        if (iss >> instr.rd >> instr.imm)
                        {
                            // Remove commas from the operands
                            instr.rd = removeCommas(instr.rd);

                            convert_to_xbase_register(instr.rd);

                            LUI(instr.rd, instr.imm);
                        }
                        else
                        {
                            cerr << "Invalid lui instruction line: " << line << endl;
                        }
                        break;
                    default:
                        cerr << "Wrong instruction, Unsupported opcode: " << opcode << endl;
                        break;
                    }
                }
                else
                {
                    cerr << "Invalid instruction line: " << line << endl;
                }

                // programCounter += 4; // Assuming each instruction takes 4 bytes in memory
                // instructions.push_back(instr);
            }
        }

        file.close();
    }
}
void RISCV_Instructions::simulation()
{
    std::cout << "Register"
              << "\t"
              << "Decimal"
              << "\t"
              << "Hexadecimal"
              << "\t"
              << "Binary" << std::endl;
    std::cout << "------------------------------------------------------------------" << std::endl;

    for (auto it = registers.begin(); it != registers.end(); ++it)
    {
        std::cout << "       " << it->first << "\t" << it->second << "\t" << std::hex << it->second << "\t" << std::bitset<32>(it->second) << std::dec << std::endl;
    }
}
void RISCV_Instructions::RunProrgam()
{
    // Parse the assembly code file
    std::string filename = "basic_sample.txt";
    parsingAssemblyCode(filename, instructions, labelMap);

    // Display the parsed instructions
    std::cout << "Parsed Instructions:" << std::endl;

    // Perform simulation
    simulation();
}


int main()
{
     RISCV_Instructions riscv;
    riscv.RunProrgam();

}