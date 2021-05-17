#pragma once

/**************************************************************************************************
*	UTF-8 - win - x86
* 
*   版本：1.01       作者：yishengjun8     
*	
* 
*	MfxBase.h	提供了构造	MicroFlakeX	的基础类和基础支持
*	
*	强制 - 
*	1、所有的	MicroFlakeX子类	必须继承于	MfxBase基类
*	2、所有的类必须实现 'operator=' 和 'Clone' 
*	3、所有的 MfxBase 子类，都必须声明 MfxObject宏
*	4、所有的方法、函数返回值必须为 MfxReturn，
*	5、任何添加到 AutoFunc 的方法，不允许重载、不允许使用右值引用、不允许使用引用传递。
* 
*	建议 - 
*	1、每次调用方法之后，都判断 MfxReturn，是否成功
*	2、实现类的 'operator==' ，以方便判断两个对象是否相等
* 
* 
*	关于	AutoFunc	的继承处理
*			如果子类实现了一个和父类同名的方法，并且都注册了 AutoFunc，
*		那么，通过 AutoFunc 调用该方法的顺序为：子类，即父类被子类覆盖。
*			如果继承方式为：基类->类0->类1->类2，并且类0 、类2都注册了
*		'Hello()'，此时调用	AutoFunc	的调用顺序为：类2::Hello()，即类0被覆盖。
* 
* 
**************************************************************************************************/

#ifdef MFXDLL_BUILDING
#define MFX_PORT __declspec(dllexport)
#else
#define MFX_PORT __declspec(dllimport)
#pragma comment(lib, "MfxBase.lib")

/* Windows 头文件 */
#include <windows.h>
/**/

/* 可变参数 - 类型获取 */
#include <stdarg.h>
#include <typeinfo>
/**/

/* STL模板库 */
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <mutex>
#include <stack>
#include <thread>
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
/**/
#endif

namespace MicroFlakeX
{
	/***************************************************************
	*	MfxReturn
	* 
	*	返回值标识符。
	*	可返回	Mfx_Return_XXX	宏来标识返回结果
	*	
	*	返回值小于 0 表示函数失败。
	*	大于等于 0 表示函数成功或者函数正常执行
	* 
	****************************************************************/
	typedef long MfxReturn;

#define Mfx_Return_Fine 0
#define Mfx_Return_Fail -1

#define Mfx_Failed(MR) (((MfxReturn)(MR)) < 0)
#define Mfx_Seccess(MR) (((MfxReturn)(MR)) >= 0)

	/***************************************************************
	*	MfxString 字符串
	* 
	*	MfxString自动扩展到适合当前编码的std::string或者std::wstring
	* 
	****************************************************************/
#define MfxString __MfxString

	/***************************************************************
	*	字符集自动展开宏
	*
	*	MfxText() 内的字符串将会自动展开到适合当前的编码状态
	*
	****************************************************************/
#define MfxText(str) __MfxText(str)

	/***************************************************************
	*	cout输出自动展开宏
	*
	*	cout自动扩展到适合当前编码的std::cout或者std::wcout
	*
	****************************************************************/
#define MfxCout __MfxCout

#ifdef UNICODE
#define __MfxCout std::wcout
#define __MfxText(str) L##str
#define __MfxString MfxStringW
#elif 
#define __MfxCout std::cout
#define __MfxText(str) str
#define __MfxString MfxStringA;
#endif

	typedef std::string MfxStringA;
	typedef std::wstring MfxStringW;
}

namespace MicroFlakeX
{
	class MFX_PORT MfxBase;


	/***************************************************************
	* 
	*	MfxObject宏：
	*		1、MfxBase	的子类需要在声明中添加	MfxObject宏	来声明	MicroFlakeX	的扩展功能
	* 
	*		2、MfxBase	的子类至少有一个无参构造函数。
	*		这个构造函数将在程序开始运行之前被创建一次，用以初始化	MicroFlakeX扩展功能。
	*	
	*		3、如果声明了	MfxObject宏	那么该方法至少需要优先实现以下三个宏扩展 ：
	*			①：MfxObject_Init_0(object)
	*				{
	*					//这里可以添加你需要在程序开始运行之前就初始化或者加载的一些内容
	*				}
	*			②：MfxObject_Init_1(object, END)
	*			③：MfxObject_Init_2(object, fatherObject)
	*
	*		3、MicroFlakeX扩展的反射就是 ‘通过字符串调用对象的方法’。
	*			如果你需要使用	MicroFlakeX扩展的反射功能，需要自行添加需要反射的函数。
	*			①：MfxAutoFunc_AutoEnum自动扩展反射 - 最高支持扩展62个函数
	*			②：MfxAutoFunc_AutoEnum_半自动扩展反射 - 最高支持扩展126个函数
	*			③：MfxAutoFunc_手动反射 - 无上限
	*
	*	更加详细的MfxObject宏示例请参照	MfxBaseExample_00.h	
	*	
	****************************************************************/
#define MfxObject __MfxObject

#define MfxObject_Init_0(OBJ) __MfxObject_Init_0(OBJ)
#define MfxObject_Init_1(OBJ, GOTO_BEGIN) __MfxObject_Init_1(OBJ, GOTO_BEGIN)
#define MfxObject_Init_2(OBJ, FATHER_OBJ) __MfxObject_Init_2(OBJ, FATHER_OBJ)

#define MfxAutoFunc_AutoEnum(...) CONNECT(__MfxAutoFunc_AutoEnum, (__VA_ARGS__))
#define MfxAutoFunc_AutoEnumBig(...) CONNECT(MfxAutoFunc_Enum_126, (__VA_ARGS__))

#define MfxAutoFunc_0(OBJ, AUTO_FUNC, GOTO_NEXT) __MfxAutoFunc_0(OBJ, AUTO_FUNC, GOTO_NEXT) 
#define MfxAutoFunc_1(OBJ, AUTO_FUNC, GOTO_NEXT) __MfxAutoFunc_1(OBJ, AUTO_FUNC, GOTO_NEXT) 
#define MfxAutoFunc_2(OBJ, AUTO_FUNC, GOTO_NEXT) __MfxAutoFunc_2(OBJ, AUTO_FUNC, GOTO_NEXT) 
#define MfxAutoFunc_3(OBJ, AUTO_FUNC, GOTO_NEXT) __MfxAutoFunc_3(OBJ, AUTO_FUNC, GOTO_NEXT) 
#define MfxAutoFunc_4(OBJ, AUTO_FUNC, GOTO_NEXT) __MfxAutoFunc_4(OBJ, AUTO_FUNC, GOTO_NEXT) 
#define MfxAutoFunc_5(OBJ, AUTO_FUNC, GOTO_NEXT) __MfxAutoFunc_5(OBJ, AUTO_FUNC, GOTO_NEXT) 
#define MfxAutoFunc_6(OBJ, AUTO_FUNC, GOTO_NEXT) __MfxAutoFunc_6(OBJ, AUTO_FUNC, GOTO_NEXT) 
#define MfxAutoFunc_7(OBJ, AUTO_FUNC, GOTO_NEXT) __MfxAutoFunc_7(OBJ, AUTO_FUNC, GOTO_NEXT) 
#define MfxAutoFunc_8(OBJ, AUTO_FUNC, GOTO_NEXT) __MfxAutoFunc_8(OBJ, AUTO_FUNC, GOTO_NEXT) 

	/***************************************************************
	*
	*	MfxBase	常用容器
	*
	****************************************************************/
	typedef std::set<MfxBase*> MfxBase_Set;
	typedef std::queue<MfxBase*> MfxBase_Queue;
	typedef std::deque<MfxBase*> MfxBase_Deque;
	typedef std::stack<MfxBase*> MfxBase_Stack;
	typedef std::vector<MfxBase*> MfxBase_Vector;

	/***************************************************************
	*
	*	MicroFlakeX 主工厂
	* 
	*	所有的	MfxBase	子类都可以通过这个工厂通过‘子类名称’生产。
	*	即：通过字符串创建对象
	* 
	*	注：
	*		1、该子类必须引用了	MfxObject	宏
	*		2、该子类必须实现了	MfxObject_Init_0 - MfxObject_Init_1 - MfxObject_Init_2	这三个辅助宏
	*
	****************************************************************/
	MFX_PORT MfxReturn MfxFactory(MfxString object, MfxBase** ret);

}

namespace MicroFlakeX
{
	/***************************************************************
	*
	*	MicroFlakeX	辅助框架
	* 
	*	MfxCodeLock宏：
	*		1、MfxBase	支持线程安全，具体方案就是保证对象不会在同一时间被两个不同的线程
	*		同时访问其有冲突的方法。
	*		2、请在会造成线程冲突的对象方法开始的时候，添加	MfxCodeLock(this);	语句，以
	*		保证访问唯一性。
	* 
	* 
	****************************************************************/
	class MFX_PORT MfxLock;
	class MFX_PORT MfxThreadServer;

