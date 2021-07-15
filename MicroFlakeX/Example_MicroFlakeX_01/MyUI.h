#pragma once
#include "MicroFlakeX.h"

using namespace MicroFlakeX;


class MyUI :
    public MfxUI
{
    //MFXOBJ_ENABLE_REFLECTION;

public:
    MyUI();

    MfxReturn MFX_CALLBACK(Test__00);
    MfxReturn MFX_CALLBACK(Test__01);
    MfxReturn MFX_CALLBACK(Test__02);

protected:
    MfxFlake myFlake;
};

