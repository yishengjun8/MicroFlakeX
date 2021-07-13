#include "pch.h"
#include "MfxAppFrame.h"

MFXOBJ_REFLECTION_INIT(MfxUI)
MFXOBJ_REFLECTION_ENDINIT(MfxUI, MfxBase, \
    CreateSuccess, \
    \
    ProcFlakesMessage, \
    RProcFlakesMessage, \
    \
    Send_Message, \
    Post_Message, \
    \
    RemoveFlake, \
    InsertFlake, \
    \
    RemoveWin32Timer, \
    InsertWin32Timer, \
    \
    RemoveUIMessage, \
    PushBackUIMessage, \
    PushFrontUIMessage, \
    \
    OpenPercentRect, \
    ClosePercentRect, \
    ChickPercentRect, \
    \
    RemoveFlakeEvent, \
    PushBackFlakeEvent, \
    PushFrontFlakeEvent, \
    \
    LockMutexFocus, \
    UnLockMutexFocus, \
    \
    SetMutexFocus, \
    GetMutexFocus, \
    SetKeyboardFocus, \
    GetKeyboardFocus, \
    \
    UnionInvalidateRect, \
    \
    GetWnd, \
    GetCanvas, \
    \
    GetWorldRect, \
    GetLocalMousePos, \
    TransWorldRectToLocalRect, \
    TransWorldPointToLocalPoint, \
    \
    \
    GetRect, \
    GetSize, \
    GetPoint, \
    GetBackColor, \
    GetMaskColor, \
    \
    SetRect, \
    SetSize, \
    SetPoint, \
    SetBackColor, \
    SetMaskColor, \
    \
    GetGlobeAlpha, \
    GetGlobeAlphaMode, \
    SetGlobeAlpha, \
    SetGlobeAlphaMode, \
    \
    WND_MAX, \
    WND_MIN, \
    WND_SHOW, \
    WND_HIDE, \
    WND_NORMAL \

);

#define UI_RECV(msg, func) UI_ADDRECV_UIMSG(msg, MfxUI, func)

void MicroFlakeX::MfxUI::RegisterRecvFunc()
{
    UI_RECV(WM_NCPAINT, __OnNCPaint);
    UI_RECV(WM_NCHITTEST, __OnNCHitTest);
    UI_RECV(WM_NCACTIVATE, __OnNCActivate);

    UI_RECV(WM_NCMOUSEMOVE, __OnNCMouseMove);
    UI_RECV(WM_NCMOUSEHOVER, __OnNCMouseHover);

    UI_RECV(WM_NCLBUTTONUP, __OnNCLButtonUp);
    UI_RECV(WM_NCLBUTTONDOWN, __OnNCLButtonDown);
    UI_RECV(WM_NCLBUTTONDBLCLK, __OnNCLButtonDouble);

    UI_RECV(WM_NCRBUTTONUP, __OnNCRButtonUp);
    UI_RECV(WM_NCRBUTTONDOWN, __OnNCRButtonDown);
    UI_RECV(WM_NCRBUTTONDBLCLK, __OnNCRButtonDouble);

    /********************************************************************************
    *
    *********************************************************************************/
    UI_RECV(WM_CREATE, __OnCreate);
    UI_RECV(WM_DESTROY, __OnDestroy);

    UI_RECV(WM_SIZE, __OnSize);
    UI_RECV(WM_MOVE, __OnMove);

    UI_RECV(WM_TIMER, __OnWin32Timer);

    UI_RECV(WM_PAINT, __OnPaint);
    UI_RECV(WM_ERASEBKGND, __OnEraseBackGrand);

    UI_RECV(UI_MSG_PaintBack, __OnPaintBackDC);
    UI_RECV(UI_MSG_PaintMask, __OnPaintMaskDC);

    UI_RECV(MSG_FlakeInsert, __OnFlakeInsert);
    UI_RECV(MSG_FlakeRemove, __OnFlakeRemove);
    UI_RECV(MSG_FlakeFloorChange, __OnFlakeFloorChange);

    UI_RECV(UI_MSG_RemoveWin32Timer, __OnRemoveWin32Timer);
    UI_RECV(UI_MSG_InsertWin32Timer, __OnInsertWin32Timer);

    UI_RECV(MSG_FlakeEvent, __OnFlakeEvent);

    UI_RECV(UI_MSG_RemoveFlakeEvent, __OnRemoveFlakeEvent);
    UI_RECV(UI_MSG_PushBackFlakeEvent, __OnPushBackFlakeEvent);
    UI_RECV(UI_MSG_PushFrontFlakeEvent, __OnPushFrontFlakeEvent);

    UI_RECV(UI_MSG_OpenPercentRect, __OnOpenPercentRect);
    UI_RECV(UI_MSG_ClosePercentRect, __OnClosePercentRect);

    UI_RECV(UI_MSG_SetBackColor, __OnSetBackColor);
    UI_RECV(UI_MSG_SetMaskColor, __OnSetMaskColor);
}

