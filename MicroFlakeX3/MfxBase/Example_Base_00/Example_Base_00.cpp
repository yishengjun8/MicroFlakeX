
#include <iostream>
#include "MfxBase.h"
using namespace MicroFlakeX;
using namespace std;


int main()
{
    cout << endl;
    MfxBase* temp = nullptr;

    MfxFactory(MfxText("MfxBaseTest00"), &temp);

    MfxString func = MfxText("SayHello");

    temp->AutoFunc(func, 66);

    func = MfxText("SayGoodBy");

    temp->AutoFunc(func, 66);


    cout << endl;
    return 0;
}
