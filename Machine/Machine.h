#if !defined(_MAHCINE_H)
#define _MAHCINE_H

#include <iostream>
#include "../Memory/Memory.h"
#include "../Registers/Registers.h"
#include "../Interface/Interface.h"
#include "../Executor/Executor.h"
#include <cinttypes>

using namespace std;

class Machine
{
private:
    uint8_t PC = 0x0A;
    uint16_t IR;
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
