#include "MfxTest.h"


MFX_OBJ_REFLECTION_INIT(MfxTest)
MFX_OBJ_REFLECTION_ENDINIT(MfxTest, MfxBase,
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
