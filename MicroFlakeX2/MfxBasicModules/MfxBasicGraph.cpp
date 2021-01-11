#include "pch.h"
#include "MfxBasicGraph.h"

MicroFlakeX::MfxBasicGraph::MfxBasicGraph()
	: MfxBasicObject()
{
}

MicroFlakeX::MfxBasicGraph::~MfxBasicGraph()
{
}

bool __MicroFlakeX::MfxGraphListFloorCompare(MfxGraphList_Value* lhs, MfxGraphList_Value* rhs)
{
	return lhs->myFloor < rhs->myFloor;
}

// Direct2D1
ID2D1Factory* m_pD2DFactory = nullptr;		// D2D工厂
IDWriteFactory* m_pDWriteFactory = nullptr;	// DWrite工厂
IWICImagingFactory* m_pWICFactory = nullptr;		// WIC工厂

ID2D1Factory* MicroFlakeX::MfxGetID2D1Factory()
{
	if (!m_pD2DFactory)
	{
		D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
	}
	return m_pD2DFactory;
}

IDWriteFactory* MicroFlakeX::MfxGetIDWriteFactory()
{
	if (!m_pDWriteFactory)
	{
		DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(MfxGetID2D1Factory()),
			reinterpret_cast<IUnknown**>(&m_pDWriteFactory));
	}
	return m_pDWriteFactory;
}

IWICImagingFactory* MicroFlakeX::MfxGetIWICImagingFactory()
{
	if (!m_pWICFactory)
	{
		(CoCreateInstance(CLSID_WICImagingFactory, NULL,
			CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pWICFactory)));
	}
	return m_pWICFactory;
}

ID2D1DCRenderTarget* MicroFlakeX::MfxGetID2D1DCRenderTarget(HDC hDC, GdipRect rect)
{
	ID2D1DCRenderTarget* ret = nullptr;
	if (hDC)
	{
		D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
			D2D1_RENDER_TARGET_TYPE_DEFAULT,
			D2D1::PixelFormat(
				DXGI_FORMAT_B8G8R8A8_UNORM,
				D2D1_ALPHA_MODE_IGNORE),
			0,
			0,
			D2D1_RENDER_TARGET_USAGE_NONE,
			D2D1_FEATURE_LEVEL_DEFAULT
		);

		if (SUCCEEDED(MfxGetID2D1Factory()->CreateDCRenderTarget(&props, &ret)))
		{
			RECT rc;
			rc.top = rect.GetTop();
			rc.left = rect.GetLeft();
			rc.right = rect.GetRight();
			rc.bottom = rect.GetBottom();
			ret->BindDC(hDC, &rc);
		}
	}
	return ret;
}

ID2D1HwndRenderTarget* MicroFlakeX::MfxGetID2D1HwndRenderTarget(HWND hWnd, GdipSize size)
{
	ID2D1HwndRenderTarget* ret = nullptr;
	if (hWnd)
	{
		D2D1_SIZE_U t_size = D2D1::SizeU(size.Width, size.Height);
		MfxGetID2D1Factory()->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hWnd, t_size),&ret);
	}
	return ret;
}

