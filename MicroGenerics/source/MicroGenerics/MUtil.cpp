#include "pch.h"

using namespace MicroFlakeX;
/****************************************************************************************************************/
void MicroFlakeX::MAny::Release()
{
	MSafeDelete(m_AnyTemp);
}
bool MicroFlakeX::MAny::MakeValue(const MAny& rhs)
{
	Release();
	m_AnyTemp = rhs.m_AnyTemp ? rhs.m_AnyTemp->MakeValue() : nullptr;
	return true;
}
bool MicroFlakeX::MAny::MakeValue_Copy(const MAny& rhs)
{
	Release();
	m_AnyTemp = rhs.m_AnyTemp ? rhs.m_AnyTemp->MakeValue_Copy() : nullptr;
	return true;
}

bool MicroFlakeX::MAny::MakeValue_Cite(const MAny& rhs)
{
	Release();
	m_AnyTemp = rhs.m_AnyTemp ? rhs.m_AnyTemp->MakeValue_Cite() : nullptr;
	return true;
}



MicroFlakeX::MAny::MAny()
	: m_AnyTemp(nullptr)
{
}

MicroFlakeX::MAny::~MAny()
{
	Release();
}

MicroFlakeX::MAny::MAny(const MAny& rhs)
	: MAny()
{
	MakeValue(rhs);
}

MicroFlakeX::MAny::MAny(MAny&& rhs) noexcept
	: MAny()
{
	m_AnyTemp = rhs.m_AnyTemp; 
	rhs.m_AnyTemp = nullptr;
}


MicroFlakeX::MAny& MicroFlakeX::MAny::operator=(MAny&& rhs) noexcept
{
	Release();
	m_AnyTemp = rhs.m_AnyTemp;
	rhs.m_AnyTemp = nullptr;
	return *this;
}
MicroFlakeX::MAny& MicroFlakeX::MAny::operator=(const MAny& rhs)
{
	Release();
	MakeValue(rhs);
	return *this;
}

bool MicroFlakeX::MAny::IsEmpty() const
{
	return m_AnyTemp;
}

void* MicroFlakeX::MAny::GetPoint() const
{
	return m_AnyTemp->GetPoint();
}
/****************************************************************************************************************/



/****************************************************************************************************************/
class MicroFlakeX::_mLock
{
public:
	std::mutex m_read;
	std::mutex m_write;
};

M_OBJECT_POOL_ACHIEVE(_mLock);

MicroFlakeX::MLock::MLock() noexcept
	: m_Interface(new_mLock())
{
}
MicroFlakeX::MLock::~MLock() noexcept
{
	del_mLock(m_Interface);
}

MicroFlakeX::MLock::MLock(MLock&& rhs) noexcept
	: m_Interface(rhs.m_Interface)
{
	rhs.m_Interface = nullptr;
}
MicroFlakeX::MLock::MLock(const MLock& rhs) noexcept
	: m_Interface(new_mLock())
{
}


MicroFlakeX::MLockHelper::MLockHelper(MLock& rhs, MLockMode mode) noexcept
	: m_Lock(rhs), m_Mode(mode)
{
	if (m_Mode == Write)
	{

	}
	else if (m_Mode == ReadOnly)
	{

	}

	m_Lock.m_Interface->m_write.lock();

}

MicroFlakeX::MLockHelper::~MLockHelper() noexcept
{
	if (m_Mode == Write)
	{

	}
	else if (m_Mode == ReadOnly)
	{

	}

	m_Lock.m_Interface->m_write.unlock();
}




