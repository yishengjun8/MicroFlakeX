#include "framework.h"
#include "Example_Graph_00.h"

#include "MfxGraph.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_EXAMPLEGRAPH00, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EXAMPLEGRAPH00));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EXAMPLEGRAPH00));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_EXAMPLEGRAPH00);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 将实例句柄存储在全局变量中

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 600, 600, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
using namespace MicroFlakeX;

MfxCanvas myCanvas;

MfxImage myImage[10];
MfxWords myWords[10];

MfxRect myRect[10];
MfxSize mySize[10];
MfxPoint myPoint[10];

IWICBitmap* myIWICBitmap;
Gdiplus::Bitmap* myBitmap;


MfxGlide myGlide;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        MfxString path = L"D:\\image\\rect.jpg";
        if (Mfx_Seccess(MfxGraph::IWICBitmapFromFile(&myIWICBitmap, path, MfxSize(300, 300))))
        {
            //MessageBox(NULL, MfxText("Mfx_Seccess"), MfxText("Mfx_Seccess"), 0);
            ;
        }

        MfxGraph::GdipBitmapFromIWICBitmap(&myBitmap, myIWICBitmap, MfxRect(0, 0, 100, 200));
        //myCanvas.SetDC(GetDC(hWnd));

        myCanvas.SetWnd((hWnd));

        myRect[0].Reset(0, 0, 1000, 1000);
        myImage[0].SetRect(&myRect[0]);
       
        myImage[0].FromFile(&path, &mySize[9]);

        myImage[0].SetCanvas(&myCanvas);

        myImage[0].FromFile(&path, &mySize[9]);


        {
            myRect[0].Reset(0, 0, 10, 10);
            myImage[1].SetRect(&myRect[0]);

            myImage[1].FromFile(&path, &mySize[9]);

            myImage[1].SetCanvas(&myCanvas);



            /**
            myGlide.SetFPS(60);
            myGlide.BindObject(&(myImage[1]));
            myGlide.BindObjectType(MfxText("Rect"), MfxText("Rect"));

            myGlide.AddGulidTypePair(MfxText("Rect"), MfxText("X"), MfxText("X"));
            myGlide.AddGulidTypePair(MfxText("Rect"), MfxText("Y"), MfxText("Y"));
            myGlide.AddGulidTypePair(MfxText("Rect"), MfxText("Width"), MfxText("Width"));
            myGlide.AddGulidTypePair(MfxText("Rect"), MfxText("Height"), MfxText("Height"));

            MfxRect* tRect = new MfxRect(200, 100, 200, 200);
            myGlide.MfxAddKeyframe(MfxText("Rect"), tRect, 5000);

            tRect = new MfxRect(100, 200, 10, 10);
            myGlide.MfxAddKeyframe(MfxText("Rect"), tRect, 5000);
            /**/

            MfxGlide tGulid;
            tGulid.SetFPS(60);
            //tGulid.BindObject(&(myImage[1]));

            tGulid.BindObjectName(MfxText("group_1"),
                MfxGulid_WidelyType(MfxText("MfxPoint"), MfxText("MfxPoint"), MfxText("GetPoint"), MfxText("SetPoint")));

            tGulid.BindObjectName(MfxText("group_2"),
                MfxGulid_WidelyType(MfxText("MfxSize"), MfxText("MfxSize"), MfxText("GetSize"), MfxText("SetSize")));

            tGulid.Add_GetSetFuncName(MfxText("group_1"), MfxText("GetX"), MfxText("SetX"));
            tGulid.Add_GetSetFuncName(MfxText("group_1"), MfxText("GetY"), MfxText("SetY"));

            tGulid.Add_GetSetFuncName(MfxText("group_2"), MfxText("GetWidth"), MfxText("SetWidth"));
            tGulid.Add_GetSetFuncName(MfxText("group_2"), MfxText("GetHeight"), MfxText("SetHeight"));


            myGlide = tGulid;
            myGlide.BindObject(&(myImage[1]));

            MfxSize* tSize = new MfxSize(200, 200);
            myGlide.MfxAddKeyframe(MfxText("group_2"), tSize, 5000);

            MfxPoint* tPoint = new MfxPoint(100, 200);
            myGlide.MfxAddKeyframe(MfxText("group_1"), tPoint, 5000);

            tPoint = new MfxPoint(0, 0);
            myGlide.MfxAddKeyframe(MfxText("group_1"), tPoint, 5000);
        }

        MfxRect tRect(19, 18, 360, 120);
        MfxPoint tPoint(19, 200);

        myWords[0].SetCanvas(&myCanvas);
        myWords[0].SetRect(&tRect);
        myWords[0].SetPoint(&tPoint);
        myWords[0].SetText(L"Welcome to MFX based on D2D");
    }
    case WM_SIZE:
    {
        MfxSize tSize(LOWORD(lParam), HIWORD(lParam));
        myCanvas.SetSize(&tSize);
        myImage[0].SetSize(&tSize);
        break;
    }
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 分析菜单选择:
        switch (wmId)
        {
        case IDM_ABOUT:
        {
            MfxSize* tSize = new MfxSize(200, 200);
            myGlide.MfxAddKeyframe(MfxText("group_2"), tSize, 5000);

            MfxPoint* tPoint = new MfxPoint(100, 200);
            myGlide.MfxAddKeyframe(MfxText("group_1"), tPoint, 5000);

            tPoint = new MfxPoint(0, 0);
            myGlide.MfxAddKeyframe(MfxText("group_1"), tPoint, 5000);

            myGlide.Begin();
        }
            //DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // TODO: 在此处添加使用 hdc 的任何绘图代码...
        EndPaint(hWnd, &ps);

        MfxRect tRect(10, 10, 200, 200);
        //myCanvas.GetRect(&tRect);
        myCanvas.PaintBegin(&tRect);


        myImage[0].Paint();
        myImage[1].Paint();
        myWords[0].Paint();

        myCanvas.PaintFinish();

        //Gdiplus::Graphics tempG(GetDC(hWnd));

        //const Gdiplus::Rect tRect(20, 20, 300, 300);
        //tempG.DrawImage(myBitmap, tRect);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
