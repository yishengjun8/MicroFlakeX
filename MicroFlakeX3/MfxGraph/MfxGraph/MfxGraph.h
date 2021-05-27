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


		/**************************************************************
		*
		*
		*
		***************************************************************/
		MfxObject;

	public:
		virtual MfxReturn GetRect(MfxRect* ret);
		virtual MfxReturn GetSize(MfxSize* ret);
		virtual MfxReturn GetPoint(MfxPoint* ret);

	public:
		virtual MfxReturn SetRect(MfxRect* set);
		virtual MfxReturn SetSize(MfxSize* set);
		virtual MfxReturn SetPoint(MfxPoint* set);

	public:
		virtual MfxReturn IntersectWith(MfxGraph* set, MfxRect* ret);

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

		MfxCanvas(MfxRect* set);
		MfxCanvas(MfxRect& set) :MfxCanvas(&set) {};
		MfxCanvas(MfxRect&& set) :MfxCanvas(&set) {};

		MfxCanvas(MfxSize* size);
		MfxCanvas(MfxSize& size) :MfxCanvas(&size) {};
		MfxCanvas(MfxSize&& size) :MfxCanvas(&size) {};

		MfxCanvas(HDC setDC, MfxRect* setRect);
		MfxCanvas(HDC setDC, MfxRect& setRect) :MfxCanvas(setDC, &setRect) {};
		MfxCanvas(HDC setDC, MfxRect&& setRect) :MfxCanvas(setDC, &setRect) {};

		MfxCanvas(HDC setDC, MfxSize* setSize) :MfxCanvas(setDC, MfxRect(setSize)) {};
		MfxCanvas(HDC setDC, MfxSize& setSize) :MfxCanvas(setDC, &setSize) {};
		MfxCanvas(HDC setDC, MfxSize&& setSize) :MfxCanvas(setDC, &setSize) {};

		MfxCanvas(HWND setWnd, MfxRect* setRect);
		MfxCanvas(HWND setWnd, MfxRect& setRect) :MfxCanvas(setWnd, &setRect) {};
		MfxCanvas(HWND setWnd, MfxRect&& setRect) :MfxCanvas(setWnd, &setRect) {};

		MfxCanvas(HWND setWnd, MfxSize* setSize) :MfxCanvas(setWnd, MfxRect(setSize)) {};
		MfxCanvas(HWND setWnd, MfxSize& setSize) :MfxCanvas(setWnd, &setSize) {};
		MfxCanvas(HWND setWnd, MfxSize&& setSize) :MfxCanvas(setWnd, &setSize) {};

		virtual ~MfxCanvas();

	public:
		MfxReturn GetDC(HDC* ret);
		MfxReturn GetWnd(HWND* ret);
		MfxReturn GetBackColor(MfxColor* ret);

	public:
		MfxReturn SetDC(HDC set);
		MfxReturn SetWnd(HWND set);
		MfxReturn SetBackColor(MfxColor* set);

	public:
		MfxReturn PaintBegin(MfxRect* clip);
		MfxReturn PaintFinish();

	public:
		MfxReturn PaintCheck(bool* ret);

	public:
		MfxReturn GetRenderTarget(ID2D1RenderTarget** ret);

	public:
		MfxReturn SetRect(MfxRect* set);
		MfxReturn SetSize(MfxSize* set);
		MfxReturn SetPoint(MfxPoint* set);

	protected:
		HDC myDC;
		HWND myWnd;

		MfxRect myClipRect;
		MfxColor myBackColor;

		bool myPaintFlag;
		ID2D1RenderTarget* myRenderTarget;
	};
}

