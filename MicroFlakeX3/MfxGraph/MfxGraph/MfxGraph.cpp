#include "pch.h"
#include "MfxGraph.h"

ID2D1Factory* gID2DFactory = nullptr;
IDWriteFactory* gIDWriteFactory = nullptr;
IWICImagingFactory* gIWICImagingFactory = nullptr;

MfxObject_Init_0(MfxGraph)

HRESULT hr;

hr = ::D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &gID2DFactory);
if(FAILED(hr))
	throw L"D2D1CreateFactory Failed";

hr = ::DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(gID2DFactory),
	reinterpret_cast<IUnknown**>(&gIDWriteFactory));
if (FAILED(hr))
	throw L"IDWriteFactory Failed";

hr = ::CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, 
	IID_PPV_ARGS(&gIWICImagingFactory));
if (FAILED(hr))
	throw L"IWICImagingFactory Failed";

MfxObject_Init_1(MfxGraph)
MfxObject_Init_2(MfxGraph, MfxBase);

const ID2D1Factory* MfxGraph::myID2DFactory = gID2DFactory;
const IDWriteFactory* MfxGraph::myIDWriteFactory = gIDWriteFactory;
const IWICImagingFactory* MfxGraph::myIWICImagingFactory = gIWICImagingFactory;


MfxReturn MicroFlakeX::MfxGraph::GetID2D1DCRenderTarget(ID2D1RenderTarget** ret, HDC set, MfxRect* rect)
{
	return RFine;
}

MfxReturn MicroFlakeX::MfxGraph::GetID2D1HwndRenderTarget(ID2D1RenderTarget** ret, HWND set, MfxSize* size)
{
	return RFine;
}

MfxReturn MicroFlakeX::MfxGraph::IWICBitmapFromFile(IWICBitmap** ret, MfxStrW path, MfxSize* size)
{
	return RFine;
}

MfxReturn MicroFlakeX::MfxGraph::ID2D1BitmapFromFile(ID2D1Bitmap** ret, ID2D1RenderTarget* pRendTar, MfxStrW filePath, MfxSize* size)
{
	return RFine;
}

MfxReturn MicroFlakeX::MfxGraph::ID2D1BitmapFromIWICBitmap(ID2D1Bitmap** ret, ID2D1RenderTarget* pRendTar, IWICBitmap* bitmap, MfxSize* size)
{
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
	return *this;
}

BOOL MicroFlakeX::MfxGraph::operator==(MfxBase& rhs)
{
	// TODO: 在此处插入 return 语句
	return false;
}

MfxReturn MicroFlakeX::MfxGraph::SetRect(MfxRect* set)
{
	myRect = *set;
	return RFine;
}

MfxReturn MicroFlakeX::MfxGraph::SetSize(MfxSize* set)
{
	myRect = *set;
	return RFine;
}

MfxReturn MicroFlakeX::MfxGraph::SetPoint(MfxPoint* set)
{
	myRect = *set;
	return RFine;
}

MfxReturn MicroFlakeX::MfxGraph::GetRect(MfxRect** set)
{
	**set = myRect;
	return RFine;
}

MfxReturn MicroFlakeX::MfxGraph::GetSize(MfxSize** set)
{
	**set = myRect;
	return RFine;
}

MfxReturn MicroFlakeX::MfxGraph::GetPoint(MfxPoint** set)
{
	**set = myRect;
	return RFine;
}

MfxReturn MicroFlakeX::MfxGraph::CollisionWith(MfxGraph* set, bool* ret)
{
	return RFine;
}


