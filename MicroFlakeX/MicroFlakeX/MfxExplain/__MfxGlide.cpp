#include "pch.h"
#include "MfxExplain.h"

MFX_OBJ_REFLECTION_INIT(__MfxGlide)
MFX_OBJ_REFLECTION_ENDINIT(__MfxGlide, MfxBase, \
	SetFPS, \
	BindObject, \
	BindObjectName, \
	Add_GetSetFuncName, \
	\
	GetFPS, \
	GetBindObject, \
	\
	Stop, \
	Begin, \
	Pause, \
	Clear, \
	\
	EachFrame, \
	AddKeyframe);

MicroFlakeX::__MfxGlide::__MfxGlide()
{
	myFPS = 60;
	myBegin = 0;
	myPTP_TIMER = nullptr;
	myBindObject = nullptr;

	myGroupType_Keyframe = new MfxGulid_GroupType_Keyframe_Queue_Map;
	myGroupType_Keyframe_Buff = new MfxGulid_GroupType_Keyframe_Queue_Map;
}

MicroFlakeX::__MfxGlide::__MfxGlide(const __MfxGlide* set) 
	: __MfxGlide()
{
	myFPS = set->myFPS;

	std::copy(set->myGroupDetails_Map.begin(), set->myGroupDetails_Map.end(), inserter(myGroupDetails_Map, myGroupDetails_Map.begin()));

	for (auto iter : myGroupDetails_Map)
	{
		MfxFactory(myGroupDetails_Map[iter.first].setObjectName, &(myGroupDetails_Map[iter.first].myGetObject_Set));
		MfxFactory(myGroupDetails_Map[iter.first].getObjectName, &(myGroupDetails_Map[iter.first].myGetObject_Begin));
	}
}

MicroFlakeX::__MfxGlide::~__MfxGlide()
{
	if (myPTP_TIMER)
	{
		MfxCloseTimer(myPTP_TIMER);
		myPTP_TIMER = 0;
	}

	for (auto i : myGroupDetails_Map)
	{
		SafeDelete(i.second.myGetObject_Set);
		SafeDelete(i.second.myGetObject_Begin);
	}

	//delete myGroupType_Keyframe + myGroupType_Keyframe_Buff
}

MfxReturn MicroFlakeX::__MfxGlide::Clone(MfxBase** ret)
{
	*ret = new __MfxGlide(this);

	return MFX_RET_SECCESS;
}

MfxBase& MicroFlakeX::__MfxGlide::operator=(MfxBase& rhs)
{
	return *this;
}

__MfxGlide& MicroFlakeX::__MfxGlide::operator=(const __MfxGlide* rhs)
{
	myFPS = rhs->myFPS;

	std::copy(rhs->myGroupDetails_Map.begin(), rhs->myGroupDetails_Map.end(), inserter(myGroupDetails_Map, myGroupDetails_Map.begin()));

	for (auto iter : myGroupDetails_Map)
	{
		MfxFactory(myGroupDetails_Map[iter.first].setObjectName, &(myGroupDetails_Map[iter.first].myGetObject_Set));
		MfxFactory(myGroupDetails_Map[iter.first].getObjectName, &(myGroupDetails_Map[iter.first].myGetObject_Begin));
	}

	return *this;
}

__MfxGlide& MicroFlakeX::__MfxGlide::operator=(const __MfxGlide& rhs)
{
	return *this = &rhs;
}

__MfxGlide& MicroFlakeX::__MfxGlide::operator=(const __MfxGlide&& rhs) noexcept
{
	return *this = &rhs;
}

bool MicroFlakeX::__MfxGlide::operator==(MfxBase& rhs)
{
	return false;
}

bool MicroFlakeX::__MfxGlide::operator==(const __MfxGlide* rhs) const
{
	return false;
}

bool MicroFlakeX::__MfxGlide::operator==(const __MfxGlide& rhs) const
{
	return false;
}

bool MicroFlakeX::__MfxGlide::operator==(const __MfxGlide&& rhs) const
{
	return false;
}

