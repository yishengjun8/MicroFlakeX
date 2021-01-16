#pragma once
#include "MfxBase.h"

namespace MicroFlakeX
{
    class MfxBaseTest00 :
        public MfxBase
    {
        MfxOBJECT;
    public:
        MfxBaseTest00();
        ~MfxBaseTest00();
        MfxReturn Clone(MfxBase** ret);
        BOOL operator==(MfxBase& rhs);
        MfxBase& operator=(MfxBase& rhs);

    public:
        MfxReturn SayHello(int set);
        MfxReturn SayGoodBy();
        MfxReturn SetData(int set);
    protected:
        int myData;
    };
}

