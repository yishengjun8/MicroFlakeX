#pragma once

namespace MicroFlakeX
{
    class MFX_PORT MfxGlide;

    typedef MfxGlide* pMfxGlide;
}

namespace MicroFlakeX
{
    typedef double(*pEaseGulid)(double);

    struct MfxGulid_Keyframe
    {
        MfxGulid_Keyframe(MfxBase* setKey, LONGLONG sTime)
        {
            key = setKey;
            time = sTime;
        }
        MfxBase* key;
        LONGLONG time;
    };

    struct MfxGulid_GetSet_FuncName
    {
        MfxGulid_GetSet_FuncName(MfxString get, MfxString set, pEaseGulid easeGulid)
        {
            myGetFuncName = get;
            mySetFuncName = set;
            myEaseGulid = easeGulid;
        }
        MfxGulid_GetSet_FuncName(MfxString type, pEaseGulid easeGulid)
        {
            myEaseGulid = easeGulid;
            mySetFuncName = myGetFuncName = type;
        }
        pEaseGulid myEaseGulid;
        MfxString myGetFuncName;
        MfxString mySetFuncName;

    };

    typedef std::vector<MfxGulid_GetSet_FuncName> MfxGulid_GetSet_FuncName_Vector;

    typedef std::queue<MfxGulid_Keyframe> MfxGulid_BindObjectType_Keyframe_Queue;
 
    typedef std::map<MfxString, MfxGulid_BindObjectType_Keyframe_Queue> MfxGulid_BindObjectType_Keyframe_Queue_Map;
    typedef MfxGulid_BindObjectType_Keyframe_Queue_Map::value_type MfxGulid_BindObjectType_Keyframe_Queue_Map_Pair;

    struct MfxGulid_WidelyType
    {
        MfxGulid_WidelyType(MfxString getObjectName, MfxString setObjectName,
            MfxString getObjectFuncName, MfxString setObjectFuncName)
        {
            myGetObject_Set = nullptr;
            myGetObject_Begin = nullptr;
            this->getObjectName = getObjectName;
            this->setObjectName = setObjectName;
            this->getObjectFuncName = getObjectFuncName;
            this->setObjectFuncName = setObjectFuncName;
            myBeginTime = 0;
            myThroughTime = 0;
        }
        MfxGulid_WidelyType()
        {
            myGetObject_Set = nullptr;
            myGetObject_Begin = nullptr;
            myBeginTime = 0;
            myThroughTime = 0;
        }
        MfxString getObjectName;
        MfxString setObjectName;
        MfxString getObjectFuncName;
        MfxString setObjectFuncName;

        LONGLONG myBeginTime;
        LONGLONG myThroughTime;
        MfxBase* myGetObject_Set;
        MfxBase* myGetObject_Begin;
        MfxGulid_GetSet_FuncName_Vector myGulidTypePair;

    };

    typedef std::map<MfxString, MfxGulid_WidelyType> MfxGulid_WidelyType_Map;
    typedef MfxGulid_WidelyType_Map::value_type MfxGulid_WidelyType_Map_Pair;

    /**************************************************************
    ***************************************************************/
    MFX_PORT double MfxEaseInSine(double x);
    MFX_PORT double MfxEaseOutSine(double x);
    MFX_PORT double MfxEaseInOutSine(double x);

    MFX_PORT double MfxEaseInQuad(double x);
    MFX_PORT double MfxEaseOutQuad(double x);
    MFX_PORT double MfxEaseInOutQuad(double x);

    MFX_PORT double MfxEaseInCubic(double x);
    MFX_PORT double MfxEaseOutCubic(double x);
    MFX_PORT double MfxEaseInOutCubic(double x);

    MFX_PORT double MfxEaseInQuart(double x);
    MFX_PORT double MfxEaseOutQuart(double x);
    MFX_PORT double MfxEaseInOutQuart(double x);

