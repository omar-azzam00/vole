#include <iostream>
#include <fstream>
#include "Interface.h"

using namespace std;

void Interface::menu()
{
    showBanner();
    string c;
    cout << "1)" << "Load a file of instructions" << endl;
    cout << "2)" << "Showing the status and execution process" << endl;
    cout << "3)" << "Exit" << endl;
    cin >> c;
    if (c == "1")
    {
        readFile();
    }
    else if (c == "2")
    {
        writeOutput();
        sayDone();
    }
    else if (c == "3")
    {
        exit(0);
    }
    else
    {
        cout << "invalid input" << endl;
    }
    menu();
}

void Interface::showBanner()
{
    cout << "this is a simulation of vole machine language" << endl;
}

string Interface::readFile()
{
    string filename;
    string instruction;
    cin >> filename;
    ifstream infile;
    infile.open(filename);

    if (!infile)
    {
        cout << "this file is not right please try again" << endl;
        readFile();
    }
    string line;

    while (getline(infile, line))
    {
        instruction += line;
    }
    cout << instruction;
    infile.close();

    return instruction;
}

void Interface::writeOutput()
{
    // cout << "Execution process" << endl;
    // for (int i = 0; i < 10; ++i) {
    //     cout << "PC: " << i << " "<< "IR" << i << endl;
    // }
    // cout << "Registers" << endl;
    // cout << "Memory" << endl;
    // for (int i = 0; i < 16; ++i) {
    //     for (int j = 0; j < 16; ++j) {
    //         cout << i << " " ;
    //         if (j == 15){
    //             cout << endl;
    //         }
    //     }

    // }
    // menu();
}

void Interface::sayDone()
{
    //  cout << "the process is done successfully" << endl;
}