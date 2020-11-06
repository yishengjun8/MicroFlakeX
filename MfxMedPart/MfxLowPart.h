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

//extern "C" {

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

		typedef unsigned int MFXWORDS_SHOW_TYPE;/* 文字框显示方式 */
		enum MFXWORDS_SHOW_TYPE_ENUM/* 文字框显示方式(将你希望的枚举用|连接起来)-枚举 */
		{
			MFXWORDS_SHOW_TYPE_NULL = 0x0000,	//仅显示文字
			MFXWORDS_SHOW_TYPE_FILL = 0x0001,	//填充背景
			MFXWORDS_SHOW_TYPE_LINE = 0x0002	//填充边框
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
		/**/
		MFX_LOWPART_IMPORT BOOL MfxFunc_CheckIntersectsWith(MfxImage* a, MfxImage* b);
		MFX_LOWPART_IMPORT BOOL MfxFunc_CheckIntersectsWith(MfxImage* a, MfxWords* b);
		MFX_LOWPART_IMPORT BOOL MfxFunc_CheckIntersectsWith(MfxWords* a, MfxWords* b);
		/**/

		/* 根据给定的指针，确定b是否在a内部 */
		/**/
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
		public:
			/* 默认加载一张大小为60*60的无色图片 */
			MfxImage(Gdiplus::Graphics* myGraphics);
			~MfxImage();

			/* 克隆一份崭新的MfxImage，可以理解为深拷贝 */
			MfxImage* Clone();
			/* 获取Bitmap的克隆版，需要释放 */
			Gdiplus::Bitmap* GetBitmapClone();

		protected:
			Gdiplus::Graphics* myGraphics;

			Gdiplus::Rect myRect;
			Gdiplus::Bitmap* myBitmap;
			Gdiplus::CachedBitmap* myBitmapQuick;

			MFXIMAGE_QUALITY myQuality;/* 图片缩放质量-默认为“MFXIMAGE_QUALITY_NORMAL” */

		public:
			/* 从文件加载图片-图片大小会重置为这张图片大小 */
			Gdiplus::Status LoadFromFile(WCHAR* iPath);
			/* 从Bitmap加载图片-图片大小会重置为这张图片的大小 */
			Gdiplus::Status LoadFromBitmap(Gdiplus::Bitmap* iBitmap);
			/* 加载纯色图片-不重置图片大小 */
			Gdiplus::Status LoadPureColor(Gdiplus::Color fillColor = Gdiplus::Color(0, 0, 0, 0));

			/* 修改图片缩放质量-返回修改前的质量 */
			MFXIMAGE_QUALITY SetImageQuality(MFXIMAGE_QUALITY iQuality = MFXIMAGE_QUALITY_NORMAL);
			/* 获取当前图片缩放质量 */
			MFXIMAGE_QUALITY GetImageQuality();

			/* 修改图片大小-返回修改前的图片大小 */
			Gdiplus::Size SetImageSize(Gdiplus::Size iSize);
			/* 获取当前图片大小 */
			Gdiplus::Size GetImageSize();

			/* 修改图片位置-返回修改前位置 */
			Gdiplus::Point SetImagePoint(Gdiplus::Point iPoint);
			/* 获取当前图片位置 */
			Gdiplus::Point GetImagePoint();

			/* 获取当前图片的Rect */
			Gdiplus::Rect GetImageRect();

			/* 判断一个点是否在图片内，是则返回true，否则返回false */
			BOOL Contains(Gdiplus::Point ifPoint);

			/* 偏移图片坐标-返回偏移后的坐标 */
			Gdiplus::Point OffsetImagePoint(Gdiplus::Point iPoint);
			/* 偏移图片大小-返回偏移后的大小(iSize+mySize) */
			Gdiplus::Size OffsetImageSize(Gdiplus::Size iSize);

			/* 高速绘制图片 */
			Gdiplus::Status Draw();
		};

		class MfxImageList/* 图集类-可存储多张MfxImage，并对它们进行统一操作 */
		{
		public:
			/* 选择本图集的绘画类 - 删除图集类的时候，会自动调用ClearImage()做收尾工作 */
			MfxImageList(Gdiplus::Graphics* myGraphics);
			~MfxImageList();
		protected:
			Gdiplus::Graphics* myGraphics;

			int mySelectImageNum;/* 当前选中的图片 */
			Gdiplus::Rect myRect;/* 图片位置和大小 */
			MFXIMAGEE_LIST myImageList;/* 图片列表 */
			MFXIMAGE_QUALITY myQuality;/* 图片缩放质量-默认为“MFXIMAGE_QUALITY_NORMAL” */

		public:
			/* 通过图片类-添加一张照片，第一张的序号为1，以此类推 */
			BOOL ListAddImage(MfxImage* addImage);

			/* 清空图集-但是不删除图集内容 */
			BOOL ListClearImage();
			/* 清空图集-并且删除图集内容 */
			BOOL ListDeleteImage();

			/* 设定当前图集中被选中的图片 - 返回上一张图片 */
			int ListSetSelectImageNum(int seNum);
			/* 获取当前图集中被选中的图片序号 */
			int ListGetSelectImageNum();

			/* 获取图集内文件总数 */
			int ListGetImageTotal();
			/* 下一张图片 */
			int ListNextImage();

			/* 修改图集缩放质量-返回修改前的质量 */
			MFXIMAGE_QUALITY SetImageQuality(MFXIMAGE_QUALITY iQuality = MFXIMAGE_QUALITY_NORMAL);
			/* 获取当前图集缩放质量 */
			MFXIMAGE_QUALITY GetImageQuality();

			/* 修改图集大小-返回修改前的图集大小 */
			Gdiplus::Size SetImageSize(Gdiplus::Size iSize);
			/* 获取当前图集大小 */
			Gdiplus::Size GetImageSize();

			/* 修改图集位置-返回修改前位置 */
			Gdiplus::Point SetImagePoint(Gdiplus::Point iPoint);
			/* 获取当前图集位置 */
			Gdiplus::Point GetImagePoint();

			/* 获取当前图集的Rect */
			Gdiplus::Rect GetImageRect();

			/* 判断一个点是否在图集范围内，是则返回true，否则返回false */
			BOOL Contains(Gdiplus::Point ifPoint);

			/* 偏移图集坐标-返回偏移后的坐标 */
			Gdiplus::Point OffsetImagePoint(Gdiplus::Point iPoint);
			/* 偏移图集大小-返回偏移后的大小(iSize+mySize) */
			Gdiplus::Size OffsetImageSize(Gdiplus::Size iSize);

			/* 高速绘制图集中被选中的图片 */
			Gdiplus::Status Draw();
		};

		class MfxWords/* 文字框类 - 在一个方框内显示文字 */
		{
		public:
			MfxWords(Gdiplus::Graphics* myGraphics);
			~MfxWords();
		protected:
			std::wstring		words;			/* 文字框内容 */
			std::wstring		wordsFontName;	/* 字体 */
			int					wordsSize;		/* 文字大小 */
			Gdiplus::RectF		wordsRectF;		/* 位置-大小 */
			Gdiplus::PointF		wordsOffset;	/* 文字偏移 */
			MFXWORDS_FORMAT	wordsFormatXY;	/* 文字排版方法 - 暂时无法实现Y轴的排版 */
			int					lineSize;		/* 边框粗细 */

		public:
			/* 设定全局字体-返回值为上一个字体-更改全局字体不会影响已经创建的实例 */
			static std::wstring SetGlobalFont(std::wstring g_wFont);
			static std::wstring GetGlobalFont();

			/* 设定全局大小-返回值为上一个大小 */
			static int SetGlobalWordsSize(int g_wSize);
			static int GetGlobalWordsSize();

			/* 设定全局边框粗细-返回值为上一个粗细 */
			static int SetGlobalLineSize(int g_lSize);
			static int GetGlobalLineSize();

		protected:
			static std::wstring	Global_FontName;	/* 全局字体 */
			static int			Global_WordsSize;	/* 全局文字大小 */
			static int			Global_LineSize;	/* 全局文字边框粗细 */

		public:
			/* 设置显示的文字-返回值为上一个显示的文字 */
			std::wstring SetWords(std::wstring wStr);
			std::wstring GetWords();

			/* 设置字体-返回上一个字体 - 失败返回error */
			std::wstring SetWordsFont(std::wstring wFont);
			std::wstring GetWordsFont();

			/* 设置字体大小-返回修改前的字体大小 - 失败返回-1 */
			int SetWordsSize(int wSize);
			int GetWordsSize();

			/* 设置边框粗细-返回修改前的边框粗细 - 失败返回-1 */
			int SetLineSize(int lSize);
			int GetLineSize();

			/* 设置文字框位置-返回修改前位置 - 失败返回-1 */
			Gdiplus::PointF SetWordsPointF(Gdiplus::PointF wPointF);
			Gdiplus::PointF GetWordsPointF();

			/* 设置文字框大小-返回修改前大小 - 失败返回-1 */
			Gdiplus::SizeF SetWordsSizeF(Gdiplus::SizeF wSizeF);
			Gdiplus::SizeF GetWordsSizeF();

			/* 获取当前文本框的RectF */
			Gdiplus::RectF GetWordsRectF();

			/* 设置文字框内文字基于边框的偏移-返回修改前的文字偏移量 */
			Gdiplus::PointF SetWordsOffset(Gdiplus::PointF wOffset);
			Gdiplus::PointF GetWordsOffset();

			/* 设置文字排版方式(将排版方式用|连接起来)-返回值为上一个排版方式 */
			MFXWORDS_FORMAT SetWordsFormat(MFXWORDS_FORMAT wFormat = MFXWORDS_FORMATX_NEAR | MFXWORDS_FORMATY_NEAR);
			MFXWORDS_FORMAT GetWordsFormat();

			/* 设置文字颜色-返回修改前的颜色 */
			Gdiplus::Color SetWordsColor(Gdiplus::Color wColor);
			Gdiplus::Color GetWordsColor();

			/* 设置文字框边框颜色-返回值为上一个颜色 */
			Gdiplus::Color SetLineColor(Gdiplus::Color lColor);
			Gdiplus::Color GetLineColor();

			/* 设置文字框背景颜色-返回值为上一个颜色 */
			Gdiplus::Color SetBackColor(Gdiplus::Color bColor);
			Gdiplus::Color GetBackColor();

			/* 判断一个点是否在文字框内，是则返回true，否则返回false */
			BOOL Contains(Gdiplus::PointF ifPointF);

			/* 偏移文本框坐标-返回偏移后的坐标 */
			Gdiplus::PointF OffsetWordsPointF(Gdiplus::PointF wPointF);
			/* 缩放文本框-返回缩放后的大小(iSize+mySize) */
			Gdiplus::SizeF OffsetWordsSizeF(Gdiplus::SizeF wSizeF);

			/* 自选的绘制模式-将需要的“MFX_TYPE”样式用“|”符号连接起来 */
			Gdiplus::Status Draw(MFXWORDS_SHOW_TYPE wType = MFXWORDS_SHOW_TYPE_NULL | MFXWORDS_SHOW_TYPE_FILL);

		protected:
			Gdiplus::Graphics* myGraphics;

			Gdiplus::Font* wordsFont;
			Gdiplus::StringFormat wordsFormat;

			Gdiplus::Color			wordsColor;//文字颜色
			Gdiplus::Color			lineColor;//边框颜色
			Gdiplus::Color			backColor;//背景颜色

			Gdiplus::SolidBrush* worldsBrush;//文字画刷
			Gdiplus::Pen* linePen;//边框画笔
			Gdiplus::SolidBrush* backBrush;//背景画刷
		};
	}
//};