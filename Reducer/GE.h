
#ifndef G_E_H
#define G_E_H

#include "Reducer/TYChen.h"

namespace TestReduce
{
	class GE : public TYChen
    {
	public:
		void reduce(
			const std::vector<TestReq*> &Reqs,
			const std::vector<TestCase*> &initTests,
			std::list<TestCase*> &resultTests
			);

		char const * name() { return "GE"; }

	private:
		void InitGRE(
			const std::vector<TestReq*> &Reqs,
			const std::vector<TestCase*> &initTests
			);

		std::list<TestReq*> workReqs;
		std::list<TestCase*> workTests;
        
    };	//class GE
    
}	//namespace TestReduce

#endif
