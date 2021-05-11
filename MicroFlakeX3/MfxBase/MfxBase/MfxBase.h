#pragma once

/**************************************************************************************************
*	UTF-8
* 
*   版本：1.01       作者：yishengjun8     
*	
* 
*	简介
*	MfxBase.h	提供了构造	MicroFlakeX	的基础类和基础支持
*	
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
#include <mutex>
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

#define Failed(mr) (((MfxReturn)(DR)) < 0)
#define Seccess(mr) (((MfxReturn)(DR)) >= 0)

	/***************************************************************
	*	字符集自动展开宏
	* 
	*	MfxString str = MfxText("str")
	* 
	*	MfxString	和	MfxText()	均被自动展开到当前编码的字符集合
	*	
	****************************************************************/
	typedef std::string MfxStringA;
	typedef std::wstring MfxStringW;

#define MfxString __MfxString
#define MfxText(str) __MfxText(str)

#ifdef UNICODE
#define __MfxText(str) L##str
#define __MfxString MfxStringW
#elif 
#define __MfxText(str) str
#define __MfxString MfxStringA;
#endif
}

namespace MicroFlakeX
{
	/***************************************************************
	* 
	*	MfxBase	的前置声明和导出标识，以及	MicroFlakeX	扩展功能
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
	*	更加详细的MfxObject宏示例请参照	MfxBaseTest00.h	
	*	
	*	MfxCodeLock宏：
	*		1、MfxBase	支持线程安全，具体方案就是保证对象不会在同一时间被两个不同的线程
	*		同时访问其有冲突的方法。
	*		2、请在会造成线程冲突的对象方法开始的时候，添加	MfxCodeLock(this);	语句，以
	*		保证访问唯一性。
	* 
	* 
	****************************************************************/
	class MFX_PORT MfxBase;
	class MFX_PORT MfxLock;

#define MfxObject __MfxObject

#define MfxCodeLock(OBJ) __MfxCodeLock(OBJ)

#define MfxObject_Init_0(OBJ) __MfxObject_Init_0(OBJ)
#define MfxObject_Init_1(OBJ, GOTO_BEGIN) __MfxObject_Init_1(OBJ, GOTO_BEGIN)
#define MfxObject_Init_2(OBJ, FATHER_OBJ) __MfxObject_Init_2(OBJ, FATHER_OBJ)

#define MfxAutoFunc_AutoEnum(...) CONNECT(__MfxAutoFunc_AutoEnum, (__VA_ARGS__))

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
	typedef std::deque<MfxBase*> MfxBase_Deque;
	typedef std::vector<MfxBase*> MfxBase_Vector;

	/***************************************************************
	*
	*	MicroFlakeX	主工厂
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
		virtual MfxBase& operator=(MfxBase& rhs);
		virtual BOOL operator==(MfxBase& rhs);

	public:
		virtual MfxReturn AutoFunc(MfxString func...);
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
	private:
		CRITICAL_SECTION* myCriticalSection;
	public:
		MfxLock(MfxBase* object);
		~MfxLock();
	};
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
	MfxReturn AutoFunc(MfxString setFunc...);\
	MfxReturn FuncName(MfxString* ret);\
	MfxReturn ObjectName(MfxString* ret);


/***************************************************************
*
*
*
****************************************************************/
#define __MfxObject_Init_0(OBJ)\
using namespace MicroFlakeX;\
using namespace __MicroFlakeX;\
using MicroFlakeX::OBJ;\
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
MfxReturn OBJ::AutoFunc(MfxString setFunc...)\
{\
	MfxReturn ret = Mfx_Return_Fail;\
	int countID = 0;\
	int iterID = 0;\
	va_list argc;\
	va_start(argc, setFunc);\
	auto iter = Mfx##OBJ##FuncMap.end();\
	if(OBJ##isFirst)\
	{\
		OBJ##isFirst = false;\
		goto REG_##GOTO_BEGIN;\
	}\
	\
	BeginSwitch:\
	iter = Mfx##OBJ##FuncMap.find(setFunc);\
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
			setFunc = va_arg(argc, MfxString);\
			argc = va_arg(argc, va_list);\
			goto BeginSwitch;\
			REG_END:\
				Mfx##OBJ##FuncMap.insert(Mfx##OBJ##FuncMapValue(MfxText("AUTOFUNC_NOTFOUND"), countID++));\
			goto BeginSwitch;\
		}\
	}\
	else\
	{\
		return FATHER_OBJ::AutoFunc(MfxText("AUTOFUNC_NOTFOUND"), setFunc, argc); \
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
		return AUTO_FUNC(); \
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
		return AUTO_FUNC(A1); \
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
****************************************************************/
#define MfxAutoFunc_AutoEnum_ArgcMap(NUM) CCONNECT(MfxAutoFunc_AutoEnum_ArgcMap_, NUM)

#define MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2) CCONNECT(CONNECT(MfxAutoFunc_, NUM_1), (OBJ, FUNC_1, FUNC_2))

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