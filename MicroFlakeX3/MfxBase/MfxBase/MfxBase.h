#pragma once

/*
* MfxBase.h提供了关于构造DeepSpace的基础类
* 
* DeepSpace编码规范:
* 
* 强制
* 1、所有的类必须继承于 MfxBase
* 2、所有的类必须实现 'operator=' 和 'Clone' 
* 3、所有的类的构造函数不允许出现参数
* 4、所有的 MfxBase 子类，都必须使用 MfxObject(obj) 声明
* 5、所有的方法、函数返回值必须为 MfxReturn，
* 6、形参如果是输入值，必须以 set 开头；如果是返回值，必须以 ret 开头
* 7、任何添加到 AutoFunc 的方法，不允许重载、不允许使用右值引用、不允许使用引用传递。
* 
* 
* 可选
* 1、每次调用方法之后，都判断 MfxReturn，是否成功
* 2、实现类的 'operator==' ，以方便判断两个对象是否相等
* 
* 
* 必要知识
* 1、关于继承
*		如果子类实现了一个和父类同名的方法，并且都注册了 AutoFunc，
*	那么，通过 AutoFunc 调用该方法的顺序为：父类->子类，如果父类失
*	败，那么将不会执行子类方法，直接返回 RFail 。
*		如果继承方式为：基类->类0->类1->类2，并且类0 、类2都注册了
*	'Hello()'，调用顺序为：类2::Hello()，即类0被覆盖。
* 
* 
* 
* 更新：
* 1、线程池
* 2、debug内存泄漏检测
* 3、
*/


#ifdef MFX_BUILDING
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
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
/**/
#endif

//公开 类型
typedef long MfxReturn;
typedef std::string MfxStringA;
typedef std::wstring MfxStringW;

#ifdef UNICODE
#define __MfxText(str) L##str
#define __MfxString MfxStringW


#elif 
#define __MfxText(str) str
#define __MfxString MfxStringA;

#endif

#define MfxString __MfxString
#define MfxText(str) __MfxText(str)

//公开 类 - 模板
namespace MicroFlakeX
{
	class MFX_PORT MfxBase;
	class MFX_PORT MfxLock;


	typedef std::vector<MfxBase*> MfxBase_Vector;
	//Mfx模板
	template<class DataType>
	class MfxDataFlag;

	template<class T>
	class MfxSmartPointer;

	template<class T>
	class MfxThreadPool;
}

//公开 函数
namespace MicroFlakeX
{
	//Mfx工厂
	MFX_PORT MfxReturn MfxBaseFactory(MfxString object, MfxBase** ret);
}

//公开 宏
namespace MicroFlakeX
{
	//强制 MfxReturn必须选择下列一项返回
#define RFine __RFine
#define RFail __RFail

	//可选 检查Mfx函数是否成功
#define Failed(mr) __Failed(mr)
#define Seccess(mr) __Seccess(mr)

	//强制 所有子类都需要声明
#define MfxObject __MfxObject

	//强制 所有的方法在使用前必须使用，以保证线程安全
#define MfxCodeLock(obj) __MfxCodeLock(obj)

	//强制 所有的子类必须在其.cpp中优先顺序调用下列三个初始化
#define MfxObject_Init_0(obj) __MfxObject_Init_0(obj)
#define MfxObject_Init_1(obj) __MfxObject_Init_1(obj)
#define MfxObject_Init_2(obj, father) __MfxObject_Init_2(obj, father)

	//可选 注册反射调用 -强制 只能在INIT_0-INIT_1之间使用
#define MfxObject_Register(obj, func, id) __MfxObject_Register(obj, func, id) 

	//可选 实现反射调用 -强制 只能在INIT_1-INIT_2之间使用
#define MfxObject_Case_0(obj, father, func, id) __MfxObject_Case_0(obj, father, func, id) 
#define MfxObject_Case_1(obj, father, func, id) __MfxObject_Case_1(obj, father, func, id) 
#define MfxObject_Case_2(obj, father, func, id) __MfxObject_Case_2(obj, father, func, id) 
#define MfxObject_Case_3(obj, father, func, id) __MfxObject_Case_3(obj, father, func, id) 
#define MfxObject_Case_4(obj, father, func, id) __MfxObject_Case_4(obj, father, func, id) 
#define MfxObject_Case_5(obj, father, func, id) __MfxObject_Case_5(obj, father, func, id) 
#define MfxObject_Case_6(obj, father, func, id) __MfxObject_Case_6(obj, father, func, id) 
#define MfxObject_Case_7(obj, father, func, id) __MfxObject_Case_7(obj, father, func, id) 
#define MfxObject_Case_8(obj, father, func, id) __MfxObject_Case_8(obj, father, func, id) 
}

