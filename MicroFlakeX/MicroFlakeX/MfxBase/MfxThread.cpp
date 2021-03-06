#include "pch.h"
#include "MfxBase.h"

using namespace MicroFlakeX;
using namespace MicroFlakeX;

struct MfxWork_AutoFunc
{
	MfxWork_AutoFunc(MfxBase* obj, MfxStringW recv, MfxParam& param)
	{
		delay = 0;
		object = obj;
		recvFunc = recv;

		myParam = param;
	}
	MfxMemberLock myMemberLock;
	int delay;
	MfxBase* object;
	MfxStringW recvFunc;

	MfxParam myParam;
};

struct MfxWork_Widel
{
	MfxWork_Widel(pThreadFunc& func, MfxParam& param)
	{
		delay = 0;

		myParam = param;
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

MfxReturn MicroFlakeX::MfxBeginNewThread(MfxBase* object, MfxStringW recvFunc, MfxParam param)
{
	MfxWork_AutoFunc* tWork = new MfxWork_AutoFunc(object, recvFunc, param);

	return TrySubmitThreadpoolCallback(&__MfxThreadCallBack, tWork, NULL) ? MFX_RET_SECCESS : MFX_RET_FAILED;
}

MfxReturn MicroFlakeX::MfxBeginNewThread_Widely(pThreadFunc pThreadFunc, MfxParam param)
{
	MfxWork_Widel* tWork = new MfxWork_Widel(pThreadFunc, param);

	return TrySubmitThreadpoolCallback(&__MfxThreadCallBack_Widely, tWork, NULL) ? MFX_RET_SECCESS : MFX_RET_FAILED;
}

MfxReturn MicroFlakeX::MfxBeginNewTimer(PTP_TIMER& pTimer, MfxBase* object, MfxStringW recvFunc, MfxParam param, MfxTime delay, LONGLONG begin, MfxTime randTime)
{
	MfxWork_AutoFunc* tWork = new MfxWork_AutoFunc(object, recvFunc, param);

	pTimer = CreateThreadpoolTimer(&__MfxTimerCallBack, tWork, NULL);

	ULARGE_INTEGER tWinTime;
	tWinTime.QuadPart = (LONGLONG) - begin;

	FILETIME tStarTime;
	tStarTime.dwLowDateTime = tWinTime.LowPart;
	tStarTime.dwHighDateTime = tWinTime.HighPart;

	tWork->delay = delay;

	SetThreadpoolTimer(pTimer, &tStarTime, delay, randTime);

	MfxThreadServer_Map.insert(MfxThreadServer_Map_Elem(pTimer, tWork));

	return MFX_RET_SECCESS;
}

MFX_DLL_EXPORT MfxReturn MicroFlakeX::MfxBeginNewTimer_Widely(PTP_TIMER& pTimer, pThreadFunc pThreadFunc, MfxParam param, MfxTime delay, LONGLONG begin, MfxTime randTime)
{
	MfxWork_Widel* tWork = new MfxWork_Widel(pThreadFunc, param);

	pTimer = CreateThreadpoolTimer(&__MfxTimerCallBack_Widely, tWork, NULL);

	ULARGE_INTEGER tWinTime;
	tWinTime.QuadPart = (LONGLONG)-begin;

	FILETIME tStarTime;
	tStarTime.dwLowDateTime = tWinTime.LowPart;
	tStarTime.dwHighDateTime = tWinTime.HighPart;

	tWork->delay = delay;

	SetThreadpoolTimer(pTimer, &tStarTime, delay, randTime);

	MfxThreadServer_Widel_Map.insert(MfxThreadServer_Widel_Map_Elem(pTimer, tWork));

	return MFX_RET_SECCESS;
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

	pTimer = nullptr;

	return MFX_RET_SECCESS;
}

VOID CALLBACK MicroFlakeX::__MfxThreadCallBack(PTP_CALLBACK_INSTANCE instance, PVOID val)
{
	MfxWork_AutoFunc* tWork = (MfxWork_AutoFunc*)val;
	tWork->object->Reflection(tWork->recvFunc, tWork->myParam);

	delete tWork;
}

VOID CALLBACK MicroFlakeX::__MfxThreadCallBack_Widely(PTP_CALLBACK_INSTANCE instance, PVOID val)
{
	MfxWork_Widel* tWork = (MfxWork_Widel*)val;
	tWork->mypThreadFunc(tWork->myParam);

	delete tWork;
}



VOID CALLBACK MicroFlakeX::__MfxTimerCallBack(PTP_CALLBACK_INSTANCE instance, PVOID val, PTP_TIMER pTimer)
{
	MfxWork_AutoFunc* tWork = (MfxWork_AutoFunc*)val;
	tWork->object->Reflection(tWork->recvFunc, tWork->myParam);

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

VOID CALLBACK MicroFlakeX::__MfxTimerCallBack_Widely(PTP_CALLBACK_INSTANCE instance, PVOID val, PTP_TIMER pTimer)
{
	//WaitForThreadpoolTimerCallbacks(pTimer, FALSE);

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

