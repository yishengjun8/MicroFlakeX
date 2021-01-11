#include "pch.h"
#include "MfxAppFramework.h"

MicroFlakeX::MfxApplication* theApp = nullptr;

LRESULT CALLBACK __MicroFlakeX::MfxAppProc(HWND hWnd, MfxMsg msg, WPARAM wParam, LPARAM lParam)
{
    return theApp->ForwardMessage(hWnd, msg, wParam, lParam);
}

void __MicroFlakeX::MfxRegApp(MfxApplication* reg)
{
    if (theApp)
    {
        //throw ¶ª³öÒ»¸ö´íÎó
    }
    else
    {
        theApp = reg;
    }
}

bool __MicroFlakeX::MfxUIMessageFloorCompare(MfxUI_MessageMap_Value* lhs, MfxUI_MessageMap_Value* rhs)
{
    return lhs->myFloor < rhs->myFloor;
}

bool __MicroFlakeX::MfxControlMessageFloorCompare(MfxControl_MessageMap_Value* lhs, MfxControl_MessageMap_Value* rhs)
{
    return lhs->myFloor < rhs->myFloor;
}

bool __MicroFlakeX::MfxControlFloorCompare(MfxControl* lhs, MfxControl* rhs)
{
    MfxFloor t_lhs, t_rhs;

    lhs->GetFloor(&t_lhs);
    rhs->GetFloor(&t_rhs);

    return t_lhs < t_rhs;
}

MicroFlakeX::MfxApplication* MicroFlakeX::MfxGetApp()
{
    return theApp;
}


