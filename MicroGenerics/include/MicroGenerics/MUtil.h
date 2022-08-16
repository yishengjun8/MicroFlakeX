#pragma once

#ifndef MUTIL_H
#define MUTIL_H

namespace MicroFlakeX
{
	typedef std::int8_t        MInt8;
	typedef std::int16_t       MInt16;
	typedef std::int32_t       MInt32;
	typedef std::int64_t       MInt64;

	typedef std::uint8_t       MInt8_U;
	typedef std::uint16_t      MInt16_U;
	typedef std::uint32_t      MInt32_U;
	typedef std::uint64_t      MInt64_U;

	typedef std::float_t       MFloat;
	typedef std::double_t      MDouble;
}

namespace MicroFlakeX
{
	//MResult
	enum class MResult
	{
		Success = 0, /* 成功执行函数 */
		Failure = 1, /* 函数执行失败 */
		NotFind = 2, /* 未找到操作数 */
		Unknow = 4,  /* 未知操作 */
		Accept = 8,  /* 接受用户操作并且成功执行 */
	};

	typedef MInt32_U MEvent;
	typedef MInt32_U MMessage;

	typedef MInt32 MNum;
	typedef MInt64 MTime;
	typedef MInt32 MFloor;
	typedef MInt64_U MHash;

	enum class MUnknowMode
	{
		Pool = 0, /* 以对象池模式创建接口 */
		New = 1,  /* 以new模式创建接口 */
	};
}

namespace MicroFlakeX
{
	template<bool isHolder> struct MPlaceholder {};
	const MPlaceholder<true> MHolder_True;
	const MPlaceholder<false> MHolder_False;
}

namespace MicroFlakeX
{
	class MStringHash
	{
	public:
		constexpr MStringHash() noexcept { m_Hash64 = 0; };

	public:
		constexpr MStringHash(MStringHash&& rhs) noexcept { m_Hash64 = rhs.m_Hash64; };
		constexpr MStringHash(const MStringHash& rhs) noexcept { m_Hash64 = rhs.m_Hash64; };

		constexpr MStringHash& operator=(MStringHash&& rhs) noexcept { m_Hash64 = rhs.m_Hash64; return *this; };
		constexpr MStringHash& operator=(const MStringHash& rhs) noexcept { m_Hash64 = rhs.m_Hash64; return *this; };

	public:
		constexpr MStringHash(const wchar_t* str) noexcept { m_Hash64 = MStringToHash(str); };

		constexpr MStringHash& operator=(const wchar_t* rhs) noexcept { m_Hash64 = MStringToHash(rhs); return *this; };

	public:
		constexpr MStringHash(MHash&& rhs) noexcept { m_Hash64 = rhs; };
		constexpr MStringHash(const MHash& rhs) noexcept { m_Hash64 = rhs; };

		constexpr MStringHash& operator=(MHash&& rhs) noexcept { m_Hash64 = rhs; return *this; };
		constexpr MStringHash& operator=(const MHash& rhs) noexcept { m_Hash64 = rhs; return *this; };

	public:
		constexpr operator MHash() const noexcept { return m_Hash64; };

	public:
		constexpr bool operator==(MStringHash&& rhs) const noexcept { return m_Hash64 == rhs.m_Hash64; };
		constexpr bool operator==(const MStringHash& rhs) const noexcept { return m_Hash64 == rhs.m_Hash64; };

	public:
		constexpr static MHash MStringToHash(const wchar_t* str, MHash offset = 0, MInt32 seed = 131) noexcept { while (MHash ch = *str++) { offset = offset * seed + ch; }return offset; };

	public:
		MHash m_Hash64{ 0 };
	};
}

namespace MicroFlakeX
{
	template<typename T>
	inline bool MSwap(T& lhs, T& rhs)
	{
		T t_Swap = lhs;
		lhs = rhs;
		rhs = t_Swap;
	};

	template<typename P>
	inline bool MDelete(P*& pPoint)
	{
		delete pPoint;
		pPoint = nullptr;
		return true;
	}

	template<typename P>
	inline bool MDeleteList(P*& pPoint)
	{
		delete[] pPoint;
		pPoint = nullptr;
		return true;
	}

