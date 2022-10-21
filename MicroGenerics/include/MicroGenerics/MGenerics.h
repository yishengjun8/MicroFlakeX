#pragma once


namespace MicroFlakeX
{
	class MGENERICS_DLL_EXPORT MObject;
	class MGENERICS_DLL_EXPORT MForward;
	class MGENERICS_DLL_EXPORT IMUnknow;
}

namespace MicroFlakeX
{
	/* 反射 - 对象工厂 */
	MGENERICS_DLL_EXPORT MResult MObjectFactory(MStringHash objectName, MObject*& ret);

	/* 反射 - 函数调用 */
	MGENERICS_DLL_EXPORT MResult MFunctionCall(MStringHash functionName, MParamOnce citeParam = MParamOnce());

	/* 反射 - 检查函数是否存在 */
	MGENERICS_DLL_EXPORT MResult MFuncationCheck(MStringHash functionName);


}

namespace MicroFlakeX
{
	/* 添加一个计数器，用来查询是否可以安全卸载dll */
	class MObject
	{
	public:
		MObject();
		virtual ~MObject();

	public:
		MObject(MObject&& rhs) = delete;
		MObject(const MObject& rhs) = delete;
		MObject& operator = (MObject&& rhs) = delete;
		MObject& operator = (const MObject& rhs) = delete;

	public:
		virtual MResult GetObjectName(const wchar_t** ret) = 0;
		virtual MResult FunctionCall(MStringHash recv, MParamOnce citeParam = MParamOnce());
	};


	class MForward
		: public MObject
	{
	public:
		MForward() noexcept;
		virtual ~MForward() noexcept;

	public:
		MForward(MForward&& rhs) noexcept;
		MForward(const MForward& rhs) noexcept;
		MForward& operator = (MForward&& rhs) noexcept;
		MForward& operator = (const MForward& rhs) noexcept;

	public:
		MResult GetObjectName(const wchar_t** ret);
		MResult FunctionCall(MStringHash recv, MParamOnce citeParam = MParamOnce());

	public:
		MResult MForward_SetForward(MObject* set);
		MResult MForward_GetForward(MObject** ret);

	private:
		MObject* m_Forward;
	};

	class IMUnknow
		: public MObject
	{
	public:
		IMUnknow(const MUnknowMode mode);
		virtual ~IMUnknow();

	public:
		IMUnknow(IMUnknow&& rhs) = delete;
		IMUnknow(const IMUnknow& rhs) = delete;
		IMUnknow& operator = (IMUnknow&& rhs) = delete;
		IMUnknow& operator = (const IMUnknow& rhs) = delete;
	public:
		virtual MResult GetObjectName(const wchar_t** ret) = 0;
		virtual MResult FunctionCall(MStringHash recv, MParamOnce citeParam = MParamOnce()) = 0;
	public:
		virtual MicroFlakeX::MResult Unknow_Release() = 0;
		virtual MicroFlakeX::MResult Unknow_IsEmpty(bool* ret) = 0;

	private:
		MUnknowMode m_Mode;
	};
}


namespace MicroFlakeX
{
	namespace MHelper
	{
		MFX_TEMPLATE_EASY_GET(MGetForward, GetForward, MicroFlakeX::MObject*, nullptr);
		MFX_TEMPLATE_EASY_SET(MSetForward, SetForward, MicroFlakeX::MObject*, nullptr);
	}

}


namespace MicroFlakeX
{
	class MGENERICS_DLL_EXPORT MObjectWorker
	{
	public:
		MObjectWorker(MStringHash objectHash);
		virtual ~MObjectWorker();

	public:
		virtual MResult Creat(MObject*& ret) = 0;

	private:
		MHash m_ObjectHash;
	};

	class MGENERICS_DLL_EXPORT MFunctionWorker
	{
	public:
		MFunctionWorker(MStringHash funcHash);
		virtual ~MFunctionWorker();

