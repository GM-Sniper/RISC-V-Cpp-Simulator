#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

class RISCV_Instructions {
public:
    void processOpcode(map<std::string, uint8_t> &opcodes) {
        string filename = "Opcodes.txt";
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string instruction;
            int opcode;
            if (getline(iss, instruction, ',') && (iss >> opcode)) {
                opcodes[instruction] = static_cast<uint8_t>(opcode);
            } else {
                cerr << "Invalid line: " << line << endl;
            }
        }

        file.close();
    }
};

int main() {
    RISCV_Instructions processor;
    map<std::string, uint8_t> opcodes;

    processor.processOpcode(opcodes);

    // Print opcode mappings
    cout << "Opcode Mappings:\n";
    for (const auto &pair : opcodes) {
        cout << pair.first << ": " << static_cast<int>(pair.second) << endl;
    }

    return 0;
}
