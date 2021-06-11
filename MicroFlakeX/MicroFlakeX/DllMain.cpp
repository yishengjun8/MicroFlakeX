#include "pch.h"

using namespace MicroFlakeX;
using namespace __MicroFlakeX;

ID2D1Factory* gID2DFactory = nullptr;
IDWriteFactory* gIDWriteFactory = nullptr;
IWICImagingFactory* gIWICImagingFactory = nullptr;

ULONG_PTR GdiPlus_Token;
Gdiplus::GdiplusStartupInput GdiPlus_StartupInput;

ID2D1Factory*& MfxGraph::myID2DFactory = gID2DFactory;
IDWriteFactory*& MfxGraph::myIDWriteFactory = gIDWriteFactory;
IWICImagingFactory*& MfxGraph::myIWICImagingFactory = gIWICImagingFactory;



std::vector<MfxSignal_Link*> MicroFlakeX::MfxSignal_Link::MfxSignal_Link_Vector;
std::vector<MfxSignal_UnLink*> MicroFlakeX::MfxSignal_UnLink::MfxSignal_UnLink_Vector;
std::unordered_map<MfxString, __MicroFlakeX::MfxFactoryHand*> __MicroFlakeX::MfxFactoryHand::MfxFactoryHand_Map;


BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call, LPVOID lpReserved
) {
    HRESULT hr;
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        Gdiplus::GdiplusStartup(&GdiPlus_Token, &GdiPlus_StartupInput, NULL);

        hr = CoInitialize(NULL);
        if (FAILED(hr))
            throw MfxText("CoInitialize Failed");

        hr = ::D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &gID2DFactory);
        if (FAILED(hr))
            throw MfxText("D2D1CreateFactory Failed");

        hr = ::DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(gIDWriteFactory),
            reinterpret_cast<IUnknown**>(&gIDWriteFactory));
        if (FAILED(hr))
            throw MfxText("IDWriteFactory Failed");

        hr = ::CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER,
            IID_PPV_ARGS(&gIWICImagingFactory));
        if (FAILED(hr))
            throw MfxText("IWICImagingFactory Failed");

        hr = MfxGraph::myIDWriteFactory->CreateTextFormat(
            L"Helvetica",                  // Font family name 微软雅黑 Arial Garamond Helvetica 等任意字体名
            NULL,                          // Font collection(NULL sets it to the system font collection)
            DWRITE_FONT_WEIGHT_REGULAR,    // Weight
            DWRITE_FONT_STYLE_NORMAL,      // Style
            DWRITE_FONT_STRETCH_NORMAL,    // Stretch
            36.0f,                         // Size    
            L"en-us",                      // Local  英国-美国 zh-CN 华 -中国
            &(MfxWords::gDefTextFormat)    // Pointer to recieve the created object
        );
        if (FAILED(hr))
            throw MfxText("gDefTextFormat Failed");


        WNDCLASSEX tempWC{ 0 };

        tempWC.cbSize = sizeof(WNDCLASSEX);
        tempWC.style = CS_HREDRAW | CS_VREDRAW;

        tempWC.lpfnWndProc = MfxAppFrameProc;
        tempWC.cbClsExtra = 0;
        tempWC.cbWndExtra = 0;
        tempWC.hInstance = GetModuleHandle(NULL);

        tempWC.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        tempWC.hCursor = LoadCursor(NULL, IDC_ARROW);
        tempWC.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);

        tempWC.lpszMenuName = 0;
        tempWC.lpszClassName = MfxText("MfxNormalUI");
        tempWC.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

        if (!RegisterClassEx(&tempWC))
        {
            MessageBox(NULL, MfxText("MfxNormalUI Registration Failed!"), MfxText("Error!"), MB_ICONEXCLAMATION | MB_OK);
        }

    }break;
    case DLL_PROCESS_DETACH:
    {
        Gdiplus::GdiplusShutdown(GdiPlus_Token);

        CoUninitialize();

        SafeRelease(gID2DFactory);
        SafeRelease(gIDWriteFactory);
        SafeRelease(gIWICImagingFactory);
    }break;

    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:

        break;
    }
    return TRUE;
}
