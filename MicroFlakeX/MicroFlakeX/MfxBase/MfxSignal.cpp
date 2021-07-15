#include "pch.h"
#include "MfxBase.h"

MicroFlakeX::MfxSignal::MfxSignal()
{
	MfxSignal_Vector.push_back(this);
}

MicroFlakeX::MfxSignal::MfxSignal(const MfxSignal& rhs)
{
	MfxSignal_Vector.push_back(this);

	for (auto iter = rhs.myReceiver.begin(); iter != rhs.myReceiver.end(); iter++)
	{
		myReceiver.push_back(*iter);
	}
}

void MicroFlakeX::MfxSignal::ReceiverDelete(MfxBase* recvObject)
{
	for (auto i = MfxSignal_Vector.begin(); i != MfxSignal_Vector.end(); i++)
	{
		(*i)->RemoveReceiver(recvObject);
	}
}

MicroFlakeX::MfxSignal::~MfxSignal()
{
	for (auto i  = MfxSignal_Vector.begin(); i != MfxSignal_Vector.end(); i++)
	{
		if (*i == this)
		{
			MfxSignal_Vector.erase(i);
			break;
		}
	}
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

void MicroFlakeX::MfxSignal::RemoveReceiver(MfxBase* recvObject, MfxStringW recvFunc)
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

void MicroFlakeX::MfxSignal::PushBackReceiver(MfxBase* recvObject, MfxStringW recvFunc)
{
	myReceiver.push_back(MfxReceiver_Info(recvObject, recvFunc));
}

void MicroFlakeX::MfxSignal::PushFrontReceiver(MfxBase* recvObject, MfxStringW recvFunc)
{
	myReceiver.push_front(MfxReceiver_Info(recvObject, recvFunc));
}




