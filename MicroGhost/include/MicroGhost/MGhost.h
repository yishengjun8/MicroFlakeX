#pragma once


namespace MicroFlakeX
{
	typedef std::string MString;

	class MGHOST_DLL_EXPORT MGhost;

	class MGHOST_DLL_EXPORT MGhostWorld;
	class MGHOST_DLL_EXPORT MGhostWorldInput;

	class MGHOST_DLL_EXPORT MResource;
}



namespace MicroFlakeX
{
	class MGhost 
		: public MObject
	{
		M_OBJECT;
	public:
		MResult PhantomWorldGoAsyn(MGhostWorld& world, MGhostWorldInput& input);
		MResult PhantomWorldResultAwit(MGhostWorld*& world);

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
	class MGhostWorldInput
		: public MObject
	{
		M_OBJECT;
	public:
		MResult PushBackCommand(MInt32U* command);
		MResult GetCommandSize(MInt32U& size);
		MResult GetCommand(MInt8U num, MInt32U*& command);
		MResult IsEnd(MInt8U num, MBool& is_end);
	public:
	};
}


namespace
{

	class Base
	{


	};


}