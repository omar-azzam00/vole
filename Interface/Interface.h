#if !defined(_INTERFACE_H)
#define _INTERFACE_H

#include <iostream>

using namespace std;

class Interface
{
public:
    void menu();
    void showBanner();
    string readFile();
    void writeOutput();
    void sayDone();
};

#endif // _INTERFACE_H
