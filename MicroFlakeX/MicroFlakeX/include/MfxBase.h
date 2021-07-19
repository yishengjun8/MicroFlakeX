#pragma once

namespace MicroFlakeX
{
#define MFXAPI _stdcall

	class MFX_DLL_EXPORT MfxBase;
	typedef MfxBase* pMfxBase;

#define MFX_OBJ_ENABLE_CLONE(ret) Clone(MfxBase** ret)
#define MFX_OBJ_ENABLE_REFLECTION __MFX_OBJ_ENABLE_REFLECTION
#define MFX_OBJ_ENABLE_FLOORCOMPARE __MFX_OBJ_ENABLE_FLOORCOMPARE

#define MFX_OBJ_REFLECTION_INIT_0(OBJ) __MFX_OBJ_REFLECTION_INIT_0(OBJ)
#define MFX_OBJ_REFLECTION_INIT_1(OBJ) __MFX_OBJ_REFLECTION_INIT_1(OBJ)
#define MFX_OBJ_REFLECTION_INIT_2(OBJ, FATHER_OBJ) __MFX_OBJ_REFLECTION_INIT_2(OBJ, FATHER_OBJ)

#define MFX_OBJ_REFLECTION_INIT(OBJ) __MFX_OBJ_REFLECTION_INIT_0(OBJ)
#define MFX_OBJ_REFLECTION_ENDINIT(OBJ, FATHER, ...) CONNECT(__MFX_OBJ_REFLECTION_ENDINIT, (OBJ, FATHER, __VA_ARGS__, END))
}

/***************************************************************
*	MfxReturn 预定义类型
****************************************************************/
namespace MicroFlakeX
{
	typedef INT32 MfxNum;
	typedef INT32 MfxFloor;
	typedef INT32 MfxReturn;

	typedef UINT64 MfxTime;
	typedef UINT32 MfxEvent;
	typedef UINT32 MfxMessage;

	typedef double MfxReal;

	typedef std::uint64_t MfxHash;

	typedef std::string MfxStringA;
	typedef std::wstring MfxStringW;

#define MFX_TXT_A(STR) STR
#define MFX_TXT_W(STR) L##STR

#define MFX_RET_SECCESS ((MicroFlakeX::MfxReturn)0)
#define MFX_RET_FAILED ((MicroFlakeX::MfxReturn)-1)
#define MFX_RET_NOTFIND ((MicroFlakeX::MfxReturn)1)
#define MFX_RET_UNKNOW ((MicroFlakeX::MfxReturn)2)
#define MFX_RET_WINACCEPT ((MicroFlakeX::MfxReturn)0)

#define MFX_SECCESS(MR) (((MicroFlakeX::MfxReturn)(MR)) == MFX_RET_SECCESS)
#define MFX_FAILED(MR) (((MicroFlakeX::MfxReturn)(MR)) == MFX_RET_FAILED)

#define MFX_NOTFIND(MR) (((MicroFlakeX::MfxReturn)(MR)) == MFX_RET_NOTFIND)
#define MFX_UNKNOW(MR) (((MicroFlakeX::MfxReturn)(MR)) == MFX_RET_UNKNOW)

#define MFX_IF_SECCESS(MR) if(MFX_SECCESS(MR))
#define MFX_IF_FAILED(MR) if(MFX_FAILED(MR))
#define MFX_IF_NOTFIND(MR) if(MFX_NOTFIND(MR))
#define MFX_IF_UNKNOW(MR) if(MFX_UNKNOW(MR))



	constexpr inline MfxHash MFXAPI MFX_STRING_HASH_A(char const* str, MfxHash hash = 0)
	{
		while (MfxHash ch = *str++)
		{
			hash = hash * 131 + ch;   // may be: 31、131、1313、13131、131313 ...
		}
		return hash;
	}

	constexpr inline MfxHash MFXAPI MFX_STRING_HASH_W(wchar_t const* str, MfxHash hash = 0)
	{
		while (MfxHash ch = *str++)
		{
			hash = hash * 131 + ch;   // may be: 31、131、1313、13131、131313 ...
		}
		return hash;
	}

