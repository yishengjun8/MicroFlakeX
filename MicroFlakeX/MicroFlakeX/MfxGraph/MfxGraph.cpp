#include "pch.h"
#include "MfxGraph.h"

MFX_OBJ_REFLECTION_INIT(MfxGraph)
MFX_OBJ_REFLECTION_ENDINIT(MfxGraph, MfxBase, \
	SetRect, \
	SetSize, \
	SetPoint, \
	\
	GetRect, \
	GetSize, \
	GetPoint, \
	\
	IntersectWith);


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxGraph::GetID2D1DCRenderTarget(ID2D1RenderTarget** ret, HDC set, MfxRect rect)
{
	D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
		D2D1_RENDER_TARGET_TYPE_DEFAULT,
		D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE),
		0, 0,
		D2D1_RENDER_TARGET_USAGE_NONE,
		D2D1_FEATURE_LEVEL_DEFAULT
	);

	ID2D1DCRenderTarget* tDCRenderTarget = nullptr;
	if (SUCCEEDED(myID2DFactory->CreateDCRenderTarget(&props, &tDCRenderTarget)))
	{
		RECT rc;
		rect.GetRECT(&rc);
		tDCRenderTarget->BindDC(set, &rc);
		*ret = tDCRenderTarget;
		return MFX_RET_SECCESS;
	}
	else
	{
		return MFX_RET_FAILED;
	}
}

MfxReturn MicroFlakeX::MfxGraph::GetID2D1HwndRenderTarget(ID2D1RenderTarget** ret, HWND set, MfxSize size)
{
	ID2D1HwndRenderTarget* tHwndRenderTarget = nullptr;
	D2D1_SIZE_U tSize; size.GetD2D1SizeU(&tSize);
	if (SUCCEEDED(myID2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(set, tSize), &tHwndRenderTarget)))
	{
		*ret = tHwndRenderTarget;
		return MFX_RET_SECCESS;
	}
	else
	{
		return MFX_RET_FAILED;
	}
}

