#pragma once
#include "MfxBasicModules.h"

namespace MicroFlakeX
{
	class MFX_MOUDULEDLL_IMPORT MfxBasicGraph;	// 图片基类
	class MFX_MOUDULEDLL_IMPORT MfxGraphList;

	class MFX_MOUDULEDLL_IMPORT MfxImage;	//图片
	class MFX_MOUDULEDLL_IMPORT MfxWords;	//文字
	class MFX_MOUDULEDLL_IMPORT MfxShape;	//形状

	class MFX_MOUDULEDLL_IMPORT MfxTexture;	//形状
	
}

//MfxBasicGraph基础
namespace MicroFlakeX
{
	typedef Gdiplus::Graphics GdipGraphics;
	typedef Gdiplus::GraphicsPath GdipGraphicsPath;

	typedef Gdiplus::Rect GdipRect; //矩形
	typedef Gdiplus::Size GdipSize; //大小
	typedef Gdiplus::Point GdipPoint; //点
	typedef Gdiplus::Color GdipColor; //颜色
	typedef int MfxPenWidth; //笔的粗细
	typedef Gdiplus::Region GdipRegion; //区域
	typedef Gdiplus::ImageAttributes GdipImageAttributes;
	typedef Gdiplus::ColorMap GdipColorMap;

	typedef Gdiplus::Pen GdipPen; //笔
	typedef Gdiplus::Font GdipFont; //字体
	typedef Gdiplus::FontFamily GdipFontFamily; //字体家族
	typedef Gdiplus::Brush GdipBrush; //画刷
	typedef Gdiplus::SolidBrush GdipBrushSolid; //纯色画刷
	typedef Gdiplus::StringFormat GdipStringFormat; //布局信息
	typedef Gdiplus::Region GdipRegion;
	typedef Gdiplus::Bitmap GdipBitmap;
	typedef Gdiplus::CachedBitmap GdipCachedBitmap;
	typedef Gdiplus::Matrix GdipMatrix;


	typedef int MfxFontStyle;
	typedef int MfxWords_TextXY;
	typedef int MfxWords_ShowStyle;


	struct MfxGraphList_Value
	{
		MfxGraphList_Value(MfxBasicGraph* graph, int floor)
		{
			myGraph = graph;
			myFloor = floor;
		}
		MfxBasicGraph* myGraph;
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

	typedef MfxDataFlag<GdipBitmap*> MfxDataFlag_pGdipBitmap;
	typedef MfxDataFlag<GdipSize> MfxDataFlag_Size;
	typedef MfxDataFlag<GdipRect> MfxDataFlag_Rect;
	typedef MfxDataFlag<GdipRegion*> MfxDataFlag_Region;
}

//MfxBasicGraph枚举
namespace MicroFlakeX
{
	//线条抗锯齿
	enum MfxSmoothingMode_EN
	{
		MfxSmoothingMode_Low = Gdiplus::SmoothingModeHighSpeed, //低质量抗锯齿
		MfxSmoothingMode_Hig = Gdiplus::SmoothingModeHighQuality, //高质量抗锯齿
		MfxSmoothingMode_Def = MfxSmoothingMode_Low, //默认的线条抗锯齿 - 等同于MfxGraph_SmoothingMode_low
	};

	//图片插值质量
	enum MfxInterpolationMode_EN
	{
		MfxInterpolationMode_Low = Gdiplus::InterpolationModeNearestNeighbor, //低质量 - 最邻近插值法
		MfxInterpolationMode_Med = Gdiplus::InterpolationModeHighQualityBilinear, //中质量 - 双线性插值法
		MfxInterpolationMode_Hig = Gdiplus::InterpolationModeHighQualityBicubic, //高质量 - 双三插值
		MfxInterpolationMode_Def = Gdiplus::InterpolationModeDefault, //默认的插值质量
	};

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
	struct MfxWorlds_Type
	{
		MfxStrW myFontName; //字体名字

