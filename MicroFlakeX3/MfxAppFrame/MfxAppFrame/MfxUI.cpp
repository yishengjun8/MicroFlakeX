#include "pch.h"
#include "MfxAppFrame.h"


MfxObject_Init_0(MfxUI)
MfxObject_Init_1(MfxUI, END)
MfxAutoFunc_AutoEnumBig(MfxUI, \
    1, GetRect, \
    1, GetSize, \
    1, GetPoint, \
    \
    1, SetRect, \
    1, SetSize, \
    1, SetPoint, \
    \
    END, END);
MfxObject_Init_2(MfxUI, MfxBase);

void MicroFlakeX::MfxUI::MfxRegMessages()
{
    /********************************************************************************
    *
    *
    *
    *
    *********************************************************************************/
    UI_ADD_FLAKE_RECVMSG(WM_SIZE);
    UI_ADD_FLAKE_RECVMSG(WM_DESTROY);

    UI_ADD_FLAKE_RECVMSG(WM_MOUSEMOVE);
    UI_ADD_FLAKE_RECVMSG(WM_LBUTTONDOWN);
    UI_ADD_FLAKE_RECVMSG(WM_LBUTTONUP);
    UI_ADD_FLAKE_RECVMSG(WM_RBUTTONDOWN);
    UI_ADD_FLAKE_RECVMSG(WM_RBUTTONUP);


    /********************************************************************************
    *
    *
    *
    *
    *********************************************************************************/
    UI_ADD_FLOOR;

    UI_ADD_RECVMSG(WM_CREATE, MfxUI, __OnCreate, myCoverFloor);
    UI_ADD_RECVMSG(WM_DESTROY, MfxUI, __OnDestroy, myCoverFloor);

    UI_ADD_RECVMSG(WM_SIZE, MfxUI, __OnSize, myCoverFloor);
    UI_ADD_RECVMSG(WM_MOVE, MfxUI, __OnMove, myCoverFloor);

    UI_ADD_RECVMSG(WM_TIMER, MfxUI, __OnTimer, myCoverFloor);

    UI_ADD_RECVMSG(WM_PAINT, MfxUI, __OnPaint, myCoverFloor);
    UI_ADD_RECVMSG(WM_ERASEBKGND, MfxUI, __OnEraseBackGrand, myCoverFloor);

    UI_ADD_RECVMSG(UI_MSG_PaintBack, MfxUI, __OnPaintBackDC, myCoverFloor);
    UI_ADD_RECVMSG(UI_MSG_PaintMask, MfxUI, __OnPaintMaskDC, myCoverFloor);

    UI_ADD_RECVMSG(UI_MSG_FlakeInsert, MfxUI, __OnFlakeInsert, myCoverFloor);
    UI_ADD_RECVMSG(UI_MSG_FlakeRemove, MfxUI, __OnFlakeRemove, myCoverFloor);
    UI_ADD_RECVMSG(UI_MSG_FlakeFloorChange, MfxUI, __OnFlakeFloorChange, myCoverFloor);

    UI_ADD_RECVMSG(UI_MSG_AddTimer, MfxUI, __OnAddTimer, myCoverFloor);
    UI_ADD_RECVMSG(UI_MSG_RemoveTimer, MfxUI, __OnRemoveTimer, myCoverFloor);

    UI_ADD_RECVMSG(UI_MSG_FlakeMessage, MfxUI, __OnFlakeMessage, myCoverFloor);

    UI_ADD_RECVMSG(UI_MSG_AddFlakeMessage, MfxUI, __OnAddFlakeMessage, myCoverFloor);
    UI_ADD_RECVMSG(UI_MSG_RemoveFlakeMessage, MfxUI, __OnRemoveFlakeMessage, myCoverFloor);

    UI_ADD_RECVMSG(UI_MSG_OpenPercentRect, MfxUI, __OnOpenPercentRect, myCoverFloor);
    UI_ADD_RECVMSG(UI_MSG_ClosePercentRect, MfxUI, __OnClosePercentRect, myCoverFloor);

    UI_ADD_RECVMSG(UI_MSG_SetBackColor, MfxUI, __OnSetBackColor, myCoverFloor);
    UI_ADD_RECVMSG(UI_MSG_SetMaskColor, MfxUI, __OnSetMaskColor, myCoverFloor);
    UI_ADD_RECVMSG(UI_MSG_SetBackImage, MfxUI, __OnSetBackImage, myCoverFloor);
    UI_ADD_RECVMSG(UI_MSG_SetMaskImage, MfxUI, __OnSetMaskImage, myCoverFloor);
}

void MicroFlakeX::MfxUI::MfxUIInitData()
{
    myUnderFloor = 0;
    myCoverFloor = 0;

    myWnd = nullptr;

    myBackImage = nullptr;
    myMaskImage = nullptr;

    myMutexFocus = nullptr;
    myKeyboardFocus = nullptr;
    myMutexFocusLockFlag = false;
    myKeyboardFocusLockFlag = false;

    myPercentRectFlag = false;

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
    SendMessageToFlakes(message, wParam, lParam, false);

    MfxReturn t_Ret = Mfx_Return_Fail;
    auto t_Iter = myMessageMap.find(message);
    if (t_Iter != myMessageMap.end())
    {
        if (!t_Iter->second->empty())
        {
            for (auto i : *(t_Iter->second))
            {
                t_Ret = (this->*i->recvFunc)(wParam, lParam);
            }
            return t_Ret;
        }
    }


    return DefWindowProc(myWnd, message, wParam, lParam);
}

