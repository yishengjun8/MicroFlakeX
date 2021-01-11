#include "pch.h"
#include "MfxBasicFile.h"


using MicroFlakeX::MfxIni;

BEGIN_INITDATA(MfxIni)
END_INITDATA;

BEGIN_AUTOMAP(MfxIni)
END_AUTOMAP;

void MicroFlakeX::MfxIni::MfxIniInitData()
{
}

MicroFlakeX::MfxIni::MfxIni()
{
}

MicroFlakeX::MfxIni::~MfxIni()
{
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxIni::Clone(MfxIni** ret)
{
	return MfxReturn();
}
