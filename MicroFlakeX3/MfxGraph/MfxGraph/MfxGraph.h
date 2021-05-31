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


	class MFX_PORT MfxEllipse;
	class MFX_PORT MfxCircular;
	class MFX_PORT MfxRectangle;
}

namespace MicroFlakeX
{
	typedef std::vector<MfxGraph*> MfxGraphVector;
}

namespace MicroFlakeX
{
	class MfxGraph : 
		public MfxBase
	{
	public:
		static MfxReturn GetID2D1DCRenderTarget(ID2D1RenderTarget** ret, const  HDC set, const  MfxRect rect);
		static MfxReturn GetID2D1HwndRenderTarget(ID2D1RenderTarget** ret, const HWND set, const  MfxSize size);

		static MfxReturn IWICBitmapFromFile(IWICBitmap** ret, const MfxString path, const MfxSize size);
		static MfxReturn IWICBitmapFromColor(IWICBitmap** ret, const  MfxColor color, const  MfxSize size);
		static MfxReturn IWICBitmapFromGdipBitmap(IWICBitmap** ret, const Gdiplus::Bitmap* set, const  MfxRect rect);

		static MfxReturn ID2D1BitmapFromFile(ID2D1Bitmap** ret, ID2D1RenderTarget* pRendTar, const MfxString path, const  MfxSize size);
		static MfxReturn ID2D1BitmapFromIWICBitmap(ID2D1Bitmap** ret, ID2D1RenderTarget* pRendTar, IWICBitmap* bitmap, const MfxSize size);

		static MfxReturn GdipBitmapFromIWICBitmap(Gdiplus::Bitmap** ret, IWICBitmap* set, const MfxRect rect);

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
		virtual MfxReturn GetRect(MfxRect* ret)const;
		virtual MfxReturn GetSize(MfxSize* ret)const;
		virtual MfxReturn GetPoint(MfxPoint* ret)const;

	public:
		virtual MfxReturn SetRect(const MfxRect* set);
		virtual MfxReturn SetSize(const MfxSize* set);
		virtual MfxReturn SetPoint(const MfxPoint* set);

	public:
		virtual MfxReturn IntersectWith(MfxGraph* set, MfxRect* ret);

	protected:
		MfxRect myRect;
	};
}

