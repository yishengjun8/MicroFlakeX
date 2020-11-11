#include "pch.h"
#include "MfxLowPart.h"

MicroFlakeX::MfxImage::MfxImage(Gdiplus::Graphics* set, Gdiplus::Rect value)
{
	myGraphics = set;

	myRect = value;
	myMainBitmap = nullptr;
	myBitmap = nullptr;
	myBitmapQuick = nullptr;

	myQuality = MFXIMAGE_QUALITY_NORMAL;

	LoadPureColor();
}

MicroFlakeX::MfxImage::MfxImage(Gdiplus::Graphics* set, WCHAR* value)
{
	myGraphics = set;

	//myRect = Gdiplus::Rect(0, 0, 120, 120);
	myMainBitmap = nullptr;
	myBitmap = nullptr;
	myBitmapQuick = nullptr;

	myQuality = MFXIMAGE_QUALITY_NORMAL;

	LoadFromFile(value);
}

MicroFlakeX::MfxImage::MfxImage(Gdiplus::Graphics* set, Gdiplus::Color valC, Gdiplus::Rect valR)
{
	myGraphics = set;

	myRect = valR;
	myMainBitmap = nullptr;
	myBitmap = nullptr;
	myBitmapQuick = nullptr;

	myQuality = MFXIMAGE_QUALITY_NORMAL;

	LoadPureColor(valC);
}


MicroFlakeX::MfxImage::~MfxImage()
{
	delete myMainBitmap;
	delete myBitmap;
	delete myBitmapQuick;
}

MicroFlakeX::MfxImage* MicroFlakeX::MfxImage::Clone()
{
	return nullptr;
}

Gdiplus::Bitmap* MicroFlakeX::MfxImage::GetBitmap()
{
	return myBitmap;
}

Gdiplus::Status MicroFlakeX::MfxImage::LoadFromFile(WCHAR* set)
{
	Gdiplus::Bitmap* t_Bitmap = nullptr;
	Gdiplus::CachedBitmap* t_BitmapQuick = nullptr;

	t_Bitmap = Gdiplus::Bitmap::FromFile(set);
	if (t_Bitmap == nullptr)
	{
		return Gdiplus::InvalidParameter;//参数错误
	}

	t_BitmapQuick = new Gdiplus::CachedBitmap(t_Bitmap, myGraphics);
	if (t_BitmapQuick == nullptr)
	{
		return Gdiplus::InvalidParameter;//参数错误
	}

	myRect.Width = t_Bitmap->GetWidth();
	myRect.Height = t_Bitmap->GetHeight();

	delete myMainBitmap;
	myMainBitmap = t_Bitmap->Clone(Gdiplus::Rect(0, 0, myRect.Width, myRect.Height), PixelFormat32bppARGB);;
	delete myBitmap;
	myBitmap = t_Bitmap;
	delete myBitmapQuick;
	myBitmapQuick = t_BitmapQuick;

	return Gdiplus::Ok; //成功
}

Gdiplus::Status MicroFlakeX::MfxImage::LoadFromBitmap(Gdiplus::Bitmap* set)
{
	Gdiplus::Bitmap* t_Bitmap = nullptr;
	Gdiplus::CachedBitmap* t_BitmapQuick = nullptr;

	try 
	{
		Gdiplus::Rect iBitmapRect(0, 0, set->GetWidth(), set->GetHeight());
		t_Bitmap = set->Clone(iBitmapRect, PixelFormat32bppARGB);
	}
	catch (Gdiplus::Status error)
	{
		return Gdiplus::InvalidParameter;//参数错误
	}
	if (t_Bitmap == nullptr)
	{
		return Gdiplus::InvalidParameter;//参数错误
	}

	t_BitmapQuick = new Gdiplus::CachedBitmap(t_Bitmap, myGraphics);
	if (t_BitmapQuick == nullptr)
	{
		return Gdiplus::InvalidParameter;//参数错误
	}

	myRect.Width = t_Bitmap->GetWidth();
	myRect.Height = t_Bitmap->GetHeight();

	/* 删除以前的图片 */
	delete myMainBitmap;
	myMainBitmap = t_Bitmap->Clone(Gdiplus::Rect(0, 0, myRect.Width, myRect.Height), PixelFormat32bppARGB);
	delete myBitmap;
	myBitmap = t_Bitmap;
	delete myBitmapQuick;
	myBitmapQuick = t_BitmapQuick;

	return Gdiplus::Ok; //成功
}

Gdiplus::Status MicroFlakeX::MfxImage::LoadPureColor(Gdiplus::Color set)
{
	Gdiplus::Bitmap* t_Bitmap = nullptr;
	Gdiplus::CachedBitmap* t_BitmapQuick = nullptr;

	t_Bitmap = new Gdiplus::Bitmap(myRect.Width, myRect.Height, myGraphics);
	if (t_Bitmap == nullptr)
	{
		return Gdiplus::InvalidParameter;//参数错误
	}

	Gdiplus::Graphics t_Graphics(t_Bitmap);
	t_Graphics.Clear(set);

	t_BitmapQuick = new Gdiplus::CachedBitmap(t_Bitmap, myGraphics);
	if (t_BitmapQuick == nullptr)
	{
		return Gdiplus::InvalidParameter;//参数错误
	}

	/* 删除以前的图片 */
	delete myMainBitmap;
	myMainBitmap = t_Bitmap->Clone(Gdiplus::Rect(0,0, myRect.Width, myRect.Height), PixelFormat32bppARGB);
	delete myBitmap;
	myBitmap = t_Bitmap;
	delete myBitmapQuick;
	myBitmapQuick = t_BitmapQuick;

	return Gdiplus::Ok;
}

