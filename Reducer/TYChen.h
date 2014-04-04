
#ifndef T_Y_CHEN_H
#define T_Y_CHEN_H

#include "Reducer/Reducer.h"
#include "Reducer/Greedy.h"

namespace TestReduce
{
	class TYChen : public Reducer
	{
	public:

	protected:
		bool FindEssentialTest(
			    const std::list<TestReq*> &,
				const std::list<TestCase*> &,
				std::list<TestCase*>::const_iterator &
				);

		void RefineReqs(
			    std::list<TestReq*> &,
				const std::list<TestCase*>::iterator &
				);

	private:

    };	//class TYChen
    
}	//namespace TestReduce

#endif