namespace MicroFlakeX
{
	class MfxCanvas :
		public MfxGraph
	{
		MfxObject;
	public:
		MfxCanvas();

		MfxCanvas(const MfxRect* set);
		MfxCanvas(const MfxRect& set) :MfxCanvas(&set) {};
		MfxCanvas(const MfxRect&& set) :MfxCanvas(&set) {};

		MfxCanvas(const MfxSize* size);
		MfxCanvas(const MfxSize& size) :MfxCanvas(&size) {};
		MfxCanvas(const MfxSize&& size) :MfxCanvas(&size) {};

		MfxCanvas(const HDC setDC, const MfxRect* setRect);
		MfxCanvas(const HDC setDC, const MfxRect& setRect) :MfxCanvas(setDC, &setRect) {};
		MfxCanvas(const HDC setDC, const MfxRect&& setRect) :MfxCanvas(setDC, &setRect) {};

		MfxCanvas(const HDC setDC, const MfxSize* setSize) :MfxCanvas(setDC, MfxRect(setSize)) {};
		MfxCanvas(const HDC setDC, const  MfxSize& setSize) :MfxCanvas(setDC, &setSize) {};
		MfxCanvas(const HDC setDC, const MfxSize&& setSize) :MfxCanvas(setDC, &setSize) {};

		MfxCanvas(const HWND setWnd, const MfxRect* setRect);
		MfxCanvas(const HWND setWnd, const MfxRect& setRect) :MfxCanvas(setWnd, &setRect) {};
		MfxCanvas(const HWND setWnd, const  MfxRect&& setRect) :MfxCanvas(setWnd, &setRect) {};

		MfxCanvas(const HWND setWnd, const MfxSize* setSize) :MfxCanvas(setWnd, MfxRect(setSize)) {};
		MfxCanvas(const HWND setWnd, const MfxSize& setSize) :MfxCanvas(setWnd, &setSize) {};
		MfxCanvas(const HWND setWnd, const MfxSize&& setSize) :MfxCanvas(setWnd, &setSize) {};

		virtual ~MfxCanvas();

	public:
		MfxReturn GetDC(HDC* ret)const;
		MfxReturn GetWnd(HWND* ret)const;
		MfxReturn GetBackColor(MfxColor* ret)const;

	public:
		MfxReturn SetDC(HDC set);
		MfxReturn SetWnd(HWND set);
		MfxReturn SetBackColor(MfxColor* set);

	public:
		MfxReturn PaintBegin(MfxRect* clip);
		MfxReturn PaintFinish();

	public:
		MfxReturn PaintCheck(bool* ret)const;

	public:
		MfxReturn GetRenderTarget(ID2D1RenderTarget** ret)const;

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
	class MfxImage : 
		public MfxGraph
	{
		MfxObject;
	public:
		MfxImage();
		MfxImage(const MfxImage* set) : MfxImage(set->myIWICBitmap, set->myRect) {};
		MfxImage(const MfxImage& set) :MfxImage(&set) {};
		MfxImage(const MfxImage&& set) noexcept :MfxImage(&set) {};

		MfxImage(const MfxColor* color, const  MfxRect* set);
		MfxImage(const MfxColor* color, const  MfxRect& set) :MfxImage(color, &set) {};
		MfxImage(const MfxColor* color, const  MfxRect&& set) :MfxImage(color, &set) {};

		MfxImage(const MfxColor* color, const MfxSize* set) :MfxImage(color, MfxRect(set)) {};
		MfxImage(const MfxColor* color, const  MfxSize& set) :MfxImage(color, &set) {};
		MfxImage(const MfxColor* color, const  MfxSize&& set) :MfxImage(color, &set) {};

		MfxImage(const MfxString* path, const MfxRect* set);
		MfxImage(const MfxString* path, const MfxRect& set) :MfxImage(path, &set) {};
		MfxImage(const MfxString* path, const MfxRect&& set) :MfxImage(path, &set) {};

		MfxImage(const MfxString* path, const  MfxSize* set) :MfxImage(path, MfxRect(set)) {};
		MfxImage(const MfxString* path, const  MfxSize& set) :MfxImage(path, &set) {};
		MfxImage(const MfxString* path, const  MfxSize&& set) :MfxImage(path, &set) {};

		MfxImage(IWICBitmap* tIWICBitmap, const MfxRect* set);
		MfxImage(IWICBitmap* tIWICBitmap, const  MfxRect& set) :MfxImage(tIWICBitmap, &set) {};
		MfxImage(IWICBitmap* tIWICBitmap, const MfxRect&& set) :MfxImage(tIWICBitmap, &set) {};

		MfxImage(IWICBitmap* tIWICBitmap, const MfxSize* set) :MfxImage(tIWICBitmap, MfxRect(set)) {};
		MfxImage(IWICBitmap* tIWICBitmap, const MfxSize& set) :MfxImage(tIWICBitmap, &set) {};
		MfxImage(IWICBitmap* tIWICBitmap, const MfxSize&& set) :MfxImage(tIWICBitmap, &set) {};

		virtual ~MfxImage();

		MfxReturn Clone(MfxImage** ret) const;

	protected:
		MfxCanvas* myCanvas;
		ID2D1RenderTarget* myRenderTarget;

		IWICBitmap* myIWICBitmap;
		ID2D1Bitmap* myID2D1Bitmap;

	public:
		MfxReturn Paint();

		MfxReturn SetCanvas(MfxCanvas* set);
		MfxReturn GetCanvas(MfxCanvas** ret)const;

		MfxReturn FromFile(MfxString* path, MfxSize* set);
		MfxReturn FromColor(MfxColor* color, MfxSize* set);

	public:
		MfxReturn GetIWICBitmap(IWICBitmap** ret)const;
		MfxReturn GetID2D1Bitmap(ID2D1Bitmap** ret)const;

		MfxReturn GetGdipBitmap(Gdiplus::Bitmap** ret)const;

		MfxReturn GetHICON(HICON* ret)const;
		MfxReturn GetHBITMAP(MfxColor* set, HBITMAP* ret)const;

	public:
		MfxReturn SetIWICBitmap(IWICBitmap* set);

	public:
		MfxReturn Update_Canvas();

		MfxReturn ResetID2D1Bitmap();

		MfxReturn ResetIWICBitmapFromFile(const MfxString* path, const MfxSize* set);
		MfxReturn ResetIWICBitmapFromColor(const MfxColor* color, const MfxSize *set);
	};
}

namespace MicroFlakeX
{
	typedef enum DWRITE_TEXT_ALIGNMENT TextAlignmentX;
	typedef enum DWRITE_PARAGRAPH_ALIGNMENT TextAlignmentY;

