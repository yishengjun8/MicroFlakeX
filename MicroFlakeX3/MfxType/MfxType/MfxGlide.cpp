#include "pch.h"
#include "MfxType.h"

MfxObject_Init(MfxGlide)
MfxObject_EndInit(MfxGlide, MfxBase, \
	1, SetFPS, \
	1, BindObject, \
	2, BindObjectName, \
	3, Add_GetSetFuncName, \
	\
	1, GetFPS, \
	1, GetBindObject, \
	\
	0, Stop, \
	0, Begin, \
	0, Pause, \
	0, Clear, \
	\
	1, EachFrame, \
	3, MfxAddKeyframe);

MicroFlakeX::MfxGlide::MfxGlide()
{
	myFPS = 60;
	myBegin = 0;
	myPTP_TIMER = nullptr;
	myBindObject = nullptr;
}

MicroFlakeX::MfxGlide::MfxGlide(const MfxGlide* set)
{
	myFPS = set->myFPS;
	myBegin = 0;
	myPTP_TIMER = nullptr;
	myBindObject = nullptr;

	std::copy(set->myWidelyTypeMap.begin(), set->myWidelyTypeMap.end(), inserter(myWidelyTypeMap, myWidelyTypeMap.begin()));

	for (auto iter : myWidelyTypeMap)
	{
		MfxFactory(myWidelyTypeMap[iter.first].setObjectName, &(myWidelyTypeMap[iter.first].myGetObject_Set));
		MfxFactory(myWidelyTypeMap[iter.first].getObjectName, &(myWidelyTypeMap[iter.first].myGetObject_Begin));
	}
}

MicroFlakeX::MfxGlide::~MfxGlide()
{
	if (myPTP_TIMER)
	{
		MfxCloseTimer(myPTP_TIMER);
		myPTP_TIMER = 0;
	}

	for (auto i : myWidelyTypeMap)
	{
		SafeDelete(i.second.myGetObject_Set);
		SafeDelete(i.second.myGetObject_Begin);
	}
}

MfxReturn MicroFlakeX::MfxGlide::Clone(MfxBase** ret)const
{
	*ret = new MfxGlide(this);

	return Mfx_Return_Fine;
}

MfxBase& MicroFlakeX::MfxGlide::operator=(MfxBase& rhs)
{
	// TODO: 在此处插入 return 语句
	return *this;
}

MfxGlide& MicroFlakeX::MfxGlide::operator=(const MfxGlide* rhs)
{
	myFPS = rhs->myFPS;

	std::copy(rhs->myWidelyTypeMap.begin(), rhs->myWidelyTypeMap.end(), inserter(myWidelyTypeMap, myWidelyTypeMap.begin()));

	for (auto iter : myWidelyTypeMap)
	{
		MfxFactory(myWidelyTypeMap[iter.first].setObjectName, &(myWidelyTypeMap[iter.first].myGetObject_Set));
		MfxFactory(myWidelyTypeMap[iter.first].getObjectName, &(myWidelyTypeMap[iter.first].myGetObject_Begin));
	}

	return *this;
}

MfxGlide& MicroFlakeX::MfxGlide::operator=(const MfxGlide& rhs)
{
	myFPS = rhs.myFPS;

	std::copy(rhs.myWidelyTypeMap.begin(), rhs.myWidelyTypeMap.end(), inserter(myWidelyTypeMap, myWidelyTypeMap.begin()));

	for (auto iter : myWidelyTypeMap)
	{
		MfxFactory(myWidelyTypeMap[iter.first].setObjectName, &(myWidelyTypeMap[iter.first].myGetObject_Set));
		MfxFactory(myWidelyTypeMap[iter.first].getObjectName, &(myWidelyTypeMap[iter.first].myGetObject_Begin));
	}

	return *this;
}

MfxGlide& MicroFlakeX::MfxGlide::operator=(const MfxGlide&& rhs)
{
	myFPS = rhs.myFPS;

	std::copy(rhs.myWidelyTypeMap.begin(), rhs.myWidelyTypeMap.end(), inserter(myWidelyTypeMap, myWidelyTypeMap.begin()));

	for (auto iter : myWidelyTypeMap)
	{
		MfxFactory(myWidelyTypeMap[iter.first].setObjectName, &(myWidelyTypeMap[iter.first].myGetObject_Set));
		MfxFactory(myWidelyTypeMap[iter.first].getObjectName, &(myWidelyTypeMap[iter.first].myGetObject_Begin));
	}

	return *this;
}

bool MicroFlakeX::MfxGlide::operator==(MfxBase& rhs)
{
	return false;
}

bool MicroFlakeX::MfxGlide::operator==(const MfxGlide* rhs)const
{
	return false;
}

bool MicroFlakeX::MfxGlide::operator==(const MfxGlide& rhs)const
{
	return false;
}

bool MicroFlakeX::MfxGlide::operator==(const MfxGlide&& rhs)const
{
	return false;
}