	template<class Interface>
	inline bool MFXAPI SafeRelease(Interface*& pInterfaceToRelease)
	{
		if (pInterfaceToRelease != nullptr)
		{
			pInterfaceToRelease->Release();
			pInterfaceToRelease = nullptr;
			return true;
		}
		return false;
	}

	template<class Pointer>
	inline bool MFXAPI SafeDelete(Pointer*& pPointerToDelete)
	{
		if (pPointerToDelete != nullptr)
		{
			delete pPointerToDelete;
			pPointerToDelete = nullptr;
			return true;
		}
		return false;
	}

	template<class Pointer>
	inline bool MFXAPI SafeDeleteList(Pointer*& pPointerToDelete)
	{
		if (pPointerToDelete != nullptr)
		{
			delete[] pPointerToDelete;
			pPointerToDelete = nullptr;
			return true;
		}
		return false;
	}
}

namespace MicroFlakeX
{
	class MFX_DLL_EXPORT MfxParam;

#define MFX_CALLBACK_PARAM iParam

	//MFX回调函数指针
	typedef MfxReturn(*pCallBack)(MfxParam);
	typedef pCallBack pThreadFunc;

	/***************************************************************
	*	MicroFlakeX 回调函数辅助声明 - 返回值必须为MfxReturn
	*	例：MfxReturn MFX_CALLBACK(MyCallBackFunc);
	****************************************************************/
#define MFX_CALLBACK(funcName) funcName(MfxParam iParam)
#define MFX_REFLECTION(funcName) funcName(MfxParam iParam)

#define MFXPARAM_GET(param, type, place)  (std::any_cast<type&>(param[place]))
#define MFXPARAM_GET_SAFE(param, type, place)  (param.IsSafe(place) ? (std::any_cast<type&>(param[place])) : type())

#define MFXPARAM_GET_0(type) MFXPARAM_GET_SAFE(MFX_CALLBACK_PARAM, type, 0) 
#define MFXPARAM_GET_1(type) MFXPARAM_GET_SAFE(MFX_CALLBACK_PARAM, type, 1) 
#define MFXPARAM_GET_2(type) MFXPARAM_GET_SAFE(MFX_CALLBACK_PARAM, type, 2) 
#define MFXPARAM_GET_3(type) MFXPARAM_GET_SAFE(MFX_CALLBACK_PARAM, type, 3) 
#define MFXPARAM_GET_4(type) MFXPARAM_GET_SAFE(MFX_CALLBACK_PARAM, type, 4) 
#define MFXPARAM_GET_5(type) MFXPARAM_GET_SAFE(MFX_CALLBACK_PARAM, type, 5) 
#define MFXPARAM_GET_6(type) MFXPARAM_GET_SAFE(MFX_CALLBACK_PARAM, type, 6) 
#define MFXPARAM_GET_7(type) MFXPARAM_GET_SAFE(MFX_CALLBACK_PARAM, type, 7) 
#define MFXPARAM_GET_8(type) MFXPARAM_GET_SAFE(MFX_CALLBACK_PARAM, type, 8) 

	class MfxParam
	{
	private:
		static void* operator new(size_t);
		static void* operator new[](size_t);
	protected:
		PVOID* myPVOID;
		MfxMessage* myMessage;
		MfxStringA* myStringA;
		MfxStringW* myStringW;

		INT32* myUseCount;
		MfxReturn* myReturn;

		std::vector<std::any>* myParam;
	public:
		MfxParam();
		MfxParam(PVOID pvoid);
		MfxParam(MfxMessage msg);
		MfxParam(MfxStringA str);
		MfxParam(MfxStringW str);
		MfxParam(const MfxParam& rhs);
	protected:
		void Release();
	public:
		~MfxParam();

		std::any& operator [] (const int i);
		MfxParam& operator=(const MfxParam& rhs);

		bool IsSafe(const int i);

		MfxNum GetParamSize();

		bool IsPVOID();
		bool IsRETURN();
		bool IsMESSAGE();
		bool IsSTRINGA();
		bool IsSTRINGW();

