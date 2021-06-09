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
		delay = 0;

		myParam = mParam;
		mypThreadFunc = func;
	}
	int delay;
	MfxParam myParam;
	pThreadFunc mypThreadFunc;
};

/* 这里需要优化，取消这俩全局变量，但是目前还不知道怎么做 */
std::map<PTP_TIMER, MfxWork_AutoFunc*> MfxThreadServer_Map;
std::map<PTP_TIMER, MfxWork_Widel*> MfxThreadServer_Widel_Map;

typedef std::map<PTP_TIMER, MfxWork_AutoFunc*>::value_type MfxThreadServer_Map_Elem;
typedef std::map<PTP_TIMER, MfxWork_Widel*>::value_type MfxThreadServer_Widel_Map_Elem;

MfxReturn MicroFlakeX::MfxBeginNewThread(MfxBase* object, MfxString recvFunc, MfxParam myParam)
{
	MfxWork_AutoFunc* tWork = new MfxWork_AutoFunc(object, recvFunc, myParam);

	return TrySubmitThreadpoolCallback(&MfxThreadCallBack, tWork, NULL) ? Mfx_Return_Fine : Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxBeginNewThread_Widely(pThreadFunc pThreadFunc, MfxParam mParam)
{
	MfxWork_Widel* tWork = new MfxWork_Widel(pThreadFunc, mParam);

	return TrySubmitThreadpoolCallback(&MfxThreadCallBack_Widely, tWork, NULL) ? Mfx_Return_Fine : Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxBeginNewTimer(PTP_TIMER& pTimer, MfxBase* object, MfxString recvFunc, MfxParam mParam, MfxTime delay, LONGLONG begin, MfxTime randTime)
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

	MfxThreadServer_Map.insert(MfxThreadServer_Map_Elem(pTimer, tWork));

	return Mfx_Return_Fine;
}

MFX_PORT MfxReturn MicroFlakeX::MfxBeginNewTimer_Widely(PTP_TIMER& pTimer, pThreadFunc pThreadFunc, MfxParam mParam, MfxTime delay, LONGLONG begin, MfxTime randTime)
{
	MfxWork_Widel* tWork = new MfxWork_Widel(pThreadFunc, mParam);

	pTimer = CreateThreadpoolTimer(&MfxTimerCallBack_Widely, tWork, NULL);

	ULARGE_INTEGER tWinTime;
	tWinTime.QuadPart = (LONGLONG)-begin;

	FILETIME tStarTime;
	tStarTime.dwLowDateTime = tWinTime.LowPart;
	tStarTime.dwHighDateTime = tWinTime.HighPart;

	tWork->delay = delay;

	SetThreadpoolTimer(pTimer, &tStarTime, delay, randTime);

	MfxThreadServer_Widel_Map.insert(MfxThreadServer_Widel_Map_Elem(pTimer, tWork));

	return Mfx_Return_Fine;
}


MfxReturn MicroFlakeX::MfxCloseTimer(PTP_TIMER& pTimer)
{
	CloseThreadpoolTimer(pTimer);

	auto tFind = MfxThreadServer_Map.find(pTimer);
	if(tFind != MfxThreadServer_Map.end())
	{
		delete tFind->second;
		MfxThreadServer_Map.erase(tFind);
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
		auto tFind = MfxThreadServer_Map.find(pTimer);
		if (tFind != MfxThreadServer_Map.end())
		{
			delete tFind->second;
			MfxThreadServer_Map.erase(tFind);
		}
	}
}

VOID CALLBACK __MicroFlakeX::MfxTimerCallBack_Widely(PTP_CALLBACK_INSTANCE instance, PVOID val, PTP_TIMER pTimer)
{
	MfxWork_Widel* tWork = (MfxWork_Widel*)val;
	tWork->mypThreadFunc(tWork->myParam);

	if (tWork->delay == 0)
	{
		auto tFind = MfxThreadServer_Widel_Map.find(pTimer);
		if (tFind != MfxThreadServer_Widel_Map.end())
		{
			delete tFind->second;
			MfxThreadServer_Widel_Map.erase(tFind);
		}
	}
}

