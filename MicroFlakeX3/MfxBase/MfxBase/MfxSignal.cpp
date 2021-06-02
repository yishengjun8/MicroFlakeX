#include "pch.h"
#include "MfxBase.h"

using namespace MicroFlakeX;

std::vector<MfxSignal*> MfxSignal_Vector;
CRITICAL_SECTION MfxSignal_Lock;

struct Init
{
	Init()
	{
		InitializeCriticalSection(&MfxSignal_Lock);
	}
	~Init()
	{
		DeleteCriticalSection(&MfxSignal_Lock);
	}
};

Init init;


MicroFlakeX::MfxSignal::MfxSignal()
{
	EnterCriticalSection(&MfxSignal_Lock);
	MfxSignal_Vector.push_back(this);
	LeaveCriticalSection(&MfxSignal_Lock);
}

MicroFlakeX::MfxSignal::MfxSignal(const MfxSignal& rhs)
{
	EnterCriticalSection(&MfxSignal_Lock);
	MfxSignal_Vector.push_back(this);
	LeaveCriticalSection(&MfxSignal_Lock);

	for (auto iter = rhs.myReceiver.begin(); iter != rhs.myReceiver.end(); iter++)
	{
		myReceiver.push_back(*iter);
	}
}

void MicroFlakeX::MfxSignal::ReceiverDelete(MfxBase* recvObject)
{
	EnterCriticalSection(&MfxSignal_Lock);

	for (auto i : MfxSignal_Vector)
	{
		i->RemoveReceiver(recvObject);
	}

	LeaveCriticalSection(&MfxSignal_Lock);
}

MicroFlakeX::MfxSignal::~MfxSignal()
{
	EnterCriticalSection(&MfxSignal_Lock);
	for (auto i  = MfxSignal_Vector.begin(); i != MfxSignal_Vector.end(); i++)
	{
		if (*i == this)
		{
			MfxSignal_Vector.erase(i);
			break;
		}
	}
	LeaveCriticalSection(&MfxSignal_Lock);
}

void MicroFlakeX::MfxSignal::RemoveReceiver(MfxBase* recvObject)
{
	for (auto iter = myReceiver.begin(); iter != myReceiver.end(); iter++)
	{
		if ((*iter).recvObject == recvObject)
		{
			myReceiver.erase(iter);
			return;
		}
	}
}

void MicroFlakeX::MfxSignal::RemoveReceiver(MfxBase* recvObject, MfxString recvFunc)
{
	for (auto iter = myReceiver.begin(); iter != myReceiver.end(); iter++)
	{
		if ((*iter).recvObject == recvObject && (*iter).recvFunc == recvFunc)
		{
			myReceiver.erase(iter);
			return;
		}
	}
}

void MicroFlakeX::MfxSignal::PushBackReceiver(MfxBase* recvObject, MfxString recvFunc)
{
	myReceiver.push_back(MfxReceiver_Info(recvObject, recvFunc));
}

void MicroFlakeX::MfxSignal::PushFrontReceiver(MfxBase* recvObject, MfxString recvFunc)
{
	myReceiver.push_front(MfxReceiver_Info(recvObject, recvFunc));
}