//内部 类型 - 类 - 函数 - 模板 - 宏
namespace __MicroFlakeX
{
	class MFX_PORT MfxFactoryHand;
	MFX_PORT MfxReturn MfxRemoveObject(MfxString object);
	MFX_PORT MfxReturn MfxRegisterObject(MfxString object, MfxFactoryHand* hand);
}

//公开 类声明
namespace MicroFlakeX
{
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

	class MfxLock
	{
	private:
		CRITICAL_SECTION* myCriticalSection;
	public:
		MfxLock(MfxBase* object);
		~MfxLock();
	};
}

//内部 类声明
namespace __MicroFlakeX
{
	class MFX_PORT MfxFactoryHand
	{
	public:
		MfxFactoryHand(MfxString object);
		virtual MfxReturn Creat(MicroFlakeX::MfxBase** ret) = 0;
		virtual ~MfxFactoryHand();
	private:
		MfxString myObjectName;
	};
}

//公开 模板实现
namespace MicroFlakeX
{
	template<typename Func>
	struct MfxArgNum_;
	template<typename R, class O, typename... Args>
	struct MfxArgNum_<R(O::*)(Args...)> { static const int num = sizeof...(Args); };
	template<typename Func>
	int MfxArgNum(Func) { return MfxArgNum_<Func>::num; };

	template <class R, class O, class A1, class... Args>
	A1 MfxArg1(R(O::*)(A1, Args...)) { return A1(); };
	template <class R, class O, class A1, class A2, class... Args>
	A2 MfxArg2(R(O::*)(A1, A2, Args...)) { return A2(); };
	template <class R, class O, class A1, class A2, class A3, class... Args>
	A3 MfxArg3(R(O::*)(A1, A2, A3, Args...)) { return A3(); };
	template <class R, class O, class A1, class A2, class A3, class A4, class... Args>
	A4 MfxArg4(R(O::*)(A1, A2, A3, A4, Args...)) { return A4(); };
	template <class R, class O, class A1, class A2, class A3, class A4, class A5, class... Args>
	A5 MfxArg5(R(O::*)(A1, A2, A3, A4, A5, Args...)) { return A5(); };
	template <class R, class O, class A1, class A2, class A3, class A4, class A5, class A6, class... Args>
	A6 MfxArg6(R(O::*)(A1, A2, A3, A4, A5, A6, Args...)) { return A6(); };
	template <class R, class O, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class... Args>
	A7 MfxArg7(R(O::*)(A1, A2, A3, A4, A5, A6, A7, Args...)) { return A7(); };
	template <class R, class O, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class... Args>
	A8 MfxArg8(R(O::*)(A1, A2, A3, A4, A5, A6, A7, A8, Args...)) { return A8(); };

	template<class DataType>
	class MfxDataFlag
	{
	public:
		MfxDataFlag()
		{
			myBeforData = myData = DataType();
			myChangeFlag = myUseFlag = 0;
		}
		~MfxDataFlag() { };
		DataType& GetData() { return myData; };
		DataType& GetBeforData() { return myBeforData; };
		void CleanUseFlag() { myUseFlag = 0; }
		void CleanChangeFlag() { myChangeFlag = 0; }
		UINT CheckUseFlag() { return myUseFlag; };
		UINT CheckChangeFlag() { return myChangeFlag; };
	private:
		DataType myData;
		DataType myBeforData;
		UINT myUseFlag;
		UINT myChangeFlag;
	public:
		DataType operator-> () { myUseFlag++; return myData; };

		DataType& operator* () { myUseFlag++; return myData; };

		DataType operator= (DataType rhs)
		{
			myChangeFlag++;
			myBeforData = myData;
			myData = rhs;
			return myData;
		};

		bool operator< (DataType rhs) { return myData < rhs; };

		bool operator> (DataType rhs) { return myData > rhs; };

