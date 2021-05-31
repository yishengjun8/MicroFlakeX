// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "MfxAppFrame.h"

using namespace MicroFlakeX;
using namespace __MicroFlakeX;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
		WNDCLASSEX tempWC{ 0 };

		tempWC.cbSize = sizeof(WNDCLASSEX);
		tempWC.style = CS_HREDRAW | CS_VREDRAW;

		tempWC.lpfnWndProc = MfxAppFrameProc;
		tempWC.cbClsExtra = 0;               // no extra class memory 
		tempWC.cbWndExtra = 0;                // no extra window memory
		tempWC.hInstance = GetModuleHandle(NULL);		//获取程序实例句柄

		tempWC.hIcon = LoadIcon(NULL, IDI_APPLICATION);             // predefined app. icon 
		tempWC.hCursor = LoadCursor(NULL, IDC_ARROW);                // predefined arrow 
		tempWC.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);

		tempWC.lpszMenuName = 0;     // name of menu resource
		tempWC.lpszClassName = MfxText("MfxNormalUI");  // name of window class
		tempWC.hIconSm = LoadIcon(NULL, IDI_APPLICATION);  // small class icon 

		if (!RegisterClassEx(&tempWC))
		{
			MessageBox(NULL, MfxText("MfxNormalUI Registration Failed!"), MfxText("Error!"), MB_ICONEXCLAMATION | MB_OK);
		}
    }break;


    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

