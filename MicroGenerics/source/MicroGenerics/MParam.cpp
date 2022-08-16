#include "pch.h"

using namespace MicroFlakeX;

M_OBJECT_POOL_ACHIEVE(_MParam_Info);

/********************************************************************************
*
*********************************************************************************/
MicroFlakeX::MTempParam::MTempParam() noexcept
	: m_AnyList(), m_ParamCount(0)
{
}
MicroFlakeX::MTempParam::~MTempParam() noexcept
{
}

MicroFlakeX::MInt8_U MicroFlakeX::MTempParam::GetSize() const noexcept
{
	return m_ParamCount;
}

void* MicroFlakeX::MTempParam::GetPoint(const MInt8_U num) const noexcept
{
	return m_AnyList[num];
}

/********************************************************************************
*
*********************************************************************************/
MicroFlakeX::MTempParam::MTempParam(MTempParam&& rhs) noexcept
	: MTempParam()
{
	m_ParamCount = rhs.m_ParamCount;
	for (auto i = 0; i < m_ParamCount; i++)
	{
		m_AnyList[i] = rhs.m_AnyList[i];
	}
}
MicroFlakeX::MTempParam::MTempParam(const MTempParam& rhs) noexcept
	: MTempParam()
{
	m_ParamCount = rhs.m_ParamCount;
	for (auto i = 0; i < m_ParamCount; i++)
	{
		m_AnyList[i] = rhs.m_AnyList[i];
	}
}


MicroFlakeX::MTempParam::MTempParam(MCiteParam&& rhs) noexcept
	: MTempParam()
{
	m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_ParamCount; i++)
	{
		m_AnyList[i] = rhs.m_Info->m_AnyList[i].GetPoint();
	}
}
MicroFlakeX::MTempParam::MTempParam(const MCiteParam& rhs) noexcept
	: MTempParam()
{
	m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_ParamCount; i++)
	{
		m_AnyList[i] = rhs.m_Info->m_AnyList[i].GetPoint();
	}

}


MicroFlakeX::MTempParam::MTempParam(MCopyParam&& rhs) noexcept
	: MTempParam()
{
	m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_ParamCount; i++)
	{
		m_AnyList[i] = rhs.m_Info->m_AnyList[i].GetPoint();
	}
}
MicroFlakeX::MTempParam::MTempParam(const MCopyParam& rhs) noexcept
	: MTempParam()
{
	m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_ParamCount; i++)
	{
		m_AnyList[i] = rhs.m_Info->m_AnyList[i].GetPoint();
	}
}


MicroFlakeX::MTempParam::MTempParam(MSmartParam&& rhs) noexcept
	: MTempParam()
{
	m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_ParamCount; i++)
	{
		m_AnyList[i] = rhs.m_Info->m_AnyList[i].GetPoint();
	}
}
MicroFlakeX::MTempParam::MTempParam(const MSmartParam& rhs) noexcept
	: MTempParam()
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
MTempParam& MicroFlakeX::MTempParam::operator=(MTempParam&& rhs) noexcept
{
	m_ParamCount = rhs.m_ParamCount;
	for (auto i = 0; i < m_ParamCount; i++)
	{
		m_AnyList[i] = rhs.m_AnyList[i];
	}
	return *this;
}
MTempParam& MicroFlakeX::MTempParam::operator=(const MTempParam& rhs) noexcept
{
	m_ParamCount = rhs.m_ParamCount;
	for (auto i = 0; i < m_ParamCount; i++)
	{
		m_AnyList[i] = rhs.m_AnyList[i];
	}
	return *this;

}


MicroFlakeX::MTempParam& MicroFlakeX::MTempParam::operator=(MCiteParam&& rhs) noexcept
{
	m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_ParamCount; i++)
	{
		m_AnyList[i] = rhs.m_Info->m_AnyList[i].GetPoint();
	}
	return *this;
}
MicroFlakeX::MTempParam& MicroFlakeX::MTempParam::operator=(const MCiteParam& rhs) noexcept
{
	m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_ParamCount; i++)
	{
		m_AnyList[i] = rhs.m_Info->m_AnyList[i].GetPoint();
	}
	return *this;
}


