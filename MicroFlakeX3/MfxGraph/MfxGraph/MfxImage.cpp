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
	0, ResetID2D1Bitmap, \
	2, ResetIWICBitmapFromFile, \
	2, ResetIWICBitmapFromColor);

MicroFlakeX::MfxImage::MfxImage()
{
	myCanvas = nullptr;
	myRenderTarget = nullptr;
	myIWICBitmap = nullptr;
	myID2D1Bitmap = nullptr;
}

MicroFlakeX::MfxImage::MfxImage(MfxString* path, MfxRect* set)
{
	myCanvas = nullptr;
	myRenderTarget = nullptr;
	myIWICBitmap = nullptr;
	myID2D1Bitmap = nullptr;

	set->GetRect(&myRect);

	MfxSize tSize(set);
	ResetIWICBitmapFromFile(path, &tSize);
}

MicroFlakeX::MfxImage::MfxImage(MfxColor* color, MfxRect* set)
{
	myCanvas = nullptr;
	myRenderTarget = nullptr;
	myIWICBitmap = nullptr;
	myID2D1Bitmap = nullptr;

	set->GetRect(&myRect);

	MfxSize tSize(set);
	ResetIWICBitmapFromColor(color, &tSize);
}

MicroFlakeX::MfxImage::MfxImage(IWICBitmap* tIWICBitmap, MfxRect* set)
{
	myCanvas = nullptr;
	myRenderTarget = nullptr;
	myIWICBitmap = nullptr;
	myID2D1Bitmap = nullptr;

	set->GetRect(&myRect);

	CopyIWICBitmap(&myIWICBitmap, tIWICBitmap);
}

MicroFlakeX::MfxImage::~MfxImage()
{
	SafeRelease(myIWICBitmap);
	SafeRelease(myID2D1Bitmap);
}

MfxReturn MicroFlakeX::MfxImage::Clone(MfxImage** ret)
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
	if (myCanvas)
	{
		ID2D1RenderTarget* tRenderTarget = nullptr;
		myCanvas->GetRenderTarget(&tRenderTarget);

		if (myRenderTarget != tRenderTarget)
		{
			myRenderTarget = tRenderTarget;
			ResetID2D1Bitmap();
		}

		if (myRenderTarget && (myRenderTarget == tRenderTarget))
		{
			D2D1_RECT_F tRectF; myRect.GetD2D1RectF(&tRectF);
			myRenderTarget->DrawBitmap(myID2D1Bitmap, &tRectF);
		}
	}
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
MfxReturn MicroFlakeX::MfxImage::GetCanvas(MfxCanvas** ret) const
{
	*ret = myCanvas;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxImage::GetIWICBitmap(IWICBitmap** ret) const
{
	CopyIWICBitmap(ret, myIWICBitmap);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxImage::GetID2D1Bitmap(ID2D1Bitmap** ret) const
{
	*ret = myID2D1Bitmap;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxImage::GetGdipBitmap(Gdiplus::Bitmap** ret) const
{
	return GdipBitmapFromIWICBitmap(ret, myIWICBitmap, MfxRect(0, 0, myRect.myWidth, myRect.myHeight));
}

MfxReturn MicroFlakeX::MfxImage::GetHICON(HICON* ret) const
{
	Gdiplus::Bitmap* tBitmap = nullptr;

	if (Mfx_Failed(GetGdipBitmap(&tBitmap)))
	{
		return Mfx_Return_Fail;
	}

	tBitmap->GetHICON(ret);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxImage::GetHBITMAP(MfxColor* set, HBITMAP* ret) const
{
	Gdiplus::Bitmap* tBitmap = nullptr;

	if (Mfx_Failed(GetGdipBitmap(&tBitmap)))
	{
		return Mfx_Return_Fail;
	}
	
	Gdiplus::Color tColor;
	set->GetGdipColor(&tColor);

	tBitmap->GetHBITMAP(tColor, ret);

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxImage::SetCanvas(MfxCanvas* set)
{
	myCanvas = set;

	if (myCanvas)
	{
		ResetID2D1Bitmap();
	}

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxImage::SetIWICBitmap(IWICBitmap* set)
{
	SafeRelease(myIWICBitmap);

	myIWICBitmap = set;

	ResetID2D1Bitmap();

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxImage::ResetID2D1Bitmap()
{
	if (myIWICBitmap && myCanvas)
	{
		SafeRelease(myID2D1Bitmap);
		myCanvas->GetRenderTarget(&myRenderTarget);

		if (myRenderTarget)
		{
			ID2D1BitmapFromIWICBitmap(&myID2D1Bitmap, myRenderTarget,
				myIWICBitmap, MfxSize());
		}
	}
	else
	{
		SafeRelease(myID2D1Bitmap);
	}

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxImage::ResetIWICBitmapFromFile(MfxString* path, MfxSize* set)
{
	SafeRelease(myIWICBitmap);

	IWICBitmapFromFile(&myIWICBitmap, *path, set);

	ResetID2D1Bitmap();

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxImage::ResetIWICBitmapFromColor(MfxColor* color, MfxSize* set)
{
	SafeRelease(myIWICBitmap);

	IWICBitmapFromColor(&myIWICBitmap, color, set);

	ResetID2D1Bitmap();

	return Mfx_Return_Fine;
}
