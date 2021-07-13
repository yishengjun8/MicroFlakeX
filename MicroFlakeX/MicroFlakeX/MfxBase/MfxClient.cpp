#include "pch.h"
#include "MfxBase.h"


MicroFlakeX::MfxClient::MfxClient()
{
	MfxClient_Vector.push_back(this);
}

MicroFlakeX::MfxClient::MfxClient(const MfxClient& rhs)
{
	MfxClient_Vector.push_back(this);

	for (auto iter = rhs.myReceiver.begin(); iter != rhs.myReceiver.end(); iter++)
	{
		myReceiver.push_back(*iter);
	}
}

void MicroFlakeX::MfxClient::ReceiverDelete(MfxBase* recvObject)
{
	for (auto i = MfxClient_Vector.begin(); i != MfxClient_Vector.end(); i++)
	{
		(*i)->RemoveReceiver(recvObject);
	}
}

MicroFlakeX::MfxClient::~MfxClient()
{
	for (auto i = MfxClient_Vector.begin(); i != MfxClient_Vector.end(); i++)
	{
		if (*i == this)
		{
			MfxClient_Vector.erase(i);
			break;
		}
	}
}

void MicroFlakeX::MfxClient::RemoveReceiver(MfxBase* recvObject)
{
	for (auto iter = myReceiver.begin(); iter != myReceiver.end(); iter++)
	{
		if ((*iter) == recvObject)
		{
			myReceiver.erase(iter);
			return;
		}
	}
}

void MicroFlakeX::MfxClient::PushBackReceiver(MfxBase* recvObject)
{
	myReceiver.push_back(recvObject);
}

void MicroFlakeX::MfxClient::PushFrontReceiver(MfxBase* recvObject)
{
	myReceiver.push_front(recvObject);
}
