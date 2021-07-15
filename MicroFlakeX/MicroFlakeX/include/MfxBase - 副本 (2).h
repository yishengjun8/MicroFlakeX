#pragma once

namespace MicroFlakeX
{
	class MFX_PORT MfxBase;
	typedef MfxBase* pMfxBase;

#define MFXOBJ_ENABLE_REFLECTION __MFXOBJ_ENABLE_REFLECTION

#define MFXOBJ_REFLECTION_INIT_0(OBJ) __MFXOBJ_REFLECTION_INIT_0(OBJ)
#define MFXOBJ_REFLECTION_INIT_1(OBJ) __MFXOBJ_REFLECTION_INIT_1(OBJ)
#define MFXOBJ_REFLECTION_INIT_2(OBJ, FATHER_OBJ) __MFXOBJ_REFLECTION_INIT_2(OBJ, FATHER_OBJ)

#define MFXOBJ_REFLECTION_INIT(OBJ) __MFXOBJ_REFLECTION_INIT_0(OBJ)
#define MFXOBJ_REFLECTION_ENDINIT(OBJ, FATHER, ...) CONNECT(__MFXOBJ_REFLECTION_ENDINIT, (OBJ, FATHER, __VA_ARGS__, END))
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

#define MfxReturn_Seccess ((MfxReturn)0)
#define MfxReturn_Failed ((MfxReturn)-1)
#define MfxReturn_NotFind ((MfxReturn)1)
#define MfxReturn_Unknow ((MfxReturn)2)
#define MfxReturn_WinAccept ((MfxReturn)0)

#define MFX_SECCESS(MR) (((MfxReturn)(MR)) == MfxReturn_Seccess)
#define MFX_FAILED(MR) (((MfxReturn)(MR)) == MfxReturn_Failed)

#define MFX_NOTFIND(MR) (((MfxReturn)(MR)) == MfxReturn_NotFind)
#define MFX_UNKNOW(MR) (((MfxReturn)(MR)) == MfxReturn_Unknow)

#define MFX_IF_SECCESS(MR) if(MFX_SECCESS(MR))
#define MFX_IF_FAILED(MR) if(MFX_FAILED(MR))
#define MFX_IF_NOTFIND(MR) if(MFX_NOTFIND(MR))
#define MFX_IF_UNKNOW(MR) if(MFX_UNKNOW(MR))


#define MfxString __MfxString
#define MfxText(str) __MfxText(str)
#define MfxStrHash(str) __MfxStrHash(str)

#ifdef UNICODE
#define __MfxCout std::wcout
#define __MfxText(str) L##str
#define __MfxString std::wstring
#define __MfxStrHash(str) MfxGetHash_StrW(str)

#elif 
#define __MfxCout std::cout
#define __MfxText(str) str
#define __MfxString std::string;
#define __MfxStrHash(str) MfxGetHash_StrA(MfxText(str))
#endif

	template<class lhsT, class rhsT = lhsT>
	bool pFloorCompare(lhsT* lhs, rhsT* rhs)
	{
		return lhs->myFloor < rhs->myFloor;
	}

	template<class lhsT, class rhsT = lhsT>
	bool FloorCompare(lhsT& lhs, rhsT& rhs)
	{
		return lhs.myFloor < rhs.myFloor;
	}

#define MFXOBJ_ENABLE_FLOORCOMPARE\
	template<class lhsT, class rhsT>\
	friend bool pFloorCompare(lhsT* lhs, rhsT* rhs);\
	template<class lhsT, class rhsT>\
	friend bool FloorCompare(lhsT& lhs, rhsT& rhs);

	constexpr MfxHash MfxGetHash_StrA(char const* str)
	{
		MfxHash hash = 0;
		while (MfxHash ch = *str++)
		{
			hash = hash * 131 + ch;   // may be: 31、131、1313、13131、131313 ...
		}
		return hash;
	}

	constexpr MfxHash MfxGetHash_StrW(wchar_t const* str)
	{
		MfxHash hash = 0;
		while (MfxHash ch = *str++)
		{
			hash = hash * 131 + ch;   // may be: 31、131、1313、13131、131313 ...
		}
		return hash;
	}

	template<class Interface>
	inline bool SafeRelease(Interface*& pInterfaceToRelease)
	{
		if (pInterfaceToRelease != nullptr)
		{
			pInterfaceToRelease->Release();
			pInterfaceToRelease = nullptr;
			return 1;
		}
		return 0;
	}

	template<class Pointer>
	inline bool SafeDelete(Pointer*& pPointerToDelete)
	{
		if (pPointerToDelete != nullptr)
		{
			delete pPointerToDelete;
			pPointerToDelete = nullptr;
			return 1;
		}
		return 0;
	}

	template<class Pointer>
	inline bool SafeDeleteL(Pointer*& pPointerToDelete)
	{
		if (pPointerToDelete != nullptr)
		{
			delete[] pPointerToDelete;
			pPointerToDelete = nullptr;
			return 1;
		}
		return 0;
	}
}

namespace MicroFlakeX
{
	typedef std::set<MfxBase*> MfxBase_Set;
	typedef std::queue<MfxBase*> MfxBase_Queue;
	typedef std::deque<MfxBase*> MfxBase_Deque;
	typedef std::stack<MfxBase*> MfxBase_Stack;
	typedef std::vector<MfxBase*> MfxBase_Vector;

	/***************************************************************
	*	MicroFlakeX 回调函数辅助声明 - 返回值必须为MfxReturn
	*	例：MfxReturn MFX_CALLBACK(MyCallBackFunc);
	****************************************************************/
#define MFX_CALLBACK(funcName) funcName(MfxParam iParam)
#define MFX_REFLECTION(funcName) funcName(MfxParam iParam)

#define MFX_CALLBACK_PARAM iParam
}


/***************************************************************
*	MicroFlakeX	辅助框架
****************************************************************/
namespace MicroFlakeX
{
	class MFX_PORT MfxParam;
	class MFX_PORT MfxMemberLock;
	class MFX_PORT MfxCriticalLock;

	typedef MfxMemberLock* pMfxMemberLock;

	class MfxCriticalLock
	{
	private:
		static void* operator new(size_t);
		static void* operator new[](size_t);
	public:
		MfxCriticalLock(CRITICAL_SECTION* set);
		~MfxCriticalLock();
	protected:
		CRITICAL_SECTION* myCriticalSection;
	};

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

		INT32* myUseCount;
		MfxReturn* myReturn;

		std::vector<std::any>* myParam;
	public:
		MfxParam();
		MfxParam(PVOID pvoid);
		MfxParam(MfxMessage msg);
		MfxParam(const MfxParam& rhs);
		~MfxParam();

		std::any& operator [] (const int i);
		MfxParam& operator=(const MfxParam& rhs);

		bool IsSafe(const int i);

		MfxNum GetParamSize();

		PVOID GetPVOID();
		MfxReturn GetRETURN();
		MfxMessage GetMESSAGE();

		MfxParam& SetPVOID(PVOID set);
		MfxParam& SetRETURN(MfxReturn set);
		MfxParam& SetMESSAGE(MfxMessage set);

