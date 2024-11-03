#include "./Machine/Machine.h"

int main()
{
    Machine *machine = new Machine();
    machine->showBanner();
    while (machine->runMachine())
    {
        machine = new Machine();
    }

    return 0;
}