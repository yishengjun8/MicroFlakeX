#include "pch.h"
#include "MfxLowPart.h"

MicroFlakeX::MfxImageList::MfxImageList(Gdiplus::Graphics* myGraphics)
{
	myGraphics = myGraphics;

	/* 当前选中的图片 */
	mySelectImageNum = 0;
	myRect = Gdiplus::Rect(0, 0, 80, 80);

	/* 图片缩放质量-默认为“MFXIMAGE_QUALITY_NORMAL” */
	myQuality = MFXIMAGE_QUALITY_NORMAL;
}

MicroFlakeX::MfxImageList::~MfxImageList()
{
	ListClearImage();
}

BOOL MicroFlakeX::MfxImageList::ListAddImage(MfxImage* addImage)
{
	if (addImage == nullptr)
	{
		return 0;
	}
	myImageList.push_back(addImage);
	addImage->SetImagePoint(Gdiplus::Point(myRect.X, myRect.Y));
	addImage->OffsetImageSize(Gdiplus::Size(myRect.Width, myRect.Height));
	addImage->SetImageQuality(myQuality);
	return 1;
}

BOOL MicroFlakeX::MfxImageList::ListClearImage()
{
	myImageList.clear();
	return 1;
}

BOOL MicroFlakeX::MfxImageList::ListDeleteImage()
{
	for (int i = 0; i < myImageList.size(); i++)
	{
		delete myImageList[i];
	}
	myImageList.clear();
	return 1;
}

int MicroFlakeX::MfxImageList::ListSetSelectImageNum(int seNum)
{
	int retNum = mySelectImageNum;
	if (mySelectImageNum > myImageList.size())
	{
		return retNum;
	}
	mySelectImageNum = seNum;
	return retNum;
}

int MicroFlakeX::MfxImageList::ListGetSelectImageNum()
{
	return mySelectImageNum;
}

int MicroFlakeX::MfxImageList::ListGetImageTotal()
{
	return myImageList.size();
}

int MicroFlakeX::MfxImageList::ListNextImage()
{
	int retNum = mySelectImageNum++;
	if (mySelectImageNum > myImageList.size())
	{
		mySelectImageNum = myImageList.size() ? 1 : 0;
	}
	return retNum;
}

MicroFlakeX::MFXIMAGE_QUALITY MicroFlakeX::MfxImageList::SetImageQuality(MFXIMAGE_QUALITY iQuality)
{
	MFXIMAGE_QUALITY retQuality = myQuality;
	for (int i = 0; i < myImageList.size(); i++)
	{
		myImageList[i]->SetImageQuality(iQuality);
	}
	myQuality = iQuality;
	return retQuality;
}

MicroFlakeX::MFXIMAGE_QUALITY MicroFlakeX::MfxImageList::GetImageQuality()
{
	return myQuality;
}

Gdiplus::Size MicroFlakeX::MfxImageList::SetImageSize(Gdiplus::Size iSize)
{
	Gdiplus::Size retSize = Gdiplus::Size(myRect.Width, myRect.Height);
	for (int i = 0; i < myImageList.size(); i++)
	{
		myImageList[i]->SetImageSize(iSize);
	}
	myRect.Width = iSize.Width;
	myRect.Height = iSize.Height;
	return retSize;
}

Gdiplus::Size MicroFlakeX::MfxImageList::GetImageSize()
{
	return Gdiplus::Size(myRect.Width, myRect.Height);
}

Gdiplus::Point MicroFlakeX::MfxImageList::SetImagePoint(Gdiplus::Point iPoint)
{
	Gdiplus::Point retPoint = Gdiplus::Point(myRect.X, myRect.Y);
	for (int i = 0; i < myImageList.size(); i++)
	{
		myImageList[i]->SetImagePoint(iPoint);
	}
	myRect.X = iPoint.Y;
	myRect.Y = iPoint.X;
	return retPoint;
}

Gdiplus::Point MicroFlakeX::MfxImageList::GetImagePoint()
{
	return Gdiplus::Point(myRect.X, myRect.Y);
}

Gdiplus::Rect MicroFlakeX::MfxImageList::GetImageRect()
{
	return myRect;
}

BOOL MicroFlakeX::MfxImageList::Contains(Gdiplus::Point ifPoint)
{
	return myRect.Contains(ifPoint);
}

Gdiplus::Point MicroFlakeX::MfxImageList::OffsetImagePoint(Gdiplus::Point iPoint)
{
	myRect.Offset(iPoint);
	for (int i = 0; i < myImageList.size(); i++)
	{
		myImageList[i]->OffsetImagePoint(iPoint);
	}
	return Gdiplus::Point(myRect.X, myRect.Y);
}

Gdiplus::Size MicroFlakeX::MfxImageList::OffsetImageSize(Gdiplus::Size iSize)
{
	Gdiplus::Size retSize(myRect.Width + iSize.Width, myRect.Height + iSize.Height);
	SetImageSize(retSize);
	return retSize;
}

