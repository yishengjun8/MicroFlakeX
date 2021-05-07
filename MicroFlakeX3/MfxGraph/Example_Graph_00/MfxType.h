#pragma once

#ifdef MFX_BUILDING
#define MFX_PORT __declspec(dllexport)
#else
#define MFX_PORT __declspec(dllimport)
#pragma comment(lib, "MfxType.lib")
#include "MfxBase.h"

/* ÊýÑ§¿â */
#include <cmath>
/**/

/* STLÄ£°å¿â */
/**/

/* Direct2D1 */
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <dwmapi.h>
/**/

/* time¿â */
#include <ctime>
/**/

#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "DWrite.lib")
#endif

namespace MicroFlakeX
{
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
        MfxRect(MfxRect* set);
        MfxRect(MfxSize* set);
        MfxRect(MfxPoint* set);
        MfxRect(FLOAT setX, FLOAT setY, FLOAT setWidth, FLOAT setHeight);
        ~MfxRect();
        MfxReturn Clone(MfxBase** ret);
        MfxBase& operator=(MfxBase& rhs);
        MfxRect& operator=(MfxRect& rhs);
        MfxRect& operator=(MfxSize& rhs);
        MfxRect& operator=(MfxPoint& rhs);
        BOOL operator==(MfxBase& rhs);
        BOOL operator==(MfxRect& rhs);

    public:
        MfxReturn Init(FLOAT setX, FLOAT setY, FLOAT setWidth, FLOAT setHeight);
    public:
        MfxReturn GetD2D1RectU(D2D1_RECT_U* ret);
        MfxReturn GetD2D1SizeU(D2D1_SIZE_U* ret);
        MfxReturn GetD2D1PointU(D2D1_POINT_2U* ret);

        MfxReturn GetD2D1RectF(D2D1_RECT_F* ret);
        MfxReturn GetD2D1SizeF(D2D1_SIZE_F* ret);
        MfxReturn GetD2D1PointF(D2D1_POINT_2F* ret);

        MfxReturn GetRECT(RECT* ret);
        MfxReturn GetSIZE(SIZE* ret);
        MfxReturn GetPOINT(POINT* ret);

        MfxReturn SetSize(MfxSize* set);
        MfxReturn SetPoint(MfxPoint* set);

        MfxReturn SetX(FLOAT set);
        MfxReturn SetY(FLOAT set);
        MfxReturn SetWidth(FLOAT set);
        MfxReturn SetHeight(FLOAT set);

        MfxReturn SetTop(FLOAT set);
        MfxReturn SetLeft(FLOAT set);
        MfxReturn SetRight(FLOAT set);
        MfxReturn SetBottom(FLOAT set);

        MfxReturn GetSize(MfxSize* ret);
        MfxReturn GetPoint(MfxPoint* ret);

        MfxReturn GetX(FLOAT* ret);
        MfxReturn GetY(FLOAT* ret);
        MfxReturn GetWidth(FLOAT* ret);
        MfxReturn GetHeight(FLOAT* ret);

        MfxReturn GetTop(FLOAT* ret);
        MfxReturn GetLeft(FLOAT* ret);
        MfxReturn GetRight(FLOAT* ret);
        MfxReturn GetBottom(FLOAT* ret);

        MfxReturn Empty(BOOL* ret);
        MfxReturn Offset(FLOAT setX, FLOAT setY);
        MfxReturn Inflate(FLOAT setX, FLOAT setY);

        MfxReturn Collision(MfxBase* set, BOOL* ret);
    public:
        FLOAT myX;
        FLOAT myY;
        FLOAT myWidth;
        FLOAT myHeight;
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
        MfxSize(MfxRect* set);
        MfxSize(MfxSize* set);
        MfxSize(FLOAT setWidth, FLOAT setHeight);
        ~MfxSize();
        MfxReturn Clone(MfxBase** ret);
        MfxBase& operator=(MfxBase& rhs);
        MfxSize& operator=(MfxRect& rhs);
        MfxSize& operator=(MfxSize& rhs);
        BOOL operator==(MfxBase& rhs);
        BOOL operator==(MfxSize& rhs);

