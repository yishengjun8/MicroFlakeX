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
	class MGhostWorldInput
		: public MObject
	{
		M_OBJECT;
	public:
		MResult PushBackCommand(MInt32U* command);
		MResult GetCommand(MInt8U num, MInt32U*& command);
		MResult IsEnd(MInt8U num, MBool& is_end);
	public:
		class iterator
		{
		private:
			MGhostWorldInput* m_iter;
		public:
			MGhostWorldInput& operator*()
			{
				return *m_iter;
			}
			iterator& operator++()
			{

			}
		};
		iterator* begin();
		iterator* end();
	};
}