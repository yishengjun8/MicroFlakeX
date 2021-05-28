#pragma once


/**************************************************************
*	UTF-8 - win - x86
*
*   版本：1.01       作者：yishengjun8
*
*
*	MfxType.h	提供了	MicroFlakeX	的基础类型对象
* 
*   MfxType内的类，都重载了拷贝构造函数，力图要求拷贝时速度最快
*       基于此，MfxType内的类可以在程序中当成基本类型使用，因为
*       它们的拷贝开销实在是很小。
* 
**************************************************************/

#ifdef MFXDLL_BUILDING
#define MFX_PORT __declspec(dllexport)
#else
#define MFX_PORT __declspec(dllimport)
#pragma comment(lib, "MfxType.lib")
#include "MfxBase.h"

/* 数学库 */
#include <cmath>
/**/

/* STL模板库 */
/**/

/* Direct2D1 */
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <dwmapi.h>
/**/

/* time库 */
#include <ctime>
/**/

#include "Gdiplus.h"
#pragma comment(lib, "Gdiplus.lib")

#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "DWrite.lib")
#endif

namespace MicroFlakeX
{
    /**************************************************************
    *
    *
    *
    ***************************************************************/
    class MFX_PORT MfxRect;
    class MFX_PORT MfxSize;
    class MFX_PORT MfxPoint;

    class MFX_PORT MfxColor;

    class MFX_PORT MfxGlide;



    /***************************************************************
    *	MfxType	常用容器
    ****************************************************************/
    typedef std::set<MfxRect> MfxRect_Set;
    typedef std::queue<MfxRect> MfxRect_Queue;
    typedef std::deque<MfxRect> MfxRect_Deque;
    typedef std::stack<MfxRect> MfxRect_Stack;
    typedef std::vector<MfxRect> MfxRect_Vector;

    typedef std::set<MfxSize> MfxSize_Set;
    typedef std::queue<MfxSize> MfxSize_Queue;
    typedef std::deque<MfxSize> MfxSize_Deque;
    typedef std::stack<MfxSize> MfxSize_Stack;
    typedef std::vector<MfxSize> MfxSize_Vector;

    typedef std::set<MfxPoint> MfxPoint_Set;
    typedef std::queue<MfxPoint> MfxPoint_Queue;
    typedef std::deque<MfxPoint> MfxPoint_Deque;
    typedef std::stack<MfxPoint> MfxPoint_Stack;
    typedef std::vector<MfxPoint> MfxPoint_Vector;

    typedef std::set<MfxColor> MfxColor_Set;
    typedef std::queue<MfxColor> MfxColor_Queue;
    typedef std::deque<MfxColor> MfxColor_Deque;
    typedef std::stack<MfxColor> MfxColor_Stack;
    typedef std::vector<MfxColor> MfxColor_Vector;

}

