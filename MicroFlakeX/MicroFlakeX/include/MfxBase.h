#pragma once

namespace MicroFlakeX
{
	class MFX_PORT MfxBase;
	typedef MfxBase* pMfxBase;

#define MfxObject __MfxObject
#define MfxObject_Init(OBJ) __MfxObject_Init_0(OBJ)
#define MfxObject_EndInit(OBJ, FATHER, ...) CONNECT(__MfxObject_EndInit, (OBJ, FATHER, __VA_ARGS__, END, END))
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
	typedef UINT32 MfxMessage;

	typedef std::uint64_t MfxHash;

#define Mfx_Return_Fine ((MfxReturn)0)
#define Mfx_Return_Fail ((MfxReturn)-1)
#define Mfx_Return_NotFind ((MfxReturn)1)
#define Mfx_Return_Unknow ((MfxReturn)2)

#define Mfx_Failed(MR) (MfxReturn)(((MfxReturn)(MR)) < 0)
#define Mfx_Seccess(MR) (MfxReturn)(((MfxReturn)(MR)) >= 0)

#define MfxString __MfxString
#define MfxText(str) __MfxText(str)

#ifdef UNICODE
#define __MfxCout std::wcout
#define __MfxText(str) L##str
#define __MfxString std::wstring
#elif 
#define __MfxCout std::cout
#define __MfxText(str) str
#define __MfxString std::string;
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

#define MFX_FloorCompare_Enable\
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
	typedef std::set<pMfxBase> MfxBase_Set;
	typedef std::queue<pMfxBase> MfxBase_Queue;
	typedef std::deque<pMfxBase> MfxBase_Deque;
	typedef std::stack<pMfxBase> MfxBase_Stack;
	typedef std::vector<pMfxBase> MfxBase_Vector;
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

#define GetParam(param, type, place)  (std::any_cast<type&>(param[place]))
#define GetParam_Safe(param, type, place)  (param.IsSafe(place) ? (std::any_cast<type&>(param[place])) : type())

	class MfxParam
	{
	private:
		static void* operator new(size_t);
		static void* operator new[](size_t);
	protected:
		INT32* myUseCount;
		MfxReturn* myReturn;
		MfxMessage* myMessage;
		std::vector<std::any>* myParam;
	public:
		MfxParam();
		MfxParam(MfxMessage msg);
		MfxParam(const MfxParam& rhs);
		~MfxParam();

		std::any& operator [] (int i);
		MfxParam& operator=(const MfxParam& rhs);

		bool IsSafe(int i);

		MfxNum GetParamSize();

		MfxReturn NowReturn();
		MfxMessage NowMessage();

		MfxReturn SetReturn(MfxReturn set);
		MfxMessage SetMessage(MfxMessage set);

		template<class T>
		void push_back(T&& val)
		{
			myParam->push_back(std::forward<T>(val));
		}
	};
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
		virtual MfxReturn AutoFunc(MfxString recvFunc...);
		virtual MfxReturn FuncName(MfxString* ret);
		virtual MfxReturn ObjectName(MfxString* ret);
	protected:
		MfxMemberLock myMemberLock;
	private:
		CRITICAL_SECTION myCriticalSection;
	};
}










namespace MicroFlakeX
{
	/***************************************************************
	*  MicroFlakeX 线程回调指针格式
	****************************************************************/
	typedef MfxReturn(*pThreadFunc)(MfxParam);

	/***************************************************************
	*  MicroFlakeX 回调函数辅助声明 - 返回值必须为MfxReturn
	*  例：MfxReturn MfxCallBack(MyCallBackFunc);
	****************************************************************/
#define MfxCallBack(funcName) funcName(MfxParam param)

	/***************************************************************
	* 异步线程请勿传入局部变量指针。
	* 参数一：回调对象指针
	* 参数二：回调对象方法名字
	* 参数三：传递给回调方法的MfxParam。
	****************************************************************/
	MFX_PORT MfxReturn MfxBeginNewThread(MfxBase* object, MfxString recvFunc, MfxParam mParam);


	/***************************************************************
	* 参数一：回调函数指针
	* 参数二：传递给回调方法的MfxParam
	****************************************************************/
	MFX_PORT MfxReturn MfxBeginNewThread_Widely(pThreadFunc pThreadFunc, MfxParam mParam);

