#pragma once


/**************************************************************
*	UTF-8 - win - x86
*
*   版本：1.01       作者：yishengjun8
*
*
*	MfxType.h	提供了	MicroFlakeX	的基础类型对象
* 
*   MfxType的子类，都重载了拷贝构造函数，力图要求拷贝时速度最快
*       基于此，MfxType的子类可以在程序中当成基本类型使用，因为
*       它们的拷贝开销实在是很小。
* 
**************************************************************/

#ifdef MFXDLL_BUILDING
#define MFX_PORT __declspec(dllexport)
#else
#define MFX_PORT __declspec(dllimport)
#pragma comment(lib, "MfxType.lib")
#include "MfxBase.h"

/* 数学库 */
#include <cmath>
/**/

/* STL模板库 */
/**/

/* Direct2D1 */
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <dwmapi.h>
/**/

/* time库 */
#include <ctime>
/**/

#include "Gdiplus.h"
#pragma comment(lib, "Gdiplus.lib")

#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "DWrite.lib")
#endif

namespace MicroFlakeX
{
    /**************************************************************
    *
    *
    *
    ***************************************************************/
    class MFX_PORT MfxType;

    class MFX_PORT MfxRect;
    class MFX_PORT MfxSize;
    class MFX_PORT MfxPoint;

    class MFX_PORT MfxColor;

    class MFX_PORT MfxMove;
}

namespace MicroFlakeX
{
    class MfxType :
        public MfxBase
    {
        MfxObject;
    public:
        MfxReturn Clone(MfxBase** ret);

        MfxBase& operator=(MfxBase& rhs);

        bool operator==(MfxBase& rhs);
    };
}

namespace MicroFlakeX
{
    class MfxRect :
        public MfxType
    {
        MfxObject;
    public:
        MfxRect();
        MfxRect(MfxBase& set);

        MfxRect(MfxRect& set);
        MfxRect(MfxRect&& set);

        MfxRect(MfxSize& set);
        MfxRect(MfxSize&& set);

        MfxRect(MfxPoint& set);
        MfxRect(MfxPoint&& set);

        MfxRect(LONG setX, LONG setY, LONG setWidth, LONG setHeight);

        ~MfxRect();

    public:
        MfxReturn Clone(MfxBase** ret);

        MfxBase& operator=(MfxBase& rhs);

        MfxRect& operator=(MfxRect& rhs);
        MfxRect& operator=(MfxRect&& rhs);

        MfxRect& operator=(MfxSize& rhs);
        MfxRect& operator=(MfxSize&& rhs);

        MfxRect& operator=(MfxPoint& rhs);
        MfxRect& operator=(MfxPoint&& rhs);

    public:
        bool operator==(MfxBase& rhs);

        bool operator==(MfxRect& rhs);
        bool operator==(MfxRect&& rhs);

    public:
        MfxReturn Reset(LONG setX, LONG setY, LONG setWidth, LONG setHeight);
    
    public:
        MfxReturn GetRect(MfxRect* ret);
        MfxReturn GetSize(MfxSize* ret);
        MfxReturn GetPoint(MfxPoint* ret);

        MfxReturn GetRECT(RECT* ret);
        MfxReturn GetSIZE(SIZE* ret);
        MfxReturn GetPOINT(POINT* ret);
      
        MfxReturn GetGdipRect(Gdiplus::Rect* ret);
        MfxReturn GetGdipSize(Gdiplus::Size* ret);
        MfxReturn GetGdipPoint(Gdiplus::Point* ret);

        MfxReturn GetGdipRectF(Gdiplus::RectF* ret);
        MfxReturn GetGdipSizeF(Gdiplus::SizeF* ret);
        MfxReturn GetGdipPointF(Gdiplus::PointF* ret);

        MfxReturn GetD2D1RectU(D2D1_RECT_U* ret);
        MfxReturn GetD2D1SizeU(D2D1_SIZE_U* ret);
        MfxReturn GetD2D1PointU(D2D1_POINT_2U* ret);

        MfxReturn GetD2D1RectF(D2D1_RECT_F* ret);
        MfxReturn GetD2D1SizeF(D2D1_SIZE_F* ret);
        MfxReturn GetD2D1PointF(D2D1_POINT_2F* ret);

    public:
        MfxReturn SetRect(MfxRect* set);
        MfxReturn SetSize(MfxSize* set);
        MfxReturn SetPoint(MfxPoint* set);

        MfxReturn SetRECT(RECT* set);
        MfxReturn SetSIZE(SIZE* set);
        MfxReturn SetPOINT(POINT* set);

        MfxReturn SetGdipRect(Gdiplus::Rect* set);
        MfxReturn SetGdipSize(Gdiplus::Size* set);
        MfxReturn SetGdipPoint(Gdiplus::Point* set);

        MfxReturn SetGdipRectF(Gdiplus::RectF* set);
        MfxReturn SetGdipSizeF(Gdiplus::SizeF* set);
        MfxReturn SetGdipPointF(Gdiplus::PointF* set);

        MfxReturn SetD2D1RectU(D2D1_RECT_U* set);
        MfxReturn SetD2D1SizeU(D2D1_SIZE_U* set);
        MfxReturn SetD2D1PointU(D2D1_POINT_2U* set);

        MfxReturn SetD2D1RectF(D2D1_RECT_F* set);
        MfxReturn SetD2D1SizeF(D2D1_SIZE_F* set);
        MfxReturn SetD2D1PointF(D2D1_POINT_2F* set);

    public:
        MfxReturn GetX(LONG* ret);
        MfxReturn GetY(LONG* ret);
        MfxReturn GetWidth(LONG* ret);
        MfxReturn GetHeight(LONG* ret);

        MfxReturn GetTop(LONG* ret);
        MfxReturn GetLeft(LONG* ret);
        MfxReturn GetRight(LONG* ret);
        MfxReturn GetBottom(LONG* ret);

    public:
        MfxReturn SetX(LONG set);
        MfxReturn SetY(LONG set);
        MfxReturn SetWidth(LONG set);
        MfxReturn SetHeight(LONG set);

        MfxReturn SetTop(LONG set);
        MfxReturn SetLeft(LONG set);
        MfxReturn SetRight(LONG set);
        MfxReturn SetBottom(LONG set);

    public:
        /* 和 */
        MfxReturn Union(MfxRect* set, MfxRect* ret);
        MfxReturn Union_Widely(MfxBase* set, MfxRect* ret);

        /* 差 */
        MfxReturn Except(MfxRect* set, MfxRect* ret);
        MfxReturn Except_Widely(MfxBase* set, MfxRect* ret);

        /* 交 */
        MfxReturn Intersect(MfxRect* set, MfxRect* ret);
        MfxReturn Intersect_Widely(MfxBase* set, MfxRect* ret);

    public:
        /* 偏移 */
        MfxReturn Offset(LONG setX, LONG setY);

        /* 膨胀 */
        MfxReturn Inflate(LONG setX, LONG setY);

        /* 扩展系数 10 100 1000 倍 */

    public:
        /* 判断是否为空 */
        MfxReturn IsEmpty(bool* ret);

        /* 判断点是否在矩形内 */
        MfxReturn IsPointInside(MfxPoint* set, bool* ret);

    public:
        LONG myX;
        LONG myY;
        LONG myWidth;
        LONG myHeight;
    };
}