MicroFlakeX::MTempParam& MicroFlakeX::MTempParam::operator=(MCopyParam&& rhs) noexcept
{
	m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_ParamCount; i++)
	{
		m_AnyList[i] = rhs.m_Info->m_AnyList[i].GetPoint();
	}
	return *this;
}
MicroFlakeX::MTempParam& MicroFlakeX::MTempParam::operator=(const MCopyParam& rhs) noexcept
{
	m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_ParamCount; i++)
	{
		m_AnyList[i] = rhs.m_Info->m_AnyList[i].GetPoint();
	}
	return *this;
}


MicroFlakeX::MTempParam& MicroFlakeX::MTempParam::operator=(MSmartParam&& rhs) noexcept
{
	m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_ParamCount; i++)
	{
		m_AnyList[i] = rhs.m_Info->m_AnyList[i].GetPoint();
	}
	return *this;
}
MicroFlakeX::MTempParam& MicroFlakeX::MTempParam::operator=(const MSmartParam& rhs) noexcept
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
MicroFlakeX::MCiteParam::MCiteParam() noexcept
	: m_Info(new_MParam_Info())
{
	m_Info->m_UseCount = 1;
	m_Info->m_ParamCount = 0;
}
MicroFlakeX::MCiteParam::~MCiteParam() noexcept
{
	del_MParam_Info(m_Info);
	m_Info = nullptr;
}

MicroFlakeX::MInt8_U MicroFlakeX::MCiteParam::GetSize() const noexcept
{
	return m_Info->m_ParamCount;
}

void* MicroFlakeX::MCiteParam::GetPoint(const MInt8_U num) const noexcept
{
	return m_Info->m_AnyList[num].GetPoint();
}
/********************************************************************************
*
*********************************************************************************/
MicroFlakeX::MCiteParam::MCiteParam(MTempParam&& rhs) noexcept
	: MCiteParam()
{
	m_Info->m_ParamCount = rhs.m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].SetCopyValue(rhs.m_AnyList[i]);
	}
}
MicroFlakeX::MCiteParam::MCiteParam(const MTempParam& rhs) noexcept
	: MCiteParam()
{
	m_Info->m_ParamCount = rhs.m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].SetCopyValue(rhs.m_AnyList[i]);
	}
}

MicroFlakeX::MCiteParam::MCiteParam(MCiteParam&& rhs) noexcept
	: MCiteParam()
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i] = std::move(rhs.m_Info->m_AnyList[i]);
	}
	rhs.m_Info->m_ParamCount = 0;
}
MicroFlakeX::MCiteParam::MCiteParam(const MCiteParam& rhs) noexcept
	: MCiteParam()
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i] = rhs.m_Info->m_AnyList[i];
	}
}


MicroFlakeX::MCiteParam::MCiteParam(MCopyParam&& rhs) noexcept
	: MCiteParam()
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].MakeValue_Cite(rhs.m_Info->m_AnyList[i]);
	}
}
MicroFlakeX::MCiteParam::MCiteParam(const MCopyParam& rhs) noexcept
	: MCiteParam()
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].MakeValue_Cite(rhs.m_Info->m_AnyList[i]);
	}
}


MicroFlakeX::MCiteParam::MCiteParam(MSmartParam&& rhs) noexcept
	: MCiteParam()
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].MakeValue_Cite(rhs.m_Info->m_AnyList[i]);
	}
}
MicroFlakeX::MCiteParam::MCiteParam(const MSmartParam& rhs) noexcept
	: MCiteParam()
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].MakeValue_Cite(rhs.m_Info->m_AnyList[i]);
	}
}

