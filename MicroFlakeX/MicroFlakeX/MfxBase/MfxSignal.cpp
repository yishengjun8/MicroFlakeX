#include "pch.h"
#include "MfxBase.h"

MicroFlakeX::MfxSignal_Link::MfxSignal_Link()
{
	MfxSignal_Link_Vector.push_back(this);
}

MicroFlakeX::MfxSignal_Link::MfxSignal_Link(const MfxSignal_Link& rhs)
{
	MfxSignal_Link_Vector.push_back(this);

	for (auto iter = rhs.myReceiver.begin(); iter != rhs.myReceiver.end(); iter++)
	{
		myReceiver.push_back(*iter);
	}
}

void MicroFlakeX::MfxSignal_Link::ReceiverDelete(pMfxBase recvObject)
{
	for (auto i = MfxSignal_Link_Vector.begin(); i != MfxSignal_Link_Vector.end(); i++)
	{
		(*i)->RemoveReceiver(recvObject);
	}
}

MicroFlakeX::MfxSignal_Link::~MfxSignal_Link()
{
	for (auto i  = MfxSignal_Link_Vector.begin(); i != MfxSignal_Link_Vector.end(); i++)
	{
		if (*i == this)
		{
			MfxSignal_Link_Vector.erase(i);
			break;
		}
	}
}

void MicroFlakeX::MfxSignal_Link::RemoveReceiver(pMfxBase recvObject)
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

void MicroFlakeX::MfxSignal_Link::RemoveReceiver(pMfxBase recvObject, MfxString recvFunc)
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

void MicroFlakeX::MfxSignal_Link::PushBackReceiver(pMfxBase recvObject, MfxString recvFunc)
{
	myReceiver.push_back(MfxReceiver_Info(recvObject, recvFunc));
}

void MicroFlakeX::MfxSignal_Link::PushFrontReceiver(pMfxBase recvObject, MfxString recvFunc)
{
	myReceiver.push_front(MfxReceiver_Info(recvObject, recvFunc));
}





/*------------------------------------------------------------------------------*/






MicroFlakeX::MfxSignal_UnLink::MfxSignal_UnLink()
{
	MfxSignal_UnLink_Vector.push_back(this);
}

MicroFlakeX::MfxSignal_UnLink::MfxSignal_UnLink(const MfxSignal_UnLink& rhs)
{
	MfxSignal_UnLink_Vector.push_back(this);

	for (auto iter = rhs.myReceiver.begin(); iter != rhs.myReceiver.end(); iter++)
	{
		myReceiver.push_back(*iter);
	}
}

void MicroFlakeX::MfxSignal_UnLink::ReceiverDelete(pMfxBase recvObject)
{
	for (auto i = MfxSignal_UnLink_Vector.begin(); i != MfxSignal_UnLink_Vector.end(); i++)
	{
		(*i)->RemoveReceiver(recvObject);
	}
}

MicroFlakeX::MfxSignal_UnLink::~MfxSignal_UnLink()
{
	for (auto i = MfxSignal_UnLink_Vector.begin(); i != MfxSignal_UnLink_Vector.end(); i++)
	{
		if (*i == this)
		{
			MfxSignal_UnLink_Vector.erase(i);
			break;
		}
	}
}

void MicroFlakeX::MfxSignal_UnLink::RemoveReceiver(pMfxBase recvObject)
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

void MicroFlakeX::MfxSignal_UnLink::PushBackReceiver(pMfxBase recvObject)
{
	myReceiver.push_back(recvObject);
}

void MicroFlakeX::MfxSignal_UnLink::PushFrontReceiver(pMfxBase recvObject)
{
	myReceiver.push_front(recvObject);
}