	template<class DataType>
	class MfxDataFlag;
	/***************************************************************
	*
	*	MfxCodeLock宏：
	*		1、MfxBase	支持线程安全，具体方案就是保证对象不会在同一时间被两个不同的线程
	*		同时访问其有冲突的方法。
	*		2、请在会造成线程冲突的对象方法开始的时候，添加	MfxCodeLock(this);	语句，以
	*		保证访问唯一性。
	*
	*
	****************************************************************/
#define MfxCodeLock(OBJ) __MfxCodeLock(OBJ)
}

namespace MicroFlakeX
{
	/***************************************************************
	*	MfxBase	基类
	*	
	*	若要继承MfxBase，则需要重写以下几个函数：
	*		①：virtual MfxReturn Clone(MfxBase** ret);
	*			深拷贝当前对象，并生成新的对象返回。
	* 
	*		②：virtual MfxBase& operator=(MfxBase& rhs);
	*			浅拷贝一份当前对象，C++内部默认的拷贝函数。
	* 
	*		③：virtual BOOL operator==(MfxBase& rhs);
	*			比较两个MfxBase是否相等。
	* 
	*	其余的	MfxBase	函数不需要用户管理，请声明	MfxObject宏	用以自动生成剩余函数。
	* 
	****************************************************************/
	class MfxBase
	{
		friend class MfxLock;
	public:
		MfxBase();
		virtual ~MfxBase();
		virtual MfxReturn Clone(MfxBase** ret);

	public:
		virtual MfxBase& operator=(MfxBase& rhs);

	public:
		virtual bool operator==(MfxBase& rhs);

	public:
		virtual MfxReturn AutoFunc(MfxString recvFunc...);
		virtual MfxReturn FuncName(MfxString* ret);
		virtual MfxReturn ObjectName(MfxString* ret);
	private:
		CRITICAL_SECTION myCriticalSection;
	};


	/***************************************************************
	*	MfxLock	
	* 
	*	这个类负责MfxBase及其派生类的线程安全，当你需要对象的某些方法不被多个线程
	*	同时调用的时候，请在该方法的开头或者需要的地方加上 ： MfxCodeLock(shit);
	*
	*
	****************************************************************/
	class MfxLock
	{
	public:
		MfxLock(MfxBase* object);
		~MfxLock();
	private:
		CRITICAL_SECTION* myCriticalSection;
	};


	/***************************************************************
	*	MfxThreadServer
	*	
	*	MfxThreadServer 是 MicroFlakeX 的线程服务器，线程服务器依赖于 MfxBase 的
	*	AutoFunc。
	* 
	*	需要添加到线程服务器内的回调函数，必须注册了 AutoFunc ，否则会调用失败。
	*	
	*	
	****************************************************************/
	class MfxThreadServer
	{
	public:
		MfxThreadServer();
		~MfxThreadServer();

	public:
		/***************************************************************
		* 
		* 异步线程请勿传入局部变量指针。
		* 参数一：回调对象指针
		* 参数二：回调对象方法名字
		* 参数三、四：传递给回调方法的wparam、lparam。
		* 
		****************************************************************/
		static MfxReturn BeginNewThread(MfxBase* object, MfxString recvFunc, WPARAM wParam = NULL, LPARAM lParam = NULL);

	public:
		/***************************************************************
		* 
		* 参数一：返回一个计时器ID
		* 参数二：回调对象指针
		* 参数三：回调对象方法名字
		* 参数四：传递给回调方法的lparam，回调方法的wparam是当前调用它的计时器id
		* 参数五：计时器每个多长时间调用一次，单位为ms
		* 参数六：计时器多久之后开始，单位为100纳秒，-1秒为立即开始。-1（秒） = -10000000（100纳秒）
		* 参数七：计时器每次开始的时候是否有微小的随机性，单位为ms。随机性指，在定时器每次调用的时候，随机提前或者延后几毫秒。
		* 
		****************************************************************/
		static MfxReturn BeginNewTimer(PTP_TIMER& pTimer, MfxBase* object, MfxString recvFunc, LPARAM lParam = NULL, DWORD delay = 0, LONGLONG begin = -10000000, DWORD randTime = 0);
		static MfxReturn CloseTimer(PTP_TIMER& pTimer);
	private:
		static VOID CALLBACK MfxWorkCallBack(PTP_CALLBACK_INSTANCE instance, PVOID val);
		static VOID CALLBACK MfxTimeCallBack(PTP_CALLBACK_INSTANCE instance, PVOID val, PTP_TIMER pTimer);
	};

#define MfxCloseTimer MicroFlakeX::MfxThreadServer::CloseTimer
#define MfxBeginNewTimer MicroFlakeX::MfxThreadServer::BeginNewTimer

#define MfxBeginNewThread MicroFlakeX::MfxThreadServer::BeginNewThread

}

namespace __MicroFlakeX
{
	/***************************************************************
	*	__MicroFlakeX内部函数
	*		>>	一般情况下这里的函数不需要额外的关注
	*
	*	MicroFlakeX辅助函数
	*
	*		MicroFlakeX的子类通过 MfxFactoryHand 来注册工厂创建。
	*		MfxRemoveObject - 移除注册
	*		MfxRegisterObject - 注册工厂
	*
	****************************************************************/
	using namespace MicroFlakeX;

	class MFX_PORT MfxFactoryHand
	{
	public:
		MfxFactoryHand(MfxString object);
		virtual MfxReturn Creat(MicroFlakeX::MfxBase** ret) = 0;
		virtual ~MfxFactoryHand();
	private:
		MfxString myObjectName;
	};

	MFX_PORT MfxReturn MfxRemoveObject(MfxString object);
	MFX_PORT MfxReturn MfxRegisterObject(MfxString object, MfxFactoryHand* hand);
}

namespace MicroFlakeX
{
	/***************************************************************
	*	MicroFlakeX辅助模板
	* 
	*	①：获取函数的参数长度Argc - 模板实现
	*		int Argc = Mfx_GetFuncArgc(T) 
	*
	*	②：获取函数第N个参数的类型并重命名为FuncT - 模板实现
	*		typedef decltype(Mfx_GetFuncArgv_N( pFunc ))) FuncT;
	*
	****************************************************************/
	template<typename T>
	struct MfxArgNum_;

	template<typename R, class O, typename... Args>
	struct MfxArgNum_<R(O::*)(Args...) const>
	{
		static const int Argc = sizeof...(Args);
	};

	template<typename R, class O, typename... Args>
	struct MfxArgNum_<R(O::*)(Args...)>
	{
		static const int Argc = sizeof...(Args);
	};

	template<typename R, typename... Args>
	struct MfxArgNum_<R(*)(Args...)>
	{
		static const int Argc = sizeof...(Args);
	};

	template<typename T>
	int Mfx_GetFuncArgc(T) 
	{ 
		return MfxArgNum_<T>::Argc;
	};

	template <class R, class O, class A1, class... Args>
	A1 Mfx_GetFuncArgv_1(R(O::*)(A1, Args...) const)
	{
		return A1();
	};

	template <class R, class O, class A1, class... Args>
	A1 Mfx_GetFuncArgv_1(R(O::*)(A1, Args...))
	{
		return A1();
	};

	template <class R, class A1, class... Args>
	A1 Mfx_GetFuncArgv_1(R(*)(A1, Args...))
	{
		return A1();
	};

	template <class R, class O, class A1, class A2, class... Args>
	A2 Mfx_GetFuncArgv_2(R(O::*)(A1, A2, Args...) const)
	{
		return A2();
	};

	template <class R, class O, class A1, class A2, class... Args>
	A2 Mfx_GetFuncArgv_2(R(O::*)(A1, A2, Args...))
	{
		return A2();
	};

	template <class R, class A1, class A2, class... Args>
	A2 Mfx_GetFuncArgv_2(R(*)(A1, A2, Args...))
	{
		return A2();
	};

	template <class R, class O, class A1, class A2, class A3, class... Args>
	A3 Mfx_GetFuncArgv_3(R(O::*)(A1, A2, A3, Args...) const)
	{
		return A3();
	};

	template <class R, class O, class A1, class A2, class A3, class... Args>
	A3 Mfx_GetFuncArgv_3(R(O::*)(A1, A2, A3, Args...))
	{
		return A3();
	};

	template <class R, class A1, class A2, class A3, class... Args>
	A3 Mfx_GetFuncArgv_3(R(*)(A1, A2, A3, Args...))
	{
		return A3();
	};

	template <class R, class O, class A1, class A2, class A3, class A4, class... Args>
	A4 Mfx_GetFuncArgv_4(R(O::*)(A1, A2, A3, A4, Args...) const)
	{
		return A4();
	};

