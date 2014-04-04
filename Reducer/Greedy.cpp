#include "Greedy.h"

namespace TestReduce
{
    void Greedy::reduce(
			const std::vector<TestReq*> &Reqs,
			const std::vector<TestCase*> &initTests,
			std::list<TestCase*> &resultTests
			)
	{
		InitGreedy(Reqs,initTests);

		while(!uncoveredReqs.empty() && FindMaxSatisfy())
		{
			resultTests.push_back(*test_iter_maxsatisfy);
			RefineReqs();
			RefineTests();
		}
	}

	void Greedy::InitGreedy(
			const std::vector<TestReq*> &Reqs,
			const std::vector<TestCase*> &initTests
			)
	{
		uncoveredReqs.assign(Reqs.begin(),Reqs.end());
		leavedTests.assign(initTests.begin(),initTests.end());
	}

	bool Greedy::FindMaxSatisfy()
	{
		int max_count_satisfy=0;
		test_iter_maxsatisfy=leavedTests.end();

		for(std::list<TestCase*>::iterator test_iter=leavedTests.begin();
			test_iter!=leavedTests.end();
			++test_iter)
		{
			int count_satisfy=0;

			for(std::list<TestReq*>::iterator req_iter=uncoveredReqs.begin();
				req_iter!=uncoveredReqs.end();
				++req_iter)
			{
				if((*req_iter)->satisfy(*test_iter))
				{
					count_satisfy++;
				}
			}

			if(count_satisfy>max_count_satisfy)
			{
				max_count_satisfy=count_satisfy;
				test_iter_maxsatisfy=test_iter;
			}
		}

		return (max_count_satisfy>0)?true:false;
	}

	void Greedy::RefineReqs()
	{
		for(std::list<TestReq*>::iterator req_iter=uncoveredReqs.begin();
			req_iter!=uncoveredReqs.end();
			++req_iter)
		{
			if((*req_iter)->satisfy(*test_iter_maxsatisfy))
			{
				req_iter=uncoveredReqs.erase(req_iter);
				--req_iter;
			}
		}
	}

	void Greedy::RefineTests()
	{
		leavedTests.erase(test_iter_maxsatisfy);
	}
    
}	//namespace TestReduce