/********************************************************************************
*
*********************************************************************************/
MicroFlakeX::MCiteParam& MicroFlakeX::MCiteParam::operator=(MTempParam&& rhs) noexcept
{
	m_Info->m_ParamCount = rhs.m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].SetCopyValue(rhs.m_AnyList[i]);
	}
	return *this;
}
MicroFlakeX::MCiteParam& MicroFlakeX::MCiteParam::operator=(const MTempParam& rhs) noexcept
{
	m_Info->m_ParamCount = rhs.m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].SetCopyValue(rhs.m_AnyList[i]);
	}
	return *this;
}


MicroFlakeX::MCiteParam& MicroFlakeX::MCiteParam::operator=(MCiteParam&& rhs) noexcept
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i] = std::move(rhs.m_Info->m_AnyList[i]);
	}
	rhs.m_Info->m_ParamCount = 0;
	return *this;
}
MicroFlakeX::MCiteParam& MicroFlakeX::MCiteParam::operator=(const MCiteParam& rhs) noexcept
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i] = rhs.m_Info->m_AnyList[i];
	}
	return *this;
}

MicroFlakeX::MCiteParam& MicroFlakeX::MCiteParam::operator=(MCopyParam&& rhs) noexcept
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].MakeValue_Cite(rhs.m_Info->m_AnyList[i]);
	}
	return *this;
}
MicroFlakeX::MCiteParam& MicroFlakeX::MCiteParam::operator=(const MCopyParam& rhs) noexcept
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].MakeValue_Cite(rhs.m_Info->m_AnyList[i]);
	}
	return *this;
}


MicroFlakeX::MCiteParam& MicroFlakeX::MCiteParam::operator=(MSmartParam&& rhs) noexcept
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].MakeValue_Cite(rhs.m_Info->m_AnyList[i]);
	}
	return *this;
}
MicroFlakeX::MCiteParam& MicroFlakeX::MCiteParam::operator=(const MSmartParam& rhs) noexcept
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].MakeValue_Cite(rhs.m_Info->m_AnyList[i]);
	}
	return *this;
}


/********************************************************************************
*
*********************************************************************************/
/********************************************************************************
*
*********************************************************************************/
MicroFlakeX::MCopyParam::MCopyParam() noexcept
	: m_Info(new_MParam_Info())
{
	m_Info->m_UseCount = 1;
	m_Info->m_ParamCount = 0;
}
MicroFlakeX::MCopyParam::~MCopyParam() noexcept
{
	del_MParam_Info(m_Info);
	m_Info = nullptr;
}

MicroFlakeX::MInt8_U MicroFlakeX::MCopyParam::GetSize() const noexcept
{
	return m_Info->m_ParamCount;
}

void* MicroFlakeX::MCopyParam::GetPoint(const MInt8_U num) const noexcept
{
	return m_Info->m_AnyList[num].GetPoint();
}
/********************************************************************************
*
*********************************************************************************/
MicroFlakeX::MCopyParam::MCopyParam(MTempParam&& rhs) noexcept
	: MCopyParam()
{
	m_Info->m_ParamCount = rhs.m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].SetCopyValue(rhs.m_AnyList[i]);
	}
}
MicroFlakeX::MCopyParam::MCopyParam(const MTempParam& rhs) noexcept
	: MCopyParam()
{
	m_Info->m_ParamCount = rhs.m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].SetCopyValue(rhs.m_AnyList[i]);
	}
}

MicroFlakeX::MCopyParam::MCopyParam(MCiteParam&& rhs) noexcept
	: MCopyParam()
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].MakeValue_Copy(rhs.m_Info->m_AnyList[i]);
	}
}
MicroFlakeX::MCopyParam::MCopyParam(const MCiteParam& rhs) noexcept
	: MCopyParam()
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].MakeValue_Copy(rhs.m_Info->m_AnyList[i]);
	}
}


MicroFlakeX::MCopyParam::MCopyParam(MCopyParam&& rhs) noexcept
	: MCopyParam()
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].MakeValue_Copy(rhs.m_Info->m_AnyList[i]);
	}
}
MicroFlakeX::MCopyParam::MCopyParam(const MCopyParam& rhs) noexcept
	: MCopyParam()
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].MakeValue_Copy(rhs.m_Info->m_AnyList[i]);
	}
}


