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
        MfxRect(MfxRect& set);
        MfxRect(MfxRect&& set);

        MfxRect(MfxSize* set);
        MfxRect(MfxSize& set);
        MfxRect(MfxSize&& set);

        MfxRect(MfxPoint* set);
        MfxRect(MfxPoint& set);
        MfxRect(MfxPoint&& set);

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
        bool operator==(MfxBase& rhs) const;

        bool operator==(MfxRect* rhs) const;
        bool operator==(MfxRect& rhs) const;
        bool operator==(MfxRect&& rhs) const;

    public:
        MfxReturn Reset(LONG setX, LONG setY, LONG setWidth, LONG setHeight);
    
    public:
        MfxReturn GetRect(MfxRect* ret) const;
        MfxReturn GetSize(MfxSize* ret) const;
        MfxReturn GetPoint(MfxPoint* ret) const;

        MfxReturn GetRECT(RECT* ret) const;
        MfxReturn GetSIZE(SIZE* ret) const;
        MfxReturn GetPOINT(POINT* ret) const;
      
        MfxReturn GetGdipRect(Gdiplus::Rect* ret) const;
        MfxReturn GetGdipSize(Gdiplus::Size* ret) const;
        MfxReturn GetGdipPoint(Gdiplus::Point* ret) const;

        MfxReturn GetGdipRectF(Gdiplus::RectF* ret) const;
        MfxReturn GetGdipSizeF(Gdiplus::SizeF* ret) const;
        MfxReturn GetGdipPointF(Gdiplus::PointF* ret) const;

        MfxReturn GetD2D1RectU(D2D1_RECT_U* ret) const;
        MfxReturn GetD2D1SizeU(D2D1_SIZE_U* ret) const;
        MfxReturn GetD2D1PointU(D2D1_POINT_2U* ret) const;

        MfxReturn GetD2D1RectF(D2D1_RECT_F* ret) const;
        MfxReturn GetD2D1SizeF(D2D1_SIZE_F* ret) const;
        MfxReturn GetD2D1PointF(D2D1_POINT_2F* ret) const;

    public:
        MfxReturn SetRect(MfxRect* set);
        MfxReturn SetSize(MfxSize* set);
        MfxReturn SetPoint(MfxPoint* set);

        MfxReturn SetRECT(RECT* set);
        MfxReturn SetSIZE(SIZE* set);
        MfxReturn SetPOINT(POINT* set);

        MfxReturn SetGdipRect(Gdiplus::Rect* set);
        MfxReturn SetGdipSize(Gdiplus::Size* set);
        MfxReturn SetGdipPoint(Gdiplus::Point* set);

        MfxReturn SetGdipRectF(Gdiplus::RectF* set);
        MfxReturn SetGdipSizeF(Gdiplus::SizeF* set);
        MfxReturn SetGdipPointF(Gdiplus::PointF* set);

        MfxReturn SetD2D1RectU(D2D1_RECT_U* set);
        MfxReturn SetD2D1SizeU(D2D1_SIZE_U* set);
        MfxReturn SetD2D1PointU(D2D1_POINT_2U* set);

        MfxReturn SetD2D1RectF(D2D1_RECT_F* set);
        MfxReturn SetD2D1SizeF(D2D1_SIZE_F* set);
        MfxReturn SetD2D1PointF(D2D1_POINT_2F* set);

    public:
        MfxReturn GetX(LONG* ret) const;
        MfxReturn GetY(LONG* ret) const;
        MfxReturn GetWidth(LONG* ret) const;
        MfxReturn GetHeight(LONG* ret) const;

        MfxReturn GetTop(LONG* ret) const;
        MfxReturn GetLeft(LONG* ret) const;
        MfxReturn GetRight(LONG* ret) const;
        MfxReturn GetBottom(LONG* ret) const;

    public:
        MfxReturn SetX(LONG set);
        MfxReturn SetY(LONG set);
        MfxReturn SetWidth(LONG set);
        MfxReturn SetHeight(LONG set);

        MfxReturn SetTop(LONG set);
        MfxReturn SetLeft(LONG set);
        MfxReturn SetRight(LONG set);
        MfxReturn SetBottom(LONG set);

    public:
        /* 和 */
        MfxReturn Union(MfxRect* set, MfxRect* ret) const;
        MfxReturn Union_Widely(MfxBase* set, MfxRect* ret) const;

        /* 差 */
        MfxReturn Except(MfxRect* set, MfxRect* ret) const;
        MfxReturn Except_Widely(MfxBase* set, MfxRect* ret) const;

        /* 交 */
        MfxReturn Intersect(MfxRect* set, MfxRect* ret) const;
        MfxReturn Intersect_Widely(MfxBase* set, MfxRect* ret) const;

    public:
        /* 偏移 */
        MfxReturn Offset(LONG setX, LONG setY);

        /* 膨胀 */
        MfxReturn Inflate(LONG setX, LONG setY);

        /* 扩展系数 10 100 1000 倍 */

    public:
        /* 判断是否为空 */
        MfxReturn IsEmpty(bool* ret) const;

        /* 判断点是否在矩形内 */
        MfxReturn IsPointInside(MfxPoint* set, bool* ret) const;

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
        MfxSize(MfxRect& set);
        MfxSize(MfxRect&& set);

        MfxSize(MfxSize* set);
        MfxSize(MfxSize& set);
        MfxSize(MfxSize&& set);

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
        bool operator==(MfxBase& rhs) const;

        bool operator==(MfxSize* rhs) const;
        bool operator==(MfxSize& rhs) const;
        bool operator==(MfxSize&& rhs) const;

    public:
        MfxReturn Reset(LONG setWidth, LONG setHeight);

    public:
        MfxReturn GetSize(MfxSize* ret) const;

        MfxReturn GetSIZE(SIZE* ret) const;;

        MfxReturn GetGdipSize(Gdiplus::Size* ret) const;
        MfxReturn GetGdipSizeF(Gdiplus::SizeF* ret) const;

        MfxReturn GetD2D1SizeF(D2D1_SIZE_F* ret) const;
        MfxReturn GetD2D1SizeU(D2D1_SIZE_U* ret) const;

    public:
        MfxReturn SetSize(MfxSize* set);

        MfxReturn SetSIZE(SIZE* set);

        MfxReturn SetGdipSize(Gdiplus::Size* set);
        MfxReturn SetGdipSizeF(Gdiplus::SizeF* set);

        MfxReturn SetD2D1SizeF(D2D1_SIZE_F* set);
        MfxReturn SetD2D1SizeU(D2D1_SIZE_U* set);

    public:
        MfxReturn GetWidth(LONG* ret) const;
        MfxReturn GetHeight(LONG* ret) const;

    public:
        MfxReturn SetWidth(LONG set);
        MfxReturn SetHeight(LONG set);


    public:
        /* 膨胀 */
        MfxReturn Inflate(LONG setX, LONG setY);

    public:
        /* 判断是否为空 */
        MfxReturn IsEmpty(bool* ret) const;

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
        MfxPoint(MfxRect& set);
        MfxPoint(MfxRect&& set);

        MfxPoint(MfxPoint* set);
        MfxPoint(MfxPoint& set);
        MfxPoint(MfxPoint&& set);

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
        bool operator==(MfxBase& rhs) const;

        bool operator==(MfxPoint* rhs) const;
        bool operator==(MfxPoint& rhs) const;
        bool operator==(MfxPoint&& rhs) const;

    public:
        MfxReturn Reset(LONG setX, LONG setY);

    public:
        MfxReturn GetPoint(MfxPoint* ret) const;

        MfxReturn GetPOINT(POINT* ret) const;

        MfxReturn GetGdipPoint(Gdiplus::Point* ret) const;
        MfxReturn GetGdipPointF(Gdiplus::PointF* ret) const;

        MfxReturn GetD2D1PointU(D2D1_POINT_2U* ret) const;
        MfxReturn GetD2D1PointF(D2D1_POINT_2F* ret) const;

    public:
        MfxReturn SetPoint(MfxPoint* set);

        MfxReturn SetPOINT(POINT* set);

        MfxReturn SetGdipPoint(Gdiplus::Point* set);
        MfxReturn SetGdipPointF(Gdiplus::PointF* set);

        MfxReturn SetD2D1PointU(D2D1_POINT_2U* set);
        MfxReturn SetD2D1PointF(D2D1_POINT_2F* set);

    public:
        MfxReturn GetX(LONG* ret) const;
        MfxReturn GetY(LONG* ret) const;

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
        MfxColor(MfxColor& set);
        MfxColor(MfxColor&& set);

        MfxColor(LONG setA, LONG setR, LONG setG, LONG setB);

        ~MfxColor();

    public:
        MfxReturn Clone(MfxBase** ret);

        MfxBase& operator=(MfxBase& rhs);

        MfxColor& operator=(MfxColor* rhs);
        MfxColor& operator=(MfxColor& rhs);
        MfxColor& operator=(MfxColor&& rhs);

    public:
        bool operator==(MfxBase& rhs) const;

        bool operator==(MfxColor* rhs) const;
        bool operator==(MfxColor& rhs) const;
        bool operator==(MfxColor&& rhs) const;

    public:
        MfxReturn Reset(LONG setA, LONG setR, LONG setG, LONG setB);

    public:
        MfxReturn GetPRGB(UINT32* ret) const;
        MfxReturn GetRGB(LONG* retA, UINT32* ret) const;

        MfxReturn GetD2D1ColorF(D2D1_COLOR_F* ret) const;

    public:
        MfxReturn SetPRGB(UINT32 set);
        MfxReturn SetRGB(LONG setA, UINT32 set);

        MfxReturn SetD2D1ColorF(D2D1_COLOR_F* set);

    public:
        MfxReturn GetA(LONG* ret) const;
        MfxReturn GetR(LONG* ret) const;
        MfxReturn GetG(LONG* ret) const;
        MfxReturn GetB(LONG* ret) const;

    public:
        MfxReturn SetA(LONG ret);
        MfxReturn SetR(LONG ret);
        MfxReturn SetG(LONG ret);
        MfxReturn SetB(LONG ret);


    public:
        LONG myA;
        LONG myR;
        LONG myG;
        LONG myB;
    };
}

