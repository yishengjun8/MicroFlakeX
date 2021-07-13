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
	myPVOID = new PVOID;
	myUseCount = new INT32;
	myReturn = new MfxReturn;
	myMessage = new MfxMessage;
	myParam = new std::vector<std::any>;

	*myPVOID = nullptr;
	*myUseCount = 1;
	*myMessage = 0;
	*myReturn = MfxReturn_Unknow;
}

MicroFlakeX::MfxParam::MfxParam(PVOID pvoid)
{
	myPVOID = new PVOID;
	myUseCount = new INT32;
	myReturn = new MfxReturn;
	myMessage = new MfxMessage;
	myParam = new std::vector<std::any>;

	*myPVOID = pvoid;
	*myUseCount = 1;
	*myMessage = 0;
	*myReturn = MfxReturn_Unknow;
}

MicroFlakeX::MfxParam::MfxParam(MfxMessage msg)
{
	myPVOID = new PVOID;
	myUseCount = new INT32;
	myReturn = new MfxReturn;
	myMessage = new MfxMessage;
	myParam = new std::vector<std::any>;

	*myPVOID = nullptr;
	*myUseCount = 1;
	*myMessage = msg;
	*myReturn = MfxReturn_Unknow;
}

MicroFlakeX::MfxParam::MfxParam(const MfxParam& rhs)
{
	myPVOID = rhs.myPVOID;
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
		SafeDelete(myPVOID);
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
		SafeDelete(myPVOID);
		SafeDelete(myParam);
		SafeDelete(myReturn);
		SafeDelete(myMessage);
		SafeDelete(myUseCount);
	}

	myPVOID = rhs.myPVOID;
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

PVOID MicroFlakeX::MfxParam::GetPVOID()
{
	return *myPVOID;
}

MfxReturn MicroFlakeX::MfxParam::GetRETURN()
{
	return *myReturn;
}

MfxMessage MicroFlakeX::MfxParam::GetMESSAGE()
{
	return *myMessage;
}

PVOID MicroFlakeX::MfxParam::SetPVOID(PVOID set)
{
	PVOID ret = myPVOID;
	*myPVOID = set;
	return ret;
}

MfxReturn MicroFlakeX::MfxParam::SetRETURN(MfxReturn set)
{
	MfxReturn ret = *myReturn;
	*myReturn = set;
	return ret;
}

MfxMessage MicroFlakeX::MfxParam::SetMESSAGE(MfxMessage set)
{
	MfxMessage ret = *myMessage;
	*myMessage = set;
	return ret;
}