	template<typename P>
	inline bool MSafeDelete(P*& pPoint)
	{
		if (pPoint != nullptr)
		{
			delete pPoint;
			pPoint = nullptr;
		}
		return true;
	}

	template<typename P>
	inline bool MSafeDeleteList(P*& pPoint)
	{
		if (pPoint != nullptr)
		{
			delete[] pPoint;
			pPoint = nullptr;
		}
		return true;
	}

	template<typename I>
	inline bool MSafeRelease(I*& pInter)
	{
		if (pInter != nullptr)
		{
			pInter->Release();
			pInter = nullptr;
		}
		return true;
	};
}


namespace MicroFlakeX
{
	class MGENERICS_DLL_EXPORT MAny;
}

namespace MicroFlakeX
{
	class _MAnyBase
	{
	public:
		virtual ~_MAnyBase() {};
	public:
		virtual void* GetPoint() const = 0;
		virtual _MAnyBase* MakeValue() const = 0;
		virtual _MAnyBase* MakeValue_Copy() const = 0;
		virtual _MAnyBase* MakeValue_Cite() const = 0;
	};

	template<typename _Ty, typename>
	class _MAnyCite;
	template<typename _Ty, typename>
	class _MAnyCopy;

	//_Ty = decay_t<>
	template<typename _Ty,
		typename = typename std::enable_if_t<std::is_same_v<typename std::decay_t<_Ty>, _Ty>, _Ty>
	>
	class _MAnyCite
		: public _MAnyBase
	{
	private:
		_Ty* m_CiteValue;

	public:
		template<typename _ValTy>
		_MAnyCite(_ValTy&& value)
			: m_CiteValue(const_cast<_Ty*>(&value))
		{

		}

	public:
		void* GetPoint() const override
		{
			return (void*)m_CiteValue;
		}

		_MAnyBase* MakeValue() const override
		{
			return new _MAnyCite<_Ty>(*static_cast<_Ty*>(m_CiteValue));
		}

		_MAnyBase* MakeValue_Copy() const override
		{
			return new _MAnyCopy<_Ty>(*static_cast<_Ty*>(m_CiteValue));
		}

		_MAnyBase* MakeValue_Cite() const override
		{
			return new _MAnyCite<_Ty>(*static_cast<_Ty*>(m_CiteValue));
		}
	};

	//_Ty = decay_t
	template<typename _Ty,
		typename = typename std::enable_if_t<std::is_same_v<typename std::decay_t<_Ty>, _Ty>, _Ty>
	>
	class _MAnyCopy
		: public _MAnyBase
	{
	private:
		_Ty m_CopyValue;

	public:
		template<typename _ValTy>
		_MAnyCopy(_ValTy&& value)
			: m_CopyValue(static_cast<_Ty>(value))
		{
		}

	public:
		void* GetPoint() const override
		{
			return (void*)&m_CopyValue;
		}

		_MAnyBase* MakeValue() const override
		{
			return new _MAnyCopy<_Ty>(m_CopyValue);
		}

		_MAnyBase* MakeValue_Copy() const override
		{
			return new _MAnyCopy<_Ty>(m_CopyValue);
		}

		_MAnyBase* MakeValue_Cite() const override
		{
			return new _MAnyCite<_Ty>(m_CopyValue);
		}
	};

}

namespace MicroFlakeX
{
	/*
	* MAny容器可以存储任意的类型。
	* 默认选择: 左值引用，右值拷贝。
	*
	* MAny保存的值会在以下两种情况下失效：
	* 引用的临时右值，MAny会在右值变量所在的栈结束后悬空
	* 引用的局部变量，MAny会在局部变量的作用域结束后悬空
	*
	* MAny工作在copy状态下时
	* 保存的值是拷贝值，不会因为原变量析构而导致MAny悬空
	* 保存的拷贝变量类型，为原类型的完全退化体。(退化:const、&、&&、volatile)
	*/
	class MAny
	{
	private:
		MicroFlakeX::_MAnyBase* m_AnyTemp;

	protected:
		void Release();

	public:
		MAny();
		virtual ~MAny();

	public:
		MAny(MAny&& rhs) noexcept;
		MAny(const MAny& rhs);
		MAny& operator=(MAny&& rhs) noexcept;
		MAny& operator=(const MAny& rhs);

