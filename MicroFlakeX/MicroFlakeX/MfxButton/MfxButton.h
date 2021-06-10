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
		MfxReturn HIDE();
		MfxReturn SHOW();

	public:


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


