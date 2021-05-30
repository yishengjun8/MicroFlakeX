#include "MfxBase.h"
#include "AutoExample.h"
using namespace MicroFlakeX;

int main()
{
    int param1 = 1;
    char param2 = 'c';
    double param3 = 55.55;

    MfxParam myParam1, myParam2;

    myParam1.push_back(param1);
    myParam1.push_back(myParam2);
    myParam1.push_back(param2);

    GetParam(myParam1, MfxParam, 1).push_back(param3);
    GetParam(myParam1, MfxParam, 1).push_back((int)99);

    std::cout << GetParam(myParam1, int, 0) << std::endl;

    std::cout << GetParam(GetParam(myParam1, MfxParam, 1), double, 0) << std::endl;
    std::cout << GetParam(GetParam(myParam1, MfxParam, 1), int, 1) << std::endl;

    AutoExample myAutoExample;

    MfxSignal mySignal;

    //mySignal.PushFrontReceiver(&myAutoExample, MfxText("OutPutString"));

    //mySignal.PostSignal(MfxString(L"<<PostSignal>>"));

    //mySignal.RemoveReceiver(&myAutoExample, MfxText("OutPutString"));

    mySignal.PushFrontReceiver(&myAutoExample, MfxText("SetData"));

    mySignal.PostSignal((int)99);
    myAutoExample.GetData(nullptr);
    /**/


    return 0;
}
