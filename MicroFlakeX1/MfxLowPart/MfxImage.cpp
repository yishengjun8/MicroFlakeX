#include "pch.h"
#include "MfxLowPart.h"

/*
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

MicroFlakeX::MfxImage::MfxImage(Gdiplus::Graphics* set, Gdiplus::Color valC, Gdiplus::Size valR)
{
	myGraphics = set;

	myRect = Gdiplus::Rect(0, 0, valR.Width, valR.Height);
	myMainBitmap = nullptr;
	myBitmap = nullptr;
	myBitmapQuick = nullptr;

	myQuality = MFXIMAGE_QUALITY_NORMAL;

	LoadPureColor(valC);
}
/**/

void MicroFlakeX::MfxImage::MfxImageInitData(Gdiplus::Graphics* gra, Gdiplus::Rect rect)
{
	myGraphics = gra;
	myRect = rect;

	myMainBitmap = nullptr;
	myBitmap = nullptr;
	myBitmapQuick = nullptr;

	myQuality = MFXIMAGE_QUALITY_NORMAL;
}

MicroFlakeX::MfxImage::MfxImage(Gdiplus::Graphics* gra)
{
	MfxImageInitData(gra, Gdiplus::Rect(0, 0, 160, 160));

	LoadPureColor();
}

MicroFlakeX::MfxImage::MfxImage(Gdiplus::Graphics* gra, WCHAR* path)
{
	MfxImageInitData(gra, Gdiplus::Rect(0, 0, 160, 160));

	LoadFromFile(path);
}

MicroFlakeX::MfxImage::MfxImage(Gdiplus::Graphics* gra, Gdiplus::Color color)
{
	MfxImageInitData(gra, Gdiplus::Rect(0, 0, 160, 160));

	LoadPureColor(color);
}

MicroFlakeX::MfxImage::MfxImage(Gdiplus::Graphics* gra, WCHAR* path, Gdiplus::Rect rect)
{
	MfxImageInitData(gra, Gdiplus::Rect(0, 0, 160, 160));

	LoadFromFile(path);
	this->SetRect(rect);
}

MicroFlakeX::MfxImage::MfxImage(Gdiplus::Graphics* gra, WCHAR* path, Gdiplus::Size size)
{
	MfxImageInitData(gra, Gdiplus::Rect(0, 0, 160, 160));

	LoadFromFile(path);
	this->SetSize(size);
}

MicroFlakeX::MfxImage::MfxImage(Gdiplus::Graphics* gra, WCHAR* path, Gdiplus::Point point)
{
	MfxImageInitData(gra, Gdiplus::Rect(point.X, point.Y, 160, 160));

	LoadFromFile(path);
}

MicroFlakeX::MfxImage::MfxImage(Gdiplus::Graphics* gra, Gdiplus::Color color, Gdiplus::Rect rect)
{
	MfxImageInitData(gra, rect);

	LoadPureColor(color);
}

MicroFlakeX::MfxImage::MfxImage(Gdiplus::Graphics* gra, Gdiplus::Color color, Gdiplus::Size size)
{
	MfxImageInitData(gra, Gdiplus::Rect(0, 0, size.Width, size.Height));

	LoadPureColor(color);
}

MicroFlakeX::MfxImage::MfxImage(Gdiplus::Graphics* gra, Gdiplus::Color color, Gdiplus::Point point)
{
	MfxImageInitData(gra, Gdiplus::Rect(point.X, point.Y, 160, 160));

	LoadPureColor(color);
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

Gdiplus::Status MicroFlakeX::MfxImage::LoadFromFile(WCHAR* path)
{
	Gdiplus::Bitmap* t_Bitmap = nullptr;
	Gdiplus::CachedBitmap* t_BitmapQuick = nullptr;

	t_Bitmap = Gdiplus::Bitmap::FromFile(path);
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

MicroFlakeX::MFXIMAGE_QUALITY MicroFlakeX::MfxImage::SetQuality(MFXIMAGE_QUALITY set)
{
	MFXIMAGE_QUALITY retQuality = myQuality;
	myQuality = set;
	return retQuality;
}

MicroFlakeX::MFXIMAGE_QUALITY MicroFlakeX::MfxImage::GetQuality()
{
	return myQuality;
}


Gdiplus::Size MicroFlakeX::MfxImage::SetSize(Gdiplus::Size set)
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

Gdiplus::Size MicroFlakeX::MfxImage::GetSize()
{
	return Gdiplus::Size(myRect.Width, myRect.Height);
}

Gdiplus::Point MicroFlakeX::MfxImage::SetPoint(Gdiplus::Point set)
{
	Gdiplus::Point retPoint(myRect.X, myRect.Y);
	myRect.X = set.X;
	myRect.Y = set.Y;
	return retPoint;
}

Gdiplus::Point MicroFlakeX::MfxImage::GetPoint()
{
	return Gdiplus::Point(myRect.X, myRect.Y);
}


Gdiplus::Rect MicroFlakeX::MfxImage::SetRect(Gdiplus::Rect set)
{
	Gdiplus::Rect retRect = myRect;
	SetPoint(Gdiplus::Point(set.X, set.Y));
	SetSize(Gdiplus::Size(set.Width, set.Height));
	myRect = set;
	return retRect;
}

Gdiplus::Rect MicroFlakeX::MfxImage::GetRect()
{
	return myRect;
}

BOOL MicroFlakeX::MfxImage::Contains(Gdiplus::Point set)
{
	return myRect.Contains(set);
}

Gdiplus::Point MicroFlakeX::MfxImage::OffsetPoint(Gdiplus::Point set)
{
	myRect.Offset(set);
	return Gdiplus::Point(myRect.X, myRect.Y);
}

Gdiplus::Size MicroFlakeX::MfxImage::OffsetSize(Gdiplus::Size set)
{
	Gdiplus::Size retSize(myRect.Width + set.Width, myRect.Height + set.Height);
	SetSize(retSize);
	return retSize;
}

Gdiplus::Status MicroFlakeX::MfxImage::SetGraphics(Gdiplus::Graphics* set)
{
	myGraphics = set;
	delete myBitmapQuick;
	myBitmapQuick = new Gdiplus::CachedBitmap(myBitmap, myGraphics);

	return Gdiplus::Status();
}

Gdiplus::Status MicroFlakeX::MfxImage::Draw()
{
	//return myGraphics->DrawImage(myMainBitmap, myRect);
	return myGraphics->DrawCachedBitmap(myBitmapQuick, myRect.X, myRect.Y);
}