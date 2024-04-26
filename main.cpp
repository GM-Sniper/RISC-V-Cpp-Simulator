#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>

// Define your classes and functions here...

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file.txt>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];

    // Add your file parsing logic here based on the filename...

    std::cout << "File path received: " << filename << std::endl;

    return 0;
}