IWICBitmap* MicroFlakeX::MfxIWICBitmapFromFile(MfxStrW path, UINT width, UINT height)
{
	IWICBitmap* ret;
	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pSource = NULL;
	//IWICImagingFactory::CreateBitmapFromSource(pSource)
	IWICBitmapScaler* pScaler = NULL;
	IWICFormatConverter* pConverter = NULL;

	// 加载位图-------------------------------------------------
	if (FAILED(MfxGetIWICImagingFactory()->CreateDecoderFromFilename(
		path.c_str(), NULL, GENERIC_READ,
		WICDecodeMetadataCacheOnLoad, &pDecoder)))
	{
		return nullptr;
	};

	pDecoder->GetFrame(0, &pSource);
	MfxGetIWICImagingFactory()->CreateFormatConverter(&pConverter);
	if (width != 0 || height != 0)
	{
		UINT originalWidth, originalHeight;
		pSource->GetSize(&originalWidth, &originalHeight);
		if (width == 0)
		{
			FLOAT scalar = static_cast<FLOAT>(height) / static_cast<FLOAT>(originalHeight);
			width = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
		}
		else if (height == 0)
		{
			FLOAT scalar = static_cast<FLOAT>(width) / static_cast<FLOAT>(originalWidth);
			height = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
		}
		MfxGetIWICImagingFactory()->CreateBitmapScaler(&pScaler);
		pScaler->Initialize(pSource, width, height, WICBitmapInterpolationModeCubic);

		pConverter->Initialize(
			pScaler,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL, 0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}
	else // Don't scale the image.
	{
		pConverter->Initialize(
			pSource,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL, 0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}
	MfxGetIWICImagingFactory()->CreateBitmapFromSource(
		pConverter,
		WICBitmapCacheOnLoad,
		&ret
	);

	MfxComRelease(&pSource);
	MfxComRelease(&pDecoder);
	MfxComRelease(&pScaler);
	MfxComRelease(&pConverter);
	return ret;
}

ID2D1Bitmap* MicroFlakeX::MfxID2D1BitmapFromIWICBitmap(IWICBitmap* bitmap, UINT width, UINT height, ID2D1RenderTarget* pRenderTarget)
{
	ID2D1Bitmap* ret = NULL;
	IWICBitmapScaler* pScaler = NULL;
	IWICFormatConverter* pConverter = NULL;

	MfxGetIWICImagingFactory()->CreateFormatConverter(&pConverter);
	if (width != 0 || height != 0)
	{
		UINT originalWidth, originalHeight;
		bitmap->GetSize(&originalWidth, &originalHeight);
		if (width == 0)
		{
			FLOAT scalar = static_cast<FLOAT>(height) / static_cast<FLOAT>(originalHeight);
			width = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
		}
		else if (height == 0)
		{
			FLOAT scalar = static_cast<FLOAT>(width) / static_cast<FLOAT>(originalWidth);
			height = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
		}
		MfxGetIWICImagingFactory()->CreateBitmapScaler(&pScaler);
		pScaler->Initialize(bitmap, width, height, WICBitmapInterpolationModeCubic);

		pConverter->Initialize(
			pScaler,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL, 0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}
	else // Don't scale the image.
	{
		pConverter->Initialize(
			bitmap,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL, 0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}

	pRenderTarget->CreateBitmapFromWicBitmap(
		pConverter,
		NULL,
		&ret
	);

	MfxComRelease(&pScaler);
	MfxComRelease(&pConverter);
	return ret;
}

ID2D1Bitmap* MicroFlakeX::MfxID2D1BitmapFromFile(MfxStrW path, UINT width, UINT height, ID2D1RenderTarget* pRenderTarget)
{
	ID2D1Bitmap* ret = NULL;
	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pSource = NULL;
	//IWICImagingFactory::CreateBitmapFromSource(pSource)
	IWICBitmapScaler* pScaler = NULL;
	IWICFormatConverter* pConverter = NULL;
	
	// 加载位图-------------------------------------------------
	if (FAILED(MfxGetIWICImagingFactory()->CreateDecoderFromFilename(
		path.c_str(), NULL, GENERIC_READ,
		WICDecodeMetadataCacheOnLoad, &pDecoder)))
	{
		return nullptr;
	};

	pDecoder->GetFrame(0, &pSource);
	MfxGetIWICImagingFactory()->CreateFormatConverter(&pConverter);
	if (width != 0 || height != 0)
	{
		UINT originalWidth, originalHeight;
		pSource->GetSize(&originalWidth, &originalHeight);
		if (width == 0)
		{
			FLOAT scalar = static_cast<FLOAT>(height) / static_cast<FLOAT>(originalHeight);
			width = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
		}
		else if (height == 0)
		{
			FLOAT scalar = static_cast<FLOAT>(width) / static_cast<FLOAT>(originalWidth);
			height = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
		}
		MfxGetIWICImagingFactory()->CreateBitmapScaler(&pScaler);
		pScaler->Initialize(pSource, width, height, WICBitmapInterpolationModeCubic);

		pConverter->Initialize(
			pScaler,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL, 0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}
	else // Don't scale the image.
	{
		pConverter->Initialize(
			pSource,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL, 0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}

	pRenderTarget->CreateBitmapFromWicBitmap(
		pConverter,
		NULL,
		&ret
	);

	MfxComRelease(&pSource);
	MfxComRelease(&pDecoder);
	MfxComRelease(&pScaler);
	MfxComRelease(&pConverter);
	return ret;
}


