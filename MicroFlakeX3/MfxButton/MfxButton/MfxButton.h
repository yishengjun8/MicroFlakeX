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
	const MfxMessage MFX_BUTTON_RESET = __MicroFlakeX::MSG_COUNT_RESET(__MicroFlakeX::MSG_COUNT_BUTTON_BEGIN);
#define BUTTON_MSG(MSG) const MfxMessage MSG = __MicroFlakeX::MSG_COUNT()
#define BUTTON_EVENT(MSG) const MfxMessage MSG = __MicroFlakeX::MSG_COUNT()
	BUTTON_MSG(BUTTON_MSG_SetTitle);
	BUTTON_MSG(BUTTON_MSG_SetTitleSize);
	BUTTON_MSG(BUTTON_MSG_SetTitleColor);

	BUTTON_MSG(BUTTON_MSG_SetBackColor);
	BUTTON_MSG(BUTTON_MSG_SetMaskColor);
	BUTTON_MSG(BUTTON_MSG_SetBackFrameSize);
	BUTTON_MSG(BUTTON_MSG_SetMaskFrameSize);

	BUTTON_MSG(BUTTON_MSG_SetWords);
	BUTTON_MSG(BUTTON_MSG_SetImage);
}
namespace MicroFlakeX
{
	class MfxButton :
		public MfxFlake
	{
		MfxObject;
	public:
		MfxButton();
		~MfxButton();

	public:

	private:
		MfxReturn OnSetTitle(MfxParam param);

		MfxReturn OnSetBackColor(MfxParam param);
		MfxReturn OnSetMaskColor(MfxParam param);
		MfxReturn OnSetTitleColor(MfxParam param);

		MfxReturn OnSetBackFrameSize(MfxParam param);
		MfxReturn OnSetMaskFrameSize(MfxParam param);

		MfxReturn OnSetWords(MfxParam param);
	};
}
namespace MicroFlakeX
{

}