		PVOID GetPVOID();
		MfxReturn GetRETURN();
		MfxMessage GetMESSAGE();
		MfxStringA GetSTRINGA();
		MfxStringW GetSTRINGW();

		MfxParam& SetPVOID(const PVOID set);
		MfxParam& SetRETURN(const MfxReturn set);
		MfxParam& SetMESSAGE(const MfxMessage set);
		MfxParam& SetSTRINGA(const MfxStringA set);
		MfxParam& SetSTRINGW(const MfxStringW set);

		template<class T>
		void push_back(T&& val)
		{
			myParam->push_back(std::forward<T>(val));
		}
	};


	class __MFX_EXTEND_PARAM_LIST
	{
	public:
		__MFX_EXTEND_PARAM_LIST(int argNum) { myNum = argNum - 1; };

		template<typename Arg>
		inline auto& EXTEND_PARAM_LIST(MfxParam& param) noexcept
		{
			return (std::any_cast<Arg&>)(param[myNum--]);
		}
	protected:
		MfxNum myNum;
	};

	template<typename ... Args>
	constexpr inline MfxParam MFX_MAKE_PARAM(Args&&... arg)
	{
		if constexpr (0 == sizeof...(Args))
		{
			return MfxParam();
		}
		else
		{
			return __MFX_MAKE_PARAM(MfxParam(), std::forward<Args>(arg)...);
		}
	}

	template<typename T, typename ... Args>
	constexpr inline MfxParam __MFX_MAKE_PARAM(MfxParam&& MFX_CALLBACK_PARAM, T&& set, Args&&... arg)
	{
		if constexpr (0 == sizeof...(Args))
		{
			MFX_CALLBACK_PARAM.push_back(std::forward<T>(set));
			return MFX_CALLBACK_PARAM;
		}
		else
		{
			MFX_CALLBACK_PARAM.push_back(std::forward<T>(set));
			return __MFX_MAKE_PARAM(std::move(MFX_CALLBACK_PARAM), std::forward<Args>(arg)...);
		}
	}

}


namespace MicroFlakeX
{
	class MFX_DLL_EXPORT MfxMemberLock;
	class MFX_DLL_EXPORT MfxFuncLock;

	/***************************************************************
	*	MfxMemberLock MFX参数锁。
	****************************************************************/
	class MfxMemberLock
	{
	protected:
		std::unordered_map<void*, CRITICAL_SECTION> myMutexResour;
		typedef std::unordered_map<void*, CRITICAL_SECTION>::value_type myResour;
	public:
		virtual ~MfxMemberLock();
		bool InsertMemberLock(void* resour);

	public:
		bool UnLock(void* first);
		bool TryLock(void* first);

	public:
		template<typename ...Args>
		inline bool UnLock(void* first, Args... rest)
		{
			return UnLock(first) ? UnLock(rest...) : false;
		}

		template<typename ...Args>
		inline bool WaitLock(Args... rest)
		{
			while (!TryLock(rest...));

			return true;
		}

		template<typename ...Args>
		inline bool TryLock(void* first, Args... rest)
		{
			bool ret = TryLock(first) == true ? TryLock(rest...) : false;

			if (ret == false)
			{
				LeaveCriticalSection(&myMutexResour[const_cast<void*>(first)]);
			}

			return ret;
		}
	};

	class MfxFuncLock
	{
	public:
		MfxFuncLock(MfxMemberLock* lock, PVOID pVoid)
		{
			myPVOID = pVoid;
			myMemberLock = lock;
			myMemberLock->WaitLock(myPVOID);
		};
		~MfxFuncLock()
		{
			myMemberLock->UnLock(myPVOID);
		}

	protected:
		PVOID myPVOID;
		MfxMemberLock* myMemberLock;
	};
}

/***************************************************************
*	MicroFlakeX 基类声明
****************************************************************/
namespace MicroFlakeX
{	
	/***************************************************************
	*	MicroFlakeX 工厂 - 通过字符串创建对象
	*	1、该子类必须声明了 MFX_OBJ_ENABLE_REFLECTION 宏
	*	2、该子类必须实现了 MFX_OBJ_REFLECTION_BEGININIT(OBJ) 和 MFX_OBJ_REFLECTION_ENDINIT(OBJ, FATHER)辅助宏
	****************************************************************/
	MFX_DLL_EXPORT MfxReturn MfxFactory(MfxStringW object, MfxBase** ret);
	MFX_DLL_EXPORT MfxBase* MfxFactory(MfxStringW object);




