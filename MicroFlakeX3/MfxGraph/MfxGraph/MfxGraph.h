#pragma once

/**************************************************************
*	UTF-8 - win - x86
*
*   版本：1.01       作者：yishengjun8
*
*
*	MfxGraph.h	提供了	MicroFlakeX	的绘制基础
* 
*	包含了一个画板，以及众多的绘制类
*
**************************************************************/

#ifdef MFXDLL_BUILDING
#define MFX_PORT __declspec(dllexport)
#else
#define MFX_PORT __declspec(dllimport)
#pragma comment(lib, "MfxGraph.lib")

#include "MfxType.h"

#include "Gdiplus.h"
#pragma comment(lib, "Gdiplus.lib")
#endif

namespace MicroFlakeX
{
	class MFX_PORT MfxGraph;

	class MFX_PORT MfxCanvas;

	class MFX_PORT MfxImage;
	class MFX_PORT MfxWords;
}

namespace MicroFlakeX
{
	typedef std::vector<MfxGraph*> MfxGraphVector;
}

namespace __MicroFlakeX
{
	template<class Interface>
	inline void SafeRelease(Interface*& pInterfaceToRelease) 
	{
		if (pInterfaceToRelease != nullptr) 
		{
			pInterfaceToRelease->Release();
			pInterfaceToRelease = nullptr;
		}
	}

	template<class Pointer>
	inline void SafeDelete(Pointer*& pPointerToDelete)
	{
		if (pPointerToDelete != nullptr)
		{
			delete pPointerToDelete;
			pPointerToDelete = nullptr;
		}
	}

	template<class Pointer>
	inline void SafeDeleteL(Pointer*& pPointerToDelete)
	{
		if (pPointerToDelete != nullptr)
		{
			delete[] pPointerToDelete;
			pPointerToDelete = nullptr;
		}
	}
}

namespace MicroFlakeX
{
	class MfxGraph
		: public MfxBase
	{
	public:
		static MfxReturn GetID2D1DCRenderTarget(ID2D1RenderTarget** ret, HDC set, MfxRect rect);
		static MfxReturn GetID2D1HwndRenderTarget(ID2D1RenderTarget** ret, HWND set, MfxSize size);

		static MfxReturn IWICBitmapFromFile(IWICBitmap** ret, MfxString path, MfxSize size);
		static MfxReturn IWICBitmapFromColor(IWICBitmap** ret, MfxColor color, MfxSize size);
		static MfxReturn IWICBitmapFromGdipBitmap(IWICBitmap** ret, Gdiplus::Bitmap* set, MfxRect rect);

		static MfxReturn ID2D1BitmapFromFile(ID2D1Bitmap** ret, ID2D1RenderTarget* pRendTar, MfxString path, MfxSize size);
		static MfxReturn ID2D1BitmapFromIWICBitmap(ID2D1Bitmap** ret, ID2D1RenderTarget* pRendTar, IWICBitmap* bitmap, MfxSize size);

		static MfxReturn GdipBitmapFromIWICBitmap(Gdiplus::Bitmap** ret, IWICBitmap* set, MfxRect rect);

		static MfxReturn CopyIWICBitmap(IWICBitmap** ret, IWICBitmap* set);
		static MfxReturn CopyTextFormat(IDWriteTextFormat** ret, IDWriteTextFormat* set);
	public:
		static ID2D1Factory*& myID2DFactory;
		static IDWriteFactory*& myIDWriteFactory;
		static IWICImagingFactory*& myIWICImagingFactory;

		MfxObject;
	public:
		MfxGraph();
		virtual ~MfxGraph();
		MfxReturn Clone(MfxBase** ret);
		MfxBase& operator=(MfxBase& rhs);
		bool operator==(MfxBase& rhs);

	public:
		virtual MfxReturn SetRect(MfxRect set);
		virtual MfxReturn SetSize(MfxSize set);
		virtual MfxReturn SetPoint(MfxPoint set);

		virtual MfxReturn GetRect(MfxRect* ret);
		virtual MfxReturn GetSize(MfxSize* ret);
		virtual MfxReturn GetPoint(MfxPoint* ret);

		virtual MfxReturn CollisionWith(MfxGraph* set, bool* ret);
	protected:
		MfxRect myRect;
	};
}

