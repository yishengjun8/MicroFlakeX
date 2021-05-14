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

        virtual bool operator==(MfxBase& rhs);

        virtual MfxBase& operator=(MfxBase& rhs);
    public:        
        MfxReturn SayGoodBy();

        MfxReturn SayHello(MfxString set);

        MfxReturn SetData(int set);
        MfxReturn SayTest(int a, int b, int c, int d);

        MfxReturn TestTimer(WPARAM wParam, LPARAM lParam);
        MfxReturn TestThread(WPARAM wParam, LPARAM lParam);


    protected:
        int myData;
    };
}

