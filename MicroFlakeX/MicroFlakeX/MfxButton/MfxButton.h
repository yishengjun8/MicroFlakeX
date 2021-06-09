#pragma once
#include "MfxAppFrame.h"


namespace MicroFlakeX
{
	class MFX_PORT MfxButton;
}

namespace MicroFlakeX
{
	const MfxMessage BUTTON_BEGIN = WM_APP + 256;

	const MfxMessage BUTTON_MSG_SetBackImage = BUTTON_BEGIN + 1;
	const MfxMessage BUTTON_MSG_SetMaskImage = BUTTON_BEGIN + 2;

	const MfxMessage BUTTON_MSG_SetTitleColor = BUTTON_BEGIN + 3;

	const MfxMessage BUTTON_MSG_SetBackColor = BUTTON_BEGIN + 4;
	const MfxMessage BUTTON_MSG_SetMaskColor = BUTTON_BEGIN + 5;
	const MfxMessage BUTTON_MSG_SetBackFrameSize = BUTTON_BEGIN + 6;
	const MfxMessage BUTTON_MSG_SetMaskFrameSize = BUTTON_BEGIN + 7;

	const MfxMessage BUTTON_MSG_SetWords = BUTTON_BEGIN + 8;
	const MfxMessage BUTTON_MSG_SetImage = BUTTON_BEGIN + 9;
}
namespace MicroFlakeX
{
	class MfxButton :
		public MfxFlake
	{
		MfxObject;
	public:
		MfxButton(MfxRect set = MfxRect(60, 60, 100, 100), pMfxBase father = nullptr);
		~MfxButton();

	public:
		MfxReturn SetBackImage(pMfxImage set);
		MfxReturn SetMaskImage(pMfxImage set);
		
		MfxReturn GetBackImage(pMfxImage* ret);
		MfxReturn GetMaskImage(pMfxImage* ret);

	private:
		MfxReturn OnSetBackImage(MfxParam param);
		MfxReturn OnSetMaskImage(MfxParam param);
	};
}
namespace MicroFlakeX
{

}


