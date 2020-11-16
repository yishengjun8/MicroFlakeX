#pragma once

#ifdef MFX_LOWPART_BUILDING
#define MFX_LOWPART_IMPORT __declspec(dllexport)
#else
#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <gdiplus.h>
#pragma comment(lib,"gdiplus.lib")
#define MFX_LOWPART_IMPORT __declspec(dllimport)
#endif

/* 各种类型声明 */

/* 声音？ */


namespace MicroFlakeX
{
	class MFX_LOWPART_IMPORT MfxWords;
	class MFX_LOWPART_IMPORT MfxImage;
	class MFX_LOWPART_IMPORT MfxImageList;

	typedef std::vector<MfxImage*> MFXIMAGEE_LIST;/* 图片类线性表 */
	typedef MFXIMAGEE_LIST::iterator MFXIMAGEE_LIST_ITERA;

	typedef unsigned int MFXIMAGE_QUALITY;/* 图片缩放质量 */
	enum MFXIMAGE_QUALITY_ENUM/* 图片缩放质量-枚举 */
	{
		MFXIMAGE_QUALITY_NORMAL = Gdiplus::InterpolationModeDefault, //普通缩放-默认值
		MFXIMAGE_QUALITY_LOW = Gdiplus::InterpolationModeNearestNeighbor, //最邻近插值法
		MFXIMAGE_QUALITY_MEDIUM = Gdiplus::InterpolationModeHighQualityBilinear, //高质量双线性插值法
		MFXIMAGE_QUALITY_HIGHT = Gdiplus::InterpolationModeHighQualityBicubic //高质量双三插值
	};

	typedef std::vector<MfxWords> MFXWORDS_LIST; /* 文字类线性表 */
	typedef MFXWORDS_LIST::iterator MFXWORDS_LIST_ITERA;

	typedef unsigned int MFXWORDS_DRAWTYPE;/* 文字框显示方式 */
	enum MFXWORDS_DRAWTYPE_ENUM/* 文字框显示方式(将你希望的枚举用|连接起来)-枚举 */
	{
		MFXWORDS_DRAWTYPE_NULL = 0x0000,	//仅显示文字
		MFXWORDS_DRAWTYPE_FILL = 0x0001,	//填充背景
		MFXWORDS_DRAWTYPE_LINE = 0x0002	//填充边框
	};

	typedef unsigned int MFXWORDS_FORMAT;/* 文字排版方式 */
	enum MFXWORDS_FORMAT_ENUM/* 文字排版方式(将你希望的枚举用|连接起来)-枚举 */
	{
		MFXWORDS_FORMATX_NEAR = 0x0000,	//X轴靠左排版
		MFXWORDS_FORMATX_CENTER = 0x0001,	//X轴居中排版
		MFXWORDS_FORMATX_FAR = 0x0002,		//X轴靠右排版
		MFXWORDS_FORMATY_NEAR = 0x0000,	//Y轴靠上排版
		MFXWORDS_FORMATY_CENTER = 0x0010,	//Y轴居中排版
		MFXWORDS_FORMATY_FAR = 0x0020		//Y轴靠下排版
	};
}

namespace MicroFlakeX
{
	//MfxSafeType<int> a, b;
}




/* 重要的导出函数 */
namespace MicroFlakeX
{
	/* 根据Wnd句柄获取与其相对应的Dc句柄 */
	MFX_LOWPART_IMPORT HDC MfxFunc_GethDC(HWND hWnd);

	/* 根据hDc和给定的大小，创建一个指定大小的兼容Dc-自动载入兼容画布 */
	MFX_LOWPART_IMPORT HDC MfxFunc_GetComhDC(HDC hDc, Gdiplus::Size dcSize);

	/* 快速刷新hDc - true = 黑色； false = 白色 */
	MFX_LOWPART_IMPORT bool MfxFunc_SethDCBack(HDC hDc, Gdiplus::Size dcSize, bool bColor = true);

