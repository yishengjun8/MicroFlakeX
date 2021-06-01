#include "pch.h"
#include "MfxGraph.h"

MfxObject_Init(MfxImage)
MfxObject_EndInit(MfxImage, MfxGraph, \
	0, Paint, \
	\
	1, SetCanvas, \
	1, GetCanvas, \
	\
	2, FromFile, \
	2, FromColor, \
	\
	1, GetIWICBitmap, \
	1, GetID2D1Bitmap, \
	1, GetGdipBitmap, \
	\
	1, SetIWICBitmap, \
	\
	0, Update_Canvas, \
	2, ResetIWICBitmapFromFile, \
	2, ResetIWICBitmapFromColor);

MicroFlakeX::MfxImage::MfxImage()
{
	myCanvas = nullptr;
	myRenderTarget = nullptr;
	myIWICBitmap = nullptr;
	myID2D1Bitmap = nullptr;
	myBitmapUpdateFlage = false;
}

MicroFlakeX::MfxImage::MfxImage(const MfxString* path, const MfxRect* set)
{
	myCanvas = nullptr;
	myRenderTarget = nullptr;
	myIWICBitmap = nullptr;
	myID2D1Bitmap = nullptr;
	myBitmapUpdateFlage = false;

	set->GetRect(&myRect);

	MfxSize tSize(set);
	ResetIWICBitmapFromFile(path, &tSize);
}

MicroFlakeX::MfxImage::MfxImage(const MfxColor* color, const MfxRect* set)
{
	myCanvas = nullptr;
	myRenderTarget = nullptr;
	myIWICBitmap = nullptr;
	myID2D1Bitmap = nullptr;
	myBitmapUpdateFlage = false;

	set->GetRect(&myRect);

	MfxSize tSize(set);
	ResetIWICBitmapFromColor(color, &tSize);
}

MicroFlakeX::MfxImage::MfxImage(IWICBitmap* tIWICBitmap, const MfxRect* set)
{
	myCanvas = nullptr;
	myRenderTarget = nullptr;
	myIWICBitmap = nullptr;
	myID2D1Bitmap = nullptr;
	myBitmapUpdateFlage = false;

	set->GetRect(&myRect);

	CopyIWICBitmap(&myIWICBitmap, tIWICBitmap);
}

MicroFlakeX::MfxImage::~MfxImage()
{
	SafeRelease(myIWICBitmap);
	SafeRelease(myID2D1Bitmap);
}

