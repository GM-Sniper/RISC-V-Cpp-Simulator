#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file.txt>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];

    // Add your file parsing logic here based on the filename...
    // For example:
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;  // Output each line of the file
        }
        file.close();
    } else {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    return 0;
}
