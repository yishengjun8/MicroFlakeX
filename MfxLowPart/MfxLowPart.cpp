#include "pch.h"
#include "MfxLowPart.h"

 HDC MicroFlakeX::MfxFunc_GethDC(HWND hWnd)
{
    return GetDC(hWnd);
}

 HDC MicroFlakeX::MfxFunc_GetComhDC(HDC hDc, Gdiplus::Size dcSize)
{
    HDC retDc = CreateCompatibleDC(hDc);
    SelectObject(retDc, CreateCompatibleBitmap(hDc, dcSize.Width, dcSize.Height));
    return retDc;
}

 bool MicroFlakeX::MfxFunc_SethDCBack(HDC hDc, Gdiplus::Size dcSize, bool bColor)
{
    if (bColor == true)
    {
        return BitBlt(hDc, 0, 0, dcSize.Width, dcSize.Height, 0, 0, 0, BLACKNESS);
    }
    else
    {
        return BitBlt(hDc, 0, 0, dcSize.Width, dcSize.Height, 0, 0, 0, WHITENESS);
    }
}

 Gdiplus::Graphics* MicroFlakeX::MfxFunc_GetGraphics(HDC hDc)
{
    return new Gdiplus::Graphics(hDc);
}
 /**/
 Gdiplus::Graphics* MicroFlakeX::MfxFunc_GetGraphics(Gdiplus::Bitmap* bitmap)
{
    return new Gdiplus::Graphics(bitmap);
}
 
 BOOL MicroFlakeX::MfxFunc_CheckIntersectsWith(MfxImage* a, MfxImage* b)
{
    return  a->GetImageRect().IntersectsWith(b->GetImageRect());
}

 BOOL MicroFlakeX::MfxFunc_CheckIntersectsWith(MfxImage* a, MfxWords* b)
{
    Gdiplus::RectF bRectF = b->GetWordsRectF();
    Gdiplus::Rect bRect(bRectF.X, bRectF.Y, bRectF.Width, bRectF.Height);
    return  a->GetImageRect().IntersectsWith(bRect);
}

 BOOL MicroFlakeX::MfxFunc_CheckIntersectsWith(MfxWords* a, MfxWords* b)
{
    return  a->GetWordsRectF().IntersectsWith(b->GetWordsRectF());
}

 BOOL MicroFlakeX::MfxFunc_CheckContains(MfxImage* a, MfxImage* b)
{
    Gdiplus::Rect bRect = b->GetImageRect();
    return a->GetImageRect().Contains(bRect);
}

 BOOL MicroFlakeX::MfxFunc_CheckContains(MfxImage* a, MfxWords* b)
{
    Gdiplus::RectF bRectF = b->GetWordsRectF();
    Gdiplus::Rect bRect(bRectF.X, bRectF.Y, bRectF.Width, bRectF.Height);
    return a->GetImageRect().Contains(bRect);
}

 BOOL MicroFlakeX::MfxFunc_CheckContains(MfxWords* a, MfxImage* b)
{
    Gdiplus::Rect bRect = b->GetImageRect();
    Gdiplus::RectF bRectF(bRect.X, bRect.Y, bRect.Width, bRect.Height);
    return a->GetWordsRectF().Contains(bRectF);
}

 BOOL MicroFlakeX::MfxFunc_CheckContains(MfxWords* a, MfxWords* b)
{
    Gdiplus::RectF bRectF = b->GetWordsRectF();
    return a->GetWordsRectF().Contains(bRectF);
}
 /**/

