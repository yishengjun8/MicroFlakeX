
#include <iostream>
#include "MfxGraph.h"
using namespace MicroFlakeX;

int main()
{
    MfxBase* temp = nullptr;
    MfxRect myRect;
    MfxImage myImage;

    MfxBaseFactory(MfxText("MfxRect"), &temp);
    //temp->AutoFunc(MfxText("SayHello"), 10);

    std::cout << "Hello World!\n";
    return 0;
}
