#pragma once
#include "MfxMedPart.h"

using namespace MicroFlakeX;


class MyUI :
    public MfxUI
{
public:
    MyUI(Gdiplus::Rect theRect, DWORD dwStyle, std::wstring title, MfxUI* father = nullptr);
//protected:
    MFXRETURE OnButton01Click(WPARAM wParam, LPARAM lParam);
};