	template <class R, class O, class A1, class A2, class A3, class A4, class... Args>
	A4 Mfx_GetFuncArgv_4(R(O::*)(A1, A2, A3, A4, Args...))
	{
		return A4();
	};

	template <class R, class A1, class A2, class A3, class A4, class... Args>
	A4 Mfx_GetFuncArgv_4(R(*)(A1, A2, A3, A4, Args...))
	{
		return A4();
	};

	template <class R, class O, class A1, class A2, class A3, class A4, class A5, class... Args>
	A5 Mfx_GetFuncArgv_5(R(O::*)(A1, A2, A3, A4, A5, Args...) const)
	{
		return A5();
	};

	template <class R, class O, class A1, class A2, class A3, class A4, class A5, class... Args>
	A5 Mfx_GetFuncArgv_5(R(O::*)(A1, A2, A3, A4, A5, Args...))
	{
		return A5();
	};

	template <class R, class A1, class A2, class A3, class A4, class A5, class... Args>
	A5 Mfx_GetFuncArgv_5(R(*)(A1, A2, A3, A4, A5, Args...))
	{
		return A5();
	};

	template <class R, class O, class A1, class A2, class A3, class A4, class A5, class A6, class... Args>
	A6 Mfx_GetFuncArgv_6(R(O::*)(A1, A2, A3, A4, A5, A6, Args...) const)
	{
		return A6();
	};

	template <class R, class O, class A1, class A2, class A3, class A4, class A5, class A6, class... Args>
	A6 Mfx_GetFuncArgv_6(R(O::*)(A1, A2, A3, A4, A5, A6, Args...))
	{
		return A6();
	};

	template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class... Args>
	A6 Mfx_GetFuncArgv_6(R(*)(A1, A2, A3, A4, A5, A6, Args...))
	{
		return A6();
	};

	template <class R, class O, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class... Args>
	A7 Mfx_GetFuncArgv_7(R(O::*)(A1, A2, A3, A4, A5, A6, A7, Args...) const)
	{
		return A7();
	};

	template <class R, class O, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class... Args>
	A7 Mfx_GetFuncArgv_7(R(O::*)(A1, A2, A3, A4, A5, A6, A7, Args...))
	{
		return A7();
	};

	template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class... Args>
	A7 Mfx_GetFuncArgv_7(R(*)(A1, A2, A3, A4, A5, A6, A7, Args...))
	{
		return A7();
	};

	template <class R, class O, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class... Args>
	A8 Mfx_GetFuncArgv_8(R(O::*)(A1, A2, A3, A4, A5, A6, A7, A8, Args...) const)
	{
		return A8();
	};

	template <class R, class O, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class... Args>
	A8 Mfx_GetFuncArgv_8(R(O::*)(A1, A2, A3, A4, A5, A6, A7, A8, Args...))
	{
		return A8();
	};

	template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class... Args>
	A8 Mfx_GetFuncArgv_8(R(*)(A1, A2, A3, A4, A5, A6, A7, A8, Args...))
	{
		return A8();
	};

	/***************************************************************
	*	MicroFlakeX辅助模板 - MfxDataFlag
	*
	*	MfxDataFlag	可以记录变量被更改的次数以及被使用的次数
	* 
	*	MfxDataFlag	重载了众多的运算符，使其在计算使用的时候，跟原版变量几乎相等
	*	MfxDataFlag	出于安全考虑，禁止了隐式类型转换，但你仍可以使用显示的类型转换
	*
	****************************************************************/
	template<class DataType>
	class MfxDataFlag
	{
	private:
		DataType myData;
		DataType myBeforData;
		UINT myUseFlag;
		UINT myChangeFlag;
	public:
		MfxDataFlag()
		{
			myBeforData = myData = DataType();
			myChangeFlag = myUseFlag = 0;
		}

		DataType& GetData()
		{
			return myData;
		};

		DataType& GetBeforData()
		{
			return myBeforData;
		};

		void CleanUseFlag()
		{
			myUseFlag = 0;
		};

		void CleanChangeFlag()
		{
			myChangeFlag = 0;
		};

		UINT CheckUseFlag()
		{
			return myUseFlag;
		};

		UINT CheckChangeFlag()
		{
			return myChangeFlag;
		};

	public:
		DataType& operator-> ()
		{
			myUseFlag++; 
			return myData;
		};

		DataType operator= (DataType& rhs)
		{
			if (myData == rhs)
			{
				return myData;
			}
			myChangeFlag++;
			myBeforData = myData;
			myData = rhs;
			return myData;
		};

		DataType operator= (DataType&& rhs)
		{
			if (myData == rhs)
			{
				return myData;
			}
			myChangeFlag++;
			myBeforData = myData;
			myData = rhs;
			return myData;
		};

		operator bool() { return (bool)(myData); };

		operator char() { return (char)(myData); };
		operator unsigned char() { return (unsigned char)(myData); };

		operator short() { return (short)(myData); };
		operator unsigned short() { return (unsigned short)(myData); };

		operator int() { return (int)(myData); };
		operator unsigned int() { return (unsigned int)(myData); };

		operator long() { return (int)(myData); };
		operator unsigned long() { return (unsigned long)(myData); };

		operator long long() { return (int)(myData); };
		operator unsigned long long() { return (unsigned long long)(myData); };

		bool operator< (DataType& rhs) { return myData < rhs; };
		bool operator< (DataType&& rhs) { return myData < rhs; };
		bool operator< (MfxDataFlag<DataType>& rhs) { return myData < rhs.GetData(); };
		bool operator< (MfxDataFlag<DataType>&& rhs) { return myData < rhs.GetData(); };

		bool operator> (DataType& rhs) { return myData > rhs; };
		bool operator> (DataType&& rhs) { return myData > rhs; };
		bool operator> (MfxDataFlag<DataType>& rhs) { return myData > rhs.GetData(); };
		bool operator> (MfxDataFlag<DataType>&& rhs) { return myData > rhs.GetData(); };

		bool operator== (DataType& rhs) { return myData == rhs; };
		bool operator== (DataType&& rhs) { return myData == rhs; };
		bool operator== (MfxDataFlag<DataType>& rhs) { return myData == rhs.GetData(); };
		bool operator== (MfxDataFlag<DataType>&& rhs) { return myData == rhs.GetData(); };

		bool operator!= (DataType& rhs) { return myData != rhs; };
		bool operator!= (DataType&& rhs) { return myData != rhs; };
		bool operator!= (MfxDataFlag<DataType>& rhs) { return myData != rhs.GetData(); };
		bool operator!= (MfxDataFlag<DataType>&& rhs) { return myData != rhs.GetData(); };

		bool operator&& (DataType& rhs) { return myData && rhs; };
		bool operator&& (DataType&& rhs) { return myData && rhs; };
		bool operator&& (MfxDataFlag<DataType>& rhs) { return myData && rhs.GetData(); };
		bool operator&& (MfxDataFlag<DataType>&& rhs) { return myData && rhs.GetData(); };

		bool operator|| (DataType& rhs) { return myData || rhs; };
		bool operator|| (DataType&& rhs) { return myData || rhs; };
		bool operator|| (MfxDataFlag<DataType>& rhs) { return myData || rhs.GetData(); };
		bool operator|| (MfxDataFlag<DataType>&& rhs) { return myData || rhs.GetData(); };
	};

}


/***************************************************************
*	MicroFlakeX辅助宏
*	
*	这里是	MicroFlakeX辅助宏	的集中定义，不多赘述。
* 
****************************************************************/

#define __MfxCodeLock(OBJ) \
	MfxLock tLock(OBJ);

#define __MfxObject \
public:\
	MfxReturn AutoFunc(MfxString recvFunc...);\
	MfxReturn FuncName(MfxString* ret);\
	MfxReturn ObjectName(MfxString* ret);

#define MfxSafeDelete(OBJ)\
	if(OBJ)\
	{\
		delete OBJ;\
		OBJ = nullptr;\
	}

