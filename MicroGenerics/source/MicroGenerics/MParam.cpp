#include "pch.h"

using namespace MicroFlakeX;

M_OBJECT_POOL_ACHIEVE(_MParam_Info);

/********************************************************************************
*
*********************************************************************************/
MicroFlakeX::MParamOnce::MParamOnce() noexcept
	: m_AnyList(), m_ParamCount(0)
{
}
MicroFlakeX::MParamOnce::~MParamOnce() noexcept
{
}

MicroFlakeX::MInt8U MicroFlakeX::MParamOnce::GetSize() const noexcept
{
	return m_ParamCount;
}

void* MicroFlakeX::MParamOnce::GetPoint(const MInt8U num) const noexcept
{
	return m_AnyList[num];
}

/********************************************************************************
*
*********************************************************************************/
MicroFlakeX::MParamOnce::MParamOnce(MParamOnce&& rhs) noexcept
	: MParamOnce()
{
	m_ParamCount = rhs.m_ParamCount;
	for (auto i = 0; i < m_ParamCount; i++)
	{
		m_AnyList[i] = rhs.m_AnyList[i];
	}
}
MicroFlakeX::MParamOnce::MParamOnce(const MParamOnce& rhs) noexcept
	: MParamOnce()
{
	m_ParamCount = rhs.m_ParamCount;
	for (auto i = 0; i < m_ParamCount; i++)
	{
		m_AnyList[i] = rhs.m_AnyList[i];
	}
}


MicroFlakeX::MParamOnce::MParamOnce(MParamRefer&& rhs) noexcept
	: MParamOnce()
{
	m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_ParamCount; i++)
	{
		m_AnyList[i] = rhs.m_Info->m_AnyList[i].GetPoint();
	}
}
MicroFlakeX::MParamOnce::MParamOnce(const MParamRefer& rhs) noexcept
	: MParamOnce()
{
	m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_ParamCount; i++)
	{
		m_AnyList[i] = rhs.m_Info->m_AnyList[i].GetPoint();
	}

}


MicroFlakeX::MParamOnce::MParamOnce(MParamAsync&& rhs) noexcept
	: MParamOnce()
{
	m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_ParamCount; i++)
	{
		m_AnyList[i] = rhs.m_Info->m_AnyList[i].GetPoint();
	}
}
MicroFlakeX::MParamOnce::MParamOnce(const MParamAsync& rhs) noexcept
	: MParamOnce()
{
	m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_ParamCount; i++)
	{
		m_AnyList[i] = rhs.m_Info->m_AnyList[i].GetPoint();
	}
}
/********************************************************************************
*
*********************************************************************************/
MParamOnce& MicroFlakeX::MParamOnce::operator=(MParamOnce&& rhs) noexcept
{
	m_ParamCount = rhs.m_ParamCount;
	for (auto i = 0; i < m_ParamCount; i++)
	{
		m_AnyList[i] = rhs.m_AnyList[i];
	}
	return *this;
}
MParamOnce& MicroFlakeX::MParamOnce::operator=(const MParamOnce& rhs) noexcept
{
	m_ParamCount = rhs.m_ParamCount;
	for (auto i = 0; i < m_ParamCount; i++)
	{
		m_AnyList[i] = rhs.m_AnyList[i];
	}
	return *this;

}


MicroFlakeX::MParamOnce& MicroFlakeX::MParamOnce::operator=(MParamRefer&& rhs) noexcept
{
	m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_ParamCount; i++)
	{
		m_AnyList[i] = rhs.m_Info->m_AnyList[i].GetPoint();
	}
	return *this;
}
MicroFlakeX::MParamOnce& MicroFlakeX::MParamOnce::operator=(const MParamRefer& rhs) noexcept
{
	m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_ParamCount; i++)
	{
		m_AnyList[i] = rhs.m_Info->m_AnyList[i].GetPoint();
	}
	return *this;
}


MicroFlakeX::MParamOnce& MicroFlakeX::MParamOnce::operator=(MParamAsync&& rhs) noexcept
{
	m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_ParamCount; i++)
	{
		m_AnyList[i] = rhs.m_Info->m_AnyList[i].GetPoint();
	}
	return *this;
}
MicroFlakeX::MParamOnce& MicroFlakeX::MParamOnce::operator=(const MParamAsync& rhs) noexcept
{
	m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_ParamCount; i++)
	{
		m_AnyList[i] = rhs.m_Info->m_AnyList[i].GetPoint();
	}
	return *this;
}