	class MfxBase
	{
	public:
		MfxBase();
		virtual ~MfxBase();
		virtual MfxReturn Clone(MfxBase** ret);
	public:
		virtual MfxBase& operator=(MfxBase& rhs);

	public:
		virtual bool operator==(MfxBase& rhs);

	public:
		virtual MfxReturn Reflection(MfxStringW recvFunc...);
		virtual MfxReturn GetObjectName(MfxStringW* ret);
	protected:
		MfxMemberLock myMemberLock;
	};
}

namespace MicroFlakeX
{
	/***************************************************************
	* 参数一：对象指针
	* 参数二：对象方法名字
	* 参数三：传递给对象方法的参数
	****************************************************************/
	MFX_DLL_EXPORT MfxReturn MfxBeginNewThread(MfxBase* object, MfxStringW recvFunc, MfxParam param);

	/***************************************************************
	* 参数一：回调函数指针
	* 参数二：传递给回调方法的MfxParam
	****************************************************************/
	MFX_DLL_EXPORT MfxReturn MfxBeginNewThread_Widely(pThreadFunc pThreadFunc, MfxParam param);

	/***************************************************************
	* 参数一：返回一个计时器ID
	* 参数二：回调对象指针
	* 参数三：回调对象方法名字
	* 参数四：传递给回调方法的MfxParam
	* 参数五：计时器每个多长时间调用一次，单位为ms，若为0，则调用一次结束
	* 参数六：计时器多久之后开始，单位为100纳秒，-1秒为立即开始。-1（秒） = -10000000（100纳秒）
	* 参数七：计时器每次开始的时候是否有微小的随机性，单位为ms。随机性指，在定时器每次调用的时候，随机提前或者延后几毫秒。
	****************************************************************/
	MFX_DLL_EXPORT MfxReturn MfxBeginNewTimer(PTP_TIMER& pTimer, MfxBase* object, MfxStringW recvFunc, MfxParam param, MfxTime delay = 0, LONGLONG begin = -10000000, MfxTime randTime = 0);

	/***************************************************************
	* 参数一：返回一个计时器ID
	* 参数二：回调函数指针
	* 参数三：传递给回调方法的MfxParam
	* 参数四：计时器每个多长时间调用一次，单位为ms，若为0，则调用一次结束
	* 参数五：计时器多久之后开始，单位为100纳秒，-1秒为立即开始。-1（秒） = -10000000（100纳秒）
	* 参数六：计时器每次开始的时候是否有微小的随机性，单位为ms。随机性指，在定时器每次调用的时候，随机提前或者延后几毫秒。
	****************************************************************/
	MFX_DLL_EXPORT MfxReturn MfxBeginNewTimer_Widely(PTP_TIMER& pTimer, pThreadFunc pThreadFunc, MfxParam param, MfxTime delay = 0, LONGLONG begin = -10000000, MfxTime randTime = 0);

	/***************************************************************
	* 参数一：计时器ID，根据ID删除对应的计时器
	****************************************************************/
	MFX_DLL_EXPORT MfxReturn MfxCloseTimer(PTP_TIMER& pTimer);
}

namespace MicroFlakeX
{
	class MFX_DLL_EXPORT MfxSignal;
	class MFX_DLL_EXPORT MfxClient;

	/***************************************************************
	*	MicroFlakeX信号槽
	*	可以一对多的发送指定信号到指定对象
	****************************************************************/
	class MfxSignal
	{
	private:
		static std::vector<MfxSignal*> MfxSignal_Vector;
	protected:
		struct MfxReceiver_Info
		{
			MfxReceiver_Info(MfxBase* recvObject, MfxStringW recvFunc)
			{
				this->recvFunc = recvFunc;
				this->recvObject = recvObject;
			}
			MfxStringW recvFunc;
			MfxBase* recvObject;
		};

