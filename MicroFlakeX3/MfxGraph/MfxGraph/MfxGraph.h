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
	class MFX_PORT MfxWorld;
}

//公开 容器
namespace MicroFlakeX
{
	typedef std::vector<MfxGraph*> MfxGraphVector;
}

//MfxBasicGraph基础
namespace MicroFlakeX
{
	typedef int MfxPenWidth; //笔的粗细
	typedef int MfxFontStyle;
	typedef int MfxWords_TextXY;


	struct MfxGraphList_Value
	{
		MfxGraphList_Value(MfxGraph* graph, int floor)
		{
			myGraph = graph;
			myFloor = floor;
		}
		MfxGraph* myGraph;
		int myFloor;

		MfxGraphList_Value* Clone()
		{
			return new MfxGraphList_Value(myGraph, myFloor);
		}
	};
}

//MfxBasicGraph容器
namespace MicroFlakeX
{
	typedef std::vector<MfxGraphList_Value*> MfxBasicGraph_Vector;

	typedef MfxDataFlag<MfxRect*> MfxFlagRect;
	typedef MfxDataFlag<MfxSize*> MfxFlagSize;
	typedef MfxDataFlag<MfxPoint*> MfxFlagPoint;
}

//MfxBasicGraph枚举
namespace MicroFlakeX
{
	//文字样式
	enum MfxFontStyle_EN
	{
		MfxFontStyle_Regu = Gdiplus::FontStyleRegular, //指定字体的正常重量或粗细。
		MfxFontStyle_Bold = Gdiplus::FontStyleBold, //指定粗体字。粗体是较重的重量或厚度。
		MfxFontStyle_Ital = Gdiplus::FontStyleItalic, //指定斜体字体，该字体使字符的垂直词干明显倾斜。
		MfxFontStyle_UnderLine = Gdiplus::FontStyleUnderline, //指定下划线，该下划线在字符的基线下方显示一行。
		MfxFontStyle_StrikeOut = Gdiplus::FontStyleStrikeout, //指定删除线，删除线显示在字符中间绘制的水平线。
	};

	//文字显示方式(将你希望的枚举用|连接起来)
	enum MfxWords_ShowStyle_EN
	{

		MfxWords_ShowStyle_null = 0x0000,	//仅显示文字
		MfxWords_ShowStyle_fill = 0x0001,	//填充背景
		MfxWords_ShowStyle_fram = 0x0002,	//填充边框
		MfxWords_ShowStyle_def = MfxWords_ShowStyle_null,	//默认的显示方式 - 等同于MfxWords_ShowType_null
	};

	//文字排版格式
	enum  MfxWords_TextXY_EN
	{
		MfxWords_TextX_near = 0x0001,		//X轴靠左排版
		MfxWords_TextX_center = 0x0002,		//X轴居中排版
		MfxWords_TextX_far = 0x0004,		//X轴靠右排版
		MfxWords_TextX_def = MfxWords_TextX_center, //默认的格式 - 等同于MfxWords_FormatX_near
		MfxWords_TextY_near = 0x0010,		//Y轴靠上排版
		MfxWords_TextY_center = 0x0020,		//Y轴居中排版
		MfxWords_TextY_far = 0x0040,		//Y轴靠下排版
		MfxWords_TextY_def = MfxWords_TextY_center, //默认的格式 - 等同于MfxWords_FormatY_near
	};
}

//MfxBasicGraph结构体
namespace MicroFlakeX
{
	/**
	struct MfxWorlds_Type
	{
		MfxStrW myFontName; //字体名字

		MfxWords_TextXY myTextXY; //MfxWords排版格式 - 居中、靠右、靠左
		MfxWords_ShowStyle myShowStyle; //MfxWords显示模式 - 文字、背景、边框
		MfxFontStyle myFontStyle; //Font样式 - 加粗、斜体、删除、下划线
		MfxSmoothingMode_EN mySmoothingMode; //文字绘制质量

		Gdiplus::Color myTextColor; //文字颜色
		MfxPenWidth myTextSize_em; //文字粗细 - em大小

		Gdiplus::Color myFrameColor; //边框颜色
		MfxPenWidth myFramePenWidth; //边框粗细

		Gdiplus::Color myBackColor; //背景颜色
	};
	/**/
}

//MfxBasicGraph基类
namespace MicroFlakeX
{
	//MfxGraph类
	class MfxGraph
		: public MfxBase
	{
		MfxObject;
		static MfxReturn GetID2D1Factory(ID2D1Factory* ret);
		static MfxReturn GetIDWriteFactory(IDWriteFactory* ret);
		static MfxReturn GetIWICImagingFactory(IWICImagingFactory* ret);

		static MfxReturn GetID2D1DCRenderTarget(ID2D1DCRenderTarget* ret, HDC setDC, MfxRect rect);
		static MfxReturn GetID2D1HwndRenderTarget(ID2D1HwndRenderTarget* ret, HWND setWnd, MfxSize size);

		static MfxReturn IWICBitmapFromFile(IWICBitmap* ret, MfxStrW path, MfxSize size);
		static MfxReturn ID2D1BitmapFromFile(ID2D1Bitmap* ret, ID2D1RenderTarget* pRendTar, 
			MfxStrW filePath, MfxSize size);
		static MfxReturn ID2D1BitmapFromIWICBitmap(ID2D1Bitmap* ret, ID2D1RenderTarget* pRendTar,
			IWICBitmap* bitmap, MfxSize size);

	};


	class MfxGraphList
		: public MfxGraph
	{
		MfxObject;
	protected:
		void MfxGraphListInitData();
	public:
		MfxGraphList();
		virtual ~MfxGraphList();
	};

}