	/* 获取一个指向该类型的Graphics指针 */
	MFX_LOWPART_IMPORT Gdiplus::Graphics* MfxFunc_GetGraphics(HDC hDc);
	MFX_LOWPART_IMPORT Gdiplus::Graphics* MfxFunc_GetGraphics(Gdiplus::Bitmap* bitmap);//

	/* 根据给定的指针，确定两个类是否有相交 */
	/*
	MFX_LOWPART_IMPORT BOOL MfxFunc_CheckIntersectsWith(MfxImage* a, MfxImage* b);
	MFX_LOWPART_IMPORT BOOL MfxFunc_CheckIntersectsWith(MfxImage* a, MfxWords* b);
	MFX_LOWPART_IMPORT BOOL MfxFunc_CheckIntersectsWith(MfxWords* a, MfxWords* b);
	/**/

	/* 根据给定的指针，确定b是否在a内部 */
	/*
	MFX_LOWPART_IMPORT BOOL MfxFunc_CheckContains(MfxImage* a, MfxImage* b);
	MFX_LOWPART_IMPORT BOOL MfxFunc_CheckContains(MfxImage* a, MfxWords* b);
	MFX_LOWPART_IMPORT BOOL MfxFunc_CheckContains(MfxWords* a, MfxImage* b);
	MFX_LOWPART_IMPORT BOOL MfxFunc_CheckContains(MfxWords* a, MfxWords* b);
	/**/
}


/* 类声明 */
namespace MicroFlakeX
{
	class MfxImage/* 图片类-可存储单张图片，可以配合图集使用，成为图集的子集 */
	{
	protected:
		//void MfxImageInitData();
	public:
		MfxImage(Gdiplus::Graphics* set, 
			Gdiplus::Rect value = Gdiplus::Rect(0, 0, 80, 80));

		MfxImage(Gdiplus::Graphics* set, WCHAR* value);

		MfxImage(Gdiplus::Graphics* set, 
			Gdiplus::Color valC = Gdiplus::Color::DarkBlue,
			Gdiplus::Rect valR = Gdiplus::Rect(0, 0, 80, 80));

		~MfxImage();
		MfxImage* Clone();
		Gdiplus::Bitmap* GetBitmap();

	protected:
		Gdiplus::Graphics* myGraphics;
	public:
		Gdiplus::Status SetGraphics(Gdiplus::Graphics* set);
		/* 高速绘制图片 */
		Gdiplus::Status Draw();

	protected:
		Gdiplus::Rect myRect;
		Gdiplus::Bitmap* myMainBitmap;
		Gdiplus::Bitmap* myBitmap;
		Gdiplus::CachedBitmap* myBitmapQuick;
		MFXIMAGE_QUALITY myQuality;
	public:
		/* 从文件加载图片-图片大小会重置为这张图片大小 */
		Gdiplus::Status LoadFromFile(WCHAR* set);
		/* 从Bitmap加载图片-图片大小会重置为这张图片的大小 */
		Gdiplus::Status LoadFromBitmap(Gdiplus::Bitmap* set);
		/* 加载纯色图片-不重置图片大小 */
		Gdiplus::Status LoadPureColor(Gdiplus::Color set = Gdiplus::Color(0, 0, 0, 0));

		/* 修改图片缩放质量-返回修改前的质量 */
		MFXIMAGE_QUALITY SetImageQuality(MFXIMAGE_QUALITY set = MFXIMAGE_QUALITY_NORMAL);
		MFXIMAGE_QUALITY GetImageQuality();

		/* 修改图片大小-返回修改前的图片大小 */
		Gdiplus::Size SetImageSize(Gdiplus::Size set);
		Gdiplus::Size GetImageSize();

		/* 修改图片位置-返回修改前位置 */
		Gdiplus::Point SetImagePoint(Gdiplus::Point set);
		Gdiplus::Point GetImagePoint();

