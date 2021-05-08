
#include <iostream>
#include "MfxBase.h"
using namespace MicroFlakeX;

int main()
{
    MfxBase* temp = nullptr;

    MfxBaseFactory(MfxText("MfxBaseTest00"), &temp);
    temp->AutoFunc(MfxText("SayHello"), 66);

    std::cout << "Hello World!\n";
    return 0;
}
