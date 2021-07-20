#pragma once

namespace MicroFlakeX
{
    class MFX_DLL_EXPORT MfxGlide;

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
    class MfxGlide
        : public MfxBase
    {
        MFX_OBJ_ENABLE_REFLECTION;
    public:
        MfxGlide();
        ~MfxGlide();

    public:
        MfxReturn SetFPS(MfxNum fps);

        MfxReturn BindObject(MfxBase* bind);

        MfxReturn AddKeyFrame(int key);
        MfxReturn AddKeyFrame(double key);
        MfxReturn AddKeyFrame(MfxBase* key);

        MfxReturn Begin();
    };
}