	public:
		bool MakeValue(const MAny& rhs);
		bool MakeValue_Copy(const MAny& rhs);
		bool MakeValue_Cite(const MAny& rhs);

		bool IsEmpty() const;
		void* GetPoint() const;

	public:
		template<typename _Ty>
		MAny(_Ty&& value)
			: MAny()
		{
			if constexpr (std::is_rvalue_reference_v<decltype(value)>)
			{
				SetCopyValue(value);
			}
			else
			{
				SetCiteValue(value);
			}
		}

		template<typename _Ty>
		MAny(bool isCopy, _Ty&& value)
			: MAny()
		{
			isCopy ? SetCopyValue(value) : SetCiteValue(value);
		}

	public:
		template<typename _Ty>
		bool SetValue(_Ty&& value)
		{
			Release();
			if constexpr (std::is_rvalue_reference_v<decltype(value)>)
			{
				SetCopyValue(value);
			}
			else
			{
				SetCiteValue(value);
			}
			return true;
		}

		template<typename _Ty>
		bool SetCiteValue(_Ty&& value)
		{
			Release();
			m_AnyTemp = new MicroFlakeX::_MAnyCite<typename std::decay_t<_Ty>>(value);
			return true;
		};

		template<typename _Ty>
		bool SetCopyValue(_Ty&& value)
		{
			Release();
			m_AnyTemp = new MicroFlakeX::_MAnyCopy<typename std::decay_t<_Ty>>(value);
			return true;
		};

		template<typename _Ty>
		_Ty&& any_cast()
		{
			return std::forward<_Ty>(*(typename std::decay_t<_Ty>*)(m_AnyTemp->GetPoint()));
		};
	};
}

namespace MicroFlakeX
{
	class MGENERICS_DLL_EXPORT MTempParam;

	class MGENERICS_DLL_EXPORT MCiteParam;
	class MGENERICS_DLL_EXPORT MCopyParam;

	class MGENERICS_DLL_EXPORT MSmartParam;
}


namespace MicroFlakeX
{
	/* 当此函数 */
	struct _MParam_Info
	{
		MAny m_AnyList[16];
		MInt8_U m_ParamCount{ 0 };
		MInt8_U m_UseCount{ 1 };
	};
	/*
	* MTempParam - 保存传入参数的地址
	* 参数从最右侧开始为0号
	* 左值引用，右值转化为左值后引用
	* 不允许在堆上新建，传入参数均为引用，展开这些参数并不会引发拷贝开销。
	* 传入的右值将会在最上层表达式结束后释放。GMTempParam不保留原始类型信息。
	* 最大参数持有为16 - 参数从右往左计算
	*/
	class MTempParam
	{
		friend class MicroFlakeX::MCiteParam;
		friend class MicroFlakeX::MCopyParam;
		friend class MicroFlakeX::MSmartParam;
	private:
		static void* operator new(size_t) { return nullptr; };
		static void* operator new[](size_t) { return nullptr; };
	private:
		void* m_AnyList[16];
		MInt8_U m_ParamCount;

	public:
		MTempParam() noexcept;
		virtual ~MTempParam() noexcept;

		MInt8_U GetSize() const noexcept;
		MAny&& GetMAny(const MInt8_U num) const noexcept;
		void* GetPoint(const MInt8_U num) const noexcept;

	public:
		MTempParam(MTempParam&& rhs) noexcept;
		MTempParam(const MTempParam& rhs) noexcept;
		MTempParam(MCiteParam&& rhs) noexcept;
		MTempParam(const MCiteParam& rhs) noexcept;
		MTempParam(MCopyParam&& rhs) noexcept;
		MTempParam(const MCopyParam& rhs) noexcept;
		MTempParam(MSmartParam&& rhs) noexcept;
		MTempParam(const MSmartParam& rhs) noexcept;

	public:
		MTempParam& operator=(MTempParam&& rhs) noexcept;
		MTempParam& operator=(const MTempParam& rhs) noexcept;
		MTempParam& operator=(MCiteParam&& rhs) noexcept;
		MTempParam& operator=(const MCiteParam& rhs) noexcept;
		MTempParam& operator=(MCopyParam&& rhs) noexcept;
		MTempParam& operator=(const MCopyParam& rhs) noexcept;
		MTempParam& operator=(MSmartParam&& rhs) noexcept;
		MTempParam& operator=(const MSmartParam& rhs) noexcept;