    MFX_PORT double MfxEaseInQuint(double x);
    MFX_PORT double MfxEaseOutQuint(double x);
    MFX_PORT double MfxEaseInOutQuint(double x);

    MFX_PORT double MfxEaseInExpo(double x);
    MFX_PORT double MfxEaseOutExpo(double x);
    MFX_PORT double MfxEaseInOutExpo(double x);

    MFX_PORT double MfxEaseInCirc(double x);
    MFX_PORT double MfxEaseOutCirc(double x);
    MFX_PORT double MfxEaseInOutCirc(double x);

    MFX_PORT double MfxEaseInBack(double x);
    MFX_PORT double MfxEaseOutBack(double x);
    MFX_PORT double MfxEaseInOutBack(double x);

    MFX_PORT double MfxEaseInElastic(double x);
    MFX_PORT double MfxEaseOutElastic(double x);
    MFX_PORT double MfxEaseInOutElastic(double x);

    MFX_PORT double MfxEaseInBounce(double x);
    MFX_PORT double MfxEaseOutBounce(double x);
    MFX_PORT double MfxEaseInOutBounce(double x);

    /**************************************************************
    *   MfxGlide 赖于 MfxBase 的 AutoFunc。
    *
    *   MfxGlide 允许绑定一个 MfxBase 对象，每帧根据给定参数
        自动调用 MfxBase::Reflection(MfxText("BindObjec"), XXX);
    *
    *   如果对象未注册 Reflection 的 BindObjec ，则会调用失败。
    *   对象必须可以Clone
    *
    ***************************************************************/
    class MfxGlide :
        public MfxBase
    {
        MFXOBJ_ENABLE_REFLECTION;
    public:
        MfxGlide();

        MfxGlide(const MfxGlide* set);
        MfxGlide(const MfxGlide& set) :MfxGlide(&set) {};
        MfxGlide(const MfxGlide&& set) noexcept :MfxGlide(&set) {};

        ~MfxGlide();

        MfxReturn Clone(MfxBase** ret)const;

        MfxBase& operator=(MfxBase& rhs);

        MfxGlide& operator=(const MfxGlide* rhs);
        MfxGlide& operator=(const MfxGlide& rhs);
        MfxGlide& operator=(const MfxGlide&& rhs);

        bool operator==(MfxBase& rhs);

        bool operator==(const MfxGlide* rhs)const;
        bool operator==(const MfxGlide& rhs)const;
        bool operator==(const MfxGlide&& rhs)const;

    public:
        MfxReturn SetFPS(const UINT set);

        MfxReturn BindObject(MfxBase* object);
        MfxReturn BindObjectName(MfxString groupName, MfxGulid_WidelyType value);
        MfxReturn Add_GetSetFuncName(MfxString groupName, MfxString getFuncName, MfxString setFuncName, pEaseGulid easeGulid = MfxEaseInOutQuad);

    public:
        MfxReturn GetFPS(UINT* ret);
        MfxReturn GetBindObject(MfxBase** object);

    public:
        MfxReturn Stop();
        MfxReturn Begin();
        MfxReturn Pause();
        MfxReturn Clear();

    public:
        MfxReturn EachFrame(MfxParam param);

    public:
        MfxReturn MfxAddKeyframe(MfxString groupName, MfxBase* set, LONGLONG delay);

    private:
        UINT myFPS;
        bool myBegin;
        PTP_TIMER myPTP_TIMER;

    private:
        MfxBase* myBindObject;
        MfxGulid_WidelyType_Map myWidelyTypeMap;

    private:
        MfxGulid_BindObjectType_Keyframe_Queue_Map myBindObjectType_Keyframe;

    };
}


namespace MicroFlakeX
{
    class MFX_PORT MfxTransitions;
    class MFX_PORT MfxTransitionsEx;
}

namespace MicroFlakeX
{
    class MfxTransitions :
        public MfxBase
    {
        MFXOBJ_ENABLE_REFLECTION;
    public:
        MfxTransitions();

    };

}

