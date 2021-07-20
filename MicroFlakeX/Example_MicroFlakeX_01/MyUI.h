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
    MfxReturn MFX_CALLBACK(LButtonClick);
    MfxReturn MFX_CALLBACK(RButtonClick);
    MfxReturn MFX_CALLBACK(Test__02);

protected:
    MfxFlake myFlake;

    __MfxGlide myGlide;
};