namespace MicroFlakeX
{
	class MfxCanvas
		: public MfxGraph
	{
		MfxObject;
	public:
		MfxCanvas();
		MfxCanvas(MfxRect sRect);
		MfxCanvas(HDC sDC, MfxRect sRect);
		MfxCanvas(HWND sWnd, MfxRect sRect);

		virtual ~MfxCanvas();
		MfxReturn Clone(MfxBase** ret);
		MfxBase& operator=(MfxBase& rhs);
		MfxCanvas& operator=(MfxCanvas& rhs);
		bool operator==(MfxBase& rhs);
		BOOL operator==(MfxCanvas& rhs);

	public:
		MfxReturn SetDC(HDC set);
		MfxReturn GetDC(HDC* ret);

		MfxReturn SetWnd(HWND set);
		MfxReturn GetWnd(HWND* ret);

	public:
		MfxReturn PaintBegin();
		MfxReturn PaintFinish();

		MfxReturn PaintCheck(bool* ret);
	public:
		MfxReturn GetRenderTarget(ID2D1RenderTarget** ret);

	public:
		MfxReturn SetRect(MfxRect set);
		MfxReturn SetSize(MfxSize set);
		MfxReturn SetPoint(MfxPoint set);

	protected:
		HDC myDC;
		HWND myWnd;
		BOOL myPaintFlag;
		MfxColor myColor;
		ID2D1RenderTarget* myRenderTarget;
	};
}

namespace MicroFlakeX
{
	class MfxImage
		: public MfxGraph
	{
		MfxObject;
	public:
		MfxImage();
		MfxImage(MfxString* path, MfxRect set);
		MfxImage(MfxColor color, MfxRect set);
		MfxImage(IWICBitmap* tIWICBitmap, MfxRect set);
		virtual ~MfxImage();
		MfxReturn Clone(MfxBase** ret);
		MfxReturn Clone(MfxImage** ret);
		MfxBase& operator=(MfxBase& rhs);
		bool operator==(MfxBase& rhs);

	protected:
		MfxCanvas* myCanvas;
		ID2D1RenderTarget* myRenderTarget;

		IWICBitmap* myIWICBitmap;
		ID2D1Bitmap* myID2D1Bitmap;

	public:
		MfxReturn Paint();

		MfxReturn SetCanvas(MfxCanvas* set);
		MfxReturn GetCanvas(MfxCanvas** ret);

	public:
		MfxReturn ResetIWICBitmapFromFile(MfxString* path, MfxSize set);
		MfxReturn ResetIWICBitmapFromColor(MfxColor color, MfxSize set);

		MfxReturn ResetID2D1Bitmap();

	public:
		MfxReturn FromFile(MfxString* path, MfxSize set);
		MfxReturn FromColor(MfxColor color, MfxSize set);

	public:
		MfxReturn GetIWICBitmap(IWICBitmap** ret);
		MfxReturn GetID2D1Bitmap(ID2D1Bitmap** ret);
		MfxReturn GetGdipBitmap(Gdiplus::Bitmap** ret);

		MfxReturn SetIWICBitmap(IWICBitmap* set);
	};
}

namespace MicroFlakeX
{
	typedef enum DWRITE_TEXT_ALIGNMENT TextAlignmentX;
	typedef enum DWRITE_PARAGRAPH_ALIGNMENT TextAlignmentY;

	class MfxWords
		: public MfxGraph
	{
		MfxObject;
	public:
		MfxWords();
		MfxWords(MfxString str, MfxRect set);
		MfxWords(MfxString str, MfxRect set, FLOAT size);
		MfxWords(MfxString str, MfxRect set, FLOAT size, IDWriteTextFormat* format);
		virtual ~MfxWords();
		MfxReturn Clone(MfxBase** ret);
		MfxReturn Clone(MfxWords** ret);
		MfxBase& operator=(MfxBase& rhs);
		bool operator==(MfxBase& rhs);

		static IDWriteTextFormat* gDefTextFormat;
	protected:
		MfxString myText;
		MfxColor myColor;
		ID2D1Brush* myTextBrush;
		IDWriteTextFormat* myTextFormat;
		IDWriteTextLayout* myTextLayout;

		MfxCanvas* myCanvas;
		ID2D1RenderTarget* myRenderTarget;
	public:
		MfxReturn Paint();

		MfxReturn SetCanvas(MfxCanvas* set);
		MfxReturn GetCanvas(MfxCanvas** ret);

	public:
		MfxReturn ResetTextLayout();
	public:
		MfxReturn SetText(MfxString set);
		MfxReturn GetText(MfxString* ret);

		MfxReturn SetTextSize(FLOAT set);
		MfxReturn GetTextSize(FLOAT* ret);

		MfxReturn SetFontName(MfxString set);
		MfxReturn GetFontName(MfxString* ret);

		MfxReturn SetTextFormat(IDWriteTextFormat* set);
		MfxReturn GetTextFormat(IDWriteTextFormat** ret);

		MfxReturn SetTextColor(MfxColor set);
		MfxReturn GetTextColor(MfxColor* set);
	public:
		MfxReturn SetRect(MfxRect set);
		MfxReturn SetSize(MfxSize set);

		MfxReturn SetTextAlignmentX(TextAlignmentX set);
		MfxReturn GetTextAlignmentX(TextAlignmentX* ret);

		MfxReturn SetTextAlignmentY(TextAlignmentY set);
		MfxReturn GetTextAlignmentY(TextAlignmentY* ret);
	};
}


