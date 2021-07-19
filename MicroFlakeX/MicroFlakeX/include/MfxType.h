#pragma once

namespace MicroFlakeX
{
    class MFX_DLL_EXPORT MfxRect;
    class MFX_DLL_EXPORT MfxSize;
    class MFX_DLL_EXPORT MfxPoint;

    class MFX_DLL_EXPORT MfxColor;
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
        MFX_OBJ_ENABLE_REFLECTION;
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
        MfxReturn MFX_OBJ_ENABLE_CLONE(ret);

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

        bool operator==(const MfxRect* rhs) const;
        bool operator==(const MfxRect& rhs) const;
        bool operator==(const MfxRect&& rhs) const;

    public:
        operator D2D1_RECT_L() const;
        operator D2D1_RECT_U() const;
        operator D2D1_RECT_F() const;

        operator D2D1_SIZE_U() const;
        operator D2D1_SIZE_F() const;

        operator D2D1_POINT_2L() const;
        operator D2D1_POINT_2U() const;
        operator D2D1_POINT_2F() const;

        operator Gdiplus::Rect() const;
        operator Gdiplus::RectF() const;

        operator Gdiplus::Size() const;
        operator Gdiplus::SizeF() const;

        operator Gdiplus::Point() const;
        operator Gdiplus::PointF() const;

    public:
        MfxReturn Reset(const LONG setX, const LONG setY, const LONG setWidth, const LONG setHeight);
    
    public:
        MfxReturn GetRect(MfxRect* ret) const;
        MfxReturn GetSize(MfxSize* ret) const;
        MfxReturn GetPoint(MfxPoint* ret) const;

        MfxReturn GetRECT(RECT* ret) const;
        MfxReturn GetSIZE(SIZE* ret) const;
        MfxReturn GetPOINT(POINT* ret) const;
      
        MfxReturn GetGdipRect(Gdiplus::Rect* ret) const;
        MfxReturn GetGdipRectF(Gdiplus::RectF* ret) const;

        MfxReturn GetGdipSize(Gdiplus::Size* ret) const;
        MfxReturn GetGdipSizeF(Gdiplus::SizeF* ret) const;

        MfxReturn GetGdipPoint(Gdiplus::Point* ret) const;
        MfxReturn GetGdipPointF(Gdiplus::PointF* ret) const;

    public:
        MfxReturn GetD2D1RectL(D2D1_RECT_L* ret) const;
        MfxReturn GetD2D1RectU(D2D1_RECT_U* ret) const;
        MfxReturn GetD2D1RectF(D2D1_RECT_F* ret) const;

        MfxReturn GetD2D1SizeU(D2D1_SIZE_U* ret) const;
        MfxReturn GetD2D1SizeF(D2D1_SIZE_F* ret) const;

        MfxReturn GetD2D1Point2L(D2D1_POINT_2L* ret) const;
        MfxReturn GetD2D1Point2U(D2D1_POINT_2U* ret) const;
        MfxReturn GetD2D1Point2F(D2D1_POINT_2F* ret) const;

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
        MfxReturn GetX(LONG* ret) const;
        MfxReturn GetY(LONG* ret) const;
        MfxReturn GetWidth(LONG* ret) const;
        MfxReturn GetHeight(LONG* ret) const;

        MfxReturn GetTop(LONG* ret) const;
        MfxReturn GetLeft(LONG* ret) const;
        MfxReturn GetRight(LONG* ret) const;
        MfxReturn GetBottom(LONG* ret) const;

        MfxReturn GetCenter(MfxPoint* ret) const;
        MfxReturn GetPointPosition(MfxPoint* ret1, MfxPoint* ret2) const;
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
        MfxReturn Union(const MfxRect* set, MfxRect* ret) const;
        MfxReturn Union_Widely(MfxBase* set, MfxRect* ret);

        /* 交 */
        MfxReturn Intersect(const MfxRect* set, MfxRect* ret) const;
        MfxReturn Intersect_Widely(MfxBase* set, MfxRect* ret);

        /* 移动到最近的内部矩形 */
        MfxReturn InsideRect(const MfxRect* set, MfxRect* ret) const;
        //MfxReturn InsideRect_Widely(MfxBase* set, MfxRect* ret);

    public:
        /* 偏移 */
        MfxReturn Offset(const LONG setX, const LONG setY);

        /* 膨胀 */
        MfxReturn Inflate(const LONG setX, const  LONG setY);

    public:
        /* 判断是否为空 */
        MfxReturn IsEmpty(bool* ret) const;

        /* 判断矩形是否在矩形内 */
        MfxReturn IsRectInside(const MfxRect* set, bool* ret) const;

        /* 判断点是否在矩形内 */
        MfxReturn IsPointInside(const MfxPoint* set, bool* ret) const;

    public:
        LONG myX;
        LONG myY;
        LONG myWidth;
        LONG myHeight;
    };
}

