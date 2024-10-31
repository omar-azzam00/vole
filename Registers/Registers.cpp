#include <iostream>
#include "Registers.h"

using namespace std;

// Constructor initializing registers to zero
Registers::Registers() : registers{} {}

// Get the value of a specific register
unsigned char Registers::getValue(int index) const
{
    if (index < 0 || index >= REGISTERS_COUNT)
    {
        throw out_of_range("Register index out of range");
    }
    return registers[index];
}

// Set the value of a specific register
void Registers::setValue(int index, unsigned char value)
{
    if (index < 0 || index >= REGISTERS_COUNT)
    {
        throw out_of_range("Register index out of range");
    }
    registers[index] = value;
}

// Print all registers
// void Registers::printRegisters() const
// {
//     // cout << "Registers:" << endl;
//     for (int i = 0; i < registers.size(); ++i)
//     {
//         cout << "R" << dec << i << ": " << hex << static_cast<int>(registers[i]);
//         if (i != registers.size() - 1)
//         {
//             cout << ", ";
//         }
//     }
// }