	/***************************************************************
	* 参数一：返回一个计时器ID
	* 参数二：回调对象指针
	* 参数三：回调对象方法名字
	* 参数四：传递给回调方法的MfxParam
	* 参数五：计时器每个多长时间调用一次，单位为ms，若为0，则调用一次结束
	* 参数六：计时器多久之后开始，单位为100纳秒，-1秒为立即开始。-1（秒） = -10000000（100纳秒）
	* 参数七：计时器每次开始的时候是否有微小的随机性，单位为ms。随机性指，在定时器每次调用的时候，随机提前或者延后几毫秒。
	****************************************************************/
	MFX_PORT MfxReturn MfxBeginNewTimer(PTP_TIMER& pTimer, MfxBase* object, MfxString recvFunc, MfxParam mParam, MfxTime delay = 0, LONGLONG begin = -10000000, MfxTime randTime = 0);

	/***************************************************************
	* 参数一：返回一个计时器ID
	* 参数二：回调函数指针
	* 参数三：传递给回调方法的MfxParam
	* 参数四：计时器每个多长时间调用一次，单位为ms，若为0，则调用一次结束
	* 参数五：计时器多久之后开始，单位为100纳秒，-1秒为立即开始。-1（秒） = -10000000（100纳秒）
	* 参数六：计时器每次开始的时候是否有微小的随机性，单位为ms。随机性指，在定时器每次调用的时候，随机提前或者延后几毫秒。
	****************************************************************/
	MFX_PORT MfxReturn MfxBeginNewTimer_Widely(PTP_TIMER& pTimer, pThreadFunc pThreadFunc, MfxParam mParam, MfxTime delay = 0, LONGLONG begin = -10000000, MfxTime randTime = 0);

	/***************************************************************
	* 参数一：计时器ID，根据id删除对应的计时器
	****************************************************************/
	MFX_PORT MfxReturn MfxCloseTimer(PTP_TIMER& pTimer);

	/***************************************************************
	*	MicroFlakeX 工厂 - 通过字符串创建对象
	*	1、该子类必须声明了 MfxObject 宏
	*	2、该子类必须实现了 MfxObject_Init(object) 和 MfxObject_EndInit(object, father)辅助宏
	****************************************************************/
	MFX_PORT MfxReturn MfxFactory(MfxString object, MfxBase** ret);
}



