#include <iostream>
#include <fstream>
#include <iomanip>
#include "Interface.h"
#include "../Memory/Memory.h"
#include "../Registers/Registers.h"

using namespace std;

// void Interface::menu()
// {
//     showBanner();
//     string c;
//     cout << "1)" << "Load a file of instructions" << endl;
//     cout << "2)" << "Showing the status and execution process" << endl;
//     cout << "3)" << "Exit" << endl;

//     cout << "Choose an option: "; // Omar: Propmt the user to enter input.

//     // cin >> c;
//     getline(cin, c); // Omar: getline is better because user might enter space seperated content.

//     if (c == "1")
//     {
//         return 1;
//     }
//     else if (c == "2")
//     {
//         writeOutput();
//         sayDone();
//     }
//     else if (c == "3")
//     {
//         exit(0);
//     }
//     else
//     {
//         cout << "Invalid input, try again!" << endl;
//     }
// }

void Interface::showBanner()
{
    cout << "This is a simulation of Vole machine\n"
         << endl;
}

string Interface::readFile()
{
    ifstream infile;
    string instruction = "";
    string filename;

    while (true)
    {
        cout << "Enter the name of the instructions file: ";
        getline(cin, filename);

        infile.open(filename);
        if (!infile)
        {
            cout << "This file can't be opened, please try again!\n";
            continue;
        }

        char c;
        while (infile.get(c))
        {
            instruction += c;
        }

        infile.close();
        cout << endl;
        return instruction;
    }
}

bool Interface::askIfWrite()
{
    cout << "Do you want to see screen output and machine status of this program ?\n";

    while (true)
    {
        cout << "Enter \"y\" or \"n\": ";
        string choice;
        getline(cin, choice);

        if (tolower(choice[0]) == 'y')
        {
            cout << endl;
            return true;
        }
        else if (tolower(choice[0]) == 'n')
        {
            cout << endl;
            return false;
        }
        else
        {
            cout << "Invalid input, try again!\n";
        }
    }
}

void Interface::writeOutput(string &screenOutput, u_int8_t &PC, u_int16_t &IR, Registers &registers, Memory &memory)
{
    cout << setfill('=');

    cout << setw(32) << " SCREEN OUTPUT " << setw(32) << '=' << '\n';
    cout << screenOutput;
    if (screenOutput[screenOutput.length() - 1] != '\n')
    {
        cout << '\n';
    }
    cout << setw(64) << '=' << "\n"
         << endl;

    cout << setw(32) << " REGISTERS STATE " << setw(32) << '=' << '\n';

    cout << setfill(' ') << "PC " << ": 0x" << hex << (int)PC << "\n"
         << "IR " << ": 0x" << IR << "\n"
         << left;
    for (int i = 0; i < REGISTERS_COUNT; i++)
    {
        cout << "R" << dec << setw(2) << i << ": " << hex << "0x" << (int)registers.getValue(i);
        if (i != REGISTERS_COUNT - 1)
        {
            cout << "\n";
        }
    }
    cout << '\n'
         << right
         << setfill('=')
         << setw(64) << '=' << "\n"
         << endl;

    cout << setw(32) << " MEMORY STATE " << setw(32) << '=' << '\n'
         << setfill(' ') << left;
    for (int i = 0; i < MEMORY_COUNT; i++)
    {
        cout << "Addr 0x" << setw(2) << hex << i << ": " << "0x" << (int)memory.getValue(i);
        if (i != MEMORY_COUNT - 1)
        {
            cout << "\n";
        }
    }
    cout << setfill('=') << '\n'
         << right
         << setw(64) << '=' << "\n"
         << endl;

    // Reset cout stream
    cout << left << dec << setfill(' ');
}

bool Interface::askIfAgain()
{
    cout << "Do you want to run another instructions file ?\n";

    while (true)
    {
        cout << "Enter \"y\" or \"n\": ";
        string choice;
        getline(cin, choice);

        if (tolower(choice[0]) == 'y')
        {
            cout << endl;
            return true;
        }
        else if (tolower(choice[0]) == 'n')
        {
            cout << endl;
            return false;
        }
        else
        {
            cout << "Invalid input, try again!\n";
        }
    }
}

void Interface::sayDone()
{
    cout << "Everything is done successfully!\n"
         << endl;
}