		bool operator== (DataType rhs) { return myData == rhs; };

		bool operator!= (DataType rhs) { return myData != rhs; };
	};

		//Mfx智能指针

		//Mfx线程池
}

#define __RFine	0
#define __RFail	-1

#define __Seccess(DR)	(((MfxReturn)(DR)) >= 0)
#define __Failed(DR)	(((MfxReturn)(DR)) < 0)

#define __MfxCodeLock(obj) \
	MfxLock tLock(obj);

#define __MfxObject \
public:\
	MfxReturn AutoFunc(MfxString setFunc...);\
	MfxReturn FuncName(MfxString* ret);\
	MfxReturn ObjectName(MfxString* ret);
	
//---------------------------------------------------
// 
//---------------------------------------------------
#define __MfxObject_Init_0(obj) \
using namespace MicroFlakeX;\
using namespace __MicroFlakeX;\
using MicroFlakeX::obj;\
struct obj##MfxAutoFuncInfor\
{\
	int myID = 0;\
	MfxString  myName;\
	MfxString myAllName;\
};\
std::map<MfxString, obj##MfxAutoFuncInfor*> obj##MfxAutoFuncMap;\
typedef std::map<MfxString,obj##MfxAutoFuncInfor*>::value_type obj##MfxAutoFuncValue;\
typedef std::map<MfxString,obj##MfxAutoFuncInfor*>::iterator obj##MfxAutoFuncIterator;\
MfxReturn obj::FuncName(MfxString* ret)\
{\
	*ret = MfxText("");\
	for(auto i : obj##MfxAutoFuncMap)\
	{\
		*ret += i.second->myName;\
		*ret += MfxText("...\n");\
	}\
	return RFine;\
}\
MfxReturn obj::ObjectName(MfxString* ret)\
{\
	*ret = MfxText(#obj);\
	return RFine;\
}\
class obj##FactoryHand\
	: public MfxFactoryHand\
{\
public:\
	obj##FactoryHand(MfxString object)\
		: MfxFactoryHand(object)\
	{\
		obj##MfxAutoFuncInfor* infor = nullptr;\
		WCHAR typeName[1024]; size_t n = 0;\
		MfxObject_Register(obj, AutoFunc, -1)
//---------------------------------------------------
//
//---------------------------------------------------
#define __MfxObject_Init_1(obj) \
	};\
	MfxReturn Creat(MfxBase** ret)\
	{\
		*ret = new obj;\
		return RFine;\
	}\
};\
obj##FactoryHand obj##Hand(MfxText(#obj));\
MfxReturn obj::AutoFunc(MfxString setFunc...)\
{\
	MfxCodeLock(this);\
	MfxReturn ret = RFail;\
	va_list argc;\
	va_start(argc, setFunc);\
	obj##MfxAutoFuncIterator iter = obj##MfxAutoFuncMap.end();\
	BeginSwitch:\
	iter = obj##MfxAutoFuncMap.find(setFunc); \
	if (iter != obj##MfxAutoFuncMap.end())\
	{\
		int caID = iter->second->myID;\
		switch (caID)\
		{
//---------------------------------------------------
// 
//---------------------------------------------------
#define __MfxObject_Init_2(obj, father) \
		case -1:\
		{\
			setFunc = va_arg(argc, MfxString);\
			argc = va_arg(argc, va_list);\
			goto BeginSwitch;\
			break;\
		}\
		}\
	}\
	else\
	{\
		ret = father::AutoFunc(MfxText("AutoFunc"), setFunc, argc); \
	}\
	return ret;\
}

//---------------------------------------------------
// 
//---------------------------------------------------
#define __MfxObject_Register(obj, func, id) \
infor = new obj##MfxAutoFuncInfor;\
infor->myID = id;\
infor->myName = L#func;\
mbstowcs_s(&n, typeName, 1024,\
	typeid(&obj::func).name(), 1023);\
infor->myAllName = typeName;\
obj##MfxAutoFuncMap.insert(obj##MfxAutoFuncValue(L#func, infor));

#define __MfxObject_Case_0(obj, father, func, id) \
case id:\
{\
	ret = func();\
	break;\
}

#define __MfxObject_Case_1(obj, father, func, id) \
case id:\
{\
	auto A1 = va_arg(argc, decltype(MfxArg1(&obj::func)));\
	ret = func(A1);\
	break;\
}

#define __MfxObject_Case_2(obj, father, func, id) \
case id:\
{\
	auto A1 = va_arg(argc, decltype(MfxArg1(&obj::func)));\
	auto A2 = va_arg(argc, decltype(MfxArg2(&obj::func)));\
	ret = func(A1, A2);\
	break;\
}

#define __MfxObject_Case_3(obj, father, func, id) \
case id:\
{\
	auto A1 = va_arg(argc, decltype(MfxArg1(&obj::func)));\
	auto A2 = va_arg(argc, decltype(MfxArg2(&obj::func)));\
	auto A3 = va_arg(argc, decltype(MfxArg3(&obj::func)));\
	ret = func(A1, A2, A3);\
	break;\
}

#define __MfxObject_Case_4(obj, father, func, id) \
case id:\
{\
	auto A1 = va_arg(argc, decltype(MfxArg1(&obj::func)));\
	auto A2 = va_arg(argc, decltype(MfxArg2(&obj::func)));\
	auto A3 = va_arg(argc, decltype(MfxArg3(&obj::func)));\
	auto A4 = va_arg(argc, decltype(MfxArg4(&obj::func)));\
	ret = func(A1, A2, A3, A4);\
	break;\
}

#define __MfxObject_Case_5(obj, father, func, id) \
case id:\
{\
	auto A1 = va_arg(argc, decltype(MfxArg1(&obj::func)));\
	auto A2 = va_arg(argc, decltype(MfxArg2(&obj::func)));\
	auto A3 = va_arg(argc, decltype(MfxArg3(&obj::func)));\
	auto A4 = va_arg(argc, decltype(MfxArg4(&obj::func)));\
	auto A5 = va_arg(argc, decltype(MfxArg5(&obj::func)));\
	ret = func(A1, A2, A3, A4, A5);\
	break;\
}

#define __MfxObject_Case_6(obj, father, func, id) \
case id:\
{\
	auto A1 = va_arg(argc, decltype(MfxArg1(&obj::func)));\
	auto A2 = va_arg(argc, decltype(MfxArg2(&obj::func)));\
	auto A3 = va_arg(argc, decltype(MfxArg3(&obj::func)));\
	auto A4 = va_arg(argc, decltype(MfxArg4(&obj::func)));\
	auto A5 = va_arg(argc, decltype(MfxArg5(&obj::func)));\
	auto A6 = va_arg(argc, decltype(MfxArg6(&obj::func)));\
	ret = func(A1, A2, A3, A4, A5, A6);\
	break;\
}

#define __MfxObject_Case_7(obj, father, func, id) \
case id:\
{\
	auto A1 = va_arg(argc, decltype(MfxArg1(&obj::func)));\
	auto A2 = va_arg(argc, decltype(MfxArg2(&obj::func)));\
	auto A3 = va_arg(argc, decltype(MfxArg3(&obj::func)));\
	auto A4 = va_arg(argc, decltype(MfxArg4(&obj::func)));\
	auto A5 = va_arg(argc, decltype(MfxArg5(&obj::func)));\
	auto A6 = va_arg(argc, decltype(MfxArg6(&obj::func)));\
	auto A7 = va_arg(argc, decltype(MfxArg7(&obj::func)));\
	ret = func(A1, A2, A3, A4, A5, A6, A7);\
	break;\
}

#define __MfxObject_Case_8(obj, father, func, id) \
case id:\
{\
	auto A1 = va_arg(argc, decltype(MfxArg1(&obj::func)));\
	auto A2 = va_arg(argc, decltype(MfxArg2(&obj::func)));\
	auto A3 = va_arg(argc, decltype(MfxArg3(&obj::func)));\
	auto A4 = va_arg(argc, decltype(MfxArg4(&obj::func)));\
	auto A5 = va_arg(argc, decltype(MfxArg5(&obj::func)));\
	auto A6 = va_arg(argc, decltype(MfxArg6(&obj::func)));\
	auto A7 = va_arg(argc, decltype(MfxArg7(&obj::func)));\
	auto A8 = va_arg(argc, decltype(MfxArg8(&obj::func)));\
	ret = func(A1, A2, A3, A4, A5, A6, A7, A8);\
	break;\
}

