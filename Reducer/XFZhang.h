
#ifndef X_F_ZHANG_H
#define X_F_ZHANG_H

#include "Reducer/Reducer.h"
#include <set>

namespace TestReduce
{
	class XFZhang : public Reducer
    {
	public:
        void reduce(
			const std::vector<TestReq*> &Reqs,
			const std::vector<TestCase> &initTests,
			std::vector<TestCase> &resultTests
			);

		char const * name() { return "X.F. Zhang"; }

	private:
		std::vector<TestReq*> reducedReqs_;
		
		std::set<TestReq*> goalReqs_;
		std::vector<TestReq*> goalVec_;
		int wayOfInter_;

		void reduceReq(const std::vector<TestReq*> &Reqs);

		void reduceTests(std::vector<TestCase> const& init,
			std::vector<TestCase> &resultTests);
		void eraseReqsByOneTest(std::vector<TestCase> const& init,
			std::vector<TestCase> &resultTests);

		bool findOneTest(std::vector<TestCase> const& init,
			std::vector<TestCase> &resultTests,
			std::vector<std::vector<int> > const& combs);
		bool satisfyComb(TestCase const& test,
			std::vector<std::vector<int> > const& combs);

		void refineGoals(std::vector<int> const& comb);

		void initGoalReqs();

    };	//class XFZhang
    
}	//namespace TestReduce

#endif
