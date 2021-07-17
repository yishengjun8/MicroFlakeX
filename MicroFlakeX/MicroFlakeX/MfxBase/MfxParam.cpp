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
	myPVOID = nullptr;
	myReturn = nullptr;
	myMessage = nullptr;
	myStringA = nullptr;
	myStringW = nullptr;

	myUseCount = new INT32{ 1 };
	myParam = new std::vector<std::any>;
}

MicroFlakeX::MfxParam::MfxParam(PVOID pvoid) : MfxParam()
{
	myPVOID = new PVOID{ pvoid };
}

MicroFlakeX::MfxParam::MfxParam(MfxMessage msg) : MfxParam()
{
	myMessage = new MfxMessage{ msg };
}

MicroFlakeX::MfxParam::MfxParam(MfxStringA str) : MfxParam()
{
	myStringA = new MfxStringA(str);
}

MicroFlakeX::MfxParam::MfxParam(MfxStringW str) : MfxParam()
{
	myStringW = new MfxStringW(str);
}

MicroFlakeX::MfxParam::MfxParam(const MfxParam& rhs)
{
	myPVOID = rhs.myPVOID;
	myReturn = rhs.myReturn;
	myMessage = rhs.myMessage;
	myStringA = rhs.myStringA;
	myStringW = rhs.myStringW;

	myParam = rhs.myParam;
	myUseCount = rhs.myUseCount;

	(*myUseCount)++;
}

void MicroFlakeX::MfxParam::Release()
{
	(*myUseCount)--;
	if (*myUseCount <= 0)
	{
		SafeDelete(myPVOID);
		SafeDelete(myReturn);
		SafeDelete(myMessage);
		SafeDelete(myStringA);
		SafeDelete(myStringW);

		SafeDelete(myParam);
		SafeDelete(myUseCount);
	}
}

MicroFlakeX::MfxParam::~MfxParam()
{
	this->Release();
}

MfxParam& MicroFlakeX::MfxParam::operator=(const MfxParam& rhs)
{
	this->Release();

	myPVOID = rhs.myPVOID;
	myReturn = rhs.myReturn;
	myMessage = rhs.myMessage;
	myStringA = rhs.myStringA;
	myStringW = rhs.myStringW;

	myParam = rhs.myParam;
	myUseCount = rhs.myUseCount;

	(*myUseCount)++;

	return *this;
}

std::any& MicroFlakeX::MfxParam::operator[](const int i)
{
	return (*myParam)[i];
}

bool MicroFlakeX::MfxParam::IsSafe(const int i)
{
	return myParam->size() > i && (*this)[i].has_value();
}

MfxNum MicroFlakeX::MfxParam::GetParamSize()
{
	return myParam->size();
}

bool MicroFlakeX::MfxParam::IsPVOID()
{
	return myPVOID;
}

bool MicroFlakeX::MfxParam::IsRETURN()
{
	return myReturn;
}

bool MicroFlakeX::MfxParam::IsMESSAGE()
{
	return myMessage;
}

bool MicroFlakeX::MfxParam::IsSTRINGA()
{
	return myStringA;
}

bool MicroFlakeX::MfxParam::IsSTRINGW()
{
	return myStringW;
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

MfxStringA MicroFlakeX::MfxParam::GetSTRINGA()
{
	return *myStringA;
}

MfxStringW MicroFlakeX::MfxParam::GetSTRINGW()
{
	return *myStringW;
}

MfxParam& MicroFlakeX::MfxParam::SetPVOID(const PVOID set)
{
	if (myPVOID)
	{
		*myPVOID = set;
	}
	else
	{
		myPVOID = new PVOID{ set };
	}
	
	return *this;
}

MfxParam& MicroFlakeX::MfxParam::SetRETURN(const MfxReturn set)
{
	if (myReturn)
	{
		*myReturn = set;
	}
	else
	{
		myReturn = new MfxReturn{ set };
	}

	return *this;
}

MfxParam& MicroFlakeX::MfxParam::SetMESSAGE(const MfxMessage set)
{
	if (myReturn)
	{
		*myMessage = set;
	}
	else
	{
		myMessage = new MfxMessage{ set };
	}

	return *this;
}

MfxParam& MicroFlakeX::MfxParam::SetSTRINGA(const MfxStringA set)
{
	if (myStringA)
	{
		*myStringA = set;
	}
	else
	{
		myStringA = new MfxStringA(set);
	}

	return *this;
}

MfxParam& MicroFlakeX::MfxParam::SetSTRINGW(const MfxStringW set)
{
	if (myStringW)
	{
		*myStringW = set;
	}
	else
	{
		myStringW = new MfxStringW(set);
	}

	return *this;
}



