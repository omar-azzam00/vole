#ifndef REGISTER_H
#define REGISTER_H

#include <array>
#include <iostream>

using namespace std;

#define REGISTERS_COUNT 16

class Registers
{
private:
    array<unsigned char, REGISTERS_COUNT> registers; // 16 registers: R0 to R15

public:
    Registers();

    // Get the value of a specific register
    unsigned char getValue(int index) const;

    // Set the value of a specific register
    void setValue(int index, unsigned char value);

    // // Print all registers
    // void printRegisters() const;
};

#endif // REGISTER_H