#include "pch.h"
#include "MfxGlide.h"

MFX_OBJ_REFLECTION_INIT(MfxGlide)
MFX_OBJ_REFLECTION_ENDINIT(MfxGlide, MfxBase);

class __MfxGlide_
	: public MfxBase
{
protected:
	MfxNum myFPS;
	MfxBase* myBindObject;
	struct __KeyFrame
	{
		MfxBase* keyWord;
		MfxTime keyDelay;
	};
	std::queue <__KeyFrame>* myKeyFrame, * myKeyFrameBuff;

	bool myRunFlag;

	PTP_TIMER myPTP_TIMER;
public:
	__MfxGlide_(MfxBase* bind, MfxNum fps)
	{
		myFPS = fps;
		myBindObject = bind;

		myKeyFrame = new std::queue<__KeyFrame>;
		myKeyFrameBuff = new std::queue<__KeyFrame>;

		myRunFlag = false;
		myPTP_TIMER = nullptr;
	}
	~__MfxGlide_()
	{
		SafeDelete(myKeyFrame);
		SafeDelete(myKeyFrameBuff);
	}

	MfxReturn AddKeyFrame(MfxBase* key, MfxTime time)
	{
		if (!myRunFlag)
		{
			myKeyFrame->push(__KeyFrame{ key, time });
			return MFX_RET_FAILED;
		}
		return MFX_RET_SECCESS;
	}

	MfxReturn Begin()
	{
		MfxBeginNewTimer(myPTP_TIMER, this, MFX_TXT_W("EachFrame"), MfxParam(), 1000 / myFPS);
	}

	MfxReturn Stop()
	{
		MfxCloseTimer(myPTP_TIMER);
		myPTP_TIMER = nullptr;
	}

	MfxReturn MFX_CALLBACK(EachFrame)
	{
		
		if (!myPTP_TIMER)
		{
			return MFX_RET_SECCESS;
		}


	}
};

MicroFlakeX::MfxGlide::MfxGlide()
{
}

MicroFlakeX::MfxGlide::~MfxGlide()
{
}