void MicroFlakeX::MfxUI::InitData_UI()
{
    myGlobeAlphaMode = LWA_COLORKEY; //LWA_COLORKEY  LWA_ALPHA

    myWnd = nullptr;

    myMutexFocus = nullptr;
    myKeyboardFocus = nullptr;
    myMutexFocusLockFlag = false;
    myKeyboardFocusLockFlag = false;

    myPercentRectFlag = false;

    myBackColor.Reset(255, 0, 255, 255);
    myMaskColor.Reset(0, 0, 0, 0);
}

/********************************************************************************
*
*
*
*
*********************************************************************************/
MicroFlakeX::MfxUI::MfxUI(MfxRect set, MfxString title, DWORD myStyle, DWORD myStyleEx, MfxUI* father)
{
    InitData_UI();
    RegisterRecvFunc();

    MfxCreateWindowsEx(this, father, set, myStyle, myStyleEx | WS_EX_LAYERED, MfxText("MfxNormalUI"), title);
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
}

MfxReturn MicroFlakeX::MfxUI::CreateSuccess()
{
    return myWnd ? MfxReturn_Seccess : MfxReturn_Failed;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(ProcMessage)
{
    MfxReturn tRet = MfxReturn_Failed;
    myMemberLock.TryWaitLock(&myMessageMap);

    ProcFlakesMessage(param);

    auto t_Iter = myMessageMap.find(getMSG);
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
        tRet = DefWindowProc(getHWND, getMSG, getWPARAM, getLPARAM);
    }

    myMemberLock.UnLock(&myMessageMap);

    return tRet;
}

MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(ProcFlakesMessage)
{
    MfxReturn t_Ret = MfxReturn_Failed;
    MfxFlake* t_FloatFocus = myMutexFocus;
    myMutexFocus = myMutexFocusLockFlag ? myMutexFocus : nullptr;
    for (auto t_Iter : myFlakeDeque)
    {
        t_Ret = t_Iter->Send_Message(param);
    }
    return t_Ret;
}

MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(RProcFlakesMessage)
{
    MfxReturn t_Ret = MfxReturn_Failed;
    MfxFlake* t_FloatFocus = myMutexFocus;
    myMutexFocus = myMutexFocusLockFlag ? myMutexFocus : nullptr;
    for (int i = myFlakeDeque.size() - 1; i >= 0; i--)
    {
        t_Ret = myFlakeDeque[i]->Send_Message(param);
    }
    return t_Ret;
}

MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(Send_Message)
{
    return ProcMessage(param);
}

MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(Post_Message)
{
    return MfxBeginNewThread(this, MfxText("Send_Message"), param);
}



