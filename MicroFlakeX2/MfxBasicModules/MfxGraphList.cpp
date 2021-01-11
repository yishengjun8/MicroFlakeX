#include "pch.h"
#include "MfxBasicGraph.h"

using MicroFlakeX::MfxGraphList;
BEGIN_INITDATA(MfxGraphList)
INITDATA(MfxGraphList, Clone, 0);
INITDATA(MfxGraphList, Similar, 1);
INITDATA(MfxGraphList, SetDC, 2);
INITDATA(MfxGraphList, GetDC, 3);
INITDATA(MfxGraphList, Draw, 4);
INITDATA(MfxGraphList, SetRect, 5);
INITDATA(MfxGraphList, SetSize, 6);
INITDATA(MfxGraphList, SetPoint, 7);
INITDATA(MfxGraphList, GetRect, 8);
INITDATA(MfxGraphList, GetSize, 9);
INITDATA(MfxGraphList, GetPoint, 10);
INITDATA(MfxGraphList, CollisionWith, 11);
INITDATA(MfxGraphList, SetCollisionBlock, 12);
END_INITDATA;
BEGIN_AUTOMAP(MfxGraphList)
CASE_FUNC_P1(MfxGraphList, Clone, 0)
CASE_FUNC_P1(MfxGraphList, Similar, 1)
CASE_FUNC_P1(MfxGraphList, SetDC, 2)
CASE_FUNC_P1(MfxGraphList, GetDC, 3)
CASE_FUNC_P0(MfxGraphList, Draw, 4)
CASE_FUNC_P1(MfxGraphList, SetRect, 5)
CASE_FUNC_P1(MfxGraphList, SetSize, 6)
CASE_FUNC_P1(MfxGraphList, SetPoint, 7)
CASE_FUNC_P1(MfxGraphList, GetRect, 8)
CASE_FUNC_P1(MfxGraphList, GetSize, 9)
CASE_FUNC_P1(MfxGraphList, GetPoint, 10)
CASE_FUNC_P2(MfxGraphList, CollisionWith, 11)
CASE_FUNC_P1(MfxGraphList, SetCollisionBlock, 12)
END_AUTOMAP;


void MicroFlakeX::MfxGraphList::MfxGraphListInitData()
{
	MFXLOCK;
	REALIZE_AUTOBASIC;
	myDC = nullptr;
	myRect = GdipRect(0, 0, 1, 1);
	myCollisionBlock = GdipSize(30, 30);
	myRenderTarget = nullptr;
}

MicroFlakeX::MfxGraphList::MfxGraphList()
{
	MFXLOCK;
	MfxGraphListInitData();
}

