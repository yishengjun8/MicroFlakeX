#include "pch.h"
#include "MfxGraph.h"

MFX_OBJ_REFLECTION_INIT(MfxRectangle)
MFX_OBJ_REFLECTION_ENDINIT(MfxRectangle, MfxGraph, \
	Paint, \
	\
	SetCanvas, \
	GetCanvas, \
	\
	SetFrameSize, \
	SetFillColor, \
	SetFrameColor, \
	\
	GetFrameSize, \
	GetFillColor, \
	GetFrameColor, \
	\
	GetReallyRect, \
	\
	SetRounded_X, \
	SetRounded_Y, \
	\
	GetRounded_X, \
	GetRounded_Y, \
	\
	OpenRounded, \
	CloseRounded \
	);


MicroFlakeX::MfxRectangle::MfxRectangle()
{
	myCanvas = nullptr;
	myFillBrush = nullptr;
	myFrameBrush = nullptr;
	myRenderTarget = nullptr;

	myRoundedFlage = false;
	myColorUpdateFlage = false;

	myFrameSize = 1;

	myRounded_X = 20;
	myRounded_Y = 20;

	myFillColor.Reset(255, 255, 0, 0);
	myFrameColor.Reset(0, 255, 255, 0);
}

MicroFlakeX::MfxRectangle::MfxRectangle(const MfxRect* set, MfxColor fillColor, MfxColor frameColor)
{
	myCanvas = nullptr;
	myFillBrush = nullptr;
	myFrameBrush = nullptr;
	myRenderTarget = nullptr;

	myRoundedFlage = false;
	myColorUpdateFlage = false;

	myFrameSize = 1;

	myRounded_X = 20;
	myRounded_Y = 20;

	myRect.SetRect(set);
	myFillColor.SetColor(&fillColor);
	myFrameColor.SetColor(&frameColor);
}

MicroFlakeX::MfxRectangle::~MfxRectangle()
{
	SafeRelease(myFillBrush);
	SafeRelease(myFrameBrush);
}

MfxReturn MicroFlakeX::MfxRectangle::MFX_OBJ_ENABLE_CLONE(ret)
{
	*ret = new MfxRectangle(&myRect, myFillColor, myFrameColor);
	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRectangle::Paint()
{
	Update_Canvas();

	myMemberLock.WaitLock(&myRenderTarget, &myRect, &myFillBrush, &myFrameBrush);

	bool IsEmpty = false;
	myRect.IsEmpty(&IsEmpty);
	if (myRenderTarget && !IsEmpty && myFillBrush&& myFrameBrush)
	{
		if (myRoundedFlage)
		{
			D2D1_ROUNDED_RECT tRoundedRect;
			tRoundedRect.rect = myRect;
			tRoundedRect.radiusX = myRounded_X;
			tRoundedRect.radiusY = myRounded_Y;
			myRenderTarget->DrawRoundedRectangle(tRoundedRect, myFrameBrush, myFrameSize);
			myRenderTarget->FillRoundedRectangle(tRoundedRect, myFillBrush);
		}
		else
		{
			myRenderTarget->DrawRectangle(myRect, myFrameBrush, myFrameSize);
			myRenderTarget->FillRectangle(myRect, myFillBrush);
		}

	}

	myMemberLock.UnLock(&myRenderTarget, &myRect, &myFillBrush, &myFrameBrush);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRectangle::SetCanvas(MfxCanvas* set)
{
	myMemberLock.WaitLock(&myCanvas);
	myCanvas = set;
	myMemberLock.UnLock(&myCanvas);

	Update_Canvas();

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRectangle::GetCanvas(MfxCanvas** ret)
{
	*ret = myCanvas;
	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRectangle::SetFrameSize(double set)
{
	myFrameSize = set < 0 ? 0 : set;
	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRectangle::SetFillColor(MfxColor* set)
{
	myMemberLock.WaitLock(&myFillColor);
	myFillColor.SetColor(set);
	myMemberLock.UnLock(&myFillColor);

	myColorUpdateFlage = true;
	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRectangle::SetFrameColor(MfxColor* set)
{
	myMemberLock.WaitLock(&myFrameColor);
	myFrameColor.SetColor(set);
	myMemberLock.UnLock(&myFrameColor);

	myColorUpdateFlage = true;
	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRectangle::GetFrameSize(double* ret)
{
	*ret = myFrameSize;
	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRectangle::GetFillColor(MfxColor* ret)
{
	*ret = myFillColor;
	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRectangle::GetFrameColor(MfxColor* ret)
{
	*ret = myFrameColor;
	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRectangle::SetRounded_X(double set)
{
	myRounded_X = set;
	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRectangle::SetRounded_Y(double set)
{
	myRounded_Y = set;
	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRectangle::GetRounded_X(double* ret)
{
	*ret = myRounded_X;
	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRectangle::GetRounded_Y(double* ret)
{
	*ret = myRounded_Y;
	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRectangle::OpenRounded()
{
	myRoundedFlage = true;
	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRectangle::CloseRounded()
{
	myRoundedFlage = false;
	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRectangle::GetReallyRect(MfxRect* ret) const
{
	*ret = myRect;
	ret->Inflate(ceil(myFrameSize / 2), ceil(myFrameSize / 2));
	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRectangle::Update_Canvas()
{
	myMemberLock.WaitLock(&myCanvas);
	if (myCanvas)
	{
		ID2D1RenderTarget* tID2D1RenderTarget;
		myCanvas->GetRenderTarget(&tID2D1RenderTarget);

		myMemberLock.UnLock(&myCanvas);
		myMemberLock.WaitLock(&myRenderTarget, &myFillColor, &myFrameColor, &myFillBrush, &myFrameBrush);

		if (tID2D1RenderTarget && (myColorUpdateFlage || (myRenderTarget != tID2D1RenderTarget)))
		{
			SafeRelease(myFillBrush);
			SafeRelease(myFrameBrush);
			tID2D1RenderTarget->CreateSolidColorBrush(myFillColor, &myFillBrush);
			tID2D1RenderTarget->CreateSolidColorBrush(myFrameColor, &myFrameBrush);
		}
		myRenderTarget = tID2D1RenderTarget;
		myColorUpdateFlage = (myFillBrush && myFrameBrush) ? false : true;

		myMemberLock.UnLock(&myRenderTarget, &myFillColor, &myFrameColor, &myFillBrush, &myFrameBrush);
	}
	else
	{
		myMemberLock.UnLock(&myCanvas);
		myMemberLock.WaitLock(&myRenderTarget, &myFillBrush, &myFrameBrush);

		SafeRelease(myFillBrush);
		SafeRelease(myFrameBrush);
		myRenderTarget = nullptr;

		myMemberLock.UnLock(&myRenderTarget, &myFillBrush, &myFrameBrush);
	}
	return MFX_RET_SECCESS;
}
