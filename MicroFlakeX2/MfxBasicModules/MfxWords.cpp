#include "pch.h"
#include "MfxBasicGraph.h"

using MicroFlakeX::MfxWords;
BEGIN_INITDATA(MfxWords)
INITDATA(MfxWords, Clone, 0);
INITDATA(MfxWords, Similar, 1);
INITDATA(MfxWords, SetDC, 2);
INITDATA(MfxWords, GetDC, 3);
INITDATA(MfxWords, Draw, 4);
INITDATA(MfxWords, SetRect, 5);
INITDATA(MfxWords, SetSize, 6);
INITDATA(MfxWords, SetPoint, 7);
INITDATA(MfxWords, GetRect, 8);
INITDATA(MfxWords, GetSize, 9);
INITDATA(MfxWords, GetPoint, 10);
INITDATA(MfxWords, GetRegion, 11);
INITDATA(MfxWords, CollisionWith, 12);
INITDATA(MfxWords, SetCollisionBlock, 13);
END_INITDATA;
BEGIN_AUTOMAP(MfxWords)
CASE_FUNC_P1(MfxWords, Clone, 0)
CASE_FUNC_P1(MfxWords, Similar, 1)
CASE_FUNC_P1(MfxWords, SetDC, 2)
CASE_FUNC_P1(MfxWords, GetDC, 3)
CASE_FUNC_P0(MfxWords, Draw, 4)
CASE_FUNC_P1(MfxWords, SetRect, 5)
CASE_FUNC_P1(MfxWords, SetSize, 6)
CASE_FUNC_P1(MfxWords, SetPoint, 7)
CASE_FUNC_P1(MfxWords, GetRect, 8)
CASE_FUNC_P1(MfxWords, GetSize, 9)
CASE_FUNC_P1(MfxWords, GetPoint, 10)
CASE_FUNC_P1(MfxWords, GetRegion, 11)
CASE_FUNC_P2(MfxWords, CollisionWith, 12)
CASE_FUNC_P1(MfxWords, SetCollisionBlock, 13)
END_AUTOMAP;


MicroFlakeX::MfxWorlds_Type MicroFlakeX::MfxWords::g_DefType{
	L"Consolas",
	MfxWords_TextX_def | MfxWords_TextY_def, //猟忖電井庁塀
	MfxWords_ShowStyle_null, MfxFontStyle_Regu, //�塋掌駟� - 猟忖鯉塀
	MfxSmoothingMode_Hig, //猟忖紙崙嵎楚
	GdipColor(GdipColor::Black), 16,		//猟忖
	GdipColor(GdipColor::Red), 2,			//円崇
	GdipColor(GdipColor::DarkBlue)		//嘘尚
};


void MicroFlakeX::MfxWords::MfxWordsInitData(MfxWorlds_Type set)
{
	MFXLOCK;
	REALIZE_AUTOBASIC;

	myDC = nullptr;
	myGraphics = nullptr;
	myGraphicsPath = new GdipGraphicsPath;

	myRect = GdipRect(0, 0, 1, 1);
	myText = L"";
	myType = set;
	myFontFamily = new GdipFontFamily(myType.myFontName.c_str());
	myStringFormat = new GdipStringFormat;

	myFramePen = new GdipPen(myType.myFrameColor, myType.myFramePenWidth);
	myBackBrush = new GdipBrushSolid(myType.myBackColor);
	myTextBrush = new GdipBrushSolid(myType.myTextColor);

	myTextRect = *myRect;
	myTextRectPen = new GdipPen(GdipColor::Red, 1);

	myShowBitmap = nullptr;
	myShowGraphics = nullptr;
	myCachedShowBitmap = nullptr;

	myShowRegion = nullptr;
	myBasicRegion = nullptr;
	myCollisionBlock = GdipSize(30, 30);

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
	MFXLOCK;
	MfxWordsInitData(g_DefType);
}

MicroFlakeX::MfxWords::MfxWords(MfxWorlds_Type set)
{
	MFXLOCK;
	MfxWordsInitData(set);
}

