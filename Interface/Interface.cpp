#include <iostream>
#include <fstream>
#include <iomanip>
#include "Interface.h"
#include "../Memory/Memory.h"
#include "../Registers/Registers.h"

using namespace std;

void Interface::showBanner()
{
    cout << "This is a simulation of Vole machine.\n"
         << endl;
}

string Interface::readFile()
{
    ifstream file;
    string fileContent = "";
    string fileName;

    while (true)
    {
        cout << "Enter the name of the instructions file: ";
        getline(cin, fileName);

        file.open(fileName);
        if (!file)
        {
            cout << "This file can't be opened, please try again!\n";
            continue;
        }

        char ch;
        while (file.get(ch))
        {
            fileContent += ch;
        }

        file.close();
        cout << endl;
        return fileContent;
    }
}

bool Interface::askIfWrite()
{
    cout << "Do you want to see screen output and machine status ?\n";

    while (true)
    {
        cout << "Enter \"y\" or \"n\": ";
        string choice;
        getline(cin, choice);

        if (choice.length() == 1 && tolower(choice[0]) == 'y')
        {
            cout << endl;
            return true;
        }
        else if (choice.length() == 1 && tolower(choice[0]) == 'n')
        {
            cout << endl;
            return false;
        }
        else
        {
            cout << "Invalid input, please try again!\n";
        }
    }
}

void Interface::writeOutput(string &screenOutput, uint8_t &PC, uint16_t &IR, Registers &registers, Memory &memory)
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

        if (choice.length() == 1 && tolower(choice[0]) == 'y')
        {
            cout << endl;
            return true;
        }
        else if (choice.length() == 1 && tolower(choice[0]) == 'n')
        {
            cout << endl;
            return false;
        }
        else
        {
            cout << "Invalid input, please try again!\n";
        }
    }
}
