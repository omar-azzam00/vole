#include <iostream>
#include <iomanip>
#include "Memory.h"

using namespace std;

// Constructor initializing memory to zero
Memory::Memory() : memory{} {}

// Get the value stored in a specific memory address
unsigned char Memory::getValue(int address) const
{
    if (address < 0 || address >= MEMORY_COUNT)
    {
        throw out_of_range("Memory address out of range");
    }
    return memory[address];
}

// Set the value at a specific memory address
void Memory::setValue(int address, unsigned char value)
{
    if (address < 0 || address >= MEMORY_COUNT)
    {
        throw out_of_range("Memory address out of range");
    }
    memory[address] = value;
}

// Print the memory content
// void Memory::printMemory() const {
//     cout << "Memory:" << endl;
//     for (int i = 0; i < memory.size(); ++i) {
//         cout << "Addr " << hex << setw(2) << setfill('0') << i << ": "
//             << static_cast<int>(memory[i]) << dec << endl;
//     }
// }
