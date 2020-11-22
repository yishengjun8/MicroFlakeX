#include "pch.h"
#include "MfxMedPart.h"

MicroFlakeX::MfxControlMessageServer::MfxControlMessageServer(MfxUI* myUI)
{
    this->myUI = myUI;
}

MicroFlakeX::MfxControlMessageServer::~MfxControlMessageServer()
{
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControlMessageServer::RegControl(MfxControl* regControl)
{
    /**/
    myRegisterControlList.push_back(regControl);
    return MFXRETURE_OK;
    /**/
    return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControlMessageServer::DelControl(MfxControl* canControl)
{
    /**/
    MFXCONTROL_LISTITERA delIter = myRegisterControlList.begin();
    while (delIter != myRegisterControlList.end())
    {
        if (*delIter == canControl)
        {
            myRegisterControlList.erase(delIter);
            return MFXRETURE_OK;
        }
        delIter++;
    }
    return MFXRETURE_NOFIND;
    /**/
    return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControlMessageServer::ForwardMessageToControl(UINT message, WPARAM wParam, LPARAM lParam)
{
    /**/
    for (int i = 0; i < myRegisterControlList.size(); i++)
    {
        (myRegisterControlList[i])->RecvMessage(message, wParam, lParam);
    }
    return MFXRETURE_OK;
    /**/
    return 0;
}

MicroFlakeX::MfxUI* MicroFlakeX::MfxControlMessageServer::GetMyUI()
{
    return myUI;
}