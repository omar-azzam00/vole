#ifndef MEMORY_H
#define MEMORY_H

#include <array>
#include <iostream>

using namespace std;

class Memory
{
private:
    array<unsigned char, 256> memory; // 256 memory locations

public:
    Memory();

    // Get the value stored in a specific memory address
    unsigned char getValue(int address) const;

    // Set the value at a specific memory address
    void setValue(int address, unsigned char value);

    // Print the memory content
    void printMemory() const;
};

#endif // MEMORY_H