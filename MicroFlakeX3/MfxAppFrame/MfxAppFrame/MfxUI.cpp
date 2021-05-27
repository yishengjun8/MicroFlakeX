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
    1, ChickPercentRect, \
    \
    1, RemoveFlake, \
    1, InsertFlake, \
    \
    1, RemoveFlakeEvent, \
    2, PushBackFlakeEvent, \
    2, PushFrontFlakeEvent, \
    \
    1, RemoveTimer, \
    1, InsertTimer, \
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
    1, GetGlobeAlpha, \
    \
    1, SetRect, \
    1, SetSize, \
    1, SetPoint, \
    \
    1, SetGlobeAlpha, \
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
    UI_ADDRECV_UIMSG(WM_NCPAINT, MfxUI, __OnNCPaint);
    UI_ADDRECV_UIMSG(WM_NCHITTEST, MfxUI, __OnNCHitTest);
    UI_ADDRECV_UIMSG(WM_NCACTIVATE, MfxUI, __OnNCActivate);

    UI_ADDRECV_UIMSG(WM_NCMOUSEMOVE, MfxUI, __OnNCMouseMove);
    UI_ADDRECV_UIMSG(WM_NCMOUSEHOVER, MfxUI, __OnNCMouseHover);

    UI_ADDRECV_UIMSG(WM_NCLBUTTONUP, MfxUI, __OnNCLButtonUp);
    UI_ADDRECV_UIMSG(WM_NCLBUTTONDOWN, MfxUI, __OnNCLButtonDown);
    UI_ADDRECV_UIMSG(WM_NCLBUTTONDBLCLK, MfxUI, __OnNCLButtonDouble);

    UI_ADDRECV_UIMSG(WM_NCRBUTTONUP, MfxUI, __OnNCRButtonUp);
    UI_ADDRECV_UIMSG(WM_NCRBUTTONDOWN, MfxUI, __OnNCRButtonDown);
    UI_ADDRECV_UIMSG(WM_NCRBUTTONDBLCLK, MfxUI, __OnNCRButtonDouble);

    /********************************************************************************
    *
    *********************************************************************************/
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

    UI_ADDRECV_UIMSG(UI_MSG_FlakeEvent, MfxUI, __OnFlakeEvent);

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
    myUIMessageReturnKeep = Mfx_Return_Fail;
    myFlakeEventReturnKeep = Mfx_Return_Fail;
    
    myGlobeAlphaMode = LWA_ALPHA; //LWA_COLORKEY

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
    myUIMessageReturnKeep = Mfx_Return_Fail;

    SendMessageToFlakes(message, wParam, lParam);

    myMutexLock.WaitLock(&myMessageMap);

    auto t_Iter = myMessageMap.find(message);
    if (t_Iter != myMessageMap.end())
    {
        if (!t_Iter->second.empty())
        {
            for (auto i : (t_Iter->second))
            {
                myUIMessageReturnKeep = (this->*i->recvFunc)(wParam, lParam);
            }
        }
    }
    else
    {
        myUIMessageReturnKeep = DefWindowProc(myWnd, message, wParam, lParam);
    }

    myMutexLock.UnLock(&myMessageMap);

    return myUIMessageReturnKeep;
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

MfxReturn MicroFlakeX::MfxUI::UI_PostMessage(MfxMessage message, MfxParam param)
{
    return MfxReturn();
}

/**/
MfxReturn MicroFlakeX::MfxUI::UIThread(WPARAM wParam, LPARAM lParam)
{
    myUIThreadID = GetCurrentThreadId();

    MSG tMsg;

    while (GetMessage(&tMsg, nullptr, 0, 0) > 0)
    {
        TranslateMessage(&tMsg);
        ProcMessage(tMsg.message, tMsg.wParam, tMsg.lParam);
    }

    MessageBox(nullptr, L"One UIThread Is Close", L"Close", 0);

    return tMsg.wParam;
}
/**/

/********************************************************************************
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::RemoveFlake(MfxFlake* set)
{
    return ProcMessage(UI_MSG_FlakeRemove, NULL, (LPARAM)set);
}

MfxReturn MicroFlakeX::MfxUI::InsertFlake(MfxFlake* set)
{
    return ProcMessage(UI_MSG_FlakeInsert, NULL, (LPARAM)set);
}

/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::RemoveTimer(ULONG setID)
{
    return ProcMessage(UI_MSG_RemoveTimer, NULL, (LPARAM)setID);
}

MfxReturn MicroFlakeX::MfxUI::InsertTimer(UI_UITimer_Info timer)
{
    return ProcMessage(UI_MSG_InsertTimer, NULL, (LPARAM)&timer);
}

/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::RemoveUIMessage(MfxMessage message, MfxString recvFuncName)
{
    auto tRet = Mfx_Return_Fail;

    myMutexLock.WaitLock(&myMessageMap);

    auto t_Iter = myMessageMap.find(message);
    if (t_Iter != myMessageMap.end())
    {
        for (auto i = t_Iter->second.begin(); i != t_Iter->second.end(); i++)
        {
            if ((*i)->myRecvFuncName == recvFuncName)
            {
                delete* i;
                t_Iter->second.erase(i);
                tRet = Mfx_Return_Fine;
                break;
            }
        }
    }

    myMutexLock.UnLock(&myMessageMap);

    return tRet;
}

MfxReturn MicroFlakeX::MfxUI::PushBackUIMessage(MfxMessage message, UI_UIRecvFunc_Info* msgValue)
{
    myMutexLock.WaitLock(&myMessageMap);

    Begin:
    auto t_Iter = myMessageMap.find(message);
    if (t_Iter == myMessageMap.end())
    {
        t_Iter = myMessageMap.insert(UI_UIMessage_Map_Elem(message, UI_UIRecvFunc_Infor_Deque())).first;
        goto Begin;
    }
    else
    {
        t_Iter->second.push_back(msgValue);
    }

    myMutexLock.UnLock(&myMessageMap);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::PushFrontUIMessage(MfxMessage message, UI_UIRecvFunc_Info* msgValue)
{
    myMutexLock.WaitLock(&myMessageMap);

    Begin:
    auto t_Iter = myMessageMap.find(message);
    if (t_Iter == myMessageMap.end())
    {
        t_Iter = myMessageMap.insert(UI_UIMessage_Map_Elem(message, UI_UIRecvFunc_Infor_Deque())).first;
        goto Begin;
    }
    else
    {
        t_Iter->second.push_front(msgValue);
    }

    myMutexLock.UnLock(&myMessageMap);

    return Mfx_Return_Fine;
}


/********************************************************************************
* 
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::RemoveFlakeEvent(UI_FlakeEvent_Info message)
{
    return ProcMessage(UI_MSG_RemoveFlakeMessage, NULL, (LPARAM)&message);
}

MfxReturn MicroFlakeX::MfxUI::PushBackFlakeEvent(UI_FlakeEvent_Info message, UI_UIRecvFunc_Info msgValue)
{
    return ProcMessage(UI_MSG_PushBackFlakeMessage, (WPARAM)&msgValue, (LPARAM)&message);
}

MfxReturn MicroFlakeX::MfxUI::PushFrontFlakeEvent(UI_FlakeEvent_Info message, UI_UIRecvFunc_Info msgValue)
{
    return ProcMessage(UI_MSG_PushFrontFlakeMessage, (WPARAM)&msgValue, (LPARAM)&message);
}


/********************************************************************************
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

MfxReturn MicroFlakeX::MfxUI::ChickPercentRect(bool* ret)
{
    *ret = myPercentRectFlag;

    return  Mfx_Return_Fine;
}
/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::LockMutexFocus(MfxFlake* set)
{
    auto tRet = Mfx_Return_Fail;

    myMutexLock.TryWaitLock(&myMutexFocusLockFlag, &myMutexFocus);

    if (myMutexFocusLockFlag)
    {
        tRet = myMutexFocus == set ? Mfx_Return_Fine : Mfx_Return_Fail;
    }
    else
    {
        myMutexFocus = set;
        myMutexFocusLockFlag = true;
        tRet = Mfx_Return_Fine;
    }

    myMutexLock.UnLock(&myMutexFocusLockFlag, &myMutexFocus);

    return tRet;
}

MfxReturn MicroFlakeX::MfxUI::UnLockMutexFocus()
{
    myMutexLock.WaitLock(&myMutexFocusLockFlag);

    myMutexFocusLockFlag = false;

    myMutexLock.UnLock(&myMutexFocusLockFlag);

    return Mfx_Return_Fine;
}


/********************************************************************************
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::SetMutexFocus(MfxFlake* set)
{
    auto tRet = Mfx_Return_Fail;

    myMutexLock.TryWaitLock(&myMutexFocusLockFlag, &myMutexFocus);

    if (!myMutexFocus && !myMutexFocusLockFlag)
    {
        myMutexFocus = set;
        tRet = Mfx_Return_Fine;
    }
    else
    {
        tRet = Mfx_Return_Fail;
    }

    myMutexLock.UnLock(&myMutexFocusLockFlag, &myMutexFocus);

    return tRet;
}

MfxReturn MicroFlakeX::MfxUI::GetMutexFocus(MfxFlake** ret)
{
    myMutexLock.WaitLock(&myMutexFocus);

    *ret = myMutexFocus;

    myMutexLock.UnLock(&myMutexFocus);

    return Mfx_Return_Fine;
}

/********************************************************************************
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::SetKeyboardFocus(MfxFlake* set)
{
    auto tRet = Mfx_Return_Fail;

    myMutexLock.TryWaitLock(&myMutexFocusLockFlag, &myKeyboardFocus);

    if (!myMutexFocusLockFlag)
    {
        myKeyboardFocus = set;
        tRet = Mfx_Return_Fine;
    }
    else
    {
        tRet = Mfx_Return_Fail;
    }

    myMutexLock.UnLock(&myMutexFocusLockFlag, &myKeyboardFocus);

    return tRet;
}

MfxReturn MicroFlakeX::MfxUI::GetKeyboardFocus(MfxFlake** ret)
{
    myMutexLock.WaitLock(&myKeyboardFocus);

    *ret = myKeyboardFocus;

    myMutexLock.UnLock(&myKeyboardFocus);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::UnionInvalidateRect(MfxRect* set)
{
    RECT tRECT;
    set->GetRECT(&tRECT);
    InvalidateRect(myWnd, &tRECT, TRUE);

    myMutexLock.WaitLock(&myInvalidateRect);

    myInvalidateRect.Union(set, &myInvalidateRect);

    myMutexLock.UnLock(&myInvalidateRect);

    return Mfx_Return_Fine;
}

/********************************************************************************
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

MfxReturn MicroFlakeX::MfxUI::GetWorldRect(MfxRect* ret)
{
    RECT tWorldRECT;
    GetWindowRect(myWnd, &tWorldRECT);

    ret->SetRECT(&tWorldRECT);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::GetLocalMousePos(MfxPoint* ret)
{
    POINT tPOINT;
    GetCursorPos(&tPOINT);

    MfxPoint tPoint;
    GetPoint(&tPoint);

    ret->Reset(tPOINT.x - tPoint.myX, tPOINT.y - tPoint.myY);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::TransWorldRectToLocalRect(MfxRect* world, MfxRect* local)
{
    RECT tWorldRECT;
    GetWindowRect(myWnd, &tWorldRECT);

    local->SetRECT(&tWorldRECT);

    world->myX -= local->myX;
    world->myY -= local->myY;

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::TransWorldPointToLocalPoint(MfxPoint* world, MfxPoint* local)
{
    RECT tWorldRECT;
    GetWindowRect(myWnd, &tWorldRECT);

    MfxRect tRect;
    tRect.SetRECT(&tWorldRECT);
    tRect.GetPoint(local);

    world->myX -= local->myX;
    world->myY -= local->myY;

    return Mfx_Return_Fine;
}


/********************************************************************************
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::GetRect(MfxRect* ret)
{
    myMutexLock.WaitLock(&myRect);

    myRect.GetRect(ret);

    myMutexLock.UnLock(&myRect);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::GetSize(MfxSize* ret)
{
    myMutexLock.WaitLock(&myRect);

    myRect.GetSize(ret);

    myMutexLock.UnLock(&myRect);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::GetPoint(MfxPoint* ret)
{
    myMutexLock.WaitLock(&myRect);

    myRect.GetPoint(ret);

    myMutexLock.UnLock(&myRect);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::GetBackColor(MfxColor* ret)
{
    myMutexLock.WaitLock(&myBackColor);

    myBackColor.GetColor(ret);

    myMutexLock.UnLock(&myBackColor);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::GetMaskColor(MfxColor* ret)
{
    myMutexLock.WaitLock(&myMaskColor);

    myMaskColor.GetColor(ret);

    myMutexLock.UnLock(&myMaskColor);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::GetBackImage(MfxImage** ret)
{
    myMutexLock.WaitLock(&myBackImage);

    auto tRet = myBackImage ? myBackImage->Clone(ret) : Mfx_Return_Fail;

    myMutexLock.UnLock(&myBackImage);

    return tRet;
}

MfxReturn MicroFlakeX::MfxUI::GetMaskImage(MfxImage** ret)
{
    myMutexLock.WaitLock(&myMaskImage);

    auto tRet = myMaskImage ? myMaskImage->Clone(ret) : Mfx_Return_Fail;

    myMutexLock.UnLock(&myMaskImage);

    return tRet;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::SetRect(MfxRect* set)
{
    return SetWindowPos(myWnd, nullptr, set->myX, set->myY, set->myWidth, set->myHeight, SWP_NOZORDER) ? Mfx_Return_Fine : Mfx_Return_Fail;;
}

MfxReturn MicroFlakeX::MfxUI::SetSize(MfxSize* set)
{
    return SetWindowPos(myWnd, nullptr, 0, 0, set->myWidth, set->myHeight, SWP_NOMOVE | SWP_NOZORDER) ? Mfx_Return_Fine : Mfx_Return_Fail;;
}

MfxReturn MicroFlakeX::MfxUI::SetPoint(MfxPoint* set)
{
    return SetWindowPos(myWnd, nullptr, set->myX, set->myY, 0, 0, SWP_NOSIZE | SWP_NOZORDER) ? Mfx_Return_Fine : Mfx_Return_Fail;;
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

MfxReturn MicroFlakeX::MfxUI::SetBigIcon(MfxImage* set)
{
    return MfxReturn();
}

MfxReturn MicroFlakeX::MfxUI::SetSmallIcon(MfxImage* set)
{
    return MfxReturn();
}

MfxReturn MicroFlakeX::MfxUI::GetGlobeAlpha(MfxColor* set)
{
    myMutexLock.WaitLock(&myGlobeAlpha);

    *set = myGlobeAlpha;

    myMutexLock.UnLock(&myGlobeAlpha);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::GetGlobeAlphaMode(UINT set)
{
    myMutexLock.WaitLock(&myGlobeAlphaMode);

    set = myGlobeAlphaMode;

    myMutexLock.UnLock(&myGlobeAlphaMode);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::SetGlobeAlpha(MfxColor* set)
{
    myMutexLock.WaitLock(&myGlobeAlpha);

    myGlobeAlpha = set;
    LONG tA = 0;
    myGlobeAlpha.GetA(&tA);

    SetLayeredWindowAttributes(myWnd, myGlobeAlpha, tA, myGlobeAlphaMode);

    myMutexLock.UnLock(&myGlobeAlpha);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::SetGlobeAlphaMode(UINT set)
{
    myMutexLock.WaitLock(&myGlobeAlphaMode);

    myGlobeAlphaMode = set;

    myMutexLock.UnLock(&myGlobeAlphaMode);

    return Mfx_Return_Fine;
}


/********************************************************************************
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::SetUI_Max()
{
    return ShowWindow(myWnd, SW_MAXIMIZE) ? Mfx_Return_Fine : Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxUI::SetUI_Min()
{
    return ShowWindow(myWnd, SW_MINIMIZE) ? Mfx_Return_Fine : Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxUI::SetUI_Show()
{
    return ShowWindow(myWnd, SW_SHOW) ? Mfx_Return_Fine : Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxUI::SetUI_Hide()
{
    return ShowWindow(myWnd, SW_HIDE) ? Mfx_Return_Fine : Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxUI::SetUI_Normal()
{
    return ShowWindow(myWnd, SW_NORMAL) ? Mfx_Return_Fine : Mfx_Return_Fail;
}


/********************************************************************************
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::__OnTest00(WPARAM wParam, LPARAM lParam)
{
    std::cout << "__OnTest00: wParam-" << wParam << " lParam-" << lParam << std::endl;

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::__OnTest01(WPARAM wParam, LPARAM lParam)
{
    std::cout << "__OnTest01: wParam-" << wParam << " lParam-" << lParam << std::endl;

    return Mfx_Return_Fine;
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

    myMutexLock.WaitLock(&myRect);

    GetWorldRect(&myRect);
    HRGN tRNG = CreateRectRgn(0, 0, myRect.myWidth, myRect.myHeight);

    myMutexLock.UnLock(&myRect);
   
    MfxSize tSize(myRect.myWidth, myRect.myHeight);
    MfxRect tRect(0, 0, myRect.myWidth, myRect.myHeight);

    myMutexLock.WaitLock(&myCanvas);

    myCanvas.SetSize(&tSize);
    myCanvas.SetDC(GetWindowDC(myWnd));

    myMutexLock.UnLock(&myCanvas);


    myMutexLock.WaitLock(&myBackImage);

    myBackImage = new MfxImage(&myBackColor, &tRect);
    myBackImage->SetCanvas(&myCanvas);

    myMutexLock.UnLock(&myBackImage);

    while (!myUIThreadID);

    SetWindowRgn(myWnd, tRNG, TRUE);

    DeleteObject(tRNG);

    SetWindowLong(myWnd, GWL_EXSTYLE, GetWindowLong(myWnd, GWL_EXSTYLE) | WS_EX_LAYERED);

    SetGlobeAlpha(&myBackColor);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::__OnDestroy(WPARAM wParam, LPARAM lParam)
{
    MessageBox(NULL, L"__OnDestroy", L"__OnDestroy", 0);

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
    myMutexLock.WaitLock(&myRect);

    GetWorldRect(&myRect);
    MfxSize tSize;
    myRect.GetSize(&tSize);
    UnionInvalidateRect(&myRect);

    myMutexLock.UnLock(&myRect);


    myMutexLock.WaitLock(&myCanvas);
    myCanvas.SetSize(&tSize);
    myMutexLock.UnLock(&myCanvas);


    myMutexLock.WaitLock(&myBackImage);
    myBackImage ? myBackImage->SetSize(&tSize) : 0;
    myMutexLock.UnLock(&myBackImage);

    myMutexLock.WaitLock(&myMaskImage);
    myMaskImage ? myMaskImage->SetSize(&tSize) : 0;
    myMutexLock.UnLock(&myMaskImage);

    HRGN tRNG = CreateRectRgn(0, 0, tSize.myWidth, tSize.myHeight);

    SetWindowRgn(myWnd, tRNG, TRUE);

    DeleteObject(tRNG);

    return DefWindowProc(myWnd, WM_SIZE, wParam, lParam);
}

MfxReturn MicroFlakeX::MfxUI::__OnMove(WPARAM wParam, LPARAM lParam)
{
    myMutexLock.WaitLock(&myRect);

    GetWorldRect(&myRect);
    UnionInvalidateRect(&myRect);

    myMutexLock.UnLock(&myRect);

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
    PAINTSTRUCT t_Paint{0};

    HDC t_Dc = BeginPaint(myWnd, &t_Paint);

    bool isEmpty = true;

    myMutexLock.WaitLock(&myInvalidateRect);
    myInvalidateRect.IsEmpty(&isEmpty);
    myMutexLock.UnLock(&myInvalidateRect);

    if (!isEmpty)
    {
        myMutexLock.TryWaitLock(&myCanvas, &myInvalidateRect);

        myCanvas.PaintBegin(&myInvalidateRect);
        myInvalidateRect.Reset(0, 0, 0, 0);

        myMutexLock.UnLock(&myCanvas, &myInvalidateRect);

        ProcMessage(UI_MSG_PaintBack, NULL, NULL);

        ProcMessage(UI_MSG_PaintMask, NULL, NULL);

        myMutexLock.WaitLock(&myCanvas);
        myCanvas.PaintFinish();
        myMutexLock.UnLock(&myCanvas);
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
    myMutexLock.WaitLock(&myBackImage);
    myBackImage ? myBackImage->Paint() : 0;
    myMutexLock.UnLock(&myBackImage);

    SendMessageToFlakes(FLAKE_MSG_PaintBack, wParam, lParam, true);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::__OnPaintMaskDC(WPARAM wParam, LPARAM lParam)
{
    SendMessageToFlakes(FLAKE_MSG_PaintMask, wParam, lParam, true);

    myMutexLock.WaitLock(&myMaskImage);
    myMaskImage ? myMaskImage->Paint() : 0;
    myMutexLock.UnLock(&myMaskImage);

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
    if (lParam)
    {
        myMutexLock.WaitLock(&myFlakeSet);
        bool tIns = myFlakeSet.insert((MfxFlake*)lParam).second;
        myMutexLock.UnLock(&myFlakeSet);

        if(tIns)
        {
            myMutexLock.WaitLock(&myFlakeDeque);
            myFlakeDeque.push_back((MfxFlake*)lParam);
            myMutexLock.UnLock(&myFlakeDeque);

            myMutexLock.TryWaitLock(&myWnd, &myCanvas, &myUIThreadID);
            ((MfxFlake*)lParam)->ProcMessage(FLAKE_MSG_SetPaper, TRUE, (LPARAM)new Paper_Infor(this, myWnd, &myCanvas, myUIThreadID));
            myMutexLock.UnLock(&myWnd, &myCanvas, &myUIThreadID);

            PostMessage(myWnd, UI_MSG_FlakeFloorChange, NULL, lParam);

            myMutexLock.WaitLock(&myRect);
            UnionInvalidateRect(&myRect);
            myMutexLock.UnLock(&myRect);

            return Mfx_Return_Fine;
        }
    }

    return Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxUI::__OnFlakeRemove(WPARAM wParam, LPARAM lParam)
{
    if (lParam)
    {
        myMutexLock.WaitLock(&myFlakeSet);
        bool tFind = myFlakeSet.find((MfxFlake*)lParam) != myFlakeSet.end();
        myMutexLock.UnLock(&myFlakeSet);

        if (tFind)
        {
            myMutexLock.WaitLock(&myFlakeDeque);
            for (auto delIt = myFlakeDeque.begin(); delIt != myFlakeDeque.end(); delIt++)
            {
                if (*delIt == ((MfxFlake*)lParam))
                {
                    ((MfxFlake*)lParam)->ProcMessage(FLAKE_MSG_RemovePaper, NULL, NULL);

                    myFlakeDeque.erase(delIt);

                    myMutexLock.WaitLock(&myFlakeSet);
                    myFlakeSet.erase(((MfxFlake*)lParam));
                    myMutexLock.UnLock(&myFlakeSet);

                    PostMessage(myWnd, UI_MSG_FlakeFloorChange, NULL, NULL);

                    InvalidateRect(myWnd, nullptr, TRUE);

                    break;
                }
            }
            myMutexLock.UnLock(&myFlakeDeque);
        }
    }

    return Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxUI::__OnFlakeFloorChange(WPARAM wParam, LPARAM lParam)
{
    myMutexLock.WaitLock(&myFlakeDeque);

    std::sort(myFlakeDeque.begin(), myFlakeDeque.end(), pFloorCompare<MfxFlake>);

    myMutexLock.UnLock(&myFlakeDeque);

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
    auto tRet = Mfx_Return_Fail;
    myMutexLock.WaitLock(&myTimerMap);

    auto t_Iter = myTimerMap.find(wParam);
    if (t_Iter != myTimerMap.end())
    {
        tRet = (this->*t_Iter->second->recvFunc)(NULL, (LPARAM)t_Iter->second);
    }

    myMutexLock.UnLock(&myTimerMap);

    return tRet;
}

MfxReturn MicroFlakeX::MfxUI::__OnInsertTimer(WPARAM wParam, LPARAM lParam)
{
    auto tRet = Mfx_Return_Fail;
    UI_UITimer_Info* tTimer = new UI_UITimer_Info(*(UI_UITimer_Info*)lParam);

    myMutexLock.WaitLock(&myTimerMap);
    bool tIns = myTimerMap.insert(UI_UITimer_Map_Elem(tTimer->myID, tTimer)).second;
    myMutexLock.UnLock(&myTimerMap);

    if (tIns)
    {
        SetTimer(myWnd, tTimer->myID, ((UI_UITimer_Info*)lParam)->delayTime, (TIMERPROC)nullptr);
        tRet = Mfx_Return_Fine;
    }

    return tRet;
}

MfxReturn MicroFlakeX::MfxUI::__OnRemoveTimer(WPARAM wParam, LPARAM lParam)
{
    auto tRet = Mfx_Return_Fail;
    myMutexLock.WaitLock(&myTimerMap);

    auto iter = myTimerMap.find(lParam);
    if (iter != myTimerMap.end())
    {
        KillTimer(myWnd, lParam);

        delete iter->second;

        myTimerMap.erase(lParam);

        tRet = Mfx_Return_Fine;
    }

    myMutexLock.UnLock(&myTimerMap);

    return tRet;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::__OnFlakeEvent(WPARAM wParam, LPARAM lParam)
{
    myMutexLock.WaitLock(&myFlakeEventMap);

    myFlakeEventReturnKeep = Mfx_Return_Fail;
    auto t_Iter = myFlakeEventMap.find(*(UI_FlakeEvent_Info*)wParam);
    if (t_Iter != myFlakeEventMap.end())
    {
        if (!t_Iter->second.empty())
        {
            for (auto i : (t_Iter->second))
            {
                myFlakeEventReturnKeep = (this->*i->recvFunc)(wParam, lParam);
            }
        }
    }

    myMutexLock.UnLock(&myFlakeEventMap);

    return myFlakeEventReturnKeep;
}

MfxReturn MicroFlakeX::MfxUI::__OnRemoveFlakeMessage(WPARAM wParam, LPARAM lParam)
{
    auto tRet = Mfx_Return_Fail;

    MfxString* tRecvFuncName = (MfxString*)lParam;
    UI_FlakeEvent_Info* tFlakeMsg_Infor = (UI_FlakeEvent_Info*)wParam;

    myMutexLock.WaitLock(&myFlakeEventMap);

    auto t_Iter = myFlakeEventMap.find(*tFlakeMsg_Infor);
    if (t_Iter != myFlakeEventMap.end())
    {
        for (auto i = t_Iter->second.begin(); i != t_Iter->second.end(); i++)
        {
            if ((*i)->myRecvFuncName == *tRecvFuncName)
            {
                delete* i;
                t_Iter->second.erase(i);
                tRet = Mfx_Return_Fine;
                break;
            }
        }
    }

    myMutexLock.UnLock(&myFlakeEventMap);

    return tRet;
}

MfxReturn MicroFlakeX::MfxUI::__OnPushBackFlakeMessage(WPARAM wParam, LPARAM lParam)
{
    myMutexLock.WaitLock(&myFlakeEventMap);

    UI_FlakeEvent_Info* tFlakeMsg_Infor = (UI_FlakeEvent_Info*)wParam;
    UI_UIRecvFunc_Info* tRecvFunc_Infor = (UI_UIRecvFunc_Info*)lParam;

Begin:
    auto t_Iter = myFlakeEventMap.find(*tFlakeMsg_Infor);
    if (t_Iter == myFlakeEventMap.end())
    {
        t_Iter = myFlakeEventMap.insert(UI_FlakeMsg_Map_Elem(*tFlakeMsg_Infor, UI_UIRecvFunc_Infor_Deque())).first;
        goto Begin;
    }
    else
    {
        t_Iter->second.push_back(tRecvFunc_Infor);
    }

    myMutexLock.UnLock(&myFlakeEventMap);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::__OnPushFrontFlakeMessage(WPARAM wParam, LPARAM lParam)
{
    myMutexLock.WaitLock(&myFlakeEventMap);

    UI_FlakeEvent_Info* tFlakeMsg_Infor = (UI_FlakeEvent_Info*)wParam;
    UI_UIRecvFunc_Info* tRecvFunc_Infor = (UI_UIRecvFunc_Info*)lParam;

Begin:
    auto t_Iter = myFlakeEventMap.find(*tFlakeMsg_Infor);
    if (t_Iter == myFlakeEventMap.end())
    {
        t_Iter = myFlakeEventMap.insert(UI_FlakeMsg_Map_Elem(*tFlakeMsg_Infor, UI_UIRecvFunc_Infor_Deque())).first;
        goto Begin;
    }
    else
    {
        t_Iter->second.push_front(tRecvFunc_Infor);
    }

    myMutexLock.UnLock(&myFlakeEventMap);

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
    myMutexLock.WaitLock(&myPercentRectFlag);

    myPercentRectFlag = true;

    myMutexLock.UnLock(&myPercentRectFlag);

    SendMessageToFlakes(FLAKE_MSG_OpenPercentRect, NULL, NULL);

    return Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxUI::__OnClosePercentRect(WPARAM wParam, LPARAM lParam)
{
    myMutexLock.WaitLock(&myPercentRectFlag);

    myPercentRectFlag = false;

    myMutexLock.UnLock(&myPercentRectFlag);

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
    myMutexLock.WaitLock(&myRect);
    MfxSize tSize(myRect);
    myMutexLock.UnLock(&myRect);

    myMutexLock.TryWaitLock(&myBackImage, &myBackColor, &myCanvas);
    myBackColor = (MfxColor*)lParam;
    if (myBackImage)
    {
        myBackImage->FromColor(&myBackColor, &tSize);
    }
    else
    {
        myBackImage = new MfxImage(&myBackColor, &tSize);
        myBackImage->SetCanvas(&myCanvas);
    }
    SetGlobeAlpha(&myBackColor);
    myMutexLock.UnLock(&myBackImage, &myBackColor, &myCanvas);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::__OnSetMaskColor(WPARAM wParam, LPARAM lParam)
{
    myMutexLock.WaitLock(&myRect);
    MfxSize tSize(myRect);
    myMutexLock.UnLock(&myRect);

    myMutexLock.TryWaitLock(&myMaskColor, &myMaskImage, &myCanvas);
    myMaskColor = (MfxColor*)lParam;
    if (myMaskImage)
    {
        myMaskImage->FromColor(&myMaskColor, &tSize);
    }
    else
    {
        myMaskImage = new MfxImage(&myMaskColor, &tSize);

        myMaskImage->SetCanvas(&myCanvas);
    }
    myMutexLock.UnLock(&myBackImage, &myBackColor, &myCanvas);

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
    MfxImage* t_Set = (MfxImage*)lParam;
    if (t_Set)
    {
        myMutexLock.TryWaitLock(&myBackImage, &myRect, &myCanvas);

        SafeDelete(myBackImage);
        (t_Set)->Clone(&myBackImage);
        MfxRect tRect(0, 0, myRect.myWidth, myRect.myHeight);
        myBackImage->SetRect(&tRect);
        myBackImage->SetCanvas(&myCanvas);

        myMutexLock.UnLock(&myBackImage, &myRect, &myCanvas);
    }

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::__OnSetMaskImage(WPARAM wParam, LPARAM lParam)
{
    MfxImage* t_Set = (MfxImage*)lParam;
    if (t_Set)
    {
        myMutexLock.TryWaitLock(&myMaskImage, &myRect, &myCanvas);

        SafeDelete(myMaskImage);
        (t_Set)->Clone(&myMaskImage);
        MfxRect tRect(0, 0, myRect.myWidth, myRect.myHeight);
        myMaskImage->SetRect(&tRect);
        myMaskImage->SetCanvas(&myCanvas);

        myMutexLock.UnLock(&myMaskImage, &myRect, &myCanvas);
    }

    return Mfx_Return_Fine;
}

/********************************************************************************
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::__OnNCPaint(WPARAM wParam, LPARAM lParam)
{
    return 1;
}

MfxReturn MicroFlakeX::MfxUI::__OnNCActivate(WPARAM wParam, LPARAM lParam)
{
    return wParam ? 0 : 1;
}

MfxReturn MicroFlakeX::MfxUI::__OnNCHitTest(WPARAM wParam, LPARAM lParam)
{
    auto ret = DefWindowProcW(myWnd, WM_NCHITTEST, wParam, lParam);

    if (ret == HTHELP
        || ret == HTCLOSE
        || ret == HTMAXBUTTON
        || ret == HTMINBUTTON
        )
    {
        return HTCAPTION;
    }

    return ret;
}


/********************************************************************************
*
*
*********************************************************************************/
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


/********************************************************************************
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::__OnNCLButtonUp(WPARAM wParam, LPARAM lParam)
{
    return myMutexFocus ? 0 : DefWindowProc(myWnd, WM_NCLBUTTONUP, wParam, lParam);
}

MfxReturn MicroFlakeX::MfxUI::__OnNCLButtonDown(WPARAM wParam, LPARAM lParam)
{
    return myMutexFocus ? 0 : DefWindowProc(myWnd, WM_NCLBUTTONDOWN, wParam, lParam);
}

MfxReturn MicroFlakeX::MfxUI::__OnNCLButtonDouble(WPARAM wParam, LPARAM lParam)
{
    return myMutexFocus ? 0 : DefWindowProc(myWnd, WM_NCLBUTTONDBLCLK, wParam, lParam);
}


/********************************************************************************
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::__OnNCRButtonUp(WPARAM wParam, LPARAM lParam)
{
    return myMutexFocus ? 0 : DefWindowProc(myWnd, WM_NCRBUTTONUP, wParam, lParam);
}

MfxReturn MicroFlakeX::MfxUI::__OnNCRButtonDown(WPARAM wParam, LPARAM lParam)
{
    return myMutexFocus ? 0 : DefWindowProc(myWnd, WM_NCRBUTTONDOWN, wParam, lParam);
}

MfxReturn MicroFlakeX::MfxUI::__OnNCRButtonDouble(WPARAM wParam, LPARAM lParam)
{
    return myMutexFocus ? 0 : DefWindowProc(myWnd, WM_NCRBUTTONDBLCLK, wParam, lParam);
}

