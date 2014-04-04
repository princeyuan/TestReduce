#ifndef GREEDY_H
#define GREEDY_H

#include "Reducer/Reducer.h"

namespace TestReduce
{
    class Greedy : public Reducer
    {
	public:
		void reduce(
			const std::vector<TestReq*> &Reqs,
			const std::vector<TestCase*> &initTests,
			std::list<TestCase*> &resultTests
			);

		char const * name() { return "Greedy"; }
        
	private:

		void InitGreedy(
			const std::vector<TestReq*> &Reqs,
			const std::vector<TestCase*> &initTests
			);

		bool FindMaxSatisfy();

		void RefineReqs();
		void RefineTests();

		std::list<TestReq*> uncoveredReqs;		
		std::list<TestCase*> leavedTests;

		std::list<TestCase*>::iterator test_iter_maxsatisfy;

    };	//class Greedy
    
}	//namespace TestReduce

#endif
