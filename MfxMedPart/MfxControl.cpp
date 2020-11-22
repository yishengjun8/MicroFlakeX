#include "pch.h"
#include "MfxMedPart.h"

void MicroFlakeX::MfxControl::MfxRegDef()
{
    //MfxRegDefMessage(MFXUIEVENT_DRAWBUFFERDC, (MFXCONTROL_FUNC)&MfxControl::MfxDefOnDrawBufferDC);
    //MfxRegDefMessage(MFXUIEVENT_DRAWMAINDC, (MFXCONTROL_FUNC)&MfxControl::MfxDefOnDrawMainDC);

    MfxRegDefMessage(WM_MOUSEMOVE, (MFXCONTROL_FUNC)&MfxControl::MfxDefOnMouseMove);

    MfxRegDefMessage(WM_LBUTTONDOWN, (MFXCONTROL_FUNC)&MfxControl::MfxDefOnLButtonDown);
    MfxRegDefMessage(WM_LBUTTONUP, (MFXCONTROL_FUNC)&MfxControl::MfxDefOnLButtonUp);
    MfxRegDefMessage(WM_LBUTTONDBLCLK, (MFXCONTROL_FUNC)&MfxControl::MfxDefOnLDoubleClick);

    MfxRegDefMessage(WM_RBUTTONDOWN, (MFXCONTROL_FUNC)&MfxControl::MfxDefOnRButtonDown);
    MfxRegDefMessage(WM_RBUTTONUP, (MFXCONTROL_FUNC)&MfxControl::MfxDefOnRButtonUp);
    MfxRegDefMessage(WM_RBUTTONDBLCLK, (MFXCONTROL_FUNC)&MfxControl::MfxDefOnRDoubleClick);
}

void MicroFlakeX::MfxControl::MfxInitData(MfxUI* father, Gdiplus::Rect value)
{
    myUI = father;
    myRect = value;
    myGraphics = myUI->GetBuffGraphics();

    myLButtonClick = false; //泣似
    myLButtonPress = false; //梓儿
    myRButtonClick = false; //泣似
    myRButtonPress = false; //梓儿

    myMouseFloat = false; //傅検

    myUI->RegControl(this); //廣過欺UI
    myUI->GetMessageServer()->RegControl(this); //廣過欺捲暦匂
}

MicroFlakeX::MfxControl::MfxControl(MfxUI* father, Gdiplus::Rect value)
{
    /**/
    MfxRegDef();
    MfxInitData(father, value);

    myType = L"MfxBasicsControl";
    /**/
}