MicroFlakeX::MCopyParam::MCopyParam(MSmartParam&& rhs) noexcept
	: MCopyParam()
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].MakeValue_Copy(rhs.m_Info->m_AnyList[i]);
	}
}
MicroFlakeX::MCopyParam::MCopyParam(const MSmartParam& rhs) noexcept
	: MCopyParam()
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].MakeValue_Copy(rhs.m_Info->m_AnyList[i]);
	}
}

/********************************************************************************
*
*********************************************************************************/
MicroFlakeX::MCopyParam& MicroFlakeX::MCopyParam::operator=(MTempParam&& rhs) noexcept
{
	m_Info->m_ParamCount = rhs.m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].SetCopyValue(rhs.m_AnyList[i]);
	}
	return *this;
}
MicroFlakeX::MCopyParam& MicroFlakeX::MCopyParam::operator=(const MTempParam& rhs) noexcept
{
	m_Info->m_ParamCount = rhs.m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].SetCopyValue(rhs.m_AnyList[i]);
	}
	return *this;
}


MicroFlakeX::MCopyParam& MicroFlakeX::MCopyParam::operator=(MCiteParam&& rhs) noexcept
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].MakeValue_Copy(rhs.m_Info->m_AnyList[i]);
	}
	return *this;
}
MicroFlakeX::MCopyParam& MicroFlakeX::MCopyParam::operator=(const MCiteParam& rhs) noexcept
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].MakeValue_Copy(rhs.m_Info->m_AnyList[i]);
	}
	return *this;
}

MicroFlakeX::MCopyParam& MicroFlakeX::MCopyParam::operator=(MCopyParam&& rhs) noexcept
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].MakeValue_Copy(rhs.m_Info->m_AnyList[i]);
	}
	return *this;
}
MicroFlakeX::MCopyParam& MicroFlakeX::MCopyParam::operator=(const MCopyParam& rhs) noexcept
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].MakeValue_Copy(rhs.m_Info->m_AnyList[i]);
	}
	return *this;
}


MicroFlakeX::MCopyParam& MicroFlakeX::MCopyParam::operator=(MSmartParam&& rhs) noexcept
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].MakeValue_Copy(rhs.m_Info->m_AnyList[i]);
	}
	return *this;
}
MicroFlakeX::MCopyParam& MicroFlakeX::MCopyParam::operator=(const MSmartParam& rhs) noexcept
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].MakeValue_Copy(rhs.m_Info->m_AnyList[i]);
	}
	return *this;
}


/********************************************************************************
*
*********************************************************************************/
MicroFlakeX::MSmartParam::MSmartParam() noexcept
	: m_Info(new_MParam_Info())
{
	m_Info->m_UseCount = 1;
	m_Info->m_ParamCount = 0;
}
MicroFlakeX::MSmartParam::~MSmartParam() noexcept
{
	Release();
}

MicroFlakeX::MInt8_U MicroFlakeX::MSmartParam::GetSize() const noexcept
{
	return m_Info ? m_Info->m_ParamCount : 0;
}

void* MicroFlakeX::MSmartParam::GetPoint(const MInt8_U num) const noexcept
{
	return m_Info ? m_Info->m_AnyList[num].GetPoint() : nullptr;
}

bool MicroFlakeX::MSmartParam::Release() noexcept
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
MicroFlakeX::MSmartParam::MSmartParam(MTempParam&& rhs) noexcept
	: MSmartParam()
{
	//m_Info = new __GMSmartParam_Info;
	m_Info->m_ParamCount = rhs.m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].SetCopyValue(rhs.m_AnyList[i]);
	}
}
MicroFlakeX::MSmartParam::MSmartParam(const MTempParam& rhs) noexcept
	: MSmartParam()
{
	//m_Info = new __GMSmartParam_Info;
	m_Info->m_ParamCount = rhs.m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].SetCopyValue(rhs.m_AnyList[i]);
	}
}

