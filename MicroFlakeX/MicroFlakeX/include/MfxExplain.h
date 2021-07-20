#pragma once

namespace MicroFlakeX
{
    class MFX_DLL_EXPORT __MfxGlide;

    typedef __MfxGlide* pMfxGlide;


    //针对每个类型做优化
    /*
    *   组合模式
    *   __MfxGlide+MfxStringW
    * 
    * 
    *   1、MfxRect   __MfxGlide_Rect;
    *   2、MfxSize   __MfxGlide_Size;
    *   3、MfxPoint  __MfxGlide_Point;
    *   4、MfxColor  __MfxGlide_Color;
    * 
    *   5、int       __MfxGlide_Int;
    *   6、double    __MfxGlide_Double;
    */
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

    typedef std::queue<MfxGulid_Keyframe> MfxGulid_GroupType_Keyframe_Queue;
 
    typedef std::map<MfxStringW, MfxGulid_GroupType_Keyframe_Queue> MfxGulid_GroupType_Keyframe_Queue_Map;
    typedef MfxGulid_GroupType_Keyframe_Queue_Map::value_type MfxGulid_GroupType_Keyframe_Queue_Map_Pair;

    struct MfxGulid_GroupDetails
    {
        MfxGulid_GroupDetails(MfxStringW getObjectName, MfxStringW setObjectName,
            MfxStringW getObjectFuncName, MfxStringW setObjectFuncName)
        {
            this->myGetObject_Set = nullptr;
            this->myGetObject_Begin = nullptr;
            this->getObjectName = getObjectName;
            this->setObjectName = setObjectName;
            this->getObjectFuncName = getObjectFuncName;
            this->setObjectFuncName = setObjectFuncName;
            this->myBeginTime = 0;
            this->myThroughTime = 0;
        }
        MfxGulid_GroupDetails()
        {
            this->myGetObject_Set = nullptr;
            this->myGetObject_Begin = nullptr;
            this->myBeginTime = 0;
            this->myThroughTime = 0;
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

    typedef std::map<MfxStringW, MfxGulid_GroupDetails> MfxGulid_GroupDetails_Map;
    typedef MfxGulid_GroupDetails_Map::value_type MfxGulid_GroupDetails_Map_Pair;

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
    *   __MfxGlide 赖于 MfxBase 的 AutoFunc。
    *
    *   __MfxGlide 允许绑定一个 MfxBase 对象，每帧根据给定参数
        自动调用 MfxBase::Reflection(MFX_TXT_W("BindObjec"), XXX);
    *
    *   如果对象未注册 Reflection 的 BindObjec ，则会调用失败。
    *   对象必须可以Clone
    *
    ***************************************************************/
    class __MfxGlide :
        public MfxBase
    {
        MFX_OBJ_ENABLE_REFLECTION;
    public:
        __MfxGlide();

        __MfxGlide(const __MfxGlide* set);
        __MfxGlide(const __MfxGlide& set) :__MfxGlide(&set) {};
        __MfxGlide(const __MfxGlide&& set) noexcept :__MfxGlide(&set) {};

        ~__MfxGlide();

        MfxReturn Clone(MfxBase** ret);

        MfxBase& operator=(MfxBase& rhs);

        __MfxGlide& operator=(const __MfxGlide* rhs);
        __MfxGlide& operator=(const __MfxGlide& rhs);
        __MfxGlide& operator=(const __MfxGlide&& rhs) noexcept;

        bool operator==(MfxBase& rhs);

        bool operator==(const __MfxGlide* rhs) const;
        bool operator==(const __MfxGlide& rhs) const;
        bool operator==(const __MfxGlide&& rhs) const;

    public:
        MfxReturn SetFPS(const UINT set);

        MfxReturn BindObject(MfxBase* object);
        MfxReturn BindObjectName(MfxStringW groupName, MfxGulid_GroupDetails value);
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
        MfxReturn IsRun(bool* ret);
    public:
        MfxReturn EachFrame(MfxParam param);

    public:
        MfxReturn AddKeyframe(MfxStringW groupName, MfxBase* set, LONGLONG delay);

    private:
        UINT myFPS;
        bool myBegin;
        PTP_TIMER myPTP_TIMER;

    private:
        MfxBase* myBindObject;
        MfxGulid_GroupDetails_Map myGroupDetails_Map;

    private:
        MfxGulid_GroupType_Keyframe_Queue_Map* myGroupType_Keyframe;
        MfxGulid_GroupType_Keyframe_Queue_Map* myGroupType_Keyframe_Buff;
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