/********************************************************************************
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::RemoveFlake(MfxFlake* set)
{
    MfxParam msgParam(MSG_FlakeRemove);
    msgParam.push_back(set);
    return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxUI::InsertFlake(MfxFlake* set)
{
    MfxParam msgParam(MSG_FlakeInsert);
    msgParam.push_back(set);
    return Send_Message(msgParam);
}

/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::RemoveWin32Timer(ULONG setID)
{
    MfxParam msgParam(UI_MSG_RemoveWin32Timer);
    msgParam.push_back(setID);
    return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxUI::InsertWin32Timer(Win32_Timer_Info timer)
{
    MfxParam msgParam(UI_MSG_InsertWin32Timer);
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
    MfxReturn tRet = MfxReturn_Failed;

    myMemberLock.WaitLock(&myMessageMap);

    auto t_Iter = myMessageMap.find(message);
    if (t_Iter != myMessageMap.end())
    {
        for (auto i = t_Iter->second.begin(); i != t_Iter->second.end(); i++)
        {
            if ((*i).myRecvFuncName == recvFuncName)
            {
                t_Iter->second.erase(i);
                tRet = MfxReturn_Seccess;
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

    return MfxReturn_Seccess;
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

    return MfxReturn_Seccess;
}


/********************************************************************************
* 
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::RemoveFlakeEvent(FlakeEvent_Info flakeEvent, MfxString recvFuncName)
{
    MfxParam msgParam(UI_MSG_RemoveFlakeEvent);
    msgParam.push_back(flakeEvent);
    msgParam.push_back(recvFuncName);
    return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxUI::PushBackFlakeEvent(FlakeEvent_Info flakeEvent, UI_UIRecvFunc_Info recvInfo)
{
    MfxParam msgParam(UI_MSG_PushBackFlakeEvent);
    msgParam.push_back(flakeEvent);
    msgParam.push_back(recvInfo);
    return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxUI::PushFrontFlakeEvent(FlakeEvent_Info flakeEvent, UI_UIRecvFunc_Info recvInfo)
{
    MfxParam msgParam(UI_MSG_PushFrontFlakeEvent);
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
    MfxParam msgParam(UI_MSG_OpenPercentRect);
    return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxUI::ClosePercentRect()
{
    MfxParam msgParam(UI_MSG_ClosePercentRect);
    return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxUI::ChickPercentRect(bool* ret)
{
    *ret = myPercentRectFlag;

    return  MfxReturn_Seccess;
}
/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::LockMutexFocus(MfxFlake* set)
{
    auto tRet = MfxReturn_Failed;

    myMemberLock.TryWaitLock(&myMutexFocusLockFlag, &myMutexFocus);

    if (myMutexFocusLockFlag)
    {
        tRet = (myMutexFocus == set) ? MfxReturn_Seccess : MfxReturn_Failed;
    }
    else
    {
        myMutexFocus = set;
        myMutexFocusLockFlag = true;
        tRet = MfxReturn_Seccess;
    }

    myMemberLock.UnLock(&myMutexFocusLockFlag, &myMutexFocus);

    return tRet;
}

MfxReturn MicroFlakeX::MfxUI::UnLockMutexFocus()
{
    myMemberLock.WaitLock(&myMutexFocusLockFlag);
    myMutexFocus = nullptr;
    myMutexFocusLockFlag = false;
    myMemberLock.UnLock(&myMutexFocusLockFlag);

    return MfxReturn_Seccess;
}


/********************************************************************************
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::SetMutexFocus(MfxFlake* set)
{
    auto tRet = MfxReturn_Failed;

    myMemberLock.TryWaitLock(&myMutexFocusLockFlag, &myMutexFocus);

    if (!myMutexFocus && !myMutexFocusLockFlag)
    {
        myMutexFocus = set;
        tRet = MfxReturn_Seccess;
    }
    else
    {
        tRet = (myMutexFocus == set) ? MfxReturn_Seccess : MfxReturn_Failed;
    }

    myMemberLock.UnLock(&myMutexFocusLockFlag, &myMutexFocus);

    return tRet;
}

MfxReturn MicroFlakeX::MfxUI::GetMutexFocus(MfxFlake** ret)
{
    myMemberLock.WaitLock(&myMutexFocus);
    *ret = myMutexFocus;
    myMemberLock.UnLock(&myMutexFocus);

    return MfxReturn_Seccess;
}

/********************************************************************************
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::SetKeyboardFocus(MfxFlake* set)
{
    auto tRet = MfxReturn_Failed;

    myMemberLock.TryWaitLock(&myKeyboardFocusLockFlag, &myKeyboardFocus);

    if (!myKeyboardFocus && !myKeyboardFocusLockFlag)
    {
        myKeyboardFocus = set;
        tRet = MfxReturn_Seccess;
    }
    else
    {
        tRet = myKeyboardFocus == set ? MfxReturn_Seccess : MfxReturn_Failed;
    }

    myMemberLock.UnLock(&myKeyboardFocusLockFlag, &myKeyboardFocus);

    return tRet;
}

MfxReturn MicroFlakeX::MfxUI::GetKeyboardFocus(MfxFlake** ret)
{
    myMemberLock.WaitLock(&myKeyboardFocus);
    *ret = myKeyboardFocus;
    myMemberLock.UnLock(&myKeyboardFocus);

    return MfxReturn_Seccess;
}

MfxReturn MicroFlakeX::MfxUI::UnionInvalidateRect(MfxRect set, double inflate)
{
    set.Inflate(inflate, inflate);

    RECT tRECT;
    set.GetRECT(&tRECT);
    InvalidateRect(myWnd, &tRECT, TRUE);

    myMemberLock.WaitLock(&myInvalidateRect);

    bool isEmpty = false;
    myInvalidateRect.IsEmpty(&isEmpty);
    if (isEmpty)
    {
        myInvalidateRect = set;
    }
    else
    {
        myInvalidateRect.Union(&set, &myInvalidateRect);
    }

    myMemberLock.UnLock(&myInvalidateRect);

    return MfxReturn_Seccess;
}

/********************************************************************************
* 
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::GetWnd(HWND* ret)
{
    *ret = myWnd;

    return MfxReturn_Seccess;
}

MfxReturn MicroFlakeX::MfxUI::GetCanvas(MfxCanvas** ret)
{
    *ret = &myCanvas;

    return MfxReturn_Seccess;
}

MfxReturn MicroFlakeX::MfxUI::GetWorldRect(MfxRect* ret)
{
    RECT tWorldRECT;
    GetWindowRect(myWnd, &tWorldRECT);

    ret->SetRECT(&tWorldRECT);

    return MfxReturn_Seccess;
}

MfxReturn MicroFlakeX::MfxUI::GetLocalMousePos(MfxPoint* ret)
{
    POINT tPOINT;
    GetCursorPos(&tPOINT);

    MfxPoint tPoint;
    GetPoint(&tPoint);

    ret->Reset(tPOINT.x - tPoint.myX, tPOINT.y - tPoint.myY);

    return MfxReturn_Seccess;
}

MfxReturn MicroFlakeX::MfxUI::TransWorldRectToLocalRect(MfxRect* world, MfxRect* local)
{
    RECT tWorldRECT;
    GetWindowRect(myWnd, &tWorldRECT);

    local->SetRECT(&tWorldRECT);

    world->myX -= local->myX;
    world->myY -= local->myY;

    return MfxReturn_Seccess;
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

    return MfxReturn_Seccess;
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

    return MfxReturn_Seccess;
}

MfxReturn MicroFlakeX::MfxUI::GetSize(MfxSize* ret)
{
    myMemberLock.WaitLock(&myRect);
    myRect.GetSize(ret);
    myMemberLock.UnLock(&myRect);

    return MfxReturn_Seccess;
}

MfxReturn MicroFlakeX::MfxUI::GetPoint(MfxPoint* ret)
{
    myMemberLock.WaitLock(&myRect);
    myRect.GetPoint(ret);
    myMemberLock.UnLock(&myRect);

    return MfxReturn_Seccess;
}

MfxReturn MicroFlakeX::MfxUI::GetBackColor(MfxColor* ret)
{
    myMemberLock.WaitLock(&myBackColor);
    myBackColor.GetColor(ret);
    myMemberLock.UnLock(&myBackColor);

    return MfxReturn_Seccess;
}

MfxReturn MicroFlakeX::MfxUI::GetMaskColor(MfxColor* ret)
{
    myMemberLock.WaitLock(&myMaskColor);
    myMaskColor.GetColor(ret);
    myMemberLock.UnLock(&myMaskColor);

    return MfxReturn_Seccess;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::SetRect(MfxRect* set)
{
    return SetWindowPos(myWnd, nullptr, set->myX, set->myY, set->myWidth, set->myHeight, SWP_NOZORDER) ? MfxReturn_Seccess : MfxReturn_Failed;
}

MfxReturn MicroFlakeX::MfxUI::SetSize(MfxSize* set)
{
    return SetWindowPos(myWnd, nullptr, 0, 0, set->myWidth, set->myHeight, SWP_NOMOVE | SWP_NOZORDER) ? MfxReturn_Seccess : MfxReturn_Failed;
}

MfxReturn MicroFlakeX::MfxUI::SetPoint(MfxPoint* set)
{
    return SetWindowPos(myWnd, nullptr, set->myX, set->myY, 0, 0, SWP_NOSIZE | SWP_NOZORDER) ? MfxReturn_Seccess : MfxReturn_Failed;
}

MfxReturn MicroFlakeX::MfxUI::SetBackColor(MfxColor* set)
{
    MfxParam msgParam(UI_MSG_SetBackColor);
    msgParam.push_back(MfxColor(set));
    return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxUI::SetMaskColor(MfxColor* set)
{
    MfxParam msgParam(UI_MSG_SetMaskColor);
    msgParam.push_back(MfxColor(set));
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

    return MfxReturn_Seccess;
}

MfxReturn MicroFlakeX::MfxUI::GetGlobeAlphaMode(UINT set)
{
    myMemberLock.WaitLock(&myGlobeAlphaMode);
    set = myGlobeAlphaMode;
    myMemberLock.UnLock(&myGlobeAlphaMode);

    return MfxReturn_Seccess;
}

MfxReturn MicroFlakeX::MfxUI::SetGlobeAlpha(MfxColor* set)
{
    myMemberLock.WaitLock(&myGlobeAlpha);

    myGlobeAlpha = set;
    LONG tA = 0;
    myGlobeAlpha.GetA(&tA);

    SetLayeredWindowAttributes(myWnd, myGlobeAlpha, tA, myGlobeAlphaMode);

    myMemberLock.UnLock(&myGlobeAlpha);

    return MfxReturn_Seccess;
}

MfxReturn MicroFlakeX::MfxUI::SetGlobeAlphaMode(UINT set)
{
    myMemberLock.WaitLock(&myGlobeAlphaMode);
    myGlobeAlphaMode = set;
    myMemberLock.UnLock(&myGlobeAlphaMode);

    return MfxReturn_Seccess;
}


/********************************************************************************
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::WND_MAX()
{
    return ShowWindow(myWnd, SW_MAXIMIZE) ? MfxReturn_Seccess : MfxReturn_Failed;
}

MfxReturn MicroFlakeX::MfxUI::WND_MIN()
{
    return ShowWindow(myWnd, SW_MINIMIZE) ? MfxReturn_Seccess : MfxReturn_Failed;
}

MfxReturn MicroFlakeX::MfxUI::WND_SHOW()
{
    return ShowWindow(myWnd, SW_SHOW) ? MfxReturn_Seccess : MfxReturn_Failed;
}

MfxReturn MicroFlakeX::MfxUI::WND_HIDE()
{
    return ShowWindow(myWnd, SW_HIDE) ? MfxReturn_Seccess : MfxReturn_Failed;
}

MfxReturn MicroFlakeX::MfxUI::WND_NORMAL()
{
    return ShowWindow(myWnd, SW_NORMAL) ? MfxReturn_Seccess : MfxReturn_Failed;
}


/********************************************************************************
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(__OnTest00)
{
    std::cout << "__OnTest00: wParam-" << getWPARAM;
    std::cout << " lParam-" << getLPARAM << std::endl;

    MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}

MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(__OnTest01)
{
    std::cout << "__OnTest01: wParam-" << getWPARAM;
    std::cout << " lParam-" << getLPARAM << std::endl;

    MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}



/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(__OnCreate)
{
    myMemberLock.TryWaitLock(&myRect, &myWnd);

    myWnd = getHWND;
    GetWorldRect(&myRect);
    HRGN tRNG = CreateRectRgn(0, 0, myRect.myWidth, myRect.myHeight);
    MfxSize tSize(myRect.myWidth, myRect.myHeight);
    MfxRect tRect(0, 0, myRect.myWidth, myRect.myHeight);

    myMemberLock.UnLock(&myRect, &myWnd);
   
    myMemberLock.WaitLock(&myCanvas);
    myCanvas.SetSize(&tSize);
    myCanvas.SetDC(GetWindowDC(myWnd));
    myMemberLock.UnLock(&myCanvas);


    myMemberLock.TryWaitLock(&myBackColor, &myBackRectangle, &myMaskColor, &myMaskRectangle);

    MfxColor tColor;
    myBackRectangle.SetSize(&tSize);
    myMaskRectangle.SetSize(&tSize);
    myBackRectangle.SetCanvas(&myCanvas);
    myMaskRectangle.SetCanvas(&myCanvas);
    myBackRectangle.SetFrameColor(&tColor);
    myMaskRectangle.SetFrameColor(&tColor);
    myBackRectangle.SetFillColor(&myBackColor);
    myMaskRectangle.SetFillColor(&myMaskColor);

    myMemberLock.UnLock(&myBackColor, &myBackRectangle, &myMaskColor, &myMaskRectangle);

    SetWindowRgn(myWnd, tRNG, TRUE);

    DeleteObject(tRNG);

    //SetWindowLong(myWnd, GWL_EXSTYLE, GetWindowLong(myWnd, GWL_EXSTYLE) | WS_EX_LAYERED);

    SetGlobeAlpha(&tColor);

    MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}

MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(__OnDestroy)
{
    MessageBox(NULL, L"__OnDestroy", L"__OnDestroy", 0);

    MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(__OnSize)
{
    myMemberLock.WaitLock(&myRect);

    GetWorldRect(&myRect);
    MfxSize tSize;
    myRect.GetSize(&tSize);
    UnionInvalidateRect(tSize);

    myMemberLock.UnLock(&myRect);

    myMemberLock.WaitLock(&myCanvas);
    myCanvas.SetSize(&tSize);
    myMemberLock.UnLock(&myCanvas);


    myMemberLock.WaitLock(&myBackRectangle);
    myBackRectangle.SetSize(&tSize);
    myMemberLock.UnLock(&myBackRectangle);

    myMemberLock.WaitLock(&myMaskRectangle);
    myMaskRectangle.SetSize(&tSize);
    myMemberLock.UnLock(&myMaskRectangle);

    HRGN tRNG = CreateRectRgn(0, 0, tSize.myWidth, tSize.myHeight);

    SetWindowRgn(myWnd, tRNG, TRUE);

    DeleteObject(tRNG);

    param.SetMESSAGE(MSG_FatherSize);
    ProcFlakesMessage(param);
    
    auto ret =  DefWindowProc(myWnd, getMSG, getWPARAM, getLPARAM);
    MFX_APPFRAME_RETURN(ret);
}

MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(__OnMove)
{
    myMemberLock.WaitLock(&myRect);
    GetWorldRect(&myRect);
    myMemberLock.UnLock(&myRect);

    param.SetMESSAGE(MSG_FatherPoint);
    ProcFlakesMessage(param);

    auto ret = DefWindowProc(myWnd, getMSG, getWPARAM, getLPARAM);
    MFX_APPFRAME_RETURN(ret);
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(__OnPaint)
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

        MfxParam msgParam1(UI_MSG_PaintBack);
        Send_Message(msgParam1);

        MfxParam msgParam2(UI_MSG_PaintMask);
        ProcMessage(msgParam2);

        myMemberLock.WaitLock(&myCanvas);
        myCanvas.PaintFinish();
        myMemberLock.UnLock(&myCanvas);
    }

    EndPaint(myWnd, &t_Paint);

    MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}

MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(__OnEraseBackGrand)
{
    MFX_APPFRAME_RETURN(1);
}

MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(__OnPaintBackDC)
{
    myMemberLock.WaitLock(&myBackRectangle);
    myBackRectangle.Paint();
    myMemberLock.UnLock(&myBackRectangle);

    MfxParam msgParam(FLAKE_MSG_PaintBack);
    RProcFlakesMessage(msgParam);

    MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}

MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(__OnPaintMaskDC)
{
    MfxParam msgParam(FLAKE_MSG_PaintMask);
    RProcFlakesMessage(msgParam);

    myMemberLock.WaitLock(&myMaskRectangle);
    myMaskRectangle.Paint();
    myMemberLock.UnLock(&myMaskRectangle);

    MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(__OnFlakeInsert)
{
    MfxFlake* tpFlake = getParam_0(pMfxFlake);
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

            MfxParam msgParam(FLAKE_MSG_SetPaper);
            msgParam.push_back(Paper_Infor(this, myWnd, &myCanvas));
            tpFlake->Send_Message(msgParam);

            myMemberLock.UnLock(&myWnd, &myCanvas);

            PostMessage(myWnd, MSG_FlakeFloorChange, NULL, NULL);

            myMemberLock.WaitLock(&myRect);
            MfxSize tSize;
            myRect.GetSize(&tSize);
            UnionInvalidateRect(tSize);
            myMemberLock.UnLock(&myRect);

            MFX_APPFRAME_RETURN(MfxReturn_Seccess);
        }
    }

    MFX_APPFRAME_RETURN(MfxReturn_Failed);
}

MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(__OnFlakeRemove)
{
    MfxFlake* tpFlake = getParam_0(pMfxFlake);
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

                    PostMessage(myWnd, MSG_FlakeFloorChange, NULL, NULL);

                    InvalidateRect(myWnd, nullptr, TRUE);

                    break;
                }
            }
            myMemberLock.UnLock(&myFlakeDeque);
        }
    }

    MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}

MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(__OnFlakeFloorChange)
{
    myMemberLock.WaitLock(&myFlakeDeque);

    std::sort(myFlakeDeque.begin(), myFlakeDeque.end(), pFloorCompare<MfxFlake>);

    myMemberLock.UnLock(&myFlakeDeque);

    MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(__OnWin32Timer)
{
    auto tRet = MfxReturn_Failed;
    myMemberLock.WaitLock(&myTimerMap);

    auto t_Iter = myTimerMap.find(getWPARAM);
    if (t_Iter != myTimerMap.end())
    {
        MfxParam msgParam(getMSG);
        msgParam.push_back(t_Iter->second);
        tRet = (this->*t_Iter->second.recvFunc)(msgParam);
    }

    myMemberLock.UnLock(&myTimerMap);

    MFX_APPFRAME_RETURN(tRet);
}

MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(__OnInsertWin32Timer)
{
    auto tRet = MfxReturn_Failed;
    Win32_Timer_Info tTimer = getParam_0(Win32_Timer_Info);

    myMemberLock.WaitLock(&myTimerMap);
    bool tIns = myTimerMap.insert(Win32_Timer_Info_Map_Elem(tTimer.myID, tTimer)).second;
    myMemberLock.UnLock(&myTimerMap);

    if (tIns)
    {
        SetTimer(myWnd, tTimer.myID, tTimer.delayTime, (TIMERPROC)nullptr);
        tRet = MfxReturn_Seccess;
    }

    MFX_APPFRAME_RETURN(tRet);
}

MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(__OnRemoveWin32Timer)
{
    auto tRet = MfxReturn_Failed;
    ULONG tTimer = getParam_0(ULONG);

    myMemberLock.WaitLock(&myTimerMap);

    auto iter = myTimerMap.find(tTimer);
    if (iter != myTimerMap.end())
    {
        KillTimer(myWnd, tTimer);

        myTimerMap.erase(tTimer);

        tRet = MfxReturn_Seccess;
    }

    myMemberLock.UnLock(&myTimerMap);

    MFX_APPFRAME_RETURN(tRet);
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(__OnFlakeEvent)
{
    MfxReturn tRet = MfxReturn_Failed;

    myMemberLock.WaitLock(&myFlakeEventMap);

    FlakeEvent_Info tInfo = getParam_0(FlakeEvent_Info);

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

    MFX_APPFRAME_RETURN(tRet);
}

MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(__OnRemoveFlakeEvent)
{
    MfxReturn tRet = MfxReturn_Failed;

    FlakeEvent_Info tFlakeEvent = getParam_0(FlakeEvent_Info);
    MfxString tRecvFuncName = getParam_1(MfxString);

    myMemberLock.WaitLock(&myFlakeEventMap);

    auto t_Iter = myFlakeEventMap.find(tFlakeEvent);
    if (t_Iter != myFlakeEventMap.end())
    {
        for (auto i = t_Iter->second.begin(); i != t_Iter->second.end(); i++)
        {
            if ((*i).myRecvFuncName == tRecvFuncName)
            {
                t_Iter->second.erase(i);
                tRet = MfxReturn_Seccess;
                break;
            }
        }
    }

    myMemberLock.UnLock(&myFlakeEventMap);

    MFX_APPFRAME_RETURN(tRet);
}

MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(__OnPushBackFlakeEvent)
{
    myMemberLock.WaitLock(&myFlakeEventMap);

    FlakeEvent_Info tFlakeEvent = getParam_0(FlakeEvent_Info);
    UI_UIRecvFunc_Info tRecvInfo = getParam_1(UI_UIRecvFunc_Info);

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

    MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}

MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(__OnPushFrontFlakeEvent)
{
    myMemberLock.WaitLock(&myFlakeEventMap);

    FlakeEvent_Info tFlakeEvent = getParam_0(FlakeEvent_Info);
    UI_UIRecvFunc_Info tRecvInfo = getParam_1( UI_UIRecvFunc_Info);

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

    MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}

/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(__OnOpenPercentRect)
{
    myMemberLock.WaitLock(&myPercentRectFlag);
    myPercentRectFlag = true;
    myMemberLock.UnLock(&myPercentRectFlag);

    MfxParam msgParam(FLAKE_MSG_OpenPercentRect);
    ProcFlakesMessage(msgParam);

    MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}

MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(__OnClosePercentRect)
{
    myMemberLock.WaitLock(&myPercentRectFlag);
    myPercentRectFlag = false;
    myMemberLock.UnLock(&myPercentRectFlag);

    MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(__OnSetBackColor)
{
    myMemberLock.WaitLock(&myRect);
    MfxSize tSize(myRect);
    myMemberLock.UnLock(&myRect);

    myMemberLock.TryWaitLock(&myBackRectangle, &myBackColor, &myCanvas);

    myBackColor = getParam_0(MfxColor);
    myBackRectangle.SetFillColor(&myBackColor);

    myMemberLock.UnLock(&myBackRectangle, &myBackColor, &myCanvas);

    MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}

MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(__OnSetMaskColor)
{
    myMemberLock.WaitLock(&myRect);
    MfxSize tSize(myRect);
    myMemberLock.UnLock(&myRect);

    myMemberLock.TryWaitLock(&myMaskRectangle, &myMaskColor, &myCanvas);

    myMaskColor = getParam_0(MfxColor);
    myMaskRectangle.SetFillColor(&myMaskColor);

    myMemberLock.UnLock(&myMaskRectangle, &myBackColor, &myCanvas);

    MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}

/********************************************************************************
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(__OnNCPaint)
{
    MFX_APPFRAME_RETURN(MfxReturn_WinAccept);
}

MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(__OnNCActivate)
{
    auto ret = getWPARAM ? 0 : 1;
    MFX_APPFRAME_RETURN(ret);
}

MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(__OnNCHitTest)
{
    MfxReturn ret = DefWindowProc(myWnd, getMSG, getWPARAM, getLPARAM);

    if (ret == HTHELP
        || ret == HTCLOSE
        || ret == HTMAXBUTTON
        || ret == HTMINBUTTON
        )
    {
        MFX_APPFRAME_RETURN(HTCAPTION);
    }

    MFX_APPFRAME_RETURN(ret);
}


/********************************************************************************
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(__OnNCMouseMove)
{
    auto ret = myMutexFocus ? 0 : DefWindowProc(myWnd, WM_NCMOUSEMOVE, getWPARAM, getLPARAM);
    MFX_APPFRAME_RETURN(ret);
}

MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(__OnNCMouseHover)
{
    auto ret = myMutexFocus ? 0 : DefWindowProc(myWnd, WM_NCMOUSEHOVER, getWPARAM, getLPARAM);
    MFX_APPFRAME_RETURN(ret);
}


/********************************************************************************
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(__OnNCLButtonUp)
{
    auto ret = myMutexFocus ? 0 : DefWindowProc(myWnd, WM_NCLBUTTONUP, getWPARAM, getLPARAM);
    MFX_APPFRAME_RETURN(ret);
}

MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(__OnNCLButtonDown)
{
    auto ret = myMutexFocus ? 0 : DefWindowProc(myWnd, WM_NCLBUTTONDOWN, getWPARAM, getLPARAM);
    MFX_APPFRAME_RETURN(ret);
}

MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(__OnNCLButtonDouble)
{
    auto ret = myMutexFocus ? 0 : DefWindowProc(myWnd, WM_NCLBUTTONDBLCLK, getWPARAM, getLPARAM);
    MFX_APPFRAME_RETURN(ret);
}


/********************************************************************************
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(__OnNCRButtonUp)
{
    auto ret = myMutexFocus ? 0 : DefWindowProc(myWnd, WM_NCRBUTTONUP, getWPARAM, getLPARAM);
    MFX_APPFRAME_RETURN(ret);
}

MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(__OnNCRButtonDown)
{
    auto ret = myMutexFocus ? 0 : DefWindowProc(myWnd, WM_NCRBUTTONDOWN, getWPARAM, getLPARAM);
    MFX_APPFRAME_RETURN(ret);
}

MfxReturn MicroFlakeX::MfxUI::MFX_CALLBACK(__OnNCRButtonDouble)
{
    auto ret = myMutexFocus ? 0 : DefWindowProc(myWnd, WM_NCRBUTTONDBLCLK, getWPARAM, getLPARAM);
    MFX_APPFRAME_RETURN(ret);
}