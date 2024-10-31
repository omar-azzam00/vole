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
    string filename;
    string instruction;

    cout << "Enter the name of the instructions file: ";

    // cin >> filename;
    getline(cin, filename);
    // Omar: getline is better because user might enter space seperated text.

    ifstream infile;
    infile.open(filename);

    if (!infile)
    {
        cout << "This file can't be opened, please try again!\n";
        readFile();
    }

    cout << endl;

    // string line;

    // while (getline(infile, line))
    // {
    //     instruction += line;
    // }

    // Omar: The previous while loop will not add new line characters to the string.
    char c;

    while (infile.get(c))
    {
        instruction += c;
    }

    // Omar: we don't want to print the instructions we read.
    // cout << instruction;

    infile.close();

    return instruction;
}

bool askIfWrite()
{
    cout << "Do you want to see screen output and machine status ?\n";

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
        else if (tolower(choice[0] == 'n'))
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

    cout << setw(64) << " SCREEN OUTPUT " << '\n';
    cout << screenOutput;
    if (screenOutput[screenOutput.length() - 1] != '\n')
    {
        cout << '\n';
    }
    cout << setw(64) << '=' << endl;

    cout << setw(64) << " REGISTERS STATE " << '\n';
    cout << "PC: " << hex << PC << ", " << "IR: " << IR << ", ";
    for (int i = 0; i < REGISTERS_COUNT; i++)
    {
        cout << "R" << dec << i << ": " << hex << (int)registers.getValue(i);
        if (i != REGISTERS_COUNT - 1)
        {
            cout << ", ";
        }
    }
    cout << '\n'
         << setw(64) << '=' << endl;

    cout << setw(64) << " MEMORY STATE " << '\n';
    for (int i = 0; i < MEMORY_COUNT; i++)
    {
        cout << "Addr " << hex << i << ": " << (int)memory.getValue(i);
        if (i != MEMORY_COUNT - 1)
        {
            cout << ", ";
        }
    }
    cout << '\n'
         << setw(64) << '=' << "\n"
         << endl;

    // Reset cout stream
    cout << dec << setfill(' ');
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
        else if (tolower(choice[0] == 'n'))
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