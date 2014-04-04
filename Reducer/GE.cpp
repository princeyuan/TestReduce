#include "Reducer/GE.h"
#include "Reducer/Greedy.h"

namespace TestReduce
{
	void GE::reduce(
			const std::vector<TestReq*> &Reqs,
			const std::vector<TestCase*> &initTests,
			std::list<TestCase*> &resultTests
			)
	{
		InitGRE(Reqs,initTests);
		std::list<TestCase*>::iterator test_iter;

		while(FindEssentialTest(workReqs,workTests,test_iter))
		{
			resultTests.push_back(*test_iter);
			RefineReqs(workReqs,test_iter);
			test_iter=workTests.erase(test_iter);
		}

		if(!workReqs.empty())
		{
			Greedy greedymethod;
			std::vector<TestReq*> temp_reqs(workReqs.begin(),workReqs.end());
			std::vector<TestCase*> temp_tests(workTests.begin(),workTests.end());
			std::list<TestCase*> greedy_resultTests;
			greedymethod.reduce(temp_reqs,temp_tests,greedy_resultTests);

			std::copy(greedy_resultTests.begin(),greedy_resultTests.end(),
				std::inserter(resultTests,resultTests.end()));
		}
	}

	void GE::InitGRE(
			const std::vector<TestReq*> &Reqs,
			const std::vector<TestCase*> &initTests
			)
	{
		workReqs.assign(Reqs.begin(),Reqs.end());
		workTests.assign(initTests.begin(),initTests.end());
	}
    
}	//namespace TestReduce

