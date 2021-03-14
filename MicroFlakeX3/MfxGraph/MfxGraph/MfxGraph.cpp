#include "pch.h"
#include "MfxGraph.h"

ID2D1Factory* gID2DFactory = nullptr;
IDWriteFactory* gIDWriteFactory = nullptr;
IWICImagingFactory* gIWICImagingFactory = nullptr;

MfxObject_Init_0(MfxGraph)
{
	HRESULT hr = ::CoInitialize(NULL);
	if (FAILED(hr))
		throw L"CoInitialize Failed";

	hr = ::D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &gID2DFactory);
	if (FAILED(hr))
		throw L"D2D1CreateFactory Failed";

	hr = ::DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(gIDWriteFactory),
		reinterpret_cast<IUnknown**>(&gIDWriteFactory));
	if (FAILED(hr))
		throw L"IDWriteFactory Failed";

	hr = ::CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&gIWICImagingFactory));
	if (FAILED(hr))
		throw L"IWICImagingFactory Failed";
}
MfxObject_Init_1(MfxGraph);
MfxObject_Init_2(MfxGraph, MfxBase);

ID2D1Factory*& MfxGraph::myID2DFactory = gID2DFactory;
IDWriteFactory*& MfxGraph::myIDWriteFactory = gIDWriteFactory;
IWICImagingFactory*& MfxGraph::myIWICImagingFactory = gIWICImagingFactory;

MfxReturn MicroFlakeX::MfxGraph::GetID2D1DCRenderTarget(ID2D1RenderTarget** ret, HDC &set, MfxRect rect)
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
		return RFine;
	}
	else
	{
		return RFail;
	}
}

MfxReturn MicroFlakeX::MfxGraph::GetID2D1HwndRenderTarget(ID2D1RenderTarget** ret, HWND &set, MfxSize size)
{
	ID2D1HwndRenderTarget* tHwndRenderTarget = nullptr;
	D2D1_SIZE_U tSize; size.GetD2D1SizeU(&tSize);
	if (SUCCEEDED(myID2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(set, tSize), &tHwndRenderTarget)))
	{
		*ret = tHwndRenderTarget;
		return RFine;
	}
	else
	{
		return RFail;
	}
}

