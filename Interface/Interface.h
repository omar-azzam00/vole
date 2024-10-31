#if !defined(_INTERFACE_H)
#define _INTERFACE_H

#include <iostream>
#include "../Registers/Registers.h"
#include "../Memory/Memory.h"

using namespace std;

enum class Option
{
    ReadFile,
    WriteOutput,

};

class Interface
{
public:
    // void menu();
    void showBanner();
    string readFile();
    bool askIfWrite();
    void writeOutput(string &screenOutput, u_int8_t &PC, u_int16_t &IR, Registers &registers, Memory &memory);
    void sayDone();
    bool askIfAgain();
};

#endif // _INTERFACE_H