	public:
		virtual MResult ReflectionCall(MParamOnce citeParam) = 0;
	
	private:
		MHash m_FunctionHash;
	};
}


namespace MicroFlakeX
{
	template <typename T_THIS, typename OBJ, typename... Args>
	inline MResult _MObjectFunctionCall(T_THIS pThis, MParamOnce& citeParam, MResult(OBJ::* pFunc)(Args...))
	{
		_MParamExtend t_ParamExtend;
		return (pThis->*pFunc)((t_ParamExtend.Extend<Args>(citeParam))...);
	};

	template <typename T_THIS, typename OBJ, typename... Args>
	inline MResult _MObjectFunctionCall(T_THIS pThis, MParamOnce& citeParam, MResult(OBJ::* pFunc)(Args...) const)
	{
		_MParamExtend t_ParamExtend;
		return (pThis->*pFunc)((t_ParamExtend.Extend<Args>(citeParam))...);
	};

	template <typename... Args>
	inline MResult _MFunctionCall(MParamOnce& citeParam, MResult(*pFunc)(Args...))
	{
		_MParamExtend t_ParamExtend;
		return pFunc((t_ParamExtend.Extend<Args>(citeParam))...);
	};
}

namespace MicroFlakeX
{
	class MGENERICS_DLL_EXPORT MInterger;
}

//测试用例，可以检测是否有多余的拷贝
namespace MicroFlakeX
{
	class MInterger
	{
	private:
		int m_int;
	public:
		MInterger(const int value)
			: m_int((int)value)
		{
			printf("\nMInterger [int] creat by value [%d]\n", m_int);
		}
		MInterger(const char value)
			: m_int((int)value)
		{
			printf("\nMInterger [char] creat by value [%d]\n", m_int);
		}
		MInterger(const short value)
			: m_int((int)value)
		{
			printf("\nMInterger [short] creat by value [%d]\n", m_int);
		}
		MInterger(const long value)
			: m_int((int)value)
		{
			printf("\nMInterger [long] creat by value [%d]\n", m_int);
		}
		MInterger(const long long value)
			: m_int((int)value)
		{
			printf("\nMInterger [long long] creat by value [%d]\n", m_int);
		}
		MInterger(const float value)
			: m_int((int)value)
		{
			printf("\nMInterger [float] creat by value [%d]\n", m_int);
		}
		MInterger(const double value)
			: m_int((int)value)
		{
			printf("\nMInterger [double] creat by value [%d]\n", m_int);
		}
		~MInterger()
		{
			printf("\nMInterger delete, m_int is [%d]\n", m_int);
		}
	public:
		MInterger(const MInterger& value)
			: m_int((int)value.m_int)
		{
			printf("\nMInterger [MInterger&] creat by value [%d]\n", m_int);
		}
		MInterger(const MInterger&& value)noexcept
			: m_int((int)value.m_int)
		{
			printf("\nMInterger [MInterger&&] creat by value [%d]\n", m_int);
		}
		MInterger& operator=(const MInterger& rhs)
		{
			printf("\nMInterger [=], m_int is[%d], rhs is [%d]\n", m_int, rhs.m_int);
			m_int = (int)rhs.m_int;
			return *this;
		}
		MInterger& operator=(const MInterger&& rhs)noexcept
		{
			printf("\nMInterger [= &&], m_int is[%d], rhs is [%d]\n", m_int, rhs.m_int);
			m_int = (int)rhs.m_int;
			return *this;
		}

	public:
		MInterger& operator=(const int rhs)
		{
			printf("\nMInterger [= int], m_int is[%d], rhs is [%d]\n", m_int, rhs);
			m_int = (int)rhs;
			return *this;
		}
		MInterger& operator=(const double rhs)
		{
			printf("\nMInterger [= double], m_int is[%d], rhs is [%f]\n", m_int, rhs);
			m_int = (int)rhs;
			return *this;
		}
	};
}