namespace MicroFlakeX
{
    class MfxRect :
        public MfxBase
    {
        MfxObject;
    public:
        MfxRect();
        MfxRect(MfxBase& set);

        MfxRect(const MfxRect* set);
        MfxRect(const MfxRect& set) :MfxRect(&set) {};
        MfxRect(const MfxRect&& set) noexcept :MfxRect(&set) {};

        MfxRect(const MfxSize* set);
        MfxRect(const MfxSize& set) :MfxRect(&set) {};
        MfxRect(const MfxSize&& set) :MfxRect(&set) {};

        MfxRect(const MfxPoint* set);
        MfxRect(const MfxPoint& set) :MfxRect(&set) {};
        MfxRect(const MfxPoint&& set) :MfxRect(&set) {};

        MfxRect(const MfxPoint* set1, const MfxPoint* set2);

        MfxRect(const MfxPoint& set1, const MfxPoint* set2) :MfxRect(&set1, set2) {};
        MfxRect(const MfxPoint&& set1, const MfxPoint* set2) :MfxRect(&set1, set2) {};

        MfxRect(const MfxPoint& set1, const  MfxPoint& set2) :MfxRect(&set1, &set2) {};
        MfxRect(const MfxPoint&& set1, const MfxPoint& set2) :MfxRect(&set1, &set2) {};

        MfxRect(const MfxPoint& set1, const MfxPoint&& set2) :MfxRect(&set1, &set2) {};
        MfxRect(const MfxPoint&& set1, const MfxPoint&& set2) :MfxRect(&set1, &set2) {};

        MfxRect(const LONG setX, const LONG setY, const LONG setWidth, const  LONG setHeight);

        ~MfxRect();

    public:
        MfxReturn Clone(MfxBase** ret);

        MfxBase& operator=(MfxBase& rhs);

        MfxRect& operator=(const MfxRect* rhs);
        MfxRect& operator=(const MfxRect& rhs);
        MfxRect& operator=(const MfxRect&& rhs);

        MfxRect& operator=(const MfxSize* rhs);
        MfxRect& operator=(const MfxSize& rhs);
        MfxRect& operator=(const MfxSize&& rhs);

        MfxRect& operator=(const MfxPoint* rhs);
        MfxRect& operator=(const MfxPoint& rhs);
        MfxRect& operator=(const MfxPoint&& rhs);

    public:
        bool operator==(MfxBase& rhs);

        bool operator==(const MfxRect* rhs)const;
        bool operator==(const MfxRect& rhs)const;
        bool operator==(const MfxRect&& rhs)const;

    public:
        operator D2D1_RECT_L()const;
        operator D2D1_RECT_U()const;
        operator D2D1_RECT_F()const;

        operator D2D1_SIZE_U()const;
        operator D2D1_SIZE_F()const;

        operator D2D1_POINT_2L()const;
        operator D2D1_POINT_2U()const;
        operator D2D1_POINT_2F()const;

        operator Gdiplus::Rect()const;
        operator Gdiplus::RectF()const;

        operator Gdiplus::Size()const;
        operator Gdiplus::SizeF()const;

        operator Gdiplus::Point()const;
        operator Gdiplus::PointF()const;

    public:
        MfxReturn Reset(const LONG setX, const LONG setY, const LONG setWidth, const LONG setHeight);
    
    public:
        MfxReturn GetRect(MfxRect* ret)const;
        MfxReturn GetSize(MfxSize* ret)const;
        MfxReturn GetPoint(MfxPoint* ret)const;

        MfxReturn GetRECT(RECT* ret)const;
        MfxReturn GetSIZE(SIZE* ret)const;
        MfxReturn GetPOINT(POINT* ret)const;
      
        MfxReturn GetGdipRect(Gdiplus::Rect* ret)const;
        MfxReturn GetGdipRectF(Gdiplus::RectF* ret)const;

        MfxReturn GetGdipSize(Gdiplus::Size* ret)const;
        MfxReturn GetGdipSizeF(Gdiplus::SizeF* ret)const;

        MfxReturn GetGdipPoint(Gdiplus::Point* ret)const;
        MfxReturn GetGdipPointF(Gdiplus::PointF* ret)const;

    public:
        MfxReturn GetD2D1RectL(D2D1_RECT_L* ret)const;
        MfxReturn GetD2D1RectU(D2D1_RECT_U* ret)const;
        MfxReturn GetD2D1RectF(D2D1_RECT_F* ret)const;

        MfxReturn GetD2D1SizeU(D2D1_SIZE_U* ret)const;
        MfxReturn GetD2D1SizeF(D2D1_SIZE_F* ret)const;

        MfxReturn GetD2D1Point2L(D2D1_POINT_2L* ret)const;
        MfxReturn GetD2D1Point2U(D2D1_POINT_2U* ret)const;
        MfxReturn GetD2D1Point2F(D2D1_POINT_2F* ret)const;

    public:
        MfxReturn SetRect(const MfxRect* set);
        MfxReturn SetSize(const MfxSize* set);
        MfxReturn SetPoint(const MfxPoint* set);

        MfxReturn SetRECT(const RECT* set);
        MfxReturn SetSIZE(const SIZE* set);
        MfxReturn SetPOINT(const POINT* set);

        MfxReturn SetGdipRect(const Gdiplus::Rect* set);
        MfxReturn SetGdipRectF(const Gdiplus::RectF* set);

        MfxReturn SetGdipSize(const Gdiplus::Size* set);
        MfxReturn SetGdipSizeF(const Gdiplus::SizeF* set);

        MfxReturn SetGdipPoint(const Gdiplus::Point* set);
        MfxReturn SetGdipPointF(const Gdiplus::PointF* set);

        MfxReturn SetD2D1RectL(const D2D1_RECT_L* set);
        MfxReturn SetD2D1RectU(const D2D1_RECT_U* set);
        MfxReturn SetD2D1RectF(const D2D1_RECT_F* set);

        MfxReturn SetD2D1SizeU(const D2D1_SIZE_U* set);
        MfxReturn SetD2D1SizeF(const D2D1_SIZE_F* set);

        MfxReturn SetD2D1Point2L(const D2D1_POINT_2L* set);
        MfxReturn SetD2D1Point2U(const D2D1_POINT_2U* set);
        MfxReturn SetD2D1Point2F(const D2D1_POINT_2F* set);

    public:
        MfxReturn GetX(LONG* ret)const;
        MfxReturn GetY(LONG* ret)const;
        MfxReturn GetWidth(LONG* ret)const;
        MfxReturn GetHeight(LONG* ret)const;

        MfxReturn GetTop(LONG* ret)const;
        MfxReturn GetLeft(LONG* ret)const;
        MfxReturn GetRight(LONG* ret)const;
        MfxReturn GetBottom(LONG* ret)const;

        MfxReturn GetCenter(MfxPoint* ret)const;
        MfxReturn GetPointPosition(MfxPoint* ret1, MfxPoint* ret2)const;
    public:
        MfxReturn SetX(const LONG set);
        MfxReturn SetY(const LONG set);
        MfxReturn SetWidth(const LONG set);
        MfxReturn SetHeight(const LONG set);

        MfxReturn SetTop(const LONG set);
        MfxReturn SetLeft(const LONG set);
        MfxReturn SetRight(const LONG set);
        MfxReturn SetBottom(const LONG set);

        MfxReturn SetCenter(const MfxPoint* set);
        MfxReturn SetPointPosition(const MfxPoint* set1, const MfxPoint* set2);

    public:
        /* 和 */
        MfxReturn Union(const MfxRect* set, MfxRect* ret);
        MfxReturn Union_Widely(MfxBase* set, MfxRect* ret);

        /* 交 */
        MfxReturn Intersect(const MfxRect* set, MfxRect* ret);
        MfxReturn Intersect_Widely(MfxBase* set, MfxRect* ret);

    public:
        /* 偏移 */
        MfxReturn Offset(const LONG setX, const LONG setY);

        /* 膨胀 */
        MfxReturn Inflate(const LONG setX, const  LONG setY);

    public:
        /* 判断是否为空 */
        MfxReturn IsEmpty(bool* ret);

        /* 判断矩形是否在矩形内 */
        MfxReturn IsRectInside(const MfxRect* set, bool* ret);

        /* 判断点是否在矩形内 */
        MfxReturn IsPointInside(const MfxPoint* set, bool* ret);

    public:
        LONG myX;
        LONG myY;
        LONG myWidth;
        LONG myHeight;
    };
}

