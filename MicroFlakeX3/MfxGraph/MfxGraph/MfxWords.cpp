#include "pch.h"
#include "MfxGraph.h"

MfxObject_Init_0(MfxWords)
MfxObject_Init_1(MfxWords)
MfxObject_Init_2(MfxWords, MfxGraph);

MicroFlakeX::MfxWorlds_Type MicroFlakeX::MfxWords::g_DefType{
	L"Consolas",
	MfxWords_TextX_def | MfxWords_TextY_def, //猟忖電井庁塀
	MfxWords_ShowStyle_null, MfxFontStyle_Regu, //�塋掌駟� - 猟忖鯉塀
	MfxSmoothingMode_Hig, //猟忖紙崙嵎楚
	Gdiplus::Color(Gdiplus::Color::Black), 16,		//猟忖
	Gdiplus::Color(Gdiplus::Color::Red), 2,			//円崇
	Gdiplus::Color(Gdiplus::Color::DarkBlue)		//嘘尚
};


void MicroFlakeX::MfxWords::MfxWordsInitData(MfxWorlds_Type set)
{
	MfxCodeLock(this);

	myDC = nullptr;
	myGraphics = nullptr;
	myGraphicsPath = new Gdiplus::GraphicsPath;

	myRect = Gdiplus::Rect(0, 0, 1, 1);
	myText = L"";
	myType = set;
	myFontFamily = new Gdiplus::FontFamily(myType.myFontName.c_str());
	myStringFormat = new Gdiplus::StringFormat;

	myFramePen = new Gdiplus::Pen(myType.myFrameColor, myType.myFramePenWidth);
	myBackBrush = new Gdiplus::SolidBrush(myType.myBackColor);
	myTextBrush = new Gdiplus::SolidBrush(myType.myTextColor);

	myTextRect = *myRect;
	myTextRectPen = new Gdiplus::Pen(Gdiplus::Color::Red, 1);

	myShowBitmap = nullptr;
	myShowGraphics = nullptr;
	myCachedShowBitmap = nullptr;

	myShowRegion = nullptr;
	myBasicRegion = nullptr;
	myCollisionBlock = Gdiplus::Size(30, 30);

	myResetRegionLock = 0;
	myResetTextPathLock = false;
	myResetShowBitmapLock = false;
	myResetShowCachedBitmapLock = false;

	myFramePen->SetAlignment(Gdiplus::PenAlignmentInset);
	{
		if (myType.myTextXY & MfxWords_TextX_near)
		{
			myStringFormat->SetAlignment(Gdiplus::StringAlignmentNear);
		}
		else if (myType.myTextXY & MfxWords_TextX_center)
		{
			myStringFormat->SetAlignment(Gdiplus::StringAlignmentCenter);
		}
		else if (myType.myTextXY & MfxWords_TextX_far)
		{
			myStringFormat->SetAlignment(Gdiplus::StringAlignmentFar);
		}
	}

	ResetTextPath();
}



MicroFlakeX::MfxWords::MfxWords()
{
	MfxCodeLock(this);
	MfxWordsInitData(g_DefType);
}

MicroFlakeX::MfxWords::MfxWords(MfxWorlds_Type set)
{
	MfxCodeLock(this);
	MfxWordsInitData(set);
}

MicroFlakeX::MfxWords::~MfxWords()
{
	MfxCodeLock(this);

	delete myGraphicsPath;
	myGraphicsPath = nullptr;

	delete myFontFamily; //猟忖社怛
	myFontFamily = nullptr;
	delete myStringFormat; //下蕉佚連
	myStringFormat = nullptr;

	delete myFramePen;
	myFramePen = nullptr;
	delete myBackBrush;
	myBackBrush = nullptr;
	delete myTextBrush;
	myTextBrush = nullptr;
	delete myTextRectPen;
	myTextRectPen = nullptr;

	delete myBasicRegion;
	myBasicRegion = nullptr;
	delete *myShowBitmap;
	myShowBitmap = nullptr;
	delete myShowGraphics;
	myShowGraphics = nullptr;
	delete myCachedShowBitmap;
	myCachedShowBitmap = nullptr;

	delete myGraphics;
	myGraphics = nullptr;
}