		template<class T>
		void push_back(T&& val)
		{
			myParam->push_back(std::forward<T>(val));
		}
	};

	inline MfxParam MFX_MAKE_PARAM()
	{
		MfxParam MFX_CALLBACK_PARAM;
		return MFX_CALLBACK_PARAM;
	}

	template<typename ... Args>
	constexpr inline MfxParam MFX_MAKE_PARAM(Args&&... arg)
	{
		MfxParam MFX_CALLBACK_PARAM;
		return __MFX_MAKE_PARAM(MFX_CALLBACK_PARAM, std::forward<Args>(arg)...);
	}

	template<typename T, typename ... Args>
	constexpr inline MfxParam __MFX_MAKE_PARAM(MfxParam& MFX_CALLBACK_PARAM, T&& set, Args&&... arg)
	{
		MFX_CALLBACK_PARAM.push_back(std::forward<T>(set));
		return __MFX_MAKE_PARAM(MFX_CALLBACK_PARAM, std::forward<Args>(arg)...);
	}

	template<typename T, typename ... Args>
	constexpr inline MfxParam __MFX_MAKE_PARAM(MfxParam& MFX_CALLBACK_PARAM, T&& set)
	{
		MFX_CALLBACK_PARAM.push_back(std::forward<T>(set));
		return MFX_CALLBACK_PARAM;
	}


}


namespace MicroFlakeX
{
	/***************************************************************
	*	MfxMemberLock Mfx参数锁。
	****************************************************************/
	class MfxMemberLock
	{
	protected:
		std::unordered_map<void*, CRITICAL_SECTION> myMutexResour;
		typedef std::unordered_map<void*, CRITICAL_SECTION>::value_type myResour;
	public:
		virtual ~MfxMemberLock();
		void InsertMemberLock(void* resour);

	public:
		void UnLock(void* first);
		void WaitLock(void* first);

		bool TryLock(void* first);

		template<typename ...Args>
		void UnLock(void* first, Args... rest)
		{
			auto tFind = myMutexResour.find(const_cast<void*>(first));
			if (tFind == myMutexResour.end())
			{
				InsertMemberLock(const_cast<void*>(first));
			}
			else
			{
				LeaveCriticalSection(&myMutexResour[const_cast<void*>(first)]);
			}

			UnLock(rest...);
		}

		template<typename ...Args>
		void TryWaitLock(Args... rest)
		{
			while (!TryLock(rest...));
		}

		template<typename ...Args>
		bool TryLock(void* first, Args... rest)
		{
			bool ret = false;
			auto tFind = myMutexResour.find(const_cast<void*>(first));
			if (tFind == myMutexResour.end())
			{
				InsertMemberLock(const_cast<void*>(first));
				ret = TryEnterCriticalSection(&myMutexResour[const_cast<void*>(first)]);
			}
			else
			{
				ret = TryEnterCriticalSection(&tFind->second);
			}

			if (ret == true)
			{
				ret = TryLock(rest...);

				if (ret)
				{
					return true;
				}
				else
				{
					LeaveCriticalSection(&myMutexResour[const_cast<void*>(first)]);
					return false;
				}
			}
			else
			{
				return false;
			}
		}
	};
}













/***************************************************************
*	MicroFlakeX 基类声明
****************************************************************/
namespace MicroFlakeX
{
	class MfxBase
	{
		friend class MfxCriticalLock;
	public:
		MfxBase();
		virtual ~MfxBase();
		virtual MfxReturn Clone(MfxBase** ret) const;
	public:
		virtual MfxBase& operator=(MfxBase& rhs);

	public:
		virtual bool operator==(MfxBase& rhs);

	public:
		virtual MfxReturn Reflection(MfxString recvFunc...);
		virtual MfxReturn GetObjectName(MfxString* ret);
	protected:
		MfxMemberLock myMemberLock;
	private:
		CRITICAL_SECTION myCriticalSection;
	};
}










namespace MicroFlakeX
{
	/***************************************************************
	*	MicroFlakeX 线程回调指针格式
	****************************************************************/
	typedef MfxReturn(*pThreadFunc)(MfxParam);

	/***************************************************************
	* 异步线程请勿传入局部变量指针。
	* 参数一：回调对象指针
	* 参数二：回调对象方法名字
	* 参数三：传递给回调方法的MfxParam。
	****************************************************************/
	MFX_PORT MfxReturn MfxBeginNewThread(MfxBase* object, MfxString recvFunc, MfxParam param);

	/***************************************************************
	* 参数一：回调函数指针
	* 参数二：传递给回调方法的MfxParam
	****************************************************************/
	MFX_PORT MfxReturn MfxBeginNewThread_Widely(pThreadFunc pThreadFunc, MfxParam param);

	/***************************************************************
	* 参数一：返回一个计时器ID
	* 参数二：回调对象指针
	* 参数三：回调对象方法名字
	* 参数四：传递给回调方法的MfxParam
	* 参数五：计时器每个多长时间调用一次，单位为ms，若为0，则调用一次结束
	* 参数六：计时器多久之后开始，单位为100纳秒，-1秒为立即开始。-1（秒） = -10000000（100纳秒）
	* 参数七：计时器每次开始的时候是否有微小的随机性，单位为ms。随机性指，在定时器每次调用的时候，随机提前或者延后几毫秒。
	****************************************************************/
	MFX_PORT MfxReturn MfxBeginNewTimer(PTP_TIMER& pTimer, MfxBase* object, MfxString recvFunc, MfxParam param, MfxTime delay = 0, LONGLONG begin = -10000000, MfxTime randTime = 0);

	/***************************************************************
	* 参数一：返回一个计时器ID
	* 参数二：回调函数指针
	* 参数三：传递给回调方法的MfxParam
	* 参数四：计时器每个多长时间调用一次，单位为ms，若为0，则调用一次结束
	* 参数五：计时器多久之后开始，单位为100纳秒，-1秒为立即开始。-1（秒） = -10000000（100纳秒）
	* 参数六：计时器每次开始的时候是否有微小的随机性，单位为ms。随机性指，在定时器每次调用的时候，随机提前或者延后几毫秒。
	****************************************************************/
	MFX_PORT MfxReturn MfxBeginNewTimer_Widely(PTP_TIMER& pTimer, pThreadFunc pThreadFunc, MfxParam param, MfxTime delay = 0, LONGLONG begin = -10000000, MfxTime randTime = 0);

	/***************************************************************
	* 参数一：计时器ID，根据id删除对应的计时器
	****************************************************************/
	MFX_PORT MfxReturn MfxCloseTimer(PTP_TIMER& pTimer);

	/***************************************************************
	*	MicroFlakeX 工厂 - 通过字符串创建对象
	*	1、该子类必须声明了 MFXOBJ_ENABLE_REFLECTION 宏
	*	2、该子类必须实现了 MFXOBJ_REFLECTION_BEGININIT(OBJ) 和 MFXOBJ_REFLECTION_ENDINIT(OBJ, FATHER)辅助宏
	****************************************************************/
	MFX_PORT MfxReturn MfxFactory(MfxString object, MfxBase** ret);
}




/***************************************************************
*	MfxSignal Mfx信号槽
****************************************************************/
namespace MicroFlakeX
{
	class MFX_PORT MfxSignal;
	class MFX_PORT MfxClient;

	/***************************************************************
	*	MicroFlakeX信号槽
	*	可以一对多的发送指定信号到指定对象
	****************************************************************/
	class MfxSignal
	{
	private:
		static std::vector<MfxSignal*> MfxSignal_Vector;
	private:
		struct MfxReceiver_Info
		{
			MfxReceiver_Info(MfxBase* recvObject, MfxString recvFunc)
			{
				this->recvFunc = recvFunc;
				this->recvObject = recvObject;
			}
			MfxString recvFunc;
			MfxBase* recvObject;
		};

	public:
		MfxSignal();
		MfxSignal(const MfxSignal& rhs);
		static void ReceiverDelete(MfxBase* recvObject);
		virtual ~MfxSignal();

		void RemoveReceiver(MfxBase* recvObject);
		void RemoveReceiver(MfxBase* recvObject, MfxString recvFunc);
		void PushBackReceiver(MfxBase* recvObject, MfxString recvFunc);
		void PushFrontReceiver(MfxBase* recvObject, MfxString recvFunc);