MfxReturn MicroFlakeX::__MfxGlide::GetFPS(UINT* ret)
{
	*ret = myFPS;

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::__MfxGlide::GetBindObject(MfxBase** object)
{
	*object = myBindObject;

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::__MfxGlide::SetFPS(const UINT set)
{
	myFPS = set;

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::__MfxGlide::BindObject(MfxBase* object)
{
	myBindObject = object;

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::__MfxGlide::BindObjectName(MfxStringW groupName, MfxGulid_GroupDetails value)
{
	myGroupDetails_Map[groupName] = value;

	//SafeDelete(myGroupDetails_Map[groupName].myGetObject_Set);
	//SafeDelete(myGroupDetails_Map[groupName].myGetObject_Begin);

	MfxFactory(myGroupDetails_Map[groupName].setObjectName, &(myGroupDetails_Map[groupName].myGetObject_Set));
	MfxFactory(myGroupDetails_Map[groupName].getObjectName, &(myGroupDetails_Map[groupName].myGetObject_Begin));

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::__MfxGlide::Add_GetSetFuncName(MfxStringW groupName, MfxStringW getFuncName, MfxStringW setFuncName, pEaseGulid easeGulid)
{
	auto tFind = myGroupDetails_Map.find(groupName);

	if (tFind != myGroupDetails_Map.end())
	{
		tFind->second.myGulidTypePair.push_back(MfxGulid_GetSet_FuncName(getFuncName, setFuncName, easeGulid));
	}

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::__MfxGlide::Stop()
{
	MFX_MAKE_TEMP_LOCK(&myGroupType_Keyframe_Buff, &myGroupType_Keyframe);

	if (myBegin && myPTP_TIMER)
	{
		myBegin = false;
		MfxCloseTimer(myPTP_TIMER);

		//优化一下这里
		for (auto& tKeyGroup : (*myGroupType_Keyframe))
		{
			while (!tKeyGroup.second.empty())
			{
				(*myGroupType_Keyframe_Buff)[tKeyGroup.first].push(tKeyGroup.second.front());
				tKeyGroup.second.pop();
			}
		}
		return MFX_RET_SECCESS;
	}
	else
	{
		return MFX_RET_FAILED;
	}
	
}

MfxReturn MicroFlakeX::__MfxGlide::Begin()
{
	MFX_MAKE_TEMP_LOCK(&myGroupType_Keyframe_Buff, &myGroupType_Keyframe);
	//线程必须没有启动并且绑定obj不为空
	if (myPTP_TIMER == nullptr && myBindObject != nullptr)
	{
		//如果开始标记为空，则代表第一次开始，交换缓冲区
		if (myBegin == false)
		{
			myBegin = true;
			Swap(myGroupType_Keyframe_Buff, myGroupType_Keyframe);
			
		}
		//开始的时候，重新获取当前位置，计算
		for (auto& iter : myGroupDetails_Map)
		{
			iter.second.myBeginTime = clock();
			myBindObject->Reflection(iter.second.getObjectFuncName, iter.second.myGetObject_Begin);
		}
		MfxBeginNewTimer(myPTP_TIMER, this, MFX_TXT_W("EachFrame"), MfxParam(), 1000 / myFPS);
		return MFX_RET_SECCESS;
	}
	return MFX_RET_FAILED;
}

MfxReturn MicroFlakeX::__MfxGlide::Pause()
{
	MFX_MAKE_TEMP_LOCK(&myGroupType_Keyframe_Buff, &myGroupType_Keyframe);
	if (myPTP_TIMER)
	{
		MfxCloseTimer(myPTP_TIMER);
	}

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::__MfxGlide::Clear()
{
	MFX_MAKE_TEMP_LOCK(&myGroupType_Keyframe_Buff, &myGroupType_Keyframe);
	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::__MfxGlide::IsRun(bool* ret)
{
	*ret = myBegin;
	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::__MfxGlide::EachFrame(MfxParam param)
{
	MFX_MAKE_TEMP_LOCK(&myGroupType_Keyframe_Buff, &myGroupType_Keyframe);

	//std::cout << t.myFuncLock.size() << std::endl;
	//检查当前线程是否已经被关闭
	if (myPTP_TIMER == nullptr || myBegin == false)
	{
		return MFX_RET_SECCESS;
	}

	//检查当前关键帧是否清空
	for (auto& tKeyGroup : (*myGroupType_Keyframe))
	{
		if (!tKeyGroup.second.empty())
		{
			goto FUNC_CONTINUE;
		}

	}

	//将开始制空，以重新分配
	myBegin = false;
	MfxCloseTimer(myPTP_TIMER);

	return MFX_RET_SECCESS;


FUNC_CONTINUE:
	for (auto& tKeyGroup : *myGroupType_Keyframe)
	{
		//关键组的Key队列是否为空
		if (tKeyGroup.second.empty()) continue;

		//从组名映射这一组的具体细节
		auto iterGroupDetails = myGroupDetails_Map.find(tKeyGroup.first);
		if (iterGroupDetails != myGroupDetails_Map.end())
		{
			//检查写入区域是否为nulllptr
			//if (!tGroupDetails.myGetObject_Set || !tGroupDetails.myGetObject_Begin || !tKeyGroup.second.front().key)
			//{
			//	continue;
			//}

			auto& tGroupDetails = iterGroupDetails->second;

			tGroupDetails.myThroughTime = clock() - tGroupDetails.myBeginTime;

			LONG tBg = 0, tTo = 0, tThrough = 0;
			for (int i = 0; i < tGroupDetails.myGulidTypePair.size(); i++)
			{
				tGroupDetails.myGetObject_Begin->Reflection(tGroupDetails.myGulidTypePair[i].myGetFuncName, &tBg);

				tKeyGroup.second.front().key->Reflection(tGroupDetails.myGulidTypePair[i].myGetFuncName, &tTo);

				tThrough = (tTo - tBg) * tGroupDetails.myGulidTypePair[i].myEaseGulid((double)tGroupDetails.myThroughTime / (double)tKeyGroup.second.front().time);

				tGroupDetails.myGetObject_Set->Reflection(tGroupDetails.myGulidTypePair[i].mySetFuncName, (tThrough + tBg));
			}

			myBindObject->Reflection(tGroupDetails.setObjectFuncName, tGroupDetails.myGetObject_Set);

			//时间结束，不再计算这一个关键帧了，从当前时刻开始转入计算下一个关键帧
			if (tGroupDetails.myThroughTime > tKeyGroup.second.front().time)
			{
				tGroupDetails.myBeginTime = clock();
				myBindObject->Reflection(tGroupDetails.getObjectFuncName, tGroupDetails.myGetObject_Begin);

				//用完的关键帧存入缓冲区中，等待下一次启用
				(*myGroupType_Keyframe_Buff)[tKeyGroup.first].push(tKeyGroup.second.front());
				tKeyGroup.second.pop();
			}
		}
		else
		{
			//用完的关键帧存入缓冲区中，等待下一次启用
			(*myGroupType_Keyframe_Buff)[tKeyGroup.first].push(tKeyGroup.second.front());
			tKeyGroup.second.pop();
		}
	}
	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::__MfxGlide::AddKeyframe(MfxStringW groupName, MfxBase* set, LONGLONG delay)
{
	if (myBegin)
	{
		return MFX_RET_FAILED;
	}
	Begin:
	auto tFind = myGroupType_Keyframe_Buff->find(groupName);
	if (tFind != myGroupType_Keyframe_Buff->end())
	{
		MfxBase* tObject = nullptr;
		set->Clone(&tObject);
		tFind->second.push(MfxGulid_Keyframe(tObject, delay));
	}
	else
	{ 
		myGroupType_Keyframe->insert(MfxGulid_GroupType_Keyframe_Queue_Map_Pair(groupName, MfxGulid_GroupType_Keyframe_Queue()));
		myGroupType_Keyframe_Buff->insert(MfxGulid_GroupType_Keyframe_Queue_Map_Pair(groupName, MfxGulid_GroupType_Keyframe_Queue()));
		goto Begin;
	}

	return MFX_RET_SECCESS;
}
