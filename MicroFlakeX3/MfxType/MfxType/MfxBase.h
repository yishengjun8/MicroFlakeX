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
* 4、所有的 MfxBase 子类，都必须使用 MfxOBJECT(obj) 声明
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
*	败，那么将不会执行子类方法，直接返回 MfxFAIL 。
*		如果继承方式为：基类->类0->类1->类2，并且类0 、类2都注册了
*	'Hello()'，调用顺序为：类0::Hello()->类2::Hello()。
*/
#ifdef MfxBUILDING
#define MfxPORT __declspec(dllexport)
#else
#define MfxPORT __declspec(dllimport)
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
namespace MicroFlakeX
{
	MfxPORT typedef long MfxReturn;
	MfxPORT typedef std::string MfxStrA;
	MfxPORT typedef std::wstring MfxStrW;

	MfxPORT typedef MfxStrW MfxStr;
}

//公开 类 - 模板
namespace MicroFlakeX
{
	class MfxPORT MfxBase;
	class MfxPORT MfxLock;

	//Mfx模板
}

//公开 函数
namespace MicroFlakeX
{
	//Mfx工厂
	MfxPORT MfxReturn MfxBaseFactory(MfxStrW object, MfxBase** ret);
}

//公开 宏
namespace MicroFlakeX
{
	//强制 MfxReturn必须选择下列一项返回
#define MfxFINE __MfxFINE
#define MfxFAIL __MfxFAIL

	//可选 检查Mfx函数是否成功
#define Mfx_FAILED(DR) __Mfx_NO(DR)
#define Mfx_SECCESS(DR) __Mfx_OK(DR)

	//强制 所有子类都需要声明
#define MfxOBJECT __MfxOBJECT

	//强制 所有的方法在使用前必须使用，以保证线程安全
#define MfxCODELOCK(obj) __MfxCODELOCK(obj)

	//强制 所有的子类必须在其.cpp中优先顺序调用下列三个初始化
#define MfxOBJECT_INIT_0(obj) __MfxOBJECT_INIT_0(obj)
#define MfxOBJECT_INIT_1(obj) __MfxOBJECT_INIT_1(obj)
#define MfxOBJECT_INIT_2(obj, father) __MfxOBJECT_INIT_2(obj, father)

	//可选 注册反射调用 -强制 只能在INIT_0-INIT_1之间使用
#define MfxOBJECT_AUTOFUNC_REG(obj, func, id) __MfxOBJECT_AUTOFUNC_REG(obj, func, id) 

	//可选 实现反射调用 -强制 只能在INIT_1-INIT_2之间使用
#define MfxOBJECT_AUTOFUNC_CASE_0(obj, father, func, id) __MfxOBJECT_AUTOFUNC_CASE_0(obj, father, func, id) 
#define MfxOBJECT_AUTOFUNC_CASE_1(obj, father, func, id) __MfxOBJECT_AUTOFUNC_CASE_1(obj, father, func, id) 
#define MfxOBJECT_AUTOFUNC_CASE_2(obj, father, func, id) __MfxOBJECT_AUTOFUNC_CASE_2(obj, father, func, id) 
#define MfxOBJECT_AUTOFUNC_CASE_3(obj, father, func, id) __MfxOBJECT_AUTOFUNC_CASE_3(obj, father, func, id) 
#define MfxOBJECT_AUTOFUNC_CASE_4(obj, father, func, id) __MfxOBJECT_AUTOFUNC_CASE_4(obj, father, func, id) 
#define MfxOBJECT_AUTOFUNC_CASE_5(obj, father, func, id) __MfxOBJECT_AUTOFUNC_CASE_5(obj, father, func, id) 
#define MfxOBJECT_AUTOFUNC_CASE_6(obj, father, func, id) __MfxOBJECT_AUTOFUNC_CASE_6(obj, father, func, id) 
#define MfxOBJECT_AUTOFUNC_CASE_7(obj, father, func, id) __MfxOBJECT_AUTOFUNC_CASE_7(obj, father, func, id) 
#define MfxOBJECT_AUTOFUNC_CASE_8(obj, father, func, id) __MfxOBJECT_AUTOFUNC_CASE_8(obj, father, func, id) 
}

//内部 类型 - 类 - 函数 - 模板 - 宏
namespace __DeepSpace
{
	class MfxPORT MfxFactoryHand;
	MfxPORT MicroFlakeX::MfxReturn MfxRegisterObject(MicroFlakeX::MfxStrW object, MfxFactoryHand* hand);

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
		virtual MfxReturn AutoFunc(MfxStrW func...);
		virtual MfxReturn FuncName(MfxStrW* ret);
		virtual MfxReturn FuncInfor(MfxStrW* ret);
		virtual MfxReturn ObjectName(MfxStrW* ret);
		virtual MfxReturn ObjectFloor(UINT* ret);
	protected:
		UINT myFloor;
		CRITICAL_SECTION myCriticalSection;
	};

	class MfxLock
	{
	protected:
		CRITICAL_SECTION* myCriticalSection;
	public:
		MfxLock(MfxBase* object);
		~MfxLock();
	};
}