	protected:
		std::deque<MfxReceiver_Info> myReceiver;

		/***************************************************************
		*  根据参数长度不同，重载信号发送函数
		****************************************************************/
	public:
		void SendSignal()
		{
			for (auto& iter : myReceiver)
			{
				iter.recvObject->Reflection(iter.recvFunc);
			}
		}

		void PostSignal()
		{
			MfxParam tParam(this);
			MfxBeginNewThread_Widely(&(MfxSignal::ThreadSignal_0), tParam);
		}

	private:
		static MfxReturn MFX_CALLBACK(ThreadSignal_0)
		{
			MfxSignal* tThis = (MfxSignal*)MFX_CALLBACK_PARAM.GetPVOID();
			for (auto& iter : tThis->myReceiver)
			{
				iter.recvObject->Reflection(iter.recvFunc);
			}

			return MfxReturn_Seccess;
		}

		/***************************************************************
		*
		****************************************************************/
	public:
		template<typename ... Args>
		void SendSignal(Args&&... arg)
		{
			for (auto& iter : myReceiver)
			{
				iter.recvObject->Reflection(iter.recvFunc, std::forward<Args>(arg)...);
			}
		}


	public:
		template<typename ... Args>
		void PostSignal(Args&&... arg)
		{
			MfxBeginNewThread_Widely(&(MfxSignal::ThreadSignal_Template<Args...>), MFX_MAKE_PARAM(std::forward<Args>(arg)...).SetPVOID(this));
		}

	public:
		template<typename T1>
		void PostSignal(T1&& A1)
		{
			MfxParam tParam(this);
			tParam.push_back(std::forward<T1>(A1));
			MfxBeginNewThread_Widely(&(MfxSignal::ThreadSignal_Template<T1>), tParam);
		}
	private:
		template<typename T1>
		static MfxReturn MFX_CALLBACK(ThreadSignal_Template)
		{
			MfxSignal* tThis = (MfxSignal*)MFX_CALLBACK_PARAM.GetPVOID();
			for (auto& iter : tThis->myReceiver)
			{
				iter.recvObject->Reflection(iter.recvFunc, 
					MFXPARAM_GET_0(T1)
				);
			}
			return MfxReturn_Seccess;
		}


		/***************************************************************
		*
		****************************************************************/
	public:
		template<class T1, class T2>
		void SendSignal(T1&& A1, T2&& A2)
		{
			for (auto& iter : myReceiver)
			{
				iter.recvObject->Reflection(iter.recvFunc,
					std::forward<T1>(A1), std::forward<T2>(A2)
				);
			}
		}

		template<class T1, class T2>
		void PostSignal(T1&& A1, T2&& A2)
		{
			MfxParam tParam(this);
			tParam.push_back(std::forward<T1>(A1)); tParam.push_back(std::forward<T2>(A2));
			MfxBeginNewThread_Widely(&(MfxSignal::ThreadSignal_Template<T1, T2>), tParam);
		}

	private:
		template<class T1, class T2>
		static MfxReturn MFX_CALLBACK(ThreadSignal_Template)
		{
			MfxSignal* tThis = (MfxSignal*)MFX_CALLBACK_PARAM.GetPVOID();
			for (auto& iter : tThis->myReceiver)
			{
				iter.recvObject->Reflection(iter.recvFunc,
					MFXPARAM_GET_0(T1), MFXPARAM_GET_1(T2)
				);
			}
			return MfxReturn_Seccess;
		}

		/***************************************************************
		*
		****************************************************************/
	public:
		template<class T1, class T2, class T3>
		void SendSignal(T1&& A1, T2&& A2, T3&& A3)
		{
			for (auto& iter : myReceiver)
			{
				iter.recvObject->Reflection(iter.recvFunc,
					std::forward<T1>(A1), std::forward<T2>(A2),
					std::forward<T3>(A3)
				);
			}
		}

		template<class T1, class T2, class T3>
		void PostSignal(T1&& A1, T2&& A2, T3&& A3)
		{
			MfxParam tParam(this);
			tParam.push_back(std::forward<T1>(A1)); tParam.push_back(std::forward<T2>(A2));
			tParam.push_back(std::forward<T3>(A3));
			MfxBeginNewThread_Widely(&(MfxSignal::ThreadSignal_Template<T1, T2, T3>), tParam);
		}

	private:
		template<class T1, class T2, class T3>
		static MfxReturn MFX_CALLBACK(ThreadSignal_Template)
		{
			MfxSignal* tThis = (MfxSignal*)MFX_CALLBACK_PARAM.GetPVOID();
			for (auto& iter : tThis->myReceiver)
			{
				iter.recvObject->Reflection(iter.recvFunc,
					MFXPARAM_GET_0(T1), MFXPARAM_GET_1(T2),
					MFXPARAM_GET_2(T3)
				);
			}
			return MfxReturn_Seccess;
		}

		/***************************************************************
		*
		****************************************************************/
	public:
		template<class T1, class T2, class T3, class T4>
		void SendSignal(T1&& A1, T2&& A2, T3&& A3, T4&& A4)
		{
			for (auto& iter : myReceiver)
			{
				iter.recvObject->Reflection(iter.recvFunc,
					std::forward<T1>(A1), std::forward<T2>(A2),
					std::forward<T3>(A3), std::forward<T4>(A4)
				);
			}
		}

		template<class T1, class T2, class T3, class T4>
		void PostSignal(T1&& A1, T2&& A2, T3&& A3, T4&& A4)
		{
			MfxParam tParam(this);
			tParam.push_back(std::forward<T1>(A1)); tParam.push_back(std::forward<T2>(A2));
			tParam.push_back(std::forward<T3>(A3)); tParam.push_back(std::forward<T4>(A4));
			MfxBeginNewThread_Widely(&(MfxSignal::ThreadSignal_Template<T1, T2, T3, T4>), tParam);
		}

	private:
		template<class T1, class T2, class T3, class T4>
		static MfxReturn MFX_CALLBACK(ThreadSignal_Template)
		{
			MfxSignal* tThis = (MfxSignal*)MFX_CALLBACK_PARAM.GetPVOID();
			for (auto& iter : tThis->myReceiver)
			{
				iter.recvObject->Reflection(iter.recvFunc,
					MFXPARAM_GET_0(T1), MFXPARAM_GET_1(T2),
					MFXPARAM_GET_2(T3), MFXPARAM_GET_3(T4)
				);
			}
			return MfxReturn_Seccess;
		}


		/***************************************************************
		*
		****************************************************************/
	public:
		template<class T1, class T2, class T3, class T4, class T5>
		void SendSignal(T1&& A1, T2&& A2, T3&& A3, T4&& A4, T5&& A5)
		{
			for (auto& iter : myReceiver)
			{
				iter.recvObject->Reflection(iter.recvFunc,
					std::forward<T1>(A1), std::forward<T2>(A2),
					std::forward<T3>(A3), std::forward<T4>(A4),
					std::forward<T5>(A5)
				);
			}
		}

		template<class T1, class T2, class T3, class T4, class T5>
		void PostSignal(T1&& A1, T2&& A2, T3&& A3, T4&& A4, T5&& A5)
		{
			MfxParam tParam(this);
			tParam.push_back(std::forward<T1>(A1)); tParam.push_back(std::forward<T2>(A2));
			tParam.push_back(std::forward<T3>(A3)); tParam.push_back(std::forward<T4>(A4));
			tParam.push_back(std::forward<T5>(A5));
			MfxBeginNewThread_Widely(&(MfxSignal::ThreadSignal_Template<T1, T2, T3, T4, T5>), tParam);
		}

