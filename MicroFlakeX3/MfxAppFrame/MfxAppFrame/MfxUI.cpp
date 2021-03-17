#include "pch.h"
#include "MfxAppFrame.h"

MfxObject_Init_0(MfxUI)
MfxObject_Init_1(MfxUI)
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

    UI_CON_RECV_MSG(MfxUI_Message_SetPaper);

    UI_CON_RECV_MSG(MfxUI_Message_PaintBack);
    UI_CON_RECV_MSG(MfxUI_Message_PaintMask);

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
    UI_REG_MSG(MfxUI_Message_PaintBack, MfxUI, __OnPaintBackDC, myCoverFloor);
    UI_REG_MSG(MfxUI_Message_PaintMask, MfxUI, __OnPaintMaskDC, myCoverFloor);

    UI_REG_MSG(MfxUI_Message_ControlInsert, MfxUI, __OnControlInsert, myCoverFloor);
    UI_REG_MSG(MfxUI_Message_ControlRemove, MfxUI, __OnControlRemove, myCoverFloor);
    UI_REG_MSG(MfxControl_Message_ControlFloorChange, MfxUI, __OnControlFloorChange, myCoverFloor);

    UI_REG_MSG(WM_TIMER, MfxUI, __OnTimer, myCoverFloor);
    UI_REG_MSG(MfxUI_Message_AddTimer, MfxUI, __OnAddTimer, myCoverFloor);
    UI_REG_MSG(MfxUI_Message_RemoveTimer, MfxUI, __OnRemoveTimer, myCoverFloor);

    UI_REG_MSG(MfxControl_Message_ControlMessage, MfxUI, __OnControlMessage, myCoverFloor);
    UI_REG_MSG(MfxUI_Message_AddControlMessage, MfxUI, __OnAddControlMessage, myCoverFloor);
    UI_REG_MSG(MfxUI_Message_RemoveControlMessage, MfxUI, __OnRemoveControlMessage, myCoverFloor);

    UI_REG_MSG(MfxUI_Message_SetBackColor, MfxUI, __OnSetBackColor, myCoverFloor);
    UI_REG_MSG(MfxUI_Message_SetMaskColor, MfxUI, __OnSetMaskColor, myCoverFloor);
    UI_REG_MSG(MfxUI_Message_SetBackImage, MfxUI, __OnSetBackImage, myCoverFloor);
    UI_REG_MSG(MfxUI_Message_SetMaskImage, MfxUI, __OnSetMaskImage, myCoverFloor);
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
    MfxApp::theApp->MfxCreateUIExW(
        this, tRect,
        NULL, MfxUI_Style_Normal,
        L"MfxNormalUI", L"MfxNormalUI");
}

MicroFlakeX::MfxUI::MfxUI(MfxRect set, MfxStrW title)
{
    MfxUIInitData();
    MfxRegMessages();

    MfxApp::theApp->MfxCreateUIExW(
        this, set,
        NULL, MfxUI_Style_Normal,
        L"MfxNormalUI", title);
}

MicroFlakeX::MfxUI::MfxUI(MfxRect set, DWORD myStyle_EN, MfxStrW title)
{
    MfxUIInitData();
    MfxRegMessages();

    MfxApp::theApp->MfxCreateUIExW(
        this, set,
        NULL, myStyle_EN,
        L"MfxNormalUI", title);
}

MicroFlakeX::MfxUI::MfxUI(MfxRect set, DWORD myStyleEx_EN, DWORD myStyle_EN, MfxStrW myClass, MfxStrW title)
{
    MfxUIInitData();
    MfxRegMessages();

    MfxApp::theApp->MfxCreateUIExW(
        this, set,
        myStyleEx_EN, myStyle_EN,
        L"MfxNormalUI", title);
}

