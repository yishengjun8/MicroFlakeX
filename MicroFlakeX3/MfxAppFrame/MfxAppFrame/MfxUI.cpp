#include "pch.h"
#include "MfxAppFrame.h"

MfxObject_Init(MfxUI)
MfxObject_EndInit(MfxUI, MfxBase, \
    \
    0, CreateSuccess, \
    \
    2, UIThread, \
    \
    3, ProcMessage, \
    4, SendMessageToFlakes, \
    \
    2, RemoveUIMessage, \
    2, PushBackUIMessage, \
    2, PushFrontUIMessage, \
    \
    0, OpenPercentRect, \
    0, ClosePercentRect, \
    0, ChickPercentRect, \
    \
    1, RemoveFlake, \
    1, InsertFlake, \
    \
    2, RemoveFlakeMessage, \
    2, PushBackFlakeMessage, \
    2, PushFrontFlakeMessage, \
    \
    1, RemoveTimer, \
    3, InsertTimer, \
    \
    1, LockMutexFocus, \
    0, UnLockMutexFocus, \
    \
    1, SetMutexFocus, \
    1, GetMutexFocus, \
    1, SetKeyboardFocus, \
    1, GetKeyboardFocus, \
    \
    1, GetWnd, \
    1, GetCanvas, \
    1, GetUIThreadID, \
    \
    1, GetRect, \
    1, GetSize, \
    1, GetPoint, \
    1, GetBackImage, \
    1, GetMaskImage, \
    \
    1, SetRect, \
    1, SetSize, \
    1, SetPoint, \
    \
    1, SetBackColor, \
    1, SetMaskColor, \
    1, SetBackImage, \
    1, SetMaskImage);


/********************************************************************************
*
*
*********************************************************************************/
void MicroFlakeX::MfxUI::MfxRegMessages()
{
    /********************************************************************************
    *
    *
    *********************************************************************************/

    //UI_ADDRECV_UIMSG(WM_NCCREATE, MfxUI, __OnNCCreat);

    UI_ADDRECV_UIMSG(WM_NCMOUSEMOVE, MfxUI, __OnNCMouseMove);
    UI_ADDRECV_UIMSG(WM_NCMOUSEHOVER, MfxUI, __OnNCMouseHover);

    UI_ADDRECV_UIMSG(WM_NCLBUTTONUP, MfxUI, __OnNCLButtonUp);
    UI_ADDRECV_UIMSG(WM_NCLBUTTONDOWN, MfxUI, __OnNCLButtonDown);
    UI_ADDRECV_UIMSG(WM_NCLBUTTONDBLCLK, MfxUI, __OnNCLButtonDblClk);

    UI_ADDRECV_UIMSG(WM_NCRBUTTONUP, MfxUI, __OnNCRButtonUp);
    UI_ADDRECV_UIMSG(WM_NCRBUTTONDOWN, MfxUI, __OnNCRButtonDown);
    UI_ADDRECV_UIMSG(WM_NCRBUTTONDBLCLK, MfxUI, __OnNCRButtonDblClk);


    

    UI_ADDRECV_UIMSG(WM_NCACTIVATE, MfxUI, __OnNCActivate);
    UI_ADDRECV_UIMSG(WM_NCPAINT, MfxUI, __OnNCPaint);
    UI_ADDRECV_UIMSG(WM_NCHITTEST, MfxUI, __OnNCHitTest);
    
    //UI_ADDRECV_UIMSG(WM_SYSCOMMAND, MfxUI, __OnSysCommand);

    //UI_ADDRECV_UIMSG(WM_ENTERMENULOOP, MfxUI, __OnINITMENUPOPUP);






    UI_ADDRECV_UIMSG(WM_CREATE, MfxUI, __OnCreate);
    UI_ADDRECV_UIMSG(WM_DESTROY, MfxUI, __OnDestroy);

    UI_ADDRECV_UIMSG(WM_SIZE, MfxUI, __OnSize);
    UI_ADDRECV_UIMSG(WM_MOVE, MfxUI, __OnMove);

    UI_ADDRECV_UIMSG(WM_TIMER, MfxUI, __OnTimer);

    UI_ADDRECV_UIMSG(WM_PAINT, MfxUI, __OnPaint);
    UI_ADDRECV_UIMSG(WM_ERASEBKGND, MfxUI, __OnEraseBackGrand);

    UI_ADDRECV_UIMSG(UI_MSG_PaintBack, MfxUI, __OnPaintBackDC);
    UI_ADDRECV_UIMSG(UI_MSG_PaintMask, MfxUI, __OnPaintMaskDC);

    UI_ADDRECV_UIMSG(UI_MSG_FlakeInsert, MfxUI, __OnFlakeInsert);
    UI_ADDRECV_UIMSG(UI_MSG_FlakeRemove, MfxUI, __OnFlakeRemove);
    UI_ADDRECV_UIMSG(UI_MSG_FlakeFloorChange, MfxUI, __OnFlakeFloorChange);

    UI_ADDRECV_UIMSG(UI_MSG_RemoveTimer, MfxUI, __OnRemoveTimer);
    UI_ADDRECV_UIMSG(UI_MSG_InsertTimer, MfxUI, __OnInsertTimer);

    UI_ADDRECV_UIMSG(UI_MSG_FlakeMessage, MfxUI, __OnFlakeMessage);

   
    UI_ADDRECV_UIMSG(UI_MSG_RemoveFlakeMessage, MfxUI, __OnRemoveFlakeMessage);
    UI_ADDRECV_UIMSG(UI_MSG_PushBackFlakeMessage, MfxUI, __OnPushBackFlakeMessage);
    UI_ADDRECV_UIMSG(UI_MSG_PushFrontFlakeMessage, MfxUI, __OnPushFrontFlakeMessage);

    UI_ADDRECV_UIMSG(UI_MSG_OpenPercentRect, MfxUI, __OnOpenPercentRect);
    UI_ADDRECV_UIMSG(UI_MSG_ClosePercentRect, MfxUI, __OnClosePercentRect);

    UI_ADDRECV_UIMSG(UI_MSG_SetBackColor, MfxUI, __OnSetBackColor);
    UI_ADDRECV_UIMSG(UI_MSG_SetMaskColor, MfxUI, __OnSetMaskColor);
    UI_ADDRECV_UIMSG(UI_MSG_SetBackImage, MfxUI, __OnSetBackImage);
    UI_ADDRECV_UIMSG(UI_MSG_SetMaskImage, MfxUI, __OnSetMaskImage);
}