MfxReturn MicroFlakeX::MfxGraph::IWICBitmapFromFile(IWICBitmap** ret, MfxStrW &path, MfxSize size)
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
		return RFail;
	};

	pDecoder->GetFrame(0, &pSource);
	myIWICImagingFactory->CreateFormatConverter(&pConverter);

	FLOAT tWidth = size.myWidth, tHeight = size.myHeight;
	if (tWidth != 0 || tHeight != 0)
	{
		UINT originalWidth, originalHeight;
		pSource->GetSize(&originalWidth, &originalHeight);

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

		myIWICImagingFactory->CreateBitmapScaler(&pScaler);
		pScaler->Initialize(pSource, tWidth, tHeight, WICBitmapInterpolationModeCubic);

		pConverter->Initialize(
			pScaler,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL, 0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}
	else
	{
		pConverter->Initialize(
			pSource,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL, 0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}
	HRESULT hr = myIWICImagingFactory->CreateBitmapFromSource(pConverter,
		WICBitmapCacheOnLoad, ret);

	if (FAILED(hr))
		throw L"CreateBitmapFromSource Failed";

	__MicroFlakeX::SafeRelease(pSource);
	__MicroFlakeX::SafeRelease(pDecoder);
	__MicroFlakeX::SafeRelease(pScaler);
	__MicroFlakeX::SafeRelease(pConverter);
	return RFine;
}

MfxReturn MicroFlakeX::MfxGraph::IWICBitmapFromColor(IWICBitmap** ret, MfxColor
	color, MfxSize size)
{
	return MfxReturn();
}

MfxReturn MicroFlakeX::MfxGraph::ID2D1BitmapFromFile(ID2D1Bitmap** ret, ID2D1RenderTarget* pRendTar, MfxStrW &path, MfxSize size)
{
	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pSource = NULL;
	IWICBitmapScaler* pScaler = NULL;
	IWICFormatConverter* pConverter = NULL;

	if (FAILED(myIWICImagingFactory->CreateDecoderFromFilename(
		path.c_str(), NULL, GENERIC_READ,
		WICDecodeMetadataCacheOnLoad, &pDecoder)))
	{
		return RFail;
	};

	pDecoder->GetFrame(0, &pSource);
	myIWICImagingFactory->CreateFormatConverter(&pConverter);

	FLOAT tWidth = size.myWidth, tHeight = size.myHeight;
	if (tWidth != 0 || tHeight != 0)
	{
		UINT originalWidth, originalHeight;
		pSource->GetSize(&originalWidth, &originalHeight);
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
		myIWICImagingFactory->CreateBitmapScaler(&pScaler);
		pScaler->Initialize(pSource, tWidth, tHeight, WICBitmapInterpolationModeCubic);

		pConverter->Initialize(
			pScaler,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL, 0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}
	else
	{
		pConverter->Initialize(
			pSource,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL, 0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}

	pRendTar->CreateBitmapFromWicBitmap(pConverter, NULL, ret);

	__MicroFlakeX::SafeRelease(pSource);
	__MicroFlakeX::SafeRelease(pDecoder);
	__MicroFlakeX::SafeRelease(pScaler);
	__MicroFlakeX::SafeRelease(pConverter);
	return RFine;
}

MfxReturn MicroFlakeX::MfxGraph::ID2D1BitmapFromIWICBitmap(ID2D1Bitmap** ret, ID2D1RenderTarget* pRendTar, IWICBitmap* bitmap, MfxSize size)
{
	IWICBitmapScaler* pScaler = nullptr;
	IWICFormatConverter* pConverter = nullptr;

	myIWICImagingFactory->CreateFormatConverter(&pConverter);

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

		myIWICImagingFactory->CreateBitmapScaler(&pScaler);
		pScaler->Initialize(bitmap, tWidth, tHeight, WICBitmapInterpolationModeCubic);

		pConverter->Initialize(
			pScaler,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL, 0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}
	else
	{
		pConverter->Initialize(
			bitmap,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL, 0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}

	HRESULT hr = pRendTar->CreateBitmapFromWicBitmap(pConverter, NULL, ret);

	if (FAILED(hr))
		throw L"CreateBitmapFromWicBitmap Failed";

	__MicroFlakeX::SafeRelease(pScaler);
	__MicroFlakeX::SafeRelease(pConverter);
	return RFine;
}


MicroFlakeX::MfxGraph::MfxGraph()
{
}

MicroFlakeX::MfxGraph::~MfxGraph()
{
}

MfxReturn MicroFlakeX::MfxGraph::Clone(MfxBase** ret)
{
	return RFine;
}

MfxBase& MicroFlakeX::MfxGraph::operator=(MfxBase& rhs)
{
	// TODO: 在此处插入 return 语句
	//rhs.AutoFunc()
	return *this;
}

BOOL MicroFlakeX::MfxGraph::operator==(MfxBase& rhs)
{
	// TODO: 在此处插入 return 语句
	return false;
}

MfxReturn MicroFlakeX::MfxGraph::SetRect(MfxRect set)
{
	SetSize(MfxSize(&set));
	SetPoint(MfxPoint(&set));
	return RFine;
}

MfxReturn MicroFlakeX::MfxGraph::SetSize(MfxSize set)
{
	myRect = set;
	return RFine;
}

MfxReturn MicroFlakeX::MfxGraph::SetPoint(MfxPoint set)
{
	myRect = set;
	return RFine;
}

MfxReturn MicroFlakeX::MfxGraph::GetRect(MfxRect* set)
{
	*set = myRect;
	return RFine;
}

MfxReturn MicroFlakeX::MfxGraph::GetSize(MfxSize* set)
{
	*set = myRect;
	return RFine;
}

MfxReturn MicroFlakeX::MfxGraph::GetPoint(MfxPoint* set)
{
	*set = myRect;
	return RFine;
}

MfxReturn MicroFlakeX::MfxGraph::CollisionWith(MfxGraph* set, bool* ret)
{
	return RFine;
}