	public:
		template<typename _Ty>
		constexpr _Ty&& any_cast(const MInt8_U num) const noexcept
		{
			return std::forward<_Ty>(*(typename std::decay<_Ty>::type*)(m_AnyList[num]));
		}

		template<typename _Ty>
		constexpr _Ty&& reverse_any_cast(const MInt8_U num) const noexcept
		{
			return std::forward<_Ty>(*(typename std::decay<_Ty>::type*)(m_AnyList[m_ParamCount - num - 1]));
		}

		template<typename _Ty>
		constexpr MInt8_U push_back(_Ty&& value) noexcept
		{
			m_AnyList[m_ParamCount++] = &value;
			return m_ParamCount;
		}

	public:
		template<bool isOver>
		constexpr MTempParam(const MPlaceholder<isOver>) noexcept
			: MTempParam()
		{

		}

		template<bool isOver, typename _Ty, typename ..._ArgsTy>
		constexpr MTempParam(const MPlaceholder<isOver>, _Ty&& value, _ArgsTy&&... args) noexcept
			: MTempParam(MHolder_True, std::forward<_ArgsTy>(args)...)
		{
			m_AnyList[m_ParamCount++] = &value;
		}

		template<typename _Ty, typename ..._ArgsTy,
			typename = typename std::enable_if_t<!std::is_same_v<typename std::decay_t<_Ty>, MTempParam>, _Ty>,
			typename = typename std::enable_if_t<!std::is_same_v<typename std::decay_t<_Ty>, MCiteParam>, _Ty>,
			typename = typename std::enable_if_t<!std::is_same_v<typename std::decay_t<_Ty>, MCopyParam>, _Ty>,
			typename = typename std::enable_if_t<!std::is_same_v<typename std::decay_t<_Ty>, MSmartParam>, _Ty>
		>
		constexpr MTempParam(_Ty&& value, _ArgsTy&&... args) noexcept
			: MTempParam(MHolder_True, std::forward<_ArgsTy>(args)...)
		{
			m_AnyList[m_ParamCount++] = &value;
		}
	};

	/*
	* MCiteParam - 暂时保持传入的参数
	* 左值引用右值拷贝
	* 不允许在堆上新建，展开这些参数并不会引发额外的拷贝开销。
	* 如果引用的局部变量超出了他的作用域，那么将会引起GMCiteParam的悬空。请注意！
	* 最大参数持有为16 - 参数从右往左计算
	*/
	class MCiteParam
	{
		friend class MTempParam;
		friend class MCopyParam;
		friend class MSmartParam;
	private:
		static void* operator new(size_t) { return nullptr; };
		static void* operator new[](size_t) { return nullptr; };
	private:
		_MParam_Info* m_Info;

	public:
		MCiteParam() noexcept;
		virtual ~MCiteParam() noexcept;

		MInt8_U GetSize() const noexcept;
		MAny&& GetMAny(const MInt8_U num) const noexcept;
		void* GetPoint(const MInt8_U num) const noexcept;

	public:
		MCiteParam(MTempParam&& rhs) noexcept;
		MCiteParam(const MTempParam& rhs) noexcept;
		MCiteParam(MCiteParam&& rhs) noexcept;
		MCiteParam(const MCiteParam& rhs) noexcept;
		MCiteParam(MCopyParam&& rhs) noexcept;
		MCiteParam(const MCopyParam& rhs) noexcept;
		MCiteParam(MSmartParam&& rhs) noexcept;
		MCiteParam(const MSmartParam& rhs) noexcept;

	public:
		MCiteParam& operator=(MTempParam&& rhs) noexcept;
		MCiteParam& operator=(const MTempParam& rhs) noexcept;
		MCiteParam& operator=(MCiteParam&& rhs) noexcept;
		MCiteParam& operator=(const MCiteParam& rhs) noexcept;
		MCiteParam& operator=(MCopyParam&& rhs) noexcept;
		MCiteParam& operator=(const MCopyParam& rhs) noexcept;
		MCiteParam& operator=(MSmartParam&& rhs) noexcept;
		MCiteParam& operator=(const MSmartParam& rhs) noexcept;