//内部 类声明
namespace __DeepSpace
{
	class MfxPORT MfxFactoryHand
	{
	public:
		MfxFactoryHand(MicroFlakeX::MfxStrW object);
		virtual MicroFlakeX::MfxReturn Creat(MicroFlakeX::MfxBase** ret) = 0;
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

}

#define __MfxFINE	0
#define __MfxFAIL	-1

#define __Mfx_OK(DR)	(((MfxReturn)(DR)) >= 0)
#define __Mfx_NO(DR)	(((MfxReturn)(DR)) < 0)

#define __MfxCODELOCK(obj) \
	MfxLock tLock(obj);

#define __MfxOBJECT \
public:\
	MfxReturn AutoFunc(MfxStrW setFunc...);\
	MfxReturn FuncName(MfxStrW* ret);\
	MfxReturn FuncInfor(MfxStrW* ret);\
	MfxReturn ObjectName(MfxStrW* ret);
	

#define __MfxOBJECT_INIT_0(obj) \
using namespace MicroFlakeX;\
using namespace __DeepSpace;\
using MicroFlakeX::obj;\
struct obj##MfxAutoFuncInfor\
{\
	int myID = 0;\
	std::wstring  myName;\
	std::wstring myAllName;\
};\
std::map<MfxStrW, obj##MfxAutoFuncInfor*> obj##MfxAutoFuncMap;\
typedef std::map<MfxStrW,obj##MfxAutoFuncInfor*>::value_type obj##MfxAutoFuncValue;\
typedef std::map<MfxStrW,obj##MfxAutoFuncInfor*>::iterator obj##MfxAutoFuncIterator;\
MfxReturn obj::FuncName(MfxStrW* ret)\
{\
	MfxCODELOCK(this);\
	*ret = L"";\
	for(auto i : obj##MfxAutoFuncMap)\
	{\
		*ret += i.second->myName;\
		*ret += L"\n";\
	}\
	return MfxFINE;\
}\
MfxReturn obj::FuncInfor(MfxStrW* ret)\
{\
	MfxCODELOCK(this);\
	*ret = L"";\
	for(auto i : obj##MfxAutoFuncMap)\
	{\
		*ret += i.second->myAllName;\
		*ret += L"\n";\
	}\
	return MfxFINE;\
}\
MfxReturn obj::ObjectName(MfxStrW* ret)\
{\
	MfxCODELOCK(this);\
	*ret = L#obj;\
	return MfxFINE;\
}\
class obj##FactoryHand\
	: public MfxFactoryHand\
{\
public:\
	obj##FactoryHand(MfxStrW object)\
		: MfxFactoryHand(object)\
	{\
		obj##MfxAutoFuncInfor* infor = nullptr;\
		WCHAR typeName[1024]; size_t n = 0;\
		MfxOBJECT_AUTOFUNC_REG(obj, AutoFunc, -1)

#define __MfxOBJECT_INIT_1(obj) \
	};\
	MfxReturn Creat(MfxBase** ret)\
	{\
		*ret = new obj;\
		return MfxFINE;\
	}\
};\
auto obj##Hand = new obj##FactoryHand(L#obj);\
MfxReturn obj::AutoFunc(MfxStrW setFunc...)\
{\
	MfxCODELOCK(this);\
	MfxReturn ret = MfxFAIL;\
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

#define __MfxOBJECT_INIT_2(obj, father) \
		case -1:\
		{\
			setFunc = va_arg(argc, MfxStrW);\
			argc = va_arg(argc, va_list);\
			goto BeginSwitch;\
			break;\
		}\
		}\
	}\
	else\
	{\
		ret = father::AutoFunc(L"AutoFunc", setFunc, argc); \
	}\
	return ret;\
}

#define __MfxOBJECT_AUTOFUNC_REG(obj, func, id) \
infor = new obj##MfxAutoFuncInfor;\
infor->myID = id;\
infor->myName = L#func;\
mbstowcs_s(&n, typeName, 1024,\
	typeid(&obj::func).name(), 1023);\
infor->myAllName = typeName;\
obj##MfxAutoFuncMap.insert(obj##MfxAutoFuncValue(L#func, infor));

#define __MfxOBJECT_AUTOFUNC_CASE_0(obj, father, func, id) \
case id:\
{\
	ret = father::AutoFunc(L#func);\
	if (Mfx_FAILED(ret)) { return MfxFAIL; };\
	ret = func();\
	break;\
}

#define __MfxOBJECT_AUTOFUNC_CASE_1(obj, father, func, id) \
case id:\
{\
	auto A1 = va_arg(argc, decltype(MfxArg1(&obj::func)));\
	ret = father::AutoFunc(L#func, A1);\
	if (Mfx_FAILED(ret)) { return MfxFAIL; };\
	ret = func(A1);\
	break;\
}

#define __MfxOBJECT_AUTOFUNC_CASE_2(obj, father, func, id) \
case id:\
{\
	auto A1 = va_arg(argc, decltype(MfxArg1(&obj::func)));\
	auto A2 = va_arg(argc, decltype(MfxArg2(&obj::func)));\
	ret = father::AutoFunc(L#func, A1, A2);\
	if (Mfx_FAILED(ret)) { return MfxFAIL; };\
	ret = func(A1, A2);\
	break;\
}

#define __MfxOBJECT_AUTOFUNC_CASE_3(obj, father, func, id) \
case id:\
{\
	auto A1 = va_arg(argc, decltype(MfxArg1(&obj::func)));\
	auto A2 = va_arg(argc, decltype(MfxArg2(&obj::func)));\
	auto A3 = va_arg(argc, decltype(MfxArg3(&obj::func)));\
	ret = father::AutoFunc(L#func, A1, A2, A3);\
	if (Mfx_FAILED(ret)) { return MfxFAIL; };\
	ret = func(A1, A2, A3);\
	break;\
}

#define __MfxOBJECT_AUTOFUNC_CASE_4(obj, father, func, id) \
case id:\
{\
	auto A1 = va_arg(argc, decltype(MfxArg1(&obj::func)));\
	auto A2 = va_arg(argc, decltype(MfxArg2(&obj::func)));\
	auto A3 = va_arg(argc, decltype(MfxArg3(&obj::func)));\
	auto A4 = va_arg(argc, decltype(MfxArg4(&obj::func)));\
	ret = father::AutoFunc(L#func, A1, A2, A3, A4);\
	if (Mfx_FAILED(ret)) { return MfxFAIL; };\
	ret = func(A1, A2, A3, A4);\
	break;\
}

#define __MfxOBJECT_AUTOFUNC_CASE_5(obj, father, func, id) \
case id:\
{\
	auto A1 = va_arg(argc, decltype(MfxArg1(&obj::func)));\
	auto A2 = va_arg(argc, decltype(MfxArg2(&obj::func)));\
	auto A3 = va_arg(argc, decltype(MfxArg3(&obj::func)));\
	auto A4 = va_arg(argc, decltype(MfxArg4(&obj::func)));\
	auto A5 = va_arg(argc, decltype(MfxArg5(&obj::func)));\
	ret = father::AutoFunc(L#func, A1, A2, A3, A4, A5);\
	if (Mfx_FAILED(ret)) { return MfxFAIL; };\
	ret = func(A1, A2, A3, A4, A5);\
	break;\
}

#define __MfxOBJECT_AUTOFUNC_CASE_6(obj, father, func, id) \
case id:\
{\
	auto A1 = va_arg(argc, decltype(MfxArg1(&obj::func)));\
	auto A2 = va_arg(argc, decltype(MfxArg2(&obj::func)));\
	auto A3 = va_arg(argc, decltype(MfxArg3(&obj::func)));\
	auto A4 = va_arg(argc, decltype(MfxArg4(&obj::func)));\
	auto A5 = va_arg(argc, decltype(MfxArg5(&obj::func)));\
	auto A6 = va_arg(argc, decltype(MfxArg6(&obj::func)));\
	ret = father::AutoFunc(L#func, A1, A2, A3, A4, A5, A6);\
	if (Mfx_FAILED(ret)) { return MfxFAIL; };\
	ret = func(A1, A2, A3, A4, A5, A6);\
	break;\
}

#define __MfxOBJECT_AUTOFUNC_CASE_7(obj, father, func, id) \
case id:\
{\
	auto A1 = va_arg(argc, decltype(MfxArg1(&obj::func)));\
	auto A2 = va_arg(argc, decltype(MfxArg2(&obj::func)));\
	auto A3 = va_arg(argc, decltype(MfxArg3(&obj::func)));\
	auto A4 = va_arg(argc, decltype(MfxArg4(&obj::func)));\
	auto A5 = va_arg(argc, decltype(MfxArg5(&obj::func)));\
	auto A6 = va_arg(argc, decltype(MfxArg6(&obj::func)));\
	auto A7 = va_arg(argc, decltype(MfxArg7(&obj::func)));\
	ret = father::AutoFunc(L#func, A1, A2, A3, A4, A5, A6, A7);\
	if (Mfx_FAILED(ret)) { return MfxFAIL; };\
	ret = func(A1, A2, A3, A4, A5, A6, A7);\
	break;\
}

#define __MfxOBJECT_AUTOFUNC_CASE_8(obj, father, func, id) \
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
	ret = father::AutoFunc(L#func, A1, A2, A3, A4, A5, A6, A7, A8);\
	if (Mfx_FAILED(ret)) { return MfxFAIL; };\
	ret = func(A1, A2, A3, A4, A5, A6, A7, A8);\
	break;\
}

