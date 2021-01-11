#include "pch.h"
#include "MfxBasicGraph.h"

using MicroFlakeX::MfxImage;
BEGIN_INITDATA(MfxImage)
INITDATA(MfxImage, Clone, 0);
INITDATA(MfxImage, Similar, 1);
INITDATA(MfxImage, SetDC, 2);
INITDATA(MfxImage, GetDC, 3);
INITDATA(MfxImage, Draw, 4);
INITDATA(MfxImage, SetRect, 5);
INITDATA(MfxImage, SetSize, 6);
INITDATA(MfxImage, SetPoint, 7);
INITDATA(MfxImage, GetRect, 8);
INITDATA(MfxImage, GetSize, 9);
INITDATA(MfxImage, GetPoint, 10);
INITDATA(MfxImage, GetRegion, 11);
INITDATA(MfxImage, CollisionWith, 12);
INITDATA(MfxImage, SetCollisionBlock, 13);
END_INITDATA;
BEGIN_AUTOMAP(MfxImage)
CASE_FUNC_P1(MfxImage, Clone, 0)
CASE_FUNC_P1(MfxImage, Similar, 1)
CASE_FUNC_P1(MfxImage, SetDC, 2)
CASE_FUNC_P1(MfxImage, GetDC, 3)
CASE_FUNC_P0(MfxImage, Draw, 4)
CASE_FUNC_P1(MfxImage, SetRect, 5)
CASE_FUNC_P1(MfxImage, SetSize, 6)
CASE_FUNC_P1(MfxImage, SetPoint, 7)
CASE_FUNC_P1(MfxImage, GetRect, 8)
CASE_FUNC_P1(MfxImage, GetSize, 9)
CASE_FUNC_P1(MfxImage, GetPoint, 10)
CASE_FUNC_P1(MfxImage, GetRegion, 11)
CASE_FUNC_P2(MfxImage, CollisionWith, 12)
CASE_FUNC_P1(MfxImage, SetCollisionBlock, 13)
END_AUTOMAP;


void MicroFlakeX::MfxImage::MfxImageInitData()
{
	MFXLOCK;
	REALIZE_AUTOBASIC;

	myRect = GdipRect(0, 0, 1, 1);

	myBasicBitmap = nullptr;
	myImageQuality = MfxInterpolationMode_Def;

	myDC = nullptr;
	myGraphics = nullptr;

	myShowBitmap = nullptr;
	myCachedShowBitmap = nullptr;

	myShowRegion = nullptr;
	myBasicRegion = nullptr;
	myCollisionBlock = GdipSize(30, 30);

	myResetRegionLock = 0;
	myResetShowBitmapLock = 0;
	myResetShowCachedBitmapLock = 0;
}

MicroFlakeX::MfxImage::MfxImage()
{
	MFXLOCK;
	MfxImageInitData();

	FromColor(GdipColor(0, 0, 0, 0));
}

MicroFlakeX::MfxImage::~MfxImage()
{
	MFXLOCK;
	delete *myBasicBitmap;
	myBasicBitmap = nullptr;

	delete myBasicRegion;
	myBasicRegion = nullptr;
	delete myShowBitmap;
	myShowBitmap = nullptr;
	delete myCachedShowBitmap;
	myCachedShowBitmap = nullptr;

	delete myGraphics;
	myGraphics = nullptr;
}

void MicroFlakeX::MfxImage::operator=(MfxImage& rhs)
{
	MFXLOCK;
	MfxCodeLock t_CodeLock2(&rhs);
	LockResetShowBitmap();
	LockResetCachedShowBitmap();

	SetDC(rhs.myDC);
	SetRect(*(rhs.myRect));
	FromBitmap(*(rhs.myBasicBitmap));
	
	UnLockResetShowBitmap();
	UnLockResetCachedShowBitmap();

	ResetShowBitmap();
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

void MicroFlakeX::MfxImage::Mode_ClearDC()
{
	MFXLOCK;
	myDC = nullptr;
	delete myGraphics;
	myGraphics = nullptr;
}

void MicroFlakeX::MfxImage::Mode_ResetDC(HDC set)
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

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::LockResetRegion()
{
	MFXLOCK;
	myResetRegionLock++;
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::UnLockResetRegion()
{
	MFXLOCK;
	myResetRegionLock--;
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::LockResetShowBitmap()
{
	MFXLOCK;
	myResetShowBitmapLock++;
	return MfxFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::UnLockResetShowBitmap()
{
	MFXLOCK;
	myResetShowBitmapLock--;
	return MfxFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::LockResetCachedShowBitmap()
{
	MFXLOCK;
	myResetShowCachedBitmapLock++;
	return MfxFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::UnLockResetCachedShowBitmap()
{
	MFXLOCK;
	myResetShowCachedBitmapLock--;
	return MfxFine;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::ResetRegion()
{
	MFXLOCK;
	if (myResetRegionLock && !*myBasicBitmap)
	{
		return MfxFine;
	}

	if (myBasicBitmap.CheckChangeFlag() || myCollisionBlock.CheckChangeFlag())
	{
		myBasicBitmap.CleanChangeFlag();

		GdipGraphicsPath t_Path;
		Gdiplus::BitmapData bmpData;
		GdipRect t_LockRect(0, 0, myBasicBitmap->GetWidth(), myBasicBitmap->GetHeight());
		if (myBasicBitmap->LockBits(&t_LockRect, Gdiplus::ImageLockModeRead, PixelFormat32bppARGB, &bmpData) == Gdiplus::Ok)
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
			myBasicBitmap->UnlockBits(&bmpData);
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
			static_cast<FLOAT>((*myRect).Width) / static_cast<FLOAT>(myBasicBitmap->GetWidth()),
			static_cast<FLOAT>((*myRect).Height) / static_cast<FLOAT>(myBasicBitmap->GetHeight()),
			Gdiplus::MatrixOrderAppend
		);

		myMatrix.Translate((*myRect).X, (*myRect).Y, Gdiplus::MatrixOrderAppend);
		myShowRegion->Transform(&myMatrix);
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::ResetShowBitmap()
{
	MFXLOCK;
	if (myResetShowBitmapLock || !*myBasicBitmap) //頁倦紗墮阻児粥夕頭
	{
		return MfxFail;
	}

	GdipBitmap* t_Bitmap = new Gdiplus::Bitmap((*myRect).Width, (*myRect).Height, PixelFormat32bppARGB);
	GdipGraphics t_Graphics(t_Bitmap);
	t_Graphics.SetInterpolationMode((Gdiplus::InterpolationMode)myImageQuality);
	t_Graphics.DrawImage(*myBasicBitmap, 0, 0, (*myRect).Width, (*myRect).Height);

	delete myShowBitmap;
	myShowBitmap = nullptr;
	myShowBitmap = t_Bitmap;

	ResetRegion();
	ResetCachedShowBitmap();
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::ResetCachedShowBitmap()
{
	MFXLOCK;
	if (myResetShowCachedBitmapLock || !myShowBitmap)
	{
		return MfxFail;
	}

	if (myGraphics)
	{
		delete myCachedShowBitmap;
		myCachedShowBitmap = nullptr;
		myCachedShowBitmap = new GdipCachedBitmap(myShowBitmap, myGraphics);
	}
	return MfxFine;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::Clone(MfxImage** ret)
{
	MFXLOCK;

	if (ret)
	{
		MfxImage* t_Image = new MfxImage;

		t_Image->LockResetShowBitmap();
		t_Image->LockResetCachedShowBitmap();

		t_Image->SetDC(myDC);
		t_Image->SetRect(*myRect);
		t_Image->FromBitmap(*myBasicBitmap);
		t_Image->SetCollisionBlock(*myCollisionBlock);
		
		t_Image->UnLockResetShowBitmap();
		t_Image->UnLockResetCachedShowBitmap();

		t_Image->ResetShowBitmap();

		(*ret) = t_Image;
		return MfxFine;
	}
	else
	{
		return MfxFail;
	}
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::Similar(MfxImage* set)
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


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::SetDC(HDC set)
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
	return MfxFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::GetDC(HDC* get)
{
	MFXLOCK;
	if (get)
	{
		(*get) = myDC;
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

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::FromFile(MfxStrW path)
{
	MFXLOCK;
	if (path.size() > 3) //補秘嗤丼
	{
		GdipBitmap* t_Bitmap = nullptr;
		t_Bitmap = GdipBitmap::FromFile(path.c_str());
		if (t_Bitmap) //頁倦嬬校屎鳩紗墮夕頭
		{
			myRect = GdipRect((*myRect).X, (*myRect).Y,
				t_Bitmap->GetWidth(), t_Bitmap->GetHeight());

			delete *myBasicBitmap;
			myBasicBitmap = nullptr;
			myBasicBitmap = t_Bitmap;

			ResetShowBitmap();
			return MfxFine;
		}
	}
	return MfxFail;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::FromColor(GdipColor set)
{
	MFXLOCK;
	GdipBitmap* t_Bitmap = new Gdiplus::Bitmap((*myRect).Width, (*myRect).Height, PixelFormat32bppARGB);
	Gdiplus::Graphics t_Graphics(t_Bitmap);
	t_Graphics.Clear(set);

	delete *myBasicBitmap;
	myBasicBitmap = nullptr;
	myBasicBitmap = t_Bitmap;

	ResetShowBitmap();
	return MfxFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::FromBitmap(GdipBitmap* set)
{
	MFXLOCK;
	if (set) //補秘頁倦嗤丼
	{
		GdipRect t_Rect(0, 0, set->GetWidth(), set->GetHeight());
		GdipBitmap* t_NewBitmap = nullptr;
		t_NewBitmap = set->Clone(t_Rect, PixelFormat32bppARGB);
		if (t_NewBitmap) //頁倦針臓撹孔
		{
			myRect = GdipRect((*myRect).X, (*myRect).Y,
				t_NewBitmap->GetWidth(), t_NewBitmap->GetHeight());

			delete *myBasicBitmap; 
			myBasicBitmap = nullptr;
			myBasicBitmap = t_NewBitmap;

			ResetShowBitmap();
			return MfxFine;
		}
	}
	return MfxFail;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::GetShowBitmap(GdipBitmap** ret)
{
	MFXLOCK;
	if (ret)
	{
		GdipBitmap* t_Bitmap = nullptr;
		t_Bitmap = myShowBitmap->Clone(GdipRect(0, 0, (*myRect).Width, (*myRect).Height), PixelFormat32bppARGB);
		if (t_Bitmap)
		{
			(*ret) = t_Bitmap;
			return MfxFine;
		}
	}
	return MfxFail;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::GetBasicBitmap(GdipBitmap** ret)
{
	MFXLOCK;
	if (ret)
	{
		GdipBitmap* t_Bitmap = nullptr;
		t_Bitmap = myBasicBitmap->Clone(GdipRect(0, 0, (*myRect).Width, (*myRect).Height), PixelFormat32bppARGB);
		if (t_Bitmap)
		{
			(*ret) = t_Bitmap;
			return MfxFine;
		}
	}
	return MfxFail;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::SetBasicBitmap(GdipBitmap* set)
{
	MFXLOCK;
	if (set)
	{
		GdipBitmap* t_Bitmap = nullptr;
		t_Bitmap = set->Clone(GdipRect(0, 0, set->GetWidth(), set->GetHeight()), PixelFormat32bppARGB);
		if (t_Bitmap)
		{
			delete *myBasicBitmap;
			myBasicBitmap = nullptr;
			myBasicBitmap = t_Bitmap;

			ResetShowBitmap();
			return MfxFine;
		}
	}
	return MfxFail;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::DrawBitmap(GdipGraphics* set)
{
	MFXLOCK;
	if (set)
	{
		set->DrawImage(myShowBitmap, GdipPoint((*myRect).X, (*myRect).Y));
		return MfxFine;
	}
	else
	{
		return MfxFail;
	}
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::Draw()
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


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::SetQuality(MfxInterpolationMode_EN set)
{
	MFXLOCK;
	if (set && myImageQuality!= set) //補秘栽隈
	{
		myImageQuality = set;
		if (myGraphics)
		{
			myGraphics->SetInterpolationMode((Gdiplus::InterpolationMode)myImageQuality);
		}

		ResetShowBitmap();
		return MfxFine;
	}
	return MfxFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::SetRect(GdipRect set)
{
	MFXLOCK;
	SetSize(GdipSize(set.Width, set.Height));
	SetPoint(GdipPoint(set.X, set.Y));
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::SetSize(GdipSize set)
{
	MFXLOCK;
	if ((*myRect).Width != set.Width || (*myRect).Height != set.Height)
	{
		myRect = GdipRect((*myRect).X, (*myRect).Y, set.Width, set.Height);
		ResetShowBitmap();
		return MfxFine;
	}
	return MfxFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::SetPoint(GdipPoint set)
{
	MFXLOCK;
	if ((*myRect).X != set.X || (*myRect).Y != set.Y)
	{
		myRect = GdipRect(set.X, set.Y, (*myRect).Width, (*myRect).Height);
		ResetRegion();
		return MfxFine;
	}
	return MfxFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::SetCollisionBlock(GdipSize set)
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

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::CollisionWith(MfxBasicGraph* set, bool* ret)
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

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::CropSize(GdipColor set)
{
	MFXLOCK;
	GdipBitmap* t_Bitmap = new GdipBitmap(myBasicBitmap->GetWidth(), myBasicBitmap->GetHeight(), PixelFormat32bppARGB);
	GdipGraphics graphics(t_Bitmap);

	GdipImageAttributes remapAttributes;
	GdipColorMap setToAlpha;
	setToAlpha.oldColor = set;
	setToAlpha.newColor = GdipColor(0, 0, 0, 0);
	remapAttributes.SetRemapTable(1, &setToAlpha);

	Gdiplus::RectF t_RectF(0, 0, (*myRect).Width, (*myRect).Height);

	graphics.DrawImage(
		*myBasicBitmap, t_RectF,
		0, 0, myBasicBitmap->GetWidth(), myBasicBitmap->GetHeight(),
		Gdiplus::UnitPixel,
		&remapAttributes, NULL, NULL);

	delete *myBasicBitmap;
	myBasicBitmap = nullptr;
	myBasicBitmap = t_Bitmap;

	ResetShowBitmap();
	return MfxFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::ChangeColor(GdipColor oldColor, GdipColor newColor)
{
	MFXLOCK;
	GdipBitmap* t_Bitmap = new GdipBitmap(myBasicBitmap->GetWidth(), myBasicBitmap->GetHeight(), PixelFormat32bppARGB);
	GdipGraphics graphics(t_Bitmap);

	GdipImageAttributes remapAttributes;
	GdipColorMap setToAlpha;
	setToAlpha.oldColor = oldColor;
	setToAlpha.newColor = newColor;
	remapAttributes.SetRemapTable(1, &setToAlpha);

	Gdiplus::RectF t_RectF(0, 0, (*myRect).Width, (*myRect).Height);

	graphics.DrawImage(
		*myBasicBitmap, t_RectF,
		0, 0, myBasicBitmap->GetWidth(), myBasicBitmap->GetHeight(),
		Gdiplus::UnitPixel,
		&remapAttributes, NULL, NULL);

	delete *myBasicBitmap;
	myBasicBitmap = nullptr;
	myBasicBitmap = t_Bitmap;

	ResetShowBitmap();
	return MfxFine;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::GetQuality(MfxInterpolationMode_EN* get)
{
	MFXLOCK;
	(*get) = myImageQuality;
	return MfxFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::GetRegion(GdipRegion** ret)
{
	MFXLOCK;
	if (ret && myShowRegion)
	{
		*ret = myShowRegion->Clone();
		return MfxFine;
	}
	return MfxFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::GetRegionBlock(GdipSize* ret)
{
	MFXLOCK;
	(*ret) = *myCollisionBlock;
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::GetRect(GdipRect* ret)
{
	MFXLOCK;
	(*ret) = *myRect;
	return MfxFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::GetSize(GdipSize* ret)
{
	MFXLOCK;
	(*ret).Width = (*myRect).Width;
	(*ret).Height = (*myRect).Height;
	return MfxFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::GetPoint(GdipPoint* ret)
{
	MFXLOCK;
	(*ret).X = (*myRect).X;
	(*ret).Y = (*myRect).Y;
	return MfxFine;
}