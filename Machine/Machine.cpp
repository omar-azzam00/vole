#include "Machine.h"
#include <iostream>
#include <sstream>

using namespace std;

Machine::Machine() : executor(PC, IR, registers, memory)
{
}

void Machine::showBanner()
{
    interface.showBanner();
}
bool Machine::runMachine()
{
    string instructionsStr = interface.readFile();
    string errorMsg = loadProgram(instructionsStr);

    if (errorMsg != "")
    {
        cout << "Error in loading the program!\n"
             << errorMsg << "\n"
             << endl;

        return interface.askIfAgain();
    }

    string screenOutput = "";
    executor.executeProgram(screenOutput);
    if (screenOutput.length() != 0 && screenOutput.back() != '\n')
    {
        cout << '\n'
             << endl;
    }
    else if (screenOutput.length() != 0 && screenOutput.back() == '\n')
    {
        cout << endl;
    }

    if (interface.askIfWrite())
    {
        interface.writeOutput(screenOutput, PC, IR, registers, memory);
    }

    return interface.askIfAgain();
}

string Machine::loadProgram(string &instructionsStr)
{
    int instructionsCount = 5;
    stringstream ss(instructionsStr);
    string instruction;

    while (ss >> instruction)
    {
        if (instructionsCount == 128)
        {
            return "The maximum number of instructions is 128.";
        }

        if (instruction.length() != 4)
        {
            return "Instruction \"" + instruction + "\" should be 4 characters long.";
        }
        char opCode = tolower(instruction[0]);
        char reg1Addr;
        char reg2Addr;
        char reg3Addr;
        string memAddr;

        switch (opCode)
        {
        case '1':
        case '2':
        case '3':
        case 'b':
            reg1Addr = instruction[1];
            memAddr = instruction.substr(2);
            if (!isxdigit(reg1Addr))
            {
                return string("Invalid Register Address ") + '"' + reg1Addr + '"' + " in the instruction \"" + instruction + "\"";
            }
            if (!isxdigit(memAddr[0]) || !isxdigit(memAddr[1]))
            {
                return string("Invalid Memory address ") + '"' + memAddr + '"' + " in the instruction \"" + instruction + "\"";
            }
            break;
        case '4':
            if (instruction[1] != '0')
            {
                return string("Invalid Instruction ") + "\"" + instruction + "\"";
            }

            reg1Addr = instruction[2];
            reg2Addr = instruction[3];

            if (!isxdigit(reg1Addr))
            {
                return string("Invalid Register Address ") + '"' + reg1Addr + '"' + " in the instruction \"" + instruction + "\"";
            }
            if (!isxdigit(reg2Addr))
            {
                return string("Invalid Register Address ") + '"' + reg2Addr + '"' + " in the instruction \"" + instruction + "\"";
            }
            break;
        case '5':
        case '6':
            reg1Addr = instruction[1];
            reg2Addr = instruction[2];
            reg3Addr = instruction[3];
            if (!isxdigit(reg1Addr))
            {
                return string("Invalid Register Address ") + '"' + reg1Addr + '"' + " in the instruction \"" + instruction + "\"";
            }
            if (!isxdigit(reg2Addr))
            {
                return string("Invalid Register Address ") + '"' + reg2Addr + '"' + " in the instruction \"" + instruction + "\"";
            }
            if (!isxdigit(reg3Addr))
            {
                return string("Invalid Register Address ") + '"' + reg3Addr + '"' + " in the instruction \"" + instruction + "\"";
            }
            break;
        case 'c':
            if (instruction[1] != '0' || instruction[2] != '0' || instruction[3] != '0')
            {
                return string("Invalid Instruction ") + "\"" + instruction + "\"";
            }
            break;
        default:
            return string("Undefined Op-Code ") + '"' + opCode + '"' + " in the instruction \"" + instruction + "\"";
            break;
        }

        stringstream instructionSS(instruction);
        uint16_t encodedInstruction;

        instructionSS >> hex >> encodedInstruction;
        uint8_t rightSide = encodedInstruction;
        uint8_t leftSide = encodedInstruction >> 8;
        memory.setValue(instructionsCount * 2, leftSide);
        memory.setValue(instructionsCount * 2 + 1, rightSide);

        instructionsCount++;
    }

    return "";
}
