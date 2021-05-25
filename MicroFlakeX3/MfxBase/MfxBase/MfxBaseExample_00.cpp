#include "pch.h"
#include "MfxBaseExample_00.h"

/***************************************************************
*	UTF-8
* 
*   版本：1.01       作者：yishengjun8  
* 
*   MfxBaseExample_00 提供了MfxBase派生类的构造标准示例
*	
*	①：注意，在声明MfxObject_Init_1的时候，第二个参数为AutoFunc的起始函数。
*		如果本方法没有为AutoFunc添加反射方法，则填写END。
*		
*		书写的时候注意，MfxObject_Init_1第二个参数一定要填对！
*			MfxObject_Init_0(MfxBaseExample_00)
*			MfxObject_Init_1(MfxBaseExample_00, END)
*			MfxObject_Init_2(MfxBaseExample_00, MfxBase);
*				//实现MfxObject_Init，但是注册的AutoFunc方法数量为0
*
*	②：如果需要为AutoFunc添加反射方法，请在MfxObject_Init_1和MfxObject_Init_2
*		声明中间，增加AutoFunc注册。
* 
*				下面两段代码是等价的
*				MfxObject_Init(MfxBaseExample_00)
*				MfxObject_EndInit(MfxBaseExample_00, MfxBase, 1, SayHello, 0, SayGoodBy, 1, SetData)
* 
*				MfxObject_Init_0(MfxBaseExample_00)
*				MfxObject_Init_1(MfxBaseExample_00, SayHello)
*				MfxAutoFunc_1(MfxBaseExample_00, SayHello, SayGoodBy)
*				MfxAutoFunc_0(MfxBaseExample_00, SayGoodBy, SetData)
*				MfxAutoFunc_1(MfxBaseExample_00, SetData, END)
*				MfxObject_Init_2(MfxBaseExample_00, MfxBase);
*
* 
*	③：如果你需要在程序从入口函数开始之前，就执行一些语句，
*		请在MfxObject_Init_0宏和MfxObject_Init_1宏之间添加。
*		或者在MfxObject_Init 和 MfxObject_EndInit之间添加
****************************************************************/
MfxObject_Init(MfxBaseExample_00)
MfxObject_EndInit(MfxBaseExample_00, MfxBase, \
	1, SetData, \
	1, SayHello, \
	\
	2, TestTimer, \
	2, TestThread, \
	\
	0, SayGoodBy, \
	3, SayTest);

/***************************************************************
****************************************************************/
MicroFlakeX::MfxBaseExample_00::MfxBaseExample_00()
{
	myData = 0;

	MfxCout << std::endl;
	MfxCout << MfxText(">> MfxBaseExample_00 Creat <<");
	MfxCout << std::endl;
}

MicroFlakeX::MfxBaseExample_00::~MfxBaseExample_00()
{
	MfxCodeLock(this);

	MfxCout << std::endl;
	MfxCout << MfxText(">> MfxBaseExample_00 Release <<");
	MfxCout << std::endl;
}

/***************************************************************
* 
****************************************************************/
MfxReturn MicroFlakeX::MfxBaseExample_00::SayGoodBy()
{
	MfxCodeLock(this);

	MfxCout << std::endl;
	MfxCout << MfxText("In MfxBaseExample_00::SayGoodBy") << std::endl;
	MfxCout << std::endl;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxBaseExample_00::SayHello(MfxString set)
{
	MfxCodeLock(this);

	MfxCout << std::endl;
	MfxCout << MfxText("In MfxBaseExample_00::SayHello Str = ") << set;
	MfxCout << std::endl;

	return Mfx_Return_Fine;
}


/***************************************************************
*	MfxCodeLock(this);
*
*	凡是写了MfxCodeLock(this);宏标识的方法，互相之间在同一时间仅能允许一个正在执行，
*	其他的方法会被挂起等待。
*
*	即线程安全。
****************************************************************/
MfxReturn MicroFlakeX::MfxBaseExample_00::SetData(int set)
{
	MfxCodeLock(this);

	myData = set;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxBaseExample_00::SayTest(int i, double f, char c)
{
	MfxCout << std::endl;
	MfxCout << MfxText("In MfxBaseExample_00::SayTest [argv i: ") << i << MfxText(" ] [argv f: ") << f << MfxText(" ] [argv c: ") << c << MfxText(" ]");
	MfxCout << std::endl;

	return Mfx_Return_Fine;

}


/***************************************************************
*
*
*
****************************************************************/
MfxReturn MicroFlakeX::MfxBaseExample_00::TestTimer(WPARAM wParam, LPARAM lParam)
{
	MfxCout << std::endl;
	MfxCout << MfxText("In MfxBaseExample_00::TestTimer wParam: ") << wParam << MfxText(" lParam: ") << lParam;
	MfxCout << std::endl;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxBaseExample_00::TestThread(WPARAM wParam, LPARAM lParam)
{
	MfxCout << std::endl;
	MfxCout << MfxText("In MfxBaseExample_00::TestThread wParam: ") << wParam << MfxText(" lParam: ") << lParam;
	MfxCout << std::endl;

	return Mfx_Return_Fine;
}