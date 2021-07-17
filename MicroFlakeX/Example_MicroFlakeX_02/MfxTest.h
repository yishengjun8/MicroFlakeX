#pragma once
#include "MicroFlakeX.h"


using namespace MicroFlakeX;


class MyClass
{
public:
    MyClass() { num = 66; };
    MyClass(const MyClass& set)
    {
        num = 66;
        std::cout << "Copy" << std::endl;
    }

    int num;
};

class MfxTest :
    public MfxBase
{

    MFX_OBJ_ENABLE_REFLECTION;

public:
    MfxReturn test001(int a = 10);
    MfxReturn test002(MyClass&& a);

};