Gdiplus::Status MicroFlakeX::MfxImageList::Draw()
{
	if (mySelectImageNum <= 0)
	{
		return Gdiplus::Aborted;
	}
	else
	{
		return myImageList[mySelectImageNum - 1]->Draw();
	}
}


/*——————————————————————————————————————————————————*/

MicroFlakeX::MfxImage::MfxImage(Gdiplus::Graphics* myGraphics)
{
	this->myGraphics = myGraphics;

	myRect = Gdiplus::Rect(0, 0, 80, 80);
	myMainBitmap = nullptr;
	myBitmap = nullptr;
	myBitmapQuick = nullptr;

	myQuality = MFXIMAGE_QUALITY_NORMAL;

	/* 构造纯色图片 */
	if (LoadPureColor() != Gdiplus::Ok)
	{
		LoadPureColor();
	}
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

Gdiplus::Status MicroFlakeX::MfxImage::LoadFromFile(WCHAR* iPath)
{
	Gdiplus::Bitmap* t_Bitmap = nullptr;
	Gdiplus::CachedBitmap* t_BitmapQuick = nullptr;

	t_Bitmap = Gdiplus::Bitmap::FromFile(iPath);
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

Gdiplus::Status MicroFlakeX::MfxImage::LoadFromBitmap(Gdiplus::Bitmap* iBitmap)
{
	Gdiplus::Bitmap* t_Bitmap = nullptr;
	Gdiplus::CachedBitmap* t_BitmapQuick = nullptr;

	try 
	{
		Gdiplus::Rect iBitmapRect(0, 0, iBitmap->GetWidth(), iBitmap->GetHeight());
		t_Bitmap = iBitmap->Clone(iBitmapRect, PixelFormat32bppARGB);
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

Gdiplus::Status MicroFlakeX::MfxImage::LoadPureColor(Gdiplus::Color fillColor)
{
	Gdiplus::Bitmap* t_Bitmap = nullptr;
	Gdiplus::CachedBitmap* t_BitmapQuick = nullptr;

	t_Bitmap = new Gdiplus::Bitmap(myRect.Width, myRect.Height, myGraphics);
	if (t_Bitmap == nullptr)
	{
		return Gdiplus::InvalidParameter;//参数错误
	}

	for (int i = 0; i < myRect.Width; i++)
		for (int j = 0; j < myRect.Height; j++)
			t_Bitmap->SetPixel(i, j, fillColor);

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

MicroFlakeX::MFXIMAGE_QUALITY MicroFlakeX::MfxImage::SetImageQuality(MFXIMAGE_QUALITY iQuality)
{
	MFXIMAGE_QUALITY retQuality = myQuality;
	myQuality = iQuality;
	return retQuality;
}

MicroFlakeX::MFXIMAGE_QUALITY MicroFlakeX::MfxImage::GetImageQuality()
{
	return myQuality;
}


Gdiplus::Size MicroFlakeX::MfxImage::SetImageSize(Gdiplus::Size iSize)
{
	Gdiplus::Size retSize(myRect.Width, myRect.Height);
	if (iSize.Width == myRect.Width && iSize.Height == myRect.Height)
	{
		return retSize;
	}

	/* 开始缩放图片 */
	Gdiplus::Bitmap* t_Bitmap = nullptr;
	Gdiplus::Graphics* t_Graphics = nullptr;
	Gdiplus::CachedBitmap* t_BitmapQuick = nullptr;
	
	t_Bitmap = new Gdiplus::Bitmap(iSize.Width, iSize.Height, myGraphics);
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
	
	if (t_Graphics->DrawImage(myMainBitmap, 0, 0, iSize.Width, iSize.Height) != Gdiplus::Ok)
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

Gdiplus::Point MicroFlakeX::MfxImage::SetImagePoint(Gdiplus::Point iPoint)
{
	Gdiplus::Point retPoint(myRect.X, myRect.Y);
	myRect.X = iPoint.X;
	myRect.Y = iPoint.Y;
	return retPoint;
}

Gdiplus::Point MicroFlakeX::MfxImage::GetImagePoint()
{
	return Gdiplus::Point(myRect.X, myRect.Y);
}

Gdiplus::Rect MicroFlakeX::MfxImage::GetImageRect()
{
	return myRect;
}

BOOL MicroFlakeX::MfxImage::Contains(Gdiplus::Point ifPoint)
{
	return myRect.Contains(ifPoint);
}

Gdiplus::Point MicroFlakeX::MfxImage::OffsetImagePoint(Gdiplus::Point iPoint)
{
	myRect.Offset(iPoint);
	return Gdiplus::Point(myRect.X, myRect.Y);
}

Gdiplus::Size MicroFlakeX::MfxImage::OffsetImageSize(Gdiplus::Size iSize)
{
	Gdiplus::Size retSize(myRect.Width + iSize.Width, myRect.Height + iSize.Height);
	SetImageSize(retSize);
	return retSize;
}

Gdiplus::Status MicroFlakeX::MfxImage::Draw()
{
	return myGraphics->DrawCachedBitmap(myBitmapQuick,
		myRect.X, myRect.Y);
}