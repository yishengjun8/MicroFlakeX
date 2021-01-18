#pragma once
#include "MfxBaseTest00.h"


namespace MicroFlakeX
{
    class MfxBaseTest01 :
        public MfxBaseTest00
    {
        MfxObject;
    public:
        MfxBaseTest01();
        ~MfxBaseTest01();
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

