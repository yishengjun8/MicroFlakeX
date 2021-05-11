#include "pch.h"
#include "MfxGraph.h"

MfxObject_Init_0(MfxImage)
MfxObject_Init_1(MfxImage, END)
MfxObject_Init_2(MfxImage, MfxGraph);

MicroFlakeX::MfxImage::MfxImage()
{
	myCanvas = nullptr;
	myRenderTarget = nullptr;
	myIWICBitmap = nullptr;
	myID2D1Bitmap = nullptr;
}

MicroFlakeX::MfxImage::MfxImage(MfxString* path, MfxRect set)
{
	myCanvas = nullptr;
	myRenderTarget = nullptr;
	myIWICBitmap = nullptr;
	myID2D1Bitmap = nullptr;

	myRect = set;
	ResetIWICBitmapFromFile(path, MfxSize(&set));
}

MicroFlakeX::MfxImage::MfxImage(MfxColor color, MfxRect set)
{
	myCanvas = nullptr;
	myRenderTarget = nullptr;
	myIWICBitmap = nullptr;
	myID2D1Bitmap = nullptr;

	myRect = set;
	ResetIWICBitmapFromColor(color, MfxSize(&set));
}

MicroFlakeX::MfxImage::MfxImage(IWICBitmap* tIWICBitmap, MfxRect set)
{
	myCanvas = nullptr;
	myRenderTarget = nullptr;
	myIWICBitmap = nullptr;
	myID2D1Bitmap = nullptr;

	myRect = set;
	CopyIWICBitmap(&myIWICBitmap, tIWICBitmap);
}

MicroFlakeX::MfxImage::~MfxImage()
{
	SafeRelease(myIWICBitmap);
	SafeRelease(myID2D1Bitmap);
}

MfxReturn MicroFlakeX::MfxImage::Clone(MfxBase** ret)
{
	*ret = new MfxImage(myIWICBitmap, myRect);
	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxImage::Clone(MfxImage** ret)
{
	*ret = new MfxImage(myIWICBitmap, myRect);
	return Mfx_Return_Fine;
}

MfxBase& MicroFlakeX::MfxImage::operator=(MfxBase& rhs)
{
	// TODO: 在此处插入 return 语句
	return *this;
}

BOOL MicroFlakeX::MfxImage::operator==(MfxBase& rhs)
{
	// TODO: 在此处插入 return 语句
	return false;
}

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

MfxReturn MicroFlakeX::MfxImage::SetCanvas(MfxCanvas* set)
{
	myCanvas = set;
	if (!myCanvas)
	{
		return Mfx_Return_Fine;
	}
	ResetID2D1Bitmap();
	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxImage::GetCanvas(MfxCanvas** ret)
{
	*ret = myCanvas;
	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxImage::ResetIWICBitmapFromFile(MfxString* path, MfxSize set)
{
	/**/
	SafeRelease(myIWICBitmap);
	IWICBitmapFromFile(&myIWICBitmap, *path, set);
	ResetID2D1Bitmap();
	/**/
	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxImage::ResetIWICBitmapFromColor(MfxColor color, MfxSize set)
{
	/**/
	SafeRelease(myIWICBitmap);
	IWICBitmapFromColor(&myIWICBitmap, color, set);
	ResetID2D1Bitmap();
	/**/
	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxImage::ResetID2D1Bitmap()
{
	if (myIWICBitmap && myCanvas)
	{
		SafeRelease(myID2D1Bitmap);
		myRenderTarget = nullptr;
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

MfxReturn MicroFlakeX::MfxImage::FromFile(MfxString* path, MfxSize set)
{
	ResetIWICBitmapFromFile(path, set);
	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxImage::FromColor(MfxColor color, MfxSize set)
{
	ResetIWICBitmapFromColor(color, set);
	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxImage::GetIWICBitmap(IWICBitmap** ret)
{
	CopyIWICBitmap(ret, myIWICBitmap);
	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxImage::GetID2D1Bitmap(ID2D1Bitmap** ret)
{
	*ret = myID2D1Bitmap;
	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxImage::SetIWICBitmap(IWICBitmap* set)
{
	SafeRelease(myIWICBitmap);
	myIWICBitmap = set;
	ResetID2D1Bitmap();
	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxImage::SetID2D1Bitmap(ID2D1Bitmap* set)
{
	SafeRelease(myID2D1Bitmap);
	myID2D1Bitmap = set;
	return Mfx_Return_Fine;
}
