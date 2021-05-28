#include "pch.h"
#include "MfxBase.h"

using namespace MicroFlakeX;


MicroFlakeX::MfxSignal::MfxSignal(const MfxSignal& rhs)
{
	for (auto iter = rhs.myReceiver.begin(); iter != rhs.myReceiver.end(); iter++)
	{
		myReceiver.push_back(*iter);
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