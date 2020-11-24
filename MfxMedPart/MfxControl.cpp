#include "pch.h"
#include "MfxMedPart.h"

void MicroFlakeX::MfxControl::MfxRegDef()
{
    MfxRegDefMessage(MFXUIEVENT_DRAWBUFFDC, (MFXCONTROL_FUNC)&MfxControl::MfxDefOnDrawBuffDC);
    MfxRegDefMessage(MFXUIEVENT_DRAWMAINDC, (MFXCONTROL_FUNC)&MfxControl::MfxDefOnDrawMainDC);

    MfxRegDefMessage(WM_MOUSEMOVE, (MFXCONTROL_FUNC)&MfxControl::MfxDefOnMouseMove);

    MfxRegDefMessage(WM_LBUTTONDOWN, (MFXCONTROL_FUNC)&MfxControl::MfxDefOnLButtonDown);
    MfxRegDefMessage(WM_LBUTTONUP, (MFXCONTROL_FUNC)&MfxControl::MfxDefOnLButtonUp);
    MfxRegDefMessage(WM_LBUTTONDBLCLK, (MFXCONTROL_FUNC)&MfxControl::MfxDefOnLDoubleClick);

    MfxRegDefMessage(WM_RBUTTONDOWN, (MFXCONTROL_FUNC)&MfxControl::MfxDefOnRButtonDown);
    MfxRegDefMessage(WM_RBUTTONUP, (MFXCONTROL_FUNC)&MfxControl::MfxDefOnRButtonUp);
    MfxRegDefMessage(WM_RBUTTONDBLCLK, (MFXCONTROL_FUNC)&MfxControl::MfxDefOnRDoubleClick);
}

void MicroFlakeX::MfxControl::MfxInitData(
    MfxUI* father, Gdiplus::Rect rect, std::wstring type, std::wstring title, LPARAM lParam
)
{
    myUI = father;
    myFloor = 8; //数字越大，越上层，每次更改需要发送MFXCONTROLEVENT_FLOORCHANGE重排序
    myType = type;
    myTitle = title;

    myRect = rect;
    myBuffGraphics = myUI->GetBuffGraphics();
    myMainGraphics = myUI->GetMainGraphics();

    myLButtonClick = false; //点击
    myLButtonPress = false; //按压
    myRButtonClick = false; //点击
    myRButtonPress = false; //按压

    myMouseFloat = false; //悬浮

    myBackImageFlag = false;
    myMaskImageFlag = false;

    myBackImage = nullptr;
    myTitleWords = nullptr;
    myMaskImage = nullptr;

    myBackImage = new MfxImage(myBuffGraphics, Gdiplus::Color::Snow, myRect);
    myTitleWords = new MfxWords(myBuffGraphics, title, myRect);
    myTitleWords->SetFormat(MFXWORDS_FORMATX_CENTER | MFXWORDS_FORMATY_CENTER);

    //注册控件 - lParam的值如果不为NULL，则UI不会注册这个控件！
    PostMessage(myUI->GetWnd(), MFXCONTROLEVENT_CONTROLCREATE, (WPARAM)this, lParam);
}

MicroFlakeX::MfxControl::MfxControl(MfxUI* father)
{
    MfxRegDef();
    MfxInitData(father, Gdiplus::Rect(0, 0, 200, 123.6), L"MfxBasicsControl", L"MfxBasicsControl");
}

MicroFlakeX::MfxControl::MfxControl(MfxUI* father, Gdiplus::Rect rect)
{
    MfxRegDef();
    MfxInitData(father, rect, L"MfxBasicsControl", L"MfxBasicsControl");
}

MicroFlakeX::MfxControl::MfxControl(MfxUI* father, std::wstring title)
{
    MfxRegDef();
    MfxInitData(father, Gdiplus::Rect(0, 0, 200, 123.6), L"MfxBasicsControl", title);
}

MicroFlakeX::MfxControl::MfxControl(MfxUI* father, Gdiplus::Rect rect, std::wstring title)
{
    MfxRegDef();
    MfxInitData(father, rect, L"MfxBasicsControl", title);
}

