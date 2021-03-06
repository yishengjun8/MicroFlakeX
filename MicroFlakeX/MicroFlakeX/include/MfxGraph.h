#pragma once

namespace MicroFlakeX
{
	class MFX_DLL_EXPORT MfxGraph;

	class MFX_DLL_EXPORT MfxCanvas;

	class MFX_DLL_EXPORT MfxImage;
	class MFX_DLL_EXPORT MfxWords;

	class MFX_DLL_EXPORT MfxEllipse;
	class MFX_DLL_EXPORT MfxRectangle;


	typedef MfxCanvas*	pMfxCanvas;
	typedef MfxImage*	pMfxImage;
	typedef MfxWords*	pMfxWords;
	typedef MfxEllipse*	pMfxEllipse;
	typedef MfxRectangle*	pMfxRectangleangle;
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

		static MfxReturn IWICBitmapFromFile(IWICBitmap** ret, const MfxStringW path, const MfxSize size);
		static MfxReturn IWICBitmapFromColor(IWICBitmap** ret, const  MfxColor color, const  MfxSize size);
		static MfxReturn IWICBitmapFromGdipBitmap(IWICBitmap** ret, const Gdiplus::Bitmap* set, const  MfxRect rect);

		static MfxReturn ID2D1BitmapFromFile(ID2D1Bitmap** ret, ID2D1RenderTarget* pRendTar, const MfxStringW path, const  MfxSize size);
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
		***************************************************************/
		MFX_OBJ_ENABLE_REFLECTION;

	public:
		virtual MfxReturn GetRect(MfxRect* ret) const;
		virtual MfxReturn GetSize(MfxSize* ret) const;
		virtual MfxReturn GetPoint(MfxPoint* ret) const;

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
		public MfxBase
	{
		MFX_OBJ_ENABLE_REFLECTION;
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
		MfxReturn GetDC(HDC* ret) const;
		MfxReturn GetWnd(HWND* ret) const;
		MfxReturn GetBackColor(MfxColor* ret) const;

	public:
		MfxReturn SetDC(HDC set);
		MfxReturn SetWnd(HWND set);
		MfxReturn SetBackColor(MfxColor* set);

	public:
		MfxReturn PaintBegin(MfxRect* clip);
		MfxReturn PaintFinish();

	public:
		MfxReturn PaintCheck(bool* ret) const;

	public:
		MfxReturn GetRenderTarget(ID2D1RenderTarget** ret) const;

	public:
		MfxReturn SetRect(MfxRect* set);
		MfxReturn SetSize(MfxSize* set);
		MfxReturn SetPoint(MfxPoint* set);
	public:
		MfxReturn GetRect(MfxRect* ret) const;
		MfxReturn GetSize(MfxSize* ret) const;
		MfxReturn GetPoint(MfxPoint* ret) const;
	protected:
		HDC myDC;
		HWND myWnd;
		MfxRect myRect;

		MfxRect myClipRect;
		MfxColor myBackColor;

		bool myPaintFlag;
		ID2D1RenderTarget* myRenderTarget;
	};
}

