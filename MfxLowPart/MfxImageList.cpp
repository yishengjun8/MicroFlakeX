#include "pch.h"
#include "MfxLowPart.h"

MicroFlakeX::MfxImageList::MfxImageList(Gdiplus::Graphics* gra)
{
	myGraphics = gra;

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

Gdiplus::Status MicroFlakeX::MfxImageList::SetGraphics(Gdiplus::Graphics* gra)
{
	for (int i = 0; i < myImageList.size(); i++)
	{
		myImageList[i]->SetGraphics(gra);
	}
	return Gdiplus::Status();
}

BOOL MicroFlakeX::MfxImageList::ListAddImage(MfxImage* set)
{
	if (set == nullptr)
	{
		return 0;
	}
	myImageList.push_back(set);
	set->SetPoint(Gdiplus::Point(myRect.X, myRect.Y));
	set->OffsetSize(Gdiplus::Size(myRect.Width, myRect.Height));
	set->SetQuality(myQuality);
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

int MicroFlakeX::MfxImageList::ListSetSelectImageNum(int set)
{
	int retNum = mySelectImageNum;
	if (mySelectImageNum > myImageList.size())
	{
		return retNum;
	}
	mySelectImageNum = set;
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

MicroFlakeX::MFXIMAGE_QUALITY MicroFlakeX::MfxImageList::SetQuality(MFXIMAGE_QUALITY set)
{
	MFXIMAGE_QUALITY retQuality = myQuality;
	for (int i = 0; i < myImageList.size(); i++)
	{
		myImageList[i]->SetQuality(set);
	}
	myQuality = set;
	return retQuality;
}

MicroFlakeX::MFXIMAGE_QUALITY MicroFlakeX::MfxImageList::GetQuality()
{
	return myQuality;
}

Gdiplus::Size MicroFlakeX::MfxImageList::SetSize(Gdiplus::Size set)
{
	Gdiplus::Size retSize = Gdiplus::Size(myRect.Width, myRect.Height);
	for (int i = 0; i < myImageList.size(); i++)
	{
		myImageList[i]->SetSize(set);
	}
	myRect.Width = set.Width;
	myRect.Height = set.Height;
	return retSize;
}

Gdiplus::Size MicroFlakeX::MfxImageList::GetSize()
{
	return Gdiplus::Size(myRect.Width, myRect.Height);
}

Gdiplus::Point MicroFlakeX::MfxImageList::SetPoint(Gdiplus::Point set)
{
	Gdiplus::Point retPoint = Gdiplus::Point(myRect.X, myRect.Y);
	for (int i = 0; i < myImageList.size(); i++)
	{
		myImageList[i]->SetPoint(set);
	}
	myRect.X = set.Y;
	myRect.Y = set.X;
	return retPoint;
}

Gdiplus::Point MicroFlakeX::MfxImageList::GetPoint()
{
	return Gdiplus::Point(myRect.X, myRect.Y);
}

Gdiplus::Rect MicroFlakeX::MfxImageList::SetRect(Gdiplus::Rect set)
{
	Gdiplus::Rect retRect = myRect;
	SetPoint(Gdiplus::Point(set.X, set.Y));
	SetSize(Gdiplus::Size(set.Width, set.Height));
	return retRect;
}

Gdiplus::Rect MicroFlakeX::MfxImageList::GetRect()
{
	return myRect;
}

BOOL MicroFlakeX::MfxImageList::Contains(Gdiplus::Point set)
{
	return myRect.Contains(set);
}

Gdiplus::Point MicroFlakeX::MfxImageList::OffsetPoint(Gdiplus::Point set)
{
	myRect.Offset(set);
	for (int i = 0; i < myImageList.size(); i++)
	{
		myImageList[i]->OffsetPoint(set);
	}
	return Gdiplus::Point(myRect.X, myRect.Y);
}

Gdiplus::Size MicroFlakeX::MfxImageList::OffsetSize(Gdiplus::Size set)
{
	Gdiplus::Size retSize(myRect.Width + set.Width, myRect.Height + set.Height);
	SetSize(retSize);
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
