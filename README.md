## MicroFlakeX
    一个运行在Windows上的简单的DirectUI库。

## 请使用下面的代码测试是否正确运行

    #include "MfxMedPart.h"
    #include "MfxButton.h"
    #pragma comment(lib,"MfxMedPart.lib")
    using namespace MicroFlakeX;
    int APIENTRY wWinMain(
        _In_ HINSTANCE hInstance,
        _In_opt_ HINSTANCE hPrevInstance,
        _In_ LPWSTR lpCmdLine,
        _In_ int nShowCmd
    ){
        MfxApplication app;
        MfxUI* a1 = new MfxUI(Gdiplus::Rect(0, 0, 500, 500),0 , MFXWINDTYPE_NORMAL,
            L"a1");
        MfxButton myButton(a1, Gdiplus::Rect(60, 60, 160, 50));
        MfxImage mytest(a1->GetBufferGraphics(), (WCHAR*)L"D:\\testt.png");
        a1->SetUIBack(&mytest);
        return app.AppRun();
    }

## 未来的控件计划：
    MfxButton.h、MfxEdit.h
    将会有一次重新的命名和对部分类的移动归类，但是整体框架不会改变了。

## 注意事项：
    当你继承UI类，重写UI消息时候，必须使用装饰的设计模式！