MfxReturn MicroFlakeX::MfxGlide::GetFPS(UINT* ret)
{
	*ret = myFPS;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxGlide::GetBindObject(MfxBase** object)
{
	*object = myBindObject;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxGlide::SetFPS(const UINT set)
{
	myFPS = set;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxGlide::BindObject(MfxBase* object)
{
	myBindObject = object;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxGlide::BindObjectName(MfxString groupName, MfxGulid_WidelyType value)
{
	myWidelyTypeMap[groupName] = value;

	//SafeDelete(myWidelyTypeMap[groupName].myGetObject_Set);
	//SafeDelete(myWidelyTypeMap[groupName].myGetObject_Begin);

	MfxFactory(myWidelyTypeMap[groupName].setObjectName, &(myWidelyTypeMap[groupName].myGetObject_Set));
	MfxFactory(myWidelyTypeMap[groupName].getObjectName, &(myWidelyTypeMap[groupName].myGetObject_Begin));

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxGlide::Add_GetSetFuncName(MfxString groupName, MfxString getFuncName, MfxString setFuncName, pEaseGulid easeGulid)
{
	auto tFind = myWidelyTypeMap.find(groupName);

	if (tFind != myWidelyTypeMap.end())
	{
		tFind->second.myGulidTypePair.push_back(MfxGulid_GetSet_FuncName(getFuncName, setFuncName, easeGulid));
	}

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxGlide::Stop()
{
	if (myPTP_TIMER)
	{
		MfxCloseTimer(myPTP_TIMER);
		myPTP_TIMER = 0;
	}

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxGlide::Begin()
{
	if (!myBindObject || !myBindObjectType_Keyframe.size())
	{
		return Mfx_Return_Fail;
	}

	if (!myBegin)
	{
		myBegin = 1;
		for (auto& iter : myWidelyTypeMap)
		{
			iter.second.myBeginTime = clock();
			myBindObject->AutoFunc(iter.second.getObjectFuncName, iter.second.myGetObject_Begin);
		}
	}

	MfxBeginNewTimer(myPTP_TIMER, this, MfxText("EachFrame"), MfxParam(), 1000 / myFPS);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxGlide::Pause()
{
	if (myPTP_TIMER)
	{
		MfxCloseTimer(myPTP_TIMER);
		myPTP_TIMER = 0;
	}
	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxGlide::Clear()
{
	return MfxReturn();
}

MfxReturn MicroFlakeX::MfxGlide::EachFrame(MfxParam myParam)
{
	if (myPTP_TIMER == 0)
	{
		return Mfx_Return_Fine;
	}

	int i = myBindObjectType_Keyframe.size();
	for (auto tKeyObjectType = myBindObjectType_Keyframe.begin(); tKeyObjectType != myBindObjectType_Keyframe.end(); tKeyObjectType++)
	{
		if (tKeyObjectType->second.size() == 0)
		{
			i--;
		}
	}
	if (i == 0)
	{
		if (myPTP_TIMER)
		{
			myBegin = 1;
			MfxCloseTimer(myPTP_TIMER);
			myPTP_TIMER = 0;
		}
		return Mfx_Return_Fine;
	}

	for (auto& tKeyObjectType : myBindObjectType_Keyframe)
	{
		if (tKeyObjectType.second.size() == 0)
		{
			continue;
		}

		auto tFind = myWidelyTypeMap.find(tKeyObjectType.first);

		if (tFind != myWidelyTypeMap.end())
		{
			//检查写入区域是否为nulllptr
			if (!tFind->second.myGetObject_Set || !tFind->second.myGetObject_Begin || !tKeyObjectType.second.front().key)
			{
				continue;
			}

			LONGLONG tBg = 0, tTo = 0, tNow = 0;

			tFind->second.myThroughTime = clock() - tFind->second.myBeginTime;

			for (int i = 0; i < tFind->second.myGulidTypePair.size(); i++)
			{
				tFind->second.myGetObject_Begin->AutoFunc(tFind->second.myGulidTypePair[i].myGetFuncName, &tBg);

				tKeyObjectType.second.front().key->AutoFunc(tFind->second.myGulidTypePair[i].myGetFuncName, &tTo);

				tNow = tBg + (tTo - tBg) * tFind->second.myGulidTypePair[i].myEaseGulid((double)tFind->second.myThroughTime / (double)tKeyObjectType.second.front().time);

				tFind->second.myGetObject_Set->AutoFunc(tFind->second.myGulidTypePair[i].mySetFuncName, tNow);
			}

			myBindObject->AutoFunc(tFind->second.setObjectFuncName, tFind->second.myGetObject_Set);


			if (tFind->second.myThroughTime > tKeyObjectType.second.front().time)
			{
				myBindObject->AutoFunc(tFind->second.getObjectFuncName, tFind->second.myGetObject_Begin);

				tFind->second.myBeginTime = clock();

				delete tKeyObjectType.second.front().key;
				tKeyObjectType.second.pop();
			}
		}
		else
		{
			delete tKeyObjectType.second.front().key;
			tKeyObjectType.second.pop();
		}
	}
	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxGlide::MfxAddKeyframe(MfxString groupName, MfxBase* set, LONGLONG delay)
{
	Begin:
	auto tFind = myBindObjectType_Keyframe.find(groupName);
	if (tFind != myBindObjectType_Keyframe.end())
	{
		MfxBase* tObject = nullptr;
		set->Clone(&tObject);
		tFind->second.push(MfxGulid_Keyframe(tObject, delay));
	}
	else
	{ 
		myBindObjectType_Keyframe.insert(MfxGulid_BindObjectType_Keyframe_Queue_Map_Pair(groupName, MfxGulid_BindObjectType_Keyframe_Queue()));
		goto Begin;
	}

	return Mfx_Return_Fine;
}
