#pragma once
#include "MfxBase.h"

namespace MicroFlakeX
{
    /***************************************************************
    *	UTF-8
    * 
    *   版本：1.01       作者：yishengjun8  
    * 
    * 
    *   MfxBaseExample_00 提供了MfxBase派生类的构造标准示例
    *   
    *   ①：以public继承MfxBase
    *   ②：在类的声明开始之前，使用 MfxObject; 宏，来辅助生成MicroFlakeX支持。
    *   ③：重载  Colne， operator==， operator= 这三个基础。
    * 
    ****************************************************************/
    class MfxBaseExample_00 :
        public MfxBase
    {
        MfxObject;
    public:
        MfxBaseExample_00();
        ~MfxBaseExample_00();
        virtual MfxReturn Clone(MfxBase** ret);
        virtual BOOL operator==(MfxBase& rhs);
        virtual MfxBase& operator=(MfxBase& rhs);
    public:
        MfxReturn SayHello(MfxString set);
        MfxReturn SayGoodBy();
        MfxReturn SetData(int set);
    protected:
        int myData;
    };
}