	private:
		template<class T1, class T2, class T3, class T4, class T5>
		static MfxReturn MFX_CALLBACK(ThreadSignal_Template)
		{
			MfxSignal* tThis = (MfxSignal*)MFX_CALLBACK_PARAM.GetPVOID();
			for (auto& iter : tThis->myReceiver)
			{
				iter.recvObject->Reflection(iter.recvFunc,
					MFXPARAM_GET_0(T1), MFXPARAM_GET_1(T2),
					MFXPARAM_GET_2(T3), MFXPARAM_GET_3(T4),
					MFXPARAM_GET_4(T5)
				);
			}
			return MfxReturn_Seccess;
		}

		/***************************************************************
		*
		****************************************************************/
	public:
		template<class T1, class T2, class T3, class T4, class T5, class T6>
		void SendSignal(T1&& A1, T2&& A2, T3&& A3, T4&& A4, T5&& A5, T6&& A6)
		{
			for (auto& iter : myReceiver)
			{
				iter.recvObject->Reflection(iter.recvFunc,
					std::forward<T1>(A1), std::forward<T2>(A2),
					std::forward<T3>(A3), std::forward<T4>(A4),
					std::forward<T5>(A5), std::forward<T6>(A6)
				);
			}
		}

		template<class T1, class T2, class T3, class T4, class T5, class T6>
		void PostSignal(T1&& A1, T2&& A2, T3&& A3, T4&& A4, T5&& A5, T6&& A6)
		{
			MfxParam tParam(this);
			tParam.push_back(std::forward<T1>(A1)); tParam.push_back(std::forward<T2>(A2));
			tParam.push_back(std::forward<T3>(A3)); tParam.push_back(std::forward<T4>(A4));
			tParam.push_back(std::forward<T5>(A5)); tParam.push_back(std::forward<T6>(A6));
			MfxBeginNewThread_Widely(&(MfxSignal::ThreadSignal_Template<T1, T2, T3, T4, T5, T6>), tParam);
		}

	private:
		template<class T1, class T2, class T3, class T4, class T5, class T6>
		static MfxReturn MFX_CALLBACK(ThreadSignal_Template)
		{
			MfxSignal* tThis = (MfxSignal*)MFX_CALLBACK_PARAM.GetPVOID();
			for (auto& iter : tThis->myReceiver)
			{
				iter.recvObject->Reflection(iter.recvFunc,
					MFXPARAM_GET_0(T1), MFXPARAM_GET_1(T2),
					MFXPARAM_GET_2(T3), MFXPARAM_GET_3(T4),
					MFXPARAM_GET_4(T5), MFXPARAM_GET_5(T6)
				);
			}
			return MfxReturn_Seccess;
		}

		/***************************************************************
		*
		****************************************************************/
	public:
		template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
		void SendSignal(T1&& A1, T2&& A2, T3&& A3, T4&& A4, T5&& A5, T6&& A6, T7&& A7)
		{
			for (auto& iter : myReceiver)
			{
				iter.recvObject->Reflection(iter.recvFunc,
					std::forward<T1>(A1), std::forward<T2>(A2),
					std::forward<T3>(A3), std::forward<T4>(A4),
					std::forward<T5>(A5), std::forward<T6>(A6),
					std::forward<T7>(A7)
				);
			}
		}

		template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
		void PostSignal(T1&& A1, T2&& A2, T3&& A3, T4&& A4, T5&& A5, T6&& A6, T7&& A7)
		{
			MfxParam tParam(this);
			tParam.push_back(std::forward<T1>(A1)); tParam.push_back(std::forward<T2>(A2));
			tParam.push_back(std::forward<T3>(A3)); tParam.push_back(std::forward<T4>(A4));
			tParam.push_back(std::forward<T5>(A5)); tParam.push_back(std::forward<T6>(A6));
			tParam.push_back(std::forward<T7>(A7)); 
			MfxBeginNewThread_Widely(&(MfxSignal::ThreadSignal_Template<T1, T2, T3, T4, T5, T6, T7>), tParam);
		}

	private:
		template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
		static MfxReturn MFX_CALLBACK(ThreadSignal_Template)
		{
			MfxSignal* tThis = (MfxSignal*)MFX_CALLBACK_PARAM.GetPVOID();
			for (auto& iter : tThis->myReceiver)
			{
				iter.recvObject->Reflection(iter.recvFunc,
					MFXPARAM_GET_0(T1), MFXPARAM_GET_1(T2),
					MFXPARAM_GET_2(T3), MFXPARAM_GET_3(T4),
					MFXPARAM_GET_4(T5), MFXPARAM_GET_5(T6),
					MFXPARAM_GET_6(T7)
				);
			}
			return MfxReturn_Seccess;
		}

		/***************************************************************
		*
		****************************************************************/
	public:
		template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
		void SendSignal(T1&& A1, T2&& A2, T3&& A3, T4&& A4, T5&& A5, T6&& A6, T7&& A7, T8&& A8)
		{
			for (auto& iter : myReceiver)
			{
				iter.recvObject->Reflection(iter.recvFunc, 
					std::forward<T1>(A1), std::forward<T2>(A2), 
					std::forward<T3>(A3), std::forward<T4>(A4),
					std::forward<T5>(A5), std::forward<T6>(A6),
					std::forward<T7>(A7), std::forward<T8>(A8)
				);
			}
		}

		template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
		void PostSignal(T1&& A1, T2&& A2, T3&& A3, T4&& A4, T5&& A5, T6&& A6, T7&& A7, T8&& A8)
		{
			MfxParam tParam(this);
			tParam.push_back(std::forward<T1>(A1)); tParam.push_back(std::forward<T2>(A2));
			tParam.push_back(std::forward<T3>(A3)); tParam.push_back(std::forward<T4>(A4));
			tParam.push_back(std::forward<T5>(A5)); tParam.push_back(std::forward<T6>(A6));
			tParam.push_back(std::forward<T7>(A7)); tParam.push_back(std::forward<T8>(A8));
			MfxBeginNewThread_Widely(&(MfxSignal::ThreadSignal_Template<T1, T2, T3, T4, T5, T6, T7, T8>), tParam);
		}

	private:
		template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
		static MfxReturn MFX_CALLBACK(ThreadSignal_Template)
		{
			MfxSignal* tThis = (MfxSignal*)MFX_CALLBACK_PARAM.GetPVOID();
			for (auto& iter : tThis->myReceiver)
			{
				iter.recvObject->Reflection(iter.recvFunc,
					MFXPARAM_GET_0(T1), MFXPARAM_GET_1(T2),
					MFXPARAM_GET_2(T3), MFXPARAM_GET_3(T4),
					MFXPARAM_GET_4(T5), MFXPARAM_GET_5(T6),
					MFXPARAM_GET_6(T7), MFXPARAM_GET_7(T8)
				);
			}
			return MfxReturn_Seccess;
		}


	};


	class MfxClient
	{
	private:
		static std::vector<MfxClient*> MfxClient_Vector;

	public:
		MfxClient();
		MfxClient(const MfxClient& rhs);
		static void ReceiverDelete(MfxBase* recvObject);
		virtual ~MfxClient();

		void RemoveReceiver(MfxBase* recvObject);
		void PushBackReceiver(MfxBase* recvObject);
		void PushFrontReceiver(MfxBase* recvObject);

	protected:
		std::deque<MfxBase*> myReceiver;

		/***************************************************************
		*  根据参数长度不同，重载信号发送函数
		****************************************************************/
	public:
		void SendClient(MfxString recvFunc)
		{
			for (auto& iter : myReceiver)
			{
				iter->Reflection(recvFunc);
			}
		}

