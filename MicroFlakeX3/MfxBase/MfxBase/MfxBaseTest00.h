#pragma once
#include "MfxBase.h"

namespace MicroFlakeX
{
    class MfxBaseTest00 :
        public MfxBase
    {
        MfxObject;
    public:
        MfxBaseTest00();
        ~MfxBaseTest00();
        MfxReturn Clone(MfxBase** ret);
        BOOL operator==(MfxBase& rhs);
        MfxBase& operator=(MfxBase& rhs);

        static void Test(MfxBaseTest00* set, int a);
    public:
        MfxReturn SayHello(int set);
        MfxReturn SayGoodBy();
        MfxReturn SetData(int set);
    protected:
        int myData;
    };
}