MfxReturn MicroFlakeX::MfxGraph::IWICBitmapFromFile(IWICBitmap** ret, MfxStringW path, MfxSize size)
{
	IWICBitmapDecoder* pDecoder = nullptr;
	IWICBitmapFrameDecode* pSource = nullptr;
	IWICBitmapScaler* pScaler = nullptr;
	IWICFormatConverter* pConverter = nullptr;

	// 加载位图
	if (FAILED(myIWICImagingFactory->CreateDecoderFromFilename(
		path.c_str(), NULL, GENERIC_READ,
		WICDecodeMetadataCacheOnLoad, &pDecoder)))
	{
		return MFX_RET_FAILED;
	};

	HRESULT hr = pDecoder->GetFrame(0, &pSource);
	hr = myIWICImagingFactory->CreateFormatConverter(&pConverter);

	FLOAT tWidth = size.myWidth, tHeight = size.myHeight;
	if (tWidth != 0 || tHeight != 0)
	{
		UINT originalWidth, originalHeight;
		hr = pSource->GetSize(&originalWidth, &originalHeight);

		if (tWidth == 0)
		{
			FLOAT scalar = static_cast<FLOAT>(tHeight) / static_cast<FLOAT>(originalHeight);
			tWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
		}
		else if (tHeight == 0)
		{
			FLOAT scalar = static_cast<FLOAT>(tWidth) / static_cast<FLOAT>(originalWidth);
			tHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
		}

		hr = myIWICImagingFactory->CreateBitmapScaler(&pScaler);
		hr = pScaler->Initialize(pSource, tWidth, tHeight, WICBitmapInterpolationModeCubic);

		hr = pConverter->Initialize(
			pScaler,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL, 0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}
	else
	{
		hr = pConverter->Initialize(
			pSource,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL, 0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}
	hr = myIWICImagingFactory->CreateBitmapFromSource(pConverter,
		WICBitmapCacheOnLoad, ret);

	if (FAILED(hr))
		throw MFX_TXT_W("CreateBitmapFromSource Failed");

	MicroFlakeX::SafeRelease(pSource);
	MicroFlakeX::SafeRelease(pDecoder);
	MicroFlakeX::SafeRelease(pScaler);
	MicroFlakeX::SafeRelease(pConverter);
	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxGraph::IWICBitmapFromColor(IWICBitmap** ret, MfxColor color, MfxSize size)
{
	WICPixelFormatGUID formatGUID = GUID_WICPixelFormat32bppPBGRA;
	if (FAILED(myIWICImagingFactory->CreateBitmap(size.myWidth, size.myHeight,
		formatGUID, WICBitmapCacheOnDemand, ret)))
	{
		return MFX_RET_FAILED;
	}

	WICRect tLockRect = { 0, 0, size.myWidth, size.myHeight };
	IWICBitmapLock* tBitmapLock = nullptr;

	HRESULT hr = (*ret)->Lock(&tLockRect, WICBitmapLockWrite, &tBitmapLock);
	if (SUCCEEDED(hr))
	{
		UINT tLockSize = 0, tStride = 0;
		BYTE* tData = nullptr;

		hr = tBitmapLock->GetStride(&tStride);
		if (SUCCEEDED(hr))
		{
			hr = tBitmapLock->GetDataPointer(&tLockSize, &tData);
		}
		if (SUCCEEDED(hr) && tData)
		{
			for (int tP = 0; tP * 4 < tLockSize; tP++)
			{
				tData[tP * 4] = (BYTE)color.myB;
				tData[(tP * 4) + 1] = (BYTE)color.myG;
				tData[(tP * 4) + 2] = (BYTE)color.myR;
				tData[(tP * 4) + 3] = (BYTE)color.myA;
			}
		}
	}
	SafeRelease(tBitmapLock);
	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxGraph::IWICBitmapFromGdipBitmap(IWICBitmap** ret, const Gdiplus::Bitmap* set, const MfxRect rect)
{
	return MFX_RET_FAILED;
}

MfxReturn MicroFlakeX::MfxGraph::ID2D1BitmapFromFile(ID2D1Bitmap** ret, ID2D1RenderTarget* pRendTar, const  MfxStringW path, const MfxSize size)
{
	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pSource = NULL;
	IWICBitmapScaler* pScaler = NULL;
	IWICFormatConverter* pConverter = NULL;

	if (FAILED(myIWICImagingFactory->CreateDecoderFromFilename(
		path.c_str(), NULL, GENERIC_READ,
		WICDecodeMetadataCacheOnLoad, &pDecoder)))
	{
		return MFX_RET_FAILED;
	};

	HRESULT hr = pDecoder->GetFrame(0, &pSource);
	hr = myIWICImagingFactory->CreateFormatConverter(&pConverter);

	FLOAT tWidth = size.myWidth, tHeight = size.myHeight;
	if (tWidth != 0 || tHeight != 0)
	{
		UINT originalWidth, originalHeight;
		hr = pSource->GetSize(&originalWidth, &originalHeight);
		if (tWidth == 0)
		{
			FLOAT scalar = static_cast<FLOAT>(tHeight) / static_cast<FLOAT>(originalHeight);
			tWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
		}
		else if (tHeight == 0)
		{
			FLOAT scalar = static_cast<FLOAT>(tWidth) / static_cast<FLOAT>(originalWidth);
			tHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
		}
		hr = myIWICImagingFactory->CreateBitmapScaler(&pScaler);
		hr = pScaler->Initialize(pSource, tWidth, tHeight, WICBitmapInterpolationModeCubic);

		hr = pConverter->Initialize(
			pScaler,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL, 0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}
	else
	{
		hr = pConverter->Initialize(
			pSource,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL, 0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}

	hr = pRendTar->CreateBitmapFromWicBitmap(pConverter, ret);

	MicroFlakeX::SafeRelease(pSource);
	MicroFlakeX::SafeRelease(pDecoder);
	MicroFlakeX::SafeRelease(pScaler);
	MicroFlakeX::SafeRelease(pConverter);
	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxGraph::ID2D1BitmapFromIWICBitmap(ID2D1Bitmap** ret, ID2D1RenderTarget* pRendTar, IWICBitmap* bitmap, const MfxSize size)
{
	IWICBitmapScaler* pScaler = nullptr;
	IWICFormatConverter* pConverter = nullptr;

	HRESULT hr = myIWICImagingFactory->CreateFormatConverter(&pConverter);

	FLOAT tWidth = size.myWidth, tHeight = size.myHeight;
	if (tWidth != 0 || tHeight != 0)
	{
		UINT originalWidth, originalHeight;
		bitmap->GetSize(&originalWidth, &originalHeight);
		if (tWidth == 0)
		{
			FLOAT scalar = static_cast<FLOAT>(tHeight) / static_cast<FLOAT>(originalHeight);
			tWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
		}
		else if (tHeight == 0)
		{
			FLOAT scalar = static_cast<FLOAT>(tWidth) / static_cast<FLOAT>(originalWidth);
			tHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
		}

		hr = myIWICImagingFactory->CreateBitmapScaler(&pScaler);
		hr = pScaler->Initialize(bitmap, tWidth, tHeight, WICBitmapInterpolationModeCubic);

		hr = pConverter->Initialize(
			pScaler,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL, 0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}
	else
	{
		hr = pConverter->Initialize(
			bitmap,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL, 0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}

	hr = pRendTar->CreateBitmapFromWicBitmap(pConverter, ret);

	if (FAILED(hr))
		throw MFX_TXT_W("CreateBitmapFromWicBitmap Failed");

	MicroFlakeX::SafeRelease(pScaler);
	MicroFlakeX::SafeRelease(pConverter);
	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxGraph::GdipBitmapFromIWICBitmap(Gdiplus::Bitmap** ret, IWICBitmap* set, MfxRect rect)
{
	WICRect tLockRect = { rect.myX, rect.myY, rect.myWidth, rect.myHeight };
	IWICBitmapLock* tBitmapLock = nullptr;

	HRESULT hr = set->Lock(&tLockRect, WICBitmapLockWrite, &tBitmapLock);
	if (SUCCEEDED(hr))
	{
		UINT tLockSize = 0, tStride = 0;
		BYTE* tData = nullptr;

		hr = tBitmapLock->GetStride(&tStride);
		if (SUCCEEDED(hr))
		{
			hr = tBitmapLock->GetDataPointer(&tLockSize, &tData);
		}
		if (SUCCEEDED(hr) && tData)
		{
			*ret = new Gdiplus::Bitmap(rect.myWidth, rect.myHeight, PixelFormat32bppARGB);
			const Gdiplus::Rect tRect(rect.myX, rect.myY, rect.myWidth, rect.myHeight);
			Gdiplus::BitmapData bitData;
			(*ret)->LockBits(&tRect, Gdiplus::ImageLockModeWrite, PixelFormat32bppPARGB, &bitData);

			int tP = 0, tGP = 0;
			for (int y = 0; y < rect.myHeight; y++)
			{
				tP = y * tStride / 4;
				tGP = y * rect.myWidth;
				for (int x = 0; x < rect.myWidth; x++, tP++, tGP++)
				{
					byte* row = ((byte*)bitData.Scan0 + tGP * 4);

					row[0] = tData[tP * 4];// = (BYTE)color.myB;
					row[1] = tData[(tP * 4) + 1];// = (BYTE)color.myG;
					row[2] = tData[tP * 4 + 2];// = (BYTE)color.myR;
					row[3] = tData[tP * 4 + 3];// = (BYTE)color.myA;
				}
			}
			(*ret)->UnlockBits(&bitData);
		}
	}
	SafeRelease(tBitmapLock);
	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxGraph::CopyIWICBitmap(IWICBitmap** ret, IWICBitmap* set)
{
	WICPixelFormatGUID formatGUID = GUID_WICPixelFormat32bppPBGRA;
	UINT tWidth = 0, tHeight = 0;
	set->GetSize(&tWidth, &tHeight);

	if (FAILED(myIWICImagingFactory->CreateBitmap(tWidth, tHeight,
		formatGUID, WICBitmapCacheOnDemand, ret)))
	{
		return MFX_RET_FAILED;
	}

	WICRect tLockRect = { 0, 0, tWidth, tWidth };
	IWICBitmapLock* tReadLock = nullptr;
	IWICBitmapLock* tWriteLock = nullptr;

	HRESULT hr = (*ret)->Lock(&tLockRect, WICBitmapLockWrite, &tWriteLock);
	if (SUCCEEDED(hr))
	{
		hr = set->Lock(&tLockRect, WICBitmapLockRead, &tReadLock);

		UINT tReadSize = 0, tWriteSize = 0;
		BYTE* tReadData = nullptr;
		BYTE* tWriteData = nullptr;

		if (SUCCEEDED(hr))
		{
			if (SUCCEEDED(tReadLock->GetDataPointer(&tReadSize, &tReadData))
				&& SUCCEEDED(tWriteLock->GetDataPointer(&tWriteSize, &tWriteData))
				&& tWriteData && tReadData)
			{
				for (int i = 0; i < tReadSize && i < tWriteSize; i++)
				{
					tWriteData[i] = tReadData[i];
				}
			}
		}
		hr = tReadLock->Release();
		hr = tWriteLock->Release();
	}
	SafeRelease(tReadLock);
	SafeRelease(tWriteLock);
	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxGraph::CopyTextFormat(IDWriteTextFormat** ret, IDWriteTextFormat* set)
{
	if (set == nullptr)
	{
		return MFX_RET_FAILED;
	}
	WCHAR* fontLocalName = new WCHAR[set->GetLocaleNameLength() + 1]{ 0 };
	WCHAR* fontFamilyName = new WCHAR[set->GetFontFamilyNameLength() + 1]{ 0 };

	set->GetLocaleName(fontLocalName, set->GetLocaleNameLength() + 1);
	set->GetFontFamilyName(fontFamilyName, set->GetFontFamilyNameLength() + 1);

	HRESULT hr = MfxGraph::myIDWriteFactory->CreateTextFormat(
		fontFamilyName,
		NULL,								// Font collection(NULL sets it to the system font collection)
		set->GetFontWeight(),    // Weight
		set->GetFontStyle(),     // Style
		set->GetFontStretch(),   // Stretch
		set->GetFontSize(),      // Size    
		fontLocalName,						// Local  英国-美国 zh-CN 华 -中国
		ret						// Pointer to recieve the created object
	);

	if (SUCCEEDED(hr))
	{
		(*ret)->SetFlowDirection(set->GetFlowDirection());
		(*ret)->SetIncrementalTabStop(set->GetIncrementalTabStop());
		(*ret)->SetParagraphAlignment(set->GetParagraphAlignment());
		(*ret)->SetReadingDirection(set->GetReadingDirection());
		(*ret)->SetTextAlignment(set->GetTextAlignment());
		(*ret)->SetWordWrapping(set->GetWordWrapping());

		DWRITE_LINE_SPACING_METHOD tLineSpacingMethod;
		FLOAT tLineSpacing{ 0 };
		FLOAT tBaseline{ 0 };
		set->GetLineSpacing(&tLineSpacingMethod, &tLineSpacing, &tBaseline);
		(*ret)->SetLineSpacing(tLineSpacingMethod, tLineSpacing, tBaseline);

		DWRITE_TRIMMING trimmingOptions;
		IDWriteInlineObject* trimmingSign;
		set->GetTrimming(&trimmingOptions, &trimmingSign);
		(*ret)->SetTrimming(&trimmingOptions, trimmingSign);

		SafeRelease(trimmingSign);
	}

	SafeDeleteList(fontLocalName);
	SafeDeleteList(fontFamilyName);

	return hr;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxGraph::GetRect(MfxRect* set) const
{
	myRect.GetRect(set);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxGraph::GetSize(MfxSize* set) const
{
	myRect.GetSize(set);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxGraph::GetPoint(MfxPoint* set) const
{
	myRect.GetPoint(set);

	return MFX_RET_SECCESS;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxGraph::SetRect(const MfxRect* set)
{
	myRect.SetRect(set);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxGraph::SetSize(const MfxSize* set)
{
	myRect.SetSize(set);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxGraph::SetPoint(const MfxPoint* set)
{
	myRect.SetPoint(set);

	return MFX_RET_SECCESS;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxGraph::IntersectWith(MfxGraph* set, MfxRect* ret)
{
	myRect.Intersect_Widely(set, ret);

	return MFX_RET_SECCESS;
}