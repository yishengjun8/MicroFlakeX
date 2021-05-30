#pragma once
#include "MfxAppFrame.h"

using namespace MicroFlakeX;


class MyUI :
    public MfxUI
{
    MfxObject;
public:
    MyUI();
    MfxReturn MfxCallBack(Test__00);
    MfxReturn MfxCallBack(Test__01);

    MfxFlake myFlake;
};