namespace MicroFlakeX
{
    class MfxSize
        : public MfxBase
    {
        MfxObject;
    public:
        MfxSize();
        MfxSize(MfxBase& set);

        MfxSize(const MfxRect* set);
        MfxSize(const MfxRect& set) :MfxSize(&set) {};
        MfxSize(const MfxRect&& set) :MfxSize(&set) {};

        MfxSize(const MfxSize* set);
        MfxSize(const MfxSize& set) :MfxSize(&set) {};
        MfxSize(const MfxSize&& set) noexcept :MfxSize(&set) {};

        MfxSize(const LONG setWidth, const LONG setHeight);

        ~MfxSize();

    public:
        MfxReturn Clone(MfxBase** ret) const;

        MfxBase& operator=(MfxBase& rhs);

        MfxSize& operator=(const MfxRect* rhs);
        MfxSize& operator=(const MfxRect& rhs);
        MfxSize& operator=(const MfxRect&& rhs);

        MfxSize& operator=(const MfxSize* rhs);
        MfxSize& operator=(const MfxSize& rhs);
        MfxSize& operator=(const MfxSize&& rhs);

    public:
        bool operator==(MfxBase& rhs);

        bool operator==(const MfxSize* rhs) const;
        bool operator==(const MfxSize& rhs)const;
        bool operator==(const MfxSize&& rhs)const;

    public:
        operator D2D1_SIZE_U()const;
        operator D2D1_SIZE_F()const;

        operator Gdiplus::Size()const;
        operator Gdiplus::SizeF()const;

    public:
        MfxReturn Reset(const LONG setWidth, const LONG setHeight);

    public:
        MfxReturn GetSize(MfxSize* ret) const;

        MfxReturn GetSIZE(SIZE* ret) const;

        MfxReturn GetGdipSize(Gdiplus::Size* ret) const;
        MfxReturn GetGdipSizeF(Gdiplus::SizeF* ret) const;

        MfxReturn GetD2D1SizeU(D2D1_SIZE_U* ret) const;
        MfxReturn GetD2D1SizeF(D2D1_SIZE_F* ret) const;

    public:
        MfxReturn SetSize(const MfxSize* set);

        MfxReturn SetSIZE(const SIZE* set);

        MfxReturn SetGdipSize(const Gdiplus::Size* set);
        MfxReturn SetGdipSizeF(const Gdiplus::SizeF* set);

        MfxReturn SetD2D1SizeU(const D2D1_SIZE_U* set);
        MfxReturn SetD2D1SizeF(const D2D1_SIZE_F* set);

    public:
        MfxReturn GetWidth(LONG* ret) const;
        MfxReturn GetHeight(LONG* ret) const;

    public:
        MfxReturn SetWidth(const LONG set);
        MfxReturn SetHeight(const LONG set);


    public:
        /* 膨胀 */
        MfxReturn Inflate(const LONG setX, const LONG setY);

    public:
        /* 判断是否为空 */
        MfxReturn IsEmpty(bool* ret);

    public:
        LONG myWidth;
        LONG myHeight;
    };
}