		std::deque<MfxReceiver_Info> myReceiver;

	public:
		MfxSignal();
		MfxSignal(const MfxSignal& rhs);
		static void ReceiverDelete(MfxBase* recvObject);
		virtual ~MfxSignal();

		void RemoveReceiver(MfxBase* recvObject);
		void RemoveReceiver(MfxBase* recvObject, MfxStringW recvFunc);
		void PushBackReceiver(MfxBase* recvObject, MfxStringW recvFunc);
		void PushFrontReceiver(MfxBase* recvObject, MfxStringW recvFunc);


	public:
		template<typename ... Args>
		void SendSignal(Args&&... arg)
		{
			for (auto& iter : myReceiver)
			{
				iter.recvObject->Reflection(iter.recvFunc, std::forward<Args>(arg)...);
			}
		}

		template<typename ... Args>
		void PostSignal(Args&&... arg)
		{
			MfxBeginNewThread_Widely(&(MfxSignal::SignalCall_Thread<Args...>), MFX_MAKE_PARAM(std::forward<Args>(arg)...).SetPVOID(this));
		}

	private:
		template<typename ... Args>
		static void SignalCall(MfxBase* set, MfxStringW& recv, MfxParam& param)
		{
			__MFX_EXTEND_PARAM_LIST exParam(param.GetParamSize());
			set->Reflection(recv, exParam.EXTEND_PARAM_LIST<Args>(param)...);
		}

	private:
		template<typename ... Args>
		static MfxReturn MFX_CALLBACK(SignalCall_Thread)
		{
			MfxSignal* tThis = (MfxSignal*)MFX_CALLBACK_PARAM.GetPVOID();
			for (auto& iter : tThis->myReceiver)
			{
				SignalCall<Args...>(iter.recvObject, iter.recvFunc, MFX_CALLBACK_PARAM);
			}
			return MFX_RET_SECCESS;
		}
	};

	class MfxClient
	{
	private:
		static std::vector<MfxClient*> MfxClient_Vector;
	protected:
		std::deque<MfxBase*> myReceiver;

	public:
		MfxClient();
		MfxClient(const MfxClient& rhs);
		static void ReceiverDelete(MfxBase* recvObject);
		virtual ~MfxClient();

		void RemoveReceiver(MfxBase* recvObject);
		void PushBackReceiver(MfxBase* recvObject);
		void PushFrontReceiver(MfxBase* recvObject);
	public:
		template<typename ... Args>
		void SendClient(MfxStringW recvFunc, Args&&... arg)
		{
			for (auto& iter : myReceiver)
			{
				iter->Reflection(recvFunc, std::forward<Args>(arg)...);
			}
		}

		template<typename ... Args>
		void PostClient(MfxStringW recvFunc, Args&&... arg)
		{
			MfxBeginNewThread_Widely(&(MfxClient::ClientCall_Thread<Args...>), MFX_MAKE_PARAM(std::forward<Args>(arg)...).SetPVOID(this).SetSTRINGW(recvFunc));
		}

	private:
		template<typename ... Args>
		static void ClientCall(MfxBase* set, MfxParam& param)
		{
			__MFX_EXTEND_PARAM_LIST exParam(param.GetParamSize());
			set->Reflection(param.GetSTRINGW(), exParam.EXTEND_PARAM_LIST<Args>(param)...);
		}

	private:
		template<typename ... Args>
		static MfxReturn MFX_CALLBACK(ClientCall_Thread)
		{
			MfxClient* tThis = (MfxClient*)MFX_CALLBACK_PARAM.GetPVOID();
			for (auto& iter : tThis->myReceiver)
			{
				ClientCall<Args...>(iter, MFX_CALLBACK_PARAM);
			}
			return MFX_RET_SECCESS;
		}
	};
}

/***************************************************************
*	MicroFlakeX内部函数
*	>>	一般情况下这里的函数不需要额外的关注
****************************************************************/
namespace MicroFlakeX
{	
	MFX_DLL_EXPORT VOID CALLBACK __MfxThreadCallBack(PTP_CALLBACK_INSTANCE instance, PVOID val);
	MFX_DLL_EXPORT VOID CALLBACK __MfxThreadCallBack_Widely(PTP_CALLBACK_INSTANCE instance, PVOID val);

