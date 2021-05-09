#include "pch.h"
#include "MfxAppFrame.h"

MfxObject_Init_0(MfxUI)
MfxObject_Init_1(MfxUI, END)
MfxObject_Init_2(MfxUI, MfxBase);

void MicroFlakeX::MfxUI::MfxRegMessages()
{
    UI_CON_RECV_MSG(WM_DESTROY);
    UI_CON_RECV_MSG(WM_SIZE);

    UI_CON_RECV_MSG(WM_MOUSEMOVE);
    UI_CON_RECV_MSG(WM_LBUTTONDOWN);
    UI_CON_RECV_MSG(WM_LBUTTONUP);
    UI_CON_RECV_MSG(WM_RBUTTONDOWN);
    UI_CON_RECV_MSG(WM_RBUTTONUP);

    UI_CON_RECV_MSG(UI_MSG_SetPaper);

    UI_CON_RECV_MSG(UI_MSG_PaintBack);
    UI_CON_RECV_MSG(UI_MSG_PaintMask);

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
    UI_REG_MSG(UI_MSG_PaintBack, MfxUI, __OnPaintBackDC, myCoverFloor);
    UI_REG_MSG(UI_MSG_PaintMask, MfxUI, __OnPaintMaskDC, myCoverFloor);

    UI_REG_MSG(UI_MSG_FlakeInsert, MfxUI, __OnFlakeInsert, myCoverFloor);
    UI_REG_MSG(UI_MSG_FlakeRemove, MfxUI, __OnFlakeRemove, myCoverFloor);
    UI_REG_MSG(FLAKE_MSG_FlakeFloorChange, MfxUI, __OnFlakeFloorChange, myCoverFloor);

    UI_REG_MSG(WM_TIMER, MfxUI, __OnTimer, myCoverFloor);
    UI_REG_MSG(UI_MSG_AddTimer, MfxUI, __OnAddTimer, myCoverFloor);
    UI_REG_MSG(UI_MSG_RemoveTimer, MfxUI, __OnRemoveTimer, myCoverFloor);

    UI_REG_MSG(FLAKE_MSG_FlakeMessage, MfxUI, __OnFlakeMessage, myCoverFloor);
    UI_REG_MSG(UI_MSG_AddFlakeMessage, MfxUI, __OnAddFlakeMessage, myCoverFloor);
    UI_REG_MSG(UI_MSG_RemoveFlakeMessage, MfxUI, __OnRemoveFlakeMessage, myCoverFloor);

    UI_REG_MSG(UI_MSG_SetBackColor, MfxUI, __OnSetBackColor, myCoverFloor);
    UI_REG_MSG(UI_MSG_SetMaskColor, MfxUI, __OnSetMaskColor, myCoverFloor);
    UI_REG_MSG(UI_MSG_SetBackImage, MfxUI, __OnSetBackImage, myCoverFloor);
    UI_REG_MSG(UI_MSG_SetMaskImage, MfxUI, __OnSetMaskImage, myCoverFloor);
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
    myKeyboardFocusLockFag = false;
}

MicroFlakeX::MfxUI::MfxUI()
{
    MfxUIInitData();
    MfxRegMessages();

    MfxRect tRect(60, 60, 400, 400);
    MfxApp::theApp->MfxCreateUIEx(
        this, tRect,
        NULL, UI_STYLE_Normal,
        MfxText("MfxNormalUI"), MfxText("MfxNormalUI"));
}

MicroFlakeX::MfxUI::MfxUI(MfxRect set, MfxString title)
{
    MfxUIInitData();
    MfxRegMessages();

    MfxApp::theApp->MfxCreateUIEx(
        this, set,
        NULL, UI_STYLE_Normal,
        MfxText("MfxNormalUI"), title);
}

MicroFlakeX::MfxUI::MfxUI(MfxRect set, DWORD myStyle_EN, MfxString title)
{
    MfxUIInitData();
    MfxRegMessages();

    MfxApp::theApp->MfxCreateUIEx(
        this, set,
        NULL, myStyle_EN,
        MfxText("MfxNormalUI"), title);
}

