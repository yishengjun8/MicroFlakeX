#include "pch.h"
#include "MfxMedPart.h"

MicroFlakeX::MfxControl::MfxControl(MfxUI* getUI, Gdiplus::Rect setRect)
{
    /**/
    myUI = getUI;
    myUI->GetMessageServer()->RegisterControl(this); // 服务器注册
    myUI->RegisterControl(this); //注册UI列表
    myRect = setRect;
    myGraphics = myUI->GetGraphics();

    myType = L"MfxBasicsControl";
    /**/
}

MicroFlakeX::MfxControl::~MfxControl()
{
    myUI->GetMessageServer()->DelRegisterControl(this); //删除服务器注册
    myUI->DelRegisterControl(this); //删除UI注册
}
MicroFlakeX::MFXRETURE MicroFlakeX::MfxControl::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
    /**/
    MFXCONTROL_MESSAGE_FUNC_MAP_ITERA handleIter = myMessageMap.find(message);
    if (handleIter != myMessageMap.end())
    {
        //响应控件自己的消息
        return (this->*handleIter->second)(wParam, lParam);
        //在自己的控件消息里面发送响应事件给UI界面
        //ret |= myUI->ReceiveControlMessage(this, message, wParam, lParam);
    }
    return MFXRETURE_NOFIND;
    /**/
    return 0;
    
}
MicroFlakeX::MFXRETURE MicroFlakeX::MfxControl::RegisterMessage(UINT keyMsg, MFXCONTROL_MESSAGE_FUNC valFunc)
{
    /**/
    MFXCONTROL_MESSAGE_FUNC_MAP_PAIR retPair = myMessageMap.insert(MFXCONTROL_MESSAGE_FUNC_MAP_ELEM(keyMsg, valFunc));
    return retPair.second;
    /**/
    return 0;
}
MicroFlakeX::MFXRETURE MicroFlakeX::MfxControl::DelRegisterControl(UINT keyMsg)
{
    /**/
    MFXCONTROL_MESSAGE_FUNC_MAP_ITERA delIter = myMessageMap.find(keyMsg);
    if (delIter != myMessageMap.end())
    {
        myMessageMap.erase(delIter);
        return MFXRETURE_OK;
    }
    return MFXRETURE_NOFIND;
    /**/
    return 0;
}
MicroFlakeX::MfxUI* MicroFlakeX::MfxControl::GetMyUI()
{
    return myUI;
}
std::wstring MicroFlakeX::MfxControl::GetMyType()
{
    return myType;
}

Gdiplus::Size MicroFlakeX::MfxControl::GetSize()
{
    return Gdiplus::Size(myRect.Width, myRect.Height);
}