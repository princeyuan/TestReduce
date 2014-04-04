#include "Harrold.h"

namespace TestReduce
{
	void Harrold::reduce(
			const std::vector<TestReq*> &Reqs,
			const std::vector<TestCase*> &initTests,
			std::list<TestCase*> &resultTests
			)
	{
		InitHarrold(Reqs,initTests);

		PartitionReqs();

		while(!req_sets.empty())
		{
			std::list<std::list<TestReq*> >::iterator req_set_iter=req_sets.begin();
			while(!req_set_iter->empty())
			{
				std::list<TestCase*>::iterator test_iter;
				test_iter=SatisfyBest(req_set_iter);
				resultTests.push_back(*test_iter);
				RefineReqs(test_iter);
			}
			req_sets.pop_front();
		}
	}

	void Harrold::InitHarrold(
			const std::vector<TestReq*> &Reqs,
			const std::vector<TestCase*> &initTests
			)
	{
		req_sets.clear();
		uncoveredReqs.assign(Reqs.begin(),Reqs.end());
		leavedTests.assign(initTests.begin(),initTests.end());
	}

	void Harrold::PartitionReqs()
	{
		int max_count=0;
		std::list<int> count_satisfy_list;
		std::list<TestReq*> temp_req_list;

		for(std::list<TestReq*>::iterator req_iter=uncoveredReqs.begin();
			req_iter!=uncoveredReqs.end();
			++req_iter)
		{
			int count=0;
			for(std::list<TestCase*>::iterator test_iter=leavedTests.begin();
				test_iter!=leavedTests.end();
				++test_iter)
			{
				if((*req_iter)->satisfy(*test_iter))
				{
					count++;
				}
			}
			count_satisfy_list.push_back(count);
			if(count>max_count)
			{
				max_count=count;
			}
		}

		for(int i=max_count;i>=1;i--)
		{
			std::list<TestReq*>::iterator req_iter;
			std::list<int>::iterator count_iter;
			for(count_iter=count_satisfy_list.begin(),req_iter=uncoveredReqs.begin();
				count_iter!=count_satisfy_list.end(),req_iter!=uncoveredReqs.end();
				++count_iter,++req_iter)
			{
				if(*count_iter==i)
				{
					temp_req_list.push_back(*req_iter);
				}
			}
			req_sets.push_front(temp_req_list);
			temp_req_list.clear();
		}
	}

	void Harrold::SatisfyMost_in_ReqSet(
		    const std::list<std::list<TestReq*> >::iterator &req_set_iter,
		    std::list<std::list<TestCase*>::iterator> &test_iter_list
		    )
	{
		int max_count=0;
		std::list<int> count_list;
		std::list<std::list<TestCase*>::iterator> temp_test_iter_list;

		if(test_iter_list.empty())
		{
			for(std::list<TestCase*>::iterator test_iter=leavedTests.begin();
				test_iter!=leavedTests.end();
				++test_iter)
			{
				temp_test_iter_list.push_back(test_iter);
			}
		}
		else
		{
			temp_test_iter_list=test_iter_list;
			test_iter_list.clear();
		}

		std::list<std::list<TestCase*>::iterator>::iterator test_iter_iter;
		for(test_iter_iter=temp_test_iter_list.begin();
			test_iter_iter!=temp_test_iter_list.end();
			++test_iter_iter)
		{
			int count=0;
			
			for(std::list<TestReq*>::iterator temp_req_iter=req_set_iter->begin();
				temp_req_iter!=req_set_iter->end();
				++temp_req_iter)
			{
				if((*temp_req_iter)->satisfy(*(*test_iter_iter)))
				{
					count++;
				}
			}

			count_list.push_back(count);

			if(max_count<count)
			{
				max_count=count;
			}
		}

		std::list<int>::iterator count_iter;
		for(count_iter=count_list.begin(),test_iter_iter=temp_test_iter_list.begin();
			count_iter!=count_list.end(),test_iter_iter!=temp_test_iter_list.end();
			++count_iter,++test_iter_iter)
		{
			if(max_count==*count_iter)
				test_iter_list.push_back(*test_iter_iter);
		}
	}

	std::list<TestCase*>::iterator Harrold::SatisfyBest(const std::list<std::list<TestReq*> >::iterator &req_set_iter)
	{
		std::list<std::list<TestReq*> >::iterator temp_req_set_iter=req_set_iter;
		std::list<std::list<TestCase*>::iterator> test_iter_list;

		SatisfyMost_in_ReqSet(temp_req_set_iter,test_iter_list);

		while(temp_req_set_iter!=req_sets.begin())
		{
			if(1==test_iter_list.size())
			{
				return *(test_iter_list.begin());
			}
			else
			{
				SatisfyMost_in_ReqSet(--temp_req_set_iter,test_iter_list);
			}
		}
		return *(test_iter_list.begin());
	}

	void Harrold::RefineReqs(const std::list<TestCase*>::iterator &test_iter)
	{
		for(std::list<std::list<TestReq*> >::iterator temp_req_set_iter=req_sets.begin(); 
			temp_req_set_iter!=req_sets.end();
			++temp_req_set_iter)
		{
			std::list<TestReq*>::iterator req_iter=temp_req_set_iter->begin();
			while(req_iter!=temp_req_set_iter->end() && !temp_req_set_iter->empty())
			{
				if((*req_iter)->satisfy(*test_iter))
				{
					req_iter=temp_req_set_iter->erase(req_iter);
				}
			    else
				{
					++req_iter;
				}
	    	}			
		}
	}
   
}	//namespace TestReduce
