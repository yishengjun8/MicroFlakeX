#pragma once


namespace MicroFlakeX
{
	typedef std::string MString;

	class MGHOST_DLL_EXPORT MGhost;

	class MGHOST_DLL_EXPORT MGhostWorld;
	class MGHOST_DLL_EXPORT MGhostWorldInput;
}



namespace MicroFlakeX
{
	class MGhost 
		: public MObject
	{
		M_OBJECT;
	public:
		MResult PhantomWorldGo(MGhostWorld& world, MGhostWorldInput& input);
		MResult PhantomWorldResult(MGhostWorld*& world);
	};
}

namespace MicroFlakeX
{
	class MGhostWorld
		: public MObject
	{
		M_OBJECT;
	public:

	};
}


namespace MicroFlakeX
{
	typedef MResult(*iterFunc)();
	class MGhostWorldInput
		: public MObject
	{
		M_OBJECT;
	public:
		MResult InsertCommand(const char* key, const char* command);
		MResult PushBackCommand();

	public:

	};
}