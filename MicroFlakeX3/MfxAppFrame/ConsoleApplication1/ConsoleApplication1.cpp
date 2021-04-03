#include <iostream>
#include "MfxAppFrame.h"
using namespace std;
using namespace MicroFlakeX;


class UI
    : public MfxUI
{
public:
    UI() :MfxUI::MfxUI()
    {
        //this->
    }
};

int main()
{
    std::cout << "Hello MicroFlakeX!\n";
    UI myUI;
    myUI.SetBackColor(MfxColor(255, 0, 255, 0));

    MfxControl myControl0(MfxRect(19, 18, 360, 120));
    MfxControl myControl1(MfxRect(19, 18*2 + 120, 360, 120));

    myUI.AddControl(&myControl0);
    myUI.AddControl(&myControl1);

    myControl0.SetTitle(L"Hello MicroFlakeX!");
    myControl1.SetTitle(L"Welcome to MFX based on D2D");

    MfxApp::theApp->Run();

    return 6;
}