MicroFlakeX::MSmartParam::MSmartParam(MCiteParam&& rhs) noexcept
	: MSmartParam()
{
	//m_Info = new __GMSmartParam_Info;
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].MakeValue_Copy(rhs.m_Info->m_AnyList[i]);
	}
}
MicroFlakeX::MSmartParam::MSmartParam(const MCiteParam& rhs) noexcept
	: MSmartParam()
{
	//m_Info = new __GMSmartParam_Info;
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].MakeValue_Copy(rhs.m_Info->m_AnyList[i]);
	}
}


MicroFlakeX::MSmartParam::MSmartParam(MCopyParam&& rhs) noexcept
	: MSmartParam()
{
	//m_Info = new __GMSmartParam_Info;
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].MakeValue_Copy(rhs.m_Info->m_AnyList[i]);
	}
}
MicroFlakeX::MSmartParam::MSmartParam(const MCopyParam& rhs) noexcept
	: MSmartParam()
{
	//m_Info = new __GMSmartParam_Info;
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].MakeValue_Copy(rhs.m_Info->m_AnyList[i]);
	}
}

MicroFlakeX::MSmartParam::MSmartParam(MSmartParam&& rhs) noexcept
	: MSmartParam()
{
	Release();
	m_Info = rhs.m_Info;
	rhs.m_Info = nullptr;
}
MicroFlakeX::MSmartParam::MSmartParam(const MSmartParam& rhs) noexcept
	: MSmartParam()
{
	Release();
	m_Info = rhs.m_Info;
	m_Info ? m_Info->m_UseCount++ : 0;
}

/********************************************************************************
*
*********************************************************************************/
MicroFlakeX::MSmartParam& MicroFlakeX::MSmartParam::operator=(MTempParam&& rhs) noexcept
{
	m_Info->m_ParamCount = rhs.m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].SetCopyValue(rhs.m_AnyList[i]);
	}
	return *this;
}
MicroFlakeX::MSmartParam& MicroFlakeX::MSmartParam::operator=(const MTempParam& rhs) noexcept
{
	m_Info->m_ParamCount = rhs.m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].SetCopyValue(rhs.m_AnyList[i]);
	}
	return *this;
}


MicroFlakeX::MSmartParam& MicroFlakeX::MSmartParam::operator=(MCiteParam&& rhs) noexcept
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].MakeValue_Copy(rhs.m_Info->m_AnyList[i]);
	}
	return *this;
}
MicroFlakeX::MSmartParam& MicroFlakeX::MSmartParam::operator=(const MCiteParam& rhs) noexcept
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].MakeValue_Copy(rhs.m_Info->m_AnyList[i]);
	}
	return *this;
}

MicroFlakeX::MSmartParam& MicroFlakeX::MSmartParam::operator=(MCopyParam&& rhs) noexcept
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].MakeValue_Copy(rhs.m_Info->m_AnyList[i]);
	}
	return *this;
}
MicroFlakeX::MSmartParam& MicroFlakeX::MSmartParam::operator=(const MCopyParam& rhs) noexcept
{
	m_Info->m_ParamCount = rhs.m_Info->m_ParamCount;
	for (auto i = 0; i < m_Info->m_ParamCount; i++)
	{
		m_Info->m_AnyList[i].MakeValue_Copy(rhs.m_Info->m_AnyList[i]);
	}
	return *this;
}


MicroFlakeX::MSmartParam& MicroFlakeX::MSmartParam::operator=(MSmartParam&& rhs) noexcept
{
	Release();
	m_Info = rhs.m_Info;
	rhs.m_Info = nullptr;
	return *this;
}
MicroFlakeX::MSmartParam& MicroFlakeX::MSmartParam::operator=(const MSmartParam& rhs) noexcept
{
	Release();
	m_Info = rhs.m_Info;
	m_Info ? m_Info->m_UseCount++ : 0;
	return *this;
}


/********************************************************************************
*
*********************************************************************************/