		void PostClient(MfxString recvFunc)
		{
			MfxParam tParam(this);
			tParam.push_back(recvFunc);
			MfxBeginNewThread_Widely(&(MfxClient::ThreadClient_0), tParam);
		}

	private:
		static MfxReturn MFX_CALLBACK(ThreadClient_0)
		{
			MfxClient* tThis = (MfxClient*)MFX_CALLBACK_PARAM.GetPVOID();
			for (auto& iter : tThis->myReceiver)
			{
				iter->Reflection(MFXPARAM_GET_0(MfxString)
				);
			}

			return MfxReturn_Seccess;
		}

		/***************************************************************
		*
		****************************************************************/
	public:
		template<class T1>
		void SendClient(MfxString recvFunc, T1&& A1)
		{
			for (auto& iter : myReceiver)
			{
				iter->Reflection(recvFunc,
					std::forward<T1>(A1)
				);
			}
		}

		template<class T1>
		void PostClient(MfxString recvFunc, T1&& A1)
		{
			MfxParam tParam(this);
			tParam.push_back(recvFunc);
			tParam.push_back(std::forward<T1>(A1));
			MfxBeginNewThread_Widely(&(MfxClient::ThreadClient_Template<T1>), tParam);
		}

	private:
		template<class T1>
		static MfxReturn MFX_CALLBACK(ThreadClient_Template)
		{
			MfxClient* tThis = (MfxClient*)MFX_CALLBACK_PARAM.GetPVOID();
			for (auto& iter : tThis->myReceiver)
			{
				iter->Reflection(MFXPARAM_GET_0(MfxString),
					MFXPARAM_GET_1(T1)
				);
			}
			return MfxReturn_Seccess;
		}


		/***************************************************************
		*
		****************************************************************/
	public:
		template<class T1, class T2>
		void SendClient(MfxString recvFunc, T1&& A1, T2&& A2)
		{
			for (auto& iter : myReceiver)
			{
				iter->Reflection(recvFunc,
					std::forward<T1>(A1), std::forward<T2>(A2)
				);
			}
		}

		template<class T1, class T2>
		void PostClient(MfxString recvFunc, T1&& A1, T2&& A2)
		{
			MfxParam tParam(this);
			tParam.push_back(recvFunc);
			tParam.push_back(std::forward<T1>(A1)); tParam.push_back(std::forward<T2>(A2));
			MfxBeginNewThread_Widely(&(MfxClient::ThreadClient_Template<T1, T2>), tParam);
		}

	private:
		template<class T1, class T2>
		static MfxReturn MFX_CALLBACK(ThreadClient_Template)
		{
			MfxClient* tThis = (MfxClient*)MFX_CALLBACK_PARAM.GetPVOID();
			for (auto& iter : tThis->myReceiver)
			{
				iter->Reflection(MFXPARAM_GET_0(MfxString),
					MFXPARAM_GET_1(T1), MFXPARAM_GET_2(T2)
				);
			}
			return MfxReturn_Seccess;
		}


		/***************************************************************
		*
		****************************************************************/
	public:
		template<class T1, class T2, class T3>
		void SendClient(MfxString recvFunc, T1&& A1, T2&& A2, T3&& A3)
		{
			for (auto& iter : myReceiver)
			{
				iter->Reflection(recvFunc,
					std::forward<T1>(A1), std::forward<T2>(A2),
					std::forward<T3>(A3)
				);
			}
		}

		template<class T1, class T2, class T3>
		void PostClient(MfxString recvFunc, T1&& A1, T2&& A2, T3&& A3)
		{
			MfxParam tParam(this);
			tParam.push_back(recvFunc);
			tParam.push_back(std::forward<T1>(A1)); tParam.push_back(std::forward<T2>(A2));
			tParam.push_back(std::forward<T3>(A3));
			MfxBeginNewThread_Widely(&(MfxClient::ThreadClient_Template<T1, T2, T3>), tParam);
		}

	private:
		template<class T1, class T2, class T3>
		static MfxReturn MFX_CALLBACK(ThreadClient_Template)
		{
			MfxClient* tThis = (MfxClient*)MFX_CALLBACK_PARAM.GetPVOID();
			for (auto& iter : tThis->myReceiver)
			{
				iter->Reflection(MFXPARAM_GET_0(MfxString),
					MFXPARAM_GET_1(T1), MFXPARAM_GET_2(T2),
					MFXPARAM_GET_3(T3)
				);
			}
			return MfxReturn_Seccess;
		}
		/***************************************************************
		*
		****************************************************************/
	public:
		template<class T1, class T2, class T3, class T4>
		void SendClient(MfxString recvFunc, T1&& A1, T2&& A2, T3&& A3, T4&& A4)
		{
			for (auto& iter : myReceiver)
			{
				iter->Reflection(recvFunc,
					std::forward<T1>(A1), std::forward<T2>(A2),
					std::forward<T3>(A3), std::forward<T4>(A4)
				);
			}
		}

		template<class T1, class T2, class T3, class T4>
		void PostClient(MfxString recvFunc, T1&& A1, T2&& A2, T3&& A3, T4&& A4)
		{
			MfxParam tParam(this);
			tParam.push_back(recvFunc);
			tParam.push_back(std::forward<T1>(A1)); tParam.push_back(std::forward<T2>(A2));
			tParam.push_back(std::forward<T3>(A3)); tParam.push_back(std::forward<T4>(A4));
			MfxBeginNewThread_Widely(&(MfxClient::ThreadClient_Template<T1, T2, T3, T4>), tParam);
		}

	private:
		template<class T1, class T2, class T3, class T4>
		static MfxReturn MFX_CALLBACK(ThreadClient_Template)
		{
			MfxClient* tThis = (MfxClient*)MFX_CALLBACK_PARAM.GetPVOID();
			for (auto& iter : tThis->myReceiver)
			{
				iter->Reflection(MFXPARAM_GET_0(MfxString),
					MFXPARAM_GET_1(T1), MFXPARAM_GET_2(T2),
					MFXPARAM_GET_3(T3), MFXPARAM_GET_4(T4)
				);
			}
			return MfxReturn_Seccess;
		}

		/***************************************************************
		*
		****************************************************************/
	public:
		template<class T1, class T2, class T3, class T4, class T5>
		void SendClient(MfxString recvFunc, T1&& A1, T2&& A2, T3&& A3, T4&& A4, T5&& A5)
		{
			for (auto& iter : myReceiver)
			{
				iter->Reflection(recvFunc,
					std::forward<T1>(A1), std::forward<T2>(A2),
					std::forward<T3>(A3), std::forward<T4>(A4),
					std::forward<T5>(A5)
				);
			}
		}

		template<class T1, class T2, class T3, class T4, class T5>
		void PostClient(MfxString recvFunc, T1&& A1, T2&& A2, T3&& A3, T4&& A4, T5&& A5)
		{
			MfxParam tParam(this);
			tParam.push_back(recvFunc);
			tParam.push_back(std::forward<T1>(A1)); tParam.push_back(std::forward<T2>(A2));
			tParam.push_back(std::forward<T3>(A3)); tParam.push_back(std::forward<T4>(A4));
			tParam.push_back(std::forward<T5>(A5));
			MfxBeginNewThread_Widely(&(MfxClient::ThreadClient_Template<T1, T2, T3, T4, T5>), tParam);
		}

