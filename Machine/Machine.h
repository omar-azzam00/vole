#if !defined(_MAHCINE_H)
#define _MAHCINE_H

#include <iostream>
#include "../Memory/Memory.h"
#include "../Registers/Registers.h"
#include "../Interface/Interface.h"
#include "../Executor/Executor.h"

using namespace std;

class Machine
{
private:
    u_int8_t PC = 0x0A;
    u_int16_t IR;
    Registers registers;
    Memory memory;
    Executor executor;
    Interface interface;

private:
    string loadProgram(string &instructionsStr);

public:
    Machine();
    void showBanner();
    bool runMachine();
};

#endif // _MACHINE_H
