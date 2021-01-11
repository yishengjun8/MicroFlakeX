#pragma once
#include "MfxBasicModules.h"

namespace MicroFlakeX
{
	class MFX_MOUDULEDLL_IMPORT MfxBasicFile;

}

namespace MicroFlakeX
{
	class MfxBasicFile
		: public MfxBasicObject
	{
	public:
		MfxBasicFile();
		virtual ~MfxBasicFile();
	};
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

namespace MicroFlakeX
{
	class MfxIni
		: public MfxBasicFile
	{
		DEFINE_AUTOBASIC;
	protected:
		void MfxIniInitData();
	public:
		MfxIni();
		virtual ~MfxIni();
		void operator=(MfxIni& rhs);

	public:
		MfxReturn Clone(MfxIni** ret);
	};
}
