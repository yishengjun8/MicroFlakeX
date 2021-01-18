#pragma once
#include "MfxBaseTest01.h"


namespace MicroFlakeX
{
    class MfxBaseTest02 :
        public MfxBaseTest01
    {
        MfxObject;
    public:
        MfxBaseTest02();
        ~MfxBaseTest02();
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

