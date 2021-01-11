#pragma once


#include "MfxBasicModules.h"

namespace MicroFlakeX
{
	class MFX_MOUDULEDLL_IMPORT MfxBasicSound;

}

namespace MicroFlakeX
{
	class MfxBasicSound
		: public MfxBasicObject
	{
	public:
		MfxBasicSound();
		virtual ~MfxBasicSound();
	};
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

namespace MicroFlakeX
{
	class MfxSound
		: public MfxBasicSound
	{
		DEFINE_AUTOBASIC;
	protected:
		void MfxSoundInitData();
	public:
		MfxSound();
		virtual ~MfxSound();
		void operator=(MfxSound& rhs);

	public:
		MfxReturn Clone(MfxSound** ret);
	};
}