MicroFlakeX::MfxUI::MfxUI(MfxRect set, DWORD myStyleEx_EN, DWORD myStyle_EN, MfxString myClass, MfxString title)
{
    MfxUIInitData();
    MfxRegMessages();

    MfxApp::theApp->MfxCreateUIEx(
        this, set,
        myStyleEx_EN, myStyle_EN,
        MfxText("MfxNormalUI"), title);
}

MicroFlakeX::MfxUI::~MfxUI()
{
    MfxCodeLock(this);
    SendMessage(myWnd, WM_DESTROY, 0, 0);

    SafeDelete(myBackImage);
    SafeDelete(myMaskImage);
}

MfxReturn MicroFlakeX::MfxUI::CreateSuccess()
{
    return myWnd ? RFine : RFail;
}

MfxReturn MicroFlakeX::MfxUI::ProcMessage(MfxMsg message, WPARAM wParam, LPARAM lParam)
{
    SendMessageToFlakes(message, wParam, lParam, false);

    MfxReturn t_Ret = RFail;
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

MfxReturn MicroFlakeX::MfxUI::SendMessageToFlakes(MfxMsg message, WPARAM wParam, LPARAM lParam, bool sort)
{
    MfxFlake* t_FloatFocus = myMutexFocus;
    myMutexFocus = myMutexFocusLockFlag ? myMutexFocus : nullptr;

    if (myFlakeMessageSet.find(message) != myFlakeMessageSet.end())
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
        return RFine;
    }
    else
    {
        myMutexFocus = (myMutexFocus ? myMutexFocus : t_FloatFocus);
        return RFail;
    }
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MfxReturn MicroFlakeX::MfxUI::AddFlake(MfxFlake* set)
{
    return ProcMessage(UI_MSG_FlakeInsert, (WPARAM)set, NULL);
}

MfxReturn MicroFlakeX::MfxUI::RemoveFlake(MfxFlake* set)
{
    return ProcMessage(UI_MSG_FlakeRemove, (WPARAM)set, NULL);
}

MfxReturn MicroFlakeX::MfxUI::AddFlakeMessage(MfxFlake* target, MfxMsg message, MfxUI_Func recv)
{
    MfxUI_FlakeMessage_Key t_FlakeMessage(target, message);
    return ProcMessage(UI_MSG_AddFlakeMessage, (WPARAM)&recv, (LPARAM)&t_FlakeMessage);
}

MfxReturn MicroFlakeX::MfxUI::RemoveFlakeMessage(MfxFlake* target, MfxMsg message)
{
    MfxUI_FlakeMessage_Key t_FlakeMessage(target, message);
    return ProcMessage(UI_MSG_RemoveFlakeMessage, NULL, (LPARAM)&t_FlakeMessage);
}

MfxReturn MicroFlakeX::MfxUI::AddTimer(WPARAM timerID, clock_t delay, MfxUI_Func recv)
{
    MfxUI_Timer_Value t_TimerValue(delay, clock(), recv);
    return ProcMessage(UI_MSG_AddTimer, timerID, (LPARAM)&t_TimerValue);
}

MfxReturn MicroFlakeX::MfxUI::RemoveTimer(WPARAM cid)
{
    return ProcMessage(UI_MSG_RemoveTimer, cid, NULL);
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MfxReturn MicroFlakeX::MfxUI::GetWnd(HWND* ret)
{
    *ret = myWnd;
    return RFine;
}

MfxReturn MicroFlakeX::MfxUI::GetRect(MfxRect* ret)
{
    *ret = myRect;
    return RFine;
}

MfxReturn MicroFlakeX::MfxUI::GetSize(MfxSize* ret)
{
    *ret = myRect;
    return RFine;
}

MfxReturn MicroFlakeX::MfxUI::GetPoint(MfxPoint* ret)
{
    *ret = myRect;
    return RFine;
}

MfxReturn MicroFlakeX::MfxUI::GetBackImage(MfxImage** ret)
{
    MfxCodeLock(this);
    return myBackImage ? myBackImage->Clone(ret) : RFail;
}

MfxReturn MicroFlakeX::MfxUI::GetMaskImage(MfxImage** ret)
{
    MfxCodeLock(this);
    return myMaskImage ? myMaskImage->Clone(ret) : RFail;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MfxReturn MicroFlakeX::MfxUI::SetRect(MfxRect set)
{
    return SetWindowPos(myWnd, NULL, set.myX, set.myY, set.myWidth, set.myHeight, SWP_NOZORDER) ? RFine : RFail;;
}

MfxReturn MicroFlakeX::MfxUI::SetSize(MfxSize set)
{
    return SetWindowPos(myWnd, NULL, 0, 0, set.myWidth, set.myHeight, SWP_NOMOVE | SWP_NOZORDER) ? RFine : RFail;;
}

MfxReturn MicroFlakeX::MfxUI::SetPoint(MfxPoint set)
{
    return SetWindowPos(myWnd, NULL, set.myX, set.myY, 0, 0, SWP_NOSIZE | SWP_NOZORDER) ? RFine : RFail;;
}

MfxReturn MicroFlakeX::MfxUI::SetBackColor(MfxColor set)
{
    return ProcMessage(UI_MSG_SetBackColor, NULL, (LPARAM)&set);
}

MfxReturn MicroFlakeX::MfxUI::SetMaskColor(MfxColor set)
{
    return ProcMessage(UI_MSG_SetMaskColor, NULL, (LPARAM)&set);
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
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MfxReturn MicroFlakeX::MfxUI::LockMutexFocus(MfxFlake* set)
{
    MfxCodeLock(this);
    myMutexFocus = set;
    myMutexFocusLockFlag = true;
    return RFine;
}

MfxReturn MicroFlakeX::MfxUI::UnLockMutexFocus()
{
    MfxCodeLock(this);
    myMutexFocusLockFlag = false;
    return RFine;
}

MfxReturn MicroFlakeX::MfxUI::SetMutexFocus(MfxFlake* set)
{
    MfxCodeLock(this);
    if (!myMutexFocus && !myMutexFocusLockFlag)
    {
        myMutexFocus = set;
        return RFine;
    }
    else
    {
        return RFail;
    }
}

MfxReturn MicroFlakeX::MfxUI::SetKeyboardFocus(MfxFlake* set)
{
    MfxCodeLock(this);
    if (!myMutexFocusLockFlag)
    {
        myKeyboardFocus = set;
        return RFine;
    }
    else
    {
        return RFail;
    }
}

MfxReturn MicroFlakeX::MfxUI::GetMutexFocus(MfxFlake** ret)
{
    MfxCodeLock(this);
    *ret = myMutexFocus;
    return RFine;
}

MfxReturn MicroFlakeX::MfxUI::GetKeyboardFocus(MfxFlake** ret)
{
    MfxCodeLock(this);
    *ret = myKeyboardFocus;
    return RFine;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MfxReturn MicroFlakeX::MfxUI::RemoveMessage(MfxMsg message, MfxString name)
{
    MfxCodeLock(this);
    auto t_Iter = myMessageMap.find(message);
    if (t_Iter != myMessageMap.end())
    {
        for (auto i = t_Iter->second->begin(); i != t_Iter->second->end(); i++)
        {
            if ((*i)->myName == name)
            {
                t_Iter->second->erase(i);
                return RFine;
            }
        }
    }
    return RFail;
}

MfxReturn MicroFlakeX::MfxUI::InsertMessage(MfxMsg message, MfxUI_MessageMap_Value* msgValue)
{
    MfxCodeLock(this);
    auto t_Iter = myMessageMap.find(message);
    if (t_Iter == myMessageMap.end())
    {
        auto t_AddVector = new MfxUI_MessageMap_Vector;
        t_Iter = myMessageMap.insert(MfxUI_MessageMap_elem(message, t_AddVector)).first;
    }

    t_Iter->second->push_back(msgValue);
    std::sort(t_Iter->second->begin(), t_Iter->second->end(), MfxApp::FloorCompare<MfxUI_MessageMap_Value>);

    return RFine;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MfxReturn MicroFlakeX::MfxUI::__OnTest00(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    std::cout << "__OnTest00: wParam-" << wParam << " lParam-" << lParam << std::endl;
    return RFine;
}

MfxReturn MicroFlakeX::MfxUI::__OnTest01(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    std::cout << "__OnTest01: wParam-" << wParam << " lParam-" << lParam << std::endl;
    return RFine;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MfxReturn MicroFlakeX::MfxUI::__OnCreate(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    CREATESTRUCTA* t_Create = (CREATESTRUCTA*)lParam;

    myRect.Init(t_Create->x, t_Create->y, t_Create->cx, t_Create->cy);

    //MfxSize t_Size(GetSystemMetrics(SM_CXFULLSCREEN), GetSystemMetrics(SM_CYFULLSCREEN));

    myCanvas.SetSize(MfxSize(myRect.myWidth, myRect.myHeight));
    myCanvas.SetWnd(myWnd);

    myBackImage = new MfxImage(MfxColor(255, 0, 255, 255), MfxRect(0, 0, myRect.myWidth, myRect.myHeight));
    myBackImage->SetCanvas(&myCanvas);
    return RFine;
}

MfxReturn MicroFlakeX::MfxUI::__OnDestroy(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);

    while (myFlakeDeque.size())
    {
        //峪俶勣距喘陣周議裂更痕方祥辛參阻
        //裂更痕方氏徭強窟僕陣周��支��連栖廣��麿議陣周啌符
        delete myFlakeDeque[0];
    }

    PostQuitMessage(0); //潤崩��連儉桟
    return RFine;
}

MfxReturn MicroFlakeX::MfxUI::__OnSize(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    myRect.myWidth = LOWORD(lParam);
    myRect.myHeight = HIWORD(lParam);
    return DefWindowProc(myWnd, WM_SIZE, wParam, lParam);
}

MfxReturn MicroFlakeX::MfxUI::__OnMove(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    myRect.myX = LOWORD(lParam);
    myRect.myY = HIWORD(lParam);
    return DefWindowProc(myWnd, WM_MOVE, wParam, lParam);
}


MfxReturn MicroFlakeX::MfxUI::__OnPaint(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    PAINTSTRUCT t_Paint{0};
    t_Paint.fErase = 1;

    HDC t_Dc = BeginPaint(myWnd, &t_Paint);

    myCanvas.PaintBegin();

    __OnPaintBackDC(NULL, NULL);

    __OnPaintMaskDC(NULL, NULL);

    myCanvas.PaintFinish();

    EndPaint(myWnd, &t_Paint);

    return RFine;
}

MfxReturn MicroFlakeX::MfxUI::__OnPaintBackDC(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    if (myBackImage)
    {
        myBackImage->Paint();
    }
    //宸戦紙崙Main
    SendMessageToFlakes(UI_MSG_PaintBack, wParam, lParam, true);
    return RFine;
}

MfxReturn MicroFlakeX::MfxUI::__OnPaintMaskDC(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    //宸戦紙崙Mask
    SendMessageToFlakes(UI_MSG_PaintMask, wParam, lParam, true);
    if (myMaskImage)
    {
        myMaskImage->Paint();
    }
    return RFine;
}

MfxReturn MicroFlakeX::MfxUI::__OnFlakeInsert(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    if (wParam)
    {
        if (myFlakeSet.insert((MfxFlake*)wParam).second)
        {
            myFlakeDeque.push_back(((MfxFlake*)wParam));
            MfxUI_Paper_Value t_PaperValue(this, myWnd, &myCanvas);
            ((MfxFlake*)wParam)->ProcMessage(UI_MSG_SetPaper, NULL, (LPARAM)&t_PaperValue);

            std::sort(myFlakeDeque.begin(), myFlakeDeque.end(), MfxApp::FloorCompare<MfxFlake>);
            PostMessage(myWnd, WM_PAINT, NULL, NULL);
            return RFine;
        }
    }
    return RFail;
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
                MfxUI_Paper_Value t_PaperValue;
                ((MfxFlake*)wParam)->ProcMessage(UI_MSG_SetPaper, NULL, (LPARAM)&t_PaperValue);
                myFlakeDeque.erase(delIt);
                myFlakeSet.erase((MfxFlake*)wParam);
                return RFine;
            }
        }
    }
    return RFail;
}

MfxReturn MicroFlakeX::MfxUI::__OnFlakeFloorChange(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    std::sort(myFlakeDeque.begin(), myFlakeDeque.end(), MfxApp::FloorCompare<MfxFlake>);
    return RFine;
}


MfxReturn MicroFlakeX::MfxUI::__OnTimer(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    auto t_Iter = __myTimerMap.find(wParam);
    if (t_Iter != __myTimerMap.end())
    {
        (this->*t_Iter->second.recvFunc)((*t_Iter).second.delayTime, clock() - (*t_Iter).second.passTime);
        (*t_Iter).second.passTime = clock();
        return RFine;
    }
    return RFail;
}

MfxReturn MicroFlakeX::MfxUI::__OnAddTimer(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    MfxUI_Timer_Value* t_TimerValue = (MfxUI_Timer_Value*)lParam;
    
    if (__myTimerMap.insert(MfxUI_Timer_Map_elem(wParam, *t_TimerValue)).second)
    {
        SetTimer(myWnd, wParam, t_TimerValue->delayTime, (TIMERPROC)NULL);
    }
    return RFine;
}

MfxReturn MicroFlakeX::MfxUI::__OnRemoveTimer(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    __myTimerMap.erase(wParam);
    KillTimer(myWnd, wParam);
    return RFine;
}


MfxReturn MicroFlakeX::MfxUI::__OnFlakeMessage(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    auto t_Iter = __myFlakeMessageMap.find(*(MfxUI_FlakeMessage_Key*)wParam);
    if (t_Iter != __myFlakeMessageMap.end())
    {
        (this->*t_Iter->second)(((MfxUI_FlakeMessage_Value*)lParam)->wParam, ((MfxUI_FlakeMessage_Value*)lParam)->lParam);
        return RFine;
    }
    return RFail;
}

MfxReturn MicroFlakeX::MfxUI::__OnAddFlakeMessage(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    return __myFlakeMessageMap.insert(
        MfxUI_FlakeMessage_Map_elem(*(MfxUI_FlakeMessage_Key*)lParam, *(MfxUI_Func*)wParam)).second ? RFine : RFail;
}

MfxReturn MicroFlakeX::MfxUI::__OnRemoveFlakeMessage(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    return  __myFlakeMessageMap.erase(*(MfxUI_FlakeMessage_Key*)lParam) ? RFine : RFail;
}

/**/
MfxReturn MicroFlakeX::MfxUI::__OnSetBackColor(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    MfxColor* t_Set = (MfxColor*)lParam;
    if (myBackImage)
    {
        myBackImage->FromColor(*t_Set, MfxSize(&myRect));
    }
    else
    {
        myBackImage = new MfxImage(*t_Set, MfxRect(0, 0, myRect.myWidth, myRect.myHeight));
        myBackImage->SetCanvas(&myCanvas);
    }
    return RFine;
}

MfxReturn MicroFlakeX::MfxUI::__OnSetMaskColor(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    MfxColor* t_Set = (MfxColor*)lParam;
    if (myMaskImage)
    {
        myMaskImage->FromColor(*t_Set, MfxSize(&myRect));
    }
    else
    {
        myMaskImage = new MfxImage(*t_Set, MfxRect(0, 0, myRect.myWidth, myRect.myHeight));
        myMaskImage->SetCanvas(&myCanvas);
    }
    return RFine;
}
/**/
MfxReturn MicroFlakeX::MfxUI::__OnSetBackImage(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    MfxImage* t_Set = (MfxImage*)lParam;
    if (t_Set)
    {
        SafeDelete(myBackImage);
        (t_Set)->Clone(&myBackImage);
        myBackImage->SetRect(MfxRect(0, 0, myRect.myWidth, myRect.myHeight));
        myBackImage->SetCanvas(&myCanvas);
    }
    return RFine;
}

MfxReturn MicroFlakeX::MfxUI::__OnSetMaskImage(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    MfxImage* t_Set = (MfxImage*)lParam;
    if (t_Set)
    {
        SafeDelete(myMaskImage);
        (t_Set)->Clone(&myMaskImage);
        myMaskImage->SetRect(MfxRect(0, 0, myRect.myWidth, myRect.myHeight));
        myMaskImage->SetCanvas(&myCanvas);
    }
    return RFine;
}

/**/