	public:
		template<typename _Ty>
		_Ty&& any_cast(const MInt8_U num) const noexcept
		{
			return std::forward<_Ty>(m_Info->m_AnyList[num].any_cast<_Ty>());
		}

		template<typename _Ty>
		_Ty&& reverse_any_cast(const MInt8_U num) const noexcept
		{
			return std::forward<_Ty>(m_Info->m_AnyList[m_Info->m_ParamCount - num - 1].any_cast<_Ty>());
		}

		template<typename _Ty>
		MInt8_U push_back(_Ty&& value) noexcept
		{
			m_Info->m_AnyList[m_Info->m_ParamCount++].SetValue(std::forward<_Ty>(value));
			return m_Info->m_ParamCount;
		}
	public:
		template<bool isOver>
		MCiteParam(const MPlaceholder<isOver>) noexcept
			: MCiteParam()
		{

		}

		template<bool isOver, typename _Ty, typename ..._ArgsTy>
		MCiteParam(const MPlaceholder<isOver>, _Ty&& value, _ArgsTy&&... args) noexcept
			: MCiteParam(MHolder_True, std::forward<_ArgsTy>(args)...)
		{
			m_Info->m_AnyList[m_Info->m_ParamCount++].SetValue(std::forward<_Ty>(value));
		}

		template<typename _Ty, typename ..._ArgsTy,
			typename = typename std::enable_if_t<!std::is_same_v<typename std::decay_t<_Ty>, MTempParam>, _Ty>,
			typename = typename std::enable_if_t<!std::is_same_v<typename std::decay_t<_Ty>, MCiteParam>, _Ty>,
			typename = typename std::enable_if_t<!std::is_same_v<typename std::decay_t<_Ty>, MCopyParam>, _Ty>,
			typename = typename std::enable_if_t<!std::is_same_v<typename std::decay_t<_Ty>, MSmartParam>, _Ty>
		>
		MCiteParam(_Ty&& value, _ArgsTy&&... args) noexcept
			: MCiteParam(MHolder_True, std::forward<_ArgsTy>(args)...)
		{
			m_Info->m_AnyList[m_Info->m_ParamCount++].SetValue(std::forward<_Ty>(value));
		}
	};

	/*
	* MCopyParam - 长期保持传入的参数
	* 左值右值均拷贝
	* 允许在堆上新建，展开这些参数并不会引发额外的拷贝开销。
	* 最大参数持有为16 - 参数从右往左计算
	*/
	class MCopyParam
	{
		friend class MTempParam;
		friend class MCiteParam;
		friend class MSmartParam;
	protected:
		_MParam_Info* m_Info;

	public:
		MCopyParam() noexcept;
		~MCopyParam() noexcept;

		MInt8_U GetSize() const noexcept;
		MAny& GetMAny(const MInt8_U num) const noexcept;
		void* GetPoint(const MInt8_U num) const noexcept;

	public:
		MCopyParam(MTempParam&& rhs) noexcept;
		MCopyParam(const MTempParam& rhs) noexcept;
		MCopyParam(MCiteParam&& rhs) noexcept;
		MCopyParam(const MCiteParam& rhs) noexcept;
		MCopyParam(MCopyParam&& rhs) noexcept;
		MCopyParam(const MCopyParam& rhs) noexcept;
		MCopyParam(MSmartParam&& rhs) noexcept;
		MCopyParam(const MSmartParam& rhs) noexcept;

	public:
		MCopyParam& operator=(MTempParam&& rhs) noexcept;
		MCopyParam& operator=(const MTempParam& rhs) noexcept;
		MCopyParam& operator=(MCiteParam&& rhs) noexcept;
		MCopyParam& operator=(const MCiteParam& rhs) noexcept;
		MCopyParam& operator=(MCopyParam&& rhs) noexcept;
		MCopyParam& operator=(const MCopyParam& rhs) noexcept;
		MCopyParam& operator=(MSmartParam&& rhs) noexcept;
		MCopyParam& operator=(const MSmartParam& rhs) noexcept;