namespace MicroFlakeX
{
	/* 等待增加轮廓碰撞 */
	class MfxImage
		: public MfxGraph
	{
		MfxObject;
	public:
		MfxImage();

		MfxImage(MfxColor* color, MfxRect* set);
		MfxImage(MfxColor* color, MfxRect& set) :MfxImage(color, &set) {};
		MfxImage(MfxColor* color, MfxRect&& set) :MfxImage(color, &set) {};

		MfxImage(MfxColor* color, MfxSize* set) :MfxImage(color, MfxRect(set)) {};
		MfxImage(MfxColor* color, MfxSize& set) :MfxImage(color, &set) {};
		MfxImage(MfxColor* color, MfxSize&& set) :MfxImage(color, &set) {};

		MfxImage(MfxString* path, MfxRect* set);
		MfxImage(MfxString* path, MfxRect& set) :MfxImage(path, &set) {};
		MfxImage(MfxString* path, MfxRect&& set) :MfxImage(path, &set) {};

		MfxImage(MfxString* path, MfxSize* set) :MfxImage(path, MfxRect(set)) {};
		MfxImage(MfxString* path, MfxSize& set) :MfxImage(path, &set) {};
		MfxImage(MfxString* path, MfxSize&& set) :MfxImage(path, &set) {};

		MfxImage(IWICBitmap* tIWICBitmap, MfxRect* set);
		MfxImage(IWICBitmap* tIWICBitmap, MfxRect& set) :MfxImage(tIWICBitmap, &set) {};
		MfxImage(IWICBitmap* tIWICBitmap, MfxRect&& set) :MfxImage(tIWICBitmap, &set) {};

		MfxImage(IWICBitmap* tIWICBitmap, MfxSize* set) :MfxImage(tIWICBitmap, MfxRect(set)) {};
		MfxImage(IWICBitmap* tIWICBitmap, MfxSize& set) :MfxImage(tIWICBitmap, &set) {};
		MfxImage(IWICBitmap* tIWICBitmap, MfxSize&& set) :MfxImage(tIWICBitmap, &set) {};

		virtual ~MfxImage();

		MfxReturn Clone(MfxImage** ret);

	protected:
		MfxCanvas* myCanvas;
		ID2D1RenderTarget* myRenderTarget;

		IWICBitmap* myIWICBitmap;
		ID2D1Bitmap* myID2D1Bitmap;

	public:
		MfxReturn Paint();

		MfxReturn SetCanvas(MfxCanvas* set);
		MfxReturn GetCanvas(MfxCanvas** ret);

		MfxReturn FromFile(MfxString* path, MfxSize* set);
		MfxReturn FromColor(MfxColor* color, MfxSize* set);

	public:
		MfxReturn GetIWICBitmap(IWICBitmap** ret);
		MfxReturn GetID2D1Bitmap(ID2D1Bitmap** ret);

		MfxReturn GetGdipBitmap(Gdiplus::Bitmap** ret);

		MfxReturn GetHICON(HICON* ret);
		MfxReturn GetHBITMAP(MfxColor* set, HBITMAP* ret);

	public:
		MfxReturn SetIWICBitmap(IWICBitmap* set);

	public:
		MfxReturn Update_Canvas();

		MfxReturn ResetID2D1Bitmap();

		MfxReturn ResetIWICBitmapFromFile(MfxString* path, MfxSize* set);
		MfxReturn ResetIWICBitmapFromColor(MfxColor* color, MfxSize *set);
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

		MfxWords(MfxString str, MfxRect* set);
		MfxWords(MfxString str, MfxRect& set) :MfxWords(str, &set) {};
		MfxWords(MfxString str, MfxRect&& set) :MfxWords(str, &set) {};

		MfxWords(MfxString str, MfxSize* set) :MfxWords(str, MfxRect(set)) {};
		MfxWords(MfxString str, MfxSize& set) :MfxWords(str, &set) {};
		MfxWords(MfxString str, MfxSize&& set) :MfxWords(str, &set) {};

		MfxWords(MfxString str, MfxRect* set, FLOAT size);
		MfxWords(MfxString str, MfxRect& set, FLOAT size) :MfxWords(str, &set, size) {};
		MfxWords(MfxString str, MfxRect&& set, FLOAT size) :MfxWords(str, &set, size) {};

		MfxWords(MfxString str, MfxSize* set, FLOAT size) :MfxWords(str, MfxRect(set)) {};
		MfxWords(MfxString str, MfxSize& set, FLOAT size) :MfxWords(str, &set, size) {};
		MfxWords(MfxString str, MfxSize&& set, FLOAT size) :MfxWords(str, &set, size) {};

		MfxWords(MfxString str, MfxRect* set, FLOAT size, IDWriteTextFormat* format);
		MfxWords(MfxString str, MfxRect& set, FLOAT size, IDWriteTextFormat* format) :MfxWords(str, &set, size, format) {};
		MfxWords(MfxString str, MfxRect&& set, FLOAT size, IDWriteTextFormat* format) :MfxWords(str, &set, size, format) {};

		MfxWords(MfxString str, MfxSize* set, FLOAT size, IDWriteTextFormat* format) :MfxWords(str, MfxRect(set), size, format) {};
		MfxWords(MfxString str, MfxSize& set, FLOAT size, IDWriteTextFormat* format) :MfxWords(str, &set, size, format) {};
		MfxWords(MfxString str, MfxSize&& set, FLOAT size, IDWriteTextFormat* format) :MfxWords(str, &set, size, format) {};

		virtual ~MfxWords();

		MfxReturn Clone(MfxWords** ret);

		static IDWriteTextFormat* gDefTextFormat;

	protected:
		MfxString myText;
		MfxColor myColor;
		ID2D1SolidColorBrush* myTextBrush;
		IDWriteTextFormat* myTextFormat;
		IDWriteTextLayout* myTextLayout;

		MfxCanvas* myCanvas;
		ID2D1RenderTarget* myRenderTarget;

	public:
		MfxReturn Paint();

		MfxReturn SetCanvas(MfxCanvas* set);
		MfxReturn GetCanvas(MfxCanvas** ret);

	public:
		MfxReturn GetText(MfxString* ret);
		MfxReturn GetTextSize(FLOAT* ret);

		MfxReturn GetFontName(MfxString* ret);
		MfxReturn GetTextColor(MfxColor* ret);

		MfxReturn GetTextFormat(IDWriteTextFormat** ret);

		MfxReturn GetTextAlignmentX(TextAlignmentX* ret);
		MfxReturn GetTextAlignmentY(TextAlignmentY* ret);

	public:
		MfxReturn SetRect(MfxRect* set);
		MfxReturn SetSize(MfxSize* set);

		MfxReturn SetText(MfxString set);
		MfxReturn SetTextSize(FLOAT set);

		MfxReturn SetFontName(MfxString set);
		MfxReturn SetTextColor(MfxColor* set);

		MfxReturn SetTextFormat(IDWriteTextFormat* set);

		MfxReturn SetTextAlignmentX(TextAlignmentX set);
		MfxReturn SetTextAlignmentY(TextAlignmentY set);

	public:
		MfxReturn Update_Canvas();
		MfxReturn ResetTextLayout();
	};
}


