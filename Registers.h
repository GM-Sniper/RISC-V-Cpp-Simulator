#pragma once
#ifndef REGISTERS_H
#define REGISTERS_H

#include <cstdint>
#include <map>
#include <string>
using namespace std;

class Registers {
public:
    Registers();
    uint32_t readRegister(const std::string& regName) const;
    void writeRegister(const std::string& regName, uint32_t value);

private:
    std::map<std::string, uint32_t> registers;
};
#endif // REGISTERS_H
