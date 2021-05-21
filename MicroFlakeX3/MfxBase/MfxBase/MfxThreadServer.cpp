#include "pch.h"
#include "MfxBase.h"

using namespace MicroFlakeX;
using namespace __MicroFlakeX;



struct MfxWork_AutoFunc
{
	MfxWork_AutoFunc(MfxBase* obj, MfxString recv, WPARAM wpar = NULL, LPARAM lpar = NULL)
	{
		delay = 0;
		object = obj;
		recvFunc = recv;

		wParam = wpar;
		lParam = lpar;
	}
	int delay;
	MfxBase* object;
	MfxString recvFunc;

	WPARAM wParam;
	LPARAM lParam;
};

struct MfxWork_Widel
{
	MfxWork_Widel(pThreadFunc func, WPARAM wpar = NULL, LPARAM lpar = NULL)
	{
		mypThreadFunc = func;
		wParam = wpar;
		lParam = lpar;
	}
	pThreadFunc mypThreadFunc;

	WPARAM wParam;
	LPARAM lParam;
};



std::map<PTP_TIMER, MfxWork_AutoFunc*> MfxThreadServerMap;
typedef std::map<PTP_TIMER, MfxWork_AutoFunc*>::value_type MfxThreadServerMap_Elem;

MicroFlakeX::MfxThreadServer::MfxThreadServer()
{
}

MicroFlakeX::MfxThreadServer::~MfxThreadServer()
{
}

MfxReturn MicroFlakeX::MfxThreadServer::BeginNewThread(MfxBase* object, MfxString recvFunc, WPARAM wParam, LPARAM lParam)
{
	MfxWork_AutoFunc* tWork = new MfxWork_AutoFunc(object, recvFunc, wParam, lParam);

	/**
	MfxCout << std::endl;
	MfxCout << MfxText("<MfxThreadServer::BeginNewThread> [NowTime: ") << clock();
	MfxCout << MfxText(" ] WPARAM: ") << wParam;
	MfxCout << MfxText(" LPARAM: ") << lParam;
	MfxCout << std::endl;
	/**/

	return TrySubmitThreadpoolCallback(&MfxThreadServer::MfxWorkCallBack, tWork, NULL) ? Mfx_Return_Fine : Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxThreadServer::BeginNewThread_Widely(pThreadFunc pThreadFunc, WPARAM wParam, LPARAM lParam)
{
	MfxWork_Widel* tWork = new MfxWork_Widel(pThreadFunc, wParam, lParam);

	/**
	MfxCout << std::endl;
	MfxCout << MfxText("<MfxThreadServer::BeginNewThread> [NowTime: ") << clock();
	MfxCout << MfxText(" ] WPARAM: ") << wParam;
	MfxCout << MfxText(" LPARAM: ") << lParam;
	MfxCout << std::endl;
	/**/

	return TrySubmitThreadpoolCallback(&MfxThreadServer::MfxWorkCallBack_Widely, tWork, NULL) ? Mfx_Return_Fine : Mfx_Return_Fail;
}



MfxReturn MicroFlakeX::MfxThreadServer::BeginNewTimer(PTP_TIMER& pTimer, MfxBase* object, MfxString recvFunc, LPARAM lParam, DWORD delay, LONGLONG begin, DWORD randTime)
{
	
	MfxWork_AutoFunc* tWork = new MfxWork_AutoFunc(object, recvFunc, NULL, lParam);

	pTimer = CreateThreadpoolTimer(&MfxThreadServer::MfxTimeCallBack, tWork, NULL);

	ULARGE_INTEGER tWinTime;
	tWinTime.QuadPart = (LONGLONG) - begin;

	FILETIME tStarTime;
	tStarTime.dwLowDateTime = tWinTime.LowPart;
	tStarTime.dwHighDateTime = tWinTime.HighPart;

	tWork->delay = delay;
	/**
	MfxCout << std::endl;
	MfxCout << MfxText("<MfxThreadServer::BeginNewTimer> [NowTime: ") << clock();
	MfxCout << MfxText(" ] PTP_TIMER: ") << pTimer;
	MfxCout << MfxText("  delay: ") << delay;
	MfxCout << MfxText("ms  randTime: ") << randTime;
	MfxCout << MfxText("ms");
	MfxCout << std::endl;
	/**/

	SetThreadpoolTimer(pTimer, &tStarTime, delay, randTime);

	MfxThreadServerMap.insert(MfxThreadServerMap_Elem(pTimer, tWork));

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxThreadServer::CloseTimer(PTP_TIMER& pTimer)
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

VOID MicroFlakeX::MfxThreadServer::MfxWorkCallBack(PTP_CALLBACK_INSTANCE instance, PVOID val)
{
	MfxWork_AutoFunc* tWork = (MfxWork_AutoFunc*)val;
	/**
	MfxCout << std::endl;
	MfxCout << MfxText("<MfxWorkCallBack> [NowTime: ") << clock();

	MfxCout << MfxText(" ] tWork->recvFunc: ") << tWork->recvFunc;
	MfxCout << MfxText(" tWork->wParam: ") << tWork->wParam;
	MfxCout << MfxText(" tWork->lParam: ") << tWork->lParam;
	MfxCout << std::endl;
	/**/
	tWork->object->AutoFunc(tWork->recvFunc, tWork->wParam, tWork->lParam);

	delete tWork;
}

VOID MicroFlakeX::MfxThreadServer::MfxWorkCallBack_Widely(PTP_CALLBACK_INSTANCE instance, PVOID val)
{
	MfxWork_Widel* tWork = (MfxWork_Widel*)val;
	/**
	MfxCout << std::endl;
	MfxCout << MfxText("<MfxTimeCallBack> [NowTime: ") << clock();

	MfxCout << MfxText(" ] tWork->recvFunc: ") << tWork->recvFunc;
	MfxCout << MfxText(" tWork->wParam: ") << pTimer;
	MfxCout << MfxText(" tWork->lParam: ") << tWork->lParam;
	MfxCout << std::endl;
	/**/

	tWork->mypThreadFunc(tWork->wParam, tWork->lParam);

	delete tWork;
}


VOID MicroFlakeX::MfxThreadServer::MfxTimeCallBack(PTP_CALLBACK_INSTANCE instance, PVOID val, PTP_TIMER pTimer)
{
	MfxWork_AutoFunc* tWork = (MfxWork_AutoFunc*)val;
	/**
	MfxCout << std::endl;
	MfxCout << MfxText("<MfxTimeCallBack> [NowTime: ") << clock();

	MfxCout << MfxText(" ] tWork->recvFunc: ") << tWork->recvFunc;
	MfxCout << MfxText(" tWork->wParam: ") << pTimer;
	MfxCout << MfxText(" tWork->lParam: ") << tWork->lParam;
	MfxCout << std::endl;
	/**/
	tWork->object->AutoFunc(tWork->recvFunc, pTimer, tWork->lParam);

	if (tWork->delay == 0)
	{
		auto tFind = MfxThreadServerMap.find(pTimer);
		if (tFind != MfxThreadServerMap.end())
		{
			delete tFind->second;
			MfxThreadServerMap.erase(tFind);
		}
	}
	//delete tWork;
}
