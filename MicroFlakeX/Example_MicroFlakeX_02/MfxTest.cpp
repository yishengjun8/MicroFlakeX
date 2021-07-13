#include "MfxTest.h"


MFXOBJ_REFLECTION_INIT(MfxTest)
MFXOBJ_REFLECTION_ENDINIT(MfxTest, MfxBase,
	test001

);

MfxReturn MfxTest::test001(int a)
{
	return clock();
}
