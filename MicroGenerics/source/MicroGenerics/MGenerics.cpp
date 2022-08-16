#include "pch.h"
using namespace MicroFlakeX;

MPP_THREAD_SAFE(ObjectWorkers);
MPP_THREAD_SAFE(FunctionWorkers);

auto& getObjectWorkers()
{
	static std::unordered_map<MicroFlakeX::MHash, MObjectWorker*> s_ObjectWorkers;
	return s_ObjectWorkers;
}

auto& getFunctionWorkers()
{
	static std::unordered_map<MicroFlakeX::MHash, MFunctionWorker*> s_FunctionWorkers;
	return s_FunctionWorkers;
}
/****************************************************************************************************************/
MResult MicroFlakeX::MObjectFactory(MStringHash objectName, MObject*& ret)
{
	MPP_THREAD_SAFE_TEMP_LOCK(ObjectWorkers);
	auto iter = getObjectWorkers().find(objectName.m_Hash64);
	if (iter != getObjectWorkers().end())
	{
		auto mr = iter->second->Creat(ret);
		return mr;
	}


	MSTR("hello");
	return MicroFlakeX::MResult::Success;
}

MResult MicroFlakeX::MFunctionCall(MStringHash funcName, MTempParam citeParam)
{
	MPP_THREAD_SAFE_TEMP_LOCK(FunctionWorkers);
	auto iter = getFunctionWorkers().find(funcName.m_Hash64);
	if (iter != getFunctionWorkers().end())
	{
		return iter->second->ReflectionCall(citeParam);
	}
	return MicroFlakeX::MResult::NotFind;
}

MResult MicroFlakeX::MFuncationCheck(MStringHash funcName)
{
	MPP_THREAD_SAFE_TEMP_LOCK(FunctionWorkers);
	auto iter = getFunctionWorkers().find(funcName.m_Hash64);
	return (iter == getFunctionWorkers().end()) ? MicroFlakeX::MResult::NotFind : MicroFlakeX::MResult::Success;
}


/****************************************************************************************************************/
MicroFlakeX::MObjectWorker::MObjectWorker(MStringHash objectHash)
{
	m_ObjectHash = objectHash;
	MPP_THREAD_SAFE_TEMP_LOCK(ObjectWorkers);
	auto tIter = getObjectWorkers().find(m_ObjectHash);
	if (tIter != getObjectWorkers().end())
	{
		// ¹þÏ£³åÍ»£¬´òlog
	}
	else
	{
		getObjectWorkers().insert({ objectHash, this });
	}
}

MicroFlakeX::MObjectWorker::~MObjectWorker()
{
	MPP_THREAD_SAFE_TEMP_LOCK(ObjectWorkers);
	auto tIter = getObjectWorkers().find(m_ObjectHash);
	if (tIter != getObjectWorkers().end())
	{
		getObjectWorkers().erase(tIter);
	}
}


/****************************************************************************************************************/
MicroFlakeX::MFunctionWorker::MFunctionWorker(MStringHash funcHash)
{
	m_FunctionHash = funcHash;
	MPP_THREAD_SAFE_TEMP_LOCK(FunctionWorkers);
	getFunctionWorkers().insert({ funcHash, this });
}

MicroFlakeX::MFunctionWorker::~MFunctionWorker()
{
	MPP_THREAD_SAFE_TEMP_LOCK(FunctionWorkers);
	auto tIter = getFunctionWorkers().find(m_FunctionHash);
	if (tIter != getFunctionWorkers().end())
	{
		getFunctionWorkers().erase(tIter);
	}
}


/****************************************************************************************************************/
MicroFlakeX::MObject::MObject()
{
}

MicroFlakeX::MObject::~MObject()
{
}

MResult MicroFlakeX::MObject::FunctionCall(MStringHash recv, MTempParam citeParam)
{
	return MicroFlakeX::MResult::NotFind;
}


/****************************************************************************************************************/
MicroFlakeX::MForward::MForward() noexcept
{
	m_Forward = nullptr;
}

MicroFlakeX::MForward::~MForward() noexcept
{
}

MicroFlakeX::MForward::MForward(MForward&& rhs) noexcept
{
	m_Forward = rhs.m_Forward; 
	rhs.m_Forward = nullptr;
}

MicroFlakeX::MForward::MForward(const MForward& rhs) noexcept
{
	m_Forward = rhs.m_Forward;
}

MForward& MicroFlakeX::MForward::operator=(MForward&& rhs) noexcept
{
	m_Forward = rhs.m_Forward;
	rhs.m_Forward = nullptr; 
	return *this;
}

MForward& MicroFlakeX::MForward::operator=(const MForward& rhs) noexcept
{
	m_Forward = rhs.m_Forward;
	return *this;
}

MResult MicroFlakeX::MForward::GetObjectName(const wchar_t** ret)
{
	return !m_Forward ? MicroFlakeX::MResult::Failure : m_Forward->GetObjectName(ret);
}

MResult MicroFlakeX::MForward::FunctionCall(MStringHash recv, MTempParam citeParam)
{
	return !m_Forward ? MicroFlakeX::MResult::Failure : m_Forward->FunctionCall(recv, citeParam);
}

MResult MicroFlakeX::MForward::MForward_SetForward(MObject* set)
{
	m_Forward = set;
	return MicroFlakeX::MResult::Success;
}

MResult MicroFlakeX::MForward::MForward_GetForward(MObject** ret)
{
	*ret = m_Forward; 
	return MicroFlakeX::MResult::Success;
}


/****************************************************************************************************************/
MicroFlakeX::IMUnknow::IMUnknow(const MUnknowMode mu_Mode)
	: m_Mode(mu_Mode)
{
}

MicroFlakeX::IMUnknow::~IMUnknow()
{
}
