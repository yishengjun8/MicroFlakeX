#include "pch.h"
#include "MfxBaseExample_00.h"

/***************************************************************
*	UTF-8
* 
*   版本：1.01       作者：yishengjun8  
* 
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
*			MfxObject_Init_0(MfxBaseExample_00)
*			MfxObject_Init_1(MfxBaseExample_00, SayHello)
*			MfxAutoFunc_AutoEnum_2(MfxBaseExample_00, 1, SayHello)
*			MfxObject_Init_2(MfxBaseExample_00, MfxBase);
*				//实现MfxObject_Init，但是注册的AutoFunc方法数量为1
* 
*			MfxObject_Init_0(MfxBaseExample_00)
*			MfxObject_Init_1(MfxBaseExample_00, SayGoodBy)
*			MfxAutoFunc_AutoEnum_2(MfxBaseExample_00, 0, SayGoodBy, 1, SetData)
*			MfxObject_Init_2(MfxBaseExample_00, MfxBase);
*				//实现MfxObject_Init，但是注册的AutoFunc方法数量为2
* 
*			MfxObject_Init_0(MfxBaseExample_00)
*			MfxObject_Init_1(MfxBaseExample_00, SetData)
*			MfxAutoFunc_AutoEnum_2(MfxBaseExample_00, 1, SetData, 1, SayHello, 0, SayGoodBy)
*			MfxObject_Init_2(MfxBaseExample_00, MfxBase);
*				//实现MfxObject_Init，但是注册的AutoFunc方法数量为3
*			如果要添加更多的AutoFunc方法，方法同上
* 
*
*	②：如果需要为AutoFunc添加反射方法，请在MfxObject_Init_1和MfxObject_Init_2
*		声明中间，增加AutoFunc注册。
* 
*			Ⅰ  -  AutoFunc注册之MfxAutoFunc_AutoEnum(...)宏
*					MfxAutoFunc_AutoEnum(...)是一个变长参数宏，其参数分段为：1、2、2、2...
*				第一段：第一个参数 - 需要注册的类
*				第二段以及之后的段：第一个参数标识函数有几个输入变量，第二个参数是函数名称
* 
*			Ⅱ  -  AutoFunc注册之MfxAutoFunc_AutoEnum_n(...)宏
*					MfxAutoFunc_AutoEnum_n(...)是一个变长参数宏，其参数分段与MfxAutoFunc_AutoEnum(...)宏一样。
*					唯一的区别是，这个宏需要手动填写n处，告知编译器输入的函数数量。
* 
*				下面两段代码是等价的
*				MfxObject_Init_0(MfxBaseExample_00)
*				MfxObject_Init_1(MfxBaseExample_00, SayHello)
*				MfxAutoFunc_AutoEnum_2(MfxBaseExample_00, 1, SayHello, 0, SayGoodBy, 1, SetData)
*				MfxObject_Init_2(MfxBaseExample_00, MfxBase);
* 
*				MfxObject_Init_0(MfxBaseExample_00)
*				MfxObject_Init_1(MfxBaseExample_00, SayHello)
*				MfxAutoFunc_AutoEnum(MfxBaseExample_00, 1, SayHello, 0, SayGoodBy, 1, SetData)
*				MfxObject_Init_2(MfxBaseExample_00, MfxBase);
*			
*			Ⅲ  -  AutoFunc注册之MfxAutoFunc_n(OBJ, AUTO_FUNC, GOTO_NEXT)宏
*					MfxAutoFunc_n(OBJ, AUTO_FUNC, GOTO_NEXT)宏是最基础的注册宏，n表示方法的参数个数。
*					第一个参数 - 需要注册的类
*					第二个参数 - 需要注册的方法
*					第三个参数 - 下一个注册的方法(如果没有下一个需要注册的方法，则填写END)
* 
*				下面两段代码是等价的
*				MfxObject_Init_0(MfxBaseExample_00)
*				MfxObject_Init_1(MfxBaseExample_00, SayHello)
*				MfxAutoFunc_AutoEnum(MfxBaseExample_00, 1, SayHello, 0, SayGoodBy, 1, SetData)
*				MfxObject_Init_2(MfxBaseExample_00, MfxBase);
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
* 
* 
* MfxAutoFunc_AutoEnum(MfxBaseExample_00, 1, SayHello, 0, SayGoodBy, 1, SetData)
****************************************************************/

MfxObject_Init_0(MfxBaseExample_00)
{
	//执行一些语句，这些语句将在程序从入口函数开始执行之前执行
}
MfxObject_Init_1(MfxBaseExample_00, SetData)
MfxAutoFunc_AutoEnumBig(MfxBaseExample_00, \
	1, SetData, \
	1, SayHello, \
	\
	2, TestTimer, \
	2, TestThread, \
	\
	0, SayGoodBy, \
	4, SayTest,\
	\
	END, END);
MfxObject_Init_2(MfxBaseExample_00, MfxBase);

MicroFlakeX::MfxBaseExample_00::MfxBaseExample_00()
{
	myData = 0;
	MfxCout << MfxText(">> MfxBaseExample_00 Creat <<\n");
}

MicroFlakeX::MfxBaseExample_00::~MfxBaseExample_00()
{
	MfxCodeLock(this);
	MfxCout << MfxText(">> MfxBaseExample_00 Release <<\n");
	MfxCout << MfxText(">> MfxBaseExample_00 myData = ") << myData << " <<\n";
}

MfxReturn MicroFlakeX::MfxBaseExample_00::Clone(MfxBase** ret)
{
	MfxCodeLock(this);
	return Mfx_Return_Fine;
}


MfxBase& MicroFlakeX::MfxBaseExample_00::operator=(MfxBase& rhs)
{
	MfxCodeLock(this);
	SetData(myData);
	return *this;
}

bool MicroFlakeX::MfxBaseExample_00::operator==(MfxBase& rhs)
{
	return 0;
}

MfxReturn MicroFlakeX::MfxBaseExample_00::SayHello(MfxString set)
{
	MfxCodeLock(this);

	MfxCout << MfxText("In MfxBaseExample_00 SayHello Str = ") << set << std::endl;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxBaseExample_00::SayGoodBy()
{
	MfxCodeLock(this);

	MfxCout << MfxText("In MfxBaseExample_00 SayGoodBy") << std::endl;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxBaseExample_00::SetData(int set)
{
	/***************************************************************
	*	MfxCodeLock(this);
	*	
	*	凡是写了MfxCodeLock(this);宏标识的方法，互相之间在同一时间仅能允许一个正在执行，
	*	其他的方法会被挂起等待。
	* 
	*	即线程安全。
	****************************************************************/
	MfxCodeLock(this);

	myData = set;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxBaseExample_00::TestTimer(WPARAM wParam, LPARAM lParam)
{
	MfxCout << MfxText("In TestTimer wParam: ") << wParam << MfxText(" lParam: ") << lParam << std::endl;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxBaseExample_00::TestThread(WPARAM wParam, LPARAM lParam)
{
	MfxCout << MfxText("In TestThread wParam: ") << wParam << MfxText(" lParam: ") << lParam << std::endl;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxBaseExample_00::SayTest(int a, int b, int c, int d)
{
	MfxCout << MfxText("In MfxBaseExample_00 SayTest argv a: ") << a << MfxText(" argv b: ") << b << MfxText(" argv c: ") << c << MfxText(" argv d: ") << d << std::endl;
	
	return Mfx_Return_Fine;
}
