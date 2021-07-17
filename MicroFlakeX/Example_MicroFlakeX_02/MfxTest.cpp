#include "MfxTest.h"


MFXOBJ_REFLECTION_INIT(MfxTest)
MFXOBJ_REFLECTION_ENDINIT(MfxTest, MfxBase,
	test001,
	test002

);

MfxReturn MfxTest::test001(int a)
{
	
	return clock();
}

MfxReturn MfxTest::test002(MyClass&& a)
{
	std::cout << "test002" << std::endl;
	return 0;
}
