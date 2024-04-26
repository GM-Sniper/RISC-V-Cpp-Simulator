#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <algorithm>

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
// Define the Instruction struct
struct Instruction
{
    string rd;
    string rs1;
    string rs2;
    int imm;
    string label;
};
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

// Function to parse an instruction line
Instruction parseInstruction(const string &instructionLine)
{
    Instruction instr;

    // Create a map to store opcode mappings
    unordered_map<string, int> opcodeMap = {
        {"add", 0x33}, {"sub", 0x33}, {"sll", 0x33}, {"slt", 0x33}, {"sltu", 0x33}, {"xor", 0x33}, {"srl", 0x33}, {"sra", 0x33}, {"or", 0x33}, {"and", 0x33}, {"jalr", 0x67}, {"sw", 0x23}, {"beq", 0x63}, // Add beq opcode
        // Add more opcode mappings as needed
    };

    istringstream iss(instructionLine);
    string instructionName;
    if (iss >> instructionName)
    {
        // Lookup the opcode for the instruction
        std::transform(instructionName.begin(), instructionName.end(), instructionName.begin(),
                   [](unsigned char c) { return std::tolower(c); });
        if (opcodeMap.find(instructionName) != opcodeMap.end())
        {
            int opcode = opcodeMap[instructionName];
            // Process based on the opcode
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
                    instr.rs2 = removeCommas(instr.rs2);
                    instr.rs1 = removeCommas(instr.rs1);
                }
                else
                {
                    cerr << "Invalid R-type instruction line: " << instructionLine << endl;
                }
                break;
            case 0x67: // jalr instruction
                // Parse the operands for jalr instruction
                // Example: "jalr x10, x20, 0"
                if (iss >> instr.rd && iss.ignore() && iss >> instr.rs1 && iss.ignore() && iss >> instr.imm)
                {
                    // Set the rs2 field to zero for jalr instruction
                    instr.rs2 = "x0";
                }
                else
                {
                    cerr << "Invalid jalr instruction line: " << instructionLine << endl;
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
                }
                else
                {
                    cerr << "Invalid S-type instruction line: " << instructionLine << endl;
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
                }
                else
                {
                    cerr << "Invalid Branch instruction line: " << instructionLine << endl;
                }
                break;
            // Add cases
            default:
                cerr << "Unsupported opcode: " << opcode << endl;
                break;
            }
        }
        else
        {
            cerr << "Unknown instruction: " << instructionName << endl;
        }
    }
    else
    {
        cerr << "Invalid instruction line: " << instructionLine << endl;
    }

    return instr;
}

int main()
{
    // Test with an example beq instruction
    string instructionLine = "jalr x10, 0()";
    Instruction instr = parseInstruction(instructionLine);
    // Print the parsed instruction
    cout << "Instruction Name: " << instructionLine << endl;
    cout << "Instruction Rd: " << instr.rd << endl;
    cout << "Instruction Rs1: " << instr.rs1 << endl;
    cout << "Instruction Rs2: " << instr.rs2 << endl;
    convert_to_xbase_register(instr.rs2);
    cout << "Instruction Rs2: " << instr.rs2 << endl;
    cout << "Instruction Label: " << instr.label << endl;
    return 0;
}
