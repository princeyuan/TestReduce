
#ifndef G_R_E_H
#define G_R_E_H

#include "Reducer/TYChen.h"

namespace TestReduce
{
	class GRE : public TYChen
    {
	public:
		void reduce(
			const std::vector<TestReq*> &Reqs,
			const std::vector<TestCase*> &initTests,
			std::list<TestCase*> &resultTests
			);

		char const * name() { return "GRE"; }

	private:
		void InitGRE(
			const std::vector<TestReq*> &Reqs,
			const std::vector<TestCase*> &initTests
			);

		bool DelRedundantTest();

		std::list<TestReq*> workReqs;
		std::list<TestCase*> workTests;
        
    };	//class GRE
    
}	//namespace TestReduce

#endif
