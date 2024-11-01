#include "Machine.h"
#include <iostream>
#include <sstream>

using namespace std;

Machine::Machine() {}

void Machine::runMachine()
{
    interface.showBanner();
    while (true)
    {
        // Fetch, Decode
        string instructionsStr = interface.readFile();
        string errorMsg = loadProgram(instructionsStr);

        if (errorMsg != "")
        {
            cout << "Error in loading the program!\n"
                 << errorMsg << "\n"
                 << endl;
            break;
        }

        // Execute
        string screenOutput = "";

        // After Run
        if (interface.askIfWrite())
        {
            interface.writeOutput(screenOutput, PC, IR, registers, memory);
        }

        if (!interface.askIfAgain())
        {
            break;
        }
    }
}

string Machine::loadProgram(string &instructionsStr)
{
    int instructionsCount = 0;
    stringstream ss(instructionsStr);
    string instruction;
    string errorMsg = "";

    while (ss >> instruction)
    {
        if (instructionsCount == 128)
        {
            errorMsg = "The program size is too big, the maximum number of instructions is 128.";
        }

        if (instruction.length() > 4)
        {
            errorMsg = "Instruction \"" + instruction + "\"" + " is too long, it should be 4 characters long only!";
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
                errorMsg = string("Invalid Register Address ") + '"' + reg1Addr + '"' + " in the instruction \"" + instruction + "\"";
            }
            if (!isxdigit(memAddr[0]) || !isxdigit(memAddr[1]))
            {
                errorMsg = string("Invalid Memory address ") + '"' + memAddr + '"' + " in the instruction \"" + instruction + "\"";
            }
            break;
        case '4':
            if (instruction[1] != '0')
            {
                errorMsg = string("Invalid Instruction ") + "\"" + instruction + "\"";
            }

            reg1Addr = instruction[2];
            reg2Addr = instruction[3];

            if (!isxdigit(reg1Addr))
            {
                errorMsg = string("Invalid Register Address ") + '"' + reg1Addr + '"' + " in the instruction \"" + instruction + "\"";
            }
            if (!isxdigit(reg2Addr))
            {
                errorMsg = string("Invalid Register Address ") + '"' + reg2Addr + '"' + " in the instruction \"" + instruction + "\"";
            }
            break;
        case '5':
        case '6':
            reg1Addr = instruction[1];
            reg2Addr = instruction[2];
            reg3Addr = instruction[3];
            if (!isxdigit(reg1Addr))
            {
                errorMsg = string("Invalid Register Address ") + '"' + reg1Addr + '"' + " in the instruction \"" + instruction + "\"";
            }
            if (!isxdigit(reg2Addr))
            {
                errorMsg = string("Invalid Register Address ") + '"' + reg2Addr + '"' + " in the instruction \"" + instruction + "\"";
            }
            if (!isxdigit(reg3Addr))
            {
                errorMsg = string("Invalid Register Address ") + '"' + reg3Addr + '"' + " in the instruction \"" + instruction + "\"";
            }
            break;
        case 'c':
            if (instruction[1] != '0' || instruction[2] != '0' || instruction[3] != '0')
            {
                errorMsg = string("Invalid Instruction ") + "\"" + instruction + "\"";
            }
            break;
        default:
            errorMsg = string("Undefined Op-Code ") + '"' + opCode + '"' + " in the instruction \"" + instruction + "\"";
            break;
        }

        if (errorMsg != "")
        {
            return errorMsg;
        }

        stringstream instructionSS(instruction);
        u_int16_t encodedInstruction;

        instructionSS >> hex >> encodedInstruction;
        u_int8_t rightSide = encodedInstruction;
        u_int8_t leftSide = encodedInstruction >> 8;
        memory.setValue(instructionsCount * 2, leftSide);
        memory.setValue(instructionsCount * 2 + 1, rightSide);

        instructionsCount++;
    }

    return errorMsg;
}
