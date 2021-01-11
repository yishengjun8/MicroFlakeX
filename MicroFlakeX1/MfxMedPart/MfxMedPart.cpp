#include "pch.h"
#include "MfxMedPart.h"


MicroFlakeX::MfxApplication* GlobleApp;

/*
#include "cstdio"
using namespace std;
FILE* gFileOut;
/**/

UINT MicroFlakeX::MfxFunc_GetUserId()
{
    static UINT mfxMessageIdPond = WM_USER + 32;
    return mfxMessageIdPond++;
}

LRESULT CALLBACK MicroFlakeX::MfxWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    //return DefWindowProc(hWnd, message, wParam, lParam);
    //fprintf(gFileOut, "hWnd:%d, message:%d, wParam:%d, lParam:%d \n", (long)hWnd, (long)message, (long)wParam, (long)lParam);
    return GlobleApp->ForwardMessageByWnd(hWnd, message, wParam, lParam);
}

bool MicroFlakeX::MfxGlobleApplication(MfxApplication* gApp)
{
    static bool flag = false;
    if (flag == false)
    {
        flag = true;
        GlobleApp = gApp;
        //fopen_s(&gFileOut, "D:\\MfxWndProc.txt", "wb");
        return true;
    }
    return false;
}

BOOL CALLBACK MicroFlakeX::MfxEnumRedrawWindow(HWND hWnd, LPARAM lParam)
{
     return RedrawWindow(hWnd, NULL, NULL, RDW_FRAME | RDW_INVALIDATE);// | RDW_NOINTERNALPAINT);
}

BOOL CALLBACK MicroFlakeX::MfxEnumFatherSize(HWND hWnd, LPARAM lParam)
{
    return PostMessage(hWnd, MFXUIEVENT_FATHERSIZE, 0, lParam);
}

MicroFlakeX::MfxApplication* MicroFlakeX::MfxFunc_GetApp()
{
    return GlobleApp;
}
