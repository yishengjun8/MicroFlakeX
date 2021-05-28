#include "pch.h"
#include "MfxAppFrame.h"

MfxObject_Init(MfxUI)
MfxObject_EndInit(MfxUI, MfxBase, \
    \
    0, CreateSuccess, \
    \
    1, ProcMessage, \
    1, ProcFlakesMessage, \
    1, RProcFlakesMessage, \
    \
    1, Send_Message, \
    1, Post_Message, \
    \
    1, RemoveFlake, \
    1, InsertFlake, \
    \
    1, RemoveTimer, \
    1, InsertTimer, \
    \
    2, RemoveUIMessage, \
    2, PushBackUIMessage, \
    2, PushFrontUIMessage, \
    \
    0, OpenPercentRect, \
    0, ClosePercentRect, \
    1, ChickPercentRect, \
    \
    2, RemoveFlakeEvent, \
    2, PushBackFlakeEvent, \
    2, PushFrontFlakeEvent, \
    \
    1, LockMutexFocus, \
    0, UnLockMutexFocus, \
    \
    1, SetMutexFocus, \
    1, GetMutexFocus, \
    1, SetKeyboardFocus, \
    1, GetKeyboardFocus, \
    \
    1, UnionInvalidateRect, \
    \
    1, GetWnd, \
    1, GetCanvas, \
    \
    1, GetWorldRect, \
    1, GetLocalMousePos, \
    2, TransWorldRectToLocalRect, \
    2, TransWorldPointToLocalPoint, \
    \
    \
    1, GetRect, \
    1, GetSize, \
    1, GetPoint, \
    1, GetBackColor, \
    1, GetMaskColor, \
    1, GetBackImage, \
    1, GetMaskImage, \
    \
    1, SetRect, \
    1, SetSize, \
    1, SetPoint, \
    1, SetBackColor, \
    1, SetMaskColor, \
    1, SetBackImage, \
    1, SetMaskImage, \
    \
    1, GetGlobeAlpha, \
    1, GetGlobeAlphaMode, \
    1, SetGlobeAlpha, \
    1, SetGlobeAlphaMode, \
    \
    0, SetUI_Max, \
    0, SetUI_Min, \
    0, SetUI_Show, \
    0, SetUI_Hide, \
    0, SetUI_Normal \

);


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

    UI_ADDRECV_UIMSG(MSG_FlakeEvent, MfxUI, __OnFlakeEvent);

    UI_ADDRECV_UIMSG(UI_MSG_RemoveFlakeEvent, MfxUI, __OnRemoveFlakeEvent);
    UI_ADDRECV_UIMSG(UI_MSG_PushBackFlakeEvent, MfxUI, __OnPushBackFlakeEvent);
    UI_ADDRECV_UIMSG(UI_MSG_PushFrontFlakeEvent, MfxUI, __OnPushFrontFlakeEvent);

    UI_ADDRECV_UIMSG(UI_MSG_OpenPercentRect, MfxUI, __OnOpenPercentRect);
    UI_ADDRECV_UIMSG(UI_MSG_ClosePercentRect, MfxUI, __OnClosePercentRect);

    UI_ADDRECV_UIMSG(UI_MSG_SetBackColor, MfxUI, __OnSetBackColor);
    UI_ADDRECV_UIMSG(UI_MSG_SetMaskColor, MfxUI, __OnSetMaskColor);
    UI_ADDRECV_UIMSG(UI_MSG_SetBackImage, MfxUI, __OnSetBackImage);
    UI_ADDRECV_UIMSG(UI_MSG_SetMaskImage, MfxUI, __OnSetMaskImage);
}

