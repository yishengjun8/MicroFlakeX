#pragma once

#ifdef MFX_BUILDING
#define MFX_PORT __declspec(dllexport)
#else
#define MFX_PORT __declspec(dllimport)
#pragma comment(lib, "MfxGraph.lib")
#include "MfxGraph.h"

#include "MfxTypes.h"

#endif

//公开 类 - 模板
namespace MicroFlakeX
{
	class MFX_PORT MfxGraph;

	class MFX_PORT MfxCanvas;

	class MFX_PORT MfxImage;
	class MFX_PORT MfxWords;
}

//公开 容器
namespace MicroFlakeX
{
	typedef std::vector<MfxGraph*> MfxGraphVector;
}

namespace __MicroFlakeX
{
	template<class Interface>
	inline void SafeRelease(Interface*& pInterfaceToRelease) {
		if (pInterfaceToRelease != nullptr) {
			pInterfaceToRelease->Release();
			pInterfaceToRelease = nullptr;
		}
	}
}

//MfxBasicGraph基类
namespace MicroFlakeX
{
	//MfxGraph类
	class MfxGraph
		: public MfxBase
	{
	public:
		static MfxReturn GetID2D1DCRenderTarget(ID2D1RenderTarget** ret, HDC &set, MfxRect rect);
		static MfxReturn GetID2D1HwndRenderTarget(ID2D1RenderTarget** ret, HWND &set, MfxSize size);

		static MfxReturn IWICBitmapFromFile(IWICBitmap** ret, MfxStrW &path, MfxSize size);
		static MfxReturn IWICBitmapFromColor(IWICBitmap** ret, MfxColor color, MfxSize size);

		static MfxReturn ID2D1BitmapFromFile(ID2D1Bitmap** ret, ID2D1RenderTarget* pRendTar, 
			MfxStrW &path, MfxSize size);
		static MfxReturn ID2D1BitmapFromIWICBitmap(ID2D1Bitmap** ret, ID2D1RenderTarget* pRendTar,
			IWICBitmap* bitmap, MfxSize size);
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
		BOOL operator==(MfxBase& rhs);
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

/* ———————————————————————————————————————————— */
/* ———————————————————————————————————————————— */
/* ———————————————————————————————————————————— */

//公开 DS画板
namespace MicroFlakeX
{
	class MfxCanvas
		: public MfxGraph
	{
		MfxObject;
	public:
		MfxCanvas();
		virtual ~MfxCanvas();
		MfxReturn Clone(MfxBase** ret);
		MfxBase& operator=(MfxBase& rhs);
		BOOL operator==(MfxBase& rhs);

	public:
		MfxReturn SetDC(HDC set);
		MfxReturn GetDC(HDC* ret);

		MfxReturn SetWnd(HWND set);
		MfxReturn GetWnd(HWND* ret);

	public:
		MfxReturn PaintBegin();
		MfxReturn PaintFinish();
	public:
		MfxReturn GetRenderTarget(ID2D1RenderTarget** ret);

	public:
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

//MfxImage
namespace MicroFlakeX
{
	//支持两种绘制模式
	class MfxImage
		: public MfxGraph
	{
		MfxObject;
	public:
		MfxImage();
		virtual ~MfxImage();
		MfxReturn Clone(MfxBase** ret);
		MfxBase& operator=(MfxBase& rhs);
		BOOL operator==(MfxBase& rhs);

	protected:
		MfxCanvas* myCanvas;
		ID2D1RenderTarget* myRenderTarget;

		IWICBitmap* myIWICBitmap;
		ID2D1Bitmap* myID2D1Bitmap;
	public:
		MfxReturn ResetIWICBitmap(MfxStrW* path, MfxSize* set);
		MfxReturn ResetID2D1Bitmap();
	public:
		MfxReturn FromFile(MfxStrW* path, MfxSize* set);
		MfxReturn FromColor(MfxStrW* path, MfxSize* set);

		MfxReturn SetCanvas(MfxCanvas* set);
		MfxReturn GetCanvas(MfxCanvas** ret);

		MfxReturn Paint();
	public:
		MfxReturn GetIWICBitmap(IWICBitmap** ret);
		MfxReturn GetID2D1Bitmap(ID2D1Bitmap** ret);

		MfxReturn SetIWICBitmap(IWICBitmap* set);
		MfxReturn SetID2D1Bitmap(ID2D1Bitmap* set);
	};
}

//MfxWorld
/**
namespace MicroFlakeX
{
	//支持两种绘制模式
	class MfxWords
		: public MfxGraph
	{
		MfxObject;
	protected:
		void MfxWordsInitData(MfxWorlds_Type set);
	public:
		MfxWords();
		MfxWords(MfxWorlds_Type set);
		virtual ~MfxWords();
		void operator=(MfxWords& rhs);

		MfxReturn Clone(MfxWords** ret);
		MfxReturn Similar(MfxWords* set);
	protected:
		static MfxWorlds_Type g_DefType;
	public:
		static void SetDefType(MfxWorlds_Type& setType);
		static void GetDefType(MfxWorlds_Type& getType);

	protected:
		int myCachedMode; //缓冲模式
		HDC myDC;
		Gdiplus::Graphics* myGraphics;
		Gdiplus::GraphicsPath* myGraphicsPath;

		MfxDataFlag_Rect myRect; //文本框位置
		MfxStrW myText;
		MfxWorlds_Type myType; //文字类型 - 使用全局参数
		Gdiplus::FontFamily* myFontFamily; //文字家族
		Gdiplus::StringFormat* myStringFormat; //布局信息

		Gdiplus::Pen* myFramePen;
		Gdiplus::Brush* myBackBrush;
		Gdiplus::Brush* myTextBrush;

		Gdiplus::Rect myTextRect; //最终文字的位置
		Gdiplus::Pen* myTextRectPen; //用来包裹文字的边框笔

		MfxDataFlag_pGdipBitmap myShowBitmap;
		Gdiplus::Graphics* myShowGraphics;
		Gdiplus::CachedBitmap* myCachedShowBitmap;

		Gdiplus::Region* myBasicRegion, * myShowRegion;
		MfxDataFlag_Size myCollisionBlock;

		BOOL myResetRegionLock;
		BOOL myResetTextPathLock;
		BOOL myResetShowBitmapLock;
		BOOL myResetShowCachedBitmapLock;
	protected:
		void Mode_ClearDC();
		void Mode_ResetDC(HDC set);

	public:
		MfxReturn LockResetRegion();
		MfxReturn UnLockResetRegion();

		MfxReturn LockResetTextPath();
		MfxReturn UnLockResetTextPath();

		MfxReturn LockResetShowBitmap();
		MfxReturn UnLockResetShowBitmap();

		MfxReturn LockResetCachedShowBitmap();
		MfxReturn UnLockResetCachedShowBitmap();

		MfxReturn ResetRegion();
		MfxReturn ResetTextPath(); //重设文字路径
		MfxReturn ResetID2D1Bitmap(); //重设显示图片
		MfxReturn ResetCachedShowBitmap();
	public:
		MfxReturn SetDC(HDC set);
		MfxReturn GetDC(HDC* ret);

		MfxReturn GetID2D1Bitmap(Gdiplus::Bitmap** ret); //获取当前显示图片

		MfxReturn Draw();
		MfxReturn DrawBitmap(Gdiplus::Graphics* set);

	public:
		MfxReturn SetText(MfxStrW set);
		MfxReturn GetText(MfxStrW* ret);

		MfxReturn SetStringFormat(Gdiplus::StringFormat* set); //设置文字格式
		MfxReturn GetStringFormat(Gdiplus::StringFormat** ret);
		
	public:
		MfxReturn SetType(MfxWorlds_Type set);

		MfxReturn SetFontName(MfxStrW set); //设置字体

		MfxReturn SetTextXY(MfxWords_TextXY set); //设置文字对齐
		MfxReturn SetShowStyle(MfxWords_ShowStyle set);
		MfxReturn SetFontStyle(MfxFontStyle set);
		MfxReturn SetSmoothingMode(MfxSmoothingMode_EN set);

		MfxReturn SetTextColor(Gdiplus::Color set);
		MfxReturn SetTextSize_em(MfxPenWidth set); //设置字体大小

		MfxReturn SetFrameColor(Gdiplus::Color set);
		MfxReturn SetFramePenWidth(MfxPenWidth set); //设置边框宽度

		MfxReturn SetBackColor(Gdiplus::Color set);

	public:
		MfxReturn GetType(MfxWorlds_Type* ret);

		MfxReturn GetFontName(MfxStrW* ret); //设置字体

		MfxReturn GetTextXY(MfxWords_TextXY* ret); //设置文字对齐
		MfxReturn GetShowStyle(MfxWords_ShowStyle* ret);
		MfxReturn GetFontStyle(MfxFontStyle* ret);
		MfxReturn GetSmoothingMode(MfxSmoothingMode_EN* ret);

		MfxReturn GetTextColor(Gdiplus::Color* ret);
		MfxReturn GetTextSize_em(MfxPenWidth* ret); //设置字体大小

		MfxReturn GetFrameColor(Gdiplus::Color* ret);
		MfxReturn GetFramePenWidth(MfxPenWidth* ret); //设置边框宽度

		MfxReturn GetBackColor(Gdiplus::Color* ret);
	
	public:
		MfxReturn SetRect(Gdiplus::Rect set);
		MfxReturn SetSize(Gdiplus::Size set);
		MfxReturn SetPoint(Gdiplus::Point set);

		MfxReturn SetCollisionBlock(Gdiplus::Size set);
		MfxReturn CollisionWith(MfxGraph* set, bool* ret);

		MfxReturn SetFramePen(Gdiplus::Pen* set);
		MfxReturn SetBackBrush(Gdiplus::Brush* set);
		MfxReturn SetTextBrush(Gdiplus::Brush* set);

	public:
		MfxReturn GetRect(Gdiplus::Rect* ret);
		MfxReturn GetSize(Gdiplus::Size* ret);
		MfxReturn GetPoint(Gdiplus::Point* ret);

		MfxReturn GetRegion(Gdiplus::Region** ret);
		MfxReturn GetRegionBlock(Gdiplus::Size* ret);

		MfxReturn GetFramePen(Gdiplus::Pen** ret);
		MfxReturn GetBackBrush(Gdiplus::Brush** ret);
		MfxReturn GetTextBrush(Gdiplus::Brush** ret);
	};
}/**/


