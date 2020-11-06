#include "pch.h"
#include "MfxMedPart.h"

MicroFlakeX::MfxControlMessageServer::MfxControlMessageServer(MfxUI* myUI)
{
    this->myUI = myUI;
}

MicroFlakeX::MfxControlMessageServer::~MfxControlMessageServer()
{
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControlMessageServer::RegisterControl(MfxControl* regControl)
{
    /**/
    myRegisterControlList.push_back(regControl);
    return MFXRETURE_OK;
    /**/
    return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControlMessageServer::DelRegisterControl(MfxControl* canControl)
{
    /**/
    MFXCONTROL_LIST_ITERA delIter = myRegisterControlList.begin();
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
    MFXCONTROL_LIST_ITERA forIter = myRegisterControlList.begin();
    while (forIter != myRegisterControlList.end())
    {
        (*forIter)->ReceiveMessage(message, wParam, lParam);
    }
    return MFXRETURE_OK;
    /**/
    return 0;
}

MicroFlakeX::MfxUI* MicroFlakeX::MfxControlMessageServer::GetMyUI()
{
    return myUI;
}