#include "pch.h"
#include "MfxAppFramework.h"

void MicroFlakeX::MfxUI::MfxRegMessages()
{
    MfxCodeLock t_CodeLock(this);
    UI_CON_RECV_MSG(WM_DESTROY);
    UI_CON_RECV_MSG(WM_SIZE);

    UI_CON_RECV_MSG(WM_MOUSEMOVE);
    UI_CON_RECV_MSG(WM_LBUTTONDOWN);
    UI_CON_RECV_MSG(WM_LBUTTONUP);
    UI_CON_RECV_MSG(WM_RBUTTONDOWN);
    UI_CON_RECV_MSG(WM_RBUTTONUP);

    UI_CON_RECV_MSG(MfxUI_Message_SetPaper);

    UI_CON_RECV_MSG(MfxUI_Message_ResetPercentRect);
    UI_CON_RECV_MSG(MfxUI_Message_ClosePercentRect);

    UI_CON_RECV_MSG(MfxUI_Message_PaintBackDC);
    UI_CON_RECV_MSG(MfxUI_Message_PaintMaskDC);

    /* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
    /* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
    /* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

    myUnderFloor--;
	myCoverFloor++;

    UI_REG_MSG(WM_CREATE, MfxUI, __OnCreate, myCoverFloor);
    UI_REG_MSG(WM_DESTROY, MfxUI, __OnDestroy, myCoverFloor);

    UI_REG_MSG(WM_SIZE, MfxUI, __OnSize, myCoverFloor);
    UI_REG_MSG(WM_MOVE, MfxUI, __OnMove, myCoverFloor);


    UI_REG_MSG(WM_PAINT, MfxUI, __OnPaint, myCoverFloor);
    UI_REG_MSG(MfxUI_Message_PaintBackDC, MfxUI, __OnPaintBackDC, myCoverFloor);
    UI_REG_MSG(MfxUI_Message_PaintMaskDC, MfxUI, __OnPaintMaskDC, myCoverFloor);

    UI_REG_MSG(MfxUI_Message_ControlInsert, MfxUI, __OnControlInsert, myCoverFloor);
    UI_REG_MSG(MfxUI_Message_ControlRemove, MfxUI, __OnControlRemove, myCoverFloor);
    UI_REG_MSG(MfxControl_Message_ControlFloorChange, MfxUI, __OnControlFloorChange, myCoverFloor);

    UI_REG_MSG(WM_TIMER, MfxUI, __OnTimer, myCoverFloor);
    UI_REG_MSG(MfxUI_Message_AddTimer, MfxUI, __OnAddTimer, myCoverFloor);
    UI_REG_MSG(MfxUI_Message_RemoveTimer, MfxUI, __OnRemoveTimer, myCoverFloor);

    UI_REG_MSG(MfxControl_Message_ControlMessage, MfxUI, __OnControlMessage, myCoverFloor);
    UI_REG_MSG(MfxUI_Message_AddControlMessage, MfxUI, __OnAddControlMessage, myCoverFloor);
    UI_REG_MSG(MfxUI_Message_RemoveControlMessage, MfxUI, __OnRemoveControlMessage, myCoverFloor);

    UI_REG_MSG(MfxUI_Message_ResetPercentRect, MfxUI, __OnResetPercentRect, myCoverFloor);
    UI_REG_MSG(MfxUI_Message_ClosePercentRect, MfxUI, __OnClosePercentRect, myCoverFloor);

    UI_REG_MSG(MfxUI_Message_SetBackColor, MfxUI, __OnSetBackColor, myCoverFloor);
    UI_REG_MSG(MfxUI_Message_SetMaskColor, MfxUI, __OnSetMaskColor, myCoverFloor);
    UI_REG_MSG(MfxUI_Message_SetBackImage, MfxUI, __OnSetBackImage, myCoverFloor);
    UI_REG_MSG(MfxUI_Message_SetMaskImage, MfxUI, __OnSetMaskImage, myCoverFloor);
}

void MicroFlakeX::MfxUI::MfxUIInitData()
{
    MfxCodeLock t_CodeLock(this);
    myUnderFloor = 0;
    myCoverFloor = 0;

    myPercentRect_Check = true;

    myWnd = nullptr;

    myWndDc = nullptr;
    myBackDC = nullptr;
    myMaskDC = nullptr;

    myBackImage = nullptr;
    myMaskImage = nullptr;

    myMutexFocus = nullptr;
    myKeyboardFocus = nullptr;
    myMutexFocusLockFlag = false;
    myKeyboardFocusLockFag = false;

    myTestImage = nullptr;
    myWndGraphics = nullptr;
}

MicroFlakeX::MfxUI::MfxUI(GdipRect gdiRect, MfxStrW title)
{
    MfxCodeLock t_CodeLock(this);
    MfxUIInitData();
    MfxRegMessages();


    MfxGetApp()->MfxCreateWindowExW(
        this, gdiRect,
        NULL, MfxUI_Style_Normal,
        L"MfxNormalUI", title);
}

MicroFlakeX::MfxUI::MfxUI(GdipRect gdiRect, DWORD myStyle_EN, MfxStrW title)
{
    MfxCodeLock t_CodeLock(this);
    MfxUIInitData();
    MfxRegMessages();


    MfxGetApp()->MfxCreateWindowExW(
        this, gdiRect,
        NULL, myStyle_EN,
        L"MfxNormalUI", title);
}

MicroFlakeX::MfxUI::MfxUI(GdipRect gdiRect, DWORD myStyleEx_EN, DWORD myStyle_EN, MfxStrW myClass, MfxStrW title)
{
    MfxCodeLock t_CodeLock(this);
    MfxUIInitData();
    MfxRegMessages();


    MfxGetApp()->MfxCreateWindowExW(
        this, gdiRect,
        myStyleEx_EN, myStyle_EN,
        L"MfxNormalUI", title);
}

MicroFlakeX::MfxUI::~MfxUI()
{
    MfxCodeLock t_CodeLock(this);
    while (myControlVector.size())
    {
        delete myControlVector[0];
    }

    delete myBackImage;
    myBackImage = nullptr;
    delete myMaskImage;
    myMaskImage = nullptr;

    ReleaseDC(myWnd, myWndDc);
    myWndDc = nullptr;
    DeleteDC(myBackDC);
    myBackDC = nullptr;
    DeleteDC(myMaskDC);
    myMaskDC = nullptr;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::CreateSuccess()
{
    MfxCodeLock t_CodeLock(this);
    if (myWnd)
    {
        return MfxFine;
    }
    else
    {
        return MfxFail;
    }
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::ProcMessage(MfxMsg message, WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock t_CodeLock(this);
    SendMessageToControls(message, wParam, lParam, false);

    MfxReturn t_Ret = MfxFail;
    auto t_Iter = myMessageMap.find(message);
    if (t_Iter != myMessageMap.end())
    {
        if (!t_Iter->second->empty())
        {
            for (auto i : *(t_Iter->second))
            {
                t_Ret = (this->*i->myFunc)(wParam, lParam);
            }
            return t_Ret;
        }
    }
    return DefWindowProc(myWnd, message, wParam, lParam);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::SendMessageToControls(MfxMsg message, WPARAM wParam, LPARAM lParam, bool sort)
{
    MfxCodeLock t_CodeLock(this);
    MfxControl* t_FloatFocus = myMutexFocus;
    myMutexFocus = myMutexFocusLockFlag ? myMutexFocus : nullptr;

    if (myControlMessageSet.find(message) != myControlMessageSet.end())
    {
        if (sort)
        {
            for (int i = myControlVector.size() - 1; i >= 0; i--)
            {
                myControlVector[i]->ProcMessage(message, wParam, lParam);
            }
        }
        else
        {
            for (auto t_Iter : myControlVector)
            {
                t_Iter->ProcMessage(message, wParam, lParam);
            }
        }
        myMutexFocus = (myMutexFocus ? myMutexFocus : t_FloatFocus);
        return MfxFine;
    }
    else
    {
        myMutexFocus = (myMutexFocus ? myMutexFocus : t_FloatFocus);
        return MfxFail;
    }
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::ResetPercentRect()
{
    MfxCodeLock t_CodeLock(this);
    return ProcMessage(MfxUI_Message_ResetPercentRect, NULL, MAKELONG(myRect.Width, myRect.Height));
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::ClosePercentRect()
{
    MfxCodeLock t_CodeLock(this);
    return ProcMessage(MfxUI_Message_ClosePercentRect, NULL, MAKELONG(myRect.Width, myRect.Height));
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::ChickPercentRect()
{
    MfxCodeLock t_CodeLock(this);
    if (myPercentRect_Check)
    {
        return MfxFine;
    }
    else
    {
        return MfxFail;
    }
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::AddControl(MfxControl* set)
{
    MfxCodeLock t_CodeLock(this);
    return ProcMessage(MfxUI_Message_ControlInsert, (WPARAM)set, NULL);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::RemoveControl(MfxControl* set)
{
    MfxCodeLock t_CodeLock(this);
    return ProcMessage(MfxUI_Message_ControlRemove, (WPARAM)set, NULL);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::AddControlMessage(MfxControl* target, MfxMsg message, MfxUI_Func recv)
{
    MfxCodeLock t_CodeLock(this);
    MfxUI_ControlMessage_Key t_ControlMessage(target, message);
    return ProcMessage(MfxUI_Message_AddControlMessage, (WPARAM)&recv, (LPARAM)&t_ControlMessage);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::RemoveControlMessage(MfxControl* target, MfxMsg message)
{
    MfxCodeLock t_CodeLock(this);
    MfxUI_ControlMessage_Key t_ControlMessage(target, message);
    return ProcMessage(MfxUI_Message_RemoveControlMessage, NULL, (LPARAM)&t_ControlMessage);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::AddTimer(WPARAM timerID, clock_t delay, MfxUI_Func recv)
{
    MfxCodeLock t_CodeLock(this);
    MfxUI_Timer_Value t_TimerValue(delay, clock(), recv);
    return ProcMessage(MfxUI_Message_AddTimer, timerID, (LPARAM)&t_TimerValue);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::RemoveTimer(WPARAM cid)
{
    MfxCodeLock t_CodeLock(this);
    return ProcMessage(MfxUI_Message_RemoveTimer, cid, NULL);
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::GetWnd(HWND* ret)
{
    MfxCodeLock t_CodeLock(this);
    *ret = myWnd;
    return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::GetWndDC(HDC* ret)
{
    MfxCodeLock t_CodeLock(this);
    *ret = myWndDc;
    return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::GetBackDC(HDC* ret)
{
    MfxCodeLock t_CodeLock(this);
    *ret = myBackDC;
    return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::GetMaskDC(HDC* ret)
{
    MfxCodeLock t_CodeLock(this);
    *ret = myMaskDC;
    return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::GetRect(GdipRect* ret)
{
    MfxCodeLock t_CodeLock(this);
    *ret = myRect;
    return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::GetSize(GdipSize* ret)
{
    MfxCodeLock t_CodeLock(this);
    *ret = GdipSize(myRect.Width, myRect.Height);
    return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::GetPoint(GdipPoint* ret)
{
    MfxCodeLock t_CodeLock(this);
    *ret = GdipPoint(myRect.X, myRect.Y);
    return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::GetBackImage(MfxImage** ret)
{
    MfxCodeLock t_CodeLock(this);
    return myBackImage ? myBackImage->Clone(ret) : MfxFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::GetMaskImage(MfxImage** ret)
{
    MfxCodeLock t_CodeLock(this);
    return myMaskImage ? myMaskImage->Clone(ret) : MfxFail;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::SetRect(GdipRect set)
{
    MfxCodeLock t_CodeLock(this);
    return SetWindowPos(myWnd, NULL, set.X, set.Y, set.Width, set.Height, SWP_NOZORDER) ? MfxFine : MfxFail;;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::SetSize(GdipSize set)
{
    MfxCodeLock t_CodeLock(this);
    return SetWindowPos(myWnd, NULL, 0, 0, set.Width, set.Height, SWP_NOMOVE | SWP_NOZORDER) ? MfxFine : MfxFail;;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::SetPoint(GdipPoint set)
{
    MfxCodeLock t_CodeLock(this);
    return SetWindowPos(myWnd, NULL, set.X, set.Y, 0, 0, SWP_NOSIZE | SWP_NOZORDER) ? MfxFine : MfxFail;;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::SetBackColor(GdipColor set)
{
    MfxCodeLock t_CodeLock(this);
    return ProcMessage(MfxUI_Message_SetBackColor, NULL, (LPARAM)&set);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::SetMaskColor(GdipColor set)
{
    MfxCodeLock t_CodeLock(this);
    return ProcMessage(MfxUI_Message_SetMaskColor, NULL, (LPARAM)&set);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::SetBackImage(MfxImage* set)
{
    MfxCodeLock t_CodeLock(this);
    return ProcMessage(MfxUI_Message_SetBackImage, NULL, (LPARAM)set);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::SetMaskImage(MfxImage* set)
{
    MfxCodeLock t_CodeLock(this);
    return ProcMessage(MfxUI_Message_SetMaskImage, NULL, (LPARAM)set);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::SetBigIcon(MfxImage* set)
{
    GdipBitmap* t_Bitmap;
    set->GetShowBitmap(&t_Bitmap);

    HICON t_Icon;
    t_Bitmap->GetHICON(&t_Icon);
    delete t_Bitmap;
    return ProcMessage(WM_SETICON, ICON_BIG, (LPARAM)t_Icon);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::SetSmallIcon(MfxImage* set)
{
    GdipBitmap* t_Bitmap;
    set->GetShowBitmap(&t_Bitmap);

    HICON t_Icon;
    t_Bitmap->GetHICON(&t_Icon);
    delete t_Bitmap;
    return ProcMessage(WM_SETICON, ICON_SMALL, (LPARAM)t_Icon);
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::LockMutexFocus(MfxControl* set)
{
    MfxCodeLock t_CodeLock(this);
    myMutexFocus = set;
    myMutexFocusLockFlag = true;
    return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::UnLockMutexFocus()
{
    MfxCodeLock t_CodeLock(this);
    myMutexFocusLockFlag = false;
    return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::SetMutexFocus(MfxControl* set)
{
    MfxCodeLock t_CodeLock(this);
    if (!myMutexFocus && !myMutexFocusLockFlag)
    {
        myMutexFocus = set;
        return MfxFine;
    }
    else
    {
        return MfxFail;
    }
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::SetKeyboardFocus(MfxControl* set)
{
    MfxCodeLock t_CodeLock(this);
    if (!myMutexFocusLockFlag)
    {
        myKeyboardFocus = set;
        return MfxFine;
    }
    else
    {
        return MfxFail;
    }

}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::GetMutexFocus(MfxControl** ret)
{
    MfxCodeLock t_CodeLock(this);
    *ret = myMutexFocus;
    return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::GetKeyboardFocus(MfxControl** ret)
{
    MfxCodeLock t_CodeLock(this);
    *ret = myKeyboardFocus;
    return MfxFine;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::RemoveMessage(MfxMsg message, MfxStrW name)
{
    MfxCodeLock t_CodeLock(this);
    auto t_Iter = myMessageMap.find(message);
    if (t_Iter != myMessageMap.end())
    {
        for (auto i = t_Iter->second->begin(); i != t_Iter->second->end(); i++)
        {
            if ((*i)->myName == name)
            {
                t_Iter->second->erase(i);
                return MfxFine;
            }
        }
    }
    return MfxFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::InsertMessage(MfxMsg message, MfxUI_MessageMap_Value* msgValue)
{
    MfxCodeLock t_CodeLock(this);
    auto t_Iter = myMessageMap.find(message);
    if (t_Iter == myMessageMap.end())
    {
        auto t_AddVector = new MfxUI_MessageMap_Vector;
        t_Iter = myMessageMap.insert(MfxUI_MessageMap_elem(message, t_AddVector)).first;
    }

    t_Iter->second->push_back(msgValue);
    std::sort(t_Iter->second->begin(), t_Iter->second->end(), __MicroFlakeX::MfxUIMessageFloorCompare);

    return MfxFine;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnTest00(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock t_CodeLock(this);
    std::cout << "__OnTest00: wParam-" << wParam << " lParam-" << lParam << std::endl;
    return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnTest01(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock t_CodeLock(this);
    std::cout << "__OnTest01: wParam-" << wParam << " lParam-" << lParam << std::endl;
    return MfxFine;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnCreate(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock t_CodeLock(this);
    CREATESTRUCTA* t_Create = (CREATESTRUCTA*)lParam;

    myRect.X = t_Create->x;
    myRect.Y = t_Create->y;
    myRect.Width = t_Create->cx;
    myRect.Height = t_Create->cy;
    
    myWndDc = GetDC(myWnd);
    myBackDC = CreateCompatibleDC(myWndDc);
    myMaskDC = CreateCompatibleDC(myWndDc);

    GdipSize t_Size(GetSystemMetrics(SM_CXFULLSCREEN), GetSystemMetrics(SM_CYFULLSCREEN));
    DeleteObject(SelectObject(myBackDC, CreateCompatibleBitmap(myWndDc, t_Size.Width, t_Size.Height)));
    DeleteObject(SelectObject(myMaskDC, CreateCompatibleBitmap(myWndDc, t_Size.Width, t_Size.Height)));

    myTestImage = new GdipBitmap(t_Size.Width, t_Size.Height, PixelFormat32bppARGB);

    myWndGraphics = new GdipGraphics(myWnd);

    myBackImage = new MfxImage;

    myBackImage->SetRect(GdipRect(0, 0, t_Size.Width, t_Size.Height));
    myBackImage->FromColor(GdipColor::DimGray);
    //myBackImage->SetGraphics(myBackDC);
    myBackImage->SetDC(myBackDC);

    return 0;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnDestroy(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock t_CodeLock(this);
    PostQuitMessage(0); //潤崩��連儉桟
    return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnSize(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock t_CodeLock(this);
    GdipSize t_Size(LOWORD(lParam), HIWORD(lParam));

    myRect.Width = t_Size.Width;
    myRect.Height = t_Size.Height;

    if (myBackImage)
    {
        myBackImage->SetSize(t_Size);
    }

    if (myMaskImage)
    {
        myMaskImage->SetSize(t_Size);
    }
    PostMessageW(myWnd, WM_PAINT, NULL, NULL);
    return DefWindowProc(myWnd, WM_SIZE, wParam, lParam);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnMove(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock t_CodeLock(this);
    GdipPoint t_Point(LOWORD(lParam), HIWORD(lParam));

    myRect.X = t_Point.X;
    myRect.Y = t_Point.Y;

    return DefWindowProc(myWnd, WM_MOVE, wParam, lParam);
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnPaint(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock t_CodeLock(this);
    PAINTSTRUCT t_Paint;
    t_Paint.fErase = 1;

    HDC t_Dc = BeginPaint(myWnd, &t_Paint);

    __OnPaintBackDC(NULL, NULL);

    __OnPaintMaskDC(NULL, NULL);

    EndPaint(myWnd, &t_Paint);

    return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnPaintBackDC(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock t_CodeLock(this);
    if (myBackImage)
    {
        myBackImage->Draw();
    }
    //宸戦紙崙Main

    this->SendMessageToControls(MfxUI_Message_PaintBackDC, wParam, lParam, true);

    return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnPaintMaskDC(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock t_CodeLock(this);
    BitBlt(myMaskDC, 0, 0, myRect.Width, myRect.Height, myBackDC, 0, 0, SRCCOPY);
    //宸戦紙崙Mask

    this->SendMessageToControls(MfxUI_Message_PaintMaskDC, wParam, lParam, true);

    if (myMaskImage)
    {
        myMaskImage->Draw();
    }


    BitBlt(myWndDc, 0, 0, myRect.Width, myRect.Height, myMaskDC, 0, 0, SRCCOPY);
    //BitBlt(myWndDc, 0, 0, myRect.Width, myRect.Height, myBackDC, 0, 0, SRCCOPY);
    return MfxFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnControlInsert(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock t_CodeLock(this);
    if (wParam)
    {
        if (myControlSet.insert((MfxControl*)wParam).second)
        {
            myControlVector.push_back(((MfxControl*)wParam));
            MfxUI_Paper_Value t_PaperValue(this, myWnd, myBackDC, myMaskDC);

            ((MfxControl*)wParam)->ProcMessage(MfxUI_Message_SetPaper, NULL, (LPARAM)&t_PaperValue);
            if (myPercentRect_Check)
            {
                ((MfxControl*)wParam)->ProcMessage(MfxUI_Message_ResetPercentRect, NULL, MAKELONG(myRect.Width, myRect.Height));
            }

            std::sort(myControlVector.begin(), myControlVector.end(), __MicroFlakeX::MfxControlFloorCompare);
            PostMessageW(myWnd, WM_PAINT, NULL, NULL);
            return MfxFine;
        }
    }
    return MfxFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnControlRemove(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock t_CodeLock(this);
    if (wParam)
    {
        for (auto delIt = myControlVector.begin(); delIt != myControlVector.end(); delIt++)
        {
            if (*delIt == (MfxControl*)wParam)
            {
                MfxUI_Paper_Value t_PaperValue;
                ((MfxControl*)wParam)->ProcMessage(MfxUI_Message_SetPaper, NULL, (LPARAM)&t_PaperValue);
                myControlVector.erase(delIt);
                myControlSet.erase((MfxControl*)wParam);
                return MfxFine;
            }
        }
    }
    return MfxFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnControlFloorChange(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock t_CodeLock(this);
    std::sort(myControlVector.begin(), myControlVector.end(), __MicroFlakeX::MfxControlFloorCompare);
    return MfxFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnTimer(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock t_CodeLock(this);
    auto t_Iter = __myTimerMap.find(wParam);
    if (t_Iter != __myTimerMap.end())
    {
        (this->*t_Iter->second.recvFunc)((*t_Iter).second.delayTime, clock() - (*t_Iter).second.passTime);
        (*t_Iter).second.passTime = clock();
        return MfxFine;
    }
    return MfxFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnAddTimer(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock t_CodeLock(this);
    MfxUI_Timer_Value* t_TimerValue = (MfxUI_Timer_Value*)lParam;
    
    if (__myTimerMap.insert(MfxUI_Timer_Map_elem(wParam, *t_TimerValue)).second)
    {
        SetTimer(myWnd, wParam, t_TimerValue->delayTime, (TIMERPROC)NULL);
    }
    return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnRemoveTimer(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock t_CodeLock(this);
    __myTimerMap.erase(wParam);
    KillTimer(myWnd, wParam);
    return MfxFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnControlMessage(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock t_CodeLock(this);
    auto t_Iter = __myControlMessageMap.find(*(MfxUI_ControlMessage_Key*)wParam);
    if (t_Iter != __myControlMessageMap.end())
    {
        (this->*t_Iter->second)(((MfxUI_ControlMessage_Value*)lParam)->wParam, ((MfxUI_ControlMessage_Value*)lParam)->lParam);
        return MfxFine;
    }
    return MfxFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnAddControlMessage(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock t_CodeLock(this);
    return __myControlMessageMap.insert(
        MfxUI_ControlMessage_Map_elem(*(MfxUI_ControlMessage_Key*)lParam, *(MfxUI_Func*)wParam)).second ? MfxFine : MfxFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnRemoveControlMessage(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock t_CodeLock(this);
    return  __myControlMessageMap.erase(*(MfxUI_ControlMessage_Key*)lParam) ? MfxFine : MfxFail;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnResetPercentRect(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock t_CodeLock(this);
    myPercentRect_Check = true;
    return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnClosePercentRect(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock t_CodeLock(this);
    myPercentRect_Check = false;
    return MfxFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnSetBackColor(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock t_CodeLock(this);
    GdipColor* t_Set = (GdipColor*)lParam;
    if (myBackImage)
    {
        myBackImage->FromColor(*t_Set);
    }
    else
    {
        myBackImage = new MfxImage;
        myBackImage->SetRect(GdipRect(0, 0, myRect.Width, myRect.Height));
        myBackImage->FromColor(*t_Set);
        myBackImage->SetDC(myBackDC);
    }
    return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnSetMaskColor(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock t_CodeLock(this);
    GdipColor* t_Set = (GdipColor*)lParam;
    if (myMaskImage)
    {
        myMaskImage->FromColor(*t_Set);
    }
    else
    {
        myMaskImage = new MfxImage;
        myMaskImage->SetRect(GdipRect(0, 0, myRect.Width, myRect.Height));
        myMaskImage->FromColor(*t_Set);
        myMaskImage->SetDC(myBackDC);
    }
    return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnSetBackImage(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock t_CodeLock(this);
    MfxImage* t_Set = (MfxImage*)lParam;
    delete myBackImage;
    myBackImage = nullptr;
    if (t_Set)
    {
        (t_Set)->Clone(&myBackImage);
        myBackImage->SetRect(GdipRect(0, 0, myRect.Width, myRect.Height));
        myBackImage->SetDC(myBackDC);
    }
    return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnSetMaskImage(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock t_CodeLock(this);
    MfxImage* t_Set = (MfxImage*)lParam;

    delete myMaskImage;
    myMaskImage = nullptr;
    if (t_Set)
    {
        (t_Set)->Clone(&myMaskImage);
        myMaskImage->SetRect(GdipRect(0, 0, myRect.Width, myRect.Height));
        myMaskImage->SetDC(myMaskDC);
    }
    return MfxFine;
}