	MFX_DLL_EXPORT VOID CALLBACK __MfxTimerCallBack(PTP_CALLBACK_INSTANCE instance, PVOID val, PTP_TIMER pTimer);
	MFX_DLL_EXPORT VOID CALLBACK __MfxTimerCallBack_Widely(PTP_CALLBACK_INSTANCE instance, PVOID val, PTP_TIMER pTimer);

	class MFX_DLL_EXPORT __MfxFactoryHand
	{
		friend MfxBase* MicroFlakeX::MfxFactory(MfxStringW object);
		friend MfxReturn MicroFlakeX::MfxFactory(MfxStringW object, MfxBase** ret);
	public:
		__MfxFactoryHand(MfxStringW object);
		virtual MfxReturn Creat(MicroFlakeX::MfxBase** ret) = 0;
		virtual ~__MfxFactoryHand();
	public:
		MfxReturn RemoveObject(MfxStringW object);
		MfxReturn RegisterObject(MfxStringW object, __MfxFactoryHand* hand);

	private:
		MfxStringW myObjectName;
		static std::unordered_map<MfxStringW, __MfxFactoryHand*> __MfxFactoryHand_Map;
	};

	template<class T>
	inline auto& __MFX_EXTEND_VA_LIST(va_list& argc)
	{
		return (*(typename std::decay<T>::type*)(argc -= _INTSIZEOF(T)));
	}

	template <typename T_THIS, typename OBJ, class... Args>
	constexpr inline MicroFlakeX::MfxReturn __MFX_REFLECTION_FUNC_EXTEND(T_THIS pThis, va_list argc, MfxReturn(OBJ::* pFunc)(Args...))
	{
		if constexpr (sizeof...(Args) == 0)
		{
			return (pThis->*pFunc)();
		}
		else
		{
			va_list r_argc = argc + (sizeof(Args) + ...);
			return (pThis->*pFunc)(std::move(__MFX_EXTEND_VA_LIST<Args>(r_argc))...);
		}
	};

	template <typename T_THIS, typename OBJ, class... Args>
	constexpr inline MicroFlakeX::MfxReturn __MFX_REFLECTION_FUNC_EXTEND(T_THIS pThis, va_list argc, MfxReturn(OBJ::* pFunc)(Args...) const)
	{
		if constexpr (sizeof...(Args) == 0)
		{
			return (pThis->*pFunc)();
		}
		else
		{
			va_list r_argc = argc + (sizeof(Args) + ...);
			return (pThis->*pFunc)(std::move(__MFX_EXTEND_VA_LIST<Args>(r_argc))...);
		}
	};


	template<class lhsT, class rhsT = lhsT>
	inline bool MFXAPI pFloorCompare(lhsT* lhs, rhsT* rhs)
	{
		return lhs->myFloor < rhs->myFloor;
	}

	template<class lhsT, class rhsT = lhsT>
	inline bool MFXAPI FloorCompare(lhsT& lhs, rhsT& rhs)
	{
		return lhs.myFloor < rhs.myFloor;
	}
}

#define __MFX_OBJ_ENABLE_REFLECTION \
public:\
	MfxReturn Reflection(MfxStringW recvFunc...);\
	MfxReturn GetObjectName(MfxStringW* ret);

#define __MFX_OBJ_ENABLE_FLOORCOMPARE\
	template<class lhsT, class rhsT>\
	friend bool MFXAPI pFloorCompare(lhsT* lhs, rhsT* rhs);\
	template<class lhsT, class rhsT>\
	friend bool MFXAPI FloorCompare(lhsT& lhs, rhsT& rhs);


