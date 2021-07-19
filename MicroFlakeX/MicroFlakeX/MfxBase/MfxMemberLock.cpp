#include "pch.h"
#include "MfxBase.h"

using namespace MicroFlakeX;
using namespace MicroFlakeX;


bool MicroFlakeX::MfxMemberLock::InsertMemberLock(void* resour)
{
	myMutexResour.insert(myResour(resour, CRITICAL_SECTION()));

	InitializeCriticalSection(&myMutexResour[resour]);

	return true;
}

bool MicroFlakeX::MfxMemberLock::TryLock(void* first)
{
	bool ret = false;
	auto tFind = myMutexResour.find(const_cast<void*>(first));
	if (tFind == myMutexResour.end())
	{
		InsertMemberLock(const_cast<void*>(first));
		ret = TryEnterCriticalSection(&myMutexResour[const_cast<void*>(first)]);
	}
	else
	{
		ret = TryEnterCriticalSection(&tFind->second);
	}

	return ret;
}

bool MicroFlakeX::MfxMemberLock::UnLock(void* first)
{
	auto tFind = myMutexResour.find(const_cast<void*>(first));
	if (tFind == myMutexResour.end())
	{
		InsertMemberLock(const_cast<void*>(first));
	}
	else
	{
		LeaveCriticalSection(&myMutexResour[const_cast<void*>(first)]);
	}

	return true;
}

MicroFlakeX::MfxMemberLock::~MfxMemberLock()
{
	for (auto iter : myMutexResour)
	{
		DeleteCriticalSection(&iter.second);
	}
}