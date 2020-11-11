#include "pch.h"
#include "MfxMedPart.h"

void MicroFlakeX::MfxControl::MfxRegDef()
{
    MfxRegDefMessage(WM_PAINT, (MFXCONTROL_MESSAGE_FUNC)&MfxControl::MfxDefOnPaint);
    MfxRegDefMessage(WM_MOUSEMOVE, (MFXCONTROL_MESSAGE_FUNC)&MfxControl::MfxDefOnMouseMove);

    MfxRegDefMessage(WM_LBUTTONDOWN, (MFXCONTROL_MESSAGE_FUNC)&MfxControl::MfxDefOnLButtonDown);
    MfxRegDefMessage(WM_LBUTTONUP, (MFXCONTROL_MESSAGE_FUNC)&MfxControl::MfxDefOnLButtonUp);
    MfxRegDefMessage(WM_LBUTTONDBLCLK, (MFXCONTROL_MESSAGE_FUNC)&MfxControl::MfxDefOnLDoubleClick);

    MfxRegDefMessage(WM_RBUTTONDOWN, (MFXCONTROL_MESSAGE_FUNC)&MfxControl::MfxDefOnRButtonDown);
    MfxRegDefMessage(WM_RBUTTONUP, (MFXCONTROL_MESSAGE_FUNC)&MfxControl::MfxDefOnRButtonUp);
    MfxRegDefMessage(WM_RBUTTONDBLCLK, (MFXCONTROL_MESSAGE_FUNC)&MfxControl::MfxDefOnRDoubleClick);
}

void MicroFlakeX::MfxControl::MfxInitData(MfxUI* father, Gdiplus::Rect value)
{
    myUI = father;
    myRect = value;
    myGraphics = myUI->GetBuffGraphics();

    myClick = false; //泣似
    myPress = false; //梓儿
    myFloat = false; //傅検

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

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControl::ThreadPaint()
{
    return RecMessage(WM_PAINT, 0, 0);
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControl::RegMessage(UINT message, MFXCONTROL_MESSAGE_FUNC valFunc)
{
    /**/
    MFXCONTROL_MESSAGE_FUNC_MAP_PAIR retPair = myMessageMap.insert(MFXCONTROL_MESSAGE_FUNC_MAP_ELEM(message, valFunc));
    return retPair.second;
    /**/
    return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControl::RecMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
    /**/
    MFXCONTROL_MESSAGE_FUNC_MAP_ITERA handleIter = myMessageMap.find(message);
    if (handleIter != myMessageMap.end())
    {
        return (this->*handleIter->second)(wParam, lParam);
    }
    return MfxRecDefMessage(message, wParam, lParam);
    /**/
    return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControl::DelMessage(UINT message)
{
    /**/
    MFXCONTROL_MESSAGE_FUNC_MAP_ITERA delIter = myMessageMap.find(message);
    if (delIter != myMessageMap.end())
    {
        myMessageMap.erase(delIter);
        return MFXRETURE_OK;
    }
    return MFXRETURE_NOFIND;
    /**/
    return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControl::MfxRegDefMessage(UINT message, MFXCONTROL_MESSAGE_FUNC valFunc)
{
    /**/
    MFXCONTROL_MESSAGE_FUNC_MAP_PAIR retPair = myMfxDefMessageMap.insert(MFXCONTROL_MESSAGE_FUNC_MAP_ELEM(message, valFunc));
    return retPair.second;
    /**/
    return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControl::MfxRecDefMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
    /**/
    MFXCONTROL_MESSAGE_FUNC_MAP_ITERA handleIter = myMfxDefMessageMap.find(message);
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
    MFXCONTROL_MESSAGE_FUNC_MAP_ITERA delIter = myMfxDefMessageMap.find(message);
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

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControl::MfxDefOnPaint(WPARAM wParam, LPARAM lParam)
{
    return MFXRETURE();
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControl::MfxDefOnMouseMove(WPARAM wParam, LPARAM lParam)
{
    Gdiplus::Point mousePos = Gdiplus::Point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
    if (myRect.Contains(mousePos))
    {
        PostMessage(myUI->GetWnd(), MFXCONTROLEVENT_MOUSEFLOAT, wParam, lParam);
        myFloat = true;
    }
    else
    {
        myClick = false;
        myFloat = false;
    }
    return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControl::MfxDefOnLButtonDown(WPARAM wParam, LPARAM lParam)
{
    Gdiplus::Point mousePos = Gdiplus::Point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
    if (myRect.Contains(mousePos))
    {
        myClick = true;
        myFloat = true;
        myPress = true;
    }
    else
    {
        myClick = false;
        myPress = false;
        myFloat = false;
    }
    return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControl::MfxDefOnLButtonUp(WPARAM wParam, LPARAM lParam)
{
    Gdiplus::Point mousePos = Gdiplus::Point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
    if (myRect.Contains(mousePos))
    {
        if (myClick == true)
        {
            PostMessage(myUI->GetWnd(), MFXCONTROLEVENT_CLICK, wParam, lParam);
        }
        myClick = false;
        myFloat = true;
        myPress = false;
    }
    else
    {
        myClick = false;
        myPress = false;
        myFloat = false;
    }
    return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControl::MfxDefOnLDoubleClick(WPARAM wParam, LPARAM lParam)
{
    return PostMessage(myUI->GetWnd(), MFXCONTROLEVENT_LDOUBLECLICK, wParam, lParam);
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControl::MfxDefOnRButtonDown(WPARAM wParam, LPARAM lParam)
{
    return MFXRETURE();
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControl::MfxDefOnRButtonUp(WPARAM wParam, LPARAM lParam)
{
    return MFXRETURE();
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControl::MfxDefOnRDoubleClick(WPARAM wParam, LPARAM lParam)
{
    return PostMessage(myUI->GetWnd(), MFXCONTROLEVENT_RDOUBLECLICK, wParam, lParam);
}