/***************************************************************
*	MfxSignal Mfx信号槽
****************************************************************/
namespace MicroFlakeX
{
	class MFX_PORT MfxSignal;
	typedef MfxSignal* pMfxSignal;

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
				iter.recvObject->AutoFunc(iter.recvFunc);
			}
		}

		void PostSignal()
		{
			MfxParam tParam;
			tParam.push_back(this);
			MfxBeginNewThread_Widely(&(MfxSignal::ThreadSignal_0), tParam);
		}

	private:
		static MfxReturn ThreadSignal_0(MfxParam myParam)
		{
			MfxSignal* tThis = GetParam(myParam, MfxSignal*, 0);
			for (auto& iter : tThis->myReceiver)
			{
				iter.recvObject->AutoFunc(iter.recvFunc);
			}

			return Mfx_Return_Fine;
		}

		/***************************************************************
		*
		****************************************************************/
	public:
		template<typename T1>
		void SendSignal(T1&& A1)
		{
			for (auto& iter : myReceiver)
			{
				iter.recvObject->AutoFunc(iter.recvFunc, 
					std::forward<T1>(A1)
				);
			}
		}

		template<typename T1>
		void PostSignal(T1&& A1)
		{
			MfxParam tParam;
			tParam.push_back(this);
			tParam.push_back(std::forward<T1>(A1));
			MfxBeginNewThread_Widely(&(MfxSignal::ThreadSignal_Template<T1>), tParam);
		}
	private:
		template<typename T1>
		static MfxReturn ThreadSignal_Template(MfxParam myParam)
		{
			MfxSignal* tThis = GetParam(myParam, MfxSignal*, 0);
			for (auto& iter : tThis->myReceiver)
			{
				iter.recvObject->AutoFunc(iter.recvFunc, 
					GetParam(myParam, T1, 1)
				);
			}
			return Mfx_Return_Fine;
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
				iter.recvObject->AutoFunc(iter.recvFunc,
					std::forward<T1>(A1), std::forward<T2>(A2)
				);
			}
		}

		template<class T1, class T2>
		void PostSignal(T1&& A1, T2&& A2)
		{
			MfxParam tParam;
			tParam.push_back(this);
			tParam.push_back(std::forward<T1>(A1)); tParam.push_back(std::forward<T2>(A2));
			MfxBeginNewThread_Widely(&(MfxSignal::ThreadSignal_Template<T1, T2>), tParam);
		}

	private:
		template<class T1, class T2>
		static MfxReturn ThreadSignal_Template(MfxParam myParam)
		{
			MfxSignal* tThis = GetParam(myParam, MfxSignal*, 0);
			for (auto& iter : tThis->myReceiver)
			{
				iter.recvObject->AutoFunc(
					iter.recvFunc,
					GetParam(myParam, T1, 1), GetParam(myParam, T2, 2)
				);
			}
			return Mfx_Return_Fine;
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
				iter.recvObject->AutoFunc(iter.recvFunc,
					std::forward<T1>(A1), std::forward<T2>(A2),
					std::forward<T3>(A3)
				);
			}
		}

		template<class T1, class T2, class T3>
		void PostSignal(T1&& A1, T2&& A2, T3&& A3)
		{
			MfxParam tParam;
			tParam.push_back(this);
			tParam.push_back(std::forward<T1>(A1)); tParam.push_back(std::forward<T2>(A2));
			tParam.push_back(std::forward<T3>(A3));
			MfxBeginNewThread_Widely(&(MfxSignal::ThreadSignal_Template<T1, T2, T3>), tParam);
		}

	private:
		template<class T1, class T2, class T3>
		static MfxReturn ThreadSignal_Template(MfxParam myParam)
		{
			MfxSignal* tThis = GetParam(myParam, MfxSignal*, 0);
			for (auto& iter : tThis->myReceiver)
			{
				iter.recvObject->AutoFunc(
					iter.recvFunc,
					GetParam(myParam, T1, 1), GetParam(myParam, T2, 2),
					GetParam(myParam, T3, 3)
				);
			}
			return Mfx_Return_Fine;
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
				iter.recvObject->AutoFunc(iter.recvFunc,
					std::forward<T1>(A1), std::forward<T2>(A2),
					std::forward<T3>(A3), std::forward<T4>(A4)
				);
			}
		}

		template<class T1, class T2, class T3, class T4>
		void PostSignal(T1&& A1, T2&& A2, T3&& A3, T4&& A4)
		{
			MfxParam tParam;
			tParam.push_back(this);
			tParam.push_back(std::forward<T1>(A1)); tParam.push_back(std::forward<T2>(A2));
			tParam.push_back(std::forward<T3>(A3)); tParam.push_back(std::forward<T4>(A4));
			MfxBeginNewThread_Widely(&(MfxSignal::ThreadSignal_Template<T1, T2, T3, T4>), tParam);
		}

	private:
		template<class T1, class T2, class T3, class T4>
		static MfxReturn ThreadSignal_Template(MfxParam myParam)
		{
			MfxSignal* tThis = GetParam(myParam, MfxSignal*, 0);
			for (auto& iter : tThis->myReceiver)
			{
				iter.recvObject->AutoFunc(
					iter.recvFunc,
					GetParam(myParam, T1, 1), GetParam(myParam, T2, 2),
					GetParam(myParam, T3, 3), GetParam(myParam, T4, 4)
				);
			}
			return Mfx_Return_Fine;
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
				iter.recvObject->AutoFunc(iter.recvFunc,
					std::forward<T1>(A1), std::forward<T2>(A2),
					std::forward<T3>(A3), std::forward<T4>(A4),
					std::forward<T5>(A5)
				);
			}
		}

		template<class T1, class T2, class T3, class T4, class T5>
		void PostSignal(T1&& A1, T2&& A2, T3&& A3, T4&& A4, T5&& A5)
		{
			MfxParam tParam;
			tParam.push_back(this);
			tParam.push_back(std::forward<T1>(A1)); tParam.push_back(std::forward<T2>(A2));
			tParam.push_back(std::forward<T3>(A3)); tParam.push_back(std::forward<T4>(A4));
			tParam.push_back(std::forward<T5>(A5));
			MfxBeginNewThread_Widely(&(MfxSignal::ThreadSignal_Template<T1, T2, T3, T4, T5>), tParam);
		}

	private:
		template<class T1, class T2, class T3, class T4, class T5>
		static MfxReturn ThreadSignal_Template(MfxParam myParam)
		{
			MfxSignal* tThis = GetParam(myParam, MfxSignal*, 0);
			for (auto& iter : tThis->myReceiver)
			{
				iter.recvObject->AutoFunc(
					iter.recvFunc,
					GetParam(myParam, T1, 1), GetParam(myParam, T2, 2),
					GetParam(myParam, T3, 3), GetParam(myParam, T4, 4),
					GetParam(myParam, T5, 5)
				);
			}
			return Mfx_Return_Fine;
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
				iter.recvObject->AutoFunc(iter.recvFunc,
					std::forward<T1>(A1), std::forward<T2>(A2),
					std::forward<T3>(A3), std::forward<T4>(A4),
					std::forward<T5>(A5), std::forward<T6>(A6)
				);
			}
		}

		template<class T1, class T2, class T3, class T4, class T5, class T6>
		void PostSignal(T1&& A1, T2&& A2, T3&& A3, T4&& A4, T5&& A5, T6&& A6)
		{
			MfxParam tParam;
			tParam.push_back(this);
			tParam.push_back(std::forward<T1>(A1)); tParam.push_back(std::forward<T2>(A2));
			tParam.push_back(std::forward<T3>(A3)); tParam.push_back(std::forward<T4>(A4));
			tParam.push_back(std::forward<T5>(A5)); tParam.push_back(std::forward<T6>(A6));
			MfxBeginNewThread_Widely(&(MfxSignal::ThreadSignal_Template<T1, T2, T3, T4, T5, T6>), tParam);
		}

	private:
		template<class T1, class T2, class T3, class T4, class T5, class T6>
		static MfxReturn ThreadSignal_Template(MfxParam myParam)
		{
			MfxSignal* tThis = GetParam(myParam, MfxSignal*, 0);
			for (auto& iter : tThis->myReceiver)
			{
				iter.recvObject->AutoFunc(
					iter.recvFunc,
					GetParam(myParam, T1, 1), GetParam(myParam, T2, 2),
					GetParam(myParam, T3, 3), GetParam(myParam, T4, 4),
					GetParam(myParam, T5, 5), GetParam(myParam, T6, 6)
				);
			}
			return Mfx_Return_Fine;
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
				iter.recvObject->AutoFunc(iter.recvFunc,
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
			MfxParam tParam;
			tParam.push_back(this);
			tParam.push_back(std::forward<T1>(A1)); tParam.push_back(std::forward<T2>(A2));
			tParam.push_back(std::forward<T3>(A3)); tParam.push_back(std::forward<T4>(A4));
			tParam.push_back(std::forward<T5>(A5)); tParam.push_back(std::forward<T6>(A6));
			tParam.push_back(std::forward<T7>(A7)); 
			MfxBeginNewThread_Widely(&(MfxSignal::ThreadSignal_Template<T1, T2, T3, T4, T5, T6, T7>), tParam);
		}

	private:
		template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
		static MfxReturn ThreadSignal_Template(MfxParam myParam)
		{
			MfxSignal* tThis = GetParam(myParam, MfxSignal*, 0);
			for (auto& iter : tThis->myReceiver)
			{
				iter.recvObject->AutoFunc(
					iter.recvFunc,
					GetParam(myParam, T1, 1), GetParam(myParam, T2, 2),
					GetParam(myParam, T3, 3), GetParam(myParam, T4, 4),
					GetParam(myParam, T5, 5), GetParam(myParam, T6, 6),
					GetParam(myParam, T7, 7)
				);
			}
			return Mfx_Return_Fine;
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
				iter.recvObject->AutoFunc(iter.recvFunc, 
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
			MfxParam tParam;
			tParam.push_back(this);
			tParam.push_back(std::forward<T1>(A1)); tParam.push_back(std::forward<T2>(A2));
			tParam.push_back(std::forward<T3>(A3)); tParam.push_back(std::forward<T4>(A4));
			tParam.push_back(std::forward<T5>(A5)); tParam.push_back(std::forward<T6>(A6));
			tParam.push_back(std::forward<T7>(A7)); tParam.push_back(std::forward<T8>(A8));
			MfxBeginNewThread_Widely(&(MfxSignal::ThreadSignal_Template<T1, T2, T3, T4, T5, T6, T7, T8>), tParam);
		}

	private:
		template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
		static MfxReturn ThreadSignal_Template(MfxParam myParam)
		{
			MfxSignal* tThis = GetParam(myParam, MfxSignal*, 0);
			for (auto& iter : tThis->myReceiver)
			{
				iter.recvObject->AutoFunc(
					iter.recvFunc,
					GetParam(myParam, T1, 1), GetParam(myParam, T2, 2),
					GetParam(myParam, T3, 3), GetParam(myParam, T4, 4),
					GetParam(myParam, T5, 5), GetParam(myParam, T6, 6),
					GetParam(myParam, T7, 7), GetParam(myParam, T8, 8)
				);
			}
			return Mfx_Return_Fine;
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
	*		MfxRemoveObject - 移除注册
	*		MfxRegisterObject - 注册工厂
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
		MfxReturn MfxRemoveObject(MfxString object);
		MfxReturn MfxRegisterObject(MfxString object, MfxFactoryHand* hand);

	private:
		MfxString myObjectName;
		static std::unordered_map<MfxString, MfxFactoryHand*> MfxFactoryMap;
	};

}



















/***************************************************************
*	MicroFlakeX 模板反推区
****************************************************************/
namespace __MicroFlakeX
{
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
}


/***************************************************************
*	MicroFlakeX 辅助宏展开区
****************************************************************/
namespace __MicroFlakeX
{
#define __MfxObject \
public:\
	MfxReturn AutoFunc(MfxString recvFunc...);\
	MfxReturn FuncName(MfxString* ret);\
	MfxReturn ObjectName(MfxString* ret);


#define MfxObject_Init_0(OBJ) __MfxObject_Init_0(OBJ)
#define MfxObject_Init_1(OBJ, GOTO_BEGIN) __MfxObject_Init_1(OBJ, GOTO_BEGIN)
#define MfxObject_Init_2(OBJ, FATHER_OBJ) __MfxObject_Init_2(OBJ, FATHER_OBJ)

#define MfxAutoFunc_AutoEnum(...) CONNECT(__MfxAutoFunc_AutoEnum, (__VA_ARGS__))
#define MfxAutoFunc_AutoEnumBig(...) CONNECT(MfxAutoFunc_Enum_120, (__VA_ARGS__))

	/***************************************************************
	*
	****************************************************************/
#define __MfxObject_EndInit(OBJ, FATHER_OBJ, NUM1, BEGIN, ...) \
	MfxObject_Init_1(OBJ, BEGIN)\
	CONNECT(MfxAutoFunc_AutoEnumBig, (OBJ, NUM1, BEGIN, __VA_ARGS__);)\
	MfxObject_Init_2(OBJ, FATHER_OBJ);

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
	*
	*
	****************************************************************/
#define __MfxObject_Init_0(OBJ)\
using namespace MicroFlakeX;\
using namespace __MicroFlakeX;\
std::unordered_map<MfxString, MfxHash> Mfx##OBJ##FuncMap;\
typedef std::unordered_map<MfxString, MfxHash>::value_type Mfx##OBJ##FuncMapValue;\
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
	if(iter != Mfx##OBJ##FuncMap.end())\
	{\
		switch (iter->second)\
		{


	/***************************************************************
	*
	*
	*
	****************************************************************/
#define __MfxObject_Init_2(OBJ, FATHER_OBJ) \
		case MfxGetHash_StrA("AUTOFUNC_NOTFOUND"):\
		{\
			recvFunc = va_arg(argc, MfxString);\
			argc = va_arg(argc, va_list);\
			goto BeginSwitch;\
			REG_END:\
				Mfx##OBJ##FuncMap.insert(Mfx##OBJ##FuncMapValue(MfxText("AUTOFUNC_NOTFOUND"), MfxGetHash_StrA("AUTOFUNC_NOTFOUND")));\
			goto BeginSwitch;\
		}\
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
*	__MfxAutoFunc_注册宏
****************************************************************/

#define __MfxAutoFunc_0(OBJ, AUTO_FUNC, GOTO_NEXT) \
case MfxGetHash_StrA(#AUTO_FUNC):\
{\
	{\
		ret = AUTO_FUNC(); \
		va_end(argc);\
		return ret;\
	}\
	REG_##AUTO_FUNC:\
		Mfx##OBJ##FuncMap.insert(Mfx##OBJ##FuncMapValue(MfxText(#AUTO_FUNC), MfxGetHash_StrA(#AUTO_FUNC)));\
	goto REG_##GOTO_NEXT;\
}\

#define __MfxAutoFunc_1(OBJ, AUTO_FUNC, GOTO_NEXT) \
case MfxGetHash_StrA(#AUTO_FUNC):\
{\
	{\
		auto A1 = va_arg(argc, decltype(Mfx_GetFuncArgv_1(&OBJ::AUTO_FUNC))); \
		ret = AUTO_FUNC(A1); \
		va_end(argc);\
		return ret;\
	}\
	\
	REG_##AUTO_FUNC:\
		Mfx##OBJ##FuncMap.insert(Mfx##OBJ##FuncMapValue(MfxText(#AUTO_FUNC), MfxGetHash_StrA(#AUTO_FUNC)));\
	goto REG_##GOTO_NEXT;\
}\

#define __MfxAutoFunc_2(OBJ, AUTO_FUNC, GOTO_NEXT) \
case MfxGetHash_StrA(#AUTO_FUNC):\
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
		Mfx##OBJ##FuncMap.insert(Mfx##OBJ##FuncMapValue(MfxText(#AUTO_FUNC), MfxGetHash_StrA(#AUTO_FUNC)));\
	goto REG_##GOTO_NEXT;\
}\

#define __MfxAutoFunc_3(OBJ, AUTO_FUNC, GOTO_NEXT) \
case MfxGetHash_StrA(#AUTO_FUNC):\
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
		Mfx##OBJ##FuncMap.insert(Mfx##OBJ##FuncMapValue(MfxText(#AUTO_FUNC), MfxGetHash_StrA(#AUTO_FUNC)));\
	goto REG_##GOTO_NEXT;\
}\

#define __MfxAutoFunc_4(OBJ, AUTO_FUNC, GOTO_NEXT) \
case MfxGetHash_StrA(#AUTO_FUNC):\
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
		Mfx##OBJ##FuncMap.insert(Mfx##OBJ##FuncMapValue(MfxText(#AUTO_FUNC), MfxGetHash_StrA(#AUTO_FUNC)));\
	goto REG_##GOTO_NEXT;\
}\

#define __MfxAutoFunc_5(OBJ, AUTO_FUNC, GOTO_NEXT) \
case MfxGetHash_StrA(#AUTO_FUNC):\
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
		Mfx##OBJ##FuncMap.insert(Mfx##OBJ##FuncMapValue(MfxText(#AUTO_FUNC), MfxGetHash_StrA(#AUTO_FUNC)));\
	goto REG_##GOTO_NEXT;\
}\

#define __MfxAutoFunc_6(OBJ, AUTO_FUNC, GOTO_NEXT) \
case MfxGetHash_StrA(#AUTO_FUNC):\
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
		Mfx##OBJ##FuncMap.insert(Mfx##OBJ##FuncMapValue(MfxText(#AUTO_FUNC), MfxGetHash_StrA(#AUTO_FUNC)));\
	goto REG_##GOTO_NEXT;\
}\


#define __MfxAutoFunc_7(OBJ, AUTO_FUNC, GOTO_NEXT) \
case MfxGetHash_StrA(#AUTO_FUNC):\
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
		Mfx##OBJ##FuncMap.insert(Mfx##OBJ##FuncMapValue(MfxText(#AUTO_FUNC), MfxGetHash_StrA(#AUTO_FUNC)));\
	goto REG_##GOTO_NEXT;\
}\

#define __MfxAutoFunc_8(OBJ, AUTO_FUNC, GOTO_NEXT) \
case MfxGetHash_StrA(#AUTO_FUNC):\
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
		Mfx##OBJ##FuncMap.insert(Mfx##OBJ##FuncMapValue(MfxText(#AUTO_FUNC), MfxGetHash_StrA(#AUTO_FUNC)));\
	goto REG_##GOTO_NEXT;\
}

}





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