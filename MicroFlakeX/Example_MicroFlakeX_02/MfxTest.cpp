#include "MfxTest.h"


MfxObject_Init(MfxTest)
MfxObject_EndInit(MfxTest, MfxBase,
	1, test001

);

MfxReturn MfxTest::test001(int a)
{
	return clock();
}
