#pragma once

#ifdef MFX_MOUDULEDLL_BUILDING
#define MFX_MOUDULEDLL_IMPORT __declspec(dllexport)
#else
/* Windows 头文件 */
#include <windows.h>
/**/

/* 可变参数 - 类型获取 */
#include <stdarg.h>
#include <typeinfo>
#include <type_traits>
/**/

/* STL模板库 */
#include <map>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
/**/

/* GDIPLUS */
#include <gdiplus.h>
#pragma comment(lib,"gdiplus.lib")
/**/

/* Direct2D1 */
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <dwmapi.h>

#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "DWrite.lib")
/**/

/* 数学库 */
#include <cmath>
/**/

#define MFX_MOUDULEDLL_IMPORT __declspec(dllimport)
#endif

namespace MicroFlakeX
{
	class MFX_MOUDULEDLL_IMPORT MfxBasicObject;
	class MFX_MOUDULEDLL_IMPORT MfxCodeLock;
}

//Mfx基础
namespace MicroFlakeX
{
	typedef char ParaCount;
	typedef LRESULT MfxReturn;
	typedef std::wstring MfxStrW;
}

//Mfx容器
namespace MicroFlakeX
{
	typedef std::vector<MfxBasicObject*> MfxBasicObject_List;
	typedef MfxBasicObject_List::iterator MfxBasicObject_List_iterator;

	struct MfxAutoFunc_Value
	{
		MfxAutoFunc_Value(UINT id, unsigned char argc)
		{
			myID = id;
			myArgc = argc;
		}
		UINT myID;
		unsigned char myArgc;
	};

	typedef std::map<MfxStrW, MfxAutoFunc_Value*> MfxAutoFunc_Map;
	typedef MfxAutoFunc_Map::value_type MfxAutoFunc_Map_elem;
}

//Mfx枚举
namespace MicroFlakeX
{
	//MfxReturn
	enum MfxReturn_EN
	{
		MfxFine = 0x0000,
		MfxFail = -0x0001,
	};

	template<class Interface>
	inline void
		MfxComRelease(
			Interface** ppInterfaceToRelease
		)
	{
		if (*ppInterfaceToRelease != NULL)
		{
			(*ppInterfaceToRelease)->Release();

			(*ppInterfaceToRelease) = NULL;
		}
	}

#define MFXFAILED(mr)	__MFXFAILED(mr)
#define __MFXFAILED(mr)	(((MfxReturn)(mr)) < 0)

#define MFXSUCCEEDED(mr)	__MFXSUCCEEDED(mr)
#define __MFXSUCCEEDED(mr)	(((MfxReturn)(mr)) >= 0)
}

//Mfx基类
namespace MicroFlakeX
{
	template<typename Func>
	struct FuncParamNum_;
	template<typename Ret, class Class, typename... Args>
	struct FuncParamNum_<Ret(Class::*)(Args...)> { static const size_t value = sizeof...(Args); };
	template<typename Func>
	size_t GetFuncParamNum(Func) { return FuncParamNum_<Func>::value; };

