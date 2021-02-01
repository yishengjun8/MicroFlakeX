#include "pch.h"
#include "MfxGraph.h"

MfxObject_Init_0(MfxImage)
MfxObject_Init_1(MfxImage)
MfxObject_Init_2(MfxImage, MfxGraph);

MicroFlakeX::MfxImage::MfxImage()
{
	myCanvas = nullptr;
	myRenderTarget = nullptr;
	myIWICBitmap = nullptr;
	myID2D1Bitmap = nullptr;
}

MicroFlakeX::MfxImage::~MfxImage()
{
	SafeRelease(myIWICBitmap);
	SafeRelease(myID2D1Bitmap);
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

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::ResetIWICBitmap(MfxStrW* path, MfxSize* set)
{
	/**/
	SafeRelease(myIWICBitmap);
	IWICBitmapFromFile(&myIWICBitmap, *path, set);
	ResetID2D1Bitmap(set);
	/**/
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::ResetID2D1Bitmap(MfxSize* set)
{
	if (myIWICBitmap && myRenderTarget)
	{
		SafeRelease(myID2D1Bitmap);
		ID2D1BitmapFromIWICBitmap(&myID2D1Bitmap, myRenderTarget,
			myIWICBitmap, set);
	}
	else
	{
		SafeRelease(myID2D1Bitmap);
	}
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::FromFile(MfxStrW* path, MfxSize* set)
{
	ResetIWICBitmap(path, set);
	return RFine;
}

MfxReturn MicroFlakeX::MfxImage::FromColor(MfxStrW *path, MfxSize* set)
{
	return RFine;
}

MfxReturn MicroFlakeX::MfxImage::SetCanvas(MfxCanvas* set)
{
	myCanvas = set;
	set->GetRenderTarget(&myRenderTarget);
	MfxSize tSize; tSize = myRect;
	ResetID2D1Bitmap(&tSize);
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
		myRenderTarget->DrawBitmap(myID2D1Bitmap, &tRectF);
	}
	return RFine;
}

MfxReturn MicroFlakeX::MfxImage::GetIWICBitmap(IWICBitmap** ret)
{
	*ret = myIWICBitmap;
	return RFine;
}

MfxReturn MicroFlakeX::MfxImage::GetID2D1Bitmap(ID2D1Bitmap** ret)
{
	*ret = myID2D1Bitmap;
	return RFine;
}

MfxReturn MicroFlakeX::MfxImage::SetIWICBitmap(IWICBitmap* set)
{
	myIWICBitmap = set;
	MfxSize tSize; tSize = myRect;
	ResetID2D1Bitmap(&tSize);
	return RFine;
}

MfxReturn MicroFlakeX::MfxImage::SetID2D1Bitmap(ID2D1Bitmap* set)
{
	myID2D1Bitmap = set;
	return RFine;
}
