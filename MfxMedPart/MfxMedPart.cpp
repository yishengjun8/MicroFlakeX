#include "pch.h"
#include "MfxMedPart.h"

MicroFlakeX::MfxApplication* GlobleApp;

UINT MicroFlakeX::MfxFunc_GetUserId()
{
    static UINT mfxMessageIdPond = WM_USER + 64;
    return mfxMessageIdPond++;
}

LRESULT CALLBACK MicroFlakeX::MfxWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    //MessageBoxW(NULL, L"MfxWndProc!", L"MfxWndProc!", MB_OK);
    return GlobleApp->ForwardMessageInWnd(hWnd, message, wParam, lParam); 
}

bool MicroFlakeX::MfxGlobleApplication(MfxApplication* gApp)
{
    static bool flag = false;
    if (flag == false)
    {
        flag = true;
        GlobleApp = gApp;
        return true;
    }
    return false;
}

MicroFlakeX::MfxApplication* MicroFlakeX::MfxFunc_GetApp()
{
    return GlobleApp;
}
