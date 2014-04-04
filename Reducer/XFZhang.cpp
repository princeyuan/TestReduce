#include <set>

#include "Reducer/XFZhang.h"
#include "Reducer/getNFromM.h"

namespace TestReduce
{
	void XFZhang::reduce(
			const std::vector<TestReq*> &Reqs,
			const std::vector<TestCase> &initTests,
			std::vector<TestCase> &resultTests
			)
	{
		reduceReq(reqs);

		reduceTests(initTests, resultTests);
	}

	void XFZhang::reduceReq(const std::vector<TestReq*> &Reqs)
	{
		std::set<int> superSets;

		int const length = reqs.size();
		for(int i=0; i<length-1; ++i)
		{
			for(int j=i+1; j<length; ++j)
			{
				if( reqs[i]->isSubsetOf(reqs[j]) )
				{
					superSets.insert(j);
				}
				else if( reqs[j]->isSubsetOf(reqs[i]) ) 
				{
					superSets.insert(i);
					break;
				}
			}
		}

		reducedReqs_.clear();
		for(int k=0; k<length; ++k)
		{
			if( superSets.count(k) == 0 )
			{
				reducedReqs_.push_back( reqs[k] );
			}
		}
	}

	void XFZhang::reduceTests(std::vector<TestCase> const& init,
		std::vector<TestCase> &resultTests)
	{
		initGoalReqs();

		while(goalReqs_.size() > 0)
		{
			eraseReqsByOneTest(init, resultTests);
		}
	}

	void XFZhang::initGoalReqs()
	{
		goalReqs_.clear();
		std::copy(reducedReqs_.begin(), reducedReqs_.end(), 
			std::inserter(goalReqs_, goalReqs_.begin()));

		goalVec_.assign(goalReqs_.begin(), goalReqs_.end());

		wayOfInter_ = goalReqs_.size();
	}

	void XFZhang::eraseReqsByOneTest(std::vector<TestCase> const& init,
			std::vector<TestCase> &resultTests)
	{
		while(wayOfInter_>0)
		{
			std::vector<std::vector<int> > combs;
			CPPTestor::GetNFromM getter;
			getter.NFromM(wayOfInter_, goalReqs_.size(), combs); 

			if( findOneTest(init, resultTests, combs) )
				break;

			--wayOfInter_;
		}
	}

	bool XFZhang::findOneTest(std::vector<TestCase> const& init,
		std::vector<TestCase> &resultTests,
		std::vector<std::vector<int> > const& combs)
	{
		int const length = init.size();
		for(int i=0; i<length; ++i)
		{
			if( satisfyComb(init[i], combs) )
			{
				resultTests.push_back( init[i] );
				return true;
			}
		}

		return false;
	}

	bool XFZhang::satisfyComb(TestCase const& test,
			std::vector<std::vector<int> > const& combs)
	{
		int const length = combs.size();
		for(int i=0; i<length; ++i)
		{
			bool satisfyAll = true;

			for(int j=0; j<combs[i].size(); ++j)
			{
				satisfyAll = satisfyAll && goalVec_[ combs[i][j] ]->satisfy(test);
				if( !satisfyAll )
					break;
			}

			if(satisfyAll)
			{
				refineGoals( combs[i] );
				return true;
			}
		}
		return false;
	}

	void XFZhang::refineGoals(std::vector<int> const& comb)
	{
		std::vector<int>::const_iterator end = comb.end();
		for(std::vector<int>::const_iterator it = comb.begin();
			it != end;
			++it)
		{
			goalReqs_.erase( goalVec_[*it] );
		}

		goalVec_.assign(goalReqs_.begin(), goalReqs_.end());
	}


	
}	//namespace TestReduce