MfxReturn MicroFlakeX::MfxUI::SendMessageToFlakes(MfxMsg message, WPARAM wParam, LPARAM lParam, bool sort)
{
    //True 从后往前
    //False 从前往后
    MfxFlake* t_FloatFocus = myMutexFocus;
    myMutexFocus = myMutexFocusLockFlag ? myMutexFocus : nullptr;

    auto t_Iter = myFlakeMessageSet.find(message);
    //if (t_Iter != myFlakeMessageSet.end())
    {
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
   // else
    //{
    //    myMutexFocus = (myMutexFocus ? myMutexFocus : t_FloatFocus);
    //    return Mfx_Return_Fail;
   // }
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::RemoveMessage(MfxMsg message, MfxString funcName)
{
    MfxCodeLock(this);
    auto t_Iter = myMessageMap.find(message);
    if (t_Iter != myMessageMap.end())
    {
        for (auto i = t_Iter->second->begin(); i != t_Iter->second->end(); i++)
        {
            if ((*i)->myFuncName == funcName)
            {
                delete (*i);
                t_Iter->second->erase(i);
                return Mfx_Return_Fine;
            }
        }
    }
    return Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxUI::InsertMessage(MfxMsg message, MfxUI_MsgMap_Infor* msgValue)
{
    MfxCodeLock(this);
    auto t_Iter = myMessageMap.find(message);
    if (t_Iter == myMessageMap.end())
    {
        auto t_AddVector = new MfxUI_MsgMap_Vector;
        t_Iter = myMessageMap.insert(MfxUI_MsgMap_elem(message, t_AddVector)).first;
    }

    t_Iter->second->push_back(msgValue);
    std::sort(t_Iter->second->begin(), t_Iter->second->end(), FloorCompare<MfxUI_MsgMap_Infor>);

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
MfxReturn MicroFlakeX::MfxUI::AddFlake(MfxFlake* set)
{
    return ProcMessage(UI_MSG_FlakeInsert, (WPARAM)set, NULL);
}

MfxReturn MicroFlakeX::MfxUI::RemoveFlake(MfxFlake* set)
{
    return ProcMessage(UI_MSG_FlakeRemove, (WPARAM)set, NULL);
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxUI::RemoveFlakeMessage(MfxFlake* target, MfxMsg message)
{
    MfxUI_FlakeMsg_Infor t_FlakeMessage(target, message);
    return ProcMessage(UI_MSG_RemoveFlakeMessage, NULL, (LPARAM)&t_FlakeMessage);
}

MfxReturn MicroFlakeX::MfxUI::AddFlakeMessage(MfxFlake* target, MfxMsg message, MfxUI_MsgFunc recv)
{
    MfxUI_FlakeMsg_Infor t_FlakeMessage(target, message);
    return ProcMessage(UI_MSG_AddFlakeMessage, (WPARAM)&recv, (LPARAM)&t_FlakeMessage);
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

MfxReturn MicroFlakeX::MfxUI::AddTimer(WPARAM timerID, clock_t delay, MfxUI_MsgFunc recv)
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
    return SetWindowPos(myWnd, NULL, set->myX, set->myY, set->myWidth, set->myHeight, SWP_NOZORDER) ? Mfx_Return_Fine : Mfx_Return_Fail;;
}

MfxReturn MicroFlakeX::MfxUI::SetSize(MfxSize* set)
{
    return SetWindowPos(myWnd, NULL, 0, 0, set->myWidth, set->myHeight, SWP_NOMOVE | SWP_NOZORDER) ? Mfx_Return_Fine : Mfx_Return_Fail;;
}

MfxReturn MicroFlakeX::MfxUI::SetPoint(MfxPoint* set)
{
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
    myCanvas.SetSize(&tSize);
    myCanvas.SetWnd(myWnd);

    myBackImage = new MfxImage(MfxColor(255, 0, 255, 255), MfxRect(0, 0, myRect.myWidth, myRect.myHeight));
    myBackImage->SetCanvas(&myCanvas);

    return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxUI::__OnDestroy(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);

    while (myFlakeDeque.size())
    {
        //只需要调用控件的析构函数就可以了
        //析构函数会自动发送控件销毁消息来注销他的控件映射
        delete myFlakeDeque[0];
    }

    //PostQuitMessage(0); //结束消息循环
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
            MfxUI_Paper_Infor t_PaperValue(this, myWnd, &myCanvas);
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
                MfxUI_Paper_Infor t_PaperValue;
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
    std::sort(myFlakeDeque.begin(), myFlakeDeque.end(), FloorCompare<MfxFlake>);
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
    auto t_Iter = myFlakeMessageMap.find(*(MfxUI_FlakeMsg_Infor*)wParam);
    if (t_Iter != myFlakeMessageMap.end())
    {
        return (this->*t_Iter->second)(((MfxUI_FlakeMsg_Value*)lParam)->wParam, ((MfxUI_FlakeMsg_Value*)lParam)->lParam);
    }
    return Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxUI::__OnAddFlakeMessage(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    return myFlakeMessageMap.insert(
        MfxUI_FlakeMsg_Map_elem(*(MfxUI_FlakeMsg_Infor*)lParam, *(MfxUI_MsgFunc*)wParam)).second ? Mfx_Return_Fine : Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxUI::__OnRemoveFlakeMessage(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    return  myFlakeMessageMap.erase(*(MfxUI_FlakeMsg_Infor*)lParam) ? Mfx_Return_Fine : Mfx_Return_Fail;
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


/********************************************************************************
*
*
*
*
*********************************************************************************/