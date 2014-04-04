#include "GRE.h"

namespace TestReduce
{
	void GRE::reduce(
			const std::vector<TestReq*> &Reqs,
			const std::vector<TestCase*> &initTests,
			std::list<TestCase*> &resultTests
			)
	{
		InitGRE(Reqs,initTests);
		std::list<TestCase*>::iterator test_iter;

		do
		{
			while(FindEssentialTest(workReqs,workTests,test_iter))
			{
				resultTests.push_back(*test_iter);
				RefineReqs(workReqs,test_iter);
				test_iter=workTests.erase(test_iter);
			}

			while(DelRedundantTest());
		}
		while(FindEssentialTest(workReqs,workTests,test_iter));

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

	void GRE::InitGRE(
			const std::vector<TestReq*> &Reqs,
			const std::vector<TestCase*> &initTests
			)
	{
		workReqs.assign(Reqs.begin(),Reqs.end());
		workTests.assign(initTests.begin(),initTests.end());
	}

	bool GRE::DelRedundantTest()
	{
		std::list<TestReq*> temp_reqs;

		for(std::list<TestCase*>::iterator test_iter=workTests.begin();
			test_iter!=workTests.end();
			++test_iter)
		{
			temp_reqs.clear();

			for(std::list<TestReq*>::iterator req_iter=workReqs.begin();
				req_iter!=workReqs.end();
				++req_iter)
			{
				if((*req_iter)->satisfy(*test_iter))
				{
					temp_reqs.push_back(*req_iter);
				}
			}

			for(std::list<TestCase*>::iterator temp_test_iter=workTests.begin();
				temp_test_iter!=workTests.end();
				++temp_test_iter)
			{
				if(!(*temp_test_iter==*test_iter))
				{
					for(std::list<TestReq*>::iterator temp_req_iter=temp_reqs.begin();
						temp_req_iter!=temp_reqs.end();
						++temp_req_iter)
					{
						if(!(*temp_req_iter)->satisfy(*temp_test_iter))
						{
							break;
						}
					}

					if(temp_req_iter==temp_reqs.end())
					{
						workTests.erase(test_iter);
						return true;
					}
				}
			}
		}

		return false;
	}
    
}	//namespace TestReduce

