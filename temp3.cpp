#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
struct data_v {
    std::string name;
    std::string type;
    std::string content;
    std::string address;
};

std::vector<data_v> parseDataFromFile(std::string filename)
{
    std::ifstream file(filename);
    std::vector<data_v> m_data;

    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return m_data;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        char temp;
        data_v d;

        if (iss >> d.name >> temp >> d.type >> temp >> d.content >> temp >> d.address)
        {
            m_data.push_back(d);
        }
    }

    return m_data;
}



int main() {
    std::string filePath = "E:/ENG Mohamed/assembly repo/RISC-V-Cpp-Simulator/data_sample.txt";
    std::vector<data_v> messages = parseDataFromFile(filePath);

    for (const auto& msg : messages) {
        std::cout << "Name: " << msg.name << std::endl;
        std::cout << "Type: " << msg.type << std::endl;
        std::cout << "Content: " << msg.content << std::endl;
        std::cout << "Memory Address: " << msg.address << std::endl;
        std::cout << std::endl;  
    }

    return 0;
}