MicroFlakeX::MfxWords::~MfxWords()
{
	MFXLOCK;

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
	MFXLOCK;
	MfxCodeLock t_CodeLock2(&rhs);

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
	MFXLOCK;
	myDC = nullptr;
	delete myGraphics;
	myGraphics = nullptr;
}

void MicroFlakeX::MfxWords::Mode_ResetDC(HDC set)
{
	MFXLOCK;
	delete myGraphics;
	myGraphics = nullptr;

	myDC = set;
	myGraphics = new GdipGraphics(myDC);
	ResetCachedShowBitmap();
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::LockResetRegion()
{
	MFXLOCK;
	myResetRegionLock++;
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::UnLockResetRegion()
{
	MFXLOCK;
	myResetRegionLock--;
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::LockResetTextPath()
{
	MFXLOCK;
	myResetTextPathLock++;
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::UnLockResetTextPath()
{
	MFXLOCK;
	myResetTextPathLock--;
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::LockResetShowBitmap()
{
	MFXLOCK;
	myResetShowBitmapLock++;
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::UnLockResetShowBitmap()
{
	MFXLOCK;
	myResetShowBitmapLock--;
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::LockResetCachedShowBitmap()
{
	MFXLOCK;
	myResetShowCachedBitmapLock++;
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::UnLockResetCachedShowBitmap()
{
	MFXLOCK;
	myResetShowCachedBitmapLock--;
	return MfxFine;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::ResetRegion()
{
	MFXLOCK;
	if (myResetRegionLock && !*myShowBitmap)
	{
		return MfxFine;
	}

	if (myShowBitmap.CheckChangeFlag() || myCollisionBlock.CheckChangeFlag())
	{
		myShowBitmap.CleanChangeFlag();

		GdipGraphicsPath t_Path;
		Gdiplus::BitmapData bmpData;
		GdipRect t_LockRect(0, 0, myShowBitmap->GetWidth(), myShowBitmap->GetHeight());
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
						t_Path.AddRectangle(GdipRect(
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
			myBasicRegion = new GdipRegion(&t_Path);
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

		GdipMatrix myMatrix;

		myMatrix.Scale(
			static_cast<FLOAT>((*myRect).Width) / static_cast<FLOAT>(myShowBitmap->GetWidth()),
			static_cast<FLOAT>((*myRect).Height) / static_cast<FLOAT>(myShowBitmap->GetHeight()),
			Gdiplus::MatrixOrderAppend
		);

		myMatrix.Translate((*myRect).X, (*myRect).Y, Gdiplus::MatrixOrderAppend);
		myShowRegion->Transform(&myMatrix);
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::ResetTextPath()
{
	MFXLOCK;
	if (myResetTextPathLock)
	{
		return MfxFail;
	}

	myGraphicsPath->Reset();
	myGraphicsPath->AddString(
		myText.c_str(), -1,
		myFontFamily, myType.myFontStyle, myType.myTextSize_em,
		GdipRect(0, 0, (*myRect).Width, (*myRect).Height), myStringFormat
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
		GdipRect(0, myTextRect.Y, (*myRect).Width, (*myRect).Height), myStringFormat
	);

	ResetShowBitmap();
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::ResetShowBitmap() //嶷鮫bitmap
{
	MFXLOCK;
	if (myResetShowBitmapLock)
	{
		return MfxFail;
	}

	delete *myShowBitmap;
	myShowBitmap = nullptr;
	delete myShowGraphics;
	myShowGraphics = nullptr;

	myShowBitmap = new GdipBitmap((*myRect).Width, (*myRect).Height, PixelFormat32bppARGB);
	myShowGraphics = new GdipGraphics(*myShowBitmap);

	myShowGraphics->SetSmoothingMode((Gdiplus::SmoothingMode)myType.mySmoothingMode);
	myShowGraphics->Clear(GdipColor(0, 0, 0, 0));

	if (myType.myShowStyle & MfxWords_ShowStyle_fill)
	{
		myShowGraphics->FillRectangle(myBackBrush, GdipRect(0, 0, (*myRect).Width, (*myRect).Height));
	}
	if (myType.myShowStyle & MfxWords_ShowStyle_fram)
	{
		myShowGraphics->DrawRectangle(myFramePen, GdipRect(0, 0, (*myRect).Width - 1, (*myRect).Height - 1));
	}

	myShowGraphics->FillPath(myTextBrush, myGraphicsPath);

	ResetRegion();
	ResetCachedShowBitmap();
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::ResetCachedShowBitmap()
{
	if (myResetShowCachedBitmapLock || !*myShowBitmap)
	{
		return MfxFail;
	}

	if (myGraphics)
	{
		delete myCachedShowBitmap;
		myCachedShowBitmap = nullptr;
		myCachedShowBitmap = new GdipCachedBitmap(*myShowBitmap, myGraphics);
	}

	return MfxFine;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::Clone(MfxWords** ret)
{
	MFXLOCK;
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
		return MfxFine;
	}
	return MfxFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::Similar(MfxWords* set)
{
	MFXLOCK;
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
		return MfxFine;
	}
	else
	{
		return MfxFail;
	}
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetDC(HDC set)
{
	MFXLOCK;
	if (set)
	{
		Mode_ResetDC(set);
	}
	else
	{
		Mode_ClearDC();
	}
	return MfxFine;;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetDC(HDC* ret)
{
	MFXLOCK;
	if (ret)
	{
		(*ret) = myDC;
		return MfxFine;
	}
	return MfxFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetShowBitmap(GdipBitmap** ret)
{
	MFXLOCK;

	if (ret)
	{
		GdipBitmap* t_Bitmap = nullptr;
		t_Bitmap = myShowBitmap->Clone(GdipRect(0, 0, (*myRect).Width, (*myRect).Height), PixelFormat32bppARGB);
		if (t_Bitmap)
		{
			(*ret) = t_Bitmap;
		}
		return MfxFine;
	}
	else
	{
		return MfxFail;
	}
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::DrawBitmap(GdipGraphics* set)
{
	MFXLOCK;
	if (set)
	{
		set->DrawImage(*myShowBitmap, GdipPoint((*myRect).X, (*myRect).Y));
		return MfxFine;
	}
	else
	{
		return MfxFail;
	}
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::Draw()
{
	MFXLOCK;
	if (myCachedShowBitmap && myGraphics)
	{
		myGraphics->DrawCachedBitmap(myCachedShowBitmap, (*myRect).X, (*myRect).Y);
		return MfxFine;
	}
	return MfxFail;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetText(MfxStrW set)
{
	MFXLOCK;

	myText = set;
	ResetTextPath();
	return MfxFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetText(MfxStrW* ret)
{
	MFXLOCK;
	(*ret) = myText;
	return MfxFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetStringFormat(GdipStringFormat* set)
{
	MFXLOCK;
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
		return MfxFine;
	}
	else
	{
		return MfxFail;
	}
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetStringFormat(GdipStringFormat** ret)
{
	MFXLOCK;

	if (ret)
	{
		(*ret) = myStringFormat->Clone();
		ResetTextPath();
		return MfxFine;
	}
	else
	{
		return MfxFail;
	}
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetType(MfxWorlds_Type set)
{
	MFXLOCK;
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
	return MfxFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetFontName(MfxStrW set)
{
	MFXLOCK;

	if (set.size())
	{
		myType.myFontName = set;
		GdipFontFamily* t_FontFamily = new GdipFontFamily(set.c_str());
		if (t_FontFamily->IsAvailable())
		{
			delete myFontFamily;
			myFontFamily = nullptr;
			myFontFamily = t_FontFamily;

			ResetTextPath();
			return MfxFine;
		}
	}
	else
	{
		return MfxFail;
	}
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetTextXY(MfxWords_TextXY set)
{
	MFXLOCK;

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
		return MfxFine;
	}
	else
	{
		return MfxFail;
	}
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetShowStyle(MfxWords_ShowStyle set)
{
	MFXLOCK;

	if (myType.myShowStyle != set)
	{
		myType.myShowStyle = set;

		ResetShowBitmap();
		return MfxFine;
	}
	else
	{
		return MfxFail;
	}
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetFontStyle(MfxFontStyle set)
{
	MFXLOCK;

	if (myType.myFontStyle != set)
	{
		myType.myFontStyle = set;

		ResetTextPath();
		return MfxFine;
	}
	else
	{
		return MfxFail;
	}
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetSmoothingMode(MfxSmoothingMode_EN set)
{
	MFXLOCK;

	if (myType.mySmoothingMode != set)
	{
		myType.mySmoothingMode = set;

		ResetShowBitmap();
		return MfxFine;
	}
	else
	{
		return MfxFail;
	}
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetTextColor(GdipColor set)
{
	MFXLOCK;

	myType.myTextColor = set;

	delete myTextBrush;
	myTextBrush = nullptr;
	myTextBrush = new GdipBrushSolid(myType.myTextColor);

	ResetShowBitmap();
	return MfxFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetTextSize_em(MfxPenWidth set)
{
	MFXLOCK;

	if (set > 0)
	{
		myType.myTextSize_em = set;
		ResetTextPath();
		return MfxFine;
	}
	else
	{
		return MfxFail;
	}
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetFrameColor(GdipColor set)
{
	MFXLOCK;

	myType.myFrameColor = set;

	delete myFramePen;
	myFramePen = nullptr;
	myFramePen = new GdipPen(myType.myFrameColor, myType.myFramePenWidth);

	ResetShowBitmap();
	return MfxFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetFramePenWidth(MfxPenWidth set)
{
	MFXLOCK;

	if (set > 0)
	{
		myType.myFramePenWidth = set;

		delete myFramePen;
		myFramePen = nullptr;
		myFramePen = new GdipPen(myType.myFrameColor, myType.myFramePenWidth);

		ResetShowBitmap();
		return MfxFine;
	}
	else
	{
		return MfxFail;
	}
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetBackColor(GdipColor set)
{
	MFXLOCK;

	myType.myBackColor = set;

	delete myBackBrush;
	myBackBrush = nullptr;
	myBackBrush = new GdipBrushSolid(myType.myBackColor);

	ResetShowBitmap();

	return MfxFine;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetType(MfxWorlds_Type* ret)
{
	MFXLOCK;

	(*ret) = myType;
	return MfxFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetFontName(MfxStrW* ret)
{
	MFXLOCK;

	(*ret) = myType.myFontName;
	return MfxFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetTextXY(MfxWords_TextXY* ret)
{
	MFXLOCK;

	(*ret) = myType.myTextXY;
	return MfxFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetShowStyle(MfxWords_ShowStyle* ret)
{
	MFXLOCK;

	(*ret) = myType.myShowStyle;
	return MfxFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetFontStyle(MfxFontStyle* ret)
{
	MFXLOCK;

	(*ret) = myType.myFontStyle;
	return MfxFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetSmoothingMode(MfxSmoothingMode_EN* ret)
{
	MFXLOCK;

	(*ret) = myType.mySmoothingMode;
	return MfxFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetTextColor(GdipColor* ret)
{
	MFXLOCK;

	(*ret) = myType.myTextColor;
	return MfxFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetTextSize_em(MfxPenWidth* ret)
{
	MFXLOCK;

	(*ret) = myType.myTextSize_em;
	return MfxFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetFrameColor(GdipColor* ret)
{
	MFXLOCK;

	(*ret) = myType.myFrameColor;
	return MfxFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetFramePenWidth(MfxPenWidth* ret)
{
	MFXLOCK;

	(*ret) = myType.myFramePenWidth;
	return MfxFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetBackColor(GdipColor* ret)
{
	MFXLOCK;

	(*ret) = myType.myBackColor;
	return MfxFine;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetRect(GdipRect set)
{
	MFXLOCK;
	SetSize(GdipSize(set.Width, set.Height));
	SetPoint(GdipPoint(set.X, set.Y));
	return MfxFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetSize(GdipSize set)
{
	MFXLOCK;

	if ((*myRect).Width != set.Width || (*myRect).Height != set.Height)
	{
		myRect = GdipRect((*myRect).X, (*myRect).Y, set.Width, set.Height);
		ResetTextPath();
		return MfxFine;
	}
	else
	{
		return MfxFail;
	}
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetPoint(GdipPoint set)
{
	MFXLOCK;
	if ((*myRect).X != set.X || (*myRect).Y != set.Y) //Size音�犁伐登菻�厚個
	{
		myRect = GdipRect(set.X, set.Y, (*myRect).Width, (*myRect).Height);
		ResetRegion();
		return MfxFine;
	}
	return MfxFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetCollisionBlock(GdipSize set)
{
	if (set.Width > 2 && set.Height > 2)
	{
		myCollisionBlock = set;
		ResetRegion();
		return MfxFine;
	}
	else
	{
		return MfxFail;
	}

}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::CollisionWith(MfxBasicGraph* set, bool* ret)
{
	if (set && ret)
	{
		*ret = false;
		GdipRect rhsRect;
		set->AutoFunc(L"GetRect", &rhsRect);
		if ((*myRect).IntersectsWith(rhsRect))
		{
			*ret = true;
			if (myGraphics)
			{
				GdipRegion* lhsRegion = nullptr, * rhsRegion = nullptr;
				if (MFXSUCCEEDED(set->AutoFunc(L"GetRegion", &rhsRegion)))
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
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetFramePen(GdipPen* set)
{
	MFXLOCK;

	if (set)
	{
		delete myFramePen;
		myFramePen = nullptr;
		myFramePen = set->Clone();

		ResetShowBitmap();
		return MfxFine;
	}
	else
	{
		return MfxFail;
	}
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetBackBrush(GdipBrush* set)
{
	MFXLOCK;

	if (set)
	{
		delete myBackBrush;
		myBackBrush = nullptr;
		myBackBrush = set->Clone();

		ResetShowBitmap();
		return MfxFine;
	}
	else
	{
		return MfxFail;
	}
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::SetTextBrush(GdipBrush* set)
{
	MFXLOCK;

	if (set)
	{
		delete myTextBrush;
		myTextBrush = nullptr;
		myTextBrush = set->Clone();

		ResetShowBitmap();
		return MfxFine;
	}
	else
	{
		return MfxFail;
	}
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetRect(GdipRect* ret)
{
	MFXLOCK;

	(*ret) = *myRect;
	return MfxFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetSize(GdipSize* ret)
{
	MFXLOCK;

	(*ret).Width = (*myRect).Width;
	(*ret).Height = (*myRect).Height;
	return MfxFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetPoint(GdipPoint* ret)
{
	MFXLOCK;

	(*ret).X = (*myRect).X;
	(*ret).Y = (*myRect).Y;
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetRegion(GdipRegion** ret)
{
	MFXLOCK;
	if (ret && myBasicRegion)
	{
		*ret = myBasicRegion->Clone();
		return MfxFine;
	}
	return MfxFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetRegionBlock(GdipSize* ret)
{
	MFXLOCK;
	(*ret) = *myCollisionBlock;
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetFramePen(GdipPen** ret)
{
	MFXLOCK;

	if (*ret)
	{
		(*ret) = myFramePen->Clone();
		return MfxFine;
	}
	else
	{
		return MfxFail;
	}
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetBackBrush(GdipBrush** ret)
{
	MFXLOCK;

	if (*ret)
	{
		(*ret) = myBackBrush->Clone();
		return MfxFine;
	}
	else
	{
		return MfxFail;
	}
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::GetTextBrush(GdipBrush** ret)
{
	MFXLOCK;

	if (*ret)
	{
		(*ret) = myTextBrush->Clone();
		return MfxFine;
	}
	else
	{
		return MfxFail;
	}
}