namespace MicroFlakeX
{
	/* �ȴ�����������ײ */
	class MfxImage : 
		public MfxGraph
	{
		MFX_OBJ_ENABLE_REFLECTION;
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

		MfxImage(const MfxStringW* path, const MfxRect* set);
		MfxImage(const MfxStringW* path, const MfxRect& set) :MfxImage(path, &set) {};
		MfxImage(const MfxStringW* path, const MfxRect&& set) :MfxImage(path, &set) {};

		MfxImage(const MfxStringW* path, const  MfxSize* set) :MfxImage(path, MfxRect(set)) {};
		MfxImage(const MfxStringW* path, const  MfxSize& set) :MfxImage(path, &set) {};
		MfxImage(const MfxStringW* path, const  MfxSize&& set) :MfxImage(path, &set) {};

		MfxImage(IWICBitmap* tIWICBitmap, const MfxRect* set);
		MfxImage(IWICBitmap* tIWICBitmap, const  MfxRect& set) :MfxImage(tIWICBitmap, &set) {};
		MfxImage(IWICBitmap* tIWICBitmap, const MfxRect&& set) :MfxImage(tIWICBitmap, &set) {};

		MfxImage(IWICBitmap* tIWICBitmap, const MfxSize* set) :MfxImage(tIWICBitmap, MfxRect(set)) {};
		MfxImage(IWICBitmap* tIWICBitmap, const MfxSize& set) :MfxImage(tIWICBitmap, &set) {};
		MfxImage(IWICBitmap* tIWICBitmap, const MfxSize&& set) :MfxImage(tIWICBitmap, &set) {};

		virtual ~MfxImage();

		MfxReturn MFX_OBJ_ENABLE_CLONE(ret);

	protected:
		MfxCanvas* myCanvas;
		ID2D1RenderTarget* myRenderTarget;

		IWICBitmap* myIWICBitmap;
		ID2D1Bitmap* myID2D1Bitmap;

		bool myBitmapUpdateFlage;
	public:
		MfxReturn Paint();

		MfxReturn SetCanvas(MfxCanvas* set);
		MfxReturn GetCanvas(MfxCanvas** ret) const;

		MfxReturn FromFile(MfxStringW* path, MfxSize* set);
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

		MfxReturn ResetIWICBitmapFromFile(const MfxStringW* path, const MfxSize* set);
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
		MFX_OBJ_ENABLE_REFLECTION;
	public:
		MfxWords();
		MfxWords(const MfxWords* set) :MfxWords(set->myText, set->myRect, set->myTextLayout->GetFontSize(), set->myTextLayout) {};
		MfxWords(const MfxWords& set) :MfxWords(&set) {};
		MfxWords(const MfxWords&& set) noexcept :MfxWords(&set) {};

		MfxWords(const MfxStringW str, const MfxRect* set);
		MfxWords(const MfxStringW str, const MfxRect& set) :MfxWords(str, &set) {};
		MfxWords(const MfxStringW str, const MfxRect&& set) :MfxWords(str, &set) {};

		MfxWords(const MfxStringW str, const MfxSize* set) :MfxWords(str, MfxRect(set)) {};
		MfxWords(const MfxStringW str, const MfxSize& set) :MfxWords(str, &set) {};
		MfxWords(const MfxStringW str, const MfxSize&& set) :MfxWords(str, &set) {};

		MfxWords(const MfxStringW str, const MfxRect* set, const FLOAT size);
		MfxWords(const MfxStringW str, const MfxRect& set, const FLOAT size) :MfxWords(str, &set, size) {};
		MfxWords(const MfxStringW str, const MfxRect&& set, const FLOAT size) :MfxWords(str, &set, size) {};

		MfxWords(const MfxStringW str, const MfxSize* set, const FLOAT size) :MfxWords(str, MfxRect(set)) {};
		MfxWords(const MfxStringW str, const MfxSize& set, const FLOAT size) :MfxWords(str, &set, size) {};
		MfxWords(const MfxStringW str, const MfxSize&& set, const FLOAT size) :MfxWords(str, &set, size) {};

		MfxWords(const MfxStringW str, const MfxRect* set, const FLOAT size, IDWriteTextFormat* format);
		MfxWords(const MfxStringW str, const MfxRect& set, const FLOAT size, IDWriteTextFormat* format) :MfxWords(str, &set, size, format) {};
		MfxWords(const MfxStringW str, const MfxRect&& set, const FLOAT size, IDWriteTextFormat* format) :MfxWords(str, &set, size, format) {};

		MfxWords(const MfxStringW str, const MfxSize* set, const FLOAT size, IDWriteTextFormat* format) :MfxWords(str, MfxRect(set), size, format) {};
		MfxWords(const MfxStringW str, const MfxSize& set, const FLOAT size, IDWriteTextFormat* format) :MfxWords(str, &set, size, format) {};
		MfxWords(const MfxStringW str, const MfxSize&& set, const FLOAT size, IDWriteTextFormat* format) :MfxWords(str, &set, size, format) {};

		virtual ~MfxWords();

		MfxReturn MFX_OBJ_ENABLE_CLONE(ret);

		static IDWriteTextFormat* gDefTextFormat;

	protected:
		MfxStringW myText;
		MfxColor myColor;
		ID2D1SolidColorBrush* myTextBrush;
		bool myTextBrushUpdateFlage;
		IDWriteTextFormat* myTextFormat;
		IDWriteTextLayout* myTextLayout;

		MfxCanvas* myCanvas;
		ID2D1RenderTarget* myRenderTarget;

	public:
		MfxReturn Paint();

		MfxReturn SetCanvas(MfxCanvas* set);
		MfxReturn GetCanvas(MfxCanvas** ret);

	public:
		MfxReturn GetText(MfxStringW* ret);
		MfxReturn GetTextSize(FLOAT* ret);

		MfxReturn GetFontName(MfxStringW* ret);
		MfxReturn GetTextColor(MfxColor* ret);

		MfxReturn GetTextFormat(IDWriteTextFormat** ret);

		MfxReturn GetTextAlignmentX(TextAlignmentX* ret);
		MfxReturn GetTextAlignmentY(TextAlignmentY* ret);

	public:
		MfxReturn SetRect(const MfxRect* set);
		MfxReturn SetSize(const MfxSize* set);

		MfxReturn SetText(const MfxStringW set);
		MfxReturn SetTextSize(const FLOAT set);

		MfxReturn SetFontName(const MfxStringW set);
		MfxReturn SetTextColor(const MfxColor* set);

		MfxReturn SetTextFormat(IDWriteTextFormat* set);

		MfxReturn SetTextAlignmentX(const TextAlignmentX set);
		MfxReturn SetTextAlignmentY(const TextAlignmentY set);

	public:
		MfxReturn Update_Canvas();
		MfxReturn ResetTextLayout();
	};
}

