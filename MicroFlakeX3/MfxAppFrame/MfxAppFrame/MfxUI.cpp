#include "pch.h"
#include "MfxAppFrame.h"

MfxObject_Init_0(MfxUI)
MfxObject_Init_1(MfxUI, CreateSuccess)
MfxAutoFunc_AutoEnumBig(MfxUI, \
    \
    0, CreateSuccess, \
    \
    2, UIThread, \
    \
    3, ProcMessage, \
    4, SendMessageToFlakes, \
    \
    2, RemoveUIMessage, \
    2, InsertUIMessage, \
    \
    0, OpenPercentRect, \
    0, ClosePercentRect, \
    0, ChickPercentRect, \
    \
    1, RemoveFlake, \
    1, InsertFlake, \
    \
    2, RemoveFlakeMessage, \
    2, InsertFlakeMessage, \
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
    1, SetBackColor, \
    1, SetMaskColor, \
    1, SetBackImage, \
    1, SetMaskImage, \
    \
    END, END);
MfxObject_Init_2(MfxUI, MfxBase);


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
    UI_ADD_FLOOR;

    UI_ADDRECV_UIMSG(WM_CREATE, MfxUI, __OnCreate, myCoverFloor);
    UI_ADDRECV_UIMSG(WM_DESTROY, MfxUI, __OnDestroy, myCoverFloor);

    UI_ADDRECV_UIMSG(WM_SIZE, MfxUI, __OnSize, myCoverFloor);
    UI_ADDRECV_UIMSG(WM_MOVE, MfxUI, __OnMove, myCoverFloor);

    UI_ADDRECV_UIMSG(WM_TIMER, MfxUI, __OnTimer, myCoverFloor);

    UI_ADDRECV_UIMSG(WM_PAINT, MfxUI, __OnPaint, myCoverFloor);
    UI_ADDRECV_UIMSG(WM_ERASEBKGND, MfxUI, __OnEraseBackGrand, myCoverFloor);

    UI_ADDRECV_UIMSG(UI_MSG_PaintBack, MfxUI, __OnPaintBackDC, myCoverFloor);
    UI_ADDRECV_UIMSG(UI_MSG_PaintMask, MfxUI, __OnPaintMaskDC, myCoverFloor);

    UI_ADDRECV_UIMSG(UI_MSG_FlakeInsert, MfxUI, __OnFlakeInsert, myCoverFloor);
    UI_ADDRECV_UIMSG(UI_MSG_FlakeRemove, MfxUI, __OnFlakeRemove, myCoverFloor);
    UI_ADDRECV_UIMSG(UI_MSG_FlakeFloorChange, MfxUI, __OnFlakeFloorChange, myCoverFloor);

    UI_ADDRECV_UIMSG(UI_MSG_AddTimer, MfxUI, __OnAddTimer, myCoverFloor);
    UI_ADDRECV_UIMSG(UI_MSG_RemoveTimer, MfxUI, __OnRemoveTimer, myCoverFloor);

    UI_ADDRECV_UIMSG(UI_MSG_FlakeMessage, MfxUI, __OnFlakeMessage, myCoverFloor);

    UI_ADDRECV_UIMSG(UI_MSG_InsertFlakeMessage, MfxUI, __OnInsertFlakeMessage, myCoverFloor);
    UI_ADDRECV_UIMSG(UI_MSG_RemoveFlakeMessage, MfxUI, __OnRemoveFlakeMessage, myCoverFloor);

    UI_ADDRECV_UIMSG(UI_MSG_OpenPercentRect, MfxUI, __OnOpenPercentRect, myCoverFloor);
    UI_ADDRECV_UIMSG(UI_MSG_ClosePercentRect, MfxUI, __OnClosePercentRect, myCoverFloor);

    UI_ADDRECV_UIMSG(UI_MSG_SetBackColor, MfxUI, __OnSetBackColor, myCoverFloor);
    UI_ADDRECV_UIMSG(UI_MSG_SetMaskColor, MfxUI, __OnSetMaskColor, myCoverFloor);
    UI_ADDRECV_UIMSG(UI_MSG_SetBackImage, MfxUI, __OnSetBackImage, myCoverFloor);
    UI_ADDRECV_UIMSG(UI_MSG_SetMaskImage, MfxUI, __OnSetMaskImage, myCoverFloor);
}