/********************************************************************************
*
*********************************************************************************/
MicroFlakeX::MParamRefer::MParamRefer() noexcept
	: m_Info(new_MParam_Info())
{
	m_Info->m_UseCount = 1;
	m_Info->m_ParamCount = 0;
}
MicroFlakeX::MParamRefer::~MParamRefer() noexcept
{
	del_MParam_Info(m_Info);
	m_Info = nullptr;
}

MicroFlakeX::MInt8U MicroFlakeX::MParamRefer::GetSize() const noexcept
{
	return m_Info->m_ParamCount;
}

void* MicroFlakeX::MParamRefer::GetPoint(const MInt8U num) const noexcept
{
	return m_Info->m_AnyList[num].GetPoint();
}
/********************************************************************************
*
*********************************************************************************/
MicroFlakeX::MParamRefer::MParamRefer(MParamOnce&& rhs) noexcept
	: MParamRefer()
{
	m_Info->m_ParamCount = rhs.m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].EmplaceCopy(rhs.m_AnyList[i]);
	}
}
MicroFlakeX::MParamRefer::MParamRefer(const MParamOnce& rhs) noexcept
	: MParamRefer()
{
	m_Info->m_ParamCount = rhs.m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].EmplaceCopy(rhs.m_AnyList[i]);
	}
}

MicroFlakeX::MParamRefer::MParamRefer(MParamRefer&& rhs) noexcept
	: MParamRefer()
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i] = std::move(rhs.m_Info->m_AnyList[i]);
	}
	rhs.m_Info->m_ParamCount = 0;
}
MicroFlakeX::MParamRefer::MParamRefer(const MParamRefer& rhs) noexcept
	: MParamRefer()
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i] = rhs.m_Info->m_AnyList[i];
	}
}


MicroFlakeX::MParamRefer::MParamRefer(MParamAsync&& rhs) noexcept
	: MParamRefer()
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].RenewAnyCite(rhs.m_Info->m_AnyList[i]);
	}
}
MicroFlakeX::MParamRefer::MParamRefer(const MParamAsync& rhs) noexcept
	: MParamRefer()
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].RenewAnyCite(rhs.m_Info->m_AnyList[i]);
	}
}

/********************************************************************************
*
*********************************************************************************/
MicroFlakeX::MParamRefer& MicroFlakeX::MParamRefer::operator=(MParamOnce&& rhs) noexcept
{
	m_Info->m_ParamCount = rhs.m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].EmplaceCopy(rhs.m_AnyList[i]);
	}
	return *this;
}
MicroFlakeX::MParamRefer& MicroFlakeX::MParamRefer::operator=(const MParamOnce& rhs) noexcept
{
	m_Info->m_ParamCount = rhs.m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].EmplaceCopy(rhs.m_AnyList[i]);
	}
	return *this;
}


MicroFlakeX::MParamRefer& MicroFlakeX::MParamRefer::operator=(MParamRefer&& rhs) noexcept
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i] = std::move(rhs.m_Info->m_AnyList[i]);
	}
	rhs.m_Info->m_ParamCount = 0;
	return *this;
}
MicroFlakeX::MParamRefer& MicroFlakeX::MParamRefer::operator=(const MParamRefer& rhs) noexcept
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i] = rhs.m_Info->m_AnyList[i];
	}
	return *this;
}



MicroFlakeX::MParamRefer& MicroFlakeX::MParamRefer::operator=(MParamAsync&& rhs) noexcept
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].RenewAnyCite(rhs.m_Info->m_AnyList[i]);
	}
	return *this;
}
MicroFlakeX::MParamRefer& MicroFlakeX::MParamRefer::operator=(const MParamAsync& rhs) noexcept
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].RenewAnyCite(rhs.m_Info->m_AnyList[i]);
	}
	return *this;
}


