#include <iostream>
#include "MfxBase.h"
using namespace MicroFlakeX;


/*********************************************************
*	UTF-8 - win - x86
*
*   版本：1.01       作者：yishengjun8
*
*   这个示例展示了如何使用MfxBase及其组件
*********************************************************/
int main()
{
    MfxCout << MfxText("\nmain begin") <<  std::endl;
    MfxBase* temp = nullptr;
    MfxString str = MfxText("Example_Base_00.cpp");
    MfxString strFuncName;



    /*********************************************************
    *   MfxFactory工厂可以根据字符串直接生成对象
    * 
    *   函数原型
    *   MfxReturn MfxFactory(MfxString, MfxBase**);
    * 
    *   原理 - new一个新对象返回
    *********************************************************/
    MfxFactory(MfxText("MfxBaseExample_00"), &temp);


    //strFuncName = MfxText("SayGoodBy");
    //temp->AutoFunc(strFuncName);

    //strFuncName = MfxText("SayHello");
    //temp->AutoFunc(strFuncName, str);

    //strFuncName = MfxText("SetData");
    //temp->AutoFunc(strFuncName, 1234);

   // strFuncName = MfxText("SayGoodBy");
    //temp->AutoFunc(strFuncName);

    //float fl = 0.6;
    //strFuncName = MfxText("SayTest");
    //temp->AutoFunc(strFuncName, 878, fl, 'M');
    
    //MfxBeginNewThread(temp, MfxText("TestThread"), 212, 323);

    //PTP_TIMER myTimer;
    //MfxBeginNewTimer(myTimer, temp, MfxText("TestTimer"), 434, 2000);
    MfxSignal<int, double, char> myOneSignal;
    MfxSignal<> myTwoSignal;

    myTwoSignal.PushBackReceiver(temp, MfxText("SayGoodBy"));
    myOneSignal.PushBackReceiver(temp, MfxText("SayTest"));

    myOneSignal.SendSignal(878, 85.5, 'A');
    myTwoSignal.SendSignal();

    MfxCout << std::endl;
    MfxCout << std::endl;
    MfxCout << std::endl;

    myTwoSignal.PostSignal();
    myOneSignal.PostSignal(868, 86.5, 'B');
    myOneSignal.PostSignal(858, 87.5, 'C');
    myOneSignal.PostSignal(848, 88.5, 'D');

    /*********************************************************
    * 
    *   使用完之后，释放对象。
    *   因为MfxFactory是new出来的对象，需要我们手动释放。
    * 
    *********************************************************/
    //delete temp;
    int a;
    std::cin >> a;

    delete temp;
    MfxCout << MfxText("main over\n") << std::endl;
    return 0;
}