MfxReturn MicroFlakeX::MfxImage::Clone(MfxImage** ret) const
{
	*ret = new MfxImage(myIWICBitmap, &myRect);

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxImage::Paint()
{
	Update_Canvas();

	myMemberLock.TryWaitLock(&myRenderTarget, &myRect, &myID2D1Bitmap);

	bool IsEmpty = false;
	myRect.IsEmpty(&IsEmpty);
	if (myRenderTarget && !IsEmpty && myID2D1Bitmap)
	{
		myRenderTarget->DrawBitmap(myID2D1Bitmap, myRect);
	}

	myMemberLock.UnLock(&myRenderTarget, &myRect, &myID2D1Bitmap);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxImage::FromFile(MfxString* path, MfxSize* set)
{
	ResetIWICBitmapFromFile(path, set);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxImage::FromColor(MfxColor* color, MfxSize* set)
{
	ResetIWICBitmapFromColor(color, set);

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxImage::GetCanvas(MfxCanvas** ret)const
{
	*ret = myCanvas;
	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxImage::GetIWICBitmap(IWICBitmap** ret)
{
	myMemberLock.TryWaitLock(&myIWICBitmap);
	MfxReturn tRet = CopyIWICBitmap(ret, myIWICBitmap);
	myMemberLock.TryWaitLock(&myIWICBitmap);

	return tRet;
}

MfxReturn MicroFlakeX::MfxImage::GetID2D1Bitmap(ID2D1Bitmap** ret)
{
	*ret = myID2D1Bitmap;
	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxImage::GetGdipBitmap(Gdiplus::Bitmap** ret)
{
	myMemberLock.TryWaitLock(&myIWICBitmap, &myRect);
	MfxReturn tRet = GdipBitmapFromIWICBitmap(ret, myIWICBitmap, MfxRect(0, 0, myRect.myWidth, myRect.myHeight));
	myMemberLock.UnLock(&myIWICBitmap, &myRect);

	return tRet;
}

MfxReturn MicroFlakeX::MfxImage::GetHICON(HICON* ret)
{
	Gdiplus::Bitmap* tBitmap = nullptr;

	if (Mfx_Failed(GetGdipBitmap(&tBitmap)))
	{
		return Mfx_Return_Fail;
	}

	tBitmap->GetHICON(ret);
	SafeDelete(tBitmap);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxImage::GetHBITMAP(MfxColor* set, HBITMAP* ret)
{
	Gdiplus::Bitmap* tBitmap = nullptr;

	if (Mfx_Failed(GetGdipBitmap(&tBitmap)))
	{
		return Mfx_Return_Fail;
	}
	
	Gdiplus::Color tColor;
	set->GetGdipColor(&tColor);

	tBitmap->GetHBITMAP(tColor, ret);
	SafeDelete(tBitmap);

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxImage::SetCanvas(MfxCanvas* set)
{
	myMemberLock.WaitLock(&myCanvas);
	myCanvas = set;
	myMemberLock.UnLock(&myCanvas);

	Update_Canvas();

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxImage::SetIWICBitmap(IWICBitmap* set)
{
	myMemberLock.TryWaitLock(&myIWICBitmap, &myBitmapUpdateFlage);

	SafeRelease(myIWICBitmap);
	myIWICBitmap = set;
	myBitmapUpdateFlage = true;

	myMemberLock.UnLock(&myIWICBitmap, &myBitmapUpdateFlage);

	return Mfx_Return_Fine;
}


MfxReturn MicroFlakeX::MfxImage::Update_Canvas()
{
	myMemberLock.WaitLock(&myCanvas);
	if (myCanvas)
	{
		ID2D1RenderTarget* tID2D1RenderTarget;
		myCanvas->GetRenderTarget(&tID2D1RenderTarget);

		myMemberLock.UnLock(&myCanvas);
		myMemberLock.TryWaitLock(&myRenderTarget, &myID2D1Bitmap, &myIWICBitmap, &myBitmapUpdateFlage);

		if (myBitmapUpdateFlage || (myRenderTarget != tID2D1RenderTarget))
		{
			SafeRelease(myID2D1Bitmap);
			(tID2D1RenderTarget && myIWICBitmap) ? ID2D1BitmapFromIWICBitmap(&myID2D1Bitmap, tID2D1RenderTarget, myIWICBitmap, MfxSize()) : 0;
		}
		myRenderTarget = tID2D1RenderTarget;
		myBitmapUpdateFlage = myID2D1Bitmap ? false : true;

		myMemberLock.UnLock(&myRenderTarget, &myID2D1Bitmap, &myIWICBitmap, &myBitmapUpdateFlage);
	}
	else
	{
		myMemberLock.UnLock(&myCanvas);
		myMemberLock.TryWaitLock(&myRenderTarget, &myID2D1Bitmap);

		SafeRelease(myID2D1Bitmap);
		myRenderTarget = nullptr;

		myMemberLock.UnLock(&myRenderTarget, &myID2D1Bitmap);
	}
	return Mfx_Return_Fine;
}

/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxImage::ResetIWICBitmapFromFile(const MfxString* path, const  MfxSize* set)
{
	myMemberLock.TryWaitLock(&myIWICBitmap, &myBitmapUpdateFlage);

	SafeRelease(myIWICBitmap);
	IWICBitmapFromFile(&myIWICBitmap, *path, set);
	myBitmapUpdateFlage = true;

	myMemberLock.UnLock(&myIWICBitmap, &myBitmapUpdateFlage);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxImage::ResetIWICBitmapFromColor(const MfxColor* color, const  MfxSize* set)
{
	myMemberLock.TryWaitLock(&myIWICBitmap, &myBitmapUpdateFlage);

	SafeRelease(myIWICBitmap);
	IWICBitmapFromColor(&myIWICBitmap, color, set);
	myBitmapUpdateFlage = true;

	myMemberLock.UnLock(&myIWICBitmap, &myBitmapUpdateFlage);

	return Mfx_Return_Fine;
}