#define __MFX_OBJ_REFLECTIONFUNC_CASE_EX(OBJ, AUTO_FUNC)\
	case MFX_STRING_HASH_W(MFX_TXT_W(#AUTO_FUNC)):\
	{\
		ret = __MFX_REFLECTION_FUNC_EXTEND(this, argc, &OBJ::AUTO_FUNC);\
		va_end(argc); \
		return ret; \
	}

/****************************************************************************************************************/
#define __MFX_OBJ_REFLECTION_INIT_0(OBJ)\
using namespace MicroFlakeX;\
using namespace MicroFlakeX;\
MfxReturn OBJ::GetObjectName(MfxStringW* ret)\
{\
	*ret = MFX_TXT_W(#OBJ);\
	return MFX_RET_SECCESS;\
}\
\
class OBJ##FactoryHand\
	: public __MfxFactoryHand\
{\
public:\
	OBJ##FactoryHand(MfxStringW object)\
		: __MfxFactoryHand(object)\
	{

/****************************************************************************************************************/
#define __MFX_OBJ_REFLECTION_INIT_1(OBJ) \
	}\
	MfxReturn Creat(MfxBase** ret)\
	{\
		*ret = new OBJ;\
		return MFX_RET_SECCESS;\
	}\
};\
OBJ##FactoryHand OBJ##Hand(MFX_TXT_W(#OBJ));\
MfxReturn OBJ::Reflection(MfxStringW recvFunc...)\
{\
	MfxReturn ret = MFX_RET_NOTFIND;\
	va_list argc;\
	va_start(argc, recvFunc);\
	BeginSwitch:\
	switch (MFX_STRING_HASH_W(recvFunc.c_str()))\
	{

/****************************************************************************************************************/
#define __MFX_OBJ_REFLECTION_INIT_2(OBJ, FATHER_OBJ) \
		case MFX_STRING_HASH_W(MFX_TXT_W("Reflection")):\
		{\
			recvFunc = va_arg(argc, MfxStringW);\
			goto BeginSwitch;\
		}\
		case MFX_STRING_HASH_W(MFX_TXT_W("REFLECTION_FUNC_NOT_FIND")):\
		{\
			recvFunc = va_arg(argc, MfxStringW);\
			argc = va_arg(argc, va_list);\
			goto BeginSwitch;\
		}\
		default:\
		{\
			ret = FATHER_OBJ::Reflection(MFX_TXT_W("REFLECTION_FUNC_NOT_FIND"), recvFunc, argc); \
			va_end(argc);\
			return ret;\
		}\
	}\
}


#define __MFX_OBJ_REFLECTION_ENDINIT(OBJ, FATHER_OBJ, ...) \
	__MFX_OBJ_REFLECTION_INIT_1(OBJ)\
	CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_0(OBJ, __VA_ARGS__));\
	__MFX_OBJ_REFLECTION_INIT_2(OBJ, FATHER_OBJ);


#define CONNECT(A, B) A##B
#define CCONNECT(A, B) CONNECT(A, B)
#define CCCONNECT(A, B) CCONNECT(A, B)
#define CCCCONNECT(A, B) CCCONNECT(A, B)
#define CCCCCONNECT(A, B) CCCCONNECT(A, B)

#define ARGS_NUM_(N1, N2, N3, N4, N5, N6, N7, N8, N9, N10, N11, N12, N13, N14, N15, N16, \
N17, N18, N19, N20, N21, N22, N23, N24, N25, N26, N27, N28, N29, N30, N31, N32, \
N33, N34, N35, N36, N37, N38, N39, N40, N41, N42, N43, N44, N45, N46, N47, N48, \
N49, N50, N51, N52, N53, N54, N55, N56, N57, N58, N59, N60, N61, N62, N63, N64, \
N65, N66, N67, N68, N69, N70, N71, N72, N73, N74, N75, N76, N77, N78, N79, N80, \
N81, N82, N83, N84, N85, N86, N87, N88, N89, N90, N91, N92, N93, N94, N95, N96, \
N97, N98, N99, N100, N101, N102, N103, N104, N105, N106, N107, N108, N109, N110, N111, ...) N111

#define GET_ARGS_NUM(...) CONNECT(ARGS_NUM_, (__VA_ARGS__, \
110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100, 99, 98, 97, 96, 95, \
94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, \
78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, \
62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, \
46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, \
30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, \
14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1))