MicroFlakeX::MfxControl::~MfxControl()
{
    //解除UI注册
    PostMessage(myUI->GetWnd(), MFXCONTROLEVENT_CONTROLDELETE, (WPARAM)this, NULL);

    if (!myBackImageFlag)
        delete myBackImage;
    delete myTitleWords;
    if (!myMaskImageFlag)
        delete myMaskImage;
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

UINT MicroFlakeX::MfxControl::GetFloor()
{
    return myFloor;
}

UINT MicroFlakeX::MfxControl::SetFloor(UINT floor, LPARAM lParam)
{
    if (floor == myFloor) return myFloor;
    UINT retFloor = myFloor;
    myFloor = floor;
    PostMessage(myUI->GetWnd(), MFXCONTROLEVENT_FLOORCHANGE, (WPARAM)this, lParam);
    /* ____如果lParam不是NULL，则UI不响应____ */
    return retFloor;
}

std::wstring MicroFlakeX::MfxControl::GetType()
{
    return myType;
}

std::wstring MicroFlakeX::MfxControl::GetTitle()
{
    return myTitle;
}

std::wstring MicroFlakeX::MfxControl::SetTitle(std::wstring set)
{
    std::wstring retTitle = myTitle;
    myTitle = set;
    if(myTitleWords)
        myTitleWords->SetWords(myTitle);
    return retTitle;
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
    if(myBackImage)
        myBackImage->SetRect(set);
    if (myTitleWords)
        myTitleWords->SetRect(set);
    if (myMaskImage)
        myMaskImage->SetRect(set);
}

void MicroFlakeX::MfxControl::SetSize(Gdiplus::Size set)
{
    myRect.Width = set.Width;
    myRect.Height = set.Height;
    if (myBackImage)
        myBackImage->SetSize(set);
    if (myTitleWords)
        myTitleWords->SetSize(set);
    if (myMaskImage)
        myMaskImage->SetSize(set);
}

void MicroFlakeX::MfxControl::SetPoint(Gdiplus::Point set)
{
    myRect.X = set.X;
    myRect.Y = set.Y;
    if (myBackImage)
        myBackImage->SetPoint(set);
    if (myTitleWords)
        myTitleWords->SetPoint(set);
    if (myMaskImage)
        myMaskImage->SetPoint(set);
}

MicroFlakeX::MfxImage* MicroFlakeX::MfxControl::SetBackImage(MfxImage* set)
{
    MfxImage* retImage = myBackImage;
    myBackImageFlag = true;
    myBackImage = set;
    myBackImage->SetRect(myRect);
    return retImage;
}

MicroFlakeX::MfxImage* MicroFlakeX::MfxControl::GetBackImage()
{
    return myBackImage;
}

MicroFlakeX::MfxImage* MicroFlakeX::MfxControl::SetMaskImage(MfxImage* set)
{
    MfxImage* retImage = myMaskImage;
    myMaskImageFlag = true;
    myMaskImage = set;
    myMaskImage->SetRect(myRect);
    return retImage;
}

MicroFlakeX::MfxImage* MicroFlakeX::MfxControl::GetMaskImage()
{
    return myMaskImage;
}

/* ———————————————————————————————————————————— */
/* ——————————————下面的代码是默认响应———————————————————— */
/* ———————————————————————————————————————————— */
/* ———————————————————————————————————————————— */

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControl::MfxDefOnDrawBuffDC(WPARAM wParam, LPARAM lParam)
{
    if (myBackImage)
        myBackImage->Draw();
    if (myTitleWords)
        myTitleWords->Draw();
    if (myMaskImage)
        myMaskImage->Draw();
    return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControl::MfxDefOnDrawMainDC(WPARAM wParam, LPARAM lParam)
{
    return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControl::MfxDefOnMouseMove(WPARAM wParam, LPARAM lParam)
{
    Gdiplus::Point mousePos = Gdiplus::Point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
    //鼠标悬浮的时候，锁定本次移动的焦点直到本次移动结束
    if (myRect.Contains(mousePos) && (myUI->SetUserFocus(this) || myUI->GetUserFocus() == this))
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
    if (myRect.Contains(mousePos) && (myUI->SetUserFocus(this) || myUI->GetUserFocus() == this))
    {
        //锁定控件焦点直到松开按钮 - 请确定锁定的时候，焦点在自己身上！！
        myUI->LockUserFocus(this);
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
    //松开按钮
    myUI->FreeUserFocus(this);
    Gdiplus::Point mousePos = Gdiplus::Point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
    if (myRect.Contains(mousePos) && (myUI->SetUserFocus(this) || myUI->GetUserFocus() == this))
    {
        if (myLButtonClick == true)
        {
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
    //if (myUI->SetUserFocus(this))
    {
    //    return myUI->RecvControlEvent(this, MFXCONTROLEVENT_LDOUBLECLICK, wParam, lParam);
    }
    //else
    {
        return 0;
    }
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxControl::MfxDefOnRButtonDown(WPARAM wParam, LPARAM lParam)
{
    Gdiplus::Point mousePos = Gdiplus::Point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
    if (myRect.Contains(mousePos) && (myUI->SetUserFocus(this) || myUI->GetUserFocus() == this))
    {
        myUI->LockUserFocus(this);
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
    myUI->FreeUserFocus(this);
    Gdiplus::Point mousePos = Gdiplus::Point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
    if (myRect.Contains(mousePos) && (myUI->SetUserFocus(this) || myUI->GetUserFocus() == this))
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
    //if (myUI->SetUserFocus(this))
    {
    //    return myUI->RecvControlEvent(this, MFXCONTROLEVENT_RDOUBLECLICK, wParam, lParam);
    }
    //else
    {
        return 0;
    }

}