MicroFlakeX::MfxUI::~MfxUI()
{
    MfxCodeLock(this);
    while (myControlDeque.size())
    {
        //峪俶勣距喘陣周議裂更痕方祥辛參阻
        //裂更痕方氏徭強窟僕陣周��支��連栖廣��麿議陣周啌符
        delete myControlDeque[0];
    }

    SafeDelete(myBackImage);
    SafeDelete(myMaskImage);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::CreateSuccess()
{
    return myWnd ? RFine : RFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::ProcMessage(MfxMsg message, WPARAM wParam, LPARAM lParam)
{
    SendMessageToControls(message, wParam, lParam, false);

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

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::SendMessageToControls(MfxMsg message, WPARAM wParam, LPARAM lParam, bool sort)
{
    MfxControl* t_FloatFocus = myMutexFocus;
    myMutexFocus = myMutexFocusLockFlag ? myMutexFocus : nullptr;

    if (myControlMessageSet.find(message) != myControlMessageSet.end())
    {
        if (sort)
        {
            for (int i = myControlDeque.size() - 1; i >= 0; i--)
            {
                myControlDeque[i]->ProcMessage(message, wParam, lParam);
            }
        }
        else
        {
            for (auto t_Iter : myControlDeque)
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

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::AddControl(MfxControl* set)
{
    return ProcMessage(MfxUI_Message_ControlInsert, (WPARAM)set, NULL);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::RemoveControl(MfxControl* set)
{
    return ProcMessage(MfxUI_Message_ControlRemove, (WPARAM)set, NULL);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::AddControlMessage(MfxControl* target, MfxMsg message, MfxUI_Func recv)
{
    MfxUI_ControlMessage_Key t_ControlMessage(target, message);
    return ProcMessage(MfxUI_Message_AddControlMessage, (WPARAM)&recv, (LPARAM)&t_ControlMessage);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::RemoveControlMessage(MfxControl* target, MfxMsg message)
{
    MfxUI_ControlMessage_Key t_ControlMessage(target, message);
    return ProcMessage(MfxUI_Message_RemoveControlMessage, NULL, (LPARAM)&t_ControlMessage);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::AddTimer(WPARAM timerID, clock_t delay, MfxUI_Func recv)
{
    MfxUI_Timer_Value t_TimerValue(delay, clock(), recv);
    return ProcMessage(MfxUI_Message_AddTimer, timerID, (LPARAM)&t_TimerValue);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::RemoveTimer(WPARAM cid)
{
    return ProcMessage(MfxUI_Message_RemoveTimer, cid, NULL);
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::GetWnd(HWND* ret)
{
    *ret = myWnd;
    return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::GetRect(MfxRect* ret)
{
    *ret = myRect;
    return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::GetSize(MfxSize* ret)
{
    *ret = myRect;
    return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::GetPoint(MfxPoint* ret)
{
    *ret = myRect;
    return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::GetBackImage(MfxImage** ret)
{
    MfxCodeLock(this);
    return myBackImage ? myBackImage->Clone(ret) : RFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::GetMaskImage(MfxImage** ret)
{
    MfxCodeLock(this);
    return myMaskImage ? myMaskImage->Clone(ret) : RFail;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::SetRect(MfxRect set)
{
    return SetWindowPos(myWnd, NULL, set.myX, set.myY, set.myWidth, set.myHeight, SWP_NOZORDER) ? RFine : RFail;;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::SetSize(MfxSize set)
{
    return SetWindowPos(myWnd, NULL, 0, 0, set.myWidth, set.myHeight, SWP_NOMOVE | SWP_NOZORDER) ? RFine : RFail;;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::SetPoint(MfxPoint set)
{
    return SetWindowPos(myWnd, NULL, set.myX, set.myY, 0, 0, SWP_NOSIZE | SWP_NOZORDER) ? RFine : RFail;;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::SetBackColor(MfxColor set)
{
    return ProcMessage(MfxUI_Message_SetBackColor, NULL, (LPARAM)&set);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::SetMaskColor(MfxColor set)
{
    return ProcMessage(MfxUI_Message_SetMaskColor, NULL, (LPARAM)&set);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::SetBackImage(MfxImage* set)
{
    return ProcMessage(MfxUI_Message_SetBackImage, NULL, (LPARAM)set);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::SetMaskImage(MfxImage* set)
{
    return ProcMessage(MfxUI_Message_SetMaskImage, NULL, (LPARAM)set);
}

/**
MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::SetBigIcon(MfxImage* set)
{
    MfxBitmap* t_Bitmap;
    set->GetShowBitmap(&t_Bitmap);

    HICON t_Icon;
    t_Bitmap->GetHICON(&t_Icon);
    delete t_Bitmap;
    return ProcMessage(WM_SETICON, ICON_BIG, (LPARAM)t_Icon);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::SetSmallIcon(MfxImage* set)
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

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::LockMutexFocus(MfxControl* set)
{
    MfxCodeLock(this);
    myMutexFocus = set;
    myMutexFocusLockFlag = true;
    return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::UnLockMutexFocus()
{
    MfxCodeLock(this);
    myMutexFocusLockFlag = false;
    return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::SetMutexFocus(MfxControl* set)
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

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::SetKeyboardFocus(MfxControl* set)
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

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::GetMutexFocus(MfxControl** ret)
{
    MfxCodeLock(this);
    *ret = myMutexFocus;
    return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::GetKeyboardFocus(MfxControl** ret)
{
    MfxCodeLock(this);
    *ret = myKeyboardFocus;
    return RFine;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::RemoveMessage(MfxMsg message, MfxStrW name)
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

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::InsertMessage(MfxMsg message, MfxUI_MessageMap_Value* msgValue)
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

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnTest00(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    std::cout << "__OnTest00: wParam-" << wParam << " lParam-" << lParam << std::endl;
    return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnTest01(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    std::cout << "__OnTest01: wParam-" << wParam << " lParam-" << lParam << std::endl;
    return RFine;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnCreate(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    CREATESTRUCTA* t_Create = (CREATESTRUCTA*)lParam;

    myRect.Init(t_Create->x, t_Create->y, t_Create->cx, t_Create->cy);

    //MfxSize t_Size(GetSystemMetrics(SM_CXFULLSCREEN), GetSystemMetrics(SM_CYFULLSCREEN));

    myCanvas.SetSize(MfxSize(myRect.myWidth, myRect.myHeight));
    myCanvas.SetWnd(myWnd);

    myBackImage = new MfxImage(MfxColor(255, 0, 255, 255), MfxRect(0, 0, myRect.myWidth, myRect.myHeight));
    myBackImage->SetCanvas(&myCanvas);
    return 0;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnDestroy(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    PostQuitMessage(0); //潤崩��連儉桟
    return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnSize(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    myRect.myWidth = LOWORD(lParam);
    myRect.myHeight = HIWORD(lParam);
    return DefWindowProc(myWnd, WM_SIZE, wParam, lParam);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnMove(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    myRect.myX = LOWORD(lParam);
    myRect.myY = HIWORD(lParam);
    return DefWindowProc(myWnd, WM_MOVE, wParam, lParam);
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnPaint(WPARAM wParam, LPARAM lParam)
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

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnPaintBackDC(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    if (myBackImage)
    {
        myBackImage->Paint();
    }
    //宸戦紙崙Main
    SendMessageToControls(MfxUI_Message_PaintBack, wParam, lParam, true);
    return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnPaintMaskDC(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    //宸戦紙崙Mask
    SendMessageToControls(MfxUI_Message_PaintMask, wParam, lParam, true);
    if (myMaskImage)
    {
        myMaskImage->Paint();
    }
    return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnControlInsert(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    if (wParam)
    {
        if (myControlSet.insert((MfxControl*)wParam).second)
        {
            myControlDeque.push_back(((MfxControl*)wParam));
            MfxUI_Paper_Value t_PaperValue(this, myWnd, &myCanvas);
            ((MfxControl*)wParam)->ProcMessage(MfxUI_Message_SetPaper, NULL, (LPARAM)&t_PaperValue);

            std::sort(myControlDeque.begin(), myControlDeque.end(), MfxApp::FloorCompare<MfxControl>);
            PostMessageW(myWnd, WM_PAINT, NULL, NULL);
            return RFine;
        }
    }
    return RFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnControlRemove(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    if (wParam)
    {
        for (auto delIt = myControlDeque.begin(); delIt != myControlDeque.end(); delIt++)
        {
            if (*delIt == (MfxControl*)wParam)
            {
                MfxUI_Paper_Value t_PaperValue;
                ((MfxControl*)wParam)->ProcMessage(MfxUI_Message_SetPaper, NULL, (LPARAM)&t_PaperValue);
                myControlDeque.erase(delIt);
                myControlSet.erase((MfxControl*)wParam);
                return RFine;
            }
        }
    }
    return RFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnControlFloorChange(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    std::sort(myControlDeque.begin(), myControlDeque.end(), MfxApp::FloorCompare<MfxControl>);
    return RFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnTimer(WPARAM wParam, LPARAM lParam)
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

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnAddTimer(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    MfxUI_Timer_Value* t_TimerValue = (MfxUI_Timer_Value*)lParam;
    
    if (__myTimerMap.insert(MfxUI_Timer_Map_elem(wParam, *t_TimerValue)).second)
    {
        SetTimer(myWnd, wParam, t_TimerValue->delayTime, (TIMERPROC)NULL);
    }
    return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnRemoveTimer(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    __myTimerMap.erase(wParam);
    KillTimer(myWnd, wParam);
    return RFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnControlMessage(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    auto t_Iter = __myControlMessageMap.find(*(MfxUI_ControlMessage_Key*)wParam);
    if (t_Iter != __myControlMessageMap.end())
    {
        (this->*t_Iter->second)(((MfxUI_ControlMessage_Value*)lParam)->wParam, ((MfxUI_ControlMessage_Value*)lParam)->lParam);
        return RFine;
    }
    return RFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnAddControlMessage(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    return __myControlMessageMap.insert(
        MfxUI_ControlMessage_Map_elem(*(MfxUI_ControlMessage_Key*)lParam, *(MfxUI_Func*)wParam)).second ? RFine : RFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnRemoveControlMessage(WPARAM wParam, LPARAM lParam)
{
    MfxCodeLock(this);
    return  __myControlMessageMap.erase(*(MfxUI_ControlMessage_Key*)lParam) ? RFine : RFail;
}

/**/
MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnSetBackColor(WPARAM wParam, LPARAM lParam)
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

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnSetMaskColor(WPARAM wParam, LPARAM lParam)
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
MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnSetBackImage(WPARAM wParam, LPARAM lParam)
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

MicroFlakeX::MfxReturn MicroFlakeX::MfxUI::__OnSetMaskImage(WPARAM wParam, LPARAM lParam)
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