/* ———————————————————————————————————————————— */
/* ———————————————————————————————————————————— */
/* ———————————————————————————————————————————— */

//公开 DS画板
namespace MicroFlakeX
{
	class DSCanvas
		: public MfxGraph
	{
		MfxObject;
	public:
		DSCanvas();
		~DSCanvas();
		MfxReturn Clone(MfxBase** ret);
		MfxBase& operator=(MfxBase& rhs);
		BOOL operator==(MfxBase& rhs);

	public:
		MfxReturn SetDC(HDC set);
		MfxReturn GetDC(HDC* ret);
	public:
		MfxReturn ResetRenderTarget();
	public:
		MfxReturn DrawEnd();
		MfxReturn DrawBegin();
		MfxReturn GetRenderTarget(ID2D1RenderTarget** ret);
	public:
		MfxReturn SetRect(MfxRect* set);
		MfxReturn SetSize(MfxSize* set);

	protected:
		HWND myWnd;
		BOOL myDrawLock;
		MfxColor myColor;
		MfxGraphVector myGraphVector;
		ID2D1HwndRenderTarget* myHwndRenderTarget;
	};
}


namespace MicroFlakeX
{
	class MfxGraphList
		: public MfxGraph
		void MfxGraphListInitData();
	public:
	ctor
		MfxRetuus::Point set);

		MfxReturn GetRect(Gdiplus::Rect* ret);
		MfxReturn GetSize(Gdiplus::Size* ret);
		MfxReturn GetPoint(Gdiplus::Point* ret);

		MfxReturn SetCollisionBlock(Gdiplus::Size set);
		MfxReturn CollisionWith(MfxGraph* set, bool* ret);
	};
}
//MfxImage
namespace MicroFlakeX
{
	//支持两种绘制模式
	class MfxTexture
		: public MfxGraph
	{
		MfxObject;
	public:
		MfxTexture();
		~MfxTexture();
		MfxReturn Clone(MfxBase** ret);
		MfxBase& operator=(MfxBase& rhs);
		BOOL operator==(MfxBase& rhs);

	protected:
		MfxDataFlag_Rect myRect;
		ID2D1RenderTarget* myRenderTarget;

		IWICBitmap* myBasicIWICBitmap;
		ID2D1Bitmap* myShowID2D1Bitmap;
	public:
		MfxReturn ResetShowBitmap();
	public:
		MfxReturn FromFile(MfxStrW path);
		MfxReturn FromColor(MfxStrW path);

		MfxReturn SetRenderTarget(ID2D1RenderTarget* set);
		MfxReturn GetRenderTarget(ID2D1RenderTarget** ret);

		MfxReturn Draw();

		MfxReturn SetRect(GdipRect set);
		MfxReturn SetSize(GdipSize set);
		MfxReturn SetPoint(GdipPoint set);

		MfxReturn GetRect(GdipRect* ret);
		MfxReturn GetSize(GdipSize* ret);
		MfxReturn GetPoint(GdipPoint* ret);

		MfxReturn CollisionWith(MfxBasicGraph* set, bool* ret);
		MfxReturn SetCollisionBlock(GdipSize set);
	};
}

//MfxWorld
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

		/**/
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
		/* ———————————————————————————————————————————— */
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
		MfxReturn ResetShowBitmap(); //重设显示图片
		MfxReturn ResetCachedShowBitmap();
	public:
		MfxReturn SetDC(HDC set);
		MfxReturn GetDC(HDC* ret);

		MfxReturn GetShowBitmap(Gdiplus::Bitmap** ret); //获取当前显示图片

		MfxReturn Draw();
		MfxReturn DrawBitmap(Gdiplus::Graphics* set);

	public:
		MfxReturn SetText(MfxStrW set);
		MfxReturn GetText(MfxStrW* ret);

		MfxReturn SetStringFormat(Gdiplus::StringFormat* set); //设置文字格式
		MfxReturn GetStringFormat(Gdiplus::StringFormat** ret);
		/* ———————————————————————————————————————————— */
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
		/* ———————————————————————————————————————————— */
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
		/* ———————————————————————————————————————————— */
	};
}

namespace MicroFlakeX
{
	class MfxTexture
		: public MfxGraph
	{
		MfxObject;
	protected:
		void MfxTextureInitData();
	public:
		MfxTexture();
		virtual ~MfxTexture();
		void operator=(MfxTexture& rhs);

		MfxReturn Clone(MfxTexture** ret);
		MfxReturn Similar(MfxTexture* set);
	protected:
		MfxDataFlag_Rect myRect;
		ID2D1RenderTarget* myRenderTarget;

		IWICBitmap* myBasicIWICBitmap;
		ID2D1Bitmap* myShowID2D1Bitmap;
	public:
		MfxReturn ResetShowBitmap();
	public:
		MfxReturn FromFile(MfxStrW path);
		MfxReturn FromColor(MfxStrW path);

		MfxReturn SetRenderTarget(ID2D1RenderTarget* set);
		MfxReturn GetRenderTarget(ID2D1RenderTarget** ret);

		MfxReturn Draw();

		MfxReturn SetRect(Gdiplus::Rect set);
		MfxReturn SetSize(Gdiplus::Size set);
		MfxReturn SetPoint(Gdiplus::Point set);

		MfxReturn GetRect(Gdiplus::Rect* ret);
		MfxReturn GetSize(Gdiplus::Size* ret);
		MfxReturn GetPoint(Gdiplus::Point* ret);

		MfxReturn CollisionWith(MfxGraph* set, bool* ret);
		MfxReturn SetCollisionBlock(Gdiplus::Size set);
	};
}