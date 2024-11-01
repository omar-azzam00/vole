#if !defined(_INTERFACE_H)
#define _INTERFACE_H

#include <iostream>
#include "../Registers/Registers.h"
#include "../Memory/Memory.h"

using namespace std;

class Interface
{
public:
    void showBanner();
    string readFile();
    bool askIfWrite();
    void writeOutput(string &screenOutput, u_int8_t &PC, u_int16_t &IR, Registers &registers, Memory &memory);
    bool askIfAgain();
};

#endif // _INTERFACE_H