namespace MicroFlakeX
{
    class MfxPoint
        : public MfxBase
    {
        MfxObject;
    public:
        MfxPoint();
        MfxPoint(MfxBase& set);

        MfxPoint(const MfxRect* set);
        MfxPoint(const MfxRect& set) :MfxPoint(&set) {};
        MfxPoint(const MfxRect&& set) :MfxPoint(&set) {};

        MfxPoint(const MfxPoint* set);
        MfxPoint(const MfxPoint& set) :MfxPoint(&set) {};
        MfxPoint(const MfxPoint&& set) noexcept :MfxPoint(&set) {};

        MfxPoint(const LONG setX, const  LONG setY);

        ~MfxPoint();

    public:
        MfxReturn Clone(MfxBase** ret)const;

        MfxBase& operator=(MfxBase& rhs);

        MfxPoint& operator=(const MfxRect* rhs);
        MfxPoint& operator=(const MfxRect& rhs);
        MfxPoint& operator=(const MfxRect&& rhs);

        MfxPoint& operator=(const MfxPoint* rhs);
        MfxPoint& operator=(const MfxPoint& rhs);
        MfxPoint& operator=(const MfxPoint&& rhs);

    public:
        bool operator==(MfxBase& rhs);

        bool operator==(const MfxPoint* rhs)const;
        bool operator==(const MfxPoint& rhs)const;
        bool operator==(const MfxPoint&& rhs)const;

    public:
        operator D2D1_POINT_2L()const;
        operator D2D1_POINT_2U()const;
        operator D2D1_POINT_2F()const;

        operator Gdiplus::Point()const;
        operator Gdiplus::PointF()const;

    public:
        MfxReturn Reset(const LONG setX, const LONG setY);

    public:
        MfxReturn GetPoint(MfxPoint* ret)const;

        MfxReturn GetPOINT(POINT* ret)const;

        MfxReturn GetGdipPoint(Gdiplus::Point* ret)const;
        MfxReturn GetGdipPointF(Gdiplus::PointF* ret)const;

        MfxReturn GetD2D1Point2L(D2D1_POINT_2L* ret)const;
        MfxReturn GetD2D1Point2U(D2D1_POINT_2U* ret)const;
        MfxReturn GetD2D1Point2F(D2D1_POINT_2F* ret)const;

    public:
        MfxReturn SetPoint(const MfxPoint* set);

        MfxReturn SetPOINT(const POINT* set);

        MfxReturn SetGdipPoint(const Gdiplus::Point* set);
        MfxReturn SetGdipPointF(const Gdiplus::PointF* set);

        MfxReturn SetD2D1Point2L(const D2D1_POINT_2U* set);
        MfxReturn SetD2D1Point2U(const D2D1_POINT_2U* set);
        MfxReturn SetD2D1Point2F(const D2D1_POINT_2F* set);

    public:
        MfxReturn GetX(LONG* ret)const;
        MfxReturn GetY(LONG* ret)const;

    public:
        MfxReturn SetX(const LONG set);
        MfxReturn SetY(const LONG set);

    public:
        /* 偏移 */
        MfxReturn Offset(const LONG setX, const LONG setY);
       
    public:
        LONG myX;
        LONG myY;
    };
}

