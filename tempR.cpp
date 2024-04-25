#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Define the Instruction struct
struct Instruction {
    string rd;
    string rs1;
    string rs2;
    int imm;
    string label;
};
string removeCommas(const string& input) {
    string result = input;
    result.erase(remove(result.begin(), result.end(), ','), result.end());
    return result;
}

// Function to remove brackets from a string
string removeBrackets(const string& input) {
    string result = input;
    result.erase(remove(result.begin(), result.end(), '('), result.end());
    result.erase(remove(result.begin(), result.end(), ')'), result.end());
    return result;
}

// Function to parse an instruction line
Instruction parseInstruction(const string& instructionLine) {
    Instruction instr;

    // Create a map to store opcode mappings
    unordered_map<string, int> opcodeMap = {
        {"add", 0x33}, {"sub", 0x33}, {"sll", 0x33}, {"slt", 0x33}, {"sltu", 0x33},
        {"xor", 0x33}, {"srl", 0x33}, {"sra", 0x33}, {"or", 0x33}, {"and", 0x33},
        {"jalr", 0x67}, {"sw", 0x23}, {"beq", 0x63}, // Add beq opcode
        // Add more opcode mappings as needed
    };

    istringstream iss(instructionLine);
    string instructionName;
    if (iss >> instructionName) {
        // Lookup the opcode for the instruction
        if (opcodeMap.find(instructionName) != opcodeMap.end()) {
            int opcode = opcodeMap[instructionName];
            // Process based on the opcode
            switch (opcode) {
                case 0x33: // R-type instructions
                    // Parse the operands for R-type instructions
                    // Example: "add x10, x11, x12"
                    if (iss >> instr.rd && iss.ignore() && iss >> instr.rs1 && iss.ignore() && iss >> instr.rs2)
                    {
                        // Set the immediate field to 0 for R-type instructions
                        instr.imm = 0;
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
        } else {
            cerr << "Unknown instruction: " << instructionName << endl;
        }
    } else {
        cerr << "Invalid instruction line: " << instructionLine << endl;
    }

    return instr;
}

int main() {
   // Test with an example beq instruction
    string instructionLine = "beq x10, x11, label";
    Instruction instr = parseInstruction(instructionLine);
    // Print the parsed instruction
    cout << "Instruction Name: " << instructionLine << endl;
    cout << "Instruction Rd: " << instr.rd << endl;
    cout << "Instruction Rs1: " << instr.rs1 << endl;
    cout << "Instruction Rs2: " << instr.rs2 << endl;
    cout << "Instruction Label: " << instr.label << endl;
    return 0;
}