namespace MicroFlakeX
{
	class MfxRectangle :
		public MfxGraph
	{
		MFX_OBJ_ENABLE_REFLECTION;
	public:
		MfxRectangle();

		MfxRectangle(const MfxRect* set, MfxColor fillColor = MfxColor(255, 255, 0, 0), MfxColor frameColor = MfxColor(255, 255, 0, 0));
		MfxRectangle(const MfxRect& set) :MfxRectangle(&set) {};
		MfxRectangle(const MfxRect&& set) :MfxRectangle(&set) {};

		virtual ~MfxRectangle();

		MfxReturn MFX_OBJ_ENABLE_CLONE(ret);

	protected:
		MfxCanvas* myCanvas;
		ID2D1RenderTarget* myRenderTarget;

		MfxColor myFillColor;
		MfxColor myFrameColor;

		ID2D1SolidColorBrush* myFillBrush;
		ID2D1SolidColorBrush* myFrameBrush;

		bool myColorUpdateFlage;
		double myFrameSize;
	public:
		MfxReturn Paint();

		MfxReturn SetCanvas(MfxCanvas* set);
		MfxReturn GetCanvas(MfxCanvas** ret);

	public:
		MfxReturn SetFrameSize(double set);
		MfxReturn SetFillColor(MfxColor* set);
		MfxReturn SetFrameColor(MfxColor* set);
	public:
		MfxReturn GetFrameSize(double* ret);
		MfxReturn GetFillColor(MfxColor* ret);
		MfxReturn GetFrameColor(MfxColor* ret);

	protected:
		double myRounded_X;
		double myRounded_Y;
		bool myRoundedFlage;
	public:
		MfxReturn SetRounded_X(double set);
		MfxReturn SetRounded_Y(double set);
	public:
		MfxReturn GetRounded_X(double* ret);
		MfxReturn GetRounded_Y(double* ret);
	public:
		MfxReturn OpenRounded();
		MfxReturn CloseRounded();
	
	public:
		MfxReturn GetReallyRect(MfxRect* ret) const;
	public:
		MfxReturn Update_Canvas();
	};
}

/**
namespace MicroFlakeX
{
	class MfxEllipse :
		public MfxGraph
	{
		MFX_OBJ_ENABLE_REFLECTION;
	public:
		MfxEllipse();

		MfxEllipse(const MfxRect* set, MfxColor fillColor = MfxColor(255, 255, 0), MfxColor frameColor = MfxColor(255, 255));
		MfxEllipse(const MfxRect& set) :MfxEllipse(&set) {};
		MfxEllipse(const MfxRect&& set) :MfxEllipse(&set) {};

		virtual ~MfxEllipse();

		MfxReturn MFX_OBJ_ENABLE_CLONE(ret);

	protected:
		MfxCanvas* myCanvas;
		ID2D1RenderTarget* myRenderTarget;

		MfxColor myFillColor;
		MfxColor myFrameColor;

		ID2D1SolidColorBrush* myFillBrush;
		ID2D1SolidColorBrush* myFrameBrush;

		bool myColorUpdateFlage;
		double myFrameSize;
	public:
		MfxReturn Paint();

		MfxReturn SetCanvas(MfxCanvas* set);
		MfxReturn GetCanvas(MfxCanvas** ret);

	public:
		MfxReturn SetFrameSize(double set);
		MfxReturn SetFillColor(MfxColor* set);
		MfxReturn SetFrameColor(MfxColor* set);
	public:
		MfxReturn GetFrameSize(double* ret);
		MfxReturn GetFillColor(MfxColor* ret);
		MfxReturn GetFrameColor(MfxColor* ret);

	protected:
		double myRounded_X;
		double myRounded_Y;
		bool myRoundedFlage;
	public:
		MfxReturn SetRounded_X(double set);
		MfxReturn SetRounded_Y(double set);
	public:
		MfxReturn GetRounded_X(double* ret);
		MfxReturn GetRounded_Y(double* ret);
	public:
		MfxReturn OpenRounded();
		MfxReturn CloseRounded();

	public:
		MfxReturn GetReallyRect(MfxRect* ret) const;
	public:
		MfxReturn Update_Canvas();
	};
}

/**/