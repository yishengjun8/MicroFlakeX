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
    * 
    ****************************************************************/
    class MfxBaseExample_00 :
        public MfxBase
    {
        MfxObject;
    public:
        MfxBaseExample_00();
        ~MfxBaseExample_00();
    public:        
        MfxReturn SayGoodBy();

        MfxReturn SayHello(MfxString set);

        MfxReturn SetData(int set);
        MfxReturn SayTest(int i, double f, char c);

        MfxReturn TestTimer(WPARAM wParam, LPARAM lParam);
        MfxReturn TestThread(WPARAM wParam, LPARAM lParam);


    protected:
        int myData;
    };
}

