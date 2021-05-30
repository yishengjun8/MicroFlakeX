#pragma once
#include "MfxBase.h"
using namespace MicroFlakeX;

class AutoExample :
	public MfxBase
{
	MfxObject;
public:
    AutoExample();

    MfxReturn SayHello();

    MfxReturn OutPutString(MfxString set);

    MfxReturn SetData(int set);
    MfxReturn GetData(int* ret);

    MfxReturn Timer(MfxParam param);
    MfxReturn Thread(MfxParam param);

public:
    int myData;
};