/********************************************************************************
*
*********************************************************************************/
MicroFlakeX::MParamAsync::MParamAsync() noexcept
	: m_Info(new_MParam_Info())
{
	m_Info->m_UseCount = 1;
	m_Info->m_ParamCount = 0;
}
MicroFlakeX::MParamAsync::~MParamAsync() noexcept
{
	Release();
}

MicroFlakeX::MInt8U MicroFlakeX::MParamAsync::GetSize() const noexcept
{
	return m_Info ? m_Info->m_ParamCount : 0;
}

void* MicroFlakeX::MParamAsync::GetPoint(const MInt8U num) const noexcept
{
	return m_Info ? m_Info->m_AnyList[num].GetPoint() : nullptr;
}

bool MicroFlakeX::MParamAsync::Release() noexcept
{
	if (m_Info)
	{
		if (--m_Info->m_UseCount <= 0)
		{
			del_MParam_Info(m_Info);
			m_Info = nullptr;
		}
	}
	return true;
}

/********************************************************************************
*
*********************************************************************************/
MicroFlakeX::MParamAsync::MParamAsync(MParamOnce&& rhs) noexcept
	: MParamAsync()
{
	//m_Info = new __GMSmartParam_Info;
	m_Info->m_ParamCount = rhs.m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].EmplaceCopy(rhs.m_AnyList[i]);
	}
}
MicroFlakeX::MParamAsync::MParamAsync(const MParamOnce& rhs) noexcept
	: MParamAsync()
{
	//m_Info = new __GMSmartParam_Info;
	m_Info->m_ParamCount = rhs.m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].EmplaceCopy(rhs.m_AnyList[i]);
	}
}

MicroFlakeX::MParamAsync::MParamAsync(MParamRefer&& rhs) noexcept
	: MParamAsync()
{
	//m_Info = new __GMSmartParam_Info;
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].RenewAnyCopy(rhs.m_Info->m_AnyList[i]);
	}
}
MicroFlakeX::MParamAsync::MParamAsync(const MParamRefer& rhs) noexcept
	: MParamAsync()
{
	//m_Info = new __GMSmartParam_Info;
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].RenewAnyCopy(rhs.m_Info->m_AnyList[i]);
	}
}




MicroFlakeX::MParamAsync::MParamAsync(MParamAsync&& rhs) noexcept
	: MParamAsync()
{
	Release();
	m_Info = rhs.m_Info;
	rhs.m_Info = nullptr;
}
MicroFlakeX::MParamAsync::MParamAsync(const MParamAsync& rhs) noexcept
	: MParamAsync()
{
	Release();
	m_Info = rhs.m_Info;
	m_Info ? m_Info->m_UseCount++ : 0;
}

/********************************************************************************
*
*********************************************************************************/
MicroFlakeX::MParamAsync& MicroFlakeX::MParamAsync::operator=(MParamOnce&& rhs) noexcept
{
	m_Info->m_ParamCount = rhs.m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].EmplaceCopy(rhs.m_AnyList[i]);
	}
	return *this;
}
MicroFlakeX::MParamAsync& MicroFlakeX::MParamAsync::operator=(const MParamOnce& rhs) noexcept
{
	m_Info->m_ParamCount = rhs.m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].EmplaceCopy(rhs.m_AnyList[i]);
	}
	return *this;
}


MicroFlakeX::MParamAsync& MicroFlakeX::MParamAsync::operator=(MParamRefer&& rhs) noexcept
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].RenewAnyCopy(rhs.m_Info->m_AnyList[i]);
	}
	return *this;
}
MicroFlakeX::MParamAsync& MicroFlakeX::MParamAsync::operator=(const MParamRefer& rhs) noexcept
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].RenewAnyCopy(rhs.m_Info->m_AnyList[i]);
	}
	return *this;
}


MicroFlakeX::MParamAsync& MicroFlakeX::MParamAsync::operator=(MParamAsync&& rhs) noexcept
{
	Release();
	m_Info = rhs.m_Info;
	rhs.m_Info = nullptr;
	return *this;
}
MicroFlakeX::MParamAsync& MicroFlakeX::MParamAsync::operator=(const MParamAsync& rhs) noexcept
{
	Release();
	m_Info = rhs.m_Info;
	m_Info ? m_Info->m_UseCount++ : 0;
	return *this;
}


/********************************************************************************
*
*********************************************************************************/