		/* 修改图片Rect，返回图片修改前的Rect */
		Gdiplus::Rect SetImageRect(Gdiplus::Rect set);
		Gdiplus::Rect GetImageRect();

		/* 判断一个点是否在图片内，是则返回true，否则返回false */
		BOOL Contains(Gdiplus::Point set);

		/* 偏移图片坐标-返回偏移后的坐标 */
		Gdiplus::Point OffsetImagePoint(Gdiplus::Point set);
		/* 偏移图片大小-返回偏移后的大小(iSize+mySize) */
		Gdiplus::Size OffsetImageSize(Gdiplus::Size set);
	};

	class MfxImageList/* 图集类-可存储多张MfxImage，并对它们进行统一操作 */
	{
	public:
		/* 选择本图集的绘画类 - 删除图集类的时候，会自动调用ClearImage()做收尾工作 */
		MfxImageList(Gdiplus::Graphics* set);
		~MfxImageList();
	protected:
		Gdiplus::Graphics* myGraphics;

		int mySelectImageNum;/* 当前选中的图片 */
		Gdiplus::Rect myRect;/* 图片位置和大小 */
		MFXIMAGEE_LIST myImageList;/* 图片列表 */
		MFXIMAGE_QUALITY myQuality;/* 图片缩放质量-默认为“MFXIMAGE_QUALITY_NORMAL” */

	public:
		/* 通过图片类-添加一张照片，第一张的序号为1，以此类推 */
		BOOL ListAddImage(MfxImage* set);

		/* 清空图集-但是不删除图集内容 */
		BOOL ListClearImage();
		/* 清空图集-并且删除图集内容 */
		BOOL ListDeleteImage();

		/* 设定当前图集中被选中的图片 - 返回上一张图片 */
		int ListSetSelectImageNum(int set);
		/* 获取当前图集中被选中的图片序号 */
		int ListGetSelectImageNum();

		/* 获取图集内文件总数 */
		int ListGetImageTotal();
		/* 下一张图片 */
		int ListNextImage();

		/* 修改图集缩放质量-返回修改前的质量 */
		MFXIMAGE_QUALITY SetImageQuality(MFXIMAGE_QUALITY set = MFXIMAGE_QUALITY_NORMAL);
		MFXIMAGE_QUALITY GetImageQuality();

		/* 修改图集大小-返回修改前的图集大小 */
		Gdiplus::Size SetImageSize(Gdiplus::Size set);
		Gdiplus::Size GetImageSize();

		/* 修改图集位置-返回修改前位置 */
		Gdiplus::Point SetImagePoint(Gdiplus::Point set);
		Gdiplus::Point GetImagePoint();

		/* 获取当前图集的Rect */
		Gdiplus::Rect GetImageRect();

		/* 判断一个点是否在图集范围内，是则返回true，否则返回false */
		BOOL Contains(Gdiplus::Point set);

		/* 偏移图集坐标-返回偏移后的坐标 */
		Gdiplus::Point OffsetImagePoint(Gdiplus::Point set);
		/* 偏移图集大小-返回偏移后的大小(iSize+mySize) */
		Gdiplus::Size OffsetImageSize(Gdiplus::Size set);

		/* 高速绘制图集中被选中的图片 */
		Gdiplus::Status Draw();
	};





	class MfxWords/* 文字类 - 在一个方框内显示文字 */
	{
	public:
		MfxWords(Gdiplus::Graphics* myGraphics);
		~MfxWords();
		Gdiplus::Status SetGraphics(Gdiplus::Graphics* set);

	protected:
		static std::wstring	Global_FontName;	/* 全局字体 */
		static int			Global_FontSize;	/* 全局文字大小 */
		static int			Global_LineSize;	/* 全局文字边框粗细 */
	public:
		static std::wstring SetGlobalFont(std::wstring set);
		static std::wstring GetGlobalFont();

		static int SetGlobalFontSize(int set);
		static int GetGlobalFontSize();