MicroFlakeX::MfxGraphList::~MfxGraphList()
{
	MFXLOCK;
	for (auto i : myGraphVector)
	{
		delete i;
		i = nullptr;
	}
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxGraphList::Clone(MfxGraphList** ret)
{
	MFXLOCK;
	if (!ret) { return MfxFail; };

	MfxGraphList* t_Ret = new MfxGraphList;
	for (auto i : myGraphVector)
	{
		t_Ret->AddItem(i->myGraph, i->myFloor);
	}
	*ret = t_Ret;
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxGraphList::Similar(MfxGraphList* set)
{
	MFXLOCK;
	return MfxReturn();
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxGraphList::AddItem(MfxBasicGraph* set, int floor)
{
	MFXLOCK;
	if (!set) { return MfxFail; };

	MfxBasicGraph* t_Add = nullptr;
	set->AutoFunc(L"Clone", &t_Add);
	if (t_Add)
	{
		t_Add->AutoFunc(L"SetDC", myDC);
		t_Add->AutoFunc(L"SetRect", myRect);
		t_Add->AutoFunc(L"SetRenderTarget", myRenderTarget);
		t_Add->AutoFunc(L"SetCollisionBlock", myCollisionBlock);
		myGraphVector.push_back(new MfxGraphList_Value(t_Add, floor));
		std::sort(myGraphVector.begin(), myGraphVector.end(), __MicroFlakeX::MfxGraphListFloorCompare);
		myItem = myGraphVector.begin();
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxGraphList::RemoveItem(MfxBasicGraph* set)
{
	MFXLOCK;
	if (!set) { return MfxFail; };

	for (auto iter = myGraphVector.begin(); iter != myGraphVector.end(); iter++)
	{
		if ((*iter)->myGraph == set)
		{
			delete (*iter);
			myGraphVector.erase(iter);
			myItem = myGraphVector.begin();
			return MfxFine;
		}
	}
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxGraphList::NextItem()
{
	MFXLOCK;
	if (myItem != myGraphVector.end())
	{
		myItem++;
	}
	if (myItem == myGraphVector.end())
	{
		myItem = myGraphVector.begin();
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxGraphList::GetItemObject(MfxBasicGraph** ret)
{
	MFXLOCK;
	if (!ret) { return MfxFail; };

	if (myItem != myGraphVector.end())
	{
		return (*myItem)->myGraph->AutoFunc(L"Clone", ret);
	}
	return MfxFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxGraphList::SetDC(HDC set)
{
	MFXLOCK;
	myDC = set;
	for (auto i : myGraphVector)
	{
		i->myGraph->AutoFunc(L"SetDC", set);
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxGraphList::GetDC(HDC* ret)
{
	MFXLOCK;
	if (!ret) { return MfxFail; };
	*ret = myDC;
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxGraphList::SetRenderTarget(ID2D1RenderTarget* set)
{
	MFXLOCK;
	myRenderTarget = set;
	for (auto i : myGraphVector)
	{
		i->myGraph->AutoFunc(L"SetRenderTarget", set);
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxGraphList::GetRenderTarget(ID2D1RenderTarget** ret)
{
	MFXLOCK;
	if (!ret) { return MfxFail; };
	*ret = myRenderTarget;
	return MfxFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxGraphList::Draw()
{
	MFXLOCK;
	if (myItem != myGraphVector.end())
	{
		return (*myItem)->myGraph->AutoFunc(L"Draw");
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxGraphList::SetRect(GdipRect set)
{
	MFXLOCK;
	myRect = set;
	for (auto i : myGraphVector)
	{
		i->myGraph->AutoFunc(L"SetRect", set);
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxGraphList::SetSize(GdipSize set)
{
	MFXLOCK;
	myRect = GdipRect(myRect.X, myRect.Y, set.Width, set.Height);
	for (auto i : myGraphVector)
	{
		i->myGraph->AutoFunc(L"SetSize", set);
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxGraphList::SetPoint(GdipPoint set)
{
	MFXLOCK;
	myRect = GdipRect(set.X, set.Y, myRect.Width, myRect.Height);
	for (auto i : myGraphVector)
	{
		i->myGraph->AutoFunc(L"SetPoint", set);
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxGraphList::GetRect(GdipRect* ret)
{
	MFXLOCK;
	if (!ret) { return MfxFail; };

	*ret = myRect;
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxGraphList::GetSize(GdipSize* ret)
{
	MFXLOCK;
	if (!ret) { return MfxFail; };
	*ret = GdipSize(myRect.Width, myRect.Height);
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxGraphList::GetPoint(GdipPoint* ret)
{
	MFXLOCK;
	if (!ret) { return MfxFail; };
	*ret = GdipSize(myRect.X, myRect.Y);
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxGraphList::CollisionWith(MfxBasicGraph* set, bool* ret)
{
	MFXLOCK;
	*ret = false;
	if (myItem != myGraphVector.end())
	{
		return (*myItem)->myGraph->AutoFunc(L"CollisionWith", set, ret);
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxGraphList::SetCollisionBlock(GdipSize set)
{
	MFXLOCK;
	myCollisionBlock = set;
	for (auto i : myGraphVector)
	{
		i->myGraph->AutoFunc(L"SetCollisionBlock", set);
	}
	return MfxFine;
}
