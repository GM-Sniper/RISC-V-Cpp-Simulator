#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

struct Instruction {
    int rd;
    int rs1;
    int rs2;
    int imm;
};

class RISCV_Instructions {
public:
    void parsingAssemblyCode(string filename, vector<Instruction> &instructions, map<string, int> &labelMap) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        string line;
        int programCounter = 0; // Initialize program counter
        while (getline(file, line)) {
            line.erase(0, line.find_first_not_of(" \t\r\n"));
            line.erase(line.find_last_not_of(" \t\r\n") + 1);
            transform(line.begin(), line.end(), line.begin(), ::tolower);

            if (!line.empty()) {
                if (line.find(':') != string::npos) {
                    istringstream lineStream(line);
                    string label;
                    getline(lineStream, label, ':');
                    if (isdigit(label[0])) {
                        cerr << "First character of label cannot be a digit " << label << endl;
                        return;
                    }
                    labelMap[label] = programCounter;
                } else {
                    Instruction instr;
                    cout << "Instruction: " << line << ", Address: " << programCounter << endl;
                    istringstream iss(line);
                    string instructionName;
                    if (iss >> instructionName) {
                        cout << "Instruction Name: " << instructionName << endl;
                        // Simulate setting opcodes for testing
                        map<string, int> opcodes{{"add", 0x33}};
                        int opcode = opcodes[instructionName];
                        switch (opcode) {
                            case 0x33: // R-type instructions
                                if (iss >> instr.rd && iss.ignore() && iss >> instr.rs1 && iss.ignore() && iss >> instr.rs2) {
                                    instr.imm = 0;
                                } else {
                                    cerr << "Invalid R-type instruction line: " << line << endl;
                                }
                                break;
                                // Add cases for other instruction types
                        }
                    } else {
                        cerr << "Invalid instruction line: " << line << endl;
                    }

                    programCounter += 4; // Assuming each instruction takes 4 bytes in memory
                }
            }
        }

        file.close(); // Close the file after reading
    }
};

int main() {
    RISCV_Instructions parser;
    vector<Instruction> instructions;
    map<string, int> labelMap;

    parser.parsingAssemblyCode("basic_sample.txt", instructions, labelMap);

    // Print labelMap contents
    cout << "Label Map:\n";
    for (const auto &pair : labelMap) {
        cout << pair.first << ": " << pair.second << endl;
    }

    return 0;
}