	template <class Ret, class Class, class... Args>
	Ret MfxGetReturn(Ret(Class::*)(Args...)) { return Ret(); };
	template <class Ret, class Class, class P1, class... Args>
	P1 MfxGetParam1(Ret(Class::*)(P1, Args...)) { return P1(); };
	template <class Ret, class Class, class P1, class P2, class... Args>
	P2 MfxGetParam2(Ret(Class::*)(P1, P2, Args...)) { return P2(); };
	template <class Ret, class Class, class P1, class P2, class P3, class... Args>
	P3 MfxGetParam3(Ret(Class::*)(P1, P2, P3, Args...)) { return P3(); };
	template <class Ret, class Class, class P1, class P2, class P3, class P4, class... Args>
	P4 MfxGetParam4(Ret(Class::*)(P1, P2, P3, P4, Args...)) { return P4(); };
	template <class Ret, class Class, class P1, class P2, class P3, class P4, class P5, class... Args>
	P5 MfxGetParam5(Ret(Class::*)(P1, P2, P3, P4, P5, Args...)) { return P5(); };
	template <class Ret, class Class, class P1, class P2, class P3, class P4, class P5, class P6, class... Args>
	P6 MfxGetParam6(Ret(Class::*)(P1, P2, P3, P4, P5, P6, Args...)) { return P6(); };
	template <class Ret, class Class, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class... Args>
	P7 MfxGetParam7(Ret(Class::*)(P1, P2, P3, P4, P5, P6, P7, Args...)) { return P7(); };

#define BEGIN_INITDATA(Class) \
void Class::MfxInitBasicData()\
{

#define INITDATA(Class, FuncName, FuncId) \
myAutoFuncMap.insert(MfxAutoFunc_Map_elem(L#FuncName, \
	new MfxAutoFunc_Value(FuncId, \
		GetFuncParamNum(&Class::FuncName)\
		) \
	));

#define END_INITDATA \
}

#define BEGIN_AUTOMAP(Class) \
MicroFlakeX::MfxReturn MicroFlakeX::Class::GetName(MicroFlakeX::MfxStrW* ret)\
{\
	MFXLOCK;\
	(*ret) = L"Class";\
	return MfxFine;\
}\
MicroFlakeX::MfxReturn Class::AutoFunc(MicroFlakeX::MfxStrW funcName, ...)\
{\
auto t_Iter = myAutoFuncMap.find(funcName);\
if(t_Iter == myAutoFuncMap.end()) return MfxFail;\
va_list myParaList; \
va_start(myParaList, funcName); \
switch (t_Iter->second->myID)\
{\

#define CASE_FUNC_P0(Class, FuncName, FuncId) \
case FuncId:\
{\
	if (typeid(decltype(MfxGetReturn(&Class::FuncName))) == typeid(MfxReturn))\
	{\
		return FuncName(); \
	}\
	else\
	{\
		FuncName(); \
		return MfxFine; \
	}\
}

#define CASE_FUNC_P1(Class, FuncName, FuncId) \
case FuncId:\
{\
	auto P1 = va_arg(myParaList, decltype(MfxGetParam1(&Class::FuncName))); \
	if(typeid(decltype(MfxGetReturn(&Class::FuncName))) == typeid(MfxReturn))\
	{\
		return FuncName(P1); \
	}\
	else\
	{\
		FuncName(P1);\
		return MfxFine;\
	}\
}

#define CASE_FUNC_P2(Class, FuncName, FuncId) \
case FuncId:\
{\
	auto P1 = va_arg(myParaList, decltype(MfxGetParam1(&Class::FuncName))); \
	auto P2 = va_arg(myParaList, decltype(MfxGetParam2(&Class::FuncName))); \
	if(typeid(decltype(MfxGetReturn(&Class::FuncName))) == typeid(MfxReturn))\
	{\
		return FuncName(P1, P2);\
	}\
	else\
	{\
		FuncName(P1, P2);\
		return MfxFine;\
	}\
}

#define CASE_FUNC_P3(Class, FuncName, FuncId) \
case FuncId:\
{\
	auto P1 = va_arg(myParaList, decltype(MfxGetParam1(&Class::FuncName))); \
	auto P2 = va_arg(myParaList, decltype(MfxGetParam2(&Class::FuncName))); \
	auto P3 = va_arg(myParaList, decltype(MfxGetParam3(&Class::FuncName))); \
	if(typeid(decltype(MfxGetReturn(&Class::FuncName))) == typeid(MfxReturn))\
	{\
		return FuncName(P1, P2, P3);\
	}\
	else\
	{\
		FuncName(P1, P2, P3);\
		return MfxFine;\
	}\
}

#define CASE_FUNC_P4(Class, FuncName, FuncId) \
case FuncId:\
{\
	auto P1 = va_arg(myParaList, decltype(MfxGetParam1(&Class::FuncName))); \
	auto P2 = va_arg(myParaList, decltype(MfxGetParam2(&Class::FuncName))); \
	auto P3 = va_arg(myParaList, decltype(MfxGetParam3(&Class::FuncName))); \
	auto P4 = va_arg(myParaList, decltype(MfxGetParam4(&Class::FuncName))); \
	if(typeid(decltype(MfxGetReturn(&Class::FuncName))) == typeid(MfxReturn))\
	{\
		return FuncName(P1, P2, P3, P4);\
	}\
	else\
	{\
		FuncName(P1, P2, P3, P4);\
		return MfxFine;\
	}\
}

#define CASE_FUNC_P5(Class, FuncName, FuncId) \
case FuncId:\
{\
	auto P1 = va_arg(myParaList, decltype(MfxGetParam1(&Class::FuncName))); \
	auto P2 = va_arg(myParaList, decltype(MfxGetParam2(&Class::FuncName))); \
	auto P3 = va_arg(myParaList, decltype(MfxGetParam3(&Class::FuncName))); \
	auto P4 = va_arg(myParaList, decltype(MfxGetParam4(&Class::FuncName))); \
	auto P5 = va_arg(myParaList, decltype(MfxGetParam5(&Class::FuncName))); \
	if(typeid(decltype(MfxGetReturn(&Class::FuncName))) == typeid(MfxReturn))\
	{\
		return FuncName(P1, P2, P3, P4, P5);\
	}\
	else\
	{\
		FuncName(P1, P2, P3, P4, P5);\
		return MfxFine;\
	}\
}

#define END_AUTOMAP \
default:\
	{\
		return MfxFail;\
	}\
}\
}


#define DEFINE_AUTOBASIC \
protected:\
void MfxInitBasicData();\
public:\
MfxReturn AutoFunc(MfxStrW funcName, ...);\
MfxReturn GetName(MfxStrW* ret);

#define REALIZE_AUTOBASIC \
MfxInitBasicData();

