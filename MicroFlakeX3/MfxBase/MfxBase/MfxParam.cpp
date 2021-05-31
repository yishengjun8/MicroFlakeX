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
	myUseCount = new INT32;
	myReturn = new MfxReturn;
	myMessage = new MfxMessage;
	myParam = new std::vector<std::any>;

	*myUseCount = 1;
	*myMessage = 0;
	*myReturn = Mfx_Return_Fine;
}

MicroFlakeX::MfxParam::MfxParam(const MfxParam& rhs)
{
	myParam = rhs.myParam;
	myReturn = rhs.myReturn;
	myMessage = rhs.myMessage;
	myUseCount = rhs.myUseCount;

	(*myUseCount)++;
}

MicroFlakeX::MfxParam::~MfxParam()
{
	(*myUseCount)--;
	if (*myUseCount <= 0)
	{
		SafeDelete(myParam);
		SafeDelete(myReturn);
		SafeDelete(myMessage);
		SafeDelete(myUseCount);
	}
}

MfxParam& MicroFlakeX::MfxParam::operator=(const MfxParam& rhs)
{
	(*myUseCount)--;
	if (*myUseCount <= 0)
	{
		SafeDelete(myParam);
		SafeDelete(myReturn);
		SafeDelete(myMessage);
		SafeDelete(myUseCount);
	}

	myParam = rhs.myParam;
	myReturn = rhs.myReturn;
	myMessage = rhs.myMessage;
	myUseCount = rhs.myUseCount;

	(*myUseCount)++;

	return *this;
}

std::any& MicroFlakeX::MfxParam::operator[](int i)
{
	return (*myParam)[i];
}

bool MicroFlakeX::MfxParam::IsSafe(int i)
{
	return myParam->size() > i && (*this)[i].has_value();
}

MfxNum MicroFlakeX::MfxParam::GetParamSize()
{
	return myParam->size();
}

MfxReturn MicroFlakeX::MfxParam::NowReturn()
{
	return *myReturn;
}

MfxMessage MicroFlakeX::MfxParam::NowMessage()
{
	return *myMessage;
}

MfxReturn MicroFlakeX::MfxParam::SetReturn(MfxReturn set)
{
	MfxReturn ret = *myReturn;
	*myReturn = set;
	return ret;
}

MfxMessage MicroFlakeX::MfxParam::SetMessage(MfxMessage set)
{
	MfxMessage ret = *myMessage;
	*myMessage = set;
	return ret;
}



