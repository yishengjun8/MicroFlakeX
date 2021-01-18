#pragma once

#ifdef MfxBUILDING
#define Mfx_PORT __declspec(dllexport)
#else
#define Mfx_PORT __declspec(dllimport)
#pragma comment(lib, "MfxTypes.lib")

/* ÊýÑ§¿â */
#include <cmath>
/**/

/* STLÄ£°å¿â */
/**/

/* GDIPLUS */
#include <gdiplus.h>
#pragma comment(lib,"gdiplus.lib")
/**/

/* Direct2D1 */
#include <d2d1.h>
#include <dwmapi.h>
#include <dwrite.h>
#include <wincodec.h>
#include <d2d1helper.h>
#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "DWrite.lib")
/**/
#endif

namespace MicroFlakeX
{
    class Mfx_PORT MfxType;

    class Mfx_PORT MfxRect;
    class Mfx_PORT MfxSize;
    class Mfx_PORT MfxPoint;

    class Mfx_PORT MfxColor;
}

namespace MicroFlakeX
{
    class MfxType :
        public MfxBase
    {

    };
}

namespace MicroFlakeX
{
    class MfxRect :
        public MfxType
    {
        MfxOBJECT;
    public:
        MfxRect();
        ~MfxRect();
        MfxReturn Clone(MfxBase** ret);
        MfxBase& operator=(MfxBase& rhs);
        BOOL operator==(MfxBase& rhs);

    public:
        MfxReturn Init(FLOAT setX, FLOAT setY, FLOAT setWidth, FLOAT setHeight);
    public:
        MfxReturn GetD2D1RectU(D2D1_RECT_U* ret);
        MfxReturn GetD2D1SizeU(D2D1_SIZE_U* ret);
        MfxReturn GetD2D1PointU(D2D1_POINT_2U* ret);

        MfxReturn GetD2D1RectF(D2D1_RECT_F* ret);
        MfxReturn GetD2D1SizeF(D2D1_SIZE_F* ret);
        MfxReturn GetD2D1PointF(D2D1_POINT_2F* ret);

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
    protected:
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
        MfxOBJECT;
    public:
        MfxSize();
        ~MfxSize();
        MfxReturn Clone(MfxBase** ret);
        MfxBase& operator=(MfxBase& rhs);
        BOOL operator==(MfxBase& rhs);

    public:
        MfxReturn Init(FLOAT setWidth, FLOAT setHeight);
    public:
        MfxReturn GetD2D1SizeF(D2D1_SIZE_F* ret);
        MfxReturn GetD2D1SizeU(D2D1_SIZE_U* ret);

        MfxReturn Empty(BOOL* ret);
        MfxReturn Inflate(FLOAT setX, FLOAT setY);

        MfxReturn SetWidth(FLOAT set);
        MfxReturn SetHeight(FLOAT set);

        MfxReturn GetWidth(FLOAT* ret);
        MfxReturn GetHeight(FLOAT* ret);
    protected:
        FLOAT myWidth;
        FLOAT myHeight;
    };
}


namespace MicroFlakeX
{
    class MfxPoint
        : public MfxType
    {
        MfxOBJECT;
    public:
        MfxPoint();
        ~MfxPoint();
        MfxReturn Clone(MfxBase** ret);
        MfxBase& operator=(MfxBase& rhs);
        BOOL operator==(MfxBase& rhs);

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
    protected:
        FLOAT myX;
        FLOAT myY;
    };
}

namespace MicroFlakeX
{
    class MfxColor
        : public MfxType
    {
        MfxOBJECT;
    public:
        MfxColor();
        ~MfxColor();
        MfxReturn Clone(MfxBase** ret);
        MfxBase& operator=(MfxBase& rhs);
        BOOL operator==(MfxBase& rhs);

    public:
        MfxReturn Init(FLOAT setA, FLOAT setR, FLOAT setG, FLOAT setB);
    public:
        MfxReturn SetColor(FLOAT setA, UINT32 set);
        MfxReturn GetD2D1ColorF(D2D1_COLOR_F* ret);

        MfxReturn GetA(FLOAT* ret);
        MfxReturn GetR(FLOAT* ret);
        MfxReturn GetG(FLOAT* ret);
        MfxReturn GetB(FLOAT* ret);
        MfxReturn GetRGB(UINT32* ret);
    protected:
        FLOAT myA;
        FLOAT myR;
        FLOAT myG;
        FLOAT myB;
    };
}