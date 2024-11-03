#if !defined(_INTERFACE_H)
#define _INTERFACE_H

#include <iostream>
#include "../Registers/Registers.h"
#include "../Memory/Memory.h"
#include <cinttypes>

using namespace std;

class Interface
{
public:
    void showBanner();
    string readFile();
    bool askIfWrite();
    void writeOutput(string &screenOutput, uint8_t &PC, uint16_t &IR, Registers &registers, Memory &memory);
    bool askIfAgain();
};

#endif // _INTERFACE_H
