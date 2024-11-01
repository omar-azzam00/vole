#include "../Executor/Executor.h"

Executor::Executor(u_int8_t &_PC,
                   u_int16_t &_IR,
                   Registers &_registers,
                   Memory &_memory) : PC(_PC),
                                      IR(_IR),
                                      registers(_registers),
                                      memory(_memory)
{
}

u_int8_t Executor::getSecondByte()
{
    return IR;
}
u_int8_t Executor::getFirst4Bits()
{
    return IR >> 12;
}
u_int8_t Executor::getSecond4Bits()
{
    return (u_int16_t)(IR << 4) >> 12;
}
u_int8_t Executor::getThird4Bits()
{
    return (u_int16_t)(IR << 8) >> 12;
}
u_int8_t Executor::getFouth4Bits()
{
    return (u_int16_t)(IR << 12) >> 12;
}

bool Executor::executeInstruction()
{
    u_int8_t data;

    IR = (memory.getValue(PC) << 8) + memory.getValue(PC + 1);

    switch (getFirst4Bits())
    {
    case 1:
        data = memory.getValue(getSecondByte());
        registers.setValue(getSecond4Bits(), data);
        break;
    case 2:
        registers.setValue(getSecond4Bits(), getSecondByte());
        break;
    case 3:
        data = registers.getValue(getSecond4Bits());
        if (getSecondByte() == 0)
        {
            *screenOutput += data;
            cout << data;
        }
        else
        {
            memory.setValue(getSecondByte(), data);
        }
        break;
    case 4:
        if (getSecond4Bits() != 0)
        {
            cerr << "Execution error, undefined instruction \"0x" << IR << "\".\n";
            return false;
        }
        data = registers.getValue(getThird4Bits());
        registers.setValue(getFouth4Bits(), data);
        break;
    case 5:
        data = registers.getValue(getThird4Bits()) + registers.getValue(getFouth4Bits());
        registers.setValue(getSecond4Bits(), data);
        break;
    case 6:
        break;
    case 0xb:
        if (registers.getValue(0) == registers.getValue(getSecond4Bits()))
        {
            PC = getSecondByte();
            return true;
        }
        break;
    case 0xc:
        if (getSecond4Bits() != 0 || getSecondByte() != 0)
        {
            cerr << "Execution error, undefined instruction \"0x" << IR << "\".\n";
        }
        return false;
        break;
    default:
        cerr << "Execution error, undefined instruction \"0x" << IR << "\".\n";
        return false;
        break;
    }

    if (PC == 254)
    {
        return false;
    }

    PC += 2;
    return true;
}

void Executor::executeProgram(string &_screenOutput)
{
    screenOutput = &_screenOutput;
    cerr << hex;
    while (executeInstruction())
    {
    }
    cerr << dec;
}