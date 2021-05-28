#include "pch.h"
#include "MfxBase.h"

using namespace MicroFlakeX;
using namespace __MicroFlakeX;


void* MicroFlakeX::MfxParam::operator new(size_t)
{
	return nullptr;
}

void* MicroFlakeX::MfxParam::operator new[](size_t)
{
	return nullptr;
}

MfxParam::MfxParam()
{
	myReturn = new MfxReturn;
	myUseCount = new int;
	myParam = new std::vector<std::any>;
	myCriticalSection = new CRITICAL_SECTION;

	InitializeCriticalSection(myCriticalSection);
	*myUseCount = 1;
	*myReturn = Mfx_Return_Fine;
}

MicroFlakeX::MfxParam::MfxParam(const MfxParam& rhs)
{
	EnterCriticalSection(rhs.myCriticalSection);

	myCriticalSection = rhs.myCriticalSection;
	myUseCount = rhs.myUseCount;
	myParam = rhs.myParam;
	myReturn = rhs.myReturn;
	(*myUseCount)++;

	LeaveCriticalSection(myCriticalSection);
}

MicroFlakeX::MfxParam::~MfxParam()
{
	EnterCriticalSection(myCriticalSection);
	(*myUseCount)--;
	if (*myUseCount <= 0)
	{
		SafeDelete(myParam);
		SafeDelete(myReturn);
		SafeDelete(myUseCount);
		DeleteCriticalSection(myCriticalSection);
		SafeDelete(myCriticalSection);
	}
	else
	{
		LeaveCriticalSection(myCriticalSection);
	}
}

MfxParam& MicroFlakeX::MfxParam::operator=(const MfxParam& rhs)
{
	EnterCriticalSection(myCriticalSection);
	(*myUseCount)--;
	if (*myUseCount <= 0)
	{
		SafeDelete(myParam);
		SafeDelete(myReturn);
		SafeDelete(myUseCount);
		DeleteCriticalSection(myCriticalSection);
		SafeDelete(myCriticalSection);
	}
	else
	{
		LeaveCriticalSection(myCriticalSection);
	}

	myCriticalSection = rhs.myCriticalSection;

	EnterCriticalSection(myCriticalSection);
	myUseCount = rhs.myUseCount;
	myParam = rhs.myParam;
	myReturn = rhs.myReturn;
	(*myUseCount)++;
	LeaveCriticalSection(myCriticalSection);

	return *this;
}

std::any& MicroFlakeX::MfxParam::operator[](int i)
{
	return (*myParam)[i];
}

bool MicroFlakeX::MfxParam::IsSafe(int i)
{
	return myParam->size() > i;
}

MfxReturn MicroFlakeX::MfxParam::GetReturn()
{
	return *myReturn;
}

MfxReturn MicroFlakeX::MfxParam::GetParamSize()
{
	return myParam->size();
}

MfxReturn MicroFlakeX::MfxParam::SetReturn(MfxReturn set)
{
	MfxReturn ret = *myReturn;
	*myReturn = set;
	return ret;
}