void MicroFlakeX::MfxWords::operator=(MfxWords& rhs)
{
	MfxCodeLock(this);
	MfxLock t_CodeLock2(&rhs);

	LockResetTextPath();
	LockResetShowBitmap();
	LockResetCachedShowBitmap();

	SetType(rhs.myType);
	SetText(rhs.myText);
	SetStringFormat(rhs.myStringFormat);

	SetDC(rhs.myDC);
	SetRect(*rhs.myRect);
	SetFramePen(rhs.myFramePen);
	SetBackBrush(rhs.myBackBrush);
	SetTextBrush(rhs.myTextBrush);

	UnLockResetTextPath();
	UnLockResetShowBitmap();
	UnLockResetCachedShowBitmap();

	ResetTextPath();
}

void MicroFlakeX::MfxWords::SetDefType(MfxWorlds_Type& setType)
{
	g_DefType = setType;
}

void MicroFlakeX::MfxWords::GetDefType(MfxWorlds_Type& getType)
{
	getType = g_DefType;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */


void MicroFlakeX::MfxWords::Mode_ClearDC()
{
	MfxCodeLock(this);
	myDC = nullptr;
	delete myGraphics;
	myGraphics = nullptr;
}

void MicroFlakeX::MfxWords::Mode_ResetDC(HDC set)
{
	MfxCodeLock(this);
	delete myGraphics;
	myGraphics = nullptr;

	myDC = set;
	myGraphics = new Gdiplus::Graphics(myDC);
	ResetCachedShowBitmap();
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::LockResetRegion()
{
	MfxCodeLock(this);
	myResetRegionLock++;
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::UnLockResetRegion()
{
	MfxCodeLock(this);
	myResetRegionLock--;
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::LockResetTextPath()
{
	MfxCodeLock(this);
	myResetTextPathLock++;
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::UnLockResetTextPath()
{
	MfxCodeLock(this);
	myResetTextPathLock--;
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::LockResetShowBitmap()
{
	MfxCodeLock(this);
	myResetShowBitmapLock++;
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::UnLockResetShowBitmap()
{
	MfxCodeLock(this);
	myResetShowBitmapLock--;
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::LockResetCachedShowBitmap()
{
	MfxCodeLock(this);
	myResetShowCachedBitmapLock++;
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::UnLockResetCachedShowBitmap()
{
	MfxCodeLock(this);
	myResetShowCachedBitmapLock--;
	return RFine;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::ResetRegion()
{
	MfxCodeLock(this);
	if (myResetRegionLock && !*myShowBitmap)
	{
		return RFine;
	}

	if (myShowBitmap.CheckChangeFlag() || myCollisionBlock.CheckChangeFlag())
	{
		myShowBitmap.CleanChangeFlag();

		Gdiplus::GraphicsPath t_Path;
		Gdiplus::BitmapData bmpData;
		Gdiplus::Rect t_LockRect(0, 0, myShowBitmap->GetWidth(), myShowBitmap->GetHeight());
		if (myShowBitmap->LockBits(&t_LockRect, Gdiplus::ImageLockModeRead, PixelFormat32bppARGB, &bmpData) == Gdiplus::Ok)
		{
			int stride = bmpData.Stride;
			unsigned int* pData = (unsigned int*)(bmpData.Scan0);

			for (int line = 0;
				line < t_LockRect.Height / (*myCollisionBlock).Height + t_LockRect.Height % (*myCollisionBlock).Height > 0 ? 1 : 0;
				line++)
			{
				for (int ver = 0;
					ver < t_LockRect.Width / (*myCollisionBlock).Width + t_LockRect.Width % (*myCollisionBlock).Width > 0 ? 1 : 0;
					ver++)
				{
					int t_A = 0, count = 1;
					for (int y = line * (*myCollisionBlock).Height;
						y < (line + 1) * (*myCollisionBlock).Height && y < t_LockRect.Height; y++)
					{
						for (int x = ver * (*myCollisionBlock).Width;
							x < (ver + 1) * (*myCollisionBlock).Width && x < t_LockRect.Width; x++)
						{
							unsigned int color = (pData[y * stride / 4 + x]);
							// color= 0xAARRGGBB
							//int A = color >> 24;
							//int R = (color << 8) >> 24;
							//int G = (color << 16) >> 24;
							//int B = (color << 24) >> 24;
							count++, t_A += color >> 24;
						}
					}
					if (t_A / count > 100)
					{
						t_Path.AddRectangle(Gdiplus::Rect(
							ver * (*myCollisionBlock).Width,
							line * (*myCollisionBlock).Height,
							(*myCollisionBlock).Width, (*myCollisionBlock).Height)
						);
					}
				}
			}
			myShowBitmap->UnlockBits(&bmpData);
			delete myBasicRegion;
			myBasicRegion = nullptr;
			myBasicRegion = new Gdiplus::Region(&t_Path);
		}
	}
	//3*2裳專延算
	if (myRect.CheckChangeFlag() || myCollisionBlock.CheckChangeFlag())
	{
		myRect.CleanChangeFlag();
		myCollisionBlock.CleanChangeFlag();

		delete myShowRegion;
		myShowRegion = nullptr;
		myShowRegion = myBasicRegion->Clone();

		Gdiplus::Matrix myMatrix;

		myMatrix.Scale(
			static_cast<FLOAT>((*myRect).Width) / static_cast<FLOAT>(myShowBitmap->GetWidth()),
			static_cast<FLOAT>((*myRect).Height) / static_cast<FLOAT>(myShowBitmap->GetHeight()),
			Gdiplus::MatrixOrderAppend
		);

		myMatrix.Translate((*myRect).X, (*myRect).Y, Gdiplus::MatrixOrderAppend);
		myShowRegion->Transform(&myMatrix);
	}
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::ResetTextPath()
{
	MfxCodeLock(this);
	if (myResetTextPathLock)
	{
		return RFail;
	}

	myGraphicsPath->Reset();
	myGraphicsPath->AddString(
		myText.c_str(), -1,
		myFontFamily, myType.myFontStyle, myType.myTextSize_em,
		Gdiplus::Rect(0, 0, (*myRect).Width, (*myRect).Height), myStringFormat
	);

	myGraphicsPath->GetBounds(&myTextRect, NULL, myTextRectPen);
	if (myType.myTextXY & MfxWords_TextY_near)
	{
		myTextRect.Y = abs(myTextRect.Y);
	}
	else if (myType.myTextXY & MfxWords_TextY_center)
	{
		myTextRect.Y = abs(myTextRect.Y) + ((*myRect).Height - myTextRect.Height) / 2;
	}
	else if (myType.myTextXY & MfxWords_TextY_far)
	{
		myTextRect.Y = abs(myTextRect.Y) + ((*myRect).Height - myTextRect.Height);
	}

	myTextRect.Y = myTextRect.Y < 0 ? 0 : myTextRect.Y;
	myGraphicsPath->Reset();
	myGraphicsPath->AddString(
		myText.c_str(), -1,
		myFontFamily, myType.myFontStyle, myType.myTextSize_em,
		Gdiplus::Rect(0, myTextRect.Y, (*myRect).Width, (*myRect).Height), myStringFormat
	);

	ResetShowBitmap();
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::ResetShowBitmap() //嶷鮫bitmap
{
	MfxCodeLock(this);
	if (myResetShowBitmapLock)
	{
		return RFail;
	}

	delete *myShowBitmap;
	myShowBitmap = nullptr;
	delete myShowGraphics;
	myShowGraphics = nullptr;

	myShowBitmap = new Gdiplus::Bitmap((*myRect).Width, (*myRect).Height, PixelFormat32bppARGB);
	myShowGraphics = new Gdiplus::Graphics(*myShowBitmap);

	myShowGraphics->SetSmoothingMode((Gdiplus::SmoothingMode)myType.mySmoothingMode);
	myShowGraphics->Clear(Gdiplus::Color(0, 0, 0, 0));

	if (myType.myShowStyle & MfxWords_ShowStyle_fill)
	{
		myShowGraphics->FillRectangle(myBackBrush, Gdiplus::Rect(0, 0, (*myRect).Width, (*myRect).Height));
	}
	if (myType.myShowStyle & MfxWords_ShowStyle_fram)
	{
		myShowGraphics->DrawRectangle(myFramePen, Gdiplus::Rect(0, 0, (*myRect).Width - 1, (*myRect).Height - 1));
	}

	myShowGraphics->FillPath(myTextBrush, myGraphicsPath);

	ResetRegion();
	ResetCachedShowBitmap();
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::ResetCachedShowBitmap()
{
	if (myResetShowCachedBitmapLock || !*myShowBitmap)
	{
		return RFail;
	}

	if (myGraphics)
	{
		delete myCachedShowBitmap;
		myCachedShowBitmap = nullptr;
		myCachedShowBitmap = new Gdiplus::CachedBitmap(*myShowBitmap, myGraphics);
	}

	return RFine;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::Clone(MfxWords** ret)
{
	MfxCodeLock(this);
	if (ret)
	{
		MfxWords* t_Words = new MfxWords(myType);

		t_Words->LockResetTextPath();
		t_Words->LockResetShowBitmap();
		t_Words->LockResetCachedShowBitmap();

		t_Words->SetText(myText);
		t_Words->SetStringFormat(myStringFormat);

		t_Words->SetDC(myDC);
		t_Words->SetRect(*myRect);
		t_Words->SetFramePen(myFramePen);
		t_Words->SetBackBrush(myBackBrush);
		t_Words->SetTextBrush(myTextBrush);
		t_Words->SetCollisionBlock(*myCollisionBlock);

		t_Words->UnLockResetTextPath();
		t_Words->UnLockResetShowBitmap();
		t_Words->UnLockResetCachedShowBitmap();

		t_Words->ResetTextPath();

		(*ret) = t_Words;
		return RFine;
	}
	return RFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::Similar(MfxWords* set)
{
	MfxCodeLock(this);
	if (set)
	{
		set->LockResetShowBitmap();
		set->LockResetCachedShowBitmap();

		set->SetDC(myDC);
		set->SetRect(*myRect);
		set->SetCollisionBlock(*myCollisionBlock);

		set->UnLockResetShowBitmap();
		set->UnLockResetCachedShowBitmap();

		set->ResetShowBitmap();
		return RFine;
	}
	else
	{
		return RFail;
	}
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetDC(HDC set)
{
	MfxCodeLock(this);
	if (set)
	{
		Mode_ResetDC(set);
	}
	else
	{
		Mode_ClearDC();
	}
	return RFine;;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetDC(HDC* ret)
{
	MfxCodeLock(this);
	if (ret)
	{
		(*ret) = myDC;
		return RFine;
	}
	return RFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetShowBitmap(Gdiplus::Bitmap** ret)
{
	MfxCodeLock(this);

	if (ret)
	{
		Gdiplus::Bitmap* t_Bitmap = nullptr;
		t_Bitmap = myShowBitmap->Clone(Gdiplus::Rect(0, 0, (*myRect).Width, (*myRect).Height), PixelFormat32bppARGB);
		if (t_Bitmap)
		{
			(*ret) = t_Bitmap;
		}
		return RFine;
	}
	else
	{
		return RFail;
	}
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::DrawBitmap(Gdiplus::Graphics* set)
{
	MfxCodeLock(this);
	if (set)
	{
		set->DrawImage(*myShowBitmap, Gdiplus::Point((*myRect).X, (*myRect).Y));
		return RFine;
	}
	else
	{
		return RFail;
	}
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::Draw()
{
	MfxCodeLock(this);
	if (myCachedShowBitmap && myGraphics)
	{
		myGraphics->DrawCachedBitmap(myCachedShowBitmap, (*myRect).X, (*myRect).Y);
		return RFine;
	}
	return RFail;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetText(MfxStrW set)
{
	MfxCodeLock(this);

	myText = set;
	ResetTextPath();
	return RFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetText(MfxStrW* ret)
{
	MfxCodeLock(this);
	(*ret) = myText;
	return RFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetStringFormat(Gdiplus::StringFormat* set)
{
	MfxCodeLock(this);
	if (set)
	{
		delete myStringFormat;
		myStringFormat = nullptr;

		myStringFormat = set->Clone();
		if (myType.myTextXY & MfxWords_TextX_near)
		{
			myStringFormat->SetAlignment(Gdiplus::StringAlignmentNear);
		}
		else if (myType.myTextXY & MfxWords_TextX_center)
		{
			myStringFormat->SetAlignment(Gdiplus::StringAlignmentCenter);
		}
		else if (myType.myTextXY & MfxWords_TextX_far)
		{
			myStringFormat->SetAlignment(Gdiplus::StringAlignmentFar);
		}

		ResetTextPath();
		return RFine;
	}
	else
	{
		return RFail;
	}
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetStringFormat(Gdiplus::StringFormat** ret)
{
	MfxCodeLock(this);

	if (ret)
	{
		(*ret) = myStringFormat->Clone();
		ResetTextPath();
		return RFine;
	}
	else
	{
		return RFail;
	}
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetType(MfxWorlds_Type set)
{
	MfxCodeLock(this);
	LockResetTextPath();

	if (myType.myFontName != set.myFontName)
	{
		SetFontName(set.myFontName);
	}
	if (myType.myTextXY != set.myTextXY)
	{
		SetTextXY(set.myTextXY);
	}
	if (myType.myShowStyle != set.myShowStyle)
	{
		SetShowStyle(set.myShowStyle);
	}
	if (myType.myFontStyle != set.myFontStyle)
	{
		SetFontStyle(set.myFontStyle);
	}
	if (myType.mySmoothingMode != set.mySmoothingMode)
	{
		SetSmoothingMode(set.mySmoothingMode);
	}
	if (myType.myTextColor.GetValue() != set.myTextColor.GetValue())
	{
		SetTextColor(set.myTextColor);
	}
	if (myType.myTextSize_em != set.myTextSize_em)
	{
		SetTextSize_em(set.myTextSize_em);
	}
	if (myType.myFrameColor.GetValue() != set.myFrameColor.GetValue())
	{
		SetFrameColor(set.myFrameColor);
	}
	if (myType.myFramePenWidth != set.myFramePenWidth)
	{
		SetFramePenWidth(set.myFramePenWidth);
	}
	if (myType.myBackColor.GetValue() != set.myBackColor.GetValue())
	{
		SetBackColor(set.myBackColor);
	}

	UnLockResetTextPath();

	ResetTextPath();
	return RFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetFontName(MfxStrW set)
{
	MfxCodeLock(this);

	if (set.size())
	{
		myType.myFontName = set;
		Gdiplus::FontFamily* t_FontFamily = new Gdiplus::FontFamily(set.c_str());
		if (t_FontFamily->IsAvailable())
		{
			delete myFontFamily;
			myFontFamily = nullptr;
			myFontFamily = t_FontFamily;

			ResetTextPath();
			return RFine;
		}
	}
	else
	{
		return RFail;
	}
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetTextXY(MfxWords_TextXY set)
{
	MfxCodeLock(this);

	if (myType.myTextXY != set)
	{
		myType.myTextXY = set;
		if (myType.myTextXY & MfxWords_TextX_near)
		{
			myStringFormat->SetAlignment(Gdiplus::StringAlignmentNear);
		}
		else if (myType.myTextXY & MfxWords_TextX_center)
		{
			myStringFormat->SetAlignment(Gdiplus::StringAlignmentCenter);
		}
		else if (myType.myTextXY & MfxWords_TextX_far)
		{
			myStringFormat->SetAlignment(Gdiplus::StringAlignmentFar);
		}

		ResetTextPath();
		return RFine;
	}
	else
	{
		return RFail;
	}
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetShowStyle(MfxWords_ShowStyle set)
{
	MfxCodeLock(this);

	if (myType.myShowStyle != set)
	{
		myType.myShowStyle = set;

		ResetShowBitmap();
		return RFine;
	}
	else
	{
		return RFail;
	}
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetFontStyle(MfxFontStyle set)
{
	MfxCodeLock(this);

	if (myType.myFontStyle != set)
	{
		myType.myFontStyle = set;

		ResetTextPath();
		return RFine;
	}
	else
	{
		return RFail;
	}
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetSmoothingMode(MfxSmoothingMode_EN set)
{
	MfxCodeLock(this);

	if (myType.mySmoothingMode != set)
	{
		myType.mySmoothingMode = set;

		ResetShowBitmap();
		return RFine;
	}
	else
	{
		return RFail;
	}
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetTextColor(Gdiplus::Color set)
{
	MfxCodeLock(this);

	myType.myTextColor = set;

	delete myTextBrush;
	myTextBrush = nullptr;
	myTextBrush = new Gdiplus::SolidBrush(myType.myTextColor);

	ResetShowBitmap();
	return RFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetTextSize_em(MfxPenWidth set)
{
	MfxCodeLock(this);

	if (set > 0)
	{
		myType.myTextSize_em = set;
		ResetTextPath();
		return RFine;
	}
	else
	{
		return RFail;
	}
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetFrameColor(Gdiplus::Color set)
{
	MfxCodeLock(this);

	myType.myFrameColor = set;

	delete myFramePen;
	myFramePen = nullptr;
	myFramePen = new Gdiplus::Pen(myType.myFrameColor, myType.myFramePenWidth);

	ResetShowBitmap();
	return RFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetFramePenWidth(MfxPenWidth set)
{
	MfxCodeLock(this);

	if (set > 0)
	{
		myType.myFramePenWidth = set;

		delete myFramePen;
		myFramePen = nullptr;
		myFramePen = new Gdiplus::Pen(myType.myFrameColor, myType.myFramePenWidth);

		ResetShowBitmap();
		return RFine;
	}
	else
	{
		return RFail;
	}
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetBackColor(Gdiplus::Color set)
{
	MfxCodeLock(this);

	myType.myBackColor = set;

	delete myBackBrush;
	myBackBrush = nullptr;
	myBackBrush = new Gdiplus::SolidBrush(myType.myBackColor);

	ResetShowBitmap();

	return RFine;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetType(MfxWorlds_Type* ret)
{
	MfxCodeLock(this);

	(*ret) = myType;
	return RFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetFontName(MfxStrW* ret)
{
	MfxCodeLock(this);

	(*ret) = myType.myFontName;
	return RFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetTextXY(MfxWords_TextXY* ret)
{
	MfxCodeLock(this);

	(*ret) = myType.myTextXY;
	return RFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetShowStyle(MfxWords_ShowStyle* ret)
{
	MfxCodeLock(this);

	(*ret) = myType.myShowStyle;
	return RFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetFontStyle(MfxFontStyle* ret)
{
	MfxCodeLock(this);

	(*ret) = myType.myFontStyle;
	return RFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetSmoothingMode(MfxSmoothingMode_EN* ret)
{
	MfxCodeLock(this);

	(*ret) = myType.mySmoothingMode;
	return RFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetTextColor(Gdiplus::Color* ret)
{
	MfxCodeLock(this);

	(*ret) = myType.myTextColor;
	return RFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetTextSize_em(MfxPenWidth* ret)
{
	MfxCodeLock(this);

	(*ret) = myType.myTextSize_em;
	return RFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetFrameColor(Gdiplus::Color* ret)
{
	MfxCodeLock(this);

	(*ret) = myType.myFrameColor;
	return RFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetFramePenWidth(MfxPenWidth* ret)
{
	MfxCodeLock(this);

	(*ret) = myType.myFramePenWidth;
	return RFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetBackColor(Gdiplus::Color* ret)
{
	MfxCodeLock(this);

	(*ret) = myType.myBackColor;
	return RFine;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetRect(Gdiplus::Rect set)
{
	MfxCodeLock(this);
	SetSize(Gdiplus::Size(set.Width, set.Height));
	SetPoint(Gdiplus::Point(set.X, set.Y));
	return RFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetSize(Gdiplus::Size set)
{
	MfxCodeLock(this);

	if ((*myRect).Width != set.Width || (*myRect).Height != set.Height)
	{
		myRect = Gdiplus::Rect((*myRect).X, (*myRect).Y, set.Width, set.Height);
		ResetTextPath();
		return RFine;
	}
	else
	{
		return RFail;
	}
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetPoint(Gdiplus::Point set)
{
	MfxCodeLock(this);
	if ((*myRect).X != set.X || (*myRect).Y != set.Y) //Size音�犁伐登菻�厚個
	{
		myRect = Gdiplus::Rect(set.X, set.Y, (*myRect).Width, (*myRect).Height);
		ResetRegion();
		return RFine;
	}
	return RFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetCollisionBlock(Gdiplus::Size set)
{
	if (set.Width > 2 && set.Height > 2)
	{
		myCollisionBlock = set;
		ResetRegion();
		return RFine;
	}
	else
	{
		return RFail;
	}

}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::CollisionWith(MfxGraph* set, bool* ret)
{
	if (set && ret)
	{
		*ret = false;
		Gdiplus::Rect rhsRect;
		set->AutoFunc(L"GetRect", &rhsRect);
		if ((*myRect).IntersectsWith(rhsRect))
		{
			*ret = true;
			if (myGraphics)
			{
				Gdiplus::Region* lhsRegion = nullptr, * rhsRegion = nullptr;
				if (Seccess(set->AutoFunc(L"GetRegion", &rhsRegion)))
				{
					lhsRegion = myShowRegion->Clone();
					if (lhsRegion && rhsRegion)
					{
						lhsRegion->Intersect(rhsRegion);

						if (!lhsRegion->IsEmpty(myGraphics))
						{
							*ret = true;
						}
						else
						{
							*ret = false;
						}
					}
				}
				delete lhsRegion;
				delete rhsRegion;
			}
		}
	}
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetFramePen(Gdiplus::Pen* set)
{
	MfxCodeLock(this);

	if (set)
	{
		delete myFramePen;
		myFramePen = nullptr;
		myFramePen = set->Clone();

		ResetShowBitmap();
		return RFine;
	}
	else
	{
		return RFail;
	}
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetBackBrush(Gdiplus::Brush* set)
{
	MfxCodeLock(this);

	if (set)
	{
		delete myBackBrush;
		myBackBrush = nullptr;
		myBackBrush = set->Clone();

		ResetShowBitmap();
		return RFine;
	}
	else
	{
		return RFail;
	}
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetTextBrush(Gdiplus::Brush* set)
{
	MfxCodeLock(this);

	if (set)
	{
		delete myTextBrush;
		myTextBrush = nullptr;
		myTextBrush = set->Clone();

		ResetShowBitmap();
		return RFine;
	}
	else
	{
		return RFail;
	}
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetRect(Gdiplus::Rect* ret)
{
	MfxCodeLock(this);

	(*ret) = *myRect;
	return RFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetSize(Gdiplus::Size* ret)
{
	MfxCodeLock(this);

	(*ret).Width = (*myRect).Width;
	(*ret).Height = (*myRect).Height;
	return RFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetPoint(Gdiplus::Point* ret)
{
	MfxCodeLock(this);

	(*ret).X = (*myRect).X;
	(*ret).Y = (*myRect).Y;
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetRegion(Gdiplus::Region** ret)
{
	MfxCodeLock(this);
	if (ret && myBasicRegion)
	{
		*ret = myBasicRegion->Clone();
		return RFine;
	}
	return RFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetRegionBlock(Gdiplus::Size* ret)
{
	MfxCodeLock(this);
	(*ret) = *myCollisionBlock;
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetFramePen(Gdiplus::Pen** ret)
{
	MfxCodeLock(this);

	if (*ret)
	{
		(*ret) = myFramePen->Clone();
		return RFine;
	}
	else
	{
		return RFail;
	}
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetBackBrush(Gdiplus::Brush** ret)
{
	MfxCodeLock(this);

	if (*ret)
	{
		(*ret) = myBackBrush->Clone();
		return RFine;
	}
	else
	{
		return RFail;
	}
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetTextBrush(Gdiplus::Brush** ret)
{
	MfxCodeLock(this);

	if (*ret)
	{
		(*ret) = myTextBrush->Clone();
		return RFine;
	}
	else
	{
		return RFail;
	}
}