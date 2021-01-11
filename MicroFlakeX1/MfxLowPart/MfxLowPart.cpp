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
 
 /**/