MicroFlakeX::MfxControl::~MfxControl()
{
    myUI->DelControl(this); //盾茅UI廣過
    myUI->GetMessageServer()->DelControl(this); //盾茅捲暦匂廣過
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControl::RegMessage(UINT message, MFXCONTROL_FUNC valFunc)
{
    /**/
    MFXCONTROL_MESSAGE_MAPPAIR retPair = myMessageMap.insert(MFXCONTROL_MESSAGE_MAPELEM(message, valFunc));
    return retPair.second;
    /**/
    return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControl::RecvMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
    /**/
    MFXCONTROL_MESSAGE_MAPITERA handleIter = myMessageMap.find(message);
    if (handleIter != myMessageMap.end())
    {
        return (this->*handleIter->second)(wParam, lParam);
    }
    return MfxRecvDefMessage(message, wParam, lParam);
    /**/
    return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControl::DelMessage(UINT message)
{
    /**/
    MFXCONTROL_MESSAGE_MAPITERA delIter = myMessageMap.find(message);
    if (delIter != myMessageMap.end())
    {
        myMessageMap.erase(delIter);
        return MFXRETURE_OK;
    }
    return MFXRETURE_NOFIND;
    /**/
    return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControl::MfxRegDefMessage(UINT message, MFXCONTROL_FUNC valFunc)
{
    /**/
    MFXCONTROL_MESSAGE_MAPPAIR retPair = myMfxDefMessageMap.insert(MFXCONTROL_MESSAGE_MAPELEM(message, valFunc));
    return retPair.second;
    /**/
    return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControl::MfxRecvDefMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
    /**/
    MFXCONTROL_MESSAGE_MAPITERA handleIter = myMfxDefMessageMap.find(message);
    if (handleIter != myMfxDefMessageMap.end())
    {
        return (this->*handleIter->second)(wParam, lParam);
    }
    /**/
    return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControl::MfxDelDefMessage(UINT message)
{
    /**/
    MFXCONTROL_MESSAGE_MAPITERA delIter = myMfxDefMessageMap.find(message);
    if (delIter != myMfxDefMessageMap.end())
    {
        myMfxDefMessageMap.erase(delIter);
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

Gdiplus::Rect MicroFlakeX::MfxControl::GetRect()
{
    return myRect;
}

Gdiplus::Size MicroFlakeX::MfxControl::GetSize()
{
    return Gdiplus::Size(myRect.Width, myRect.Height);
}

Gdiplus::Point MicroFlakeX::MfxControl::GetPoint()
{
    return Gdiplus::Point(myRect.X, myRect.Y);
}

void MicroFlakeX::MfxControl::SetRect(Gdiplus::Rect set)
{
    myRect = set;
}

void MicroFlakeX::MfxControl::SetSize(Gdiplus::Size set)
{
    myRect.Width = set.Width;
    myRect.Height = set.Height;
}

void MicroFlakeX::MfxControl::SetPoint(Gdiplus::Point set)
{
    myRect.X = set.X;
    myRect.Y = set.Y;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！和中議旗鷹頁潮範�贄Α�！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControl::MfxDefOnDrawBufferDC(WPARAM wParam, LPARAM lParam)
{
    return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControl::MfxDefOnDrawMainDC(WPARAM wParam, LPARAM lParam)
{
    return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControl::MfxDefOnMouseMove(WPARAM wParam, LPARAM lParam)
{
    Gdiplus::Point mousePos = Gdiplus::Point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
    if (myRect.Contains(mousePos))
    {
        myUI->RecvControlEvent(this, MFXCONTROLEVENT_MOUSEFLOAT, wParam, lParam);
        myMouseFloat = true;
    }
    else
    {
        myLButtonClick = false;
        myRButtonClick = false;
        myMouseFloat = false;
    }
    return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControl::MfxDefOnLButtonDown(WPARAM wParam, LPARAM lParam)
{
    Gdiplus::Point mousePos = Gdiplus::Point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
    if (myRect.Contains(mousePos))
    {
        myLButtonClick = true;
        myLButtonPress = true;
        myMouseFloat = true;
    }
    else
    {
        myLButtonClick = false;
        myLButtonPress = false;
        myMouseFloat = false;
    }
    return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControl::MfxDefOnLButtonUp(WPARAM wParam, LPARAM lParam)
{
    Gdiplus::Point mousePos = Gdiplus::Point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
    if (myRect.Contains(mousePos))
    {
        if (myLButtonClick == true)
        {
            myUI->SetUserFocus(this);
            myUI->RecvControlEvent(this, MFXCONTROLEVENT_LBUTTONCLICK, wParam, lParam);
        }
        myLButtonClick = false;
        myLButtonPress = false;
        myMouseFloat = true;
    }
    else
    {
        myLButtonClick = false;
        myLButtonPress = false;
        myMouseFloat = false;
    }
    return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControl::MfxDefOnLDoubleClick(WPARAM wParam, LPARAM lParam)
{
    return myUI->RecvControlEvent(this, MFXCONTROLEVENT_LDOUBLECLICK, wParam, lParam);
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControl::MfxDefOnRButtonDown(WPARAM wParam, LPARAM lParam)
{
    Gdiplus::Point mousePos = Gdiplus::Point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
    if (myRect.Contains(mousePos))
    {
        myRButtonClick = true;
        myRButtonPress = true;
        myMouseFloat = true;
    }
    else
    {
        myRButtonClick = false;
        myRButtonPress = false;
        myMouseFloat = false;
    }
    return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControl::MfxDefOnRButtonUp(WPARAM wParam, LPARAM lParam)
{
    Gdiplus::Point mousePos = Gdiplus::Point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
    if (myRect.Contains(mousePos))
    {
        if (myRButtonClick == true)
        {
            myUI->RecvControlEvent(this, MFXCONTROLEVENT_RBUTTONCLICK, wParam, lParam);
        }
        myRButtonClick = false;
        myRButtonPress = false;
        myMouseFloat = true;
    }
    else
    {
        myRButtonClick = false;
        myRButtonPress = false;
        myMouseFloat = false;
    }
    return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControl::MfxDefOnRDoubleClick(WPARAM wParam, LPARAM lParam)
{
    return myUI->RecvControlEvent(this, MFXCONTROLEVENT_RDOUBLECLICK, wParam, lParam);
}