namespace MicroFlakeX
{
    class MfxColor
        : public MfxBase
    {
        MfxObject;
    public:
        MfxColor();
        MfxColor(MfxBase& set);

        MfxColor(const MfxColor* set);
        MfxColor(const MfxColor& set) :MfxColor(&set) {};
        MfxColor(const MfxColor&& set)noexcept :MfxColor(&set) {};

        MfxColor(const LONG setA, const LONG setR, const LONG setG, const LONG setB);

        ~MfxColor();

    public:
        MfxReturn Clone(MfxBase** ret)const;

        MfxBase& operator=(MfxBase& rhs);

        MfxColor& operator=(const MfxColor* rhs);
        MfxColor& operator=(const MfxColor& rhs);
        MfxColor& operator=(const MfxColor&& rhs);

    public:
        bool operator==(MfxBase& rhs);

        bool operator==(const MfxColor* rhs)const;
        bool operator==(const MfxColor& rhs)const;
        bool operator==(const MfxColor&& rhs)const;

    public:
        operator COLORREF()const;
        operator D2D1_COLOR_F()const;
        operator Gdiplus::Color()const;

    public:
        MfxReturn Reset(const LONG setA, const LONG setR, const LONG setG, const LONG setB);

    public:
        MfxReturn GetColor(MfxColor* ret)const;
        MfxReturn GetGdipColor(Gdiplus::Color* ret)const;

        MfxReturn GetPRGB(UINT32* ret)const;
        MfxReturn GetRGB(LONG* retA, COLORREF* ret)const;

        MfxReturn GetD2D1ColorF(D2D1_COLOR_F* ret)const;

    public:
        MfxReturn SetColor(const MfxColor* set);
        MfxReturn SetGdipColor(const Gdiplus::Color* set);

        MfxReturn SetPRGB(const UINT32 set);
        MfxReturn SetRGB(const LONG setA, const UINT32 set);

        MfxReturn SetD2D1ColorF(const D2D1_COLOR_F* set);

    public:
        MfxReturn GetA(LONG* ret)const;
        MfxReturn GetR(LONG* ret)const;
        MfxReturn GetG(LONG* ret)const;
        MfxReturn GetB(LONG* ret)const;

    public:
        MfxReturn SetA(const LONG set);
        MfxReturn SetR(const LONG set);
        MfxReturn SetG(const LONG set);
        MfxReturn SetB(const LONG set);


    public:
        LONG myA;
        LONG myR;
        LONG myG;
        LONG myB;
    };
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
        自动调用 MfxBase::AutoFunc(MfxText("BindObjec"), XXX);
    *   
    *   如果对象未注册 AutoFunc 的 BindObjec ，则会调用失败。
    *   对象必须可以Clone
    * 
    ***************************************************************/
    class MfxGlide
        : public MfxBase
    {
        MfxObject;
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
        MfxReturn EachFrame(MfxParam myParam);

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
