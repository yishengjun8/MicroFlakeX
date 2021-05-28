#include "pch.h"
#include "MfxBase.h"

using namespace MicroFlakeX;
using namespace __MicroFlakeX;

struct MfxWork_AutoFunc
{
	MfxWork_AutoFunc(MfxBase* obj, MfxString recv, MfxParam& mParam)
	{
		delay = 0;
		object = obj;
		recvFunc = recv;

		myParam = mParam;
	}
	int delay;
	MfxBase* object;
	MfxString recvFunc;

	MfxParam myParam;
};

struct MfxWork_Widel
{
	MfxWork_Widel(pThreadFunc& func, MfxParam& mParam)
	{
		myParam = mParam;
		mypThreadFunc = func;
	}
	MfxParam myParam;
	pThreadFunc mypThreadFunc;
};



std::map<PTP_TIMER, MfxWork_AutoFunc*> MfxThreadServerMap;
typedef std::map<PTP_TIMER, MfxWork_AutoFunc*>::value_type MfxThreadServerMap_Elem;


MfxReturn MicroFlakeX::MfxBeginNewThread(MfxBase* object, MfxString recvFunc, MfxParam myParam)
{
	MfxWork_AutoFunc* tWork = new MfxWork_AutoFunc(object, recvFunc, myParam);

	/**
	MfxCout << std::endl;
	MfxCout << MfxText("<MfxBeginNewThread> [NowTime: ") << clock();
	MfxCout << MfxText(" ] WPARAM: ") << wParam;
	MfxCout << MfxText(" LPARAM: ") << lParam;
	MfxCout << std::endl;
	/**/

	return TrySubmitThreadpoolCallback(&MfxThreadCallBack, tWork, NULL) ? Mfx_Return_Fine : Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxBeginNewThread_Widely(pThreadFunc pThreadFunc, MfxParam mParam)
{
	MfxWork_Widel* tWork = new MfxWork_Widel(pThreadFunc, mParam);

	return TrySubmitThreadpoolCallback(&MfxThreadCallBack_Widely, tWork, NULL) ? Mfx_Return_Fine : Mfx_Return_Fail;
}



MfxReturn MicroFlakeX::MfxBeginNewTimer(PTP_TIMER& pTimer, MfxBase* object, MfxString recvFunc, MfxParam mParam, DWORD delay, LONGLONG begin, DWORD randTime)
{
	
	MfxWork_AutoFunc* tWork = new MfxWork_AutoFunc(object, recvFunc, mParam);

	pTimer = CreateThreadpoolTimer(&MfxTimerCallBack, tWork, NULL);

	ULARGE_INTEGER tWinTime;
	tWinTime.QuadPart = (LONGLONG) - begin;

	FILETIME tStarTime;
	tStarTime.dwLowDateTime = tWinTime.LowPart;
	tStarTime.dwHighDateTime = tWinTime.HighPart;

	tWork->delay = delay;

	SetThreadpoolTimer(pTimer, &tStarTime, delay, randTime);

	MfxThreadServerMap.insert(MfxThreadServerMap_Elem(pTimer, tWork));

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxCloseTimer(PTP_TIMER& pTimer)
{
	CloseThreadpoolTimer(pTimer);

	auto tFind = MfxThreadServerMap.find(pTimer);
	if(tFind != MfxThreadServerMap.end())
	{
		delete tFind->second;
		MfxThreadServerMap.erase(tFind);
	}

	return Mfx_Return_Fine;
}

VOID CALLBACK __MicroFlakeX::MfxThreadCallBack(PTP_CALLBACK_INSTANCE instance, PVOID val)
{
	MfxWork_AutoFunc* tWork = (MfxWork_AutoFunc*)val;
	tWork->object->AutoFunc(tWork->recvFunc, tWork->myParam);

	delete tWork;
}

VOID CALLBACK __MicroFlakeX::MfxThreadCallBack_Widely(PTP_CALLBACK_INSTANCE instance, PVOID val)
{
	MfxWork_Widel* tWork = (MfxWork_Widel*)val;
	tWork->mypThreadFunc(tWork->myParam);

	delete tWork;
}



VOID CALLBACK __MicroFlakeX::MfxTimerCallBack(PTP_CALLBACK_INSTANCE instance, PVOID val, PTP_TIMER pTimer)
{
	MfxWork_AutoFunc* tWork = (MfxWork_AutoFunc*)val;
	tWork->object->AutoFunc(tWork->recvFunc, tWork->myParam);

	if (tWork->delay == 0)
	{
		auto tFind = MfxThreadServerMap.find(pTimer);
		if (tFind != MfxThreadServerMap.end())
		{
			delete tFind->second;
			MfxThreadServerMap.erase(tFind);
		}
	}
}