	public:
		template<typename _Ty>
		_Ty&& any_cast(const MInt8_U num) const noexcept
		{
			return std::forward<_Ty>(m_Info->m_AnyList[num].any_cast<_Ty>());
		}

		template<typename _Ty>
		_Ty&& reverse_any_cast(const MInt8_U num) const noexcept
		{
			return std::forward<_Ty>(m_Info->m_AnyList[m_Info->m_ParamCount - num - 1].any_cast<_Ty>());
		}

		template<typename _Ty>
		MInt8_U push_back(_Ty&& value) noexcept
		{
			m_Info->m_AnyList[m_Info->m_ParamCount++].SetCopyValue(std::forward<_Ty>(value));
			return m_Info->m_ParamCount;
		}

	public:
		template<bool isOver>
		MCopyParam(const MPlaceholder<isOver>)  noexcept
			: MCopyParam()
		{

		}

		template<bool isOver, typename _Ty, typename ..._ArgsTy>
		MCopyParam(const MPlaceholder<isOver>, _Ty&& value, _ArgsTy&&... args)  noexcept
			: MCopyParam(MHolder_True, std::forward<_ArgsTy>(args)...)
		{
			m_Info->m_AnyList[m_Info->m_ParamCount++].SetCopyValue(std::forward<_Ty>(value));
		}

		template<typename _Ty, typename ..._ArgsTy,
			typename = typename std::enable_if_t<!std::is_same_v<typename std::decay_t<_Ty>, MTempParam>, _Ty>,
			typename = typename std::enable_if_t<!std::is_same_v<typename std::decay_t<_Ty>, MCiteParam>, _Ty>,
			typename = typename std::enable_if_t<!std::is_same_v<typename std::decay_t<_Ty>, MCopyParam>, _Ty>,
			typename = typename std::enable_if_t<!std::is_same_v<typename std::decay_t<_Ty>, MSmartParam>, _Ty>
		>
		MCopyParam(_Ty&& value, _ArgsTy&&... args) noexcept
			: MCopyParam(MHolder_True, std::forward<_ArgsTy>(args)...)
		{
			m_Info->m_AnyList[m_Info->m_ParamCount++].SetCopyValue(std::forward<_Ty>(value));
		}
	};

	/*
	* MSmartParam - MCopyParam的智能指针升级版
	* 允许在堆上新建，传入参数强制拷贝，展开这些参数并不会引发额外的拷贝开销。
	* 内部有引用计数，当所有的引用计数归零，销毁传入的参数
	* 最大参数持有为16 - 参数从右往左计算
	*/
	class MSmartParam
	{
		friend class MTempParam;
		friend class MCiteParam;
		friend class MCopyParam;
	private:
		_MParam_Info* m_Info;

	protected:
		bool Release() noexcept;

	public:
		MSmartParam() noexcept;
		~MSmartParam() noexcept;

		MInt8_U GetSize() const noexcept;
		MAny& GetMAny(const MInt8_U num) const noexcept;
		void* GetPoint(const MInt8_U num) const noexcept;

	public:
		MSmartParam(MTempParam&& rhs) noexcept;
		MSmartParam(const MTempParam& rhs) noexcept;
		MSmartParam(MCiteParam&& rhs) noexcept;
		MSmartParam(const MCiteParam& rhs) noexcept;
		MSmartParam(MCopyParam&& rhs) noexcept;
		MSmartParam(const MCopyParam& rhs) noexcept;
		MSmartParam(MSmartParam&& rhs) noexcept;
		MSmartParam(const MSmartParam& rhs) noexcept;

	public:
		MSmartParam& operator=(MTempParam&& rhs) noexcept;
		MSmartParam& operator=(const MTempParam& rhs) noexcept;
		MSmartParam& operator=(MCiteParam&& rhs) noexcept;
		MSmartParam& operator=(const MCiteParam& rhs) noexcept;
		MSmartParam& operator=(MCopyParam&& rhs) noexcept;
		MSmartParam& operator=(const MCopyParam& rhs) noexcept;
		MSmartParam& operator=(MSmartParam&& rhs) noexcept;
		MSmartParam& operator=(const MSmartParam& rhs) noexcept;