		static int SetGlobalLineSize(int set);
		static int GetGlobalLineSize();

	protected:
		std::wstring		myWords;		/* 文字框内容 */
		std::wstring		myFontName;		/* 字体 */
		int					myFontSize;		/* 文字大小 */
		Gdiplus::Rect		myRect;			/* 位置-大小 */
		Gdiplus::Point		myFontOffset;	/* 文字偏移 */
		MFXWORDS_FORMAT		myFormatXY;		/* 文字排版方法 - 暂时无法实现Y轴的排版 */
		int					myLineSize;		/* 边框粗细 */
	public:
		std::wstring SetWords(std::wstring set);
		std::wstring GetWords();

		std::wstring SetFont(std::wstring set);
		std::wstring GetFont();

		/* 设置字体大小-返回修改前的字体大小 - 失败返回-1 */
		int SetFontSize(int set);
		int GetFontSize();

		/* 设置边框粗细-返回修改前的边框粗细 - 失败返回-1 */
		int SetLineSize(int set);
		int GetLineSize();

		/* 设置文字框位置-返回修改前位置 - 失败返回-1 */
		Gdiplus::Point SetPoint(Gdiplus::Point set);
		Gdiplus::Point GetPoint();

		/* 设置文字框大小-返回修改前大小 - 失败返回-1 */
		Gdiplus::Size SetSize(Gdiplus::Size set);
		Gdiplus::Size GetSize();

		/* 设置文字框Rect-返回修改前大小 - 失败返回-1 */
		Gdiplus::Rect SetRect(Gdiplus::Rect set);
		Gdiplus::Rect GetRect();

		/* 设置文字框内文字基于边框的偏移-返回修改前的文字偏移量 */
		Gdiplus::Point SetFontOffset(Gdiplus::Point set);
		Gdiplus::Point GetFontOffset();

		/* 设置文字排版方式(将排版方式用|连接起来)-返回值为上一个排版方式 */
		MFXWORDS_FORMAT SetFormat(MFXWORDS_FORMAT set = MFXWORDS_FORMATX_NEAR | MFXWORDS_FORMATY_NEAR);
		MFXWORDS_FORMAT GetFormat();

		/* 设置文字颜色-返回修改前的颜色 */
		Gdiplus::Color SetFontColor(Gdiplus::Color set);
		Gdiplus::Color GetFontColor();

		/* 设置文字框边框颜色-返回值为上一个颜色 */
		Gdiplus::Color SetLineColor(Gdiplus::Color set);
		Gdiplus::Color GetLineColor();

		/* 设置文字框背景颜色-返回值为上一个颜色 */
		Gdiplus::Color SetBackColor(Gdiplus::Color set);
		Gdiplus::Color GetBackColor();

		/* 判断一个点是否在文字框内，是则返回true，否则返回false */
		BOOL Contains(Gdiplus::Point set);

		/* 偏移文本框坐标-返回偏移后的坐标 */
		Gdiplus::Point OffsetPoint(Gdiplus::Point set);
		/* 缩放文本框-返回缩放后的大小(iSize+mySize) */
		Gdiplus::Size OffsetSize(Gdiplus::Size set);

		/* 自选的绘制模式-将需要的“MFX_TYPE”样式用“|”符号连接起来 */
		Gdiplus::Status Draw(MFXWORDS_DRAWTYPE set = MFXWORDS_DRAWTYPE_NULL);

	protected:
		Gdiplus::Graphics* myGraphics;

		Gdiplus::Font* wordsFont;
		Gdiplus::StringFormat wordsFormat;

		Gdiplus::Color			wordsColor;//文字颜色
		Gdiplus::Color			lineColor;//边框颜色
		Gdiplus::Color			backColor;//背景颜色

		Gdiplus::SolidBrush* worldsBrush;//文字画刷
		Gdiplus::Pen* linePen;			//边框画笔
		Gdiplus::SolidBrush* backBrush;//背景画刷
	};
}