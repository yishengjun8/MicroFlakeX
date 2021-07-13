#pragma once
#include "MicroFlakeX.h"


using namespace MicroFlakeX;

class MfxTest :
    public MfxBase
{

    MFXOBJ_ENABLE_REFLECTION;

public:
    MfxReturn test001(int a);


};

