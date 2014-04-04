#include "TYChen.h"

namespace TestReduce
{
	bool TYChen::FindEssentialTest(
			    const std::list<TestReq*> &Reqs,
				const std::list<TestCase*> &Tests,
				std::list<TestCase*>::const_iterator &test_iter
				)
	{
		for(std::list<TestReq*>::const_iterator req_iter=Reqs.begin();
			req_iter!=Reqs.end();
			++req_iter)
		{
			int count=0;

			for(std::list<TestCase*>::const_iterator temp_test_iter=Tests.begin();
				temp_test_iter!=Tests.end();
				++temp_test_iter)
			{
				if((*req_iter)->satisfy(*temp_test_iter))
				{
					count++;
				}
			}

			if(1==count)
			{
				for(temp_test_iter=Tests.begin();
					temp_test_iter!=Tests.end();
					++temp_test_iter)
				{
					if((*req_iter)->satisfy(*temp_test_iter))
					{
						test_iter=temp_test_iter;
						return true;
					}
				}
			}
		}

		return false;
	}

	void TYChen::RefineReqs(
			    std::list<TestReq*> & Reqs,
				const std::list<TestCase*>::iterator &test_iter
				)
	{
		for(std::list<TestReq*>::iterator req_iter=Reqs.begin();
			req_iter!=Reqs.end();
			++req_iter)
		{
			if((*req_iter)->satisfy(*test_iter))
			{
				req_iter=Reqs.erase(req_iter);
				--req_iter;
			}
		}
	}
    
}	//namespace TestReduce