	//反射基类 - Mfx都从这个类继承
	class MfxBasicObject
	{
	protected:
		friend class MfxCodeLock;
		CRITICAL_SECTION myCriticalSection;
		virtual void MfxInitBasicData();
	public:
		MfxBasicObject();
		virtual ~MfxBasicObject();
		virtual MfxReturn GetName(MfxStrW* ret);

	protected:
		MfxAutoFunc_Map myAutoFuncMap;
	public:
		virtual MfxReturn AutoFunc(MfxStrW funcName, ...);
		virtual MfxReturn GetAutoFuncName(MfxStrW& ret);
	};


#define MFXLOCK \
	MfxCodeLock t_CodeLock(this);

	//线程锁
	class MfxCodeLock
	{
	protected:
		CRITICAL_SECTION* myCriticalSection;
	public:
		MfxCodeLock(MfxBasicObject* object);
		~MfxCodeLock();
	};
}

//Mfx模板库
namespace MicroFlakeX
{
	//Mfx数据标签
	template<class DataType>
	class MfxDataFlag
		: public MfxBasicObject
	{
	public:
		MfxDataFlag()
		{
			MFXLOCK;
			myBeforData = myData = DataType();
			myChangeFlag = myUseFlag = 0;
		}
		~MfxDataFlag() { MFXLOCK; };
		DataType& GetData() { MFXLOCK; return myData; };
		DataType& GetBeforData() { MFXLOCK; return myBeforData; };
		void CleanUseFlag() { MFXLOCK; myUseFlag = 0; }
		void CleanChangeFlag() { MFXLOCK; myChangeFlag = 0; }
		UINT CheckUseFlag() { MFXLOCK; return myUseFlag; };
		UINT CheckChangeFlag() { MFXLOCK; return myChangeFlag; };
	protected:
		DataType myData;
		DataType myBeforData;
		UINT myUseFlag;
		UINT myChangeFlag;
	public:
		DataType operator-> () { MFXLOCK; myUseFlag++; return myData; };

		DataType& operator* () { MFXLOCK; myUseFlag++; return myData; };

		DataType operator= (DataType rhs)
		{
			MFXLOCK; 
			myChangeFlag++; 
			myBeforData = myData;
			myData = rhs; 
			return myData;
		};

		bool operator< (DataType rhs) { MFXLOCK; return myData < rhs; };

		bool operator> (DataType rhs) { MFXLOCK; return myData > rhs; };

		bool operator== (DataType rhs) { MFXLOCK; return myData == rhs; };

		bool operator!= (DataType rhs) { MFXLOCK; return myData != rhs; };
	};

	//Mfx智能指针

	//Mfx智能线程

}

namespace MicroFlakeX
{

}