void MicroFlakeX::MfxUI::MfxUIInitData()
{
    myWnd = nullptr;
    myUIThreadID = 0;

    myBackImage = nullptr;
    myMaskImage = nullptr;

    myMutexFocus = nullptr;
    myKeyboardFocus = nullptr;
    myMutexFocusLockFlag = false;
    myKeyboardFocusLockFlag = false;

    myPercentRectFlag = false;

    myBackColor.Reset(255, 0, 255, 255);
}

/**/
MfxReturn MicroFlakeX::MfxUI::UIThread(WPARAM wParam, LPARAM lParam)
{
    myUIThreadID = GetCurrentThreadId();

    MSG tMsg;

    while (GetMessage(&tMsg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&tMsg);
        ProcMessage(tMsg.message, tMsg.wParam, tMsg.lParam);
    }

    MessageBox(NULL, L"One UIThread Is Close", L"Close", 0);

    return tMsg.wParam;
}
/**/
/********************************************************************************
*
*
*
*
*********************************************************************************/
MicroFlakeX::MfxUI::MfxUI()
{
    MfxUIInitData();
    MfxRegMessages();

    MFXAPP->MfxCreateUIEx(this, MfxRect(60, 60, 400, 400), NULL, UI_WINDOWS_STYLE_Normal, MfxText("MfxNormalUI"), MfxText("MfxNormalUI"));
}

MicroFlakeX::MfxUI::MfxUI(MfxRect set, MfxString title)
{
    MfxUIInitData();
    MfxRegMessages();

    MFXAPP->MfxCreateUIEx(this, set, NULL, UI_WINDOWS_STYLE_Normal, MfxText("MfxNormalUI"), title);
}

MicroFlakeX::MfxUI::MfxUI(MfxRect set, DWORD myStyle_EN, MfxString title)
{
    MfxUIInitData();
    MfxRegMessages();

    MFXAPP->MfxCreateUIEx(this, set, NULL, myStyle_EN, MfxText("MfxNormalUI"), title);
}