	public:
		template<typename _Ty>
		_Ty&& any_cast(const MInt8_U num) const noexcept
		{
			return std::forward<_Ty>(m_Info->m_AnyList[num].any_cast<_Ty>());
		}

		template<typename _Ty>
		_Ty&& reverse_any_cast(const MInt8_U num) const noexcept
		{
			return std::forward<_Ty>(m_Info->m_AnyList[m_Info->m_ParamCount - num - 1].any_cast<_Ty>());
		}

		template<typename _Ty>
		MInt8_U push_back(_Ty&& value) noexcept
		{
			m_Info->m_AnyList[m_Info->m_ParamCount++].SetCopyValue(std::forward<_Ty>(value));
			return m_Info->m_ParamCount;
		}
	public:
		template<bool isOver>
		MSmartParam(const MPlaceholder<isOver>) noexcept
			: MSmartParam()
		{

		}

		template<bool isOver, typename _Ty, typename ..._ArgsTy>
		MSmartParam(const MPlaceholder<isOver>, _Ty&& value, _ArgsTy&&... args) noexcept
			: MSmartParam(MHolder_True, std::forward<_ArgsTy>(args)...)
		{
			m_Info->m_AnyList[m_Info->m_ParamCount++].SetCopyValue(std::forward<_Ty>(value));
		}

		template<typename _Ty, typename ..._ArgsTy,
			typename = typename std::enable_if_t<!std::is_same_v<typename std::decay_t<_Ty>, MTempParam>, _Ty>,
			typename = typename std::enable_if_t<!std::is_same_v<typename std::decay_t<_Ty>, MCiteParam>, _Ty>,
			typename = typename std::enable_if_t<!std::is_same_v<typename std::decay_t<_Ty>, MCopyParam>, _Ty>,
			typename = typename std::enable_if_t<!std::is_same_v<typename std::decay_t<_Ty>, MSmartParam>, _Ty>
		>
		MSmartParam(_Ty&& value, _ArgsTy&&... args) noexcept
			: MSmartParam(MHolder_True, std::forward<_ArgsTy>(args)...)
		{
			m_Info->m_AnyList[m_Info->m_ParamCount++].SetCopyValue(std::forward<_Ty>(value));
		}
	};


}

namespace MicroFlakeX
{
	class _MParamExtend
	{
	protected:
		MicroFlakeX::MInt8 m_Num;
	public:
		_MParamExtend(MicroFlakeX::MInt8 begin = 0) { m_Num = begin; };
		template<typename _Ty>
		inline _Ty&& Extend(MicroFlakeX::MTempParam& param) noexcept
		{
			return param.any_cast<_Ty>(m_Num++);
		}

		template<typename _Ty>
		inline _Ty&& Extend(MicroFlakeX::MCiteParam& param) noexcept
		{
			return param.any_cast<_Ty>(m_Num++);
		}

		template<typename _Ty>
		inline _Ty&& Extend(MicroFlakeX::MCopyParam& param) noexcept
		{
			return param.any_cast<_Ty>(m_Num++);
		}
	};

}

namespace MicroFlakeX
{
	class MGENERICS_DLL_EXPORT MLock;
	class MGENERICS_DLL_EXPORT MLockHelper;
}

namespace MicroFlakeX
{
	class _mLock;
	class MLock
	{
		friend class MLockHelper;
	public:
		MLock() noexcept;
		virtual ~MLock() noexcept;

	public:
		MLock(MLock&& rhs) noexcept;
		MLock(const MLock& rhs) noexcept;
		MLock& operator = (MLock&& rhs) noexcept;
		MLock& operator = (const MLock& rhs) noexcept;

	public:
		bool Lock();
		bool UnLock();

	private:
		_mLock* m_Interface;

	};

	enum MLockMode
	{
		ReadOnly = 0x0000,
		Write = 0x0001
	};

	class MLockHelper
	{
	public:
		MLockHelper(MLock& rhs, MLockMode mode = ReadOnly) noexcept;
		virtual ~MLockHelper() noexcept;
	public:
		bool Lock();
		bool UnLock();
	private:

		MLock& m_Lock;
		MLockMode m_Mode;
	};
}



#endif //PCH_H