#include "pch.h"
#include "MfxBasicGraph.h"


using MicroFlakeX::MfxTexture;
BEGIN_INITDATA(MfxTexture)
END_INITDATA;
BEGIN_AUTOMAP(MfxTexture)
END_AUTOMAP;

void MicroFlakeX::MfxTexture::MfxTextureInitData()
{
	MFXLOCK;
	REALIZE_AUTOBASIC;
	myRenderTarget = NULL;
	myBasicIWICBitmap = NULL;
	myShowID2D1Bitmap = NULL;
}

MicroFlakeX::MfxTexture::MfxTexture()
{
	MFXLOCK;
	MfxTextureInitData();
}

MicroFlakeX::MfxTexture::~MfxTexture()
{
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxTexture::ResetShowBitmap()
{
	if (myBasicIWICBitmap && myRenderTarget)
	{
		MfxComRelease(&myShowID2D1Bitmap);

		myShowID2D1Bitmap = MfxID2D1BitmapFromIWICBitmap(
			myBasicIWICBitmap, (*myRect).Width, (*myRect).Height, myRenderTarget);
	}
	if (!myRenderTarget)
	{
		MfxComRelease(&myShowID2D1Bitmap);
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxTexture::FromFile(MfxStrW path)
{
	myBasicIWICBitmap = MfxIWICBitmapFromFile(path, 0, 0);
	if (myRenderTarget)
	{
		ResetShowBitmap();
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxTexture::SetRenderTarget(ID2D1RenderTarget* set)
{
	if (myRenderTarget != set)
	{
		myRenderTarget = set;
		ResetShowBitmap();
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxTexture::Draw()
{
	if (myRenderTarget)
	{
		myRenderTarget->DrawBitmap(
			myShowID2D1Bitmap,
			D2D1::RectF(
				(*myRect).GetLeft(), (*myRect).GetTop(),
				(*myRect).GetRight(), (*myRect).GetBottom())
		);
	}
	return MfxReturn();
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxTexture::SetRect(GdipRect set)
{
	MFXLOCK;
	SetSize(GdipSize(set.Width, set.Height));
	SetPoint(GdipPoint(set.X, set.Y));
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxTexture::SetSize(GdipSize set)
{
	MFXLOCK;
	if ((*myRect).Width != set.Width || (*myRect).Height != set.Height) 
	{
		myRect = GdipRect((*myRect).X, (*myRect).Y, set.Width, set.Height);
		return MfxFine;
	}
	return MfxFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxTexture::SetPoint(GdipPoint set)
{
	MFXLOCK;
	if ((*myRect).X != set.X || (*myRect).Y != set.Y)
	{
		myRect = GdipRect(set.X, set.Y, (*myRect).Width, (*myRect).Height);
		return MfxFine;
	}
	return MfxFail;
}
