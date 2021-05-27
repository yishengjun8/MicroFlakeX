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

        MfxRect(MfxRect* set);
        MfxRect(MfxRect& set) :MfxRect(&set) {};
        MfxRect(MfxRect&& set) noexcept :MfxRect(&set) {};

        MfxRect(MfxSize* set);
        MfxRect(MfxSize& set) :MfxRect(&set) {};
        MfxRect(MfxSize&& set) :MfxRect(&set) {};

        MfxRect(MfxPoint* set);
        MfxRect(MfxPoint& set) :MfxRect(&set) {};
        MfxRect(MfxPoint&& set) :MfxRect(&set) {};

        MfxRect(MfxPoint* set1, MfxPoint* set2);

        MfxRect(MfxPoint& set1, MfxPoint* set2) :MfxRect(&set1, set2) {};
        MfxRect(MfxPoint&& set1, MfxPoint* set2) :MfxRect(&set1, set2) {};

        MfxRect(MfxPoint& set1, MfxPoint& set2) :MfxRect(&set1, &set2) {};
        MfxRect(MfxPoint&& set1, MfxPoint& set2) :MfxRect(&set1, &set2) {};

        MfxRect(MfxPoint& set1, MfxPoint&& set2) :MfxRect(&set1, &set2) {};
        MfxRect(MfxPoint&& set1, MfxPoint&& set2) :MfxRect(&set1, &set2) {};

        MfxRect(LONG setX, LONG setY, LONG setWidth, LONG setHeight);

        ~MfxRect();

    public:
        MfxReturn Clone(MfxBase** ret);

        MfxBase& operator=(MfxBase& rhs);

        MfxRect& operator=(MfxRect* rhs);
        MfxRect& operator=(MfxRect& rhs);
        MfxRect& operator=(MfxRect&& rhs);

        MfxRect& operator=(MfxSize* rhs);
        MfxRect& operator=(MfxSize& rhs);
        MfxRect& operator=(MfxSize&& rhs);

        MfxRect& operator=(MfxPoint* rhs);
        MfxRect& operator=(MfxPoint& rhs);
        MfxRect& operator=(MfxPoint&& rhs);

    public:
        bool operator==(MfxBase& rhs);

        bool operator==(MfxRect* rhs);
        bool operator==(MfxRect& rhs);
        bool operator==(MfxRect&& rhs);

    public:

        operator D2D1_RECT_L();
        operator D2D1_RECT_U();
        operator D2D1_RECT_F();

        operator D2D1_SIZE_U();
        operator D2D1_SIZE_F();

        operator D2D1_POINT_2L();
        operator D2D1_POINT_2U();
        operator D2D1_POINT_2F();

        operator Gdiplus::Rect();
        operator Gdiplus::RectF();

        operator Gdiplus::Size();
        operator Gdiplus::SizeF();

        operator Gdiplus::Point();
        operator Gdiplus::PointF();

    public:
        MfxReturn Reset(LONG setX, LONG setY, LONG setWidth, LONG setHeight);
    
    public:
        MfxReturn GetRect(MfxRect* ret);
        MfxReturn GetSize(MfxSize* ret);
        MfxReturn GetPoint(MfxPoint* ret);

        MfxReturn GetRECT(RECT* ret);
        MfxReturn GetSIZE(SIZE* ret);
        MfxReturn GetPOINT(POINT* ret);
      
        MfxReturn GetGdipRect(Gdiplus::Rect* ret);
        MfxReturn GetGdipRectF(Gdiplus::RectF* ret);

        MfxReturn GetGdipSize(Gdiplus::Size* ret);
        MfxReturn GetGdipSizeF(Gdiplus::SizeF* ret);

        MfxReturn GetGdipPoint(Gdiplus::Point* ret);
        MfxReturn GetGdipPointF(Gdiplus::PointF* ret);

    public:
        MfxReturn GetD2D1RectL(D2D1_RECT_L* ret);
        MfxReturn GetD2D1RectU(D2D1_RECT_U* ret);
        MfxReturn GetD2D1RectF(D2D1_RECT_F* ret);

        MfxReturn GetD2D1SizeU(D2D1_SIZE_U* ret);
        MfxReturn GetD2D1SizeF(D2D1_SIZE_F* ret);

        MfxReturn GetD2D1Point2L(D2D1_POINT_2L* ret);
        MfxReturn GetD2D1Point2U(D2D1_POINT_2U* ret);
        MfxReturn GetD2D1Point2F(D2D1_POINT_2F* ret);

    public:
        MfxReturn SetRect(MfxRect* set);
        MfxReturn SetSize(MfxSize* set);
        MfxReturn SetPoint(MfxPoint* set);

        MfxReturn SetRECT(RECT* set);
        MfxReturn SetSIZE(SIZE* set);
        MfxReturn SetPOINT(POINT* set);

        MfxReturn SetGdipRect(Gdiplus::Rect* set);
        MfxReturn SetGdipRectF(Gdiplus::RectF* set);

        MfxReturn SetGdipSize(Gdiplus::Size* set);
        MfxReturn SetGdipSizeF(Gdiplus::SizeF* set);

        MfxReturn SetGdipPoint(Gdiplus::Point* set);
        MfxReturn SetGdipPointF(Gdiplus::PointF* set);

        MfxReturn SetD2D1RectL(D2D1_RECT_L* set);
        MfxReturn SetD2D1RectU(D2D1_RECT_U* set);
        MfxReturn SetD2D1RectF(D2D1_RECT_F* set);

        MfxReturn SetD2D1SizeU(D2D1_SIZE_U* set);
        MfxReturn SetD2D1SizeF(D2D1_SIZE_F* set);

        MfxReturn SetD2D1Point2L(D2D1_POINT_2L* set);
        MfxReturn SetD2D1Point2U(D2D1_POINT_2U* set);
        MfxReturn SetD2D1Point2F(D2D1_POINT_2F* set);

    public:
        MfxReturn GetX(LONG* ret);
        MfxReturn GetY(LONG* ret);
        MfxReturn GetWidth(LONG* ret);
        MfxReturn GetHeight(LONG* ret);

        MfxReturn GetTop(LONG* ret);
        MfxReturn GetLeft(LONG* ret);
        MfxReturn GetRight(LONG* ret);
        MfxReturn GetBottom(LONG* ret);

        MfxReturn GetCenter(MfxPoint* ret);
        MfxReturn GetPointPosition(MfxPoint* ret1, MfxPoint* ret2);
    public:
        MfxReturn SetX(LONG set);
        MfxReturn SetY(LONG set);
        MfxReturn SetWidth(LONG set);
        MfxReturn SetHeight(LONG set);

        MfxReturn SetTop(LONG set);
        MfxReturn SetLeft(LONG set);
        MfxReturn SetRight(LONG set);
        MfxReturn SetBottom(LONG set);

        MfxReturn SetCenter(MfxPoint* set);
        MfxReturn SetPointPosition(MfxPoint* set1, MfxPoint* set2);

    public:
        /* 和 */
        MfxReturn Union(MfxRect* set, MfxRect* ret);
        MfxReturn Union_Widely(MfxBase* set, MfxRect* ret);

        /* 交 */
        MfxReturn Intersect(MfxRect* set, MfxRect* ret);
        MfxReturn Intersect_Widely(MfxBase* set, MfxRect* ret);

    public:
        /* 偏移 */
        MfxReturn Offset(LONG setX, LONG setY);

        /* 膨胀 */
        MfxReturn Inflate(LONG setX, LONG setY);

    public:
        /* 判断是否为空 */
        MfxReturn IsEmpty(bool* ret);

        /* 判断矩形是否在矩形内 */
        MfxReturn IsRectInside(MfxRect* set, bool* ret);

        /* 判断点是否在矩形内 */
        MfxReturn IsPointInside(MfxPoint* set, bool* ret);

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

        MfxSize(MfxRect* set);
        MfxSize(MfxRect& set) :MfxSize(&set) {};
        MfxSize(MfxRect&& set) :MfxSize(&set) {};

        MfxSize(MfxSize* set);
        MfxSize(MfxSize& set) :MfxSize(&set) {};
        MfxSize(MfxSize&& set) noexcept :MfxSize(&set) {};

        MfxSize(LONG setWidth, LONG setHeight);

        ~MfxSize();

    public:
        MfxReturn Clone(MfxBase** ret);

        MfxBase& operator=(MfxBase& rhs);

        MfxSize& operator=(MfxRect* rhs);
        MfxSize& operator=(MfxRect& rhs);
        MfxSize& operator=(MfxRect&& rhs);

        MfxSize& operator=(MfxSize* rhs);
        MfxSize& operator=(MfxSize& rhs);
        MfxSize& operator=(MfxSize&& rhs);

    public:
        bool operator==(MfxBase& rhs);

        bool operator==(MfxSize* rhs);
        bool operator==(MfxSize& rhs);
        bool operator==(MfxSize&& rhs);

    public:
        operator D2D1_SIZE_U();
        operator D2D1_SIZE_F();

        operator Gdiplus::Size();
        operator Gdiplus::SizeF();

    public:
        MfxReturn Reset(LONG setWidth, LONG setHeight);

    public:
        MfxReturn GetSize(MfxSize* ret);

        MfxReturn GetSIZE(SIZE* ret);;

        MfxReturn GetGdipSize(Gdiplus::Size* ret);
        MfxReturn GetGdipSizeF(Gdiplus::SizeF* ret);

        MfxReturn GetD2D1SizeU(D2D1_SIZE_U* ret);
        MfxReturn GetD2D1SizeF(D2D1_SIZE_F* ret);

    public:
        MfxReturn SetSize(MfxSize* set);

        MfxReturn SetSIZE(SIZE* set);

        MfxReturn SetGdipSize(Gdiplus::Size* set);
        MfxReturn SetGdipSizeF(Gdiplus::SizeF* set);

        MfxReturn SetD2D1SizeU(D2D1_SIZE_U* set);
        MfxReturn SetD2D1SizeF(D2D1_SIZE_F* set);

    public:
        MfxReturn GetWidth(LONG* ret);
        MfxReturn GetHeight(LONG* ret);

    public:
        MfxReturn SetWidth(LONG set);
        MfxReturn SetHeight(LONG set);


    public:
        /* 膨胀 */
        MfxReturn Inflate(LONG setX, LONG setY);

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

        MfxPoint(MfxRect* set);
        MfxPoint(MfxRect& set) :MfxPoint(&set) {};
        MfxPoint(MfxRect&& set) :MfxPoint(&set) {};

        MfxPoint(MfxPoint* set);
        MfxPoint(MfxPoint& set) :MfxPoint(&set) {};
        MfxPoint(MfxPoint&& set) noexcept :MfxPoint(&set) {};

        MfxPoint(LONG setX, LONG setY);

        ~MfxPoint();

    public:
        MfxReturn Clone(MfxBase** ret);

        MfxBase& operator=(MfxBase& rhs);

        MfxPoint& operator=(MfxRect* rhs);
        MfxPoint& operator=(MfxRect& rhs);
        MfxPoint& operator=(MfxRect&& rhs);

        MfxPoint& operator=(MfxPoint* rhs);
        MfxPoint& operator=(MfxPoint& rhs);
        MfxPoint& operator=(MfxPoint&& rhs);

    public:
        bool operator==(MfxBase& rhs);

        bool operator==(MfxPoint* rhs);
        bool operator==(MfxPoint& rhs);
        bool operator==(MfxPoint&& rhs);

    public:
        operator D2D1_POINT_2L();
        operator D2D1_POINT_2U();
        operator D2D1_POINT_2F();

        operator Gdiplus::Point();
        operator Gdiplus::PointF();

    public:
        MfxReturn Reset(LONG setX, LONG setY);

    public:
        MfxReturn GetPoint(MfxPoint* ret);

        MfxReturn GetPOINT(POINT* ret);

        MfxReturn GetGdipPoint(Gdiplus::Point* ret);
        MfxReturn GetGdipPointF(Gdiplus::PointF* ret);

        MfxReturn GetD2D1Point2L(D2D1_POINT_2L* ret);
        MfxReturn GetD2D1Point2U(D2D1_POINT_2U* ret);
        MfxReturn GetD2D1Point2F(D2D1_POINT_2F* ret);

    public:
        MfxReturn SetPoint(MfxPoint* set);

        MfxReturn SetPOINT(POINT* set);

        MfxReturn SetGdipPoint(Gdiplus::Point* set);
        MfxReturn SetGdipPointF(Gdiplus::PointF* set);

        MfxReturn SetD2D1Point2L(D2D1_POINT_2U* set);
        MfxReturn SetD2D1Point2U(D2D1_POINT_2U* set);
        MfxReturn SetD2D1Point2F(D2D1_POINT_2F* set);

    public:
        MfxReturn GetX(LONG* ret);
        MfxReturn GetY(LONG* ret);

    public:
        MfxReturn SetX(LONG set);
        MfxReturn SetY(LONG set);

    public:
        /* 偏移 */
        MfxReturn Offset(LONG setX, LONG setY);
       
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

        MfxColor(MfxColor* set);
        MfxColor(MfxColor& set) :MfxColor(&set) {};
        MfxColor(MfxColor&& set)noexcept :MfxColor(&set) {};

        MfxColor(LONG setA, LONG setR, LONG setG, LONG setB);

        ~MfxColor();

    public:
        MfxReturn Clone(MfxBase** ret);

        MfxBase& operator=(MfxBase& rhs);

        MfxColor& operator=(MfxColor* rhs);
        MfxColor& operator=(MfxColor& rhs);
        MfxColor& operator=(MfxColor&& rhs);

    public:
        bool operator==(MfxBase& rhs);

        bool operator==(MfxColor* rhs);
        bool operator==(MfxColor& rhs);
        bool operator==(MfxColor&& rhs);

    public:
        operator COLORREF();
        operator D2D1_COLOR_F();
        operator Gdiplus::Color();

    public:
        MfxReturn Reset(LONG setA, LONG setR, LONG setG, LONG setB);

    public:
        MfxReturn GetColor(MfxColor* ret);
        MfxReturn GetGdipColor(Gdiplus::Color* ret);

        MfxReturn GetPRGB(UINT32* ret);
        MfxReturn GetRGB(LONG* retA, COLORREF* ret);

        MfxReturn GetD2D1ColorF(D2D1_COLOR_F* ret);

    public:
        MfxReturn SetColor(MfxColor* set);
        MfxReturn SetGdipColor(Gdiplus::Color* set);

        MfxReturn SetPRGB(UINT32 set);
        MfxReturn SetRGB(LONG setA, UINT32 set);

        MfxReturn SetD2D1ColorF(D2D1_COLOR_F* set);

    public:
        MfxReturn GetA(LONG* ret);
        MfxReturn GetR(LONG* ret);
        MfxReturn GetG(LONG* ret);
        MfxReturn GetB(LONG* ret);

    public:
        MfxReturn SetA(LONG set);
        MfxReturn SetR(LONG set);
        MfxReturn SetG(LONG set);
        MfxReturn SetB(LONG set);


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

        MfxGlide(MfxGlide* set);
        MfxGlide(MfxGlide& set) :MfxGlide(&set) {};
        MfxGlide(MfxGlide&& set) noexcept :MfxGlide(&set) {};

        ~MfxGlide();

        MfxReturn Clone(MfxBase** ret);

        MfxBase& operator=(MfxBase& rhs);

        MfxGlide& operator=(MfxGlide* rhs);
        MfxGlide& operator=(MfxGlide& rhs);
        MfxGlide& operator=(MfxGlide&& rhs);

        bool operator==(MfxBase& rhs);

        bool operator==(MfxGlide* rhs);
        bool operator==(MfxGlide& rhs);
        bool operator==(MfxGlide&& rhs);

    public:
        MfxReturn SetFPS(UINT set);

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
        MfxReturn EachFrame(WPARAM wParam, LPARAM lParam);

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
