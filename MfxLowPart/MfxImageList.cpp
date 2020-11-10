#include "pch.h"
#include "MfxLowPart.h"

MicroFlakeX::MfxImageList::MfxImageList(Gdiplus::Graphics* myGraphics)
{
	this->myGraphics = myGraphics;

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
