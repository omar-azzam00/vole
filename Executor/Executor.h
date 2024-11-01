#if !defined(_Executor_H)
#define _Executor_H

#include "../Registers/Registers.h"
#include "../Memory/Memory.h"

using namespace std;

class Executor
{
private:
    u_int8_t &PC;
    u_int16_t &IR;
    Registers &registers;
    Memory &memory;
    string *screenOutput;

    u_int8_t getSecondByte();
    u_int8_t getFirst4Bits();
    u_int8_t getSecond4Bits();
    u_int8_t getThird4Bits();
    u_int8_t getFouth4Bits();
    bool executeInstruction();

public:
    Executor(u_int8_t &_PC,
             u_int16_t &_IR,
             Registers &_registers,
             Memory &_memory);
    void executeProgram(string &_screenOutput);
};

#endif // _Executor_H
