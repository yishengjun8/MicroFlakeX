#pragma once
#include "MfxAppFrame.h"


#ifdef MFXDLL_BUILDING
#define MFX_PORT __declspec(dllexport)
#else
#define MFX_PORT __declspec(dllimport)
#pragma comment(lib, "MfxButton.lib")
#include "MfxAppFrame.h"

#endif


namespace MicroFlakeX
{
	class MFX_PORT MfxButton;
}
namespace MicroFlakeX
{
#define BUTTON_MSG(MSG) const MfxMessage MSG = __MicroFlakeX::MSG_COUNT()
#define BUTTON_EVENT(MSG) const MfxMessage MSG = __MicroFlakeX::MSG_COUNT()


}
namespace MicroFlakeX
{

	class MfxButton :
		public MfxFlake
	{
	public:
		MfxButton();




	};
}