namespace MicroFlakeX
{
    class MfxSize
        : public MfxType
    {
        MfxObject;
    public:
        MfxSize();
        MfxSize(MfxBase& set);

        MfxSize(MfxRect& set);
        MfxSize(MfxRect&& set);

        MfxSize(MfxSize& set);
        MfxSize(MfxSize&& set);

        MfxSize(LONG setWidth, LONG setHeight);

        ~MfxSize();

    public:
        MfxReturn Clone(MfxBase** ret);

        MfxBase& operator=(MfxBase& rhs);

        MfxSize& operator=(MfxRect& rhs);
        MfxSize& operator=(MfxRect&& rhs);

        MfxSize& operator=(MfxSize& rhs);
        MfxSize& operator=(MfxSize&& rhs);

    public:
        bool operator==(MfxBase& rhs);

        bool operator==(MfxSize& rhs);
        bool operator==(MfxSize&& rhs);

    public:
        MfxReturn Reset(LONG setWidth, LONG setHeight);

    public:
        MfxReturn GetSize(MfxSize* ret);

        MfxReturn GetSIZE(SIZE* ret);

        MfxReturn GetGdipSize(Gdiplus::Size* ret);
        MfxReturn GetGdipSizeF(Gdiplus::SizeF* ret);

        MfxReturn GetD2D1SizeF(D2D1_SIZE_F* ret);
        MfxReturn GetD2D1SizeU(D2D1_SIZE_U* ret);

    public:
        MfxReturn SetSize(MfxSize* set);

        MfxReturn SetSIZE(SIZE* set);

        MfxReturn SetGdipSize(Gdiplus::Size* set);
        MfxReturn SetGdipSizeF(Gdiplus::SizeF* set);

        MfxReturn SetD2D1SizeF(D2D1_SIZE_F* set);
        MfxReturn SetD2D1SizeU(D2D1_SIZE_U* set);

    public:
        MfxReturn GetWidth(LONG* ret);
        MfxReturn GetHeight(LONG* ret);

    public:
        MfxReturn SetWidth(LONG set);
        MfxReturn SetHeight(LONG set);


    public:
        /* 膨胀 */
        MfxReturn Inflate(LONG setX, LONG setY);

    public:
        /* 判断是否为空 */
        MfxReturn IsEmpty(bool* ret);

    public:
        LONG myWidth;
        LONG myHeight;
    };
}


