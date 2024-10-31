#include "Machine.h"
#include <iostream>

using namespace std;

Machine::Machine() {}

void Machine::runMachine()
{
    interface.showBanner();
    while (true)
    {
        string instructionsStr = interface.readFile();
        string screenOutput;

        // Here we will parse the instructionStr and run it;

        if (interface.askIfWrite())
        {
            interface.writeOutput(screenOutput, PC, IR, registers, memory);
            interface.sayDone();
        }

        if (!interface.askIfAgain())
        {
            break;
        }
    }
}