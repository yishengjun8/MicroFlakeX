#pragma once
#include "MfxMedPart.h"
#include "MfxButton.h"
using namespace MicroFlakeX;

#define MYCLOCL_1 WM_APP+1

class MyUI :
    public MfxUI
{
public:
    MyUI(Gdiplus::Rect theRect, DWORD dwStyle, std::wstring title, MfxUI* father = nullptr);
protected:
    MFXRETURE OnButton01Click(WPARAM wParam, LPARAM lParam);
    //MFXRETURE OnClock1(WPARAM wParam, LPARAM lParam);
};