MicroFlakeX::MfxUI::MfxUI(MfxRect set, DWORD myStyleEx_EN, DWORD myStyle_EN, MfxString myClass, MfxString title)
{
    MfxUIInitData();
    MfxRegMessages();

    MFXAPP->MfxCreateUIEx(this, set, myStyleEx_EN, myStyle_EN, MfxText("MfxNormalUI"), title);
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MicroFlakeX::MfxUI::~MfxUI()
{
    MfxCodeLock(this);
    SendMessage(myWnd, WM_CLOSE, 0, 0);

    SafeDelete(myBackImage);
    SafeDelete(myMaskImage);
}

MfxReturn MicroFlakeX::MfxUI::CreateSuccess()
{
    return myWnd ? Mfx_Return_Fine : Mfx_Return_Fail;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::ProcMessage(MfxMessage message, WPARAM wParam, LPARAM lParam)
{
    /* 这里添加识别 - 耗时的全部移交到UI线程内处理 */
    MfxReturn t_Ret = Mfx_Return_Fail;

    SendMessageToFlakes(message, wParam, lParam);

    auto t_Iter = myMessageMap.find(message);
    if (t_Iter != myMessageMap.end())
    {
        if (!t_Iter->second.empty())
        {
            for (auto i : (t_Iter->second))
            {
                t_Ret = (this->*i->recvFunc)(wParam, lParam);
            }
;
            return t_Ret;
        }
    }

    return DefWindowProc(myWnd, message, wParam, lParam);
}

MfxReturn MicroFlakeX::MfxUI::SendMessageToFlakes(MfxMessage message, WPARAM wParam, LPARAM lParam, bool sort)
{
    //True 从后往前
    //False 从前往后
    MfxReturn t_Ret = Mfx_Return_Fail;
    MfxFlake* t_FloatFocus = myMutexFocus;
    myMutexFocus = myMutexFocusLockFlag ? myMutexFocus : nullptr;

    if (sort)
    {
        for (int i = myFlakeDeque.size() - 1; i >= 0; i--)
        {
            t_Ret = myFlakeDeque[i]->ProcMessage(message, wParam, lParam);
        }
    }
    else
    {
        for (auto t_Iter : myFlakeDeque)
        {
            t_Ret = t_Iter->ProcMessage(message, wParam, lParam);
        }
    }

    //myMutexFocus = (myMutexFocus ? myMutexFocus : t_FloatFocus);
    return t_Ret;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::RemoveUIMessage(MfxMessage message, MfxString recvFuncName)
{
    MfxCodeLock(this);

    auto t_Iter = myMessageMap.find(message);
    if (t_Iter != myMessageMap.end())
    {
        for (auto i = t_Iter->second.begin(); i != t_Iter->second.end(); i++)
        {
            if ((*i)->myRecvFuncName == recvFuncName)
            {
                delete* i;
                t_Iter->second.erase(i);
                return Mfx_Return_Fine;
            }
        }
    }

    return Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxUI::PushBackUIMessage(MfxMessage message, UI_UIMsg_RecvFunc_Infor* msgValue)
{
    MfxCodeLock(this);

Begin:
    auto t_Iter = myMessageMap.find(message);
    if (t_Iter == myMessageMap.end())
    {
        t_Iter = myMessageMap.insert(UI_UIMsg_Map_Elem(message, UI_UIMsg_RecvFunc_Infor_Deque())).first;
        goto Begin;
    }
    else
    {
        t_Iter->second.push_back(msgValue);
    }

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::PushFrontUIMessage(MfxMessage message, UI_UIMsg_RecvFunc_Infor* msgValue)
{
    MfxCodeLock(this);

Begin:
    auto t_Iter = myMessageMap.find(message);
    if (t_Iter == myMessageMap.end())
    {
        t_Iter = myMessageMap.insert(UI_UIMsg_Map_Elem(message, UI_UIMsg_RecvFunc_Infor_Deque())).first;
        goto Begin;
    }
    else
    {
        t_Iter->second.push_front(msgValue);
    }

    return Mfx_Return_Fine;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::OpenPercentRect()
{
    return ProcMessage(UI_MSG_OpenPercentRect, NULL, NULL);
}

MfxReturn MicroFlakeX::MfxUI::ClosePercentRect()
{
    return ProcMessage(UI_MSG_ClosePercentRect, NULL, NULL);
}

MfxReturn MicroFlakeX::MfxUI::ChickPercentRect()
{
    return  myPercentRectFlag ? Mfx_Return_Fine : Mfx_Return_Fail;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::RemoveFlake(MfxFlake* set)
{
    return ProcMessage(UI_MSG_FlakeRemove, (WPARAM)set, NULL);
}

MfxReturn MicroFlakeX::MfxUI::InsertFlake(MfxFlake* set)
{
    return ProcMessage(UI_MSG_FlakeInsert, (WPARAM)set, NULL);
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::RemoveFlakeMessage(UI_FlakeMsg_Infor message, MfxString recvFuncName)
{
    return ProcMessage(UI_MSG_RemoveFlakeMessage, (WPARAM)&message, (LPARAM)&recvFuncName);
}

MfxReturn MicroFlakeX::MfxUI::PushBackFlakeMessage(UI_FlakeMsg_Infor message, UI_UIMsg_RecvFunc_Infor* msgValue)
{
    return ProcMessage(UI_MSG_PushBackFlakeMessage, (WPARAM)&message, (LPARAM)msgValue);
}

MfxReturn MicroFlakeX::MfxUI::PushFrontFlakeMessage(UI_FlakeMsg_Infor message, UI_UIMsg_RecvFunc_Infor* msgValue)
{
    return ProcMessage(UI_MSG_PushFrontFlakeMessage, (WPARAM)&message, (LPARAM)msgValue);
}



/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::RemoveTimer(WPARAM setID)
{
    return ProcMessage(UI_MSG_RemoveTimer, setID, NULL);
}

MfxReturn MicroFlakeX::MfxUI::InsertTimer(WPARAM setID, clock_t delay, pUIRecvFunc recv)
{
    return ProcMessage(UI_MSG_InsertTimer, setID, (LPARAM)(new UI_UITimer_Infor(delay, clock(), recv)));
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::LockMutexFocus(MfxFlake* set)
{
    MfxCodeLock(this);
    myMutexFocus = set;
    myMutexFocusLockFlag = true;
    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::UnLockMutexFocus()
{
    MfxCodeLock(this);
    myMutexFocusLockFlag = false;
    return Mfx_Return_Fine;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::SetMutexFocus(MfxFlake* set)
{
    MfxCodeLock(this);
    if (!myMutexFocus && !myMutexFocusLockFlag)
    {
        myMutexFocus = set;
        return Mfx_Return_Fine;
    }
    else
    {
        return Mfx_Return_Fail;
    }
}

MfxReturn MicroFlakeX::MfxUI::GetMutexFocus(MfxFlake** ret)
{
    MfxCodeLock(this);
    *ret = myMutexFocus;
    return Mfx_Return_Fine;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::SetKeyboardFocus(MfxFlake* set)
{
    MfxCodeLock(this);
    if (!myMutexFocusLockFlag)
    {
        myKeyboardFocus = set;
        return Mfx_Return_Fine;
    }
    else
    {
        return Mfx_Return_Fail;
    }
}

MfxReturn MicroFlakeX::MfxUI::GetKeyboardFocus(MfxFlake** ret)
{
    MfxCodeLock(this);
    *ret = myKeyboardFocus;
    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::UnionInvalidateRect(MfxRect* set)
{
    RECT tRECT;
    set->GetRECT(&tRECT);

    InvalidateRect(myWnd, &tRECT, TRUE);

    myInvalidateRect.Union(set, &myInvalidateRect);

    return Mfx_Return_Fine;
}


/********************************************************************************
* 
* 
* 
* 
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::GetWnd(HWND* ret)
{
    *ret = myWnd;
    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::GetUIThreadID(DWORD* ret)
{
    *ret = myUIThreadID;
    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::GetCanvas(MfxCanvas** ret)
{
    *ret = &myCanvas;
    return Mfx_Return_Fine;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::GetRect(MfxRect* ret)
{
    myRect.GetRect(ret);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::GetSize(MfxSize* ret)
{
    myRect.GetSize(ret);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::GetPoint(MfxPoint* ret)
{
    myRect.GetPoint(ret);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::GetBackColor(MfxColor* ret)
{
    myBackColor.GetColor(ret);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::GetMaskColor(MfxColor* ret)
{
    myMaskColor.GetColor(ret);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::GetBackImage(MfxImage** ret)
{
    return myBackImage ? myBackImage->Clone(ret) : Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxUI::GetMaskImage(MfxImage** ret)
{
    return myMaskImage ? myMaskImage->Clone(ret) : Mfx_Return_Fail;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::SetRect(MfxRect* set)
{
    MfxCodeLock(this);

    return SetWindowPos(myWnd, NULL, set->myX, set->myY, set->myWidth, set->myHeight, SWP_NOZORDER) ? Mfx_Return_Fine : Mfx_Return_Fail;;
}

MfxReturn MicroFlakeX::MfxUI::SetSize(MfxSize* set)
{
    MfxCodeLock(this);

    return SetWindowPos(myWnd, NULL, 0, 0, set->myWidth, set->myHeight, SWP_NOMOVE | SWP_NOZORDER) ? Mfx_Return_Fine : Mfx_Return_Fail;;
}

MfxReturn MicroFlakeX::MfxUI::SetPoint(MfxPoint* set)
{
    MfxCodeLock(this);

    return SetWindowPos(myWnd, NULL, set->myX, set->myY, 0, 0, SWP_NOSIZE | SWP_NOZORDER) ? Mfx_Return_Fine : Mfx_Return_Fail;;
}

MfxReturn MicroFlakeX::MfxUI::SetBackColor(MfxColor* set)
{
    return ProcMessage(UI_MSG_SetBackColor, NULL, (LPARAM)set);
}

MfxReturn MicroFlakeX::MfxUI::SetMaskColor(MfxColor* set)
{
    return ProcMessage(UI_MSG_SetMaskColor, NULL, (LPARAM)set);
}

MfxReturn MicroFlakeX::MfxUI::SetBackImage(MfxImage* set)
{
    return ProcMessage(UI_MSG_SetBackImage, NULL, (LPARAM)set);
}

MfxReturn MicroFlakeX::MfxUI::SetMaskImage(MfxImage* set)
{
    return ProcMessage(UI_MSG_SetMaskImage, NULL, (LPARAM)set);
}

/**
MfxReturn MicroFlakeX::MfxUI::SetBigIcon(MfxImage* set)
{
    MfxBitmap* t_Bitmap;
    set->GetShowBitmap(&t_Bitmap);

    HICON t_Icon;
    t_Bitmap->GetHICON(&t_Icon);
    delete t_Bitmap;
    return ProcMessage(WM_SETICON, ICON_BIG, (LPARAM)t_Icon);
}

MfxReturn MicroFlakeX::MfxUI::SetSmallIcon(MfxImage* set)
{
    MfxBitmap* t_Bitmap;
    set->GetShowBitmap(&t_Bitmap);

    HICON t_Icon;
    t_Bitmap->GetHICON(&t_Icon);
    delete t_Bitmap;
    return ProcMessage(WM_SETICON, ICON_SMALL, (LPARAM)t_Icon);
}
/**/


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::__OnTest00(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);

    std::cout << "__OnTest00: wParam-" << wParam << " lParam-" << lParam << std::endl;

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::__OnTest01(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);

    std::cout << "__OnTest01: wParam-" << wParam << " lParam-" << lParam << std::endl;

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::__OnNCMouseMove(WPARAM wParam, LPARAM lParam)
{
    if (myMutexFocus)
    {
        return 0;
    }
    return DefWindowProc(myWnd, WM_NCMOUSEMOVE, wParam, lParam);
}

MfxReturn MicroFlakeX::MfxUI::__OnNCMouseHover(WPARAM wParam, LPARAM lParam)
{
    if (myMutexFocus)
    {
        return 0;
    }
    return DefWindowProc(myWnd, WM_NCMOUSEHOVER, wParam, lParam);
}

MfxReturn MicroFlakeX::MfxUI::__OnNCLButtonUp(WPARAM wParam, LPARAM lParam)
{
    if (myMutexFocus)
    {
        return 0;
    }
    return DefWindowProc(myWnd, WM_NCLBUTTONUP, wParam, lParam);
}

MfxReturn MicroFlakeX::MfxUI::__OnNCLButtonDown(WPARAM wParam, LPARAM lParam)
{
    if (myMutexFocus)
    {
        return 0;
    }
    return DefWindowProc(myWnd, WM_NCLBUTTONDOWN, wParam, lParam);
}

MfxReturn MicroFlakeX::MfxUI::__OnNCLButtonDblClk(WPARAM wParam, LPARAM lParam)
{
    if (myMutexFocus)
    {
        return 0;
    }
    return DefWindowProc(myWnd, WM_NCLBUTTONDBLCLK, wParam, lParam);
}

MfxReturn MicroFlakeX::MfxUI::__OnNCRButtonUp(WPARAM wParam, LPARAM lParam)
{
    if (myMutexFocus)
    {
        return 0;
    }
    return DefWindowProc(myWnd, WM_NCRBUTTONUP, wParam, lParam);
}

MfxReturn MicroFlakeX::MfxUI::__OnNCRButtonDown(WPARAM wParam, LPARAM lParam)
{
    if (myMutexFocus)
    {
        return 0;
    }
    return DefWindowProc(myWnd, WM_NCRBUTTONDOWN, wParam, lParam);
}

MfxReturn MicroFlakeX::MfxUI::__OnNCRButtonDblClk(WPARAM wParam, LPARAM lParam)
{
    if (myMutexFocus)
    {
        return 0;
    }
    return DefWindowProc(myWnd, WM_NCRBUTTONDBLCLK, wParam, lParam);
}



MfxReturn MicroFlakeX::MfxUI::__OnNCActivate(WPARAM wParam, LPARAM lParam)
{
    return wParam ? 0 : 1;
}


MfxReturn MicroFlakeX::MfxUI::__OnNCPaint(WPARAM wParam, LPARAM lParam)
{
    //HDC hdc = GetWindowDC(myWnd);

    //RECT rcWin;
    //GetWindowRect(myWnd, &rcWin);
    //OffsetRect(&rcWin, -rcWin.left, -rcWin.top);

    //hdc = GetDCEx(myWnd, (HRGN)wParam, DCX_WINDOW | DCX_INTERSECTRGN);

    //RECT rcWin;
    //GetWindowRect(myWnd, &rcWin);
    //HICON m_hIcon;
    //myBackImage->GetHICON(&m_hIcon);
    //MfxRect tRect;
    //tRect.SetRECT(&rcWin);
    //DrawIconEx(hdc, tRect.myX, tRect.myY, m_hIcon, tRect.myWidth, tRect.myHeight, 0, 0, DI_IMAGE);

    //DeleteObject(m_hIcon);
    //ReleaseDC(myWnd, hdc);
    /**
    HICON m_hIcon;
    myBackImage->GetHICON(&m_hIcon);


    MfxRect tRect;


    SIZE sizeButton{ GetSystemMetrics(SM_CXSIZE), GetSystemMetrics(SM_CYSIZE) };// 27,27

    HDC pWinDC = GetWindowDC(myWnd);
    RECT rcWin;
    GetWindowRect(myWnd, &rcWin);
    OffsetRect(&rcWin, -rcWin.left, -rcWin.top);
    // 3 pixel
    HBRUSH hbr = CreateSolidBrush(RGB(255, 0, 0));
    hbr = (HBRUSH)SelectObject(pWinDC, hbr);

    rcWin.top -= 3;
    rcWin.left -= 3;
    rcWin.right -= 3;
    rcWin.bottom -= 3;

    rcWin.bottom = GetSystemMetrics(SM_CYCAPTION) + rcWin.top;

    SetBkMode(pWinDC, TRANSPARENT);
    SetTextColor(pWinDC, RGB(255, 255, 255));
    TextOut(pWinDC, 40, 6, L"SelfDraw Cap", 12);

    //    m_hIcon DrawIcon
    LONG style = GetWindowLong(myWnd, GWL_STYLE);

    if (style & WS_SYSMENU) // 0x00080000L
    {
      

        DrawIconEx(pWinDC, 6, 6, m_hIcon, 16, 16, 0, 0, DI_IMAGE);
        //
        RECT rc;
        rc.right = rcWin.right - rcWin.left;
        rc.left = rc.right - sizeButton.cx + 2;
        rc.top = rcWin.top + 3;
        rc.bottom = sizeButton.cy + 3;
        //
        DrawFrameControl(pWinDC, &rc, DFC_CAPTION, DFCS_CAPTIONCLOSE);

        if ((style & WS_MAXIMIZEBOX) || (style & WS_MINIMIZEBOX))
        {
            rc.left += -sizeButton.cx;
            rc.right += -sizeButton.cx;

            if (style & WS_MAXIMIZEBOX)
            {
                if (IsZoomed(myWnd))
                {
                    tRect.SetRECT(&rc);
                    DrawIconEx(pWinDC, tRect.myX, tRect.myY, m_hIcon, tRect.myWidth, tRect.myHeight, 0, 0, DI_IMAGE);
                }
                //DrawFrameControl(pWinDC, &rc, DFC_CAPTION, DFCS_CAPTIONRESTORE);
                else
                {
                    tRect.SetRECT(&rc);
                    DrawIconEx(pWinDC, tRect.myX, tRect.myY, m_hIcon, tRect.myWidth, tRect.myHeight, 0, 0, DI_IMAGE);
                }
                //DrawFrameControl(pWinDC, &rc, DFC_CAPTION, DFCS_CAPTIONMAX);
            }
            else
            {
                tRect.SetRECT(&rc);
                DrawIconEx(pWinDC, tRect.myX, tRect.myY, m_hIcon, tRect.myWidth, tRect.myHeight, 0, 0, DI_IMAGE);
            }
               // DrawFrameControl(pWinDC, &rc, DFC_CAPTION, DFCS_CAPTIONMAX | DFCS_INACTIVE);

            rc.left += -sizeButton.cx + 2;
            rc.right += -sizeButton.cx + 2;

            if (style & WS_MINIMIZEBOX)
            {
                tRect.SetRECT(&rc);
                DrawIconEx(pWinDC, tRect.myX, tRect.myY, m_hIcon, tRect.myWidth, tRect.myHeight, 0, 0, DI_IMAGE);
            }
                //DrawFrameControl(pWinDC, &rc, DFC_CAPTION, DFCS_CAPTIONMIN);
            else
            {
                tRect.SetRECT(&rc);
                DrawIconEx(pWinDC, tRect.myX, tRect.myY, m_hIcon, tRect.myWidth, tRect.myHeight, 0, 0, DI_IMAGE);
            }
                //DrawFrameControl(pWinDC, &rc, DFC_CAPTION, DFCS_CAPTIONMIN | DFCS_INACTIVE);
        }
    }
    //
    ReleaseDC(myWnd, pWinDC);
    /**/
    return 1;
}

MfxReturn MicroFlakeX::MfxUI::__OnNCHitTest(WPARAM wParam, LPARAM lParam)
{
    auto a = DefWindowProcW(myWnd, WM_NCHITTEST, wParam, lParam);

    if (a == HTMINBUTTON
        || a == HTMAXBUTTON
        || a == HTHELP
        || a == HTCLOSE
        )
    {
        return HTCAPTION;
    }

    return a;
}

MfxReturn MicroFlakeX::MfxUI::__OnSysCommand(WPARAM wParam, LPARAM lParam)
{

    return DefWindowProc(myWnd, WM_SYSCOMMAND, wParam, lParam);
}

MfxReturn MicroFlakeX::MfxUI::__OnINITMENUPOPUP(WPARAM wParam, LPARAM lParam)
{
    return 0;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::__OnCreate(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    //CREATESTRUCTA* t_Create = (CREATESTRUCTA*)lParam;
    //myRect.Reset(t_Create->x, t_Create->y, t_Create->cx, t_Create->cy);

    RECT rcWin;
    GetWindowRect(myWnd, &rcWin);
    myRect.SetRECT(&rcWin);
   

    MfxSize tSize(myRect.myWidth, myRect.myHeight);
    MfxRect tRect(0, 0, myRect.myWidth, myRect.myHeight);

    myCanvas.SetDC(GetWindowDC(myWnd));
    myCanvas.SetSize(&tSize);

    myBackImage = new MfxImage(&myBackColor, &tRect);
    myBackImage->SetCanvas(&myCanvas);

    while (!myUIThreadID);

    HRGN tRNG = CreateRectRgn(0, 0, rcWin.right - rcWin.left, rcWin.bottom - rcWin.top);

    SetWindowRgn(myWnd, tRNG, TRUE);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::__OnDestroy(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);

    //终结UI线程
    PostThreadMessage(myUIThreadID, WM_QUIT, NULL, NULL);

    return Mfx_Return_Fine;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::__OnSize(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    //MfxSize tSize(LOWORD(lParam), HIWORD(lParam));

    RECT rcWin;
    GetWindowRect(myWnd, &rcWin);
    myRect.SetRECT(&rcWin);

    MfxSize tSize;
    myRect.GetSize(&tSize);

    myCanvas.SetSize(&tSize);

    if (myBackImage)
    {
        myBackImage->SetSize(&tSize);
    }
    if (myMaskImage)
    {
        myMaskImage->SetSize(&tSize);
    }

    HRGN tRNG = CreateRectRgn(0, 0, rcWin.right - rcWin.left, rcWin.bottom - rcWin.top);

    SetWindowRgn(myWnd, tRNG, TRUE);

    UnionInvalidateRect(&myRect);

    return DefWindowProc(myWnd, WM_SIZE, wParam, lParam);
}

MfxReturn MicroFlakeX::MfxUI::__OnMove(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);

    //myRect.myX = LOWORD(lParam);
   // myRect.myY = HIWORD(lParam);

    RECT rcWin;
    GetWindowRect(myWnd, &rcWin);
    myRect.SetRECT(&rcWin);

    UnionInvalidateRect(&myRect);

    return DefWindowProc(myWnd, WM_MOVE, wParam, lParam);
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::__OnPaint(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);

    PAINTSTRUCT t_Paint{0};

    HDC t_Dc = BeginPaint(myWnd, &t_Paint);

    bool isEmpty = true;
    myInvalidateRect.IsEmpty(&isEmpty);
    if (!isEmpty)
    {
        myCanvas.PaintBegin(&myInvalidateRect);

        ProcMessage(UI_MSG_PaintBack, NULL, NULL);

        ProcMessage(UI_MSG_PaintMask, NULL, NULL);

        myCanvas.PaintFinish();

        myInvalidateRect.Reset(0, 0, 0, 0);
    }

    EndPaint(myWnd, &t_Paint);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::__OnEraseBackGrand(WPARAM wParam, LPARAM lParam)
{
    return 1;
}

MfxReturn MicroFlakeX::MfxUI::__OnPaintBackDC(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    if (myBackImage)
    {
        myBackImage->Paint();
    }

    //这里绘制Main
    SendMessageToFlakes(FLAKE_MSG_PaintBack, wParam, lParam, true);
    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::__OnPaintMaskDC(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);

    //这里绘制Mask
    SendMessageToFlakes(FLAKE_MSG_PaintMask, wParam, lParam, true);

    if (myMaskImage)
    {
        myMaskImage->Paint();
    }
    return Mfx_Return_Fine;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::__OnFlakeInsert(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);

    if (wParam)
    {
        if (myFlakeSet.insert((MfxFlake*)wParam).second)
        {
            myFlakeDeque.push_back(((MfxFlake*)wParam));
            Paper_Infor t_PaperValue(this, myWnd, &myCanvas, myUIThreadID);
            ((MfxFlake*)wParam)->ProcMessage(FLAKE_MSG_SetPaper, NULL, (LPARAM)&t_PaperValue);

            PostMessage(myWnd, UI_MSG_FlakeFloorChange, NULL, NULL);
            InvalidateRect(myWnd, NULL, TRUE);
            return Mfx_Return_Fine;
        }
    }

    return Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxUI::__OnFlakeRemove(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);

    if (wParam)
    {
        for (auto delIt = myFlakeDeque.begin(); delIt != myFlakeDeque.end(); delIt++)
        {
            if (*delIt == (MfxFlake*)wParam)
            {
                Paper_Infor t_PaperValue;
                ((MfxFlake*)wParam)->ProcMessage(FLAKE_MSG_SetPaper, NULL, (LPARAM)&t_PaperValue);
                myFlakeDeque.erase(delIt);
                myFlakeSet.erase((MfxFlake*)wParam);
                
                PostMessage(myWnd, UI_MSG_FlakeFloorChange, NULL, NULL);
                InvalidateRect(myWnd, NULL, TRUE);
                return Mfx_Return_Fine;
            }
        }
    }

    return Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxUI::__OnFlakeFloorChange(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);

    std::sort(myFlakeDeque.begin(), myFlakeDeque.end(), pFloorCompare<MfxFlake>);

    return Mfx_Return_Fine;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::__OnTimer(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);

    auto t_Iter = myTimerMap.find(wParam);
    if (t_Iter != myTimerMap.end())
    {
        (this->*t_Iter->second->recvFunc)(NULL, (LPARAM)t_Iter->second);

        return Mfx_Return_Fine;
    }

    return Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxUI::__OnInsertTimer(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);

    if (myTimerMap.insert(UI_UITimer_Infor_Map_Elem(wParam, (UI_UITimer_Infor*)lParam)).second)
    {
        SetTimer(myWnd, wParam, ((UI_UITimer_Infor*)lParam)->delayTime, (TIMERPROC)NULL);

        return Mfx_Return_Fine;
    }

    return Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxUI::__OnRemoveTimer(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);

    auto iter = myTimerMap.find(wParam);
    if (iter != myTimerMap.end())
    {
        KillTimer(myWnd, wParam);

        delete iter->second;

        myTimerMap.erase(wParam);

        return Mfx_Return_Fine;
    }

    return Mfx_Return_Fail;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::__OnFlakeMessage(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);

    UI_FlakeMsg_Infor* tFlakeMsg_Infor = (UI_FlakeMsg_Infor*)wParam;
    UI_FlakeMsg_Value* tFlakeMsg_Value = (UI_FlakeMsg_Value*)lParam;

    auto t_Ret = Mfx_Return_Fail;
    auto t_Iter = myFlakeMessageMap.find(*tFlakeMsg_Infor);
    if (t_Iter != myFlakeMessageMap.end())
    {
        if (!t_Iter->second.empty())
        {
            for (auto i : (t_Iter->second))
            {
                t_Ret = (this->*i->recvFunc)(wParam, lParam);
            }
        }
    }

    delete tFlakeMsg_Infor;
    delete tFlakeMsg_Value;

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::__OnRemoveFlakeMessage(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);

    UI_FlakeMsg_Infor* tFlakeMsg_Infor = (UI_FlakeMsg_Infor*)wParam;
    MfxString* tRecvFuncName = (MfxString*)lParam;

    auto t_Iter = myFlakeMessageMap.find(*tFlakeMsg_Infor);
    if (t_Iter != myFlakeMessageMap.end())
    {
        for (auto i = t_Iter->second.begin(); i != t_Iter->second.end(); i++)
        {
            if ((*i)->myRecvFuncName == *tRecvFuncName)
            {
                delete* i;
                t_Iter->second.erase(i);
                return Mfx_Return_Fine;
            }
        }
    }

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::__OnPushBackFlakeMessage(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);

    UI_FlakeMsg_Infor* tFlakeMsg_Infor = (UI_FlakeMsg_Infor*)wParam;
    UI_UIMsg_RecvFunc_Infor* tRecvFunc_Infor = (UI_UIMsg_RecvFunc_Infor*)lParam;

Begin:
    auto t_Iter = myFlakeMessageMap.find(*tFlakeMsg_Infor);
    if (t_Iter == myFlakeMessageMap.end())
    {
        t_Iter = myFlakeMessageMap.insert(UI_FlakeMsg_Map_Elem(*tFlakeMsg_Infor, UI_UIMsg_RecvFunc_Infor_Deque())).first;
        goto Begin;
    }
    else
    {
        t_Iter->second.push_back(tRecvFunc_Infor);
    }

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::__OnPushFrontFlakeMessage(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);

    UI_FlakeMsg_Infor* tFlakeMsg_Infor = (UI_FlakeMsg_Infor*)wParam;
    UI_UIMsg_RecvFunc_Infor* tRecvFunc_Infor = (UI_UIMsg_RecvFunc_Infor*)lParam;

Begin:
    auto t_Iter = myFlakeMessageMap.find(*tFlakeMsg_Infor);
    if (t_Iter == myFlakeMessageMap.end())
    {
        t_Iter = myFlakeMessageMap.insert(UI_FlakeMsg_Map_Elem(*tFlakeMsg_Infor, UI_UIMsg_RecvFunc_Infor_Deque())).first;
        goto Begin;
    }
    else
    {
        t_Iter->second.push_front(tRecvFunc_Infor);
    }

    return Mfx_Return_Fine;
}

/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::__OnOpenPercentRect(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);

    myPercentRectFlag = true;

    SendMessageToFlakes(FLAKE_MSG_OpenPercentRect, NULL, NULL);

    return Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxUI::__OnClosePercentRect(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);

    myPercentRectFlag = false;

    return Mfx_Return_Fine;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::__OnSetBackColor(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);

    myBackColor = (MfxColor*)lParam;

    if (myBackImage)
    {
        MfxSize tSize(myRect);

        myBackImage->FromColor(&myBackColor, &tSize);
    }
    else
    {
        MfxRect tRect(0, 0, myRect.myWidth, myRect.myHeight);

        myBackImage = new MfxImage(&myBackColor, &tRect);

        myBackImage->SetCanvas(&myCanvas);
    }

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::__OnSetMaskColor(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);

    myMaskColor = (MfxColor*)lParam;

    if (myMaskImage)
    {
        MfxSize tSize(myRect);
        myMaskImage->FromColor(&myMaskColor, &tSize);
    }
    else
    {
        MfxRect tRect(0, 0, myRect.myWidth, myRect.myHeight);

        myMaskImage = new MfxImage(&myMaskColor, &tRect);

        myMaskImage->SetCanvas(&myCanvas);
    }

    return Mfx_Return_Fine;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::__OnSetBackImage(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);

    MfxImage* t_Set = (MfxImage*)lParam;
    if (t_Set)
    {
        SafeDelete(myBackImage);
        (t_Set)->Clone(&myBackImage);
        MfxRect tRect(0, 0, myRect.myWidth, myRect.myHeight);
        myBackImage->SetRect(&tRect);
        myBackImage->SetCanvas(&myCanvas);
    }

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::__OnSetMaskImage(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);

    MfxImage* t_Set = (MfxImage*)lParam;
    if (t_Set)
    {
        SafeDelete(myMaskImage);
        (t_Set)->Clone(&myMaskImage);
        MfxRect tRect(0, 0, myRect.myWidth, myRect.myHeight);
        myMaskImage->SetRect(&tRect);
        myMaskImage->SetCanvas(&myCanvas);
    }

    return Mfx_Return_Fine;
}