#define __MFX_IS_END_ 0,0
#define __MFX_IS_END_END 0,0,0
#define __MFX_IS_END(SYMBOL) GET_ARGS_NUM(__MFX_IS_END_##SYMBOL)

//const int ATEST = __MFX_IS_END(END); //3
//const int BTEST = __MFX_IS_END(pFunc); //1
//const int CTEST = __MFX_IS_END(); //2

#define __MFX_OBJ_REFLECTIONFUNC_CASE_1(OBJ, FUNC_1) __MFX_OBJ_REFLECTIONFUNC_CASE_EX(OBJ, FUNC_1)
#define __MFX_OBJ_REFLECTIONFUNC_CASE_2(...)
#define __MFX_OBJ_REFLECTIONFUNC_CASE_3(...)

#define MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1) \
	CCCONNECT(__MFX_OBJ_REFLECTIONFUNC_CASE_, __MFX_IS_END(FUNC_1))(OBJ, FUNC_1)

namespace
{
#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_0(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_1(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_1(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_2(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_2(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_3(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_3(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_4(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_4(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_5(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_5(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_6(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_6(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_7(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_7(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_8(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_8(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_9(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_9(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_10(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_10(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_11(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_11(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_12(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_12(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_13(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_13(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_14(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_14(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_15(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_15(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_16(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_16(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_17(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_17(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_18(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_18(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_19(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_19(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_20(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_20(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_21(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_21(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_22(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_22(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_23(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_23(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_24(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_24(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_25(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_25(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_26(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_26(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_27(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_27(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_28(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_28(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_29(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_29(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_30(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_30(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_31(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_31(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_32(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_32(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_33(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_33(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_34(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_34(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_35(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_35(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_36(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_36(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_37(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_37(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_38(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_38(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_39(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_39(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_40(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_40(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_41(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_41(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_42(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_42(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_43(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_43(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_44(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_44(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_45(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_45(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_46(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_46(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_47(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_47(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_48(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_48(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_49(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_49(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_50(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_50(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_51(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_51(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_52(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_52(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_53(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_53(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_54(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_54(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_55(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_55(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_56(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_56(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_57(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_57(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_58(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_58(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_59(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_59(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_60(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_60(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_61(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_61(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_62(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_62(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_63(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_63(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_64(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_64(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_65(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_65(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_66(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_66(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_67(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_67(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_68(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_68(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_69(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_69(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_70(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_70(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_71(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_71(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_72(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_72(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_73(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_73(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_74(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_74(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_75(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_75(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_76(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_76(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_77(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_77(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_78(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_78(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_79(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_79(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_80(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_80(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_81(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_81(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_82(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_82(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_83(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_83(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_84(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_84(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_85(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_85(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_86(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_86(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_87(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_87(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_88(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_88(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_89(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_89(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_90(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_90(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_91(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_91(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_92(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_92(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_93(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_93(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_94(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_94(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_95(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_95(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_96(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_96(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_97(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_97(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_98(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_98(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_99(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_99(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_100(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_100(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_101(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_101(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_102(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_102(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_103(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_103(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_104(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_104(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_105(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_105(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_106(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_106(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_107(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_107(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_108(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_108(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_109(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_109(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_110(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_110(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_111(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_111(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_112(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_112(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_113(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_113(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_114(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_114(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_115(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_115(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_116(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_116(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_117(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_117(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_118(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_118(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_119(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_119(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFX_OBJ_REFLECTIONFUNC_SPREADCASE_120(OBJ, __VA_ARGS__))

#define __MFX_OBJ_REFLECTIONFUNC_SPREADCASE_120(OBJ, FUNC_1, FUNC_2, ...)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFX_OBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)

}

/*
	&&OBJ&&;\
	&&FUNC_1&&;\
	&&FUNC_2&&;\
*/


/***************************************************************
*	由于设计问题，暂时废弃的区域
****************************************************************/
namespace
{
	/***************************************************************
	*	MfxDataFlag	可以记录变量被更改的次数以及被使用的次数
	*	由于设计问题，暂时废弃。请等待后续维护更新
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