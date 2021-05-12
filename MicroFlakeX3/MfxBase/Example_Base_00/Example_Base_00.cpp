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

    /*********************************************************
     *   AutoFunc可以根据字符串调用对应的方法
     *
     *   函数原型
     *   MfxReturn AutoFunc(MfxString...);
     *      注意：AutoFunc必须同时传入对应方法的对应参数，如果没有参数，运行时可能会访问到未知地址空间
     *
     *********************************************************/
    strFuncName = MfxText("SayHello");
    temp->AutoFunc(strFuncName, str);

    strFuncName = MfxText("SayGoodBy");
    temp->AutoFunc(strFuncName);

    strFuncName = MfxText("SetData");
    temp->AutoFunc(strFuncName, 9999);

    strFuncName = MfxText("SayGoodBy");
    temp->AutoFunc(strFuncName, 66);

    /*********************************************************
    * 
    *   使用完之后，释放对象。
    *   因为MfxFactory是new出来的对象，需要我们手动释放。
    * 
    *********************************************************/
    delete temp;

    MfxCout << MfxText("main over\n") << std::endl;
    return 0;
}