void MicroFlakeX::MfxUI::MfxUIInitData()
{
    myUnderFloor = 0;
    myCoverFloor = 0;

    myWnd = nullptr;
    myUIThreadID = 0;

    myBackImage = nullptr;
    myMaskImage = nullptr;

    myMutexFocus = nullptr;
    myKeyboardFocus = nullptr;
    myMutexFocusLockFlag = false;
    myKeyboardFocusLockFlag = false;

    myPercentRectFlag = false;
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

    MessageBox(NULL, L"Close", L"Close", 0);
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
MfxReturn MicroFlakeX::MfxUI::ProcMessage(MfxMsg message, WPARAM wParam, LPARAM lParam)
{
    /* 这里添加识别 - 耗时的全部移交到UI线程内处理 */
    MfxReturn t_Ret = Mfx_Return_Fail;

    auto t_Iter = myMessageMap.find(message);
    if (t_Iter != myMessageMap.end())
    {
        if (!t_Iter->second.empty())
        {
            for (auto i : (t_Iter->second))
            {
                t_Ret = (this->*i.recvFunc)(wParam, lParam);
            }
            return t_Ret;
        }
    }

    SendMessageToFlakes(message, wParam, lParam);

    return DefWindowProc(myWnd, message, wParam, lParam);
}

MfxReturn MicroFlakeX::MfxUI::SendMessageToFlakes(MfxMsg message, WPARAM wParam, LPARAM lParam, bool sort)
{
    //True 从后往前
    //False 从前往后
    MfxFlake* t_FloatFocus = myMutexFocus;
    myMutexFocus = myMutexFocusLockFlag ? myMutexFocus : nullptr;

    if (sort)
    {
        for (int i = myFlakeDeque.size() - 1; i >= 0; i--)
        {
            myFlakeDeque[i]->ProcMessage(message, wParam, lParam);
        }
    }
    else
    {
        for (auto t_Iter : myFlakeDeque)
        {
            t_Iter->ProcMessage(message, wParam, lParam);
        }
    }

    myMutexFocus = (myMutexFocus ? myMutexFocus : t_FloatFocus);

    return Mfx_Return_Fine;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::RemoveUIMessage(MfxMsg message, MfxString recvFuncName)
{
    MfxCodeLock(this);

    auto t_Iter = myMessageMap.find(message);
    if (t_Iter != myMessageMap.end())
    {
        for (auto i = t_Iter->second.begin(); i != t_Iter->second.end(); i++)
        {
            if (i->myRecvFuncName == recvFuncName)
            {
                t_Iter->second.erase(i);
                return Mfx_Return_Fine;
            }
        }
    }

    return Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxUI::InsertUIMessage(MfxMsg message, UI_UIMsg_RecvFunc_Infor msgValue)
{
    MfxCodeLock(this);

    Begin:
    auto t_Iter = myMessageMap.find(message);
    if (t_Iter == myMessageMap.end())
    {
        t_Iter = myMessageMap.insert(UI_UIMsg_Map_Elem(message, UI_UIMsg_RecvFunc_Infor_Vector())).first;
        goto Begin;
    }
    else
    {
        t_Iter->second.push_back(msgValue);
        std::sort(t_Iter->second.begin(), t_Iter->second.end(), FloorCompare<UI_UIMsg_RecvFunc_Infor>);
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

MfxReturn MicroFlakeX::MfxUI::InsertFlakeMessage(UI_FlakeMsg_Infor message, UI_UIMsg_RecvFunc_Infor msgValue)
{
    return ProcMessage(UI_MSG_InsertFlakeMessage, (WPARAM)&message, (LPARAM)&msgValue);
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::RemoveTimer(WPARAM cid)
{
    return ProcMessage(UI_MSG_RemoveTimer, cid, NULL);
}

MfxReturn MicroFlakeX::MfxUI::InsertTimer(WPARAM timerID, clock_t delay, pUIRecvFunc recv)
{
    return ProcMessage(UI_MSG_AddTimer, timerID, (LPARAM)(new MfxUI_Timer_Infor(delay, clock(), recv)));
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
    *ret = myRect;

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::GetSize(MfxSize* ret)
{
    *ret = myRect;

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::GetPoint(MfxPoint* ret)
{
    *ret = myRect;

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::GetBackImage(MfxImage** ret)
{
    MfxCodeLock(this);
    return myBackImage ? myBackImage->Clone(ret) : Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxUI::GetMaskImage(MfxImage** ret)
{
    MfxCodeLock(this);
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


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::__OnCreate(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    CREATESTRUCTA* t_Create = (CREATESTRUCTA*)lParam;

    myRect.Reset(t_Create->x, t_Create->y, t_Create->cx, t_Create->cy);

    //MfxSize t_Size(GetSystemMetrics(SM_CXFULLSCREEN), GetSystemMetrics(SM_CYFULLSCREEN));
    MfxSize tSize(myRect.myWidth, myRect.myHeight);
    myCanvas.SetWnd(myWnd);
    myCanvas.SetSize(&tSize);

    myBackImage = new MfxImage(MfxColor(255, 0, 255, 255), MfxRect(0, 0, myRect.myWidth, myRect.myHeight));
    myBackImage->SetCanvas(&myCanvas);

    while (!myUIThreadID);

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
    MfxSize tSize(LOWORD(lParam), HIWORD(lParam));

    myRect = tSize;
    myCanvas.SetSize(&tSize);
    if (myBackImage)
    {
        myBackImage->SetSize(&tSize);
    }
    if (myMaskImage)
    {
        myMaskImage->SetSize(&tSize);
    }

    return DefWindowProc(myWnd, WM_SIZE, wParam, lParam);
}

MfxReturn MicroFlakeX::MfxUI::__OnMove(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);

    myRect.myX = LOWORD(lParam);
    myRect.myY = HIWORD(lParam);

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

    myCanvas.PaintBegin();

    ProcMessage(UI_MSG_PaintBack, NULL, NULL);

    ProcMessage(UI_MSG_PaintMask, NULL, NULL);

    myCanvas.PaintFinish();

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
        (this->*t_Iter->second->recvFunc)((*t_Iter).second->delayTime, clock() - (*t_Iter).second->passTime);
        (*t_Iter).second->passTime = clock();
        return Mfx_Return_Fine;
    }

    return Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxUI::__OnAddTimer(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);

    if (myTimerMap.insert(MfxUI_Timer_Map_elem(wParam, (MfxUI_Timer_Infor*)lParam)).second)
    {
        SetTimer(myWnd, wParam, ((MfxUI_Timer_Infor*)lParam)->delayTime, (TIMERPROC)NULL);
    }

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::__OnRemoveTimer(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);

    delete (myTimerMap[wParam]);
    myTimerMap.erase(wParam);
    KillTimer(myWnd, wParam);

    return Mfx_Return_Fine;
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
                t_Ret = (this->*i.recvFunc)(wParam, lParam);
            }
        }
    }

    delete tFlakeMsg_Infor;
    delete tFlakeMsg_Value;

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::__OnInsertFlakeMessage(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);

    UI_FlakeMsg_Infor* tFlakeMsg_Infor = (UI_FlakeMsg_Infor*)wParam;
    UI_UIMsg_RecvFunc_Infor* tRecvFunc_Infor = (UI_UIMsg_RecvFunc_Infor*)lParam;

    Begin:
    auto t_Iter = myFlakeMessageMap.find(*tFlakeMsg_Infor);
    if (t_Iter == myFlakeMessageMap.end())
    {
        t_Iter = myFlakeMessageMap.insert(UI_FlakeMsg_Map_Elem(*tFlakeMsg_Infor, UI_UIMsg_RecvFunc_Infor_Vector())).first;
        goto Begin;
    }
    else
    {
        t_Iter->second.push_back(*tRecvFunc_Infor);
        std::sort(t_Iter->second.begin(), t_Iter->second.end(), FloorCompare<UI_UIMsg_RecvFunc_Infor>);
    }
    
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
            if (i->myRecvFuncName == *tRecvFuncName)
            {
                t_Iter->second.erase(i);
                return Mfx_Return_Fine;
            }
        }
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

    MfxColor* t_Set = (MfxColor*)lParam;
    if (myBackImage)
    {
        myBackImage->FromColor(*t_Set, MfxSize(myRect));
    }
    else
    {
        myBackImage = new MfxImage(*t_Set, MfxRect(0, 0, myRect.myWidth, myRect.myHeight));
        myBackImage->SetCanvas(&myCanvas);
    }

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::__OnSetMaskColor(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);

    MfxColor* t_Set = (MfxColor*)lParam;
    if (myMaskImage)
    {
        myMaskImage->FromColor(*t_Set, MfxSize(myRect));
    }
    else
    {
        myMaskImage = new MfxImage(*t_Set, MfxRect(0, 0, myRect.myWidth, myRect.myHeight));
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