    public:
        MfxReturn Init(FLOAT setWidth, FLOAT setHeight);
    public:
        MfxReturn GetD2D1SizeF(D2D1_SIZE_F* ret);
        MfxReturn GetD2D1SizeU(D2D1_SIZE_U* ret);

        MfxReturn GetSIZE(SIZE* ret);

        MfxReturn Empty(BOOL* ret);
        MfxReturn Inflate(FLOAT setX, FLOAT setY);

        MfxReturn SetWidth(FLOAT set);
        MfxReturn SetHeight(FLOAT set);

        MfxReturn GetWidth(FLOAT* ret);
        MfxReturn GetHeight(FLOAT* ret);
    public:
        FLOAT myWidth;
        FLOAT myHeight;
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
        MfxPoint(MfxRect* set);
        MfxPoint(MfxPoint* set);
        MfxPoint(FLOAT setX, FLOAT setY);
        ~MfxPoint();
        MfxReturn Clone(MfxBase** ret);
        MfxBase& operator=(MfxBase& rhs);
        MfxPoint& operator=(MfxRect& rhs);
        MfxPoint& operator=(MfxPoint& rhs);
        BOOL operator==(MfxBase& rhs);
        BOOL operator==(MfxPoint& rhs);

    public:
        MfxReturn Init(FLOAT setX, FLOAT setY);
    public:
        MfxReturn GetD2D1PointU(D2D1_POINT_2U* ret);
        MfxReturn GetD2D1PointF(D2D1_POINT_2F* ret);

        MfxReturn Offset(FLOAT setX, FLOAT setY);

        MfxReturn SetX(FLOAT set);
        MfxReturn SetY(FLOAT set);

        MfxReturn GetX(FLOAT* ret);
        MfxReturn GetY(FLOAT* ret);
    public:
        FLOAT myX;
        FLOAT myY;
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
        MfxColor(FLOAT setA, FLOAT setR, FLOAT setG, FLOAT setB);
        ~MfxColor();
        MfxReturn Clone(MfxBase** ret);
        MfxBase& operator=(MfxBase& rhs);
        MfxColor& operator=(MfxColor& rhs);
        BOOL operator==(MfxBase& rhs);
        BOOL operator==(MfxColor& rhs);

    public:
        MfxReturn Init(FLOAT setA, FLOAT setR, FLOAT setG, FLOAT setB);
    public:
        MfxReturn SetColor(FLOAT setA, UINT32 set);
        MfxReturn GetD2D1ColorF(D2D1_COLOR_F* ret);

        MfxReturn SetA(FLOAT ret);
        MfxReturn SetR(FLOAT ret);
        MfxReturn SetG(FLOAT ret);
        MfxReturn SetB(FLOAT ret);

        MfxReturn GetA(FLOAT* ret);
        MfxReturn GetR(FLOAT* ret);
        MfxReturn GetG(FLOAT* ret);
        MfxReturn GetB(FLOAT* ret);

        MfxReturn GetRGB(UINT32* ret);
    public:
        FLOAT myA;
        FLOAT myR;
        FLOAT myG;
        FLOAT myB;
    };
}

namespace MicroFlakeX
{
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
        BOOL operator==(MfxBase& rhs);
        BOOL operator==(MfxMove& rhs);

    public:
        MfxReturn MoveTo(MfxPoint* setEnd);
        MfxReturn EachFrame();
    public:
        MfxReturn GetPoint(MfxPoint* ret);

        MfxReturn GetD2D1PointU(D2D1_POINT_2U* ret);
        MfxReturn GetD2D1PointF(D2D1_POINT_2F* ret);

        MfxReturn GetX(FLOAT* ret);
        MfxReturn GetY(FLOAT* ret);
    public:
        time_t myTime_Begin, myTime_End, myTime_Now;
        MfxPoint myPoint_Begin, myPoint_End, myPoint_Now;
    };
}