namespace MicroFlakeX
{
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
        MfxGulid_GetSet_FuncName(MfxString get, MfxString set)
        {
            myGetFuncName = get;
            mySetFuncName = set;
        }
        MfxGulid_GetSet_FuncName(MfxString type)
        {
            mySetFuncName = myGetFuncName = type;
        }
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
    *   MfxGlide 赖于 MfxBase 的 AutoFunc。
    * 
    *   MfxGlide 允许绑定一个 MfxBase 对象，每帧根据给定参数
        自动调用 MfxBase::AutoFunc(MfxText("BindObjec"), XXX);
    *   
    *   如果对象未注册 AutoFunc 的 BindObjec ，则会调用失败。
    *
    ***************************************************************/
    class MfxGlide
        : public MfxBase
    {
        MfxObject;
    public:
        MfxGlide();

        MfxGlide(MfxGlide* set);
        MfxGlide(MfxGlide& set);
        MfxGlide(MfxGlide&& set);

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
        MfxReturn Add_GetSetFuncName(MfxString groupName, MfxString getFuncName, MfxString setFuncName);

    public:
        MfxReturn GetFPS(UINT& ret);
        MfxReturn GetBindObject(MfxBase** object);

    public:
        MfxReturn Stop();
        MfxReturn Begin();
        MfxReturn Pause();
        MfxReturn Clear();

    public:
        MfxReturn EachFrame(WPARAM wParam, LPARAM lParam);

    public:
        MfxReturn MfxAddKeyframe(MfxString bindObjectType, MfxBase* set, LONGLONG span);

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