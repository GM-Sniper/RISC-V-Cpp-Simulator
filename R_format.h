#pragma once
#include "RISCV_Instructions.h"

class R_format : public RISCV_Instructions
{
public:
    R_format();
    ~R_format();
    void set_func3(int func3);
    void set_func7(int func7);
    
};