		MfxWords_TextXY myTextXY; //MfxWords排版格式 - 居中、靠右、靠左
		MfxWords_ShowStyle myShowStyle; //MfxWords显示模式 - 文字、背景、边框
		MfxFontStyle myFontStyle; //Font样式 - 加粗、斜体、删除、下划线
		MfxSmoothingMode_EN mySmoothingMode; //文字绘制质量

		GdipColor myTextColor; //文字颜色
		MfxPenWidth myTextSize_em; //文字粗细 - em大小

		GdipColor myFrameColor; //边框颜色
		MfxPenWidth myFramePenWidth; //边框粗细

		GdipColor myBackColor; //背景颜色
	};
}

//
namespace MicroFlakeX
{
	MFX_MOUDULEDLL_IMPORT ID2D1Factory* MfxGetID2D1Factory();
	MFX_MOUDULEDLL_IMPORT IDWriteFactory* MfxGetIDWriteFactory();
	MFX_MOUDULEDLL_IMPORT IWICImagingFactory* MfxGetIWICImagingFactory();

	MFX_MOUDULEDLL_IMPORT ID2D1DCRenderTarget* MfxGetID2D1DCRenderTarget(HDC hDC, GdipRect rect);
	MFX_MOUDULEDLL_IMPORT ID2D1HwndRenderTarget* MfxGetID2D1HwndRenderTarget(HWND hWnd, GdipSize size);

