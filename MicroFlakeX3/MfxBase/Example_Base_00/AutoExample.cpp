#include "AutoExample.h"
MfxObject_Init(AutoExample)
{

}
MfxObject_EndInit(AutoExample, MfxBase, \
    0, SayHello, \
    1, OutPutString, \
    \
    \
    1, SetData, \
    1, GetData, \
    \
    1, Timer, \
    1, Thread
);


AutoExample::AutoExample()
{
    myMemberLock.WaitLock(&myData);
    myData = 99;
    myMemberLock.UnLock(&myData);
}

MfxReturn AutoExample::SayHello()
{
    myMemberLock.WaitLock(&myData);
    std::wcout << MfxText("AutoExample::SayHello()") << std::endl;
    myMemberLock.UnLock(&myData);
    return Mfx_Return_Fine;
}

MfxReturn AutoExample::OutPutString(MfxString set)
{
    myMemberLock.WaitLock(&myData);
    std::wcout << "AutoExample::OutPutString(" << set << MfxText(")") << std::endl;
    myMemberLock.UnLock(&myData);
    return Mfx_Return_Fine;
}

MfxReturn AutoExample::SetData(int set)
{
    myMemberLock.TryWaitLock(&myData);
    myData = set;
    //myMemberLock.UnLock(&myData);
    return Mfx_Return_Fine;
}

MfxReturn AutoExample::GetData(int* ret)
{
    myMemberLock.TryWaitLock(&myData);
    ret ? *ret = myData : 0;
    std::wcout << "AutoExample::myData = " << myData << std::endl;
    myMemberLock.UnLock(&myData);
    return Mfx_Return_Fine;
}

MfxReturn AutoExample::Timer(MfxParam param)
{
    
    //std::wcout << "AutoExample::Timer(" << GetParam(param, int, 0) << MfxText(")") << std::endl;
    return Mfx_Return_Fine;
}

MfxReturn AutoExample::Thread(MfxParam param)
{

    //std::wcout << "AutoExample::Thread(" << GetParam(param, char, 0) << MfxText(")") << std::endl;
    return Mfx_Return_Fine;
}