/***************************************************************
*
*
*
****************************************************************/
#define __MfxObject_Init_0(OBJ)\
using namespace MicroFlakeX;\
using namespace __MicroFlakeX;\
std::map<MfxString, int> Mfx##OBJ##FuncMap;\
typedef std::map<MfxString,int>::value_type Mfx##OBJ##FuncMapValue;\
MfxReturn OBJ::FuncName(MfxString* ret)\
{\
	*ret = MfxText("");\
	for(auto& i : Mfx##OBJ##FuncMap)\
	{\
		(*ret) += (i.first);\
		*ret += MfxText("...\n");\
	}\
	return Mfx_Return_Fine;\
}\
MfxReturn OBJ::ObjectName(MfxString* ret)\
{\
	*ret = MfxText(#OBJ);\
	return Mfx_Return_Fine;\
}\
\
class OBJ##FactoryHand\
	: public MfxFactoryHand\
{\
public:\
	OBJ##FactoryHand(MfxString object)\
		: MfxFactoryHand(object)\
	{


/***************************************************************
*
*
*
****************************************************************/
#define __MfxObject_Init_1(OBJ, GOTO_BEGIN) \
	}\
	MfxReturn Creat(MfxBase** ret)\
	{\
		*ret = new OBJ;\
		return Mfx_Return_Fine;\
	}\
};\
OBJ##FactoryHand OBJ##Hand(MfxText(#OBJ));\
bool OBJ##isFirst = true;\
MfxReturn OBJ::AutoFunc(MfxString recvFunc...)\
{\
	MfxReturn ret = Mfx_Return_Fail;\
	int countID = 0;\
	int iterID = 0;\
	va_list argc;\
	va_start(argc, recvFunc);\
	auto iter = Mfx##OBJ##FuncMap.end();\
	if(OBJ##isFirst)\
	{\
		OBJ##isFirst = false;\
		goto REG_##GOTO_BEGIN;\
	}\
	\
	BeginSwitch:\
	iter = Mfx##OBJ##FuncMap.find(recvFunc);\
	if (iter != Mfx##OBJ##FuncMap.end())\
	{\
		iterID = iter->second;\
		countID = 0;


/***************************************************************
*
*
*
****************************************************************/
#define __MfxObject_Init_2(OBJ, FATHER_OBJ) \
		if(iterID == countID++)\
		{\
			recvFunc = va_arg(argc, MfxString);\
			argc = va_arg(argc, va_list);\
			goto BeginSwitch;\
			REG_END:\
				Mfx##OBJ##FuncMap.insert(Mfx##OBJ##FuncMapValue(MfxText("AUTOFUNC_NOTFOUND"), countID++));\
			goto BeginSwitch;\
		}\
	}\
	else\
	{\
		ret = FATHER_OBJ::AutoFunc(MfxText("AUTOFUNC_NOTFOUND"), recvFunc, argc); \
		va_end(argc);\
		return ret;\
	}\
}


/***************************************************************
*
*
*
****************************************************************/

#define __MfxAutoFunc_0(OBJ, AUTO_FUNC, GOTO_NEXT) \
if(iterID == countID++)\
{\
	{\
		ret = AUTO_FUNC(); \
		va_end(argc);\
		return ret;\
	}\
	REG_##AUTO_FUNC:\
		Mfx##OBJ##FuncMap.insert(Mfx##OBJ##FuncMapValue(MfxText(#AUTO_FUNC), countID++));\
	goto REG_##GOTO_NEXT;\
}\

#define __MfxAutoFunc_1(OBJ, AUTO_FUNC, GOTO_NEXT) \
if(iterID == countID++)\
{\
	{\
		auto A1 = va_arg(argc, decltype(Mfx_GetFuncArgv_1(&OBJ::AUTO_FUNC))); \
		ret = AUTO_FUNC(A1); \
		va_end(argc);\
		return ret;\
	}\
	\
	REG_##AUTO_FUNC:\
		Mfx##OBJ##FuncMap.insert(Mfx##OBJ##FuncMapValue(MfxText(#AUTO_FUNC), countID++));\
	goto REG_##GOTO_NEXT;\
}\

#define __MfxAutoFunc_2(OBJ, AUTO_FUNC, GOTO_NEXT) \
if(iterID == countID++)\
{\
	{\
		auto A1 = va_arg(argc, decltype(Mfx_GetFuncArgv_1(&OBJ::AUTO_FUNC)));\
		auto A2 = va_arg(argc, decltype(Mfx_GetFuncArgv_2(&OBJ::AUTO_FUNC)));\
		ret = AUTO_FUNC(A1, A2);\
		va_end(argc);\
		return ret;\
	}\
	\
	REG_##AUTO_FUNC:\
		Mfx##OBJ##FuncMap.insert(Mfx##OBJ##FuncMapValue(MfxText(#AUTO_FUNC), countID++));\
	goto REG_##GOTO_NEXT;\
}\

#define __MfxAutoFunc_3(OBJ, AUTO_FUNC, GOTO_NEXT) \
if(iterID == countID++)\
{\
	{\
		auto A1 = va_arg(argc, decltype(Mfx_GetFuncArgv_1(&OBJ::AUTO_FUNC)));\
		auto A2 = va_arg(argc, decltype(Mfx_GetFuncArgv_2(&OBJ::AUTO_FUNC)));\
		auto A3 = va_arg(argc, decltype(Mfx_GetFuncArgv_3(&OBJ::AUTO_FUNC)));\
		ret = AUTO_FUNC(A1, A2, A3);\
		va_end(argc);\
		return ret;\
	}\
	\
	REG_##AUTO_FUNC:\
		Mfx##OBJ##FuncMap.insert(Mfx##OBJ##FuncMapValue(MfxText(#AUTO_FUNC), countID++));\
	goto REG_##GOTO_NEXT;\
}\

#define __MfxAutoFunc_4(OBJ, AUTO_FUNC, GOTO_NEXT) \
if(iterID == countID++)\
{\
	{\
		auto A1 = va_arg(argc, decltype(Mfx_GetFuncArgv_1(&OBJ::AUTO_FUNC)));\
		auto A2 = va_arg(argc, decltype(Mfx_GetFuncArgv_2(&OBJ::AUTO_FUNC)));\
		auto A3 = va_arg(argc, decltype(Mfx_GetFuncArgv_3(&OBJ::AUTO_FUNC)));\
		auto A4 = va_arg(argc, decltype(Mfx_GetFuncArgv_4(&OBJ::AUTO_FUNC)));\
		ret = AUTO_FUNC(A1, A2, A3, A4);\
		va_end(argc);\
		return ret;\
	}\
	\
	REG_##AUTO_FUNC:\
		Mfx##OBJ##FuncMap.insert(Mfx##OBJ##FuncMapValue(MfxText(#AUTO_FUNC), countID++));\
	goto REG_##GOTO_NEXT;\
}\

#define __MfxAutoFunc_5(OBJ, AUTO_FUNC, GOTO_NEXT) \
if(iterID == countID++)\
{\
	{\
		auto A1 = va_arg(argc, decltype(Mfx_GetFuncArgv_1(&OBJ::AUTO_FUNC)));\
		auto A2 = va_arg(argc, decltype(Mfx_GetFuncArgv_2(&OBJ::AUTO_FUNC)));\
		auto A3 = va_arg(argc, decltype(Mfx_GetFuncArgv_3(&OBJ::AUTO_FUNC)));\
		auto A4 = va_arg(argc, decltype(Mfx_GetFuncArgv_4(&OBJ::AUTO_FUNC)));\
		auto A5 = va_arg(argc, decltype(Mfx_GetFuncArgv_5(&OBJ::AUTO_FUNC)));\
		ret = AUTO_FUNC(A1, A2, A3, A4, A5);\
		va_end(argc);\
		return ret;\
	}\
	\
	REG_##AUTO_FUNC:\
		Mfx##OBJ##FuncMap.insert(Mfx##OBJ##FuncMapValue(MfxText(#AUTO_FUNC), countID++));\
	goto REG_##GOTO_NEXT;\
}\

#define __MfxAutoFunc_6(OBJ, AUTO_FUNC, GOTO_NEXT) \
if(iterID == countID++)\
{\
	{\
		auto A1 = va_arg(argc, decltype(Mfx_GetFuncArgv_1(&OBJ::AUTO_FUNC)));\
		auto A2 = va_arg(argc, decltype(Mfx_GetFuncArgv_2(&OBJ::AUTO_FUNC)));\
		auto A3 = va_arg(argc, decltype(Mfx_GetFuncArgv_3(&OBJ::AUTO_FUNC)));\
		auto A4 = va_arg(argc, decltype(Mfx_GetFuncArgv_4(&OBJ::AUTO_FUNC)));\
		auto A5 = va_arg(argc, decltype(Mfx_GetFuncArgv_5(&OBJ::AUTO_FUNC)));\
		auto A6 = va_arg(argc, decltype(Mfx_GetFuncArgv_6(&OBJ::AUTO_FUNC)));\
		ret = AUTO_FUNC(A1, A2, A3, A4, A5, A6);\
		va_end(argc);\
		return ret;\
	}\
	\
	REG_##AUTO_FUNC:\
		Mfx##OBJ##FuncMap.insert(Mfx##OBJ##FuncMapValue(MfxText(#AUTO_FUNC), countID++));\
	goto REG_##GOTO_NEXT;\
}\


#define __MfxAutoFunc_7(OBJ, AUTO_FUNC, GOTO_NEXT) \
if(iterID == countID++)\
{\
	{\
		auto A1 = va_arg(argc, decltype(Mfx_GetFuncArgv_1(&OBJ::AUTO_FUNC)));\
		auto A2 = va_arg(argc, decltype(Mfx_GetFuncArgv_2(&OBJ::AUTO_FUNC)));\
		auto A3 = va_arg(argc, decltype(Mfx_GetFuncArgv_3(&OBJ::AUTO_FUNC)));\
		auto A4 = va_arg(argc, decltype(Mfx_GetFuncArgv_4(&OBJ::AUTO_FUNC)));\
		auto A5 = va_arg(argc, decltype(Mfx_GetFuncArgv_5(&OBJ::AUTO_FUNC)));\
		auto A6 = va_arg(argc, decltype(Mfx_GetFuncArgv_6(&OBJ::AUTO_FUNC)));\
		auto A7 = va_arg(argc, decltype(Mfx_GetFuncArgv_7(&OBJ::AUTO_FUNC)));\
		ret = AUTO_FUNC(A1, A2, A3, A4, A5, A6, A7);\
		va_end(argc);\
		return ret;\
	}\
	\
	REG_##AUTO_FUNC:\
		Mfx##OBJ##FuncMap.insert(Mfx##OBJ##FuncMapValue(MfxText(#AUTO_FUNC), countID++));\
	goto REG_##GOTO_NEXT;\
}\

#define __MfxAutoFunc_8(OBJ, AUTO_FUNC, GOTO_NEXT) \
if(iterID == countID++)\
{\
	{\
		auto A1 = va_arg(argc, decltype(Mfx_GetFuncArgv_1(&OBJ::AUTO_FUNC)));\
		auto A2 = va_arg(argc, decltype(Mfx_GetFuncArgv_2(&OBJ::AUTO_FUNC)));\
		auto A3 = va_arg(argc, decltype(Mfx_GetFuncArgv_3(&OBJ::AUTO_FUNC)));\
		auto A4 = va_arg(argc, decltype(Mfx_GetFuncArgv_4(&OBJ::AUTO_FUNC)));\
		auto A5 = va_arg(argc, decltype(Mfx_GetFuncArgv_5(&OBJ::AUTO_FUNC)));\
		auto A6 = va_arg(argc, decltype(Mfx_GetFuncArgv_6(&OBJ::AUTO_FUNC)));\
		auto A7 = va_arg(argc, decltype(Mfx_GetFuncArgv_7(&OBJ::AUTO_FUNC)));\
		auto A8 = va_arg(argc, decltype(Mfx_GetFuncArgv_8(&OBJ::AUTO_FUNC)));\
		ret = AUTO_FUNC(A1, A2, A3, A4, A5, A6, A7, A8);\
		va_end(argc);\
		return ret;\
	}\
	\
	REG_##AUTO_FUNC:\
		Mfx##OBJ##FuncMap.insert(Mfx##OBJ##FuncMapValue(MfxText(#AUTO_FUNC), countID++));\
	goto REG_##GOTO_NEXT;\
}


/***************************************************************
*	①：MfxAutoFunc_AutoEnum_ArgcMap宏 - 从参数总数映射函数数量
*	
*	②：MfxAutoFunc_Connect宏 - 跳转生成对应的	MfxAutoFunc_NUM
* 
*	③：MfxAutoFunc_AutoEnum宏 - 根据给定的参数，自动推断需要生成的
*		MfxAutoFunc_NUM。推断上限为62个函数。
*	
*	④：CONNECT组宏 - 延迟展开宏，非常重要的辅助宏，用来延迟宏的展开层次
*
*	⑤：MFX_COUNT宏 - 利用__COUNTER__自动展开计数。
* 
*	⑥：Mfx_Inc宏 - 自增宏，最高支持自增到512
* 
****************************************************************/
#define MfxAutoFunc_AutoEnum_ArgcMap(NUM) CCONNECT(MfxAutoFunc_AutoEnum_ArgcMap_, NUM)

#define MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2) CCONNECT(CONNECT(MfxAutoFunc_, NUM_1), (OBJ, FUNC_1, FUNC_2))

#define MfxAutoFunc_END(...)

#define MfxAutoFunc_(...)

#define __MfxAutoFunc_AutoEnum(...) \
    CONNECT(CCONNECT(MfxAutoFunc_Enum_, MfxAutoFunc_AutoEnum_ArgcMap(GET_ARGS_NUM(__VA_ARGS__))), (__VA_ARGS__))

#define CONNECT(A, B) A##B
#define CCONNECT(A, B) CONNECT(A, B)
#define CCCONNECT(A, B) CCONNECT(A, B)
#define CCCCONNECT(A, B) CCCONNECT(A, B)
#define CCCCCONNECT(A, B) CCCCONNECT(A, B)

#define ARGS_NUM_(\
N1, N2, N3, N4, N5, N6, N7, N8, N9, N10, N11, N12, N13, N14, N15, N16, \
N17, N18, N19, N20, N21, N22, N23, N24, N25, N26, N27, N28, N29, N30, N31, N32, \
N33, N34, N35, N36, N37, N38, N39, N40, N41, N42, N43, N44, N45, N46, N47, N48, \
N49, N50, N51, N52, N53, N54, N55, N56, N57, N58, N59, N60, N61, N62, N63, N64, \
N65, N66, N67, N68, N69, N70, N71, N72, N73, N74, N75, N76, N77, N78, N79, N80, \
N81, N82, N83, N84, N85, N86, N87, N88, N89, N90, N91, N92, N93, N94, N95, N96, \
N97, N98, N99, N100, N101, N102, N103, N104, N105, N106, N107, N108, N109, N110, N111, N112, \
N113, N114, N115, N116, N117, N118, N119, N120, N121, N122, N123, N124, N125, N126, ...) N126

#define GET_ARGS_NUM(...) CONNECT(ARGS_NUM_, (__VA_ARGS__, \
125, 124, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114, 113, 112, 111, \
110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100, 99, 98, 97, 96, 95, \
94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, \
78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, \
62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, \
46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, \
30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, \
14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1))


#define MFX_COUNT(BEGIN) (__COUNTER__ - BEGIN)

#define Mfx_Inc(Num) CONNECT(Mfx_Inc_, Num)
#define Mfx_Inc_0 1
#define Mfx_Inc_1 2
#define Mfx_Inc_2 3
#define Mfx_Inc_3 4
#define Mfx_Inc_4 5
#define Mfx_Inc_5 6
#define Mfx_Inc_6 7
#define Mfx_Inc_7 8
#define Mfx_Inc_8 9
#define Mfx_Inc_9 10
#define Mfx_Inc_10 11
#define Mfx_Inc_11 12
#define Mfx_Inc_12 13
#define Mfx_Inc_13 14
#define Mfx_Inc_14 15
#define Mfx_Inc_15 16
#define Mfx_Inc_16 17
#define Mfx_Inc_17 18
#define Mfx_Inc_18 19
#define Mfx_Inc_19 20
#define Mfx_Inc_20 21
#define Mfx_Inc_21 22
#define Mfx_Inc_22 23
#define Mfx_Inc_23 24
#define Mfx_Inc_24 25
#define Mfx_Inc_25 26
#define Mfx_Inc_26 27
#define Mfx_Inc_27 28
#define Mfx_Inc_28 29
#define Mfx_Inc_29 30
#define Mfx_Inc_30 31
#define Mfx_Inc_31 32
#define Mfx_Inc_32 33
#define Mfx_Inc_33 34
#define Mfx_Inc_34 35
#define Mfx_Inc_35 36
#define Mfx_Inc_36 37
#define Mfx_Inc_37 38
#define Mfx_Inc_38 39
#define Mfx_Inc_39 40
#define Mfx_Inc_40 41
#define Mfx_Inc_41 42
#define Mfx_Inc_42 43
#define Mfx_Inc_43 44
#define Mfx_Inc_44 45
#define Mfx_Inc_45 46
#define Mfx_Inc_46 47
#define Mfx_Inc_47 48
#define Mfx_Inc_48 49
#define Mfx_Inc_49 50
#define Mfx_Inc_50 51
#define Mfx_Inc_51 52
#define Mfx_Inc_52 53
#define Mfx_Inc_53 54
#define Mfx_Inc_54 55
#define Mfx_Inc_55 56
#define Mfx_Inc_56 57
#define Mfx_Inc_57 58
#define Mfx_Inc_58 59
#define Mfx_Inc_59 60
#define Mfx_Inc_60 61
#define Mfx_Inc_61 62
#define Mfx_Inc_62 63
#define Mfx_Inc_63 64
#define Mfx_Inc_64 65
#define Mfx_Inc_65 66
#define Mfx_Inc_66 67
#define Mfx_Inc_67 68
#define Mfx_Inc_68 69
#define Mfx_Inc_69 70
#define Mfx_Inc_70 71
#define Mfx_Inc_71 72
#define Mfx_Inc_72 73
#define Mfx_Inc_73 74
#define Mfx_Inc_74 75
#define Mfx_Inc_75 76
#define Mfx_Inc_76 77
#define Mfx_Inc_77 78
#define Mfx_Inc_78 79
#define Mfx_Inc_79 80
#define Mfx_Inc_80 81
#define Mfx_Inc_81 82
#define Mfx_Inc_82 83
#define Mfx_Inc_83 84
#define Mfx_Inc_84 85
#define Mfx_Inc_85 86
#define Mfx_Inc_86 87
#define Mfx_Inc_87 88
#define Mfx_Inc_88 89
#define Mfx_Inc_89 90
#define Mfx_Inc_90 91
#define Mfx_Inc_91 92
#define Mfx_Inc_92 93
#define Mfx_Inc_93 94
#define Mfx_Inc_94 95
#define Mfx_Inc_95 96
#define Mfx_Inc_96 97
#define Mfx_Inc_97 98
#define Mfx_Inc_98 99
#define Mfx_Inc_99 100
#define Mfx_Inc_100 101
#define Mfx_Inc_101 102
#define Mfx_Inc_102 103
#define Mfx_Inc_103 104
#define Mfx_Inc_104 105
#define Mfx_Inc_105 106
#define Mfx_Inc_106 107
#define Mfx_Inc_107 108
#define Mfx_Inc_108 109
#define Mfx_Inc_109 110
#define Mfx_Inc_110 111
#define Mfx_Inc_111 112
#define Mfx_Inc_112 113
#define Mfx_Inc_113 114
#define Mfx_Inc_114 115
#define Mfx_Inc_115 116
#define Mfx_Inc_116 117
#define Mfx_Inc_117 118
#define Mfx_Inc_118 119
#define Mfx_Inc_119 120
#define Mfx_Inc_120 121
#define Mfx_Inc_121 122
#define Mfx_Inc_122 123
#define Mfx_Inc_123 124
#define Mfx_Inc_124 125
#define Mfx_Inc_125 126
#define Mfx_Inc_126 127
#define Mfx_Inc_127 128
#define Mfx_Inc_128 129
#define Mfx_Inc_129 130
#define Mfx_Inc_130 131
#define Mfx_Inc_131 132
#define Mfx_Inc_132 133
#define Mfx_Inc_133 134
#define Mfx_Inc_134 135
#define Mfx_Inc_135 136
#define Mfx_Inc_136 137
#define Mfx_Inc_137 138
#define Mfx_Inc_138 139
#define Mfx_Inc_139 140
#define Mfx_Inc_140 141
#define Mfx_Inc_141 142
#define Mfx_Inc_142 143
#define Mfx_Inc_143 144
#define Mfx_Inc_144 145
#define Mfx_Inc_145 146
#define Mfx_Inc_146 147
#define Mfx_Inc_147 148
#define Mfx_Inc_148 149
#define Mfx_Inc_149 150
#define Mfx_Inc_150 151
#define Mfx_Inc_151 152
#define Mfx_Inc_152 153
#define Mfx_Inc_153 154
#define Mfx_Inc_154 155
#define Mfx_Inc_155 156
#define Mfx_Inc_156 157
#define Mfx_Inc_157 158
#define Mfx_Inc_158 159
#define Mfx_Inc_159 160
#define Mfx_Inc_160 161
#define Mfx_Inc_161 162
#define Mfx_Inc_162 163
#define Mfx_Inc_163 164
#define Mfx_Inc_164 165
#define Mfx_Inc_165 166
#define Mfx_Inc_166 167
#define Mfx_Inc_167 168
#define Mfx_Inc_168 169
#define Mfx_Inc_169 170
#define Mfx_Inc_170 171
#define Mfx_Inc_171 172
#define Mfx_Inc_172 173
#define Mfx_Inc_173 174
#define Mfx_Inc_174 175
#define Mfx_Inc_175 176
#define Mfx_Inc_176 177
#define Mfx_Inc_177 178
#define Mfx_Inc_178 179
#define Mfx_Inc_179 180
#define Mfx_Inc_180 181
#define Mfx_Inc_181 182
#define Mfx_Inc_182 183
#define Mfx_Inc_183 184
#define Mfx_Inc_184 185
#define Mfx_Inc_185 186
#define Mfx_Inc_186 187
#define Mfx_Inc_187 188
#define Mfx_Inc_188 189
#define Mfx_Inc_189 190
#define Mfx_Inc_190 191
#define Mfx_Inc_191 192
#define Mfx_Inc_192 193
#define Mfx_Inc_193 194
#define Mfx_Inc_194 195
#define Mfx_Inc_195 196
#define Mfx_Inc_196 197
#define Mfx_Inc_197 198
#define Mfx_Inc_198 199
#define Mfx_Inc_199 200
#define Mfx_Inc_200 201
#define Mfx_Inc_201 202
#define Mfx_Inc_202 203
#define Mfx_Inc_203 204
#define Mfx_Inc_204 205
#define Mfx_Inc_205 206
#define Mfx_Inc_206 207
#define Mfx_Inc_207 208
#define Mfx_Inc_208 209
#define Mfx_Inc_209 210
#define Mfx_Inc_210 211
#define Mfx_Inc_211 212
#define Mfx_Inc_212 213
#define Mfx_Inc_213 214
#define Mfx_Inc_214 215
#define Mfx_Inc_215 216
#define Mfx_Inc_216 217
#define Mfx_Inc_217 218
#define Mfx_Inc_218 219
#define Mfx_Inc_219 220
#define Mfx_Inc_220 221
#define Mfx_Inc_221 222
#define Mfx_Inc_222 223
#define Mfx_Inc_223 224
#define Mfx_Inc_224 225
#define Mfx_Inc_225 226
#define Mfx_Inc_226 227
#define Mfx_Inc_227 228
#define Mfx_Inc_228 229
#define Mfx_Inc_229 230
#define Mfx_Inc_230 231
#define Mfx_Inc_231 232
#define Mfx_Inc_232 233
#define Mfx_Inc_233 234
#define Mfx_Inc_234 235
#define Mfx_Inc_235 236
#define Mfx_Inc_236 237
#define Mfx_Inc_237 238
#define Mfx_Inc_238 239
#define Mfx_Inc_239 240
#define Mfx_Inc_240 241
#define Mfx_Inc_241 242
#define Mfx_Inc_242 243
#define Mfx_Inc_243 244
#define Mfx_Inc_244 245
#define Mfx_Inc_245 246
#define Mfx_Inc_246 247
#define Mfx_Inc_247 248
#define Mfx_Inc_248 249
#define Mfx_Inc_249 250
#define Mfx_Inc_250 251
#define Mfx_Inc_251 252
#define Mfx_Inc_252 253
#define Mfx_Inc_253 254
#define Mfx_Inc_254 255
#define Mfx_Inc_255 256
#define Mfx_Inc_256 257
#define Mfx_Inc_257 258
#define Mfx_Inc_258 259
#define Mfx_Inc_259 260
#define Mfx_Inc_260 261
#define Mfx_Inc_261 262
#define Mfx_Inc_262 263
#define Mfx_Inc_263 264
#define Mfx_Inc_264 265
#define Mfx_Inc_265 266
#define Mfx_Inc_266 267
#define Mfx_Inc_267 268
#define Mfx_Inc_268 269
#define Mfx_Inc_269 270
#define Mfx_Inc_270 271
#define Mfx_Inc_271 272
#define Mfx_Inc_272 273
#define Mfx_Inc_273 274
#define Mfx_Inc_274 275
#define Mfx_Inc_275 276
#define Mfx_Inc_276 277
#define Mfx_Inc_277 278
#define Mfx_Inc_278 279
#define Mfx_Inc_279 280
#define Mfx_Inc_280 281
#define Mfx_Inc_281 282
#define Mfx_Inc_282 283
#define Mfx_Inc_283 284
#define Mfx_Inc_284 285
#define Mfx_Inc_285 286
#define Mfx_Inc_286 287
#define Mfx_Inc_287 288
#define Mfx_Inc_288 289
#define Mfx_Inc_289 290
#define Mfx_Inc_290 291
#define Mfx_Inc_291 292
#define Mfx_Inc_292 293
#define Mfx_Inc_293 294
#define Mfx_Inc_294 295
#define Mfx_Inc_295 296
#define Mfx_Inc_296 297
#define Mfx_Inc_297 298
#define Mfx_Inc_298 299
#define Mfx_Inc_299 300
#define Mfx_Inc_300 301
#define Mfx_Inc_301 302
#define Mfx_Inc_302 303
#define Mfx_Inc_303 304
#define Mfx_Inc_304 305
#define Mfx_Inc_305 306
#define Mfx_Inc_306 307
#define Mfx_Inc_307 308
#define Mfx_Inc_308 309
#define Mfx_Inc_309 310
#define Mfx_Inc_310 311
#define Mfx_Inc_311 312
#define Mfx_Inc_312 313
#define Mfx_Inc_313 314
#define Mfx_Inc_314 315
#define Mfx_Inc_315 316
#define Mfx_Inc_316 317
#define Mfx_Inc_317 318
#define Mfx_Inc_318 319
#define Mfx_Inc_319 320
#define Mfx_Inc_320 321
#define Mfx_Inc_321 322
#define Mfx_Inc_322 323
#define Mfx_Inc_323 324
#define Mfx_Inc_324 325
#define Mfx_Inc_325 326
#define Mfx_Inc_326 327
#define Mfx_Inc_327 328
#define Mfx_Inc_328 329
#define Mfx_Inc_329 330
#define Mfx_Inc_330 331
#define Mfx_Inc_331 332
#define Mfx_Inc_332 333
#define Mfx_Inc_333 334
#define Mfx_Inc_334 335
#define Mfx_Inc_335 336
#define Mfx_Inc_336 337
#define Mfx_Inc_337 338
#define Mfx_Inc_338 339
#define Mfx_Inc_339 340
#define Mfx_Inc_340 341
#define Mfx_Inc_341 342
#define Mfx_Inc_342 343
#define Mfx_Inc_343 344
#define Mfx_Inc_344 345
#define Mfx_Inc_345 346
#define Mfx_Inc_346 347
#define Mfx_Inc_347 348
#define Mfx_Inc_348 349
#define Mfx_Inc_349 350
#define Mfx_Inc_350 351
#define Mfx_Inc_351 352
#define Mfx_Inc_352 353
#define Mfx_Inc_353 354
#define Mfx_Inc_354 355
#define Mfx_Inc_355 356
#define Mfx_Inc_356 357
#define Mfx_Inc_357 358
#define Mfx_Inc_358 359
#define Mfx_Inc_359 360
#define Mfx_Inc_360 361
#define Mfx_Inc_361 362
#define Mfx_Inc_362 363
#define Mfx_Inc_363 364
#define Mfx_Inc_364 365
#define Mfx_Inc_365 366
#define Mfx_Inc_366 367
#define Mfx_Inc_367 368
#define Mfx_Inc_368 369
#define Mfx_Inc_369 370
#define Mfx_Inc_370 371
#define Mfx_Inc_371 372
#define Mfx_Inc_372 373
#define Mfx_Inc_373 374
#define Mfx_Inc_374 375
#define Mfx_Inc_375 376
#define Mfx_Inc_376 377
#define Mfx_Inc_377 378
#define Mfx_Inc_378 379
#define Mfx_Inc_379 380
#define Mfx_Inc_380 381
#define Mfx_Inc_381 382
#define Mfx_Inc_382 383
#define Mfx_Inc_383 384
#define Mfx_Inc_384 385
#define Mfx_Inc_385 386
#define Mfx_Inc_386 387
#define Mfx_Inc_387 388
#define Mfx_Inc_388 389
#define Mfx_Inc_389 390
#define Mfx_Inc_390 391
#define Mfx_Inc_391 392
#define Mfx_Inc_392 393
#define Mfx_Inc_393 394
#define Mfx_Inc_394 395
#define Mfx_Inc_395 396
#define Mfx_Inc_396 397
#define Mfx_Inc_397 398
#define Mfx_Inc_398 399
#define Mfx_Inc_399 400
#define Mfx_Inc_400 401
#define Mfx_Inc_401 402
#define Mfx_Inc_402 403
#define Mfx_Inc_403 404
#define Mfx_Inc_404 405
#define Mfx_Inc_405 406
#define Mfx_Inc_406 407
#define Mfx_Inc_407 408
#define Mfx_Inc_408 409
#define Mfx_Inc_409 410
#define Mfx_Inc_410 411
#define Mfx_Inc_411 412
#define Mfx_Inc_412 413
#define Mfx_Inc_413 414
#define Mfx_Inc_414 415
#define Mfx_Inc_415 416
#define Mfx_Inc_416 417
#define Mfx_Inc_417 418
#define Mfx_Inc_418 419
#define Mfx_Inc_419 420
#define Mfx_Inc_420 421
#define Mfx_Inc_421 422
#define Mfx_Inc_422 423
#define Mfx_Inc_423 424
#define Mfx_Inc_424 425
#define Mfx_Inc_425 426
#define Mfx_Inc_426 427
#define Mfx_Inc_427 428
#define Mfx_Inc_428 429
#define Mfx_Inc_429 430
#define Mfx_Inc_430 431
#define Mfx_Inc_431 432
#define Mfx_Inc_432 433
#define Mfx_Inc_433 434
#define Mfx_Inc_434 435
#define Mfx_Inc_435 436
#define Mfx_Inc_436 437
#define Mfx_Inc_437 438
#define Mfx_Inc_438 439
#define Mfx_Inc_439 440
#define Mfx_Inc_440 441
#define Mfx_Inc_441 442
#define Mfx_Inc_442 443
#define Mfx_Inc_443 444
#define Mfx_Inc_444 445
#define Mfx_Inc_445 446
#define Mfx_Inc_446 447
#define Mfx_Inc_447 448
#define Mfx_Inc_448 449
#define Mfx_Inc_449 450
#define Mfx_Inc_450 451
#define Mfx_Inc_451 452
#define Mfx_Inc_452 453
#define Mfx_Inc_453 454
#define Mfx_Inc_454 455
#define Mfx_Inc_455 456
#define Mfx_Inc_456 457
#define Mfx_Inc_457 458
#define Mfx_Inc_458 459
#define Mfx_Inc_459 460
#define Mfx_Inc_460 461
#define Mfx_Inc_461 462
#define Mfx_Inc_462 463
#define Mfx_Inc_463 464
#define Mfx_Inc_464 465
#define Mfx_Inc_465 466
#define Mfx_Inc_466 467
#define Mfx_Inc_467 468
#define Mfx_Inc_468 469
#define Mfx_Inc_469 470
#define Mfx_Inc_470 471
#define Mfx_Inc_471 472
#define Mfx_Inc_472 473
#define Mfx_Inc_473 474
#define Mfx_Inc_474 475
#define Mfx_Inc_475 476
#define Mfx_Inc_476 477
#define Mfx_Inc_477 478
#define Mfx_Inc_478 479
#define Mfx_Inc_479 480
#define Mfx_Inc_480 481
#define Mfx_Inc_481 482
#define Mfx_Inc_482 483
#define Mfx_Inc_483 484
#define Mfx_Inc_484 485
#define Mfx_Inc_485 486
#define Mfx_Inc_486 487
#define Mfx_Inc_487 488
#define Mfx_Inc_488 489
#define Mfx_Inc_489 490
#define Mfx_Inc_490 491
#define Mfx_Inc_491 492
#define Mfx_Inc_492 493
#define Mfx_Inc_493 494
#define Mfx_Inc_494 495
#define Mfx_Inc_495 496
#define Mfx_Inc_496 497
#define Mfx_Inc_497 498
#define Mfx_Inc_498 499
#define Mfx_Inc_499 500
#define Mfx_Inc_500 501
#define Mfx_Inc_501 502
#define Mfx_Inc_502 503
#define Mfx_Inc_503 504
#define Mfx_Inc_504 505
#define Mfx_Inc_505 506
#define Mfx_Inc_506 507
#define Mfx_Inc_507 508
#define Mfx_Inc_508 509
#define Mfx_Inc_509 510
#define Mfx_Inc_510 511
#define Mfx_Inc_511 512


#define MfxAutoFunc_AutoEnum_ArgcMap_3 1

#define MfxAutoFunc_AutoEnum_ArgcMap_5 2

#define MfxAutoFunc_AutoEnum_ArgcMap_7 3

#define MfxAutoFunc_AutoEnum_ArgcMap_9 4

#define MfxAutoFunc_AutoEnum_ArgcMap_11 5

#define MfxAutoFunc_AutoEnum_ArgcMap_13 6

#define MfxAutoFunc_AutoEnum_ArgcMap_15 7

#define MfxAutoFunc_AutoEnum_ArgcMap_17 8

#define MfxAutoFunc_AutoEnum_ArgcMap_19 9

#define MfxAutoFunc_AutoEnum_ArgcMap_21 10

#define MfxAutoFunc_AutoEnum_ArgcMap_23 11

#define MfxAutoFunc_AutoEnum_ArgcMap_25 12

#define MfxAutoFunc_AutoEnum_ArgcMap_27 13

#define MfxAutoFunc_AutoEnum_ArgcMap_29 14

#define MfxAutoFunc_AutoEnum_ArgcMap_31 15

#define MfxAutoFunc_AutoEnum_ArgcMap_33 16

#define MfxAutoFunc_AutoEnum_ArgcMap_35 17

#define MfxAutoFunc_AutoEnum_ArgcMap_37 18

#define MfxAutoFunc_AutoEnum_ArgcMap_39 19

#define MfxAutoFunc_AutoEnum_ArgcMap_41 20

#define MfxAutoFunc_AutoEnum_ArgcMap_43 21

#define MfxAutoFunc_AutoEnum_ArgcMap_45 22

#define MfxAutoFunc_AutoEnum_ArgcMap_47 23

#define MfxAutoFunc_AutoEnum_ArgcMap_49 24

#define MfxAutoFunc_AutoEnum_ArgcMap_51 25

#define MfxAutoFunc_AutoEnum_ArgcMap_53 26

#define MfxAutoFunc_AutoEnum_ArgcMap_55 27

#define MfxAutoFunc_AutoEnum_ArgcMap_57 28

#define MfxAutoFunc_AutoEnum_ArgcMap_59 29

#define MfxAutoFunc_AutoEnum_ArgcMap_61 30

#define MfxAutoFunc_AutoEnum_ArgcMap_63 31

#define MfxAutoFunc_AutoEnum_ArgcMap_65 32

#define MfxAutoFunc_AutoEnum_ArgcMap_67 33

#define MfxAutoFunc_AutoEnum_ArgcMap_69 34

#define MfxAutoFunc_AutoEnum_ArgcMap_71 35

#define MfxAutoFunc_AutoEnum_ArgcMap_73 36

#define MfxAutoFunc_AutoEnum_ArgcMap_75 37

#define MfxAutoFunc_AutoEnum_ArgcMap_77 38

#define MfxAutoFunc_AutoEnum_ArgcMap_79 39

#define MfxAutoFunc_AutoEnum_ArgcMap_81 40

#define MfxAutoFunc_AutoEnum_ArgcMap_83 41

#define MfxAutoFunc_AutoEnum_ArgcMap_85 42

#define MfxAutoFunc_AutoEnum_ArgcMap_87 43

#define MfxAutoFunc_AutoEnum_ArgcMap_89 44

#define MfxAutoFunc_AutoEnum_ArgcMap_91 45

#define MfxAutoFunc_AutoEnum_ArgcMap_93 46

#define MfxAutoFunc_AutoEnum_ArgcMap_95 47

#define MfxAutoFunc_AutoEnum_ArgcMap_97 48

#define MfxAutoFunc_AutoEnum_ArgcMap_99 49

#define MfxAutoFunc_AutoEnum_ArgcMap_101 50

#define MfxAutoFunc_AutoEnum_ArgcMap_103 51

#define MfxAutoFunc_AutoEnum_ArgcMap_105 52

#define MfxAutoFunc_AutoEnum_ArgcMap_107 53

#define MfxAutoFunc_AutoEnum_ArgcMap_109 54

#define MfxAutoFunc_AutoEnum_ArgcMap_111 55

#define MfxAutoFunc_AutoEnum_ArgcMap_113 56

#define MfxAutoFunc_AutoEnum_ArgcMap_115 57

#define MfxAutoFunc_AutoEnum_ArgcMap_117 58

#define MfxAutoFunc_AutoEnum_ArgcMap_119 59

#define MfxAutoFunc_AutoEnum_ArgcMap_121 60

#define MfxAutoFunc_AutoEnum_ArgcMap_123 61

#define MfxAutoFunc_AutoEnum_ArgcMap_125 62

#define MfxAutoFunc_Enum_1(OBJ, NUM_1, FUNC_1, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, END)

#define MfxAutoFunc_Enum_2(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_1(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_3(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_2(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_4(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_3(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_5(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_4(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_6(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_5(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_7(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_6(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_8(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_7(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_9(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_8(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_10(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_9(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_11(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_10(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_12(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_11(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_13(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_12(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_14(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_13(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_15(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_14(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_16(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_15(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_17(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_16(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_18(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_17(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_19(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_18(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_20(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_19(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_21(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_20(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_22(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_21(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_23(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_22(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_24(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_23(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_25(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_24(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_26(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_25(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_27(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_26(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_28(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_27(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_29(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_28(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_30(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_29(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_31(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_30(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_32(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_31(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_33(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_32(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_34(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_33(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_35(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_34(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_36(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_35(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_37(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_36(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_38(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_37(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_39(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_38(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_40(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_39(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_41(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_40(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_42(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_41(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_43(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_42(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_44(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_43(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_45(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_44(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_46(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_45(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_47(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_46(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_48(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_47(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_49(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_48(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_50(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_49(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_51(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_50(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_52(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_51(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_53(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_52(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_54(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_53(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_55(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_54(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_56(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_55(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_57(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_56(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_58(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_57(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_59(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_58(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_60(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_59(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_61(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_60(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_62(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_61(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_63(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_62(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_64(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_63(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_65(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_64(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_66(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_65(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_67(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_66(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_68(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_67(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_69(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_68(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_70(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_69(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_71(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_70(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_72(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_71(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_73(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_72(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_74(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_73(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_75(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_74(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_76(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_75(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_77(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_76(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_78(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_77(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_79(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_78(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_80(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_79(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_81(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_80(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_82(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_81(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_83(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_82(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_84(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_83(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_85(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_84(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_86(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_85(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_87(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_86(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_88(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_87(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_89(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_88(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_90(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_89(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_91(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_90(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_92(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_91(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_93(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_92(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_94(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_93(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_95(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_94(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_96(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_95(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_97(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_96(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_98(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_97(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_99(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_98(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_100(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_99(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_101(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_100(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_102(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_101(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_103(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_102(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_104(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_103(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_105(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_104(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_106(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_105(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_107(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_106(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_108(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_107(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_109(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_108(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_110(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_109(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_111(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_110(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_112(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_111(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_113(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_112(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_114(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_113(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_115(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_114(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_116(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_115(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_117(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_116(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_118(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_117(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_119(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_118(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_120(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_119(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_121(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_120(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_122(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_121(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_123(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_122(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_124(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_123(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_125(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_124(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_126(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_125(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_127(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_126(OBJ, NUM_2, FUNC_2, __VA_ARGS__))

#define MfxAutoFunc_Enum_128(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CONNECT(MfxAutoFunc_Enum_127(OBJ, NUM_2, FUNC_2, __VA_ARGS__))



// 实验失败的宏递归
// 宏不支持递归展开
#define Mfx_AutoEnumBig_ForInc(Num) CONNECT(Mfx_AutoEnumBig_ForInc_, Num)
#define Mfx_AutoEnumBig_ForInc_0 1
#define Mfx_AutoEnumBig_ForInc_1 0
#define Mfx_AutoEnumBig_ForInc_END END

#define __MfxAutoFunc_AutoEnumBig(BEGIN, OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, FLAG, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CCCCONNECT(CCCONNECT(MfxAutoFunc_AutoEnumBig_, CCONNECT(Mfx_AutoEnumBig_ForInc(BEGIN) , FLAG))(BEGIN, OBJ, NUM_2, FUNC_2, FLAG, __VA_ARGS__))

#define MfxAutoFunc_AutoEnumBig_END(BEGIN, OBJ, NUM_1, FUNC_1, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, END)

#define MfxAutoFunc_AutoEnumBig_00(BEGIN, OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, FLAG, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CCCCONNECT(CCCONNECT(MfxAutoFunc_AutoEnumBig_, CCONNECT(Mfx_AutoEnumBig_ForInc(BEGIN), FLAG))(BEGIN, OBJ, NUM_2, FUNC_2, FLAG, __VA_ARGS__))

#define MfxAutoFunc_AutoEnumBig_10(BEGIN, OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, FLAG, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CCCCONNECT(CCCONNECT(MfxAutoFunc_AutoEnumBig_, CCONNECT(Mfx_AutoEnumBig_ForInc(BEGIN), FLAG))(BEGIN, OBJ, NUM_2, FUNC_2, FLAG, __VA_ARGS__))

#define MfxAutoFunc_AutoEnumBig_01(BEGIN, OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, FLAG, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CCCCONNECT(CCCONNECT(MfxAutoFunc_AutoEnumBig_, CCONNECT(Mfx_AutoEnumBig_ForInc(BEGIN), FLAG))(BEGIN, OBJ, NUM_2, FUNC_2, FLAG, __VA_ARGS__))

#define MfxAutoFunc_AutoEnumBig_11(BEGIN, OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, FLAG, ...)\
    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\
    CCCCONNECT(CCCONNECT(MfxAutoFunc_AutoEnumBig_, CCONNECT(Mfx_AutoEnumBig_ForInc(BEGIN), FLAG))(BEGIN, OBJ, NUM_2, FUNC_2, FLAG, __VA_ARGS__))