MicroFlakeX::MFXIMAGE_QUALITY MicroFlakeX::MfxImage::SetImageQuality(MFXIMAGE_QUALITY set)
{
	MFXIMAGE_QUALITY retQuality = myQuality;
	myQuality = set;
	return retQuality;
}

MicroFlakeX::MFXIMAGE_QUALITY MicroFlakeX::MfxImage::GetImageQuality()
{
	return myQuality;
}


Gdiplus::Size MicroFlakeX::MfxImage::SetImageSize(Gdiplus::Size set)
{
	Gdiplus::Size retSize(myRect.Width, myRect.Height);
	if (set.Width == myRect.Width && set.Height == myRect.Height)
	{
		return retSize;
	}

	/* 开始缩放图片 */
	Gdiplus::Bitmap* t_Bitmap = nullptr;
	Gdiplus::Graphics* t_Graphics = nullptr;
	Gdiplus::CachedBitmap* t_BitmapQuick = nullptr;
	
	t_Bitmap = new Gdiplus::Bitmap(set.Width, set.Height, myGraphics);
	if (t_Bitmap == nullptr)
	{
		return Gdiplus::Size(-1, -1);//参数错误
	}

	t_Graphics = new Gdiplus::Graphics(t_Bitmap);
	if (t_Graphics == nullptr)
	{
		delete t_Bitmap;
		return Gdiplus::Size(-1, -1);//参数错误
	}

	if (t_Graphics->SetInterpolationMode((Gdiplus::InterpolationMode)myQuality) != Gdiplus::Ok)
	{
		delete t_Bitmap;
		delete t_Graphics;
		return Gdiplus::Size(-1, -1);//参数错误
	}
	
	if (t_Graphics->DrawImage(myMainBitmap, 0, 0, set.Width, set.Height) != Gdiplus::Ok)
	{
		delete t_Bitmap;
		delete t_Graphics;
		return Gdiplus::Size(-1, -1);//参数错误
	}


	t_BitmapQuick = new Gdiplus::CachedBitmap(t_Bitmap, myGraphics);
	if (t_BitmapQuick == nullptr)
	{
		delete t_Bitmap;
		delete t_Graphics;
		return Gdiplus::Size(-1, -1);//参数错误
	}

	delete t_Graphics;

	/* 删除老旧图片 */
	delete myBitmap;
	myBitmap = t_Bitmap;
	delete myBitmapQuick;
	myBitmapQuick = t_BitmapQuick;

	/* 重新设置大小 */
	myRect.Width = myBitmap->GetWidth();
	myRect.Height = myBitmap->GetHeight();

	return retSize;
}

Gdiplus::Size MicroFlakeX::MfxImage::GetImageSize()
{
	return Gdiplus::Size(myRect.Width, myRect.Height);
}

Gdiplus::Point MicroFlakeX::MfxImage::SetImagePoint(Gdiplus::Point set)
{
	Gdiplus::Point retPoint(myRect.X, myRect.Y);
	myRect.X = set.X;
	myRect.Y = set.Y;
	return retPoint;
}

Gdiplus::Point MicroFlakeX::MfxImage::GetImagePoint()
{
	return Gdiplus::Point(myRect.X, myRect.Y);
}


Gdiplus::Rect MicroFlakeX::MfxImage::SetImageRect(Gdiplus::Rect set)
{
	Gdiplus::Rect retRect = myRect;
	SetImagePoint(Gdiplus::Point(set.X, set.Y));
	SetImageSize(Gdiplus::Size(set.Width, set.Height));
	myRect = set;
	return retRect;
}

Gdiplus::Rect MicroFlakeX::MfxImage::GetImageRect()
{
	return myRect;
}

BOOL MicroFlakeX::MfxImage::Contains(Gdiplus::Point set)
{
	return myRect.Contains(set);
}

Gdiplus::Point MicroFlakeX::MfxImage::OffsetImagePoint(Gdiplus::Point set)
{
	myRect.Offset(set);
	return Gdiplus::Point(myRect.X, myRect.Y);
}

Gdiplus::Size MicroFlakeX::MfxImage::OffsetImageSize(Gdiplus::Size set)
{
	Gdiplus::Size retSize(myRect.Width + set.Width, myRect.Height + set.Height);
	SetImageSize(retSize);
	return retSize;
}

Gdiplus::Status MicroFlakeX::MfxImage::SetGraphics(Gdiplus::Graphics* set)
{
	myGraphics = set;
	myBitmapQuick = new Gdiplus::CachedBitmap(myBitmap, myGraphics);

	return Gdiplus::Status();
}

Gdiplus::Status MicroFlakeX::MfxImage::Draw()
{
	//return myGraphics->DrawImage(myMainBitmap, myRect);
	return myGraphics->DrawCachedBitmap(myBitmapQuick, myRect.X, myRect.Y);
}