#include <cmath>
#include "Executor.h"

Executor::Executor(uint8_t &_PC,
                   uint16_t &_IR,
                   Registers &_registers,
                   Memory &_memory) : PC(_PC),
                                      IR(_IR),
                                      registers(_registers),
                                      memory(_memory)
{
}

uint8_t Executor::getSecondByte()
{
    return IR;
}
uint8_t Executor::getFirst4Bits()
{
    return IR >> 12;
}
uint8_t Executor::getSecond4Bits()
{
    return (uint16_t)(IR << 4) >> 12;
}
uint8_t Executor::getThird4Bits()
{
    return (uint16_t)(IR << 8) >> 12;
}
uint8_t Executor::getFouth4Bits()
{
    return (uint16_t)(IR << 12) >> 12;
}

bool Executor::executeInstruction()
{
    uint8_t data, data2, result;

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
        // data = registers.getValue(getThird4Bits());
        // data2 = registers.getValue(getFouth4Bits());
        // int sign1 = getSign(data), exponent1 = getExponent(data), mantisa1 = getMantisa(data),
        //     sign2 = getSign(data2), exponent2 = getExponent(data2), mantisa2 = getMantisa(data2),
        //     resultSign, resultExponent, resultMantisa;

        // if (exponent1 >= exponent2)
        // {
        //     mantisa2 = mantisa2 >> (exponent1 - exponent2);
        //     exponent2 = exponent1;
        //     resultExponent = exponent1;
        // }
        // else
        // {
        //     mantisa1 = mantisa1 >> (exponent2 - exponent1);
        //     exponent1 = exponent2;
        //     resultExponent = exponent1;
        // }

        // if (sign1 == sign2)
        // {
        //     resultMantisa = mantisa1 + mantisa2;
        //     resultSign = sign1;
        // }
        // else
        // {
        //     if (mantisa1 > mantisa2)
        //     {

        //         resultMantisa = mantisa1 - mantisa2;
        //         resultSign = sign1;
        //     }
        //     else
        //     {
        //         resultMantisa = mantisa2 - mantisa1;
        //         resultSign = sign2;
        //     }
        // }

        // registers.setValue(getSecond4Bits(), (resultSign << 7) + (resultExponent << 4) + resultMantisa);
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

uint8_t Executor::getSign(uint8_t byte)
{
    return byte >> 7;
}

uint8_t Executor::getExponent(uint8_t byte)
{
    return (uint8_t(byte << 1) >> 5) - 8;
}

uint8_t Executor::getMantisa(uint8_t byte)
{
    return uint8_t(byte << 4) >> 4;
}