namespace MicroFlakeX
{
    class MfxPoint
        : public MfxType
    {
        MfxObject;
    public:
        MfxPoint();
        MfxPoint(MfxBase& set);

        MfxPoint(MfxRect& set);
        MfxPoint(MfxRect&& set);

        MfxPoint(MfxPoint& set);
        MfxPoint(MfxPoint&& set);

        MfxPoint(LONG setX, LONG setY);

        ~MfxPoint();

    public:
        MfxReturn Clone(MfxBase** ret);

        MfxBase& operator=(MfxBase& rhs);

        MfxPoint& operator=(MfxRect& rhs);
        MfxPoint& operator=(MfxRect&& rhs);

        MfxPoint& operator=(MfxPoint& rhs);
        MfxPoint& operator=(MfxPoint&& rhs);

    public:
        bool operator==(MfxBase& rhs);

        bool operator==(MfxPoint& rhs);
        bool operator==(MfxPoint&& rhs);

    public:
        MfxReturn Reset(LONG setX, LONG setY);

    public:
        MfxReturn GetPoint(MfxPoint* ret);

        MfxReturn GetPOINT(POINT* ret);

        MfxReturn GetGdipPoint(Gdiplus::Point* ret);
        MfxReturn GetGdipPointF(Gdiplus::PointF* ret);

        MfxReturn GetD2D1PointU(D2D1_POINT_2U* ret);
        MfxReturn GetD2D1PointF(D2D1_POINT_2F* ret);

    public:
        MfxReturn SetPoint(MfxPoint* set);

        MfxReturn SetPOINT(POINT* set);

        MfxReturn SetGdipPoint(Gdiplus::Point* set);
        MfxReturn SetGdipPointF(Gdiplus::PointF* set);

        MfxReturn SetD2D1PointU(D2D1_POINT_2U* set);
        MfxReturn SetD2D1PointF(D2D1_POINT_2F* set);

    public:
        MfxReturn GetX(LONG* ret);
        MfxReturn GetY(LONG* ret);

    public:
        MfxReturn SetX(LONG set);
        MfxReturn SetY(LONG set);

    public:
        /* 偏移 */
        MfxReturn Offset(LONG setX, LONG setY);
       
    public:
        LONG myX;
        LONG myY;
    };
}

namespace MicroFlakeX
{
    class MfxColor
        : public MfxType
    {
        MfxObject;
    public:
        MfxColor();
        MfxColor(MfxBase& set);

        MfxColor(MfxColor& set);
        MfxColor(MfxColor&& set);

        MfxColor(LONG setA, LONG setR, LONG setG, LONG setB);

        ~MfxColor();

    public:
        MfxReturn Clone(MfxBase** ret);

        MfxBase& operator=(MfxBase& rhs);

        MfxColor& operator=(MfxColor& rhs);
        MfxColor& operator=(MfxColor&& rhs);

    public:
        bool operator==(MfxBase& rhs);

        bool operator==(MfxColor& rhs);
        bool operator==(MfxColor&& rhs);

    public:
        MfxReturn Reset(LONG setA, LONG setR, LONG setG, LONG setB);

    public:
        MfxReturn GetPRGB(UINT32* ret);
        MfxReturn GetRGB(LONG* retA, UINT32* ret);

        MfxReturn GetD2D1ColorF(D2D1_COLOR_F* ret);

    public:
        MfxReturn SetPRGB(UINT32 set);
        MfxReturn SetRGB(LONG setA, UINT32 set);

        MfxReturn SetD2D1ColorF(D2D1_COLOR_F* set);

    public:
        MfxReturn GetA(LONG* ret);
        MfxReturn GetR(LONG* ret);
        MfxReturn GetG(LONG* ret);
        MfxReturn GetB(LONG* ret);

    public:
        MfxReturn SetA(LONG ret);
        MfxReturn SetR(LONG ret);
        MfxReturn SetG(LONG ret);
        MfxReturn SetB(LONG ret);


    public:
        LONG myA;
        LONG myR;
        LONG myG;
        LONG myB;
    };
}

namespace MicroFlakeX
{
    /* 等待补充 */
    class MfxMove
        : public MfxType
    {
        MfxObject;
    public:
        MfxMove();

        MfxMove(MfxPoint* setBegin, MfxPoint* setEnd, time_t time_ms);
        MfxMove(MfxPoint* setBegin, MfxPoint* setEnd, time_t timeBegin, time_t timeEnd);
        
        ~MfxMove();

        MfxReturn Clone(MfxBase** ret);

        MfxBase& operator=(MfxBase& rhs);

        MfxMove& operator=(MfxMove& rhs);

        bool operator==(MfxBase& rhs);

        bool operator==(MfxMove& rhs);

    public:
        MfxReturn MoveTo(MfxPoint* setEnd);

        MfxReturn EachFrame();
    public:
        MfxReturn GetPoint(MfxPoint* ret);

        MfxReturn GetD2D1PointU(D2D1_POINT_2U* ret);
        MfxReturn GetD2D1PointF(D2D1_POINT_2F* ret);

        MfxReturn GetX(LONG* ret);
        MfxReturn GetY(LONG* ret);
    public:
        time_t myTime_Begin, myTime_End, myTime_Now;
        MfxPoint myPoint_Begin, myPoint_End, myPoint_Now;
    };
}