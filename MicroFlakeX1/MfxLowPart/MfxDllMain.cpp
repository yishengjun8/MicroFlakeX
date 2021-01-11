// MF_DllMain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"

ULONG_PTR GdiPlus_Token;
Gdiplus::GdiplusStartupInput GdiPlus_StartupInput;

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    {
        /* 初始化Gdiplus，必须要做的 */
        Gdiplus::GdiplusStartup(&GdiPlus_Token, &GdiPlus_StartupInput, NULL);
    }break;
    case DLL_THREAD_DETACH:
    {
        /* 初始化结束后释放资源 */
        Gdiplus::GdiplusShutdown(GdiPlus_Token);
    }break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