	MFX_MOUDULEDLL_IMPORT IWICBitmap* MfxIWICBitmapFromFile(MfxStrW path, UINT width, UINT height);
	MFX_MOUDULEDLL_IMPORT ID2D1Bitmap* MfxID2D1BitmapFromIWICBitmap(IWICBitmap* bitmap, UINT width, UINT height, ID2D1RenderTarget* pRenderTarget);
	MFX_MOUDULEDLL_IMPORT ID2D1Bitmap* MfxID2D1BitmapFromFile(MfxStrW path, UINT width, UINT height, ID2D1RenderTarget * pRenderTarget);
}

//内部函数
namespace __MicroFlakeX
{
	using namespace MicroFlakeX;
	MFX_MOUDULEDLL_IMPORT bool MfxGraphListFloorCompare(MfxGraphList_Value* lhs, MfxGraphList_Value* rhs);
}

//MfxBasicGraph基类
namespace MicroFlakeX
{
	//MfxGraph类 - 可以绘制图形
	class MfxBasicGraph
		: public MfxBasicObject
	{
	public:
		MfxBasicGraph();
		virtual ~MfxBasicGraph();
	};
}

namespace MicroFlakeX
{
	class MfxGraphList 
		: public MfxBasicGraph
	{
		DEFINE_AUTOBASIC;
	protected:
		void MfxGraphListInitData();
	public:
		MfxGraphList();
		virtual ~MfxGraphList();
		MfxReturn Clone(MfxGraphList** ret);
		MfxReturn Similar(MfxGraphList* set);

	protected:
		HDC myDC;
		GdipRect myRect;
		GdipSize myCollisionBlock;
		ID2D1RenderTarget* myRenderTarget;
		MfxBasicGraph_Vector myGraphVector;
		MfxBasicGraph_Vector::iterator myItem;
	public:
		MfxReturn AddItem(MfxBasicGraph* set, int floor);
		MfxReturn RemoveItem(MfxBasicGraph* set);

		MfxReturn NextItem();
		MfxReturn GetItemObject(MfxBasicGraph** ret);

	public:
		MfxReturn Draw();

		MfxReturn SetDC(HDC set);
		MfxReturn GetDC(HDC* ret);

		MfxReturn SetRenderTarget(ID2D1RenderTarget* set);
		MfxReturn GetRenderTarget(ID2D1RenderTarget** ret);

		MfxReturn SetRect(GdipRect set);
		MfxReturn SetSize(GdipSize set);
		MfxReturn SetPoint(GdipPoint set);
		
		MfxReturn GetRect(GdipRect* ret);
		MfxReturn GetSize(GdipSize* ret);
		MfxReturn GetPoint(GdipPoint* ret);

		MfxReturn SetCollisionBlock(GdipSize set);
		MfxReturn CollisionWith(MfxBasicGraph* set, bool* ret);
	};
}

/* ———————————————————————————————————————————— */
/* ———————————————————————————————————————————— */
/* ———————————————————————————————————————————— */

//MfxImage
namespace MicroFlakeX
{
	//支持两种绘制模式
	class MfxImage
		: public MfxBasicGraph
	{
		DEFINE_AUTOBASIC;
	protected:
		void MfxImageInitData();
	public:
		MfxImage();
		virtual ~MfxImage();
		void operator=(MfxImage& rhs);

		MfxReturn Clone(MfxImage** ret);
		MfxReturn Similar(MfxImage* set);
	protected:
		MfxDataFlag_Rect myRect; //图片区域
		MfxDataFlag_pGdipBitmap myBasicBitmap; //图片基准 - 缩放的时候均以这幅图片为基准
		MfxInterpolationMode_EN myImageQuality; //图片质量

		HDC myDC;
		GdipGraphics* myGraphics;
		GdipBitmap* myShowBitmap;
		GdipCachedBitmap* myCachedShowBitmap;

		GdipRegion* myBasicRegion,* myShowRegion;
		MfxDataFlag_Size myCollisionBlock;

		BOOL myResetRegionLock;
		BOOL myResetShowBitmapLock;
		BOOL myResetShowCachedBitmapLock;
	protected:
		void Mode_ClearDC();
		void Mode_ResetDC(HDC set);

	public:
		MfxReturn LockResetRegion();
		MfxReturn UnLockResetRegion();

		MfxReturn LockResetShowBitmap();
		MfxReturn UnLockResetShowBitmap();

		MfxReturn LockResetCachedShowBitmap();
		MfxReturn UnLockResetCachedShowBitmap();

		MfxReturn ResetRegion();
		MfxReturn ResetShowBitmap();
		MfxReturn ResetCachedShowBitmap();
	public:
		MfxReturn SetDC(HDC set);
		MfxReturn GetDC(HDC* get);
	public:
		MfxReturn FromFile(MfxStrW path);
		MfxReturn FromColor(GdipColor set);
		MfxReturn FromBitmap(GdipBitmap* set);

		MfxReturn GetShowBitmap(GdipBitmap** ret); //获取当前显示图片
		MfxReturn GetBasicBitmap(GdipBitmap** ret); //获取基础图片
		MfxReturn SetBasicBitmap(GdipBitmap* set);

		MfxReturn Draw();
		MfxReturn DrawBitmap(GdipGraphics* set); //绘制图片，参数为: GdipGraphics*

	public:
		MfxReturn SetQuality(MfxInterpolationMode_EN set); //设置图片插值质量

		MfxReturn SetRect(GdipRect set);
		MfxReturn SetSize(GdipSize set);
		MfxReturn SetPoint(GdipPoint set);

		MfxReturn CollisionWith(MfxBasicGraph* set, bool* ret);
		MfxReturn SetCollisionBlock(GdipSize set);

		MfxReturn CropSize(GdipColor set); //根据颜色裁剪图片，选中的颜色将会被裁剪
		MfxReturn ChangeColor(GdipColor oldColor, GdipColor newColor); //更换颜色，第一个参数是oldcolor，第二个参数是newcolor

	public:
		MfxReturn GetQuality(MfxInterpolationMode_EN* ret);

		MfxReturn GetRegion(GdipRegion** ret);
		MfxReturn GetRegionBlock(GdipSize* ret);

		MfxReturn GetRect(GdipRect* ret);
		MfxReturn GetSize(GdipSize* ret);
		MfxReturn GetPoint(GdipPoint* ret);
	};
}

//MfxWorld
namespace MicroFlakeX
{
	//支持两种绘制模式
	class MfxWords
		: public MfxBasicGraph
	{
		DEFINE_AUTOBASIC;
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
		GdipGraphics* myGraphics;
		GdipGraphicsPath* myGraphicsPath;

		MfxDataFlag_Rect myRect; //文本框位置
		MfxStrW myText;
		MfxWorlds_Type myType; //文字类型 - 使用全局参数
		GdipFontFamily* myFontFamily; //文字家族
		GdipStringFormat* myStringFormat; //布局信息

		GdipPen* myFramePen;
		GdipBrush* myBackBrush;
		GdipBrush* myTextBrush;

		GdipRect myTextRect; //最终文字的位置
		GdipPen* myTextRectPen; //用来包裹文字的边框笔

		MfxDataFlag_pGdipBitmap myShowBitmap;
		GdipGraphics* myShowGraphics;
		GdipCachedBitmap* myCachedShowBitmap;

		GdipRegion* myBasicRegion, * myShowRegion;
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

		MfxReturn GetShowBitmap(GdipBitmap** ret); //获取当前显示图片

		MfxReturn Draw();
		MfxReturn DrawBitmap(GdipGraphics* set);

	public:
		MfxReturn SetText(MfxStrW set);
		MfxReturn GetText(MfxStrW* ret);

		MfxReturn SetStringFormat(GdipStringFormat* set); //设置文字格式
		MfxReturn GetStringFormat(GdipStringFormat** ret);
		/* ———————————————————————————————————————————— */
	public:
		MfxReturn SetType(MfxWorlds_Type set);

		MfxReturn SetFontName(MfxStrW set); //设置字体

		MfxReturn SetTextXY(MfxWords_TextXY set); //设置文字对齐
		MfxReturn SetShowStyle(MfxWords_ShowStyle set);
		MfxReturn SetFontStyle(MfxFontStyle set);
		MfxReturn SetSmoothingMode(MfxSmoothingMode_EN set);

		MfxReturn SetTextColor(GdipColor set);
		MfxReturn SetTextSize_em(MfxPenWidth set); //设置字体大小

		MfxReturn SetFrameColor(GdipColor set);
		MfxReturn SetFramePenWidth(MfxPenWidth set); //设置边框宽度

		MfxReturn SetBackColor(GdipColor set);

	public:
		MfxReturn GetType(MfxWorlds_Type* ret);

		MfxReturn GetFontName(MfxStrW* ret); //设置字体

		MfxReturn GetTextXY(MfxWords_TextXY* ret); //设置文字对齐
		MfxReturn GetShowStyle(MfxWords_ShowStyle* ret);
		MfxReturn GetFontStyle(MfxFontStyle* ret);
		MfxReturn GetSmoothingMode(MfxSmoothingMode_EN* ret);

		MfxReturn GetTextColor(GdipColor* ret);
		MfxReturn GetTextSize_em(MfxPenWidth* ret); //设置字体大小

		MfxReturn GetFrameColor(GdipColor* ret);
		MfxReturn GetFramePenWidth(MfxPenWidth* ret); //设置边框宽度

		MfxReturn GetBackColor(GdipColor* ret);
		/* ———————————————————————————————————————————— */
	public:
		MfxReturn SetRect(GdipRect set);
		MfxReturn SetSize(GdipSize set);
		MfxReturn SetPoint(GdipPoint set);

		MfxReturn SetCollisionBlock(GdipSize set);
		MfxReturn CollisionWith(MfxBasicGraph* set, bool* ret);

		MfxReturn SetFramePen(GdipPen* set);
		MfxReturn SetBackBrush(GdipBrush* set);
		MfxReturn SetTextBrush(GdipBrush* set);

	public:
		MfxReturn GetRect(GdipRect* ret);
		MfxReturn GetSize(GdipSize* ret);
		MfxReturn GetPoint(GdipPoint* ret);

		MfxReturn GetRegion(GdipRegion** ret);
		MfxReturn GetRegionBlock(GdipSize* ret);

		MfxReturn GetFramePen(GdipPen** ret);
		MfxReturn GetBackBrush(GdipBrush** ret);
		MfxReturn GetTextBrush(GdipBrush** ret);
		/* ———————————————————————————————————————————— */
	};
}

namespace MicroFlakeX
{
	class MfxTexture
		: public MfxBasicGraph
	{
		DEFINE_AUTOBASIC;
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