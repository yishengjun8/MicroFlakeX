#include <iostream>
#include "MfxBase.h"
using namespace MicroFlakeX;



MfxThreadServer* myThreadServer = new MfxThreadServer;
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


    strFuncName = MfxText("SayGoodBy");
    temp->AutoFunc(strFuncName);

    strFuncName = MfxText("SayHello");
    temp->AutoFunc(strFuncName, str);

    strFuncName = MfxText("SetData");
    temp->AutoFunc(strFuncName, 1234);

    strFuncName = MfxText("SayGoodBy");
    temp->AutoFunc(strFuncName);

    strFuncName = MfxText("SayTest");
    temp->AutoFunc(strFuncName, 878, 767, 656, 545);
    
    myThreadServer->BeginNewThread(temp, MfxText("TestThread"), 212, 323);

    PTP_TIMER myTimer;
    myThreadServer->BeginNewTimer(myTimer, temp, MfxText("TestTimer"), 434, 2000);

    /*********************************************************
    * 
    *   使用完之后，释放对象。
    *   因为MfxFactory是new出来的对象，需要我们手动释放。
    * 
    *********************************************************/
    //delete temp;
    int a;
    std::cin >> a;
    MfxCout << MfxText("main over\n") << std::endl;
    return 0;
}
