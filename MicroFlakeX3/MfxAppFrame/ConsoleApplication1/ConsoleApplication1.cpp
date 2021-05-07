#include <iostream>
#include "MfxAppFrame.h"

using namespace std;
using namespace MicroFlakeX;

int main()
{
    MfxImage myImage;

    std::cout << "Hello MicroFlakeX!\n";
    MfxUI myUI;
    myUI.SetBackColor(MfxColor(255, 0, 255, 0));

    MfxFlake* myControl0 = new MfxFlake(MfxRect(19, 18, 360, 120));
    MfxFlake* myControl1 = new MfxFlake(MfxRect(19, 18 * 2 + 120, 360, 120));

    myUI.AddFlake(myControl0);
    myUI.AddFlake(myControl1);

    myControl0->SetTitle(L"Hello MicroFlakeX!");
    myControl1->SetTitle(L"Welcome to MFX based on D2D");

    MfxApp::theApp->Run();

    return 6;
}