	private:
		template<class T1, class T2, class T3, class T4, class T5>
		static MfxReturn MFX_CALLBACK(ThreadClient_Template)
		{
			MfxClient* tThis = (MfxClient*)MFX_CALLBACK_PARAM.GetPVOID();
			for (auto& iter : tThis->myReceiver)
			{
				iter->Reflection(MFXPARAM_GET_0(MfxString),
					MFXPARAM_GET_1(T1), MFXPARAM_GET_2(T2),
					MFXPARAM_GET_3(T3), MFXPARAM_GET_4(T4),
					MFXPARAM_GET_5(T5)
				);
			}
			return MfxReturn_Seccess;
		}
		/***************************************************************
		*
		****************************************************************/
	public:
		template<class T1, class T2, class T3, class T4, class T5, class T6>
		void SendClient(MfxString recvFunc, T1&& A1, T2&& A2, T3&& A3, T4&& A4, T5&& A5, T6&& A6)
		{
			for (auto& iter : myReceiver)
			{
				iter->Reflection(recvFunc,
					std::forward<T1>(A1), std::forward<T2>(A2),
					std::forward<T3>(A3), std::forward<T4>(A4),
					std::forward<T5>(A5), std::forward<T6>(A6)
				);
			}
		}

		template<class T1, class T2, class T3, class T4, class T5, class T6>
		void PostClient(MfxString recvFunc, T1&& A1, T2&& A2, T3&& A3, T4&& A4, T5&& A5, T6&& A6)
		{
			MfxParam tParam(this);
			tParam.push_back(recvFunc);
			tParam.push_back(std::forward<T1>(A1)); tParam.push_back(std::forward<T2>(A2));
			tParam.push_back(std::forward<T3>(A3)); tParam.push_back(std::forward<T4>(A4));
			tParam.push_back(std::forward<T5>(A5)); tParam.push_back(std::forward<T6>(A6));
			MfxBeginNewThread_Widely(&(MfxClient::ThreadClient_Template<T1, T2, T3, T4, T5, T6>), tParam);
		}

	private:
		template<class T1, class T2, class T3, class T4, class T5, class T6>
		static MfxReturn MFX_CALLBACK(ThreadClient_Template)
		{
			MfxClient* tThis = (MfxClient*)MFX_CALLBACK_PARAM.GetPVOID();
			for (auto& iter : tThis->myReceiver)
			{
				iter->Reflection(MFXPARAM_GET_0(MfxString),
					MFXPARAM_GET_1(T1), MFXPARAM_GET_2(T2),
					MFXPARAM_GET_3(T3), MFXPARAM_GET_4(T4),
					MFXPARAM_GET_5(T5), MFXPARAM_GET_6(T6)
				);
			}
			return MfxReturn_Seccess;
		}
		/***************************************************************
		*
		****************************************************************/
	public:
		template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
		void SendClient(MfxString recvFunc, T1&& A1, T2&& A2, T3&& A3, T4&& A4, T5&& A5, T6&& A6, T7&& A7)
		{
			for (auto& iter : myReceiver)
			{
				iter->Reflection(recvFunc,
					std::forward<T1>(A1), std::forward<T2>(A2),
					std::forward<T3>(A3), std::forward<T4>(A4),
					std::forward<T5>(A5), std::forward<T6>(A6),
					std::forward<T7>(A7)
				);
			}
		}

		template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
		void PostClient(MfxString recvFunc, T1&& A1, T2&& A2, T3&& A3, T4&& A4, T5&& A5, T6&& A6, T7&& A7)
		{
			MfxParam tParam(this);
			tParam.push_back(recvFunc);
			tParam.push_back(std::forward<T1>(A1)); tParam.push_back(std::forward<T2>(A2));
			tParam.push_back(std::forward<T3>(A3)); tParam.push_back(std::forward<T4>(A4));
			tParam.push_back(std::forward<T5>(A5)); tParam.push_back(std::forward<T6>(A6));
			tParam.push_back(std::forward<T7>(A7));
			MfxBeginNewThread_Widely(&(MfxClient::ThreadClient_Template<T1, T2, T3, T4, T5, T6, T7>), tParam);
		}

	private:
		template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
		static MfxReturn MFX_CALLBACK(ThreadClient_Template)
		{
			MfxClient* tThis = (MfxClient*)MFX_CALLBACK_PARAM.GetPVOID();
			for (auto& iter : tThis->myReceiver)
			{
				iter->Reflection(MFXPARAM_GET_0(MfxString),
					MFXPARAM_GET_1(T1), MFXPARAM_GET_2(T2),
					MFXPARAM_GET_3(T3), MFXPARAM_GET_4(T4),
					MFXPARAM_GET_5(T5), MFXPARAM_GET_6(T6),
					MFXPARAM_GET_7(T7)
				);
			}
			return MfxReturn_Seccess;
		}
		/***************************************************************
		*
		****************************************************************/
	public:
		template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
		void SendClient(MfxString recvFunc, T1&& A1, T2&& A2, T3&& A3, T4&& A4, T5&& A5, T6&& A6, T7&& A7, T8&& A8)
		{
			for (auto& iter : myReceiver)
			{
				iter->Reflection(recvFunc, 
					std::forward<T1>(A1), std::forward<T2>(A2),
					std::forward<T3>(A3), std::forward<T4>(A4),
					std::forward<T5>(A5), std::forward<T6>(A6),
					std::forward<T7>(A7), std::forward<T8>(A8)
				);
			}
		}

		template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
		void PostClient(MfxString recvFunc, T1&& A1, T2&& A2, T3&& A3, T4&& A4, T5&& A5, T6&& A6, T7&& A7, T8&& A8)
		{
			MfxParam tParam(this);
			tParam.push_back(recvFunc);
			tParam.push_back(std::forward<T1>(A1)); tParam.push_back(std::forward<T2>(A2));
			tParam.push_back(std::forward<T3>(A3)); tParam.push_back(std::forward<T4>(A4));
			tParam.push_back(std::forward<T5>(A5)); tParam.push_back(std::forward<T6>(A6));
			tParam.push_back(std::forward<T7>(A7)); tParam.push_back(std::forward<T8>(A8));
			MfxBeginNewThread_Widely(&(MfxClient::ThreadClient_Template<T1, T2, T3, T4, T5, T6, T7, T8>), tParam);
		}

	private:
		template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
		static MfxReturn MFX_CALLBACK(ThreadClient_Template)
		{
			MfxClient* tThis = (MfxClient*)MFX_CALLBACK_PARAM.GetPVOID();
			for (auto& iter : tThis->myReceiver)
			{
				iter->Reflection(MFXPARAM_GET_0(MfxString),
					MFXPARAM_GET_1(T1), MFXPARAM_GET_2(T2),
					MFXPARAM_GET_3(T3), MFXPARAM_GET_4(T4),
					MFXPARAM_GET_5(T5), MFXPARAM_GET_6(T6),
					MFXPARAM_GET_7(T7), MFXPARAM_GET_8(T8)
				);
			}
			return MfxReturn_Seccess;
		}
	};
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
	*		RemoveObject - 移除注册
	*		RegisterObject - 注册工厂
	*
	****************************************************************/
	using namespace MicroFlakeX;

	MFX_PORT VOID CALLBACK MfxThreadCallBack(PTP_CALLBACK_INSTANCE instance, PVOID val);
	MFX_PORT VOID CALLBACK MfxThreadCallBack_Widely(PTP_CALLBACK_INSTANCE instance, PVOID val);

	MFX_PORT VOID CALLBACK MfxTimerCallBack(PTP_CALLBACK_INSTANCE instance, PVOID val, PTP_TIMER pTimer);
	MFX_PORT VOID CALLBACK MfxTimerCallBack_Widely(PTP_CALLBACK_INSTANCE instance, PVOID val, PTP_TIMER pTimer);