namespace MicroFlakeX
{
    class MfxSize :
        public MfxBase
    {
        MFX_OBJ_ENABLE_REFLECTION;
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
        MfxReturn MFX_OBJ_ENABLE_CLONE(ret);

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
        bool operator==(const MfxSize& rhs) const;
        bool operator==(const MfxSize&& rhs) const;

    public:
        operator D2D1_SIZE_U() const;
        operator D2D1_SIZE_F() const;

        operator Gdiplus::Size() const;
        operator Gdiplus::SizeF() const;

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
    class MfxPoint :
        public MfxBase
    {
        MFX_OBJ_ENABLE_REFLECTION;
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
        MfxReturn MFX_OBJ_ENABLE_CLONE(ret);

        MfxBase& operator=(MfxBase& rhs);

        MfxPoint& operator=(const MfxRect* rhs);
        MfxPoint& operator=(const MfxRect& rhs);
        MfxPoint& operator=(const MfxRect&& rhs);

        MfxPoint& operator=(const MfxPoint* rhs);
        MfxPoint& operator=(const MfxPoint& rhs);
        MfxPoint& operator=(const MfxPoint&& rhs);

    public:
        bool operator==(MfxBase& rhs);

        bool operator==(const MfxPoint* rhs) const;
        bool operator==(const MfxPoint& rhs) const;
        bool operator==(const MfxPoint&& rhs) const;

    public:
        operator D2D1_POINT_2L() const;
        operator D2D1_POINT_2U() const;
        operator D2D1_POINT_2F() const;

        operator Gdiplus::Point() const;
        operator Gdiplus::PointF() const;

    public:
        MfxReturn Reset(const LONG setX, const LONG setY);

    public:
        MfxReturn GetPoint(MfxPoint* ret) const;

        MfxReturn GetPOINT(POINT* ret) const;

        MfxReturn GetGdipPoint(Gdiplus::Point* ret) const;
        MfxReturn GetGdipPointF(Gdiplus::PointF* ret) const;

        MfxReturn GetD2D1Point2L(D2D1_POINT_2L* ret) const;
        MfxReturn GetD2D1Point2U(D2D1_POINT_2U* ret) const;
        MfxReturn GetD2D1Point2F(D2D1_POINT_2F* ret) const;

    public:
        MfxReturn SetPoint(const MfxPoint* set);

        MfxReturn SetPOINT(const POINT* set);

        MfxReturn SetGdipPoint(const Gdiplus::Point* set);
        MfxReturn SetGdipPointF(const Gdiplus::PointF* set);

        MfxReturn SetD2D1Point2L(const D2D1_POINT_2U* set);
        MfxReturn SetD2D1Point2U(const D2D1_POINT_2U* set);
        MfxReturn SetD2D1Point2F(const D2D1_POINT_2F* set);

    public:
        MfxReturn GetX(LONG* ret) const;
        MfxReturn GetY(LONG* ret) const;

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
    class MfxColor :
        public MfxBase
    {
        MFX_OBJ_ENABLE_REFLECTION;
    public:
        MfxColor();
        MfxColor(MfxBase& set);

        MfxColor(const MfxColor* set);
        MfxColor(const MfxColor& set) :MfxColor(&set) {};
        MfxColor(const MfxColor&& set)noexcept :MfxColor(&set) {};

        MfxColor(const LONG setA, const LONG setR, const LONG setG, const LONG setB);

        ~MfxColor();

    public:
        MfxReturn MFX_OBJ_ENABLE_CLONE(ret);

        MfxBase& operator=(MfxBase& rhs);

        MfxColor& operator=(const MfxColor* rhs);
        MfxColor& operator=(const MfxColor& rhs);
        MfxColor& operator=(const MfxColor&& rhs);

    public:
        bool operator==(MfxBase& rhs);

        bool operator==(const MfxColor* rhs) const;
        bool operator==(const MfxColor& rhs) const;
        bool operator==(const MfxColor&& rhs) const;

    public:
        operator COLORREF() const;
        operator D2D1_COLOR_F() const;
        operator Gdiplus::Color() const;

    public:
        MfxReturn Reset(const LONG setA, const LONG setR, const LONG setG, const LONG setB);

    public:
        MfxReturn GetColor(MfxColor* ret) const;
        MfxReturn GetGdipColor(Gdiplus::Color* ret) const;

        MfxReturn GetPRGB(UINT32* ret) const;
        MfxReturn GetRGB(LONG* retA, COLORREF* ret) const;

        MfxReturn GetD2D1ColorF(D2D1_COLOR_F* ret) const;

    public:
        MfxReturn SetColor(const MfxColor* set);
        MfxReturn SetGdipColor(const Gdiplus::Color* set);

        MfxReturn SetPRGB(const UINT32 set);
        MfxReturn SetRGB(const LONG setA, const UINT32 set);

        MfxReturn SetD2D1ColorF(const D2D1_COLOR_F* set);

    public:
        MfxReturn GetA(LONG* ret) const;
        MfxReturn GetR(LONG* ret) const;
        MfxReturn GetG(LONG* ret) const;
        MfxReturn GetB(LONG* ret) const;

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

