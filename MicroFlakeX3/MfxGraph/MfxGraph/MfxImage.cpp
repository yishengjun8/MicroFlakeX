#include "pch.h"
#include "MfxGraph.h"

MfxObject_Init_0(MfxImage)
MfxObject_Init_1(MfxImage)
MfxObject_Init_2(MfxImage, MfxGraph);

MicroFlakeX::MfxImage::MfxImage()
{
}

MicroFlakeX::MfxImage::~MfxImage()
{
}

MfxReturn MicroFlakeX::MfxImage::Clone(MfxBase** ret)
{
	return RFine;
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

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::ResetBaseBitmap()
{
	/**
	if (myBaseIWICBitmap && myRenderTarget)
	{
		SafeRelease(myShowID2D1Bitmap);
		MfxSize tSize; tSize = myRect;
		ID2D1BitmapFromIWICBitmap(&myShowID2D1Bitmap, myRenderTarget,
			myBaseIWICBitmap, &tSize);
		ResetShowBitmap();
	}
	else
	{
		SafeRelease(myShowID2D1Bitmap);
	}
	/**/
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::ResetShowBitmap()
{
	if (myBaseIWICBitmap && myRenderTarget)
	{
		SafeRelease(myShowID2D1Bitmap);
		MfxSize tSize; tSize = myRect;
		ID2D1BitmapFromIWICBitmap(&myShowID2D1Bitmap, myRenderTarget,
			myBaseIWICBitmap, &tSize);
	}
	else
	{
		SafeRelease(myShowID2D1Bitmap);
	}
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::FromFile(MfxStrW path, MfxSize* set)
{
	myRect = *set;
	IWICBitmapFromFile(&myBaseIWICBitmap, path, set);
	ResetShowBitmap();
	return RFine;
}

MfxReturn MicroFlakeX::MfxImage::FromColor(MfxStrW path, MfxSize* set)
{
	return RFine;
}

MfxReturn MicroFlakeX::MfxImage::SetCanvas(MfxCanvas* set)
{
	myCanvas = set;
	set->GetRenderTarget(&myRenderTarget);
	ResetShowBitmap();
	return RFine;
}

MfxReturn MicroFlakeX::MfxImage::GetCanvas(MfxCanvas** ret)
{
	*ret = myCanvas;
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::Paint()
{
	if (myRenderTarget)
	{
		D2D1_RECT_F tRectF;
		myRect.GetD2D1RectF(&tRectF);
		myRenderTarget->DrawBitmap(myShowID2D1Bitmap, &tRectF);
	}
	return RFine;
}
