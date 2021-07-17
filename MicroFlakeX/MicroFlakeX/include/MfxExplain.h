#pragma once

namespace MicroFlakeX
{
    class MFX_DLL_EXPORT MfxGlide;

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
        MfxGulid_GetSet_FuncName(MfxStringW get, MfxStringW set, pEaseGulid easeGulid)
        {
            myGetFuncName = get;
            mySetFuncName = set;
            myEaseGulid = easeGulid;
        }
        MfxGulid_GetSet_FuncName(MfxStringW type, pEaseGulid easeGulid)
        {
            myEaseGulid = easeGulid;
            mySetFuncName = myGetFuncName = type;
        }
        pEaseGulid myEaseGulid;
        MfxStringW myGetFuncName;
        MfxStringW mySetFuncName;

    };

    typedef std::vector<MfxGulid_GetSet_FuncName> MfxGulid_GetSet_FuncName_Vector;

    typedef std::queue<MfxGulid_Keyframe> MfxGulid_BindObjectType_Keyframe_Queue;
 
    typedef std::map<MfxStringW, MfxGulid_BindObjectType_Keyframe_Queue> MfxGulid_BindObjectType_Keyframe_Queue_Map;
    typedef MfxGulid_BindObjectType_Keyframe_Queue_Map::value_type MfxGulid_BindObjectType_Keyframe_Queue_Map_Pair;

    struct MfxGulid_WidelyType
    {
        MfxGulid_WidelyType(MfxStringW getObjectName, MfxStringW setObjectName,
            MfxStringW getObjectFuncName, MfxStringW setObjectFuncName)
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
        MfxStringW getObjectName;
        MfxStringW setObjectName;
        MfxStringW getObjectFuncName;
        MfxStringW setObjectFuncName;

        LONGLONG myBeginTime;
        LONGLONG myThroughTime;
        MfxBase* myGetObject_Set;
        MfxBase* myGetObject_Begin;
        MfxGulid_GetSet_FuncName_Vector myGulidTypePair;

    };

    typedef std::map<MfxStringW, MfxGulid_WidelyType> MfxGulid_WidelyType_Map;
    typedef MfxGulid_WidelyType_Map::value_type MfxGulid_WidelyType_Map_Pair;

    /**************************************************************
    ***************************************************************/
    MFX_DLL_EXPORT double MfxEaseInSine(double x);
    MFX_DLL_EXPORT double MfxEaseOutSine(double x);
    MFX_DLL_EXPORT double MfxEaseInOutSine(double x);

    MFX_DLL_EXPORT double MfxEaseInQuad(double x);
    MFX_DLL_EXPORT double MfxEaseOutQuad(double x);
    MFX_DLL_EXPORT double MfxEaseInOutQuad(double x);

    MFX_DLL_EXPORT double MfxEaseInCubic(double x);
    MFX_DLL_EXPORT double MfxEaseOutCubic(double x);
    MFX_DLL_EXPORT double MfxEaseInOutCubic(double x);

    MFX_DLL_EXPORT double MfxEaseInQuart(double x);
    MFX_DLL_EXPORT double MfxEaseOutQuart(double x);
    MFX_DLL_EXPORT double MfxEaseInOutQuart(double x);

    MFX_DLL_EXPORT double MfxEaseInQuint(double x);
    MFX_DLL_EXPORT double MfxEaseOutQuint(double x);
    MFX_DLL_EXPORT double MfxEaseInOutQuint(double x);

    MFX_DLL_EXPORT double MfxEaseInExpo(double x);
    MFX_DLL_EXPORT double MfxEaseOutExpo(double x);
    MFX_DLL_EXPORT double MfxEaseInOutExpo(double x);

    MFX_DLL_EXPORT double MfxEaseInCirc(double x);
    MFX_DLL_EXPORT double MfxEaseOutCirc(double x);
    MFX_DLL_EXPORT double MfxEaseInOutCirc(double x);

    MFX_DLL_EXPORT double MfxEaseInBack(double x);
    MFX_DLL_EXPORT double MfxEaseOutBack(double x);
    MFX_DLL_EXPORT double MfxEaseInOutBack(double x);

    MFX_DLL_EXPORT double MfxEaseInElastic(double x);
    MFX_DLL_EXPORT double MfxEaseOutElastic(double x);
    MFX_DLL_EXPORT double MfxEaseInOutElastic(double x);

    MFX_DLL_EXPORT double MfxEaseInBounce(double x);
    MFX_DLL_EXPORT double MfxEaseOutBounce(double x);
    MFX_DLL_EXPORT double MfxEaseInOutBounce(double x);

    /**************************************************************
    *   MfxGlide 赖于 MfxBase 的 AutoFunc。
    *
    *   MfxGlide 允许绑定一个 MfxBase 对象，每帧根据给定参数
        自动调用 MfxBase::Reflection(MFX_TXT_W("BindObjec"), XXX);
    *
    *   如果对象未注册 Reflection 的 BindObjec ，则会调用失败。
    *   对象必须可以Clone
    *
    ***************************************************************/
    class MfxGlide :
        public MfxBase
    {
        MFX_OBJ_ENABLE_REFLECTION;
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
        MfxReturn BindObjectName(MfxStringW groupName, MfxGulid_WidelyType value);
        MfxReturn Add_GetSetFuncName(MfxStringW groupName, MfxStringW getFuncName, MfxStringW setFuncName, pEaseGulid easeGulid = MfxEaseInOutQuad);

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
        MfxReturn MfxAddKeyframe(MfxStringW groupName, MfxBase* set, LONGLONG delay);

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
    class MFX_DLL_EXPORT MfxTransitions;
    class MFX_DLL_EXPORT MfxTransitionsEx;
}

namespace MicroFlakeX
{
    class MfxTransitions :
        public MfxBase
    {
        MFX_OBJ_ENABLE_REFLECTION;
    public:
        MfxTransitions();

    };

}