	class MfxWords :
		public MfxGraph
	{
		MfxObject;
	public:
		MfxWords();
		MfxWords(const MfxWords* set) :MfxWords(set->myText, set->myRect, set->myTextLayout->GetFontSize(), set->myTextLayout) {};
		MfxWords(const MfxWords& set) :MfxWords(&set) {};
		MfxWords(const MfxWords&& set) noexcept :MfxWords(&set) {};

		MfxWords(const MfxString str, const MfxRect* set);
		MfxWords(const MfxString str, const MfxRect& set) :MfxWords(str, &set) {};
		MfxWords(const MfxString str, const MfxRect&& set) :MfxWords(str, &set) {};

		MfxWords(const MfxString str, const MfxSize* set) :MfxWords(str, MfxRect(set)) {};
		MfxWords(const MfxString str, const MfxSize& set) :MfxWords(str, &set) {};
		MfxWords(const MfxString str, const MfxSize&& set) :MfxWords(str, &set) {};

		MfxWords(const MfxString str, const MfxRect* set, const FLOAT size);
		MfxWords(const MfxString str, const MfxRect& set, const FLOAT size) :MfxWords(str, &set, size) {};
		MfxWords(const MfxString str, const MfxRect&& set, const FLOAT size) :MfxWords(str, &set, size) {};

		MfxWords(const MfxString str, const MfxSize* set, const FLOAT size) :MfxWords(str, MfxRect(set)) {};
		MfxWords(const MfxString str, const MfxSize& set, const FLOAT size) :MfxWords(str, &set, size) {};
		MfxWords(const MfxString str, const MfxSize&& set, const FLOAT size) :MfxWords(str, &set, size) {};

		MfxWords(const MfxString str, const MfxRect* set, const FLOAT size, IDWriteTextFormat* format);
		MfxWords(const MfxString str, const MfxRect& set, const FLOAT size, IDWriteTextFormat* format) :MfxWords(str, &set, size, format) {};
		MfxWords(const MfxString str, const MfxRect&& set, const FLOAT size, IDWriteTextFormat* format) :MfxWords(str, &set, size, format) {};

		MfxWords(const MfxString str, const MfxSize* set, const FLOAT size, IDWriteTextFormat* format) :MfxWords(str, MfxRect(set), size, format) {};
		MfxWords(const MfxString str, const MfxSize& set, const FLOAT size, IDWriteTextFormat* format) :MfxWords(str, &set, size, format) {};
		MfxWords(const MfxString str, const MfxSize&& set, const FLOAT size, IDWriteTextFormat* format) :MfxWords(str, &set, size, format) {};

		virtual ~MfxWords();

		MfxReturn Clone(MfxWords** ret) const;

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
		MfxReturn SetRect(const MfxRect* set);
		MfxReturn SetSize(const MfxSize* set);

		MfxReturn SetText(const MfxString set);
		MfxReturn SetTextSize(const FLOAT set);

		MfxReturn SetFontName(const MfxString set);
		MfxReturn SetTextColor(const MfxColor* set);

		MfxReturn SetTextFormat(IDWriteTextFormat* set);

		MfxReturn SetTextAlignmentX(const TextAlignmentX set);
		MfxReturn SetTextAlignmentY(const TextAlignmentY set);

	public:
		MfxReturn Update_Canvas();
		MfxReturn ResetTextLayout();
	};
}


