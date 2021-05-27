#include "pch.h"
#include "MfxBase.h"

using namespace MicroFlakeX;


void MicroFlakeX::MfxSignal::RemoveReceiver(MfxBase* recvObject, MfxString recvFunc)
{
	for (auto iter = myReceiver.begin(); iter != myReceiver.end(); iter++)
	{
		if ((*iter)->recvObject == recvObject && (*iter)->recvFunc == recvFunc)
		{
			delete *iter;
			myReceiver.erase(iter);
			return;
		}
	}
}

void MicroFlakeX::MfxSignal::PushBackReceiver(MfxBase* recvObject, MfxString recvFunc)
{
	myReceiver.push_back(new MfxReceiver_Info(recvObject, recvFunc));
}

void MicroFlakeX::MfxSignal::PushFrontReceiver(MfxBase* recvObject, MfxString recvFunc)
{
	myReceiver.push_front(new MfxReceiver_Info(recvObject, recvFunc));
}