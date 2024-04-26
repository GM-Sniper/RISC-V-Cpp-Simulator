#include <iostream>
 #include <string>
// #include <fstream>
// #include <sstream>
// #include <vector>

// #include "R_format.h"
#include "RISCV_Instructions.h"
// #include "Registers.h"
using namespace std;

// parser.cpp


int main() {
    std::string input;
    std::getline(std::cin, input);  // Read input from Python GUI
    // Process input and send output back to Python GUI
    std::cout << "Parsed output: " << input << std::endl;
    return 0;
}

// int main()
// {
//     RISCV_Instructions simulation;
//     return 0;
// }