	class MFX_PORT MfxFactoryHand
	{
		friend MfxReturn MicroFlakeX::MfxFactory(MfxString object, MfxBase** ret);
	public:
		MfxFactoryHand(MfxString object);
		virtual MfxReturn Creat(MicroFlakeX::MfxBase** ret) = 0;
		virtual ~MfxFactoryHand();
	public:
		MfxReturn RemoveObject(MfxString object);
		MfxReturn RegisterObject(MfxString object, MfxFactoryHand* hand);

	private:
		MfxString myObjectName;
		static std::unordered_map<MfxString, MfxFactoryHand*> MfxFactoryHand_Map;
	};

}



















/***************************************************************
*	MicroFlakeX 模板反推区
****************************************************************/
namespace __MicroFlakeX
{
	/**
	template<typename R, typename O, typename... Args>
	constexpr const int Mfx_GetFuncArgc(R(O::*)(Args...) const)
	{
		return sizeof...(Args);
	};
	template<typename R, typename O, typename... Args>
	constexpr const int Mfx_GetFuncArgc(R(O::*)(Args...))
	{
		return sizeof...(Args);
	};
	template<typename R, typename... Args>
	constexpr const int Mfx_GetFuncArgc(R(*)(Args...))
	{
		return sizeof...(Args);
	};
	/**/


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
	constexpr const int Mfx_GetFuncArgc(T)
	{
		return MfxArgNum_<T>::Argc;
	};







	template <class R, class O, class... Args>
	O Mfx_GetFuncObject(R(O::*)(Args...) const)
	{
		return O();
	};

	template <class R, class O, class... Args>
	O Mfx_GetFuncObject(R(O::*)(Args...))
	{
		return O();
	};

	template <class R, class O, class... Args>
	R Mfx_GetFuncRet(R(O::*)(Args...) const)
	{
		return R();
	};

	template <class R, class O, class... Args>
	R Mfx_GetFuncRet(R(O::*)(Args...))
	{
		return R();
	};

	template <class R, class... Args>
	R Mfx_GetFuncRet(R(*)(Args...))
	{
		return R();
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
}


/***************************************************************
*	MicroFlakeX 辅助宏展开区
****************************************************************/
namespace __MicroFlakeX
{
#define __MFXOBJ_ENABLE_REFLECTION \
public:\
	MfxReturn Reflection(MfxString recvFunc...);\
	MfxReturn GetObjectName(MfxString* ret);



	/***************************************************************
	*
	*
	*
	****************************************************************/
#define __MFXOBJ_REFLECTION_INIT_0(OBJ)\
using namespace MicroFlakeX;\
using namespace __MicroFlakeX;\
MfxReturn OBJ::GetObjectName(MfxString* ret)\
{\
	*ret = MfxText(#OBJ);\
	return MfxReturn_Seccess;\
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
#define __MFXOBJ_REFLECTION_INIT_1(OBJ) \
	}\
	MfxReturn Creat(MfxBase** ret)\
	{\
		*ret = new OBJ;\
		return MfxReturn_Seccess;\
	}\
};\
OBJ##FactoryHand OBJ##Hand(MfxText(#OBJ));\
MfxReturn OBJ::Reflection(MfxString recvFunc...)\
{\
	MfxReturn ret = MfxReturn_Failed;\
	va_list argc;\
	va_start(argc, recvFunc);\
	BeginSwitch:\
	switch (MfxStrHash(recvFunc.c_str()))\
	{


	/***************************************************************
	*
	****************************************************************/
#define __MFXOBJ_REFLECTION_INIT_2(OBJ, FATHER_OBJ) \
		case MfxStrHash(MfxText("Reflection")):\
		{\
			recvFunc = va_arg(argc, MfxString);\
			argc = va_arg(argc, va_list);\
			goto BeginSwitch;\
		}\
		default:\
		{\
			ret = FATHER_OBJ::Reflection(MfxText("Reflection"), recvFunc, argc); \
			va_end(argc);\
			return ret;\
		}\
	}\
}

	template<typename T, typename T_This>
	inline MicroFlakeX::MfxReturn __T_MFXOBJ_REFLECTIONFUNC_CASE_EX(T_This pThis, T pFunc, va_list argc)
	{
		MicroFlakeX::MfxReturn ret = MfxReturn_Failed;
		if constexpr (__MicroFlakeX::MfxArgNum_<T>::Argc == 0)
		{
			ret = (pThis->*pFunc)();
			return ret;
		}
		else if constexpr (__MicroFlakeX::MfxArgNum_<T>::Argc == 1)
		{
			auto& A1 = va_arg(argc, decltype(__MicroFlakeX::Mfx_GetFuncArgv_1(pFunc)));
			ret = (pThis->*pFunc)(std::move(A1));
			return ret;
		}
		else if constexpr (__MicroFlakeX::MfxArgNum_<T>::Argc == 2)
		{
			auto& A1 = va_arg(argc, decltype(__MicroFlakeX::Mfx_GetFuncArgv_1(pFunc)));
			auto& A2 = va_arg(argc, decltype(__MicroFlakeX::Mfx_GetFuncArgv_2(pFunc)));
			ret = (pThis->*pFunc)(std::move(A1), std::move(A2));
			return ret;
		}
		else if constexpr (__MicroFlakeX::MfxArgNum_<T>::Argc == 3)
		{
			auto& A1 = va_arg(argc, decltype(__MicroFlakeX::Mfx_GetFuncArgv_1(pFunc)));
			auto& A2 = va_arg(argc, decltype(__MicroFlakeX::Mfx_GetFuncArgv_2(pFunc)));
			auto& A3 = va_arg(argc, decltype(__MicroFlakeX::Mfx_GetFuncArgv_3(pFunc)));
			ret = (pThis->*pFunc)(std::move(A1), std::move(A2), std::move(A3));
			return ret;
		}
		else if constexpr (__MicroFlakeX::MfxArgNum_<T>::Argc == 4)
		{
			auto& A1 = va_arg(argc, decltype(__MicroFlakeX::Mfx_GetFuncArgv_1(pFunc)));
			auto& A2 = va_arg(argc, decltype(__MicroFlakeX::Mfx_GetFuncArgv_2(pFunc)));
			auto& A3 = va_arg(argc, decltype(__MicroFlakeX::Mfx_GetFuncArgv_3(pFunc)));
			auto& A4 = va_arg(argc, decltype(__MicroFlakeX::Mfx_GetFuncArgv_4(pFunc)));
			ret = (pThis->*pFunc)(std::move(A1), std::move(A2), std::move(A3), std::move(A4));
			return ret;
		}
		else if constexpr (__MicroFlakeX::MfxArgNum_<T>::Argc == 5)
		{
			auto& A1 = va_arg(argc, decltype(__MicroFlakeX::Mfx_GetFuncArgv_1(pFunc)));
			auto& A2 = va_arg(argc, decltype(__MicroFlakeX::Mfx_GetFuncArgv_2(pFunc)));
			auto& A3 = va_arg(argc, decltype(__MicroFlakeX::Mfx_GetFuncArgv_3(pFunc)));
			auto& A4 = va_arg(argc, decltype(__MicroFlakeX::Mfx_GetFuncArgv_4(pFunc)));
			auto& A5 = va_arg(argc, decltype(__MicroFlakeX::Mfx_GetFuncArgv_5(pFunc)));
			ret = (pThis->*pFunc)(std::move(A1), std::move(A2), std::move(A3), std::move(A4), std::move(A5));
			return ret;
		}
		else if constexpr (__MicroFlakeX::MfxArgNum_<T>::Argc == 6)
		{
			auto& A1 = va_arg(argc, decltype(__MicroFlakeX::Mfx_GetFuncArgv_1(pFunc)));
			auto& A2 = va_arg(argc, decltype(__MicroFlakeX::Mfx_GetFuncArgv_2(pFunc)));
			auto& A3 = va_arg(argc, decltype(__MicroFlakeX::Mfx_GetFuncArgv_3(pFunc)));
			auto& A4 = va_arg(argc, decltype(__MicroFlakeX::Mfx_GetFuncArgv_4(pFunc)));
			auto& A5 = va_arg(argc, decltype(__MicroFlakeX::Mfx_GetFuncArgv_5(pFunc)));
			auto& A6 = va_arg(argc, decltype(__MicroFlakeX::Mfx_GetFuncArgv_6(pFunc)));
			ret = (pThis->*pFunc)(std::move(A1), std::move(A2), std::move(A3), std::move(A4), std::move(A5), std::move(A6));
			return ret;
		}
		else if constexpr (__MicroFlakeX::MfxArgNum_<T>::Argc == 7)
		{
			auto& A1 = va_arg(argc, decltype(__MicroFlakeX::Mfx_GetFuncArgv_1(pFunc)));
			auto& A2 = va_arg(argc, decltype(__MicroFlakeX::Mfx_GetFuncArgv_2(pFunc)));
			auto& A3 = va_arg(argc, decltype(__MicroFlakeX::Mfx_GetFuncArgv_3(pFunc)));
			auto& A4 = va_arg(argc, decltype(__MicroFlakeX::Mfx_GetFuncArgv_4(pFunc)));
			auto& A5 = va_arg(argc, decltype(__MicroFlakeX::Mfx_GetFuncArgv_5(pFunc)));
			auto& A6 = va_arg(argc, decltype(__MicroFlakeX::Mfx_GetFuncArgv_6(pFunc)));
			auto& A7 = va_arg(argc, decltype(__MicroFlakeX::Mfx_GetFuncArgv_7(pFunc)));
			ret = (pThis->*pFunc)(std::move(A1), std::move(A2), std::move(A3), std::move(A4), std::move(A5), std::move(A6), std::move(A7));
			return ret;
		}
		else if constexpr (__MicroFlakeX::MfxArgNum_<T>::Argc == 8)
		{
			auto& A1 = va_arg(argc, decltype(__MicroFlakeX::Mfx_GetFuncArgv_1(pFunc)));
			auto& A2 = va_arg(argc, decltype(__MicroFlakeX::Mfx_GetFuncArgv_2(pFunc)));
			auto& A3 = va_arg(argc, decltype(__MicroFlakeX::Mfx_GetFuncArgv_3(pFunc)));
			auto& A4 = va_arg(argc, decltype(__MicroFlakeX::Mfx_GetFuncArgv_4(pFunc)));
			auto& A5 = va_arg(argc, decltype(__MicroFlakeX::Mfx_GetFuncArgv_5(pFunc)));
			auto& A6 = va_arg(argc, decltype(__MicroFlakeX::Mfx_GetFuncArgv_6(pFunc)));
			auto& A7 = va_arg(argc, decltype(__MicroFlakeX::Mfx_GetFuncArgv_7(pFunc)));
			auto& A8 = va_arg(argc, decltype(__MicroFlakeX::Mfx_GetFuncArgv_8(pFunc)));
			ret = (pThis->*pFunc)(std::move(A1), std::move(A2), std::move(A3), std::move(A4), std::move(A5), std::move(A6), std::move(A7), std::move(A8));
			return ret;
		}
	}
	/***************************************************************
	*	MFXOBJ_REFLECTIONFUNC_CASE_EX注册宏
	****************************************************************/
#define __MFXOBJ_REFLECTIONFUNC_CASE_EX(OBJ, AUTO_FUNC)\
	case MfxStrHash(MfxText(#AUTO_FUNC)):\
	{\
		ret = __T_MFXOBJ_REFLECTIONFUNC_CASE_EX(this, &OBJ::AUTO_FUNC, argc);\
		va_end(argc); \
		return ret; \
	}
}




#define __MFXOBJ_REFLECTION_ENDINIT(OBJ, FATHER_OBJ, ...) \
	__MFXOBJ_REFLECTION_INIT_1(OBJ)\
	CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_0(OBJ, __VA_ARGS__));\
	__MFXOBJ_REFLECTION_INIT_2(OBJ, FATHER_OBJ);


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

const int ATEST = __MFX_IS_END(END); //3
const int BTEST = __MFX_IS_END(pFunc); //1
const int CTEST = __MFX_IS_END(); //2

#define __MFXOBJ_REFLECTIONFUNC_CASE_1(OBJ, FUNC_1) __MFXOBJ_REFLECTIONFUNC_CASE_EX(OBJ, FUNC_1)
#define __MFXOBJ_REFLECTIONFUNC_CASE_2(...)
#define __MFXOBJ_REFLECTIONFUNC_CASE_3(...)

#define MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1) \
	CCCONNECT(__MFXOBJ_REFLECTIONFUNC_CASE_, __MFX_IS_END(FUNC_1))(OBJ, FUNC_1)

namespace
{
#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_0(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_1(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_1(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_2(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_2(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_3(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_3(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_4(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_4(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_5(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_5(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_6(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_6(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_7(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_7(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_8(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_8(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_9(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_9(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_10(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_10(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_11(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_11(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_12(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_12(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_13(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_13(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_14(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_14(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_15(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_15(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_16(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_16(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_17(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_17(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_18(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_18(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_19(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_19(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_20(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_20(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_21(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_21(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_22(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_22(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_23(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_23(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_24(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_24(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_25(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_25(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_26(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_26(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_27(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_27(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_28(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_28(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_29(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_29(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_30(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_30(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_31(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_31(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_32(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_32(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_33(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_33(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_34(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_34(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_35(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_35(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_36(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_36(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_37(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_37(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_38(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_38(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_39(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_39(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_40(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_40(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_41(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_41(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_42(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_42(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_43(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_43(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_44(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_44(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_45(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_45(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_46(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_46(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_47(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_47(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_48(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_48(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_49(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_49(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_50(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_50(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_51(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_51(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_52(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_52(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_53(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_53(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_54(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_54(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_55(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_55(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_56(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_56(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_57(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_57(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_58(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_58(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_59(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_59(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_60(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_60(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_61(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_61(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_62(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_62(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_63(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_63(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_64(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_64(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_65(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_65(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_66(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_66(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_67(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_67(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_68(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_68(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_69(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_69(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_70(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_70(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_71(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_71(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_72(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_72(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_73(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_73(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_74(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_74(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_75(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_75(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_76(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_76(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_77(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_77(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_78(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_78(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_79(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_79(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_80(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_80(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_81(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_81(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_82(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_82(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_83(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_83(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_84(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_84(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_85(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_85(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_86(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_86(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_87(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_87(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_88(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_88(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_89(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_89(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_90(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_90(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_91(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_91(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_92(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_92(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_93(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_93(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_94(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_94(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_95(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_95(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_96(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_96(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_97(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_97(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_98(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_98(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_99(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_99(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_100(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_100(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_101(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_101(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_102(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_102(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_103(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_103(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_104(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_104(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_105(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_105(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_106(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_106(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_107(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_107(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_108(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_108(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_109(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_109(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_110(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_110(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_111(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_111(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_112(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_112(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_113(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_113(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_114(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_114(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_115(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_115(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_116(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_116(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_117(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_117(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_118(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_118(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_119(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_119(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)\
    CONNECT(__MFXOBJ_REFLECTIONFUNC_SPREADCASE_120(OBJ, __VA_ARGS__))

#define __MFXOBJ_REFLECTIONFUNC_SPREADCASE_120(OBJ, FUNC_1, FUNC_2, ...)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_1)\
    MFXOBJ_REFLECTIONFUNC_CASE(OBJ, FUNC_2)

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