void MicroFlakeX::MfxUI::MfxUIInitData()
{
    myGlobeAlphaMode = LWA_ALPHA; //LWA_COLORKEY

    myWnd = nullptr;

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
MfxReturn MicroFlakeX::MfxUI::ProcMessage(MfxParam param)
{
    /* 这里添加识别 - 耗时的全部移交到UI线程内处理 */
    MfxReturn tRet = Mfx_Return_Fail;
    ProcFlakesMessage(param);

    myMemberLock.WaitLock(&myMessageMap);

    auto t_Iter = myMessageMap.find(GetParam(param, MfxMessage, 0));
    if (t_Iter != myMessageMap.end())
    {
        if (!t_Iter->second.empty())
        {
            for (auto i : (t_Iter->second))
            {
                tRet = (this->*i.recvFunc)(param);
            }
        }
    }
    else
    {
        MfxMessage message = GetParam(param, MfxMessage, 0);
        WPARAM wParam = GetParam_Safe(param, WPARAM, 1);
        LPARAM lParam = GetParam_Safe(param, LPARAM, 2);

        tRet = DefWindowProc(myWnd, message, wParam, lParam);
    }

    myMemberLock.UnLock(&myMessageMap);

    return tRet;
}

MfxReturn MicroFlakeX::MfxUI::ProcFlakesMessage(MfxParam param)
{
    MfxReturn t_Ret = Mfx_Return_Fail;
    pMfxFlake t_FloatFocus = myMutexFocus;
    myMutexFocus = myMutexFocusLockFlag ? myMutexFocus : nullptr;

    for (auto t_Iter : myFlakeDeque)
    {
        t_Ret = t_Iter->Send_Message(param);
    }

    return t_Ret;
}

MfxReturn MicroFlakeX::MfxUI::RProcFlakesMessage(MfxParam param)
{
    MfxReturn t_Ret = Mfx_Return_Fail;
    pMfxFlake t_FloatFocus = myMutexFocus;
    myMutexFocus = myMutexFocusLockFlag ? myMutexFocus : nullptr;

    for (int i = myFlakeDeque.size() - 1; i >= 0; i--)
    {
        t_Ret = myFlakeDeque[i]->Send_Message(param);
    }

    return t_Ret;
}

MfxReturn MicroFlakeX::MfxUI::Send_Message(MfxParam param)
{
    return ProcMessage(param);
}

MfxReturn MicroFlakeX::MfxUI::Post_Message(MfxParam param)
{
    return MfxBeginNewThread(this, MfxText("ProcMessage"), param);
}



/********************************************************************************
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::RemoveFlake(pMfxFlake set)
{
    MfxParam msgParam;
    msgParam.push_back(UI_MSG_FlakeRemove);
    msgParam.push_back(set);
    return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxUI::InsertFlake(pMfxFlake set)
{
    MfxParam msgParam;
    msgParam.push_back(UI_MSG_FlakeInsert);
    msgParam.push_back(set);
    return Send_Message(msgParam);
}

/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::RemoveTimer(ULONG setID)
{
    MfxParam msgParam;
    msgParam.push_back(UI_MSG_RemoveTimer);
    msgParam.push_back(setID);
    return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxUI::InsertTimer(UI_UITimer_Info timer)
{
    MfxParam msgParam;
    msgParam.push_back(UI_MSG_InsertTimer);
    msgParam.push_back(timer);
    return Send_Message(msgParam);
}

/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::RemoveUIMessage(MfxMessage message, MfxString recvFuncName)
{
    MfxReturn tRet = Mfx_Return_Fail;

    myMemberLock.WaitLock(&myMessageMap);

    auto t_Iter = myMessageMap.find(message);
    if (t_Iter != myMessageMap.end())
    {
        for (auto i = t_Iter->second.begin(); i != t_Iter->second.end(); i++)
        {
            if ((*i).myRecvFuncName == recvFuncName)
            {
                t_Iter->second.erase(i);
                tRet = Mfx_Return_Fine;
                break;
            }
        }
    }

    myMemberLock.UnLock(&myMessageMap);

    return tRet;
}

MfxReturn MicroFlakeX::MfxUI::PushBackUIMessage(MfxMessage message, UI_UIRecvFunc_Info recvInfo)
{
    myMemberLock.WaitLock(&myMessageMap);

    Begin:
    auto t_Iter = myMessageMap.find(message);
    if (t_Iter == myMessageMap.end())
    {
        t_Iter = myMessageMap.insert(UI_UIMessage_Map_Elem(message, UI_UIRecvFunc_Infor_Deque())).first;
        goto Begin;
    }
    else
    {
        t_Iter->second.push_back(recvInfo);
    }

    myMemberLock.UnLock(&myMessageMap);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::PushFrontUIMessage(MfxMessage message, UI_UIRecvFunc_Info recvInfo)
{
    myMemberLock.WaitLock(&myMessageMap);

    Begin:
    auto t_Iter = myMessageMap.find(message);
    if (t_Iter == myMessageMap.end())
    {
        t_Iter = myMessageMap.insert(UI_UIMessage_Map_Elem(message, UI_UIRecvFunc_Infor_Deque())).first;
        goto Begin;
    }
    else
    {
        t_Iter->second.push_front(recvInfo);
    }

    myMemberLock.UnLock(&myMessageMap);

    return Mfx_Return_Fine;
}


/********************************************************************************
* 
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::RemoveFlakeEvent(FlakeEvent_Info flakeEvent, MfxString recvFuncName)
{
    MfxParam msgParam;
    msgParam.push_back(UI_MSG_RemoveFlakeEvent);
    msgParam.push_back(flakeEvent);
    msgParam.push_back(recvFuncName);
    return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxUI::PushBackFlakeEvent(FlakeEvent_Info flakeEvent, UI_UIRecvFunc_Info recvInfo)
{
    MfxParam msgParam;
    msgParam.push_back(UI_MSG_PushBackFlakeEvent);
    msgParam.push_back(flakeEvent);
    msgParam.push_back(recvInfo);
    return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxUI::PushFrontFlakeEvent(FlakeEvent_Info flakeEvent, UI_UIRecvFunc_Info recvInfo)
{
    MfxParam msgParam;
    msgParam.push_back(UI_MSG_PushFrontFlakeEvent);
    msgParam.push_back(flakeEvent);
    msgParam.push_back(recvInfo);
    return Send_Message(msgParam);
}


/********************************************************************************
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::OpenPercentRect()
{
    MfxParam msgParam;
    msgParam.push_back(UI_MSG_OpenPercentRect);
    return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxUI::ClosePercentRect()
{
    MfxParam msgParam;
    msgParam.push_back(UI_MSG_ClosePercentRect);
    return Send_Message(msgParam);
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
MfxReturn MicroFlakeX::MfxUI::LockMutexFocus(pMfxFlake set)
{
    auto tRet = Mfx_Return_Fail;

    myMemberLock.TryWaitLock(&myMutexFocusLockFlag, &myMutexFocus);

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

    myMemberLock.UnLock(&myMutexFocusLockFlag, &myMutexFocus);

    return tRet;
}

MfxReturn MicroFlakeX::MfxUI::UnLockMutexFocus()
{
    myMemberLock.WaitLock(&myMutexFocusLockFlag);

    myMutexFocusLockFlag = false;

    myMemberLock.UnLock(&myMutexFocusLockFlag);

    return Mfx_Return_Fine;
}


/********************************************************************************
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::SetMutexFocus(pMfxFlake set)
{
    auto tRet = Mfx_Return_Fail;

    myMemberLock.TryWaitLock(&myMutexFocusLockFlag, &myMutexFocus);

    if (!myMutexFocus && !myMutexFocusLockFlag)
    {
        myMutexFocus = set;
        tRet = Mfx_Return_Fine;
    }
    else
    {
        tRet = Mfx_Return_Fail;
    }

    myMemberLock.UnLock(&myMutexFocusLockFlag, &myMutexFocus);

    return tRet;
}

MfxReturn MicroFlakeX::MfxUI::GetMutexFocus(pMfxFlake* ret)
{
    myMemberLock.WaitLock(&myMutexFocus);

    *ret = myMutexFocus;

    myMemberLock.UnLock(&myMutexFocus);

    return Mfx_Return_Fine;
}

/********************************************************************************
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::SetKeyboardFocus(pMfxFlake set)
{
    auto tRet = Mfx_Return_Fail;

    myMemberLock.TryWaitLock(&myMutexFocusLockFlag, &myKeyboardFocus);

    if (!myMutexFocusLockFlag)
    {
        myKeyboardFocus = set;
        tRet = Mfx_Return_Fine;
    }
    else
    {
        tRet = Mfx_Return_Fail;
    }

    myMemberLock.UnLock(&myMutexFocusLockFlag, &myKeyboardFocus);

    return tRet;
}

MfxReturn MicroFlakeX::MfxUI::GetKeyboardFocus(pMfxFlake* ret)
{
    myMemberLock.WaitLock(&myKeyboardFocus);

    *ret = myKeyboardFocus;

    myMemberLock.UnLock(&myKeyboardFocus);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::UnionInvalidateRect(MfxRect* set)
{
    RECT tRECT;
    set->GetRECT(&tRECT);
    InvalidateRect(myWnd, &tRECT, TRUE);

    myMemberLock.WaitLock(&myInvalidateRect);

    myInvalidateRect.Union(set, &myInvalidateRect);

    myMemberLock.UnLock(&myInvalidateRect);

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
    myMemberLock.WaitLock(&myRect);

    myRect.GetRect(ret);

    myMemberLock.UnLock(&myRect);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::GetSize(MfxSize* ret)
{
    myMemberLock.WaitLock(&myRect);

    myRect.GetSize(ret);

    myMemberLock.UnLock(&myRect);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::GetPoint(MfxPoint* ret)
{
    myMemberLock.WaitLock(&myRect);

    myRect.GetPoint(ret);

    myMemberLock.UnLock(&myRect);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::GetBackColor(MfxColor* ret)
{
    myMemberLock.WaitLock(&myBackColor);

    myBackColor.GetColor(ret);

    myMemberLock.UnLock(&myBackColor);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::GetMaskColor(MfxColor* ret)
{
    myMemberLock.WaitLock(&myMaskColor);

    myMaskColor.GetColor(ret);

    myMemberLock.UnLock(&myMaskColor);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::GetBackImage(MfxImage** ret)
{
    myMemberLock.WaitLock(&myBackImage);

    auto tRet = myBackImage ? myBackImage->Clone(ret) : Mfx_Return_Fail;

    myMemberLock.UnLock(&myBackImage);

    return tRet;
}

MfxReturn MicroFlakeX::MfxUI::GetMaskImage(MfxImage** ret)
{
    myMemberLock.WaitLock(&myMaskImage);

    auto tRet = myMaskImage ? myMaskImage->Clone(ret) : Mfx_Return_Fail;

    myMemberLock.UnLock(&myMaskImage);

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
    MfxParam msgParam;
    msgParam.push_back(UI_MSG_SetBackColor);
    msgParam.push_back(MfxColor(set));
    return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxUI::SetMaskColor(MfxColor* set)
{
    MfxParam msgParam;
    msgParam.push_back(UI_MSG_SetMaskColor);
    msgParam.push_back(MfxColor(set));
    return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxUI::SetBackImage(MfxImage* set)
{
    MfxParam msgParam;
    msgParam.push_back(UI_MSG_SetBackImage);
    msgParam.push_back(MfxImage(set));
    return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxUI::SetMaskImage(MfxImage* set)
{
    MfxParam msgParam;
    msgParam.push_back(UI_MSG_SetMaskImage);
    msgParam.push_back(MfxImage(set));
    return Send_Message(msgParam);
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
    myMemberLock.WaitLock(&myGlobeAlpha);
    *set = myGlobeAlpha;
    myMemberLock.UnLock(&myGlobeAlpha);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::GetGlobeAlphaMode(UINT set)
{
    myMemberLock.WaitLock(&myGlobeAlphaMode);
    set = myGlobeAlphaMode;
    myMemberLock.UnLock(&myGlobeAlphaMode);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::SetGlobeAlpha(MfxColor* set)
{
    myMemberLock.WaitLock(&myGlobeAlpha);

    myGlobeAlpha = set;
    LONG tA = 0;
    myGlobeAlpha.GetA(&tA);

    SetLayeredWindowAttributes(myWnd, myGlobeAlpha, tA, myGlobeAlphaMode);

    myMemberLock.UnLock(&myGlobeAlpha);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::SetGlobeAlphaMode(UINT set)
{
    myMemberLock.WaitLock(&myGlobeAlphaMode);
    myGlobeAlphaMode = set;
    myMemberLock.UnLock(&myGlobeAlphaMode);

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
MfxReturn MicroFlakeX::MfxUI::__OnTest00(MfxParam param)
{
    std::cout << "__OnTest00: wParam-" << GetParam_Safe(param, WPARAM, 1);
    std::cout << " lParam-" << GetParam_Safe(param, LPARAM, 1) << std::endl;

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::__OnTest01(MfxParam param)
{
    std::cout << "__OnTest01: wParam-" << GetParam_Safe(param, WPARAM, 1);
    std::cout << " lParam-" << GetParam_Safe(param, LPARAM, 1) << std::endl;

    return Mfx_Return_Fine;
}



/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::__OnCreate(MfxParam param)
{
    myMemberLock.WaitLock(&myRect);

    GetWorldRect(&myRect);
    HRGN tRNG = CreateRectRgn(0, 0, myRect.myWidth, myRect.myHeight);

    myMemberLock.UnLock(&myRect);
   
    MfxSize tSize(myRect.myWidth, myRect.myHeight);
    MfxRect tRect(0, 0, myRect.myWidth, myRect.myHeight);

    myMemberLock.WaitLock(&myCanvas);

    myCanvas.SetSize(&tSize);
    myCanvas.SetDC(GetWindowDC(myWnd));

    myMemberLock.UnLock(&myCanvas);


    myMemberLock.WaitLock(&myBackImage);

    myBackImage = new MfxImage(&myBackColor, &tRect);
    myBackImage->SetCanvas(&myCanvas);

    myMemberLock.UnLock(&myBackImage);

    SetWindowRgn(myWnd, tRNG, TRUE);

    DeleteObject(tRNG);

    SetWindowLong(myWnd, GWL_EXSTYLE, GetWindowLong(myWnd, GWL_EXSTYLE) | WS_EX_LAYERED);

    SetGlobeAlpha(&myBackColor);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::__OnDestroy(MfxParam param)
{
    MessageBox(NULL, L"__OnDestroy", L"__OnDestroy", 0);

    return Mfx_Return_Fine;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::__OnSize(MfxParam param)
{
    myMemberLock.WaitLock(&myRect);

    GetWorldRect(&myRect);
    MfxSize tSize;
    myRect.GetSize(&tSize);
    UnionInvalidateRect(&myRect);

    myMemberLock.UnLock(&myRect);


    myMemberLock.WaitLock(&myCanvas);
    myCanvas.SetSize(&tSize);
    myMemberLock.UnLock(&myCanvas);


    myMemberLock.WaitLock(&myBackImage);
    myBackImage ? myBackImage->SetSize(&tSize) : 0;
    myMemberLock.UnLock(&myBackImage);

    myMemberLock.WaitLock(&myMaskImage);
    myMaskImage ? myMaskImage->SetSize(&tSize) : 0;
    myMemberLock.UnLock(&myMaskImage);

    HRGN tRNG = CreateRectRgn(0, 0, tSize.myWidth, tSize.myHeight);

    SetWindowRgn(myWnd, tRNG, TRUE);

    DeleteObject(tRNG);

    MfxMessage message = GetParam(param, MfxMessage, 0);
    WPARAM wParam = GetParam_Safe(param, WPARAM, 1);
    LPARAM lParam = GetParam_Safe(param, LPARAM, 2);

    return DefWindowProc(myWnd, message, wParam, lParam);
}

MfxReturn MicroFlakeX::MfxUI::__OnMove(MfxParam param)
{
    myMemberLock.WaitLock(&myRect);
    GetWorldRect(&myRect);
    myMemberLock.UnLock(&myRect);

    MfxMessage message = GetParam(param, MfxMessage, 0);
    WPARAM wParam = GetParam_Safe(param, WPARAM, 1);
    LPARAM lParam = GetParam_Safe(param, LPARAM, 2);

    return DefWindowProc(myWnd, message, wParam, lParam);
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::__OnPaint(MfxParam param)
{
    PAINTSTRUCT t_Paint{0};

    HDC t_Dc = BeginPaint(myWnd, &t_Paint);

    bool isEmpty = true;

    myMemberLock.WaitLock(&myInvalidateRect);
    myInvalidateRect.IsEmpty(&isEmpty);
    myMemberLock.UnLock(&myInvalidateRect);

    if (!isEmpty)
    {
        myMemberLock.TryWaitLock(&myCanvas, &myInvalidateRect);

        myCanvas.PaintBegin(&myInvalidateRect);
        myInvalidateRect.Reset(0, 0, 0, 0);

        myMemberLock.UnLock(&myCanvas, &myInvalidateRect);

        MfxParam msgParam1;
        msgParam1.push_back(UI_MSG_PaintBack);
        Send_Message(msgParam1);

        MfxParam msgParam2;
        msgParam2.push_back(UI_MSG_PaintMask);
        ProcMessage(msgParam2);

        myMemberLock.WaitLock(&myCanvas);
        myCanvas.PaintFinish();
        myMemberLock.UnLock(&myCanvas);
    }

    EndPaint(myWnd, &t_Paint);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::__OnEraseBackGrand(MfxParam param)
{
    return 1;
}

MfxReturn MicroFlakeX::MfxUI::__OnPaintBackDC(MfxParam param)
{
    myMemberLock.WaitLock(&myBackImage);
    myBackImage ? myBackImage->Paint() : 0;
    myMemberLock.UnLock(&myBackImage);

    MfxParam msgParam;
    msgParam.push_back(FLAKE_MSG_PaintBack);
    RProcFlakesMessage(msgParam);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::__OnPaintMaskDC(MfxParam param)
{
    MfxParam msgParam;
    msgParam.push_back(FLAKE_MSG_PaintMask);
    RProcFlakesMessage(msgParam);

    myMemberLock.WaitLock(&myMaskImage);
    myMaskImage ? myMaskImage->Paint() : 0;
    myMemberLock.UnLock(&myMaskImage);

    return Mfx_Return_Fine;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::__OnFlakeInsert(MfxParam param)
{
    pMfxFlake tpFlake = GetParam_Safe(param, pMfxFlake, 1);
    if (tpFlake)
    {
        myMemberLock.WaitLock(&myFlakeSet);
        bool tIns = myFlakeSet.insert(tpFlake).second;
        myMemberLock.UnLock(&myFlakeSet);

        if(tIns)
        {
            myMemberLock.WaitLock(&myFlakeDeque);
            myFlakeDeque.push_back(tpFlake);
            myMemberLock.UnLock(&myFlakeDeque);

            myMemberLock.TryWaitLock(&myWnd, &myCanvas);

            MfxParam msgParam;
            msgParam.push_back(FLAKE_MSG_SetPaper);
            msgParam.push_back(Paper_Infor(this, myWnd, &myCanvas));
            tpFlake->Send_Message(msgParam);

            myMemberLock.UnLock(&myWnd, &myCanvas);

            PostMessage(myWnd, UI_MSG_FlakeFloorChange, NULL, NULL);

            myMemberLock.WaitLock(&myRect);
            UnionInvalidateRect(&myRect);
            myMemberLock.UnLock(&myRect);

            return Mfx_Return_Fine;
        }
    }

    return Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxUI::__OnFlakeRemove(MfxParam param)
{
    pMfxFlake tpFlake = GetParam_Safe(param, pMfxFlake, 1);
    if (tpFlake)
    {
        myMemberLock.WaitLock(&myFlakeSet);
        bool tFind = myFlakeSet.find(tpFlake) != myFlakeSet.end();
        myMemberLock.UnLock(&myFlakeSet);

        if (tFind)
        {
            myMemberLock.WaitLock(&myFlakeDeque);
            for (auto delIt = myFlakeDeque.begin(); delIt != myFlakeDeque.end(); delIt++)
            {
                if (*delIt == (tpFlake))
                {

                    MfxParam msgParam;
                    msgParam.push_back(FLAKE_MSG_RemovePaper);
                    tpFlake->Send_Message(msgParam);

                    myFlakeDeque.erase(delIt);

                    myMemberLock.WaitLock(&myFlakeSet);
                    myFlakeSet.erase(tpFlake);
                    myMemberLock.UnLock(&myFlakeSet);

                    PostMessage(myWnd, UI_MSG_FlakeFloorChange, NULL, NULL);

                    InvalidateRect(myWnd, nullptr, TRUE);

                    break;
                }
            }
            myMemberLock.UnLock(&myFlakeDeque);
        }
    }

    return Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxUI::__OnFlakeFloorChange(MfxParam param)
{
    myMemberLock.WaitLock(&myFlakeDeque);

    std::sort(myFlakeDeque.begin(), myFlakeDeque.end(), pFloorCompare<MfxFlake>);

    myMemberLock.UnLock(&myFlakeDeque);

    return Mfx_Return_Fine;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::__OnTimer(MfxParam param)
{
    auto tRet = Mfx_Return_Fail;
    myMemberLock.WaitLock(&myTimerMap);

    auto t_Iter = myTimerMap.find(GetParam_Safe(param, WPARAM, 1));
    if (t_Iter != myTimerMap.end())
    {
        MfxParam msgParam;
        msgParam.push_back(t_Iter->second);
        tRet = (this->*t_Iter->second.recvFunc)(msgParam);
    }

    myMemberLock.UnLock(&myTimerMap);

    return tRet;
}

MfxReturn MicroFlakeX::MfxUI::__OnInsertTimer(MfxParam param)
{
    auto tRet = Mfx_Return_Fail;
    UI_UITimer_Info tTimer = GetParam_Safe(param, UI_UITimer_Info, 1);

    myMemberLock.WaitLock(&myTimerMap);
    bool tIns = myTimerMap.insert(UI_UITimer_Map_Elem(tTimer.myID, tTimer)).second;
    myMemberLock.UnLock(&myTimerMap);

    if (tIns)
    {
        SetTimer(myWnd, tTimer.myID, tTimer.delayTime, (TIMERPROC)nullptr);
        tRet = Mfx_Return_Fine;
    }

    return tRet;
}

MfxReturn MicroFlakeX::MfxUI::__OnRemoveTimer(MfxParam param)
{
    auto tRet = Mfx_Return_Fail;
    UI_UITimer_Info tTimer = GetParam_Safe(param, UI_UITimer_Info, 1);

    myMemberLock.WaitLock(&myTimerMap);

    auto iter = myTimerMap.find(tTimer.myID);
    if (iter != myTimerMap.end())
    {
        KillTimer(myWnd, tTimer.myID);

        myTimerMap.erase(tTimer.myID);

        tRet = Mfx_Return_Fine;
    }

    myMemberLock.UnLock(&myTimerMap);

    return tRet;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::__OnFlakeEvent(MfxParam param)
{
    MfxReturn tRet = Mfx_Return_Fail;

    myMemberLock.WaitLock(&myFlakeEventMap);

    FlakeEvent_Info tInfo = GetParam_Safe(param, FlakeEvent_Info, 1);

    auto t_Iter = myFlakeEventMap.find(tInfo);
    if (t_Iter != myFlakeEventMap.end())
    {
        if (!t_Iter->second.empty())
        {
            for (auto i : (t_Iter->second))
            {
                tRet = (this->*i.recvFunc)(param);
            }
        }
    }

    myMemberLock.UnLock(&myFlakeEventMap);

    return tRet;
}

MfxReturn MicroFlakeX::MfxUI::__OnRemoveFlakeEvent(MfxParam param)
{
    MfxReturn tRet = Mfx_Return_Fail;

    FlakeEvent_Info tFlakeEvent = GetParam_Safe(param, FlakeEvent_Info, 1);
    MfxString tRecvFuncName = GetParam_Safe(param, MfxString, 2);

    myMemberLock.WaitLock(&myFlakeEventMap);

    auto t_Iter = myFlakeEventMap.find(tFlakeEvent);
    if (t_Iter != myFlakeEventMap.end())
    {
        for (auto i = t_Iter->second.begin(); i != t_Iter->second.end(); i++)
        {
            if ((*i).myRecvFuncName == tRecvFuncName)
            {
                t_Iter->second.erase(i);
                tRet = Mfx_Return_Fine;
                break;
            }
        }
    }

    myMemberLock.UnLock(&myFlakeEventMap);

    return tRet;
}

MfxReturn MicroFlakeX::MfxUI::__OnPushBackFlakeEvent(MfxParam param)
{
    myMemberLock.WaitLock(&myFlakeEventMap);

    FlakeEvent_Info tFlakeEvent = GetParam_Safe(param, FlakeEvent_Info, 1);
    UI_UIRecvFunc_Info tRecvInfo = GetParam_Safe(param, UI_UIRecvFunc_Info, 2);

Begin:
    auto t_Iter = myFlakeEventMap.find(tFlakeEvent);
    if (t_Iter == myFlakeEventMap.end())
    {
        t_Iter = myFlakeEventMap.insert(UI_FlakeMsg_Map_Elem(tFlakeEvent, UI_UIRecvFunc_Infor_Deque())).first;
        goto Begin;
    }
    else
    {
        t_Iter->second.push_back(tRecvInfo);
    }

    myMemberLock.UnLock(&myFlakeEventMap);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::__OnPushFrontFlakeEvent(MfxParam param)
{
    myMemberLock.WaitLock(&myFlakeEventMap);

    FlakeEvent_Info tFlakeEvent = GetParam_Safe(param, FlakeEvent_Info, 1);
    UI_UIRecvFunc_Info tRecvInfo = GetParam_Safe(param, UI_UIRecvFunc_Info, 2);

Begin:
    auto t_Iter = myFlakeEventMap.find(tFlakeEvent);
    if (t_Iter == myFlakeEventMap.end())
    {
        t_Iter = myFlakeEventMap.insert(UI_FlakeMsg_Map_Elem(tFlakeEvent, UI_UIRecvFunc_Infor_Deque())).first;
        goto Begin;
    }
    else
    {
        t_Iter->second.push_front(tRecvInfo);
    }

    myMemberLock.UnLock(&myFlakeEventMap);

    return Mfx_Return_Fine;
}

/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::__OnOpenPercentRect(MfxParam param)
{
    myMemberLock.WaitLock(&myPercentRectFlag);
    myPercentRectFlag = true;
    myMemberLock.UnLock(&myPercentRectFlag);

    MfxParam msgParam;
    msgParam.push_back(FLAKE_MSG_OpenPercentRect);
    ProcFlakesMessage(msgParam);

    return Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxUI::__OnClosePercentRect(MfxParam param)
{
    myMemberLock.WaitLock(&myPercentRectFlag);
    myPercentRectFlag = false;
    myMemberLock.UnLock(&myPercentRectFlag);

    return Mfx_Return_Fine;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::__OnSetBackColor(MfxParam param)
{
    myMemberLock.WaitLock(&myRect);
    MfxSize tSize(myRect);
    myMemberLock.UnLock(&myRect);

    myMemberLock.TryWaitLock(&myBackImage, &myBackColor, &myCanvas);
    myBackColor = GetParam_Safe(param, MfxColor, 1);
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
    myMemberLock.UnLock(&myBackImage, &myBackColor, &myCanvas);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::__OnSetMaskColor(MfxParam param)
{
    myMemberLock.WaitLock(&myRect);
    MfxSize tSize(myRect);
    myMemberLock.UnLock(&myRect);

    myMemberLock.TryWaitLock(&myMaskColor, &myMaskImage, &myCanvas);
    myMaskColor = GetParam_Safe(param, MfxColor, 1);
    if (myMaskImage)
    {
        myMaskImage->FromColor(&myMaskColor, &tSize);
    }
    else
    {
        myMaskImage = new MfxImage(&myMaskColor, &tSize);

        myMaskImage->SetCanvas(&myCanvas);
    }
    myMemberLock.UnLock(&myBackImage, &myBackColor, &myCanvas);

    return Mfx_Return_Fine;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::__OnSetBackImage(MfxParam param)
{
    myMemberLock.TryWaitLock(&myBackImage, &myRect, &myCanvas);

    SafeDelete(myBackImage);
    (GetParam_Safe(param, MfxImage, 1)).Clone(&myBackImage);
    MfxRect tRect(0, 0, myRect.myWidth, myRect.myHeight);
    myBackImage->SetRect(&tRect);
    myBackImage->SetCanvas(&myCanvas);

    myMemberLock.UnLock(&myBackImage, &myRect, &myCanvas);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::__OnSetMaskImage(MfxParam param)
{
    myMemberLock.TryWaitLock(&myMaskImage, &myRect, &myCanvas);

    SafeDelete(myMaskImage);
    (GetParam_Safe(param, MfxImage, 1)).Clone(&myMaskImage);
    MfxRect tRect(0, 0, myRect.myWidth, myRect.myHeight);
    myMaskImage->SetRect(&tRect);
    myMaskImage->SetCanvas(&myCanvas);

    myMemberLock.UnLock(&myMaskImage, &myRect, &myCanvas);

    return Mfx_Return_Fine;
}

/********************************************************************************
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::__OnNCPaint(MfxParam param)
{
    return 1;
}

MfxReturn MicroFlakeX::MfxUI::__OnNCActivate(MfxParam param)
{
    return GetParam_Safe(param, WPARAM, 1) ? 0 : 1;
}

MfxReturn MicroFlakeX::MfxUI::__OnNCHitTest(MfxParam param)
{
    MfxMessage message = GetParam(param, MfxMessage, 0);
    WPARAM wParam = GetParam_Safe(param, WPARAM, 1);
    LPARAM lParam = GetParam_Safe(param, LPARAM, 2);

    MfxReturn ret = DefWindowProc(myWnd, message, wParam, lParam);

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
MfxReturn MicroFlakeX::MfxUI::__OnNCMouseMove(MfxParam param)
{
    if (myMutexFocus)
    {
        return 0;
    }
    return DefWindowProc(myWnd, WM_NCMOUSEMOVE, GetParam_Safe(param, WPARAM, 1), GetParam_Safe(param, LPARAM, 2));
}

MfxReturn MicroFlakeX::MfxUI::__OnNCMouseHover(MfxParam param)
{
    if (myMutexFocus)
    {
        return 0;
    }
    return DefWindowProc(myWnd, WM_NCMOUSEHOVER, GetParam_Safe(param, WPARAM, 1), GetParam_Safe(param, LPARAM, 2));
}


/********************************************************************************
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::__OnNCLButtonUp(MfxParam param)
{
    return myMutexFocus ? 0 : DefWindowProc(myWnd, WM_NCLBUTTONUP, GetParam_Safe(param, WPARAM, 1), GetParam_Safe(param, LPARAM, 2));
}

MfxReturn MicroFlakeX::MfxUI::__OnNCLButtonDown(MfxParam param)
{
    return myMutexFocus ? 0 : DefWindowProc(myWnd, WM_NCLBUTTONDOWN, GetParam_Safe(param, WPARAM, 1), GetParam_Safe(param, LPARAM, 2));
}

MfxReturn MicroFlakeX::MfxUI::__OnNCLButtonDouble(MfxParam param)
{
    return myMutexFocus ? 0 : DefWindowProc(myWnd, WM_NCLBUTTONDBLCLK, GetParam_Safe(param, WPARAM, 1), GetParam_Safe(param, LPARAM, 2));
}


/********************************************************************************
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::__OnNCRButtonUp(MfxParam param)
{
    return myMutexFocus ? 0 : DefWindowProc(myWnd, WM_NCRBUTTONUP, GetParam_Safe(param, WPARAM, 1), GetParam_Safe(param, LPARAM, 2));
}

MfxReturn MicroFlakeX::MfxUI::__OnNCRButtonDown(MfxParam param)
{
    return myMutexFocus ? 0 : DefWindowProc(myWnd, WM_NCRBUTTONDOWN, GetParam_Safe(param, WPARAM, 1), GetParam_Safe(param, LPARAM, 2));
}

MfxReturn MicroFlakeX::MfxUI::__OnNCRButtonDouble(MfxParam param)
{
    return myMutexFocus ? 0 : DefWindowProc(myWnd, WM_NCRBUTTONDBLCLK, GetParam_Safe(param, WPARAM, 1), GetParam_Safe(param, LPARAM, 2));
}