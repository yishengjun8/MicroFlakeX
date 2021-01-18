#include "pch.h"
#include "MfxGraph.h"

MfxObject_Init_0(MfxImage)
MfxObject_Init_1(MfxImage)
MfxObject_Init_2(MfxImage, MfxGraph);

void MicroFlakeX::MfxImage::MfxImageInitData()
{
	MfxCodeLock(this);

	myRect = Gdiplus::Rect(0, 0, 1, 1);

	myBasicBitmap = nullptr;
	myImageQuality = MfxInterpolationMode_Def;

	myDC = nullptr;
	myGraphics = nullptr;

	myShowBitmap = nullptr;
	myCachedShowBitmap = nullptr;

	myShowRegion = nullptr;
	myBasicRegion = nullptr;
	myCollisionBlock = Gdiplus::Size(30, 30);

	myResetRegionLock = 0;
	myResetShowBitmapLock = 0;
	myResetShowCachedBitmapLock = 0;
}

MicroFlakeX::MfxImage::MfxImage()
{
	MfxCodeLock(this);
	MfxImageInitData();

	FromColor(Gdiplus::Color(0, 0, 0, 0));
}

MicroFlakeX::MfxImage::~MfxImage()
{
	MfxCodeLock(this);
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
	MfxCodeLock(this);
	MfxLock t_CodeLock2(&rhs);
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
	MfxCodeLock(this);
	myDC = nullptr;
	delete myGraphics;
	myGraphics = nullptr;
}

void MicroFlakeX::MfxImage::Mode_ResetDC(HDC set)
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

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::LockResetRegion()
{
	MfxCodeLock(this);
	myResetRegionLock++;
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::UnLockResetRegion()
{
	MfxCodeLock(this);
	myResetRegionLock--;
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::LockResetShowBitmap()
{
	MfxCodeLock(this);
	myResetShowBitmapLock++;
	return RFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::UnLockResetShowBitmap()
{
	MfxCodeLock(this);
	myResetShowBitmapLock--;
	return RFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::LockResetCachedShowBitmap()
{
	MfxCodeLock(this);
	myResetShowCachedBitmapLock++;
	return RFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::UnLockResetCachedShowBitmap()
{
	MfxCodeLock(this);
	myResetShowCachedBitmapLock--;
	return RFine;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::ResetRegion()
{
	MfxCodeLock(this);
	if (myResetRegionLock && !*myBasicBitmap)
	{
		return RFine;
	}

	if (myBasicBitmap.CheckChangeFlag() || myCollisionBlock.CheckChangeFlag())
	{
		myBasicBitmap.CleanChangeFlag();

		Gdiplus::GraphicsPath t_Path;
		Gdiplus::BitmapData bmpData;
		Gdiplus::Rect t_LockRect(0, 0, myBasicBitmap->GetWidth(), myBasicBitmap->GetHeight());
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
						t_Path.AddRectangle(Gdiplus::Rect(
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
			static_cast<FLOAT>((*myRect).Width) / static_cast<FLOAT>(myBasicBitmap->GetWidth()),
			static_cast<FLOAT>((*myRect).Height) / static_cast<FLOAT>(myBasicBitmap->GetHeight()),
			Gdiplus::MatrixOrderAppend
		);

		myMatrix.Translate((*myRect).X, (*myRect).Y, Gdiplus::MatrixOrderAppend);
		myShowRegion->Transform(&myMatrix);
	}
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::ResetShowBitmap()
{
	MfxCodeLock(this);
	if (myResetShowBitmapLock || !*myBasicBitmap) //頁倦紗墮阻児粥夕頭
	{
		return RFail;
	}

	Gdiplus::Bitmap* t_Bitmap = new Gdiplus::Bitmap((*myRect).Width, (*myRect).Height, PixelFormat32bppARGB);
	Gdiplus::Graphics t_Graphics(t_Bitmap);
	t_Graphics.SetInterpolationMode((Gdiplus::InterpolationMode)myImageQuality);
	t_Graphics.DrawImage(*myBasicBitmap, 0, 0, (*myRect).Width, (*myRect).Height);

	delete myShowBitmap;
	myShowBitmap = nullptr;
	myShowBitmap = t_Bitmap;

	ResetRegion();
	ResetCachedShowBitmap();
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::ResetCachedShowBitmap()
{
	MfxCodeLock(this);
	if (myResetShowCachedBitmapLock || !myShowBitmap)
	{
		return RFail;
	}

	if (myGraphics)
	{
		delete myCachedShowBitmap;
		myCachedShowBitmap = nullptr;
		myCachedShowBitmap = new Gdiplus::CachedBitmap(myShowBitmap, myGraphics);
	}
	return RFine;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::Clone(MfxImage** ret)
{
	MfxCodeLock(this);

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
		return RFine;
	}
	else
	{
		return RFail;
	}
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::Similar(MfxImage* set)
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


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::SetDC(HDC set)
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
	return RFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::GetDC(HDC* get)
{
	MfxCodeLock(this);
	if (get)
	{
		(*get) = myDC;
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

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::FromFile(MfxStrW path)
{
	MfxCodeLock(this);
	if (path.size() > 3) //補秘嗤丼
	{
		Gdiplus::Bitmap* t_Bitmap = nullptr;
		t_Bitmap = Gdiplus::Bitmap::FromFile(path.c_str());
		if (t_Bitmap) //頁倦嬬校屎鳩紗墮夕頭
		{
			myRect = Gdiplus::Rect((*myRect).X, (*myRect).Y,
				t_Bitmap->GetWidth(), t_Bitmap->GetHeight());

			delete *myBasicBitmap;
			myBasicBitmap = nullptr;
			myBasicBitmap = t_Bitmap;

			ResetShowBitmap();
			return RFine;
		}
	}
	return RFail;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::FromColor(Gdiplus::Color set)
{
	MfxCodeLock(this);
	Gdiplus::Bitmap* t_Bitmap = new Gdiplus::Bitmap((*myRect).Width, (*myRect).Height, PixelFormat32bppARGB);
	Gdiplus::Graphics t_Graphics(t_Bitmap);
	t_Graphics.Clear(set);

	delete *myBasicBitmap;
	myBasicBitmap = nullptr;
	myBasicBitmap = t_Bitmap;

	ResetShowBitmap();
	return RFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::FromBitmap(Gdiplus::Bitmap* set)
{
	MfxCodeLock(this);
	if (set) //補秘頁倦嗤丼
	{
		Gdiplus::Rect t_Rect(0, 0, set->GetWidth(), set->GetHeight());
		Gdiplus::Bitmap* t_NewBitmap = nullptr;
		t_NewBitmap = set->Clone(t_Rect, PixelFormat32bppARGB);
		if (t_NewBitmap) //頁倦針臓撹孔
		{
			myRect = Gdiplus::Rect((*myRect).X, (*myRect).Y,
				t_NewBitmap->GetWidth(), t_NewBitmap->GetHeight());

			delete *myBasicBitmap; 
			myBasicBitmap = nullptr;
			myBasicBitmap = t_NewBitmap;

			ResetShowBitmap();
			return RFine;
		}
	}
	return RFail;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::GetShowBitmap(Gdiplus::Bitmap** ret)
{
	MfxCodeLock(this);
	if (ret)
	{
		Gdiplus::Bitmap* t_Bitmap = nullptr;
		t_Bitmap = myShowBitmap->Clone(Gdiplus::Rect(0, 0, (*myRect).Width, (*myRect).Height), PixelFormat32bppARGB);
		if (t_Bitmap)
		{
			(*ret) = t_Bitmap;
			return RFine;
		}
	}
	return RFail;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::GetBasicBitmap(Gdiplus::Bitmap** ret)
{
	MfxCodeLock(this);
	if (ret)
	{
		Gdiplus::Bitmap* t_Bitmap = nullptr;
		t_Bitmap = myBasicBitmap->Clone(Gdiplus::Rect(0, 0, (*myRect).Width, (*myRect).Height), PixelFormat32bppARGB);
		if (t_Bitmap)
		{
			(*ret) = t_Bitmap;
			return RFine;
		}
	}
	return RFail;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::SetBasicBitmap(Gdiplus::Bitmap* set)
{
	MfxCodeLock(this);
	if (set)
	{
		Gdiplus::Bitmap* t_Bitmap = nullptr;
		t_Bitmap = set->Clone(Gdiplus::Rect(0, 0, set->GetWidth(), set->GetHeight()), PixelFormat32bppARGB);
		if (t_Bitmap)
		{
			delete *myBasicBitmap;
			myBasicBitmap = nullptr;
			myBasicBitmap = t_Bitmap;

			ResetShowBitmap();
			return RFine;
		}
	}
	return RFail;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::DrawBitmap(Gdiplus::Graphics* set)
{
	MfxCodeLock(this);
	if (set)
	{
		set->DrawImage(myShowBitmap, Gdiplus::Point((*myRect).X, (*myRect).Y));
		return RFine;
	}
	else
	{
		return RFail;
	}
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::Draw()
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


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::SetQuality(MfxInterpolationMode_EN set)
{
	MfxCodeLock(this);
	if (set && myImageQuality!= set) //補秘栽隈
	{
		myImageQuality = set;
		if (myGraphics)
		{
			myGraphics->SetInterpolationMode((Gdiplus::InterpolationMode)myImageQuality);
		}

		ResetShowBitmap();
		return RFine;
	}
	return RFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::SetRect(Gdiplus::Rect set)
{
	MfxCodeLock(this);
	SetSize(Gdiplus::Size(set.Width, set.Height));
	SetPoint(Gdiplus::Point(set.X, set.Y));
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::SetSize(Gdiplus::Size set)
{
	MfxCodeLock(this);
	if ((*myRect).Width != set.Width || (*myRect).Height != set.Height)
	{
		myRect = Gdiplus::Rect((*myRect).X, (*myRect).Y, set.Width, set.Height);
		ResetShowBitmap();
		return RFine;
	}
	return RFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::SetPoint(Gdiplus::Point set)
{
	MfxCodeLock(this);
	if ((*myRect).X != set.X || (*myRect).Y != set.Y)
	{
		myRect = Gdiplus::Rect(set.X, set.Y, (*myRect).Width, (*myRect).Height);
		ResetRegion();
		return RFine;
	}
	return RFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::SetCollisionBlock(Gdiplus::Size set)
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

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::CollisionWith(MfxGraph* set, bool* ret)
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

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::CropSize(Gdiplus::Color set)
{
	MfxCodeLock(this);
	Gdiplus::Bitmap* t_Bitmap = new Gdiplus::Bitmap(myBasicBitmap->GetWidth(), myBasicBitmap->GetHeight(), PixelFormat32bppARGB);
	Gdiplus::Graphics graphics(t_Bitmap);

	Gdiplus::ImageAttributes remapAttributes;
	Gdiplus::ColorMap setToAlpha;
	setToAlpha.oldColor = set;
	setToAlpha.newColor = Gdiplus::Color(0, 0, 0, 0);
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
	return RFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::ChangeColor(Gdiplus::Color oldColor, Gdiplus::Color newColor)
{
	MfxCodeLock(this);
	Gdiplus::Bitmap* t_Bitmap = new Gdiplus::Bitmap(myBasicBitmap->GetWidth(), myBasicBitmap->GetHeight(), PixelFormat32bppARGB);
	Gdiplus::Graphics graphics(t_Bitmap);

	Gdiplus::ImageAttributes remapAttributes;
	Gdiplus::ColorMap setToAlpha;
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
	return RFine;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::GetQuality(MfxInterpolationMode_EN* get)
{
	MfxCodeLock(this);
	(*get) = myImageQuality;
	return RFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::GetRegion(Gdiplus::Region** ret)
{
	MfxCodeLock(this);
	if (ret && myShowRegion)
	{
		*ret = myShowRegion->Clone();
		return RFine;
	}
	return RFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::GetRegionBlock(Gdiplus::Size* ret)
{
	MfxCodeLock(this);
	(*ret) = *myCollisionBlock;
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::GetRect(Gdiplus::Rect* ret)
{
	MfxCodeLock(this);
	(*ret) = *myRect;
	return RFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::GetSize(Gdiplus::Size* ret)
{
	MfxCodeLock(this);
	(*ret).Width = (*myRect).Width;
	(*ret).Height = (*myRect).Height;
	return RFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxImage::GetPoint(Gdiplus::Point* ret)
{
	MfxCodeLock(this);
	(*ret).X = (*myRect).X;
	(*ret).Y = (*myRect).Y;
	return RFine;
}