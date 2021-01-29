#include "pch.h"

ULONG_PTR GdiPlus_Token;
Gdiplus::GdiplusStartupInput GdiPlus_StartupInput;

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call, LPVOID lpReserved
) {
    HRESULT hr;
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        hr = CoInitialize(NULL);
        if (FAILED(hr))
            throw L"CoInitialize Failed";
        Gdiplus::GdiplusStartup(&GdiPlus_Token, &GdiPlus_StartupInput, NULL);
    }break;
    case DLL_PROCESS_DETACH:
    {
        CoUninitialize();
        Gdiplus::GdiplusShutdown(GdiPlus_Token);
